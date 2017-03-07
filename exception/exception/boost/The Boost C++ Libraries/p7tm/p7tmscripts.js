function P7_TMenu(b,og) { //v2.5 by Project Seven Development(PVII)
 var i,s,c,k,j,tN,hh;if(document.getElementById){
 if(b.parentNode && b.parentNode.childNodes){tN=b.parentNode.childNodes;}else{return;}
 for(i=0;i<tN.length;i++){if(tN[i].tagName=="DIV"){s=tN[i].style.display;
 hh=(s=="block")?"none":"block";if(og==1){hh="block";}tN[i].style.display=hh;}}
 c=b.firstChild;if(c.data){k=c.data;j=k.charAt(0);if(j=='+'){k='-'+k.substring(1,k.length);
 }else if(j=='-'){k='+'+k.substring(1,k.length);}c.data=k;}if(b.className=='p7plusmark'){
 b.className='p7minusmark';}else if(b.className=='p7minusmark'){b.className='p7plusmark';}}
}

function P7_setTMenu(){ //v2.5 by Project Seven Development(PVII)
 var i,d='',h='<style type=\"text/css\">';if(document.getElementById){
 var tA=navigator.userAgent.toLowerCase();if(window.opera){
 if(tA.indexOf("opera 5")>-1 || tA.indexOf("opera 6")>-1){return;}}
 for(i=1;i<20;i++){d+='div ';h+="\n#p7TMnav div "+d+"{display:none;}";}
 document.write(h+"\n</style>");}
}
P7_setTMenu();

function P7_TMopen(){ //v2.5 by Project Seven Development(PVII)
 var i,x,d,hr,ha,ef,a,ag;if(document.getElementById){d=document.getElementById('p7TMnav');
 if(d){hr=window.location.href;ha=d.getElementsByTagName("A");if(ha&&ha.length){
 for(i=0;i<ha.length;i++){if(ha[i].href){if(hr.indexOf(ha[i].href)>-1){
 ha[i].className="p7currentmark";a=ha[i].parentNode.parentNode;while(a){
 if(a.firstChild && a.firstChild.tagName=="A"){if(a.firstChild.onclick){
 ag=a.firstChild.onclick.toString();if(ag&&ag.indexOf("P7_TMenu")>-1){
 P7_TMenu(a.firstChild,1);}}}a=a.parentNode;}}}}}}}
}

function P7_TMall(a){ //v2.5 by Project Seven Development(PVII)
 var i,x,ha,s,tN;if(document.getElementById){ha=document.getElementsByTagName("A");
 for(i=0;i<ha.length;i++){if(ha[i].onclick){ag=ha[i].onclick.toString();
 if(ag&&ag.indexOf("P7_TMenu")>-1){if(ha[i].parentNode && ha[i].parentNode.childNodes){
 tN=ha[i].parentNode.childNodes;}else{break;}for(x=0;x<tN.length;x++){
 if(tN[x].tagName=="DIV"){s=tN[x].style.display;if(a==0&&s!='block'){P7_TMenu(ha[i]);
 }else if(a==1&&s=='block'){P7_TMenu(ha[i]);}break;}}}}}}
}

function P7_TMclass(){ //v2.5 by Project Seven Development(PVII)
 var i,x,d,tN,ag;if(document.getElementById){d=document.getElementById('p7TMnav');
 if(d){tN=d.getElementsByTagName("A");if(tN&&tN.length){for(i=0;i<tN.length;i++){
 ag=(tN[i].onclick)?tN[i].onclick.toString():false;if(ag&&ag.indexOf("P7_TMenu")>-1){
 tN[i].className='p7plusmark';}else{tN[i].className='p7defmark';}}}}}
}