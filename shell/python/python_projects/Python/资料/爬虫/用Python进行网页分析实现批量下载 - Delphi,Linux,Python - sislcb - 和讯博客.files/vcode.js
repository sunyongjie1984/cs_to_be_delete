function refreshC_code(aid)
{	
    var pp= Math.round((Math.random()) * 100000000);
	document.getElementById("VerificationPic").src = "http://comment.blog.hexun.com/inc/vcodepic.aspx?pp="+pp;
}

function refreshCode(aid)
{	
    var pp= Math.round((Math.random()) * 100000000);
	document.getElementById("VerificationPic").src = "http://comment.blog.hexun.com/inc/vcodepic.aspx?articleid=" + aid + "&pp="+pp;
}

function refreshCodeV2(aid)
{	
    var pp= Math.round((Math.random()) * 100000000);
	document.getElementById("VerificationPic").src = "http://comment.blog.hexun.com/inc/vcodepic.aspx?articleid=" + aid + "&pp="+pp;
	if (document.getElementById("vcodeHint"))
    {
        document.getElementById("vcodeHint").innerHTML = "看不清楚？换一张吧。（输入不区分大小写）";
    }
    if (document.getElementById("vcodeShow"))
    {
        document.getElementById("vcodeShow").innerHTML = "1";
    }
}

function showCode(aid)
{
    if (document.getElementById("vcodeShow"))
    {
        if (document.getElementById("vcodeShow").innerHTML == "0")
        {
            refreshCodeV2(aid);
        }
    }
}


