<!--
function GetCookie(name) {
  var dc = document.cookie;
  var prefix = name + '=';
  var begin = dc.indexOf('; ' + prefix);
  if (begin == -1) {
    begin = dc.indexOf(prefix);
    if (begin != 0) return null;
  } else
    begin += 2;
  var end = document.cookie.indexOf(';', begin);
  if (end == -1)
    end = dc.length;
  var sret=unescape(dc.substring(begin + prefix.length, end));
  var aret=sret.split('+'); sret=aret.join(' ');
  return sret;
}
function SetCookie(name, value) {
    document.cookie = name + "=" + escape(value) + "; path=/";
}

var sessionid=new String();
var previous_seen=new Number();
var user=new String();
var access=new Number();
var ulevel=new Number();
var npms=new Number();
var usrattr = new Array();

function GetSsnCookie() {
	user='';
	var begin = document.cookie.indexOf('codehq_ssn22=')+13;
	if (begin==12) {return;}
	var end = document.cookie.indexOf(';',begin);
	if (end==-1) end=document.cookie.length;
	var str = unescape(document.cookie.substring(begin,end)); var i=0;

	sessionid = str.substring(i,i+=16);
	for (var j=0;j<7;j++) usrattr[j]=parseInt(str.substring(i,i+=8),16);

	access = usrattr[1];
	ulevel = access;
	previous_seen = usrattr[4];
	npms=usrattr[6];

	while (i<str.length-1) {
		if (str.substring(i,i+2)=="00") break;
		else user+=unescape ("%"+str.substring(i,i+=2));
	};

}


var mo = new Array("Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec");

GetSsnCookie();

function When(ts) {
 var dt = new Date(ts*1000);
 document.write(mo[dt.getMonth()]+" "+dt.getDate()+", "+(dt.getYear()+(dt.getYear()<1900?1900:0)));
 document.write(" at "+((dt.getHours()%12)==0?12:dt.getHours()%12)+":"+(dt.getMinutes()<10?"0":"")+dt.getMinutes()+(dt.getHours()<12?"am":"pm"));
}

var lb;
var tout;

function LoginBox() {
if (tout) clearTimeout (tout);
var s= new String;
if (!user)
{
	if ((dynamic==1)||(dynamic==2)) s+='<form name="loginform" id="loginform" onSubmit="return DoLogin()" method="post">';
	else s+='<form id="loginform" action="/member/login.cgi" method="post"><input type="hidden" name="redirectto" value="'+here+'">';
	s+='<table>';
	s+='<tr><td><b>login:<\/b><\/td><td><input class="txt" name="l" size="4" type="text"><\/td><td><input class="txt" name="p" size="4" type="password"><\/td><td><input class="btn" value="sign in" type="submit"><\/td><\/tr>';
	s+='<tr><td colspan="3" class="right"><label for="rememberme">remember me<input class="chk" name="rememberme" id="rememberme" value="1" type="checkbox"> &nbsp;<\/td>';
	s+=' <td>[<a href="/member/signup.form">register<\/a>]<\/td><\/tr>';
	s+='<\/table>';
	s+='</form>';
}
else
{
	if ((dynamic==1)||(dynamic==2)) s+='<form name="logoutform" id="logoutform" onSubmit="return DoLogout()" method="post">';
	else s+='<form id="logoutform" action="/member/login.cgi" method="post"><input type="hidden" name="redirectto" value="'+here+'">';
	s+='<input type="hidden" name="log" value="out">';
	s+='<table>';
	s+='<tr><td colspan="2">Logged in as: <b>'+user+'<\/b><\/td><\/tr>';
	s+='<tr><td class="right"><input class="btn" value="log out" type="submit"><\/td>';
	s+='<td>[<b><a href="/member/">user cp<\/a><\/b>]';
	if ((npms>0)&&(npms!=1000000)) s+='[<a href="/member/pmlist.cgi">'+npms+'<img src="/img/newmail.gif" alt="You have '+npms+' new PMs" title="You have '+npms+' new PMs"></a>]';
	s+='<\/td><\/tr>';
	s+='<\/table>';
	s+='</form>';
}
if (lb) lb.innerHTML=s;
}

function DoLogout() {
	var head=document.getElementsByTagName('head').item(0);
	var ScriptTag=document.getElementById('loggingscript');
	if (ScriptTag) head.removeChild (ScriptTag);
	lscr=document.createElement('script');
	lscr.src='/member/minilogin.form?log=out';
	lscr.type='text/javascript';
	lscr.id='loggingscript';
	head.appendChild(lscr);
	return false;
}

function DoLogin() {
	var lform=document.loginform.l.value;
	var pform=document.loginform.p.value;
	var remembermeform=document.loginform.rememberme.checked?1:0;
	lb.innerHTML='<table width="150"><tr><td align="center"><small><b>Logging in</b><br><img src="/img/waitblue.gif"><br>please wait</small></td></tr></table>';
	tout=setTimeout('LoginTimeout()',3000); // change to 60000 (1 min)

	var head=document.getElementsByTagName('head').item(0);
	// remove any previous logging script
	var ScriptTag=document.getElementById('loggingscript');
	if (ScriptTag) head.removeChild (ScriptTag);

	//call logging script:
	lscr=document.createElement('script');
	lscr.src='/member/minilogin.form?log=in&l='+escape(lform)+'&p='+escape(pform)+'&rememberme='+remembermeform;
	lscr.type='text/javascript';
	lscr.id='loggingscript';
	head.appendChild(lscr);
	return false;
}

function LoginTimeout() {
	lb.innerHTML='<table width="150"><tr><td align="center"><small><br>Login timeout</small></td></tr></table>';
	setTimeout('LoginBox()',3000); }

// tx: Wrap text in textarea
function tx(txtleft, txtright, elem)
{
	// FF:
	if (elem.setSelectionRange)
		elem.value=elem.value.substring(0,elem.selectionStart)+txtleft+elem.value.substring(elem.selectionStart,elem.selectionEnd)+txtright+elem.value.substring(elem.selectionEnd,elem.value.length);
	// IE:
	else if (document.selection && document.selection.createRange)
	{
		elem.focus();
		var range=document.selection.createRange();
		range.text=txtleft+range.text+txtright;
	}
	// otherwise append:
	else
	{
		elem.value += txtleft + txtright;
	}
}

// -->