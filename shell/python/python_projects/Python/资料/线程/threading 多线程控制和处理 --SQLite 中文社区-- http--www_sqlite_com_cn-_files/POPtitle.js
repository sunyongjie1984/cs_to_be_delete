var currentpos,timer; 

function initialize() 

{ 

timer=setInterval("scrollwindow()",90);

} 

function sc(){

clearInterval(timer); 

}

function scrollwindow() 

{ 

currentpos=document.body.scrollTop; 

window.scroll(0,++currentpos); 

if (currentpos != document.body.scrollTop) 

sc();

} 

document.onmousedown=sc

document.ondblclick=initialize

function open_window(url,name,size)
{ 
 var windowname=window.open(url,name,"left=0,top=0,status=no,scrollbars=no,resizable=no,"+size); 
}
function openwindow(url,name,size)
{ 
 var windowname=window.open(url,name,"left=0,top=0,status=yes,scrollbars=yes,resizable=yes,"+size); 
}
var kmjmmDiscoMusicplay;