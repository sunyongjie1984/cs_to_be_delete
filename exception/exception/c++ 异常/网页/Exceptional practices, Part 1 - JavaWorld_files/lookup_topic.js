function menu_lookup(){
		if(topicid != (-2) && topicid < 1001) topicid = topicid + 1000;
		if(subtopicid != 0 && subtopicid < 1001) subtopicid = subtopicid + 1000;
		// To display Home
		/*
		if(topicid == (-2)){
		homepage = document.getElementById('hmbar');
		homepage.className='current';
		}
		*/
		// To display the appropriate subtopics 
		var search = 'navbar';
		var fsearch = search + topicid
	   	var test= document.getElementById(fsearch);
		if (test != null) test.className='current';
		
		// To activate red bar above topic 
		var topbar = 'linknav';
		var ftopbar = topbar + topicid;
		var toplink = document.getElementById(ftopbar);
		if (toplink != null) toplink.className = 'current'; 
		
		// To change the span tag of the current topic
		var name = 'showplus';
		var fname = name + topicid;
		var removespan = document.getElementById(fname);
		if (removespan != null) removespan.innerHTML = '';
		
		// To Highlight the appropriate subtopic
		var subsearch = 'subnav';
		var fsubsearch = subsearch + subtopicid;
		var subtopic = document.getElementById(fsubsearch);
		if (subtopic != null) subtopic.className='current';
		
		var botbar = 'sr';
		var botbarsearch = botbar + subtopicid;
		var botbarid = document.getElementById(botbarsearch);
		if (botbarid != null) botbarid.className='current1';
}
	   
	   
	   function getRequestParameter(param){
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