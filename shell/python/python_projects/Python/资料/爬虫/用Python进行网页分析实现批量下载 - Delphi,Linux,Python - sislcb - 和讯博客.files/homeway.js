function MM_reloadPage(init) {  //reloads the window if Nav4 resized
  if (init==true) with (navigator) {if ((appName=="Netscape")&&(parseInt(appVersion)==4)) {
    document.MM_pgW=innerWidth; document.MM_pgH=innerHeight; onresize=MM_reloadPage; }}
  else if (innerWidth!=document.MM_pgW || innerHeight!=document.MM_pgH) location.reload();
}
MM_reloadPage(true);
function MM_findObj(n, d) { //v4.01
  var p,i,x;  if(!d) d=document; if((p=n.indexOf("?"))>0&&parent.frames.length) {
    d=parent.frames[n.substring(p+1)].document; n=n.substring(0,p);}
  if(!(x=d[n])&&d.all) x=d.all[n]; for (i=0;!x&&i<d.forms.length;i++) x=d.forms[i][n];
  for(i=0;!x&&d.layers&&i<d.layers.length;i++) x=MM_findObj(n,d.layers[i].document);
  if(!x && d.getElementById) x=d.getElementById(n); return x;
}
var newtop=0
var newleft=0
if (navigator.appName == "Netscape") {
	layerStyleRef="layer.";
	layerRef="document.layers";
	styleSwitch="";
}
else
{
	layerStyleRef="layer.style.";
	layerRef="document.all";
	styleSwitch=".style";
}
function doMouseClick(photoUrl,photoid,width,height) {
	layerName = 'iit'
	eval('var curElement='+layerRef+'["'+layerName+'"]')
	eval('newleft=document.body.clientWidth-curElement'+styleSwitch+'.pixelWidth')
	eval('newtop=document.body.clientHeight-curElement'+styleSwitch+'.pixelHeight')
	if (event.clientX > (document.body.clientWidth - 5 - width))
	{
	newleft=document.body.clientWidth + document.body.scrollLeft - 5 - width
	}
	else
	{
	newleft=document.body.scrollLeft + event.clientX
	}
	eval('curElement'+styleSwitch+'.pixelLeft=newleft')
	if (event.clientY > (document.body.clientHeight - 5 - height))
	{
	newtop=document.body.clientHeight + document.body.scrollTop - 5 - height
	}
	else
	{
	newtop=document.body.scrollTop + event.clientY
	}
	eval('curElement'+styleSwitch+'.pixelTop=newtop')
	curElement.src=photoUrl;
	eval('curElement'+styleSwitch+'.visibility="visible"')
	window.clipboardData.clearData();
	window.clipboardData.setData("text","[图"+photoid+"]");
	document.photoCenter.strTip.value='[图'+photoid+']复制成功！';
}
function doLayerClick() {
	layerName = 'iit'
	eval('var curElement='+layerRef+'["'+layerName+'"]')
	eval('curElement'+styleSwitch+'.visibility="hidden"')
}
function msg() {
	var strMfsg ="使用秘籍：\n点击图片，将看到“[图18188]复制成功！”的提示，然后在写帖子的地方按“Ctrl+V”就可以将图片贴到您的帖子中了。";
	strMfsg+="\n\n贴图中心说明：\n\n";
	strMfsg+="1、“贴图中心”是论坛为大家提供的一个自由上传共享图片的地方。\n";
	strMfsg+="2、“贴图中心”的图片在论坛能非常方便的调用。\n";
	strMfsg+="3、“贴图中心”的发展要靠大家来共同支持。\n";
	strMfsg+="4、还等什么，把你珍藏的宝贝都发上来吧，奖励多多。";	
	alert(strMfsg);
}
function go_channel(){
	this.location = document.photoCenter.fidSelect.options[document.photoCenter.fidSelect.selectedIndex].value;
}
function go_channel1(){
	this.location = document.photoCenter.cataSelect.options[document.photoCenter.cataSelect.selectedIndex].value;
}
function go_channel2(){
	this.location = 'pindex.aspx?listtype='+document.photoCenter.listType.options[document.photoCenter.listType.selectedIndex].value;
}
function popw(url)
{
	var a;
	a = window.open(url,"a","scrollbars=no,left=200,top=66,height=466,width=388");	
}
function OpenAdminVoice(bid)
{
	var a;
	a = window.open("AdminVoice.aspx?bid="+bid,"AdminVoice","scrollbars=no,left=200,top=66,height=198,width=300");	
}
function checkAll()
{
	for (var i=0;i<document.photoCenter.elements.length;i++)
    {
		var e = document.photoCenter.elements[i];
		e.checked = !e.checked;
	}
}
function loadlistType(listType,a){
	for(i=0;i<listType.length;i++){
		if(listType.options[i].value==a)
		listType.options[i].selected=true;
	}
}
var moveWindow = null
function openmove()
{
	var count;
	var photoidArr="";
	count=document.photoCenter.photoidArr.length;
	if (!(count>1))
	{
		if (document.photoCenter.photoidArr.checked==true)
		{
			photoidArr=document.photoCenter.photoidArr.value;
		}
	}
	else
	{
		for (i=0;i<count;i++){
			if (document.photoCenter.photoidArr[i].checked==true)
			{
				if(photoidArr=="")
					photoidArr=document.photoCenter.photoidArr[i].value;
				else
					photoidArr+=","+document.photoCenter.photoidArr[i].value;
			}
		}
	}
	if (photoidArr=="")
	{
		alert("您没有选择图片！");
    }
	else
	{
		if (! moveWindow || moveWindow.closed){
			newWindow = window.open("move.aspx?photoIDArr="+photoidArr,"movewin","status=no,scrollbars=no,resizable=no,left=300,top=150,height=170,width=300");
		}else{
			newWindow.focus();
		}
	}
}
var Code = 0;
var text_enter_url      = "请输入连接网址";
var text_enter_txt      = "请输入连接说明";
var text_enter_image    = "请输入图片网址";
var text_enter_email    = "请输入邮件网址";
var error_no_url        = "您必须连接网址";
var error_no_txt		= "您必须连接说明";
var error_no_email      = "您必须输入邮件网址";
var error_no_gset       = "必须正确按照各式输入！";
var error_no_gtxt       = "必须输入文字！";
function commentWrite(NewCode) {
	document.getElementById("content").value+=NewCode;
	document.getElementById("content").focus();
	return;
}
function Curl() 
{
	var FoundErrors = '';
	var enterURL   = prompt(text_enter_url, "http://");
	if(!enterURL)
	   	FoundErrors += error_no_url;
	if(FoundErrors)
		return;
	var enterTxT   = prompt(text_enter_txt, enterURL);
	if(!enterTxT)
	   	FoundErrors += error_no_txt;
	if(FoundErrors)
		return;
	var ToAdd = "[URL="+enterURL+"]"+enterTxT+"[/URL]";
	document.getElementById("content").value+=ToAdd;	
	document.getElementById("content").focus();
}
function Cemail() 
{
	var emailAddress = prompt(text_enter_email,"");
	if (!emailAddress) { return;}
	var ToAdd = "[EMAIL]"+emailAddress+"[/EMAIL]";
	commentWrite(ToAdd);
}
function Cbold() 
{
	fontbegin="[B]";
	fontend="[/B]";	
	fontchuli();
}
function Citalic() 
{
	fontbegin="[I]";
	fontend="[/I]";
	fontchuli();
}
function Cunder() 
{
	fontbegin="[U]";
	fontend="[/U]";
	fontchuli();
}
function ChangeColor(color) 
{
	fontbegin="[color="+color+"]";
	fontend="[/color]";
	fontchuli();
}
function CSetSize(size)
{
	fontbegin="[size="+size+"]";
	fontend="[/size]";
	fontchuli();
}
//加入图片
function InsertPic(pic) 
{
	fontbegin=" [PIC="+pic+"]";
	fontend="";
	document.getElementById("content").value=document.getElementById("content").value+fontbegin+fontend;
	document.getElementById("content").focus();
}
function fontchuli()
{
	if ((document.selection)&&(document.selection.type == "Text")) 
	{
		var range = document.selection.createRange();
		var ch_text=range.text;
		range.text = fontbegin + ch_text + fontend;
	} 
	else 
	{
	document.getElementById("content").value=fontbegin+document.getElementById("content").value+fontend;
	document.getElementById("content").focus();
	}
}
ie = (document.all)? true:false
if (ie){
function ctlent(eventobject){if(event.ctrlKey && window.event.keyCode==13){this.document.formpost.submit();}}
}
function em(emnum)
{
	var ToAdd = "[em"+emnum+"]";
	commentWrite(ToAdd);
}
function ResetForm()
{
	document.formpost.reset();
	return false;
}
function checkform()
{
	if(document.formpost.title.value.length==0)
	{
		alert("文章标题还没写！");
		document.formpost.title.focus();
		return false;
	}
	if(document.getElementById("content").value.length==0)
	{
		alert("文章内容还没写！");
		document.getElementById("content").focus();
		return false;
	}
	return true;
}
function CheckReplyForm()
{
	if(document.getElementById("content").value.length==0)
	{
		alert("文章内容还没写！");
		document.getElementById("content").focus();
		return false;
	}
	return true;
}
function popwSingleUpload()
{
	var a;
	//a = window.open("/photocenter/singleupload.aspx","uploadphoto","scrollbars=no,left=300,top=150,height=126,width=388");
	var target=window.location.hostname.substring(0,window.location.hostname.indexOf('.hexun.com'));
	a = window.open("http://photo.hexun.com/upload/GroupBBSUpload.aspx?url="+target,"uploadphoto","scrollbars=no,left=100,top=100,height=356,width=600");
}
function popwGetStockImage()
{
	var a;
	//a = window.open("/photocenter/GetStockImage.aspx","GetStockImage","scrollbars=no,left=300,top=150,height=126,width=388");	
	var target=window.location.hostname.substring(0,window.location.hostname.indexOf('.hexun.com'));
	a = window.open("/photocenter/GetStockImage.aspx?url="+target,"uploadphoto","scrollbars=no,left=300,top=150,height=126,width=388");
}
function AddPhoto(photoID)
{
	var ToAdd = "[图"+photoID+"]";
	commentWrite(ToAdd);
}

//cookie的处理……写入
function setCookie (name, value, expires) {

  document.cookie = name + "=" + escape(value) +
    "; expires=" + expires.toGMTString() +  "; path=/";
}
//cookie的处理……读出  
function getCookie(name) {

  var search;

  search = name + "="
  offset = document.cookie.indexOf(search) 
  if (offset != -1) {
    offset += search.length ;
    end = document.cookie.indexOf(";", offset) ;
    if (end == -1)
      end = document.cookie.length;
    return unescape(document.cookie.substring(offset, end));
  }
  else
    return "";
}
//cookie的处理……删除
function deleteCookie(name) {

  var expdate = new Date();
  expdate.setTime(expdate.getTime() - (86400 * 1000 * 1));
  setCookie(name, "", expdate);
}

// 点击用户名，弹出菜单---BEGIN
var NS4;
var IE4;
var mouse_top;
var mouse_left;
var scroll_top;
var scroll_left;
var event_id = "none";
var status_over = false;	
var parent_menu_name = "LeftMenu_parent";
var submenu_left_indent = 70;
var column_height = 18;
var submenu_top_indent = 0;
var mainmenu_top_indent = 0;

NS4 = (document.layers);
IE4 = (document.all);
isWin = (navigator.appVersion.indexOf("Win") != -1)

if (NS4) {
	document.captureEvents(Event.CLICK)
	document.onclick = MouseDown;
} else if (IE4) {
	document.onclick = MouseDown;
}
function MouseDown(e) {
	event_target = event.srcElement;
	event_target = event_target.toString();
	event_check = event_target.indexOf("javascript:LeftPopMenu(");
	if (!status_over) 
	{
		hideAll();
	}
	if (!event_check) 
	{
		viewMenu(event,  parent_menu_name);
	}
}
function hideAll() {
	eval(parent_menu_name + ".style.display = \"none\"");
	if (event_id == "none") return;
	var menu_len = child_menu_array.length;
	for (i=0; i<menu_len; i++) eval(child_menu_array[i] + ".style.display = \"none\"");
}
function viewMenu(e, ar_id) {
	if (ar_id == "none") return;
	menuLocBod = window.document.body;
	xPos = menuLocBod.scrollLeft + event.clientX;
	yPos = event.clientY + menuLocBod.scrollTop;
	screen_height = window.document.body.offsetHeight;
	screen_width = window.document.body.offsetWidth;
	mouse_top = e.y;
	mouse_left = e.x;
	eval("mainmenu_top_indent = " + parent_menu_name + ".children[0].children[0].children.length");
	mainmenu_top_indent = mainmenu_top_indent * column_height;
	if (screen_height > mouse_top + mainmenu_top_indent)
		yPos = event.clientY + menuLocBod.scrollTop;
	else
		yPos = (event.clientY + menuLocBod.scrollTop) - mainmenu_top_indent;
	if (mouse_top - mainmenu_top_indent < 0)
		yPos = event.clientY + menuLocBod.scrollTop;
	eval(ar_id + ".style.pixelTop =" + yPos);
	eval(ar_id + ".style.pixelLeft =" + xPos);
	eval(ar_id + ".style.display = \"\"");
}
function LeftPopMenu(type,uId) {
	if(type==1)
		document.getElementById("LeftMenu_parent").innerHTML=blog;
	else if(type==2){
		document.getElementById("LeftMenu_parent").innerHTML=uinfo_1+uId+uinfo_2+uId+uinfo_3+uId+uinfo_4;
	}
}
var blog="<table border='1' width='78' bordercolor='#000000' cellspacing='0' cellpadding='1'><tr><td width='78' bordercolor='#ffffff' height='18'  style='font-size:9pt;color=40444A;cursor:hand;top:0;left:0' onmouseover=\"this.style.backgroundColor='#cecfce'\" onmouseout=\"this.style.backgroundColor='ffffff'\" bgColor=#ffffff><a href='http://blog.hexun.com/default.aspx' target=_blank>BLOG首页</a></td></tr><tr><td width='78' bordercolor='#ffffff' height='18' style='font-size:9pt;color=40444A;cursor:hand;top:0;left:0' onmouseover=\"this.style.backgroundColor='#cecfce'\" onmouseout=\"this.style.backgroundColor='ffffff'\"  bgColor=#ffffff><a href='http://blog.hexun.com/postarticle.aspx' target=_blank>发表文章</a></td></tr><tr><td width='78' bordercolor='#ffffff' height='18'  style='font-size:9pt;color=40444A;cursor:hand;top:0;left:0' onmouseover=\"this.style.backgroundColor='#cecfce'\" onmouseout=\"this.style.backgroundColor='ffffff'\"  bgColor=#ffffff><a href='http://blog.hexun.com/admingeneral.aspx' target=_blank>进入管理</a></td></tr><tr><td width='78' bordercolor='#ffffff' height='18'  style='font-size:9pt;color=40444A;cursor:hand;top:0;left:0' onmouseover=\"this.style.backgroundColor='#cecfce'\" onmouseout=\"this.style.backgroundColor='ffffff'\" bgColor=#ffffff><span onclick=window.open('http://blog.hexun.com/MessageBoard.aspx')><font color=black>留言板</font></span></td></tr></table>";
var uinfo_1="<table border='1' width='78' bordercolor='#000000' cellspacing='0' cellpadding='1'><tr><td width='78' bordercolor='#ffffff' height='18'  style='font-size:9pt;color=40444A;cursor:hand;top:0;left:0' onmouseover=\"this.style.backgroundColor='#cecfce'\" onmouseout=\"this.style.backgroundColor='ffffff'\" bgColor=#ffffff><a href='http://wayup.hexun.com/userinfo.aspx?id=";
var uinfo_2="' target=_blank>个人信息</a></td></tr><tr><td width='78' bordercolor='#ffffff' height='18'  style='font-size:9pt;color=40444A;cursor:hand;top:0;left:0' onmouseover=\"this.style.backgroundColor='#cecfce'\" onmouseout=\"this.style.backgroundColor='ffffff'\" bgColor=#ffffff><a onclick=window.open('http://hexun.com/address/FriendsAdd.aspx?friend=";
var uinfo_3="',null,'toolbar=no,height=170,width=300')>加为好友</a></td></tr><tr><td width='78' bordercolor='#ffffff' height='18' style='font-size:9pt;color=40444A;cursor:hand;top:0;left:0' onmouseover=\"this.style.backgroundColor='#cecfce'\" onmouseout=\"this.style.backgroundColor='ffffff'\"  bgColor=#ffffff><a href=http://home.hexun.com/address/sendmessage.aspx?userid=";
var uinfo_4=" target=_blank>留言</a></td></tr></table>";

document.write("<div id='LeftMenu_parent' style='position:absolute;Z-INDEX:1115;display:none;top:10;left:10'>");
document.write("<table border='1' width='78' bordercolor='#000000' cellspacing='0' cellpadding='1'>");
document.write("<tr>");
document.write("<td></td>");
document.write("</tr>");
document.write("</table></div>");

