# -*- coding: gb2312 -*-

import os
import sys
import email
import smtplib
import xml.dom.minidom

# 用于调试输出日志
debuglog = 1
debuglogfile = 1
debuglogmail = 0

def Log(sLog):
    if debuglogfile:
        f = open('sendmaillog.txt','a')
        f.write(str(sLog))
        f.write('\r\n')
        f.close()
    if debuglog:
        print str(sLog)
        

# 创建邮件
class MailCreator:
    def __init__(self):
        # 创建邮件的message对象
        self.msg = email.Message.Message()
        self.mail = ""    
        
    def create(self, mailheader, maildata, mailattachlist=[]):
        # mailheader 是dict类型，maildata是list, 且里面第一项为纯文本类型，第二项为html.
        # mailattachlist 是list, 里面为附件文件名
        if not mailheader or not maildata:
            return
        
        for k in mailheader.keys():
            # 对subject要作特殊处理，中文要转换一下。
            # 比如 "我的一个测试邮件" 就要转换为 =?gb2312?b?ztK1xNK7uPay4srU08q8/g==?=
            if k == 'subject':
                self.msg[k] = email.Header.Header(mailheader[k], 'gb2312')           
            else:
                self.msg[k] = mailheader[k]
        # 创建纯文本部分
        body_plain = email.MIMEText.MIMEText(maildata[0], _subtype='plain', _charset='gb2312')
        body_html = None
        # 创建html部分，这个是可选的
        if maildata[1]:
            body_html = email.MIMEText.MIMEText(maildata[1], _subtype='html', _charset='gb2312')
        
        
        # 创建一个multipart, 然后把前面的文本部分和html部分都附加到上面，至于为什么，可以看看mime相关内容
        attach=email.MIMEMultipart.MIMEMultipart()
        attach.attach(body_plain)
        if body_html:
            attach.attach(body_html)
        # 处理每一个附件
        for fname in mailattachlist:
            attachment=email.MIMEText.MIMEText(email.Encoders._bencode(open(fname,'rb').read()))
            # 这里设置文件类型，全部都设置为Application.当然也可以是Image,Audio什么的，这里不管那么多
            attachment.replace_header('Content-type','Application/octet-stream;name="'+os.path.basename(fname)+'"')
            # 一定要把传输编码设置为base64,因为这里默认就是用的base64
            attachment.replace_header('Content-Transfer-Encoding', 'base64')
            attachment.add_header('Content-Disposition','attachment;filename="'+os.path.basename(fname)+'"')
            attach.attach(attachment)
        # 生成最终的邮件            
        self.mail = self.msg.as_string()[:-1] + attach.as_string()
        
        return self.mail
        
# 获取服务器信息
def smtpsetting(xdom):
	xsrv = xdom.getElementsByTagName('smtp')[0]
	
	sServer = xsrv.getAttributeNode('server').nodeValue
	sPort = xsrv.getAttributeNode('port').nodeValue	
	sUser = xsrv.getAttributeNode('user').nodeValue	
	sPwd = xsrv.getAttributeNode('password').nodeValue	
	
	return sServer,sPort,sUser,sPwd
	
# 获取邮件信息
def mailsetting(xdom):
	xsrv = xdom.getElementsByTagName('mail')[0]
	
	sSendTo = xsrv.getAttributeNode('sendto').nodeValue
	sFrom = xsrv.getAttributeNode('from').nodeValue	
	sTitle = xsrv.getAttributeNode('title').nodeValue
	
	sBodyFile = ''
	sAttachFile = []
	for iNode in xsrv.childNodes:
		if iNode.nodeName == 'body':
			sBodyFile = iNode.getAttributeNode('file').nodeValue
		if iNode.nodeName == 'attach':
#			print iNode.getAttributeNode('file').nodeValue	
			sAttachFile.append(iNode.getAttributeNode('file').nodeValue)
		
	return sSendTo,sFrom,sTitle,sBodyFile,sAttachFile

def readxmlgb2312(xmlpath):
	fp = open(xmlpath, 'r')
	content = fp.read()
	fp.close()
	content = content.replace("encoding=\"GB2312\"", " encoding='utf-8'")
	content = content.replace("encoding=\"gb2312\"", " encoding='utf-8'")
	content = content.decode('gb2312').encode('utf-8')
	print content
	xdom = xml.dom.minidom.parseString(content)
	return xdom

# 主函数	
def sendmailxml(xmlfile):

	Log('邮件：'+xmlfile)
	xdom = readxmlgb2312(xmlfile)
	sServer,sPort,sUser,sPwd = smtpsetting(xdom)
	sSendTo,sFrom,sTitle,sBodyFile,sAttachFile = mailsetting(xdom)
	Log('解析服务器参数:'+str(sServer)+str(sPort)+str(sUser)+str(sPwd))
	Log('解析邮件参数:'+str(sSendTo)+str(sFrom)+str(sBodyFile)+str(sAttachFile))
	
	# 邮件设置
	mc = MailCreator()

	sBodyTxt = 'txt'
	f = open(sBodyFile,'rb')
	sBodyTxt = f.read()
	f.close()
	
	
	header = {'from': sFrom, 'to':sSendTo, 'subject':sTitle}
	sBody=[sBodyTxt, 0]#'Not Support HTML View']
	mail = mc.create(header, sBody, sAttachFile)
	
	
	if mail:
		Log('邮件生成成功')

	# 发送邮件到服务器
	smtpsrv = smtplib.SMTP(str(sServer), int(sPort))
	smtpsrv.set_debuglevel(1)
	sret = smtpsrv.ehlo()
	if sret[0]== 250:
            Log('链接服务器成功:' + str(sServer) + ':' + str(sPort))
        else:
            Log('链接服务器失败:' + str(sServer) + ':' + str(sPort) + 'err:' + str(sret))
        
	sret = smtpsrv.login(str(sUser), str(sPwd))
	if sret[0]== 235:
            Log('登陆服务器成功:' + str(sUser))
        else:
            Log('登陆服务器失败:' + str(sUser) + 'err:' + str(sret))
        
	smtpsrv.ehlo()
	try:
            sret = smtpsrv.sendmail(str(sFrom), str(sSendTo), str(mail))
        except Exception, e:
            Log('发送失败' + str(sFrom)+ str(sSendTo)+ 'err:' + str(e))
        smtpsrv.quit()
	smtpsrv.close()
	Log('邮件发送完成')

    # 保存测试邮件
	if debuglogmail:
		f = open('sendmailtest.eml','wb')
		f.write(mail)
		f.close() 
	
		
if __name__ == '__main__':
    
	# 检查参数
	if len(sys.argv) < 2 :
		print '运行方式：python[w].exe sendmailxml.py mail.xml'
		print '     python[w].exe 脚本解释器'
		print '     sendmailxml.py 发送邮件的脚本'
		print '     mail.xml 以一定格式规范的邮件服务器和邮件内容的描述文件'
		print ''
		Log('参数错误')
        else:
            try:
                xmlfile = sys.argv[1]
                sendmailxml(xmlfile)
            except Exception, e:
                Log('程序错误' + str(xmlfile) + ' err:' + str(e))
