from urllib import urlopen  
  
webdata = urlopen("http://ioa.rising.com.cn/OAHome.nsf/Index.htm").read()  
print webdata  

#urllib.urlretrieve(url, filePath + fileName) 