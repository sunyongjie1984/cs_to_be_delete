var bms={};bms.popup=function(){var popupDiv;var alwaysPopup=false;var interruptTime=10;var callback;this.init=function(A,B,C,D,E){popupDiv=$(A);var closeBtn=$(B);if(closeBtn){Event.observe(closeBtn,"click",this.closeAd);}
if(C){alwaysPopup=true;}else{alwaysPopup=false;}
if(D&&D>0){interruptTime=D;}
if(E&&typeof E=="function"){callback=E;}};this.closeAd=function(){popupDiv.hide();};this.popupAd=function(){if(!popupDiv)return;if(!alwaysPopup&&getCookie){var isPopup=getCookie("popupAd");if(isPopup)return;}
popupDiv.style.display="block";var adW=popupDiv.getWidth();var adH=popupDiv.getHeight();var ztH=0;if($('webim_panel_div')){ztH=0||$('webim_panel_div').getHeight();}
ztH=ztH+3;popupDiv.style.bottom=ztH-adH+"px";popupDiv.style.right=4+"px";popupDiv.style.zIndex="1000";var toDo=adH;var step=10;var itvId=setInterval(function(){step=Math.min(step,toDo);popupDiv.style.bottom=ztH-(toDo-step)+"px";toDo=toDo-step;if(toDo<=0){clearInterval(itvId);popupDiv.addClassName('fixed-bottom')}},50);if(setCookie)
setCookie('popupAd',"true",interruptTime,"/",getSecDomain());if(callback){callback.apply();}};var getSecDomain=function(){var dm=document.domain;if(dm.indexOf('sohu.com')!=-1){var reg=/^(([\w\-]+\.)*)([\w\-]+\.sohu\.com)$/;if(reg.test(dm)){var r=dm.match(reg);dm=r[3];}}
return dm;}}