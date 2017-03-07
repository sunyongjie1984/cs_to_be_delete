switch(ad_id){
	case 0401:
	var ad_id=0501
		document.write("<script language=\"JavaScript\" src=\"http://www.yesky.com/lbad/050.js\"></script>");break;
	case 0402:
	var ad_id=0502
		document.write("<script language=\"JavaScript\" src=\"http://www.yesky.com/lbad/050.js\"></script>");break;
	case 0403:
	var ad_id=0500003
	document.write("<script language=\"JavaScript\" src=\"http://www.yesky.com/lbad/050000.js\"></script>");break;
	case 0404:
		document.write("");break;
	case 0405:
		document.write("<iframe frameBorder=no width=180 height=400 marginHeight=0 marginWidth=0 name=top scrolling=no scrolling=aotu src=\"http://114.yesky.com/club/mini2.html\"></iframe>");break;
}

if (readCookie("yesky")!="T") 
{
document.write("<form name=\"jumpto\" action=\"http://soft.yesky.com\" method=\"post\" target=\"_blank\"></form>");
document.jumpto.submit();
self.focus();
writeCookie("yesky","T",72) //写入cookie及过期时间，8760为24*365小时，即一年
}

function writeCookie(name, value, hours)//写入cookie的函数，按名称，值，和小时
{
  var expire = "";
  if(hours != null)
  {
    expire = new Date((new Date()).getTime() + hours * 3600000);
    expire = "; expires=" + expire.toGMTString();
  }
  document.cookie = name + "=" + escape(value) + expire + ";path=/";
}

function readCookie(name)//读取cookie函数
{
  var cookievalue = "";
  var search = name + "=";
  if(document.cookie.length > 0)
  { 
    offset = document.cookie.indexOf(search);
    if (offset != -1)
    { 
      offset += search.length;
      end = document.cookie.indexOf(";", offset);
      if (end == -1) end = document.cookie.length;
      cookievalue = unescape(document.cookie.substring(offset, end))
    }
  }
  return cookievalue;
}