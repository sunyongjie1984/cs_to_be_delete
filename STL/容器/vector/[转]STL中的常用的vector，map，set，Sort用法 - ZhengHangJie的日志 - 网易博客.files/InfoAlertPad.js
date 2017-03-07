if(NEPlatform==undefined)
var NEPlatform={};
if(NEPlatform.DwrHook==undefined)
NEPlatform.DwrHook={};
if(NEPlatform.DwrHook.Switch==undefined)
NEPlatform.DwrHook.Switch={};
NEPlatform.DwrHook.Switch={
turnOnHook:function(){
NEPlatform.DwrHook.Switch._isHookOff=false;
},
shutDownHook:function(){
NEPlatform.DwrHook.Switch._isHookOff=true;
},
isHookOff:function(){
return NEPlatform.DwrHook.Switch._isHookOff;
}
};
NEPlatform.DwrHook.Switch._isHookOff=false;
var __MESSAGE_STRING__='<img src="'+Const.STDomain+'/style/common/indicator.gif"/>'
function useLoadingMessage(message){
var loadingMessage;
if(message)loadingMessage=message;
else loadingMessage="正在加载中...";
DWREngine.setPreHook(function(){
if(NEPlatform.DwrHook.Switch.isHookOff()){
NEPlatform.DwrHook.Switch.turnOnHook();
return;
}
var disabledZone=$('disabledZone');
if(!disabledZone){
disabledZone=document.createElement('div');
disabledZone.setAttribute('id','disabledZone');
disabledZone.style.position="absolute";
disabledZone.style.zIndex="1000";
disabledZone.style.left="0px";
disabledZone.style.top="0px";
disabledZone.style.width="100%";
disabledZone.style.height="100%";
disabledZone.style.color="#000000";
document.body.appendChild(disabledZone);
var messageZone=document.createElement('div');
disabledZone.appendChild(messageZone);
messageZone.setAttribute('id','messageZone');
messageZone.innerHTML=__MESSAGE_STRING__+loadingMessage;
}
else{
$('messageZone').innerHTML=__MESSAGE_STRING__+loadingMessage;
disabledZone.style.visibility='visible';
}
});
DWREngine.setPostHook(function(){
var disabledZone=$('disabledZone');
if(disabledZone){
disabledZone.style.visibility='hidden';
}
NEPlatform.DwrHook.Switch.turnOnHook();
});
}
useLoadingMessage();
