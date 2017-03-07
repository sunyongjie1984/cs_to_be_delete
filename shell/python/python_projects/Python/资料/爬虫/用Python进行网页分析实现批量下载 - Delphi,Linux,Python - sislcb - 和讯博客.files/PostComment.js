//判断标题栏是否为空
function CheckTitle(e)
{
    if(typeof(initAddComment)=="function")
    {
        initAddComment();
    }
    CopyToClipboard('NoHtmlCommentContent');
	if(e.CommentTitle.value=="")
	{
		alert("标题不能为空。");
		return false;
	}
	return true;
}

function CopyToClipboard(theField) 
{
    try
    {
        if (document.all && window.external)
        {
	        eval("tempval = document.getElementById('"+theField+"')");			
	        if(tempval)
	        {
		        tempval.focus();
		        tempval.document.execCommand("SelectAll");
		        tempval.document.execCommand("Copy");
	        }
	    }
	}
	catch(e)
	{
	}
}

//限制下发语长度。
function SymError()
{
	return true;
}
window.onerror = SymError;

function strlength(str)
{
	var l=str.length;
	var n=l;
	for (var i=0;i<l;i++)
	{
		if (str.charCodeAt(i)<0||str.charCodeAt(i)>255)
		{
			n++;
		}
	}
	return n;
}
			
function changebyte1(num,length)
{
	var l=strlength(document.getElementById("NoHtmlCommentContent").value);
	if (l<=length) {
		if (document.all!=null)
		document.getElementById("byte"+num).innerHTML="（您还可以输入"+(length-l)/2+"个字）";
	}
	else
	{
		document.getElementById("byte"+num).innerHTML="(超过2000的字数上限了，请重新编辑。)";
	}
	return true;
}

function CheckNoHtmlCommentContent()
{
    var content = document.getElementById("NoHtmlCommentContent");
    var title = document.getElementById("CommentTitle");
    if(!title.value)
    {
        alert("请输入标题。");
        title.focus();
        return false;
    }
	if(content.value=="")
	{
		alert("请填写内容。");
		content.focus();
		return false;
	}
	if(content.value=="字数上限为2000字")
	{
		alert("请填写内容。");
		content.focus();
		return false;
	}
	
	var CheckL = strlength(content.value);
	if(CheckL>4000)
	{
		alert("超过2000的字数上限了，请重新编辑。");
		content.focus();
		return false;
	}
	
	if(document.getElementById("VerificationDiv").style.display != "none")
	{
	    var vInput = document.getElementById("VerificationInput");
	    if(vInput)
	    {
	        if (vInput.value == "")
	        {
		        alert("请输入验证码。");
		        vInput.focus();
		        return false;
		    }
	    }
	}
	return true;
}