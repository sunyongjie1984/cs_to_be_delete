var predates = new Array('09/11/2008');
var preshown=0;
var topicid;
var subtopicid;
var practive = 0;
var author = "";
var keywords = "";
var refresh;
var adrefresh = 0;
var timerID = 0;
var agt=navigator.userAgent.toLowerCase();
var is_ie = ((agt.indexOf("msie") != -1) && (agt.indexOf("opera") == -1));
var firefox = (agt.indexOf("firefox") != -1);
var safari = (agt.indexOf("safari") != -1);
if(refresh) adrefresh = refresh;
var adrefresh = 60000 * adrefresh; // 60000ms/ minute
var imusrc = '';
var skysrc = '';
var bannersrc = '';
var myref = '';
// comment out line below for adrotate
if(adrefresh > 0) timerID = setTimeout("switchad()",adrefresh);

if (navigator.appVersion.charAt(0) >= 4)
{
  //http://www.javaworld.com/javaworld/jw-08-2001/jw-0803-exceptions.html?
	var outerref;
	var ref = "";
	if (outerref) ref = outerref;
  ref = ref.substr(7);
  ref = ref.slice(0,ref.indexOf("/"));
  var idgnet_check = new RegExp ("(nww.com$)|(javaworld.com$)|(networkworld.com$)|(nwfusion.com$)|(idg.net$)|(idg.com$)|(www.vortex.net)|(www.nwwsubscribe.com)|(www.e-businessworld.com)|(www.e-commerceworld.com)|(www.year2000world.com)|(www.techinformer.com)","i");

  if (top.location != window.location)
     if (!idgnet_check.test(ref) && is_ie)
       //top.location = window.location;
       top.location.replace(window.location);
}

new_window = null;
function openNewWindow()
{
    new_window = window.open('','new_window','width=800,height=500, scrollbars=yes,resizable=yes,toolbar=no,directories=no,location=no,menubar=no,status=no,left=0,top=0');
    return true;
}

var popWin = null
function openurl(url)
{
  closePopWin()
  popWin=window.open(url,'NewWindow','width=588,height=480,menubar=no,toolbar=no,location=no,scrollbars=0,top=50,left=100');
}

function closePopWin()
{
        if (navigator.appName != "Microsoft Internet Explorer" || parseInt(navigator.appVersion) >=4) //do not close if early IE
        if(popWin != null) if(!popWin.closed) popWin.close()
}

function openWindow(URL,width,height)
{
	var w = screen.width;
	var h = screen.height;
	var left = (w - width) / 2;
	var top = (h - height) / 2;
	var args = "toolbar=0,location=0,scrollbars=1,resizable=1,width=" +
		width + ",height=" + height + ",left=" + left + ",top=" + top;
	nwwWin = window.open(URL,"nwwWin",args);
	nwwWin.focus();
}

function MM_swapImgRestore() { //v3.0
  var i,x,a=document.MM_sr; for(i=0;a&&i<a.length&&(x=a[i])&&x.oSrc;i++) x.src=x.oSrc;
}

function MM_preloadImages() { //v3.0
  var d=document; if(d.images){ if(!d.MM_p) d.MM_p=new Array();
    var i,j=d.MM_p.length,a=MM_preloadImages.arguments; for(i=0; i<a.length; i++)
    if (a[i].indexOf("#")!=0){ d.MM_p[j]=new Image; d.MM_p[j++].src=a[i];}}
}

function MM_findObj(n, d) { //v3.0
  var p,i,x;  if(!d) d=document; if((p=n.indexOf("?"))>0&&parent.frames.length) {
    d=parent.frames[n.substring(p+1)].document; n=n.substring(0,p);}
  if(!(x=d[n])&&d.all) x=d.all[n]; for (i=0;!x&&i<d.forms.length;i++) x=d.forms[i][n];
  for(i=0;!x&&d.layers&&i<d.layers.length;i++) x=MM_findObj(n,d.layers[i].document); return x;
}

function MM_swapImage() { //v3.0
  var i,j=0,x,a=MM_swapImage.arguments; document.MM_sr=new Array; for(i=0;i<(a.length-2);i+=3)
    if ((x=MM_findObj(a[i]))!=null){
			document.MM_sr[j++]=x; if(!x.oSrc) x.oSrc=x.src; if(x.sel != "1") x.src=a[i+2];
	 }
}

function switchad()
{
	//bannersrc= '';
	//skysrc= '';
	if (practive == 0) {
	  var rand = Math.random();
	  if (bannersrc != '') {
	  	if (document.all)	document.frames.banner.location = bannersrc + rand + "?";
			//else document.layers.banner.location = imusrc;
		}
	  if (imusrc != '') {
	  	if (document.all)	document.frames.imu.location = imusrc; + rand + "?"
			//else document.layers.imu.location = imusrc;
		}
	  if (skysrc != '') {
	  	if (document.all)	document.frames.skyscraper.location = skysrc + rand + "?";
			//else document.layers.imu.location = imusrc;
		}	
	  if (bannersrc != '' || imusrc != '' || skysrc != '') {
	  	timerID = setTimeout('switchad()',adrefresh);
	  }
	}
}

function getmouse() {
	if ((typeof prRoll == "function") && (typeof f24 == "function")) document.onmousemove = newmousemove;
}

function newmousemove() {
	f24(e);
	prRoll(e);
}

function showdiv(name) { 
	if (document.getElementById) { // DOM3 = IE5, NS6 
		var obj = document.getElementById(name);
		if (!obj) return;	
		obj.style.visibility = 'visible'; 
	} 
	else { 
		if (document.layers) { // Netscape 4 
			document.dimdiv.visibility = 'visible'; 
		} 
		else { // IE 4 
			document.all.dimdiv.style.visibility = 'visible'; 
		} 
	} 
}

function hidediv(name) { 
	if (document.getElementById) { // DOM3 = IE5, NS6 
		var obj = document.getElementById(name);
		if (!obj) return;
		obj.style.display = 'none'; 
	} 
	else { 
		if (document.layers) { // Netscape 4 
			document.dimdiv.visibility = 'hidden'; 
		} 
		else { // IE 4 
			document.all.dimdiv.style.visibility = 'hidden'; 
		} 
	} 
}

function findPosX(name)
{
	var obj = document.getElementById(name);
	if (!obj) return 10000;
	var curleft = 0;
	if (obj.offsetParent)
	{
		while (obj.offsetParent)
		{
			curleft += obj.offsetLeft
			obj = obj.offsetParent;
		}
	}
	else if (obj.x)
		curleft += obj.x;
	return curleft;
}

function findPosY(name)
{
	var obj = document.getElementById(name);
	if (!obj) return 10000;
	var curtop = 0;
	if (obj.offsetParent)
	{
		while (obj.offsetParent)
		{
			curtop += obj.offsetTop
			obj = obj.offsetParent;
		}
	}
	else if (obj.y)
		curtop += obj.y;
	return curtop;
}

function hbxStrip(a)
{
	 a = a.split("\n").join("");
	 a = a.split("\r").join("");
     a = a.split("|").join("");
     a = a.split("&").join("");
     a = a.split("'").join("");
     a = a.split("#").join("");
     a = a.split("$").join("");
     a = a.split("%").join("");
     a = a.split("^").join("");
     a = a.split("*").join("");
     a = a.split(":").join("");
     a = a.split("!").join("");
     a = a.split("<").join("");
     a = a.split(">").join("");
     a = a.split("~").join("");
     a = a.split(";").join("");
     a = a.split(" ").join("+");
     return a;
}

if (document.getElementsByName) {
  var metaArray = document.getElementsByName('author');
  if(metaArray[0]) author = hbxStrip(metaArray[0].content);
  var metaArray = document.getElementsByName('keywords');
  if(metaArray[0]) keywords = hbxStrip(metaArray[0].content);
}
 
function register(e)
{
	if (!e) e = window.event;
	var element = e.srcElement;
	if(firefox) element = e.target;
	if(safari) element = e.target.parentNode;
	var ref = element.href;
	myref = ref;
   	if(ref && ref.slice(0,ref.indexOf("://")) == "http" && element.target != "_blank") {
      ref = ref.substr(7);
      ref = ref.slice(0,ref.indexOf("/"));
      var idgnet_check = new RegExp ("(nww.com$)|(javaworld.com$)|(networkworld.com$)|(nwfusion.com$)","i");
      if (!idgnet_check.test(ref) && (is_ie || firefox || safari)) {
         element.target = "_blank";
      } 
   	}
	if (typeof customOnclick== "function") customOnclick();
	return true;
}
 
// old auddev functions
var newWin;

function doneNewCookie(Name) {
  var search = Name + "="
  if (document.cookie.length > 0) { 
    // if there are any cookies
    offset = document.cookie.indexOf(search)
    if (offset != -1) return true;
    else return false;
  }else return false;
}

function SetCookie (name, value, expire, path, domain) { 
	var argv = SetCookie.arguments; 
	var argc = SetCookie.arguments.length; 
	var expires = null;
	var expire = (argc > 2) ? argv[2] : null; 
	var path = (argc > 3) ? argv[3] : null; 
	var domain = (argc > 4) ? argv[4] : null; 
	var secure = (argc > 5) ? argv[5] : false; 
	if(expire != null) expires = new Date(expire);
	document.cookie = name + "=" + value + 
	((expires == null) ? "" : ("; expires=" + expires.toGMTString())) + 
	((path == null) ? "" : ("; path=" + path)) + 
	((domain == null) ? "" : ("; domain=" + domain)) + 
	((secure == true) ? "; secure" : ""); 
} 

/* ---- get value of query string param ---- */
function getQueryParamValue (param){
	var q = document.location.search || document.location.href.hash;
	if(q){
		var startIndex = q.indexOf(param +"=");
		var endIndex = (q.indexOf("&", startIndex) > -1) ? q.indexOf("&", startIndex) : q.length;
		if (q.length > 1 && startIndex > -1) {
			return q.substring(q.indexOf("=", startIndex)+1, endIndex);
		}
	}
	return "";
}

// deprecated, keep placeholder in case of legacy calls
function CheckPre() { return null; }

function toggleBox(szDivID, iState) // 1 visible, 0 hidden
{
    if(document.layers)	   //NN4+
    {
       document.layers[szDivID].visibility = iState ? "show" : "hide";
    }
    else if(document.getElementById)	  //gecko(NN6) + IE 5+
    {
        var obj = document.getElementById(szDivID);
        obj.style.display = iState ? "block" : "none";
    }
    else if(document.all)	// IE 4
    {
        document.all[szDivID].style.display = iState ? "block" : "none";
    }
}

function doClear(theText) 
{
     if (theText.value == theText.defaultValue) theText.value = ""
}


function init()
{
	if (typeof customInit == "function") customInit();
	//if (typeof menu_lookup == "function") menu_lookup();
	if (typeof initTip == "function") initTip();
	var maxDepth = Math.max(findPosY('ddepth'),findPosY('rdepth'));

	for (i=10;i>6;i--) {
		if (findPosY('dedepth') > findPosY('ddepth')) {
	    	var id = "depos" + i;
			hidediv(id);
		}
	}
	if (findPosY('rdepth') > 9000) {maxDepth = findPosY('ddepth');}
	if (maxDepth < findPosY('d4end'))hidediv('d4div');
	if (maxDepth < findPosY('d5end')) hidediv('d5div');
	if (practive > 0) { 
	  adrefresh = 0;
	  clearTimeout(timerID);
	}
	// to put external links into _blank
	if (safari) document.addEventListener("click", register, false);
	else document.onclick = register;
}
//  End -->
