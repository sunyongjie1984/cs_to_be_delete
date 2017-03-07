function ShowHideMenu(obj,obj2)
{
	if(obj.style.display=="none")
	{
		obj.style.display="";
	}
	else
	{
		obj.style.display="none";
	}
	if(obj2.innerText == "╋")
	{
		obj2.innerText = "├";
	}
	else
	{
		obj2.innerText = "╋";
	}
}

function CheckForm()
{
	if(document.getElementById("PostUserName").value=="")
	{
		alert("昵称不能为空");
		return false;
	}
	if(document.getElementById("RndCode").value=="")
	{
		alert("随机码不能为空");
		return false;
	}
	if(document.getElementById("Content").value=="")
	{
		alert("内容不能为空");
		return false;
	}
	return true;
}

function CheckSearchForm()
{
	if(document.getElementById("SearchKeywords").value=="")
	{
		alert("关键字不能为空");
		return false;
	}
	return true;
}