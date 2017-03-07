function check_followups() {
	if (this.document.followups_form.name.value == "") { alert("请输入昵称"); this.document.followups_form.name.focus(); return false; }
	if (this.document.followups_form.email.value != "") {
	if (check_email(this.document.followups_form.email.value) == false) {
	alert("请输入正确的Email地址"); this.document.followups_form.email.focus(); return false; } }
	if (this.document.followups_form.content.value == "") { alert("请输入评论内容"); this.document.followups_form.content.focus(); return false; }
	this.document.followups_form.submit();
}

function check_email(str) { var pattern = /^([a-zA-Z0-9_]|\-|\.)+@(([a-zA-Z0-9_]|\-)+\.)+[a-zA-Z]{2,4}$/; return pattern.test(str); }

var replyEmotions = "[:Automan:] [:^^1:] [:^^2:] [:-_-b:] [:^^3:] [:Cry:] [:Orz:] [:Bow:] [:Yeah:] [:Admire:] [:Wakeup:] [:Sao:]";
replyEmotions = replyEmotions.split(" ");
function appendReplyEmotions(i) {
	document.getElementById("replyContent").value += replyEmotions[i];
}

function drawReplyEmotionsInput() {
	for (i = 0; i < replyEmotions.length; i++) {
	document.write('<a href="#" onclick="javascript: appendReplyEmotions('+i+'); return false; ">');
	document.write('<img width="50" height="50" src="http://s.ycul.com/blog.public/emotions/reply/tt'+i+'.gif" style="border: 0; "></a>');
	document.write("\n");
	}
}

function drawReplyEmotionsInputAnon() {
	for (i = 0; i < replyEmotions.length; i++) {
	document.write('<a href="#" onclick="javascript: appendReplyEmotions('+i+'); f_focus(); return false; ">');
	document.write('<img width="50" height="50" src="http://s.ycul.com/blog.public/emotions/reply/tt'+i+'.gif" style="border: 0; "></a>');
	document.write("\n");
	}
}

function f_focus() { if(document.getElementById('authcode_td2').innerHTML==null || document.getElementById('authcode_td2').innerHTML=='') {
document.getElementById('authcode_td1').style.display='block'; document.getElementById('authcode_td2').innerHTML=authcode_td2_str; document.getElementById('authcode_td3').style.display='block';} }

function switchAnonymousReply() {if (document.getElementById('replyFormIsAnonymousCheckbox').checked) {
document.getElementById('replyFormReplierNickName').readOnly = true;document.getElementById('replyFormReplierNickName').disabled = true;
} else {if (confirm('如果不使用你的歪酷账户评论, 将不能显示头像, 且无法追踪这条评论是否被回复, 您确定要继续吗?')){
document.getElementById('replyFormReplierNickName').readOnly = false;document.getElementById('replyFormReplierNickName').disabled = false;
} else {return false;}}return true;}
