//TOP10滑动门
function change_top10(id){
	document.getElementById("top_1").className = "";
	document.getElementById("top_2").className = "";
	document.getElementById("top_3").className = "";
	document.getElementById("top_"+id).className = "myon";
	document.getElementById("top10_1").style.display = "none";
	document.getElementById("top10_2").style.display = "none";
	document.getElementById("top10_3").style.display = "none";
	document.getElementById("top10_"+id).style.display = "block";
}

//广告延展
var intervalId = null;

slideAd('MyMoveAd',10); 
key = 1;
set_search();
function set_foot(){
	if(key != 1) return;
	document.getElementById("tanc").style.top = (document.body.clientHeight - 240) + "px";
	document.getElementById("tanc").style.left = (document.body.clientWidth - 260) + "px";

	document.getElementById("tanc").style.display = "block";
}

function getPosition() { 
	var top = document.documentElement.scrollTop; 
	var left = document.documentElement.scrollLeft; 
	var height = document.documentElement.clientHeight; 
	var width = document.documentElement.clientWidth; 
	return {top:top,left:left,height:height,width:width}; 
}

function close_this(){
	key = 0;
	document.getElementById("tanc").style.display = "none";
}

function set_search(){	
	var ajax = InitAjax();
	if(get_kw() == "undefined" || get_kw() == ""){
		return;
	}
	var url = "/shtml/art_search.php?type=name&keyword=" + get_kw();
	ajax.open("GET",url,false);
	ajax.send();
	err=ajax.responseText;
	document.getElementById("search_title").innerHTML = err;
	document.getElementById("search_foot").innerHTML = err;

	var url = "/shtml/art_search.php?type=keyword&keyword=" + get_kw();
	ajax.open("GET",url,false);
	ajax.send();
	err=ajax.responseText;
	document.getElementById("search_url").href = "http://www.51cto.com/php/search.php?keyword="+err;

	ajax = InitAjax();
	var url = "/shtml/art_search.php?type=art&keyword=" + get_kw();
	ajax.open("GET",url,false);
	ajax.send();
	err=ajax.responseText;
	if(err != ""){
		document.getElementById("search_body").innerHTML = err;
	}else{
		return;
	}
	set_sreach();
	document.getElementById("tanc").style.display = "block";
}

function set_sreach(){
	var win = document.getElementById("tanc").style;
	win.top = (document.body.clientHeight - 220) + "px";
	win.left = (document.body.clientWidth - 260) + "px";
}

function get_kw(){
	url = document.referrer;
	if(url == ""){
		return "";
	}
	urls = url.split("&");
	for(i=0;i<urls.length;i++){
		if(urls[i].match("q=") == "q="){
			return urls[i].substr(urls[i].indexOf("q=")+2,urls[i].length);
		}
		if(urls[i].match("wd=") == "wd="){
			return urls[i].substr(urls[i].indexOf("wd=")+3,urls[i].length);
		}
	}
}




function InitAjax()
{
  var ajax=false; 
  try { 
    ajax = new ActiveXObject("Msxml2.XMLHTTP.3.0"); 
  } catch (e) { 
    try { 
      ajax = new ActiveXObject("Microsoft.XMLHTTP.3.0"); 
    } catch (E) { 
      ajax = false; 
    } 
  }
  if (!ajax && typeof XMLHttpRequest!='undefined') { 
    ajax = new XMLHttpRequest(); 
  } 
  return ajax;
}


function check_clean(){
	if(document.getElementById("msg").innerHTML == "发表评论请注意语言文明"){
		document.getElementById("msg").innerHTML = "";
	}
}

function slideAd(id,nStayTime,sState,nMaxHth,nMinHth){
  this.stayTime=nStayTime*1000 || 3000; 
  this.maxHeigth=nMaxHth || 380; 
  this.minHeigth=nMinHth || 1; 
  this.state=sState || "down" ; 
  var obj = document.getElementById(id); 
  if(intervalId != null)window.clearInterval(intervalId); 
  function openBox(){ 
   var h = obj.offsetHeight; 
   obj.style.height = ((this.state == "down") ? (h + 2) : (h - 2))+"px"; 
    if(obj.offsetHeight>this.maxHeigth){ 
    window.clearInterval(intervalId); 
    } 
    if (obj.offsetHeight<this.minHeigth){ 
    window.clearInterval(intervalId); 
    obj.style.display="none"; 
    } 
  } 
  intervalId = window.setInterval(openBox,2); 
}