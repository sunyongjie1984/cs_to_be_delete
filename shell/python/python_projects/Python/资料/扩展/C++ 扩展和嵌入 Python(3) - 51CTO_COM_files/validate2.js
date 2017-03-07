function validate(theform) {
	
	if( theform.msg.value == '' || theform.msg.value == ''){
		alert('请输入评论内容');
		theform.msg.focus();
		return false;
	}
	
	if(theform.password.value == '' && theform.nouser.checked==false ){
			alert('请您登陆或选择匿名发表!');
			
			return false;
		}
	if(theform.username.value == '' && theform.nouser.checked==false){
			alert('请您登陆或选择匿名发表!');
			
			return false;
		}
	if( theform.authnum.value == ''){
		alert('请输入验证码');
		theform.authnum.focus();
		return false;
	}

	
}
function big(o)
{
	var zoom=parseInt(o.style.zoom, 10)||100;zoom+=window.event.wheelDelta/12;
	if (zoom>0) o.style.zoom=zoom+'%';
	return false; 
}

var clickCount = 0;
function clearCommentContent(oObject){
	clickCount++;
	if (clickCount == 1){
		oObject.value = "";
	}
}