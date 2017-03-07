from sgmllib import SGMLParser
from string import find, replace, rjust
from threading import Thread
import urllib

__author__ = "Chen Peng (peng.ch@hotmail.com)"
__version__ = "$Revision: 1.0 $"
__date__ = "$Date: 2006/03/03 $"
__copyright__ = "Copyright (c) 2006 Chen Peng"
__license__ = "Python"

__all__ = ["Gif_163_Parser"]

class PDownloadThread( Thread ):
    """
    Download the files in the dict and save them to local files with the given name
    """
    def __init__( self, DictList,i ):
        Thread.__init__( self )
        self.DictList=DictList
        self.pageno=str(i);
  
    def run( self ):    
        for k in self.DictList.keys():
            try:
              print 'Download'+self.DictList[k]+'......'
              uFile=urllib.urlretrieve( self.DictList[k], '.\\files\\'+k+'.'+self.DictList[k].split('.')[self.DictList[k].split('.').__len__()-1])
            except :
               logfile = open('error.log', 'a')
               logfile.write(self.pageno+' '+self.DictList[k]+'   '+k+'\n')
               logfile.close() 
            print 'Save to file '+k       

class Gif_163_Parser( SGMLParser ):
   """
    任务:下载163彩图
    原理:http://mms.163.com/new_web/cm_lv2_pic.jsp?catID=&ord=dDate&page=2&type=1&key=
        从1到415页（共6637）分析得到如下路径：“/fgwx/hhsj/1_060302175613_186/128x128.gif”
   eg:<script>showPic('22930','1','/fgwx/hhsj/1_060302175613_186/128x128.gif','1','编号：22930\n名字: 因为有你\n人气:100');</script>     
   下载路径:http://mmsimg.163.com/new_web/loaditem.jsp/type=1/path=/fgwx/llfj/1_060302175612_995/176x176.gif
   """
   def reset( self ):                             
        SGMLParser.reset( self )
        self.headURL='http://mmsimg.163.com/new_web/loaditem.jsp/type=1/path='
        self.SubURL = []
        self.Links = {}
         
   def start_script( self, attrs ):
        #self.SubURL.extend( [' %s="%s"' % ( key, value ) for key, value in attrs] )
        pass

   def end_script( self ):
        pass
  
   def handle_data( self, text ):
        if find( text, 'showPic' )!=-1:
           self.Links[replace( text.split( '\\n' )[1], '\xc3\xfb\xd7\xd6: ', '' )]=self.headURL+replace ( text.split( ',' )[2], '\'', '' );
           
   def Execute( self ):  
       for i in range( 1, 415 ):
           self.Links.clear;
           try:
               usock = urllib.urlopen( "http://mms.163.com/new_web/cm_lv2_pic.jsp?catID=&ord=dDate&page="+str(i)+"&type=1&key=" )
               self.feed( usock.read() )
               usock.close()                    
               TestThread=PDownloadThread( self.Links ,i)
               TestThread.start()                
               self.close()    
           except IOError:
               pass   
        #print ( ["%s=%sn"% ( k, self.Links[k] ) for k in self.Links.keys()] )
        #print self.Links

if __name__ == '__main__':
    #Gif_163_Parser().Execute();
     testtask=Gif_163_Parser()
     testtask.Execute()