var photo_hash = {};
var set_hash = {};

var hexunAPI = {};
hexunAPI.callMethod = function(APIMethod, params, listener, testingURL, attempts) 
{    
	if (typeof params != 'object') params = {}; // because we are going to stick a few things in even if no params are passed
	params.method = APIMethod; // see? And this also makes sure a method parameter is not passed	
	
	var RESTURLROOT = '/ResponseClient.aspx';
	var RESTURL='';
	for (var p in params) {	    
		if(RESTURL=='')		    
			RESTURL=p + '=' + escape(params[p]);
		else		    
			RESTURL+= '&' + p + '=' + escape(params[p]);
	}
	
	params.RESTURL = RESTURL; // again. we stick this in here because we pass params to the callback, and it might want to see the URL
	
	var attempts = (attempts == undefined) ? 1 : attempts;
	var req = new XMLHttpRequest();
	if (req) 
	{
		req.onreadystatechange = function() 
		{		    
			if (req.readyState == 4) {
				if (req.responseText == '' && attempts<2) 
				{
					attempts++;
					req.abort();
					hexunAPI.callMethod(APIMethod, params, listener, testingURL, attempts);
				} 
				else 
				{
					hexunAPI.handleResponseForTitle(req.responseXML, APIMethod, params, req.responseText, listener);
				}
			}
		}		
		if (testingURL) RESTURLROOT = testingURL;		
		req.open('POST', RESTURLROOT);
		req.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');

		req.send(RESTURL);
	}
}


hexunAPI.getCallBackName = function (dotted) {
	return dotted.split('.').join('_')+'_onLoad';
}

hexunAPI.handleResponseForTitle = function(responseXML, APIMethod, params, responseText, listener) {
	if (!responseXML) { //OPERA!
		var success = (responseText.indexOf('stat="ok"') > -1) ? true : false;
	} else {
		var success = (responseXML.documentElement && responseXML.documentElement.getAttribute('stat') == 'ok') ? true : false;
	}
	listener = (listener) ? listener : this;
	listener[this.getCallBackName(APIMethod)](success, responseXML, responseText);
}

RejectAnonymousComment = function(blogname, commentid)
{    
    var listener = document.getElementById('CheckAnonymousComment_' + commentid);
    
    if(listener != null)
    {
        listener.hexun_photos_rejectComment_onLoad = function(success, responseXML, responseText)
        {            
            if(success)
            {
                var ret = responseXML.documentElement.getElementsByTagName('comment')[0].firstChild.nodeValue;
			    if( ret == "100")
			    {
				    GotoHead();
			    }
			    else if(  ret == "101" )
			    {
				    listener.onclick = '';
				    listener.innerHTML = '[您没有权限执行此操作]'
			    }
			    else if(ret == "200")
			    {				    
				    listener.onclick = '';
				    listener.innerHTML = '[操作成功]';			
			    }
            }
        }
        hexunAPI.callMethod('hexun.photos.rejectComment', {blogname:blogname,rejectComment:1}, listener);
	    return;
    }
    else
    {
        return;
    }
}

dovote = function(articleid,tagid)
{
    var listener = document.getElementById('votelistener_' + articleid);
    
    if(listener != null)
    {
        //alert(responseText);
        listener.hexun_photos_addVote_onLoad = function(success, responseXML, responseText)
        {            
            if(success)
            {
                var ret = responseXML.documentElement.getElementsByTagName('friend')[0].firstChild.nodeValue;
			    if( ret == "100")
			    {
				    GotoHead();
			    }
			    else if(  ret <= 0 )
			    {
				    alert("您已经推荐过此文章了，推荐失败！");
			    }
			    else if(ret > 0)
			    {				    
				    if(document.getElementById("voteCount_"+articleid)!=null)
				    {					   
					    document.getElementById("voteCount_"+articleid).innerHTML = ret;
				    }
				    alert("推荐成功！");				
			    }
            }            
        }
        hexunAPI.callMethod('hexun.photos.addVote', {articleid:articleid,tagid:tagid,addVote:1}, listener);
	    return;
    }
    else
    {
        return;
    }
}

initCheckContent_div = function(title, content)
{
    var listener = document.getElementById('CheckArticleContent');  
    if(listener!=null)
	{
	    listener.hexun_photos_checkTag_onLoad = function(success, responseXML, responseText)
	    {	            
	            var itemsDiv = '';	 
	            if(responseXML.documentElement)
	            {	                
			        if(responseXML.documentElement.getElementsByTagName('keyword'))
			        {
			            var toptagItems = responseXML.documentElement.getElementsByTagName('keyword');
			            if(toptagItems.length > 0)
			            {			        
				            for(var t=0 ; t<toptagItems.length ; t++)
				            {				                
					            if(t == 0)
					            {
					                itemsDiv += toptagItems[t].childNodes[0].nodeValue;
					            }
					            else
					            {
					                itemsDiv += " " + toptagItems[t].childNodes[0].nodeValue;
	                            }			
				            }
			            }			    
        			        
			            if(document.getElementById('TagTextbox'))
	                    {
	                        document.getElementById('TagTextbox').value = itemsDiv;
	                    }	
	                }
	            }  
	            
	            document.getElementById('DealTagSpan').style.display = 'inline';   
                document.getElementById('CheckArticleContent').style.display = 'none';    			
	    }
	    hexunAPI.callMethod('hexun.photos.checkTag', {title:title,content:content,checkTag:1}, listener);
	    return;
	}
	else
	{
	    return;
	}
}

var getUserTags = function()
{
    var listener = document.getElementById('myTagsList');
    if(listener!=null && listener.gettag == null)
	{
	    var getTagspan = document.getElementById('getTagspan').style.display = 'inline';
	    listener.hexun_photos_getTag_onLoad = function(success, responseXML, responseText)
	    {     
            var itemsDiv = '';	 
            if(responseXML.documentElement)
            {
                var userTags = responseXML.documentElement.childNodes[0].nodeValue.split("|");
                var tagsting = "";
                for(var i = 0; i < userTags.length; i++)
                {
                    tagsting += "<A href=\"javascript:selectTag('" + userTags[i] + "')\" class=\"f_black\">" + userTags[i] + "</A>&nbsp;&nbsp;";
//                    if(i%11 == 0)
//                    {
//                        tagsting += "<br/>";
//                    }
                }
                listener.innerHTML = tagsting;
                listener.gettag = true;
            }
	    }
	    hexunAPI.callMethod('hexun.photos.getTag', {getTag:1}, listener);
	    return;
	}
	else
	{
	    return;
	}
}


var getUserGroup = function()
{
    var listener = document.getElementById('userGroupDiv');
    
    if(listener!=null && listener.getgroup == null)
	{
	    var getGroupspan = document.getElementById('userGroupSpan').style.display = 'inline';
	    listener.hexun_User_getGroup_onLoad = function(success, responseXML, responseText)
	    { 
	        var jsonResults = "("+unescape(responseText)+")";
            var resp = eval(jsonResults);
            if(resp.RecordCount > 0)
            {
                var userGroups ="";
                for(var i = 0; i < resp.RecordCount; i++)
                {
                    if(i > 1 && i%3==0)
                     {
                        userGroups+= "<div style='clear:both'><div>";
                     }
                     userGroups += "<div style='width:200px;float:left;'><input type='checkbox' name='checkGroup' onclick='CkeckCo(circleCount)' value='"+resp.Items[i].GroupID +"|"+resp.Items[i].IsNew+"'><a href='" + (resp.Items[i].IsNew=="0"?"http://group.hexun.com/":"http://q.hexun.com/") +resp.Items[i].GroupName+"/default.html' title='"+resp.Items[i].GroupTitle+"' target=_blank>"+resp.Items[i].GroupTitle+"</a></div>";  
                }
                listener.innerHTML = userGroups;
            }
            listener.getgroup = true;
	    }
	    hexunAPI.callMethod('hexun.User.getGroup',{getGroup:1}, listener);
	    return;
	}
	else
	{
	    return;
	}
}

var GetLatestDrafts = function(blogid, blogname, count)
{
    var listener = document.getElementById('LatestDrafts');
    
    if(listener!=null && listener.getdrafts == null)
	{
	    document.getElementById('userDraftsSpan').style.display = 'inline';
	    listener.hexun_User_GetLatestDrafts_onLoad = function(success, responseXML, responseText)
	    { 
	        if(responseXML.documentElement.childNodes[0])
	        {
                document.getElementById('userDraftsSpan').innerHTML = "<b>您的草稿</b>：" + responseXML.documentElement.childNodes[0].nodeValue;
            }
            else
            {
                listener.style.display = 'none';
            }
            listener.getdrafts = true;
	    }
	    hexunAPI.callMethod('hexun.User.GetLatestDrafts',{GetLatestDrafts:1,blogid:blogid,blogname:blogname,count:count}, listener);
	    return;
	}
	else
	{
	    return;
	}
}


//查询自动完成
//编写人：邓旭
//编写时间：2007.08.30
initRelateUser_div = function(username,userid)
{
	var listener = document.getElementById('textRelateUser');
	if(listener!=null)
	{
	    listener.hexun_photos_addRelateUser_onLoad = function(success, responseXML, responseText)
	    {
	        //alert(responseText);
			var itemsDiv = "<table id=\"tblContent\" style=\"background-color:#f4f4f4;border:#ddd 1px solid;width:100%\">";
			var topdiscussionItems = responseXML.documentElement.getElementsByTagName('UserInfo');
			if(topdiscussionItems.length > 0)
			{
				for(var t=0 ; t<topdiscussionItems.length ; t++)
				{
					var id = topdiscussionItems[t].getAttribute('id');
					var username = topdiscussionItems[t].getAttribute('username');
					var blogname = topdiscussionItems[t].getAttribute('blogname');
					var logourl = topdiscussionItems[t].getAttribute('logourl');
					itemsDiv += "<tr><td onmousedown=\"selValue(event);\" style=\"cursor:hand\" onmouseover=\"colorLine(this);\" onmouseout=\"discolorLine(this);\" \" value="+id+" onmouseout=\"clearColor()\">"+username+"<input id='id_"+t+"' name='id_"+t+"' type=hidden value="+id+" /><input id='username_"+t+"' name='username_"+t+"' type=hidden value="+username+" /><input id='blogname_"+t+"' name='blogname_"+t+"' type=hidden value="+blogname+" /><input id='logourl_"+t+"' name='logourl_"+t+"' type=hidden value="+logourl+" /><input name='selectbyid' type=hidden value="+t+" /></td></tr>";
				}
			}
			
			itemsDiv += "</table>";
			//alert(itemsDiv);
			document.getElementById("relateContent").style.display = 'block';
			document.getElementById('relateContent').innerHTML = itemsDiv ;
	    }
	    hexunAPI.callMethod('hexun.photos.addRelateUser', {username:escape(username),userid:userid,relateUser:1}, listener);
	    return;
	}
	else
	{
	    return;
	}
}

checkValueIsFriend = function(username,boardid,userid)
{
    var listener = document.getElementById('textRelateUser');
    
	if(listener!=null)
	{
	    listener.hexun_photos_checkRelateUser_onLoad = function(success, responseXML, responseText)
	    {
	        
			var topdiscussionItems = responseXML.documentElement.getElementsByTagName('UserInfo');
			if(topdiscussionItems.length > 0)
			{
				for(var t=0 ; t<topdiscussionItems.length ; t++)
				{
					var id = topdiscussionItems[t].getAttribute('id');
					var username = topdiscussionItems[t].getAttribute('username');
					var blogname = topdiscussionItems[t].getAttribute('blogname');
					var logourl = topdiscussionItems[t].getAttribute('logourl');
					var hrefid = "a_"+boardid;
                    var imgid = "img_"+boardid;
                    var dlid = "dl_"+boardid;
                    var ddid = "dd_"+boardid;
                    var spanid = "postContent_"+boardid;
                    //判断是否已经被添加过
                    var status = true;   
                    
                    if(boardid > 1)
                    {                       
                        //建立一个数组，比较是否有存在的username
                        var temp = new Array(boardid-1);
                        var count = 0;
                        var len = document.submitform.elements.length;
                        for(var y = 0 ; y < len ; y++)
                        {
                            if(document.submitform.elements[y].name == "postselectbyid")
                            {
                                temp[count] = document.submitform.elements[y].value;
                                count++;
                            }
                        }                        
                        
                        for(var i=0 ; i < temp.length ; i++)
                        {    
                             if(document.getElementById("postusername_"+temp[i]))  
                             {                       
                                if(username == document.getElementById("postusername_"+temp[i]).value)
                                {
                                    status = false;
                                    break;
                                }
                             }
                        }
                    }                                                    
                    
                    if(status == true)
                    {       
                        createInitChild(boardid,id,username,blogname,logourl);  
                    }
                    			
				}
			}
	    }
	    hexunAPI.callMethod('hexun.photos.checkRelateUser', {username:escape(username),boardid:boardid,userid:userid,checkrelate:1}, listener);
	    return;
	}
	else
	{
	    return;
	}
}


