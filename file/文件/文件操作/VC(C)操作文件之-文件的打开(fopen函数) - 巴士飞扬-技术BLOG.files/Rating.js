//********************************************************************************
//** 插件功能:		文章投票插件
//** 插件应用:		Z-Blog(修改getID函数后可用在其它系统上)
//** 插件制作:		软件兔 (http://blog.wyshen.com/ SoftBunny+Soft@Gmail.com)
//** 插件修改:		williamlong  http://www.williamlong.info
//** 备　　注:	
//**
//********************************************************************************
var xmlhttp
var ID=getID();
var Path=getPath();
var Score=0;
var UserScore=0;
var Rnumber=0;

sndReqShowRating();

function getID(){
	var str = document.location.pathname;
	if (PostID)
		return PostID;
	else
		return str.substring(str.lastIndexOf("/")+1,str.lastIndexOf("."));

}

function getPath(){
	var strtmp;
	var scripts=document.getElementsByTagName("script");
	for (i=scripts.length-1; i>0; i--)
		if (scripts[i].src != "")
			if(scripts[i].src.toLowerCase().indexOf("rating.js")>0)
				strtmp = scripts[i].src.toLowerCase().replace("rating.js","");
	if (strtmp!="")
		if (strtmp.substr(0,4).toLowerCase() != "http")
			strtmp=document.location.protocol + "//" + document.location.host + strtmp;
	return strtmp;
}

function myXMLHttpRequest() {
	var xmlhttplocal;
   
	var msxmlhttp = new Array(
	'Msxml2.XMLHTTP.5.0',
	'Msxml2.XMLHTTP.4.0',
	'Msxml2.XMLHTTP.3.0',
	'Msxml2.XMLHTTP',
	'Microsoft.XMLHTTP');
	for (var i = 0; i < msxmlhttp.length; i++) {
		try {
			xmlhttplocal = new ActiveXObject(msxmlhttp[i]);
		} catch (e) {
			xmlhttplocal = null;
		}
	}
	
	if(!xmlhttplocal && typeof XMLHttpRequest != "undefined")
		xmlhttplocal = new XMLHttpRequest();
	if (!xmlhttplocal)
		alert("Could not create connection object.");
	return xmlhttplocal;
}

function sndReqShowRating()
{
	xmlhttp=myXMLHttpRequest();
    xmlhttp.open('get', Path + 'Score' + ID + '.txt?rnd=' + Math.random());
    xmlhttp.onreadystatechange = handleShowRating;
    xmlhttp.send(null);	
}

function handleShowRating() {
	if(xmlhttp.readyState == 4)
	{
		if (xmlhttp.status == 200){
			var Rdata = xmlhttp.responseText.split(",");
			Score = new Number(Rdata[0]);
			Rnumber =  Rdata[1];
		}
		else if (xmlhttp.status == 404)
		{
			Score = 0;
			Rnumber = 0;
		}
		else
		{
			Score = 0;
			Rnumber = 0;
		}
		var strtmp="";
		document.getElementById("RatingPre").innerHTML = "<div id=\"Rating\"><div id=\"Star\"><div id=\"Star-Cur\"><\/div><a href=\"JavaScript:Rating(" + ID + ",1)\" id=\"Star1\" title=\"这么差的文章，怎么写出来的！\"><\/a><a href=\"JavaScript:Rating(" + ID + ",2)\" id=\"Star2\" title=\"马马虎虎，写得不怎么样\"><\/a><a href=\"JavaScript:Rating(" + ID + ",3)\" id=\"Star3\" title=\"一般情况吧\"><\/a><a href=\"JavaScript:Rating(" + ID + ",4)\" id=\"Star4\" title=\"写得不错，再努力呀！\"><\/a><a href=\"JavaScript:Rating(" + ID + ",5)\" id=\"Star5\" title=\"精彩，太值得读了！\"><\/a><\/div><div id=\"Score\"><\/div><\/div>";
		if (Score==0)
		{
			document.getElementById("Star-Cur").style.width = "0px";
			document.getElementById("Score").innerHTML = "<div id=\"Rating-no\">当前尚无评分记录</div>";
		}
		else
		{
			document.getElementById("Star-Cur").style.width = Score * 30 + "px";
			document.getElementById("Score").innerHTML = "<div id=\"Rating-show\">平均得分" + Score.toFixed(2) + "分（共" + Rnumber + "次打分）</div>";
		}
	}
}

function Rating(intID,intScore)
{
	document.getElementById("Score").innerHTML = "<div id=\"Rating-now\">正在投票，请稍候……</div>";
	UserScore=intScore;
	xmlhttp=myXMLHttpRequest();
    xmlhttp.open('get', Path + 'Rating.asp?ID=' + intID + '&S=' + intScore);
    xmlhttp.onreadystatechange = handleRating;
    xmlhttp.send(null);	
}

function handleRating() {
	if(xmlhttp.readyState == 4)
		if (xmlhttp.status == 200){
			var Rdata = xmlhttp.responseText.toLowerCase();
			if (Rdata == "ok")
			{
				Score = (Score*Rnumber+parseInt(UserScore))/(parseInt(Rnumber)+1);
				Score = Score.toFixed(2);
				Rnumber =  parseInt(Rnumber)+1;
				document.getElementById("Star-Cur").style.width = Score * 30 + "px";
				//document.getElementById("Score").innerHTML = "<div id=\"Rating-show\">平均得分" + Score + "分（共" + Rnumber + "次打分）</div>";
				document.getElementById("Score").innerHTML = "<div id=\"Rating-Tanks\">投票成功,感谢您的投票</div>";
			}
			else if (Rdata=="already")
			{
				document.getElementById("Score").innerHTML = "<div id=\"Rating-already\">您已经投过一票了</div>";
			}
			else if (Rdata=="error")
			{
				document.getElementById("Score").innerHTML = "<div id=\"Rating-err\">遇到未知错误，请向作者反映</div>";
			}
			else
			{
				document.getElementById("Score").innerHTML = "<div id=\"Rating-err\">遇到未知错误，请向作者反映</div>";
			}
		}
}