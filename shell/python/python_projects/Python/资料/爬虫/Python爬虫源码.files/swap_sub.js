function topnavi(sid)
{	var i = 1
	if (document.getElementById("topnavi" + sid).style.display == "none")
	{
		while(i<=11){
			document.getElementById("topnavi" + i).style.display = "none";
			i++;
		}
		document.getElementById("topnavi" + sid).style.display = "block";
		
	}else{
	
		document.getElementById("topnavi" + sid).style.display = "block";
	}
}

function sublist(sid)
{	var i = 1
	if (document.getElementById("sublist" + sid).style.display == "none")
	{
		while(i<4){
			document.getElementById("sublist" + i).style.display = "none";
			i++;
		}
		document.getElementById("sublist" + sid).style.display = "block";
		
	}else{
	
		document.getElementById("sublist" + sid).style.display = "block";
	}
}

function sub_list(sid)
{	var i = 1
	if (document.getElementById("sub_list" + sid).style.display == "none")
	{
		while(i<4){
			document.getElementById("sub_list" + i).style.display = "none";
			i++;
		}
		document.getElementById("sub_list" + sid).style.display = "block";
		
	}else{
	
		document.getElementById("sub_list" + sid).style.display = "block";
	}
}

function swap_c(sid)
{	var i = 1
	if (document.getElementById("swap_c" + sid).style.display == "none")
	{
		while(i<5){
			document.getElementById("swap_c" + i).style.display = "none";
			document.getElementById("swaplink" + i).className = "linkdown";
			i++;
		}
		document.getElementById("swap_c" + sid).style.display = "block";
		document.getElementById("swaplink" + sid).className = "linkup";
		
	}else{
	
		document.getElementById("swap_c" + sid).style.display = "block";
		document.getElementById("swaplink" + sid).className = "linkup";
	}
}
//
function download(sid)
{	var i = 1
	if (document.getElementById("download" + sid).style.display == "none")
	{
		while(i<7){
			document.getElementById("download" + i).style.display = "none";
			document.getElementById("downlink" + i).className = "";
			i++;
		}
		document.getElementById("download" + sid).style.display = "block";
		document.getElementById("downlink" + sid).className = "swap_on";
		
	}else{
	
		document.getElementById("download" + sid).style.display = "block";
		document.getElementById("downlink" + sid).className = "swap_on";
	}
}
//
function timg(sid)
{	var i = 1
	if (document.getElementById("timg_c" + sid).style.display == "none")
	{
		while(i<5){
			document.getElementById("timg_c" + i).style.display = "none";
			document.getElementById("tilink" + i).className = "timg_off";
			i++;
		}
		document.getElementById("timg_c" + sid).style.display = "block";
		document.getElementById("tilink" + sid).className = "timg_on";
		
	}else{
	
		document.getElementById("timg_c" + sid).style.display = "block";
		document.getElementById("tilink" + sid).className = "timg_on";
	}
}

//
function dswap(sid)
{	var i = 1
	if (document.getElementById("ds_c" + sid).style.display == "none")
	{
		while(i<3){
			document.getElementById("ds_c" + i).style.display = "none";
			document.getElementById("dslink" + i).className = "";
			i++;
		}
		document.getElementById("ds_c" + sid).style.display = "block";
		document.getElementById("dslink" + sid).className = "dswap_on";
		
	}else{
	
		document.getElementById("ds_c" + sid).style.display = "block";
		document.getElementById("dslink" + sid).className = "dswap_on";
	}
}


var bodyObj;
var AdDiv,AdDiv_Ad,AdDiv_Img,AdDiv_top;
var w_body = 0;
var h_body = 0;

//漂浮广告ID
var piaoFAdId,bodyElement;        

//页面加载初始化
function Init(){
    bodyObj = document.body;    
    //if(isOpenAd())AdInit();           //首页广告
	//PiaoF();            //漂浮广告
	//isOpenAd();
}

function PiaoF(){  
    var tmpstr ="";   	
	var agt=navigator.userAgent.toLowerCase(); 
    var isopera = agt.indexOf('opera')!=-1?true:false;
    bodyElement = ( document.compatMode.toLowerCase()=="css1compat" ) ? document.documentElement : document.body;
    if(isopera) bodyElement=document.body;	
	piaoFAdId = document.createElement("div");
	piaoFAdId.id = "piaoFAdId";
	//piaoFAdId.style.background="url(/ad/ad_yh.jpg)";
	piaoFAdId.className="piaof"
	tmpstr = tmpstr+"<div class=\"piao_top\"><p><a href=\"#\" onclick=\"piaoFAdId.style.display='none';return false;\"><!--关闭--></a></p></div>";
	tmpstr = tmpstr+"<div class=\"piao_m fl\"><div class=\"piao_t\"><p>再爆惊喜：免费班又开班啦！</p></div><div class=\"piao_cont\"><p>为进一步推动中国网络安全事业发展，戴威尔网络安全培训将于12月8号——12月29号再次开放免费班。</p></div></div>";  
	tmpstr = tmpstr+"<div class=\"piao_b fl\"><p><a href=\"/Article/HTML/20681.html\"><!--查看--></a></p></div>";
	piaoFAdId.innerHTML=tmpstr;
	bodyObj.appendChild(piaoFAdId);
	h_body = piaoFAdId.offsetHeight;
	w_body = piaoFAdId.offsetWidth;
    setInterval("PiaoFAd();", 80);	
}

function PiaoFAd() {
	piaoFAdId.style.top = ( bodyElement.scrollTop + bodyElement.clientHeight - h_body ) + "px";
	piaoFAdId.style.left = ( bodyElement.scrollLeft + bodyElement.clientWidth - w_body ) + "px";
}

function AdInit(){	 
	var tmpElement;
	
	AdDiv =  document.createElement("div");
	AdDiv.id="AdDiv"; 
	AdDiv.className="centre"; 
	AdDiv.style.overflow='hidden';
	AdDiv.onmouseover=displayAd;
	AdDiv.style.background="url(/ad/ad_yh.jpg)";
	var oListChilds = document.body.childNodes;	
	bodyObj.insertBefore(AdDiv,oListChilds[0]); 
	
	AdDiv_top =  document.createElement("div");
	AdDiv_top.id="AdDiv_top";	
	AdDiv_top.className="yh_adlink"; 
	AdDiv.appendChild(AdDiv_top);
	
	
	AdDiv_Ad =  document.createElement("div");
	AdDiv_Ad.id="AdDiv_Ad"; 
	AdDiv_Ad.style.width=947+"px";
	AdDiv_Ad.style.height=421+"px";
	AdDiv.appendChild(AdDiv_Ad);
	
	
	tmpElement = document.createElement("p");
	AdDiv_top.appendChild(tmpElement);
	tmpElement.innerHTML ="<a href=\"#\" onclick=\"CloseIndexTopAd();return false;\">关闭</a>" ;
	
	AdDiv_Img =  document.createElement("div");
	AdDiv_Img.id="AdDiv_Img"; 
	AdDiv_Img.style.width=947+"px";
	AdDiv_Img.style.height=421+"px";
	AdDiv_Img.onclick = getAdUrl;
	AdDiv_Img.style.cursor="pointer";
	AdDiv_Ad.appendChild(AdDiv_Img);
	
	IndexTopAd();
	
}
function displayAd(){if(!isOpenAd){Num=1;IndexTopAd();}}
function getAdUrl(){window.location='/Article/HTML/20681.html ';}


//首页大广告
var   delayID=0;   
var   Num=1; 
var OpenAd=false;

//首页头部广告
function IndexTopAd(){
	OpenAd=true;
	delayID=setTimeout("IndexTopAd()",1);  
	
	if(Num<421){		
		AdDiv.style.height=Num+"px";	
	}
	if (Num>3000){			
		AdDiv.style.height=1+"px";
		clearTimeout(delayID);		
	}else{		
		Num += 4;	
	}	
}

function CloseIndexTopAd(){
	AdDiv.style.height=1+"px";
	OpenAd = false;
	clearTimeout(delayID);
}

function piaof(){			
	var piao_topPfHeitht;
	var obj=document.getElementById("piaof");
	
	obj.style.bottom= "20px";
	obj.style.right = "20px";
}

function isOpenAd(){
    var thisUrl = window.location.href;
    
    if(thisUrl == "http://" + window.location.host+"/" || thisUrl.toLowerCase().indexOf("/index.") != -1)
        return true;
    else
        return false;
}