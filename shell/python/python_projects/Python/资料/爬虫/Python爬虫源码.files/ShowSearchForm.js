document.write("<table border='0' cellpadding='0' cellspacing='0'><form method='Get' name='SearchForm' action='/Article/Search.asp'><tr><td height='28' align='center'><select name='Field' size='1'><option value='Title' selected>文章标题</option><option value='Content'>文章内容</option><option value='Author'>文章作者</option><option value='Inputer'>录 入 者</option><option value='Keywords'>关键字</option><option value='ArticleID'>文章ID</option></select>&nbsp;<select name='ClassID'><option value=''>所有栏目</option><option value='1'>最新新闻</option><option value='2'>&nbsp;&nbsp;├&nbsp;安全新闻</option><option value='3'>&nbsp;&nbsp;├&nbsp;业界事件</option><option value='4'>&nbsp;&nbsp;├&nbsp;本站公告</option><option value='5'>&nbsp;&nbsp;├&nbsp;政策法规</option><option value='6'>&nbsp;&nbsp;├&nbsp;黑客现象</option><option value='311'>&nbsp;&nbsp;└&nbsp;今日课程</option><option value='273'>&nbsp;&nbsp;├&nbsp;会员公告</option><option value='12'>基础入门</option><option value='13'>&nbsp;&nbsp;├&nbsp;基础知识</option><option value='14'>&nbsp;&nbsp;├&nbsp;工具介绍</option><option value='16'>&nbsp;&nbsp;├&nbsp;QQ小技巧</option><option value='17'>&nbsp;&nbsp;└&nbsp;免费资源</option><option value='219'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;└&nbsp;黑客教程</option><option value='220'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;├&nbsp;黑客文字教程</option><option value='221'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;└&nbsp;黑客音频教程</option><option value='18'>黑客技术</option><option value='19'>&nbsp;&nbsp;├&nbsp;经验心得</option><option value='20'>&nbsp;&nbsp;├&nbsp;加密解密</option><option value='21'>&nbsp;&nbsp;├&nbsp;病毒知识</option><option value='22'>&nbsp;&nbsp;├&nbsp;Exploit</option><option value='23'>&nbsp;&nbsp;├&nbsp;脚本游戏</option><option value='24'>&nbsp;&nbsp;├&nbsp;后门技术</option><option value='25'>&nbsp;&nbsp;├&nbsp;脚本攻击</option><option value='26'>&nbsp;&nbsp;├&nbsp;代码编写</option><option value='27'>&nbsp;&nbsp;├&nbsp;攻防实战</option><option value='227'>&nbsp;&nbsp;└&nbsp;黑客基础知识</option><option value='228'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;├&nbsp;安全工具介绍</option><option value='229'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;├&nbsp;常见安全漏洞分类</option><option value='230'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;├&nbsp;黑客文化</option><option value='231'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;├&nbsp;网络安全基本知识</option><option value='232'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;├&nbsp;网络攻击方法步骤</option><option value='233'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;└&nbsp;学习方法步骤</option><option value='28'>网络管理</option><option value='29'>&nbsp;&nbsp;├&nbsp;应用安全</option><option value='30'>&nbsp;&nbsp;├&nbsp;网络架设</option><option value='31'>&nbsp;&nbsp;├&nbsp;入侵检测</option><option value='32'>&nbsp;&nbsp;├&nbsp;疑难技巧</option><option value='33'>&nbsp;&nbsp;├&nbsp;数据恢复</option><option value='34'>&nbsp;&nbsp;├&nbsp;无盘网络</option><option value='187'>&nbsp;&nbsp;├&nbsp;防火墙</option><option value='314'>&nbsp;&nbsp;├&nbsp;网络安全产品</option><option value='323'>&nbsp;&nbsp;└&nbsp;网络存储</option><option value='324'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;├&nbsp;存储虚拟化</option><option value='325'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;├&nbsp;网络存储知识</option><option value='326'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;├&nbsp;数据备份与恢复</option><option value='327'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;└&nbsp;网络存储保护与管理</option><option value='36'>程序开发</option><option value='37'>&nbsp;&nbsp;├&nbsp;C和汇编</option><option value='38'>&nbsp;&nbsp;├&nbsp;vc和vb</option><option value='39'>&nbsp;&nbsp;├&nbsp;delphi</option><option value='40'>&nbsp;&nbsp;├&nbsp;其它类别</option><option value='41'>&nbsp;&nbsp;├&nbsp;IT考试</option><option value='328'>&nbsp;&nbsp;└&nbsp;易语言</option><option value='329'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;├&nbsp;易语言编程</option><option value='330'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;├&nbsp;易语言产品介绍</option><option value='331'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;└&nbsp;易语言疑难技巧</option><option value='42'>网页编程</option><option value='43'>&nbsp;&nbsp;├&nbsp;ASP编程</option><option value='44'>&nbsp;&nbsp;├&nbsp;CGI编程</option><option value='45'>&nbsp;&nbsp;├&nbsp;PHP编程</option><option value='46'>&nbsp;&nbsp;├&nbsp;jsp编程</option><option value='47'>&nbsp;&nbsp;├&nbsp;数据库类</option><option value='48'>&nbsp;&nbsp;├&nbsp;其它类别</option><option value='188'>&nbsp;&nbsp;├&nbsp;asp.net</option><option value='189'>&nbsp;&nbsp;├&nbsp;SQL2000</option><option value='190'>&nbsp;&nbsp;├&nbsp;Mysql</option><option value='191'>&nbsp;&nbsp;└&nbsp;XML</option><option value='55'>操作系统</option><option value='59'>&nbsp;&nbsp;├&nbsp;Windows系统</option><option value='234'>&nbsp;&nbsp;│&nbsp;&nbsp;├&nbsp;windows批处理</option><option value='235'>&nbsp;&nbsp;│&nbsp;&nbsp;│&nbsp;&nbsp;├&nbsp;黑客批处理</option><option value='236'>&nbsp;&nbsp;│&nbsp;&nbsp;│&nbsp;&nbsp;├&nbsp;批处理技巧</option><option value='237'>&nbsp;&nbsp;│&nbsp;&nbsp;│&nbsp;&nbsp;├&nbsp;批处理教程文章</option><option value='238'>&nbsp;&nbsp;│&nbsp;&nbsp;│&nbsp;&nbsp;├&nbsp;批处理入门</option><option value='239'>&nbsp;&nbsp;│&nbsp;&nbsp;│&nbsp;&nbsp;└&nbsp;批处理实例</option><option value='296'>&nbsp;&nbsp;│&nbsp;&nbsp;└&nbsp;系统技巧</option><option value='61'>&nbsp;&nbsp;├&nbsp;linux系统</option><option value='224'>&nbsp;&nbsp;│&nbsp;&nbsp;└&nbsp;iptables</option><option value='180'>&nbsp;&nbsp;├&nbsp;UNIX系统</option><option value='240'>&nbsp;&nbsp;└&nbsp;虚拟机</option><option value='241'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;├&nbsp;Bochs</option><option value='242'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;├&nbsp;Cygwin</option><option value='243'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;├&nbsp;KVM</option><option value='244'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;├&nbsp;Parallels</option><option value='245'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;├&nbsp;QEMU</option><option value='246'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;├&nbsp;Virtual</option><option value='247'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;├&nbsp;VirtualBox</option><option value='248'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;├&nbsp;Virtuozzo</option><option value='249'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;├&nbsp;VMware</option><option value='250'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;└&nbsp;XEN</option><option value='62'>协议</option><option value='63'>&nbsp;&nbsp;├&nbsp;协议分析技术</option><option value='64'>&nbsp;&nbsp;├&nbsp;FTP协议</option><option value='65'>&nbsp;&nbsp;├&nbsp;TCPIP协议</option><option value='66'>&nbsp;&nbsp;├&nbsp;WINS协议</option><option value='67'>&nbsp;&nbsp;├&nbsp;DNS协议</option><option value='68'>&nbsp;&nbsp;├&nbsp;DHCP协议</option><option value='69'>&nbsp;&nbsp;├&nbsp;pop3协议</option><option value='70'>&nbsp;&nbsp;├&nbsp;HTTP协议</option><option value='71'>&nbsp;&nbsp;├&nbsp;IPV6协议</option><option value='72'>&nbsp;&nbsp;├&nbsp;SNMP协议</option><option value='73'>&nbsp;&nbsp;└&nbsp;UDP协议</option></select>&nbsp;<input type='text' name='keyword'  size='20' value='关键字' maxlength='50' onFocus='this.select();'>&nbsp;<input type='submit' name='Submit'  value=' 搜索 '></td></tr></form></table>");