

var isUserSelf=false;
var flag=0;
var isLogin=false;
if(!isUserSelf) 
{
     
        if(document.getElementById('tag_bar_title')!=null && document.getElementById('tag_bar_left')!=null)
        {
         document.getElementById('tag_bar_title').innerHTML='联系主人';
         document.getElementById('tag_bar_left').innerHTML="<a href='http://message.hexun.com/Send.aspx?id=3302962' target='_blank' title='发送私信'>发送私信</a> | <a style ='cursor:hand' href='http://hexun.com/3302962/messageboard.html' >给主人留言</a> | <a href='http://i.hexun.com/gift/gift_index.aspx?userid=3302962' target='_blank'>送小礼物</a> | <a  href='http://i.hexun.com/focus/myfocusList.aspx?userid=3302962' target='_blank'>关注主人</a> | <a href='http://message.hexun.com/FriendsAdd.aspx?friend=3302962' target='_blank'>加为好友</a> | <a href='http://i.hexun.com/myhome.html?id=3302962' target='_blank'>进入Ta的家</a>";
        }
}

 if(document.getElementById("SelfTab_Login") !=null)
 {
     var login="";
     if(flag==1)
     {
        if (isLogin)
	    { 				
						
				login+="<a href='http://i.hexun.com/myhome.html' target=_blank>进入我的家</a> | <a href='http://t.hexun.com/' target='_blank'>去我的微博</a> | <a  href='http://utility.tool.hexun.com/quit.aspx?gourl="+document.location.href+"'>登出</a> | ";
		}
		else
		{
				login+="<a href='javascript:GotoLogin()'>登录</a> | <a href='http://reg.hexun.com' target='_blank'>注册</a> | ";
		}
     }
     else
     {
        if (isLogin)
	    { 				
						
			login+="<a href='http://i.hexun.com/myhome.html' target=_blank>进入我的家</a> | <a href='http://t.hexun.com/' target='_blank'>去我的微博</a> | <a  href='http://utility.tool.hexun.com/quit.aspx?gourl="+document.location.href+"'>登出</a> | ";
		}
		else
		{
			login+="<a href='javascript:GotoLogin()'>登录</a> | <a href='http://reg.hexun.com' target='_blank'>注册</a> | ";
		}
     }
     document.getElementById("SelfTab_Login").innerHTML=login;
 }

 function GotoLogin()
 {
    document.location.href='http://reg.hexun.com/login.aspx?gourl='+escape(window.document.location);
 }  
