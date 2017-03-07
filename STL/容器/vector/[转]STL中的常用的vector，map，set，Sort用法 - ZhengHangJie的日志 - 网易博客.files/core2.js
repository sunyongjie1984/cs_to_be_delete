if(NECtrl==undefined){
var NECtrl={};
}
NECtrl.Barrier=Class.create();
NECtrl.Barrier.prototype.initialize=fBarInitialize;
NECtrl.Barrier.prototype.regReq=fBarRegisterReq;
NECtrl.Barrier.prototype.callReq=fBarCallRegistedReq;
NECtrl.Barrier.prototype.mkParam=fBarMakeParam;
NECtrl.Barrier.prototype.reset=fBarStatusReset;
NECtrl.Barrier.prototype._fInCbk=_fBarInternalCallback;
function fBarInitialize(){
this._mModuleObserve=[];
this._mReq2Module=[];
}
function fBarRegisterReq(sReqName,sModuleName,fReqMethod){
this._mModuleObserve[''+sModuleName]={bHasReq:false};
this._mReq2Module[''+sReqName]={sModuleName:sModuleName,fReq:fReqMethod};
}
function fBarCallRegistedReq(sReqName,oReqParam){
var _oModuleObj=this._mReq2Module[''+sReqName];
if(!_oModuleObj)
return;
var _oModuleState=this._mModuleObserve[''+_oModuleObj.sModuleName];
if(!_oModuleState)
return;
if(_oModuleState.bHasReq){
oReqParam.fCancelMethod(oReqParam.oCancelParam);
return;
}
_oModuleState.bHasReq=true;
_oModuleObj.fReq(oReqParam.oUserParam,oReqParam.fInternalCallBack
);
return;
}
function fBarMakeParam(sReqName,oUserParam,fExternalCallBack,oCancelParam,fCancelMethod){
var _oReqParam={};
_oReqParam.oUserParam=oUserParam;
_oReqParam.fInternalCallBack=this._fInCbk.bind(this,sReqName,fExternalCallBack);
if(!oCancelParam)
_oReqParam.oCancelParam={};
else
_oReqParam.oCancelParam=oCancelParam;
if(!fCancelMethod||!(typeof fCancelMethod=="function"))
_oReqParam.fCancelMethod=Prototype.emptyFunction;
else
_oReqParam.fCancelMethod=fCancelMethod;
return _oReqParam;
}
function _fBarInternalCallback(sReqName,fExternalCallBack,oCallBackParam){
var _oModuleObj=this._mReq2Module[''+sReqName];
if(!_oModuleObj)
return;
var _oModuleState=this._mModuleObserve[''+_oModuleObj.sModuleName];
if(!_oModuleState)
return;
try{
fExternalCallBack(oCallBackParam);
}catch(e){
_oModuleState.bHasReq=false;
throw e;
}
_oModuleState.bHasReq=false;
}
function fBarStatusReset(sReqName){
var _oModuleObj=this._mReq2Module[''+sReqName];
if(!_oModuleObj)
return;
var _oModuleState=this._mModuleObserve[''+_oModuleObj.sModuleName];
if(!_oModuleState)
return;
_oModuleState.bHasReq=false;
}
if(NECtrl==undefined){
var NECtrl={};
}
NECtrl.DynamicLoader={
AdvanceEditorJSUrl:Const.STDomain+"/js/netease/Ctrl/AdvancedEditor.js",
jsArr:[],
load:function(jssrc,fnload){
var _fnload=fnload||Prototype.emptyFunction;
for(var i=0,l=this.jsArr.length;i<l;i=i+1){
if(jssrc==this.jsArr[i]){
_fnload();
return;
}
}
this.jsArr.push(jssrc);
dynamic_load_javascript(jssrc,_fnload);
}
}
setTimeout("NECtrl.DynamicLoader.load(NECtrl.DynamicLoader.AdvanceEditorJSUrl)",5*60*1000);
if(NetEase==undefined){
var NetEase={};
}
NetEase.DwrLogger=Class.create();
NetEase.DwrLogger.prototype={
initialize:function(){
this.options=Object.extend({
fade:true,
container:null,
style:Const.STDomain+'/style/common',
width:200,
opacity:0.80,
timeout:3000,
delay:1500,
position:'absolute'
},arguments[0]||{});
this._init();
this.loggerIndex=-1;
this.cacheLogger=[];
},
_init:function(){
this.loggerZone=$('$_loggerZone');
if(!this.loggerZone){
this.loggerZone=document.createElement('div');
this.loggerZone.setAttribute('id','$_loggerZone');
this.loggerZone.style.position=this.options.position;
this.loggerZone.style.zIndex="100019";
this.loggerZone.style.right='20px';
this.loggerZone.style.top='20px';
if(this.options.container!=null){
this.options.container.appendChild(this.loggerZone);
}else
UD.layer.appendChild(this.loggerZone);
}
},
appendMsg:function(msg,type){
this.loggerIndex++;
var logger={};
logger.id="$_loggerMsg"+this.loggerIndex;
logger.msg=msg;
logger.type=type;
var messageZone=document.createElement('div');
messageZone.setAttribute('id',logger.id);
if(logger.type=="info"){
messageZone.innerHTML='<img src="'+this.options.style+'/ico_info.gif"/>&nbsp;'+msg;
}else
if(logger.type=="ok"){
messageZone.innerHTML='<img src="'+this.options.style+'/ico_confirm.gif"/>&nbsp;'+msg;
}
else
if(logger.type=="error"){
messageZone.innerHTML='<img src="'+this.options.style+'/ico_error.gif"/>&nbsp;'+msg;
}else
messageZone.innerHTML='<img src="'+this.options.style+'/ico_info.gif"/>&nbsp;'+msg;
messageZone.style.display="block";
messageZone.style.backgroundColor="#ffffff";
messageZone.style.color="#000000";
messageZone.style.fontSize="12px";
messageZone.style.margin="5px";
messageZone.style.padding="2px";
messageZone.style.textAlign="left";
messageZone.style.MozOpacity=this.options.opacity+"";
messageZone.style.filter="alpha(opacity="+this.options.opacity*100+")";
messageZone.style.width=this.options.width+'px';
this.loggerZone.insertBefore(messageZone,this.loggerZone.firstChild);
this.cacheLogger.push(logger);
if(!this.toFadeCheck)
this.toFadeCheck=window.setTimeout(this._clean.bind(this,logger),this.options.timeout);
},
_clean:function(logger){
if(this.options.fade){
if($(logger.id)){
Effect.Fade(logger.id,{duration:0.5,userCallBack:this._remove.bind(this,logger)});
}
}else{
this._remove(logger);
}
},
setMsg:function(msg,type){
this.toFadeCheck=window.clearTimeout(this.toFadeCheck);
if(this.cacheLogger.length)
this._remove(this.cacheLogger[0]);
this.appendMsg(msg,type);
},
_remove:function(logger){
if($(logger.id)){
$(logger.id).innerHTML='';
$(logger.id).style.display='none';
Element.removeChild($(logger.id));
this.cacheLogger.shift(logger);
if(this.cacheLogger.length>0){
logger=this.cacheLogger[0];
this.toFadeCheck=window.setTimeout(this._clean.bind(this,logger),this.options.delay);
}else{
this.toFadeCheck=null;
}
}
}
}
NetEase.DwrLogger.TYPE_INFO="info";
NetEase.DwrLogger.TYPE_OK="ok";
NetEase.DwrLogger.TYPE_ERROR="error";
if(NetEase==undefined){
var NetEase={};
}
if(NetEase.DateTime==undefined){
NetEase.DateTime={};
}
NetEase.DateTime.MONTH_NAMES=new Array('January','February','March','April','May','June','July','August','September','October','November','December','Jan','Feb','Mar','Apr','May','Jun','Jul','Aug','Sep','Oct','Nov','Dec');
NetEase.DateTime.DAY_NAMES=new Array('Sunday','Monday','Tuesday','Wednesday','Thursday','Friday','Saturday','Sun','Mon','Tue','Wed','Thu','Fri','Sat');
NetEase.DateTime.LZ=function(x){return(x<0||x>9?"":"0")+x}
NetEase.DateTime.isDate=function(val,format){
var date=NetEase.DateTime.getDateFromFormat(val,format);
if(date==0){return false;}
return true;
}
NetEase.DateTime.compareDates=function(date1,dateformat1,date2,dateformat2){
var d1=NetEase.DateTime.getDateFromFormat(date1,dateformat1);
var d2=NetEase.DateTime.getDateFromFormat(date2,dateformat2);
if(d1==0||d2==0){
return-1;
}
else if(d1>d2){
return 1;
}
return 0;
}
NetEase.DateTime.formatDate=function(_time,format){
var date=new Date(_time);
format=format+"";
var result="";
var i_format=0;
var c="";
var token="";
var lastToken="";
var y=date.getYear()+"";
var M=date.getMonth()+1;
var d=date.getDate();
var E=date.getDay();
var H=date.getHours();
var m=date.getMinutes();
var s=date.getSeconds();
var yyyy,yy,MMM,MM,dd,hh,h,mm,ss,ampm,HH,H,KK,K,kk,k;
var value=new Object();
if(y.length<4){y=""+(parseInt(y)-0+1900);}
value["y"]=""+y;
value["yyyy"]=y;
value["yy"]=y.substring(2,4);
var currDate=new Date();
if(currDate.getFullYear()==date.getFullYear()){
value["Y"]="";
value["YYYY"]="";
value["YY"]="";
}else{
value["Y"]=""+y;
value["YYYY"]=y;
value["YY"]=y.substring(2,4);
}
value["M"]=M;
value["MM"]=NetEase.DateTime.LZ(M);
value["MMM"]=NetEase.DateTime.MONTH_NAMES[M-1];
value["NNN"]=NetEase.DateTime.MONTH_NAMES[M+11];
value["d"]=d;
value["dd"]=NetEase.DateTime.LZ(d);
value["E"]=NetEase.DateTime.DAY_NAMES[E+7];
value["EE"]=NetEase.DateTime.DAY_NAMES[E];
value["H"]=H;
value["HH"]=NetEase.DateTime.LZ(H);
if(H==0){value["h"]=12;}
else if(H>12){value["h"]=H-12;}
else{value["h"]=H;}
value["hh"]=NetEase.DateTime.LZ(value["h"]);
if(H>11){value["K"]=H-12;}else{value["K"]=H;}
value["k"]=H+1;
value["KK"]=NetEase.DateTime.LZ(value["K"]);
value["kk"]=NetEase.DateTime.LZ(value["k"]);
if(H>11){value["a"]="PM";}
else{value["a"]="AM";}
value["m"]=m;
value["mm"]=NetEase.DateTime.LZ(m);
value["s"]=s;
value["ss"]=NetEase.DateTime.LZ(s);
while(i_format<format.length){
c=format.charAt(i_format);
token="";
while((format.charAt(i_format)==c)&&(i_format<format.length)){
token+=format.charAt(i_format++);
}
if(value[token]!=null){
result=result+value[token];
}
else{
if(!((lastToken=="YYYY"||lastToken=="YY"||lastToken=="Y")&&value[lastToken]==""))
result=result+token;
}
lastToken=token;
}
return result;
}
NetEase.DateTime._isInteger=function(val){
var digits="1234567890";
for(var i=0;i<val.length;i++){
if(digits.indexOf(val.charAt(i))==-1){return false;}
}
return true;
}
NetEase.DateTime._getInt=function(str,i,minlength,maxlength){
for(var x=maxlength;x>=minlength;x--){
var token=str.substring(i,i+x);
if(token.length<minlength){return null;}
if(NetEase.DateTime._isInteger(token)){return token;}
}
return null;
}
NetEase.DateTime.getDateFromFormat=function(val,format){
val=val+"";
format=format+"";
var i_val=0;
var i_format=0;
var c="";
var token="";
var token2="";
var x,y;
var now=new Date();
var year=now.getYear();
var month=now.getMonth()+1;
var date=1;
var hh=now.getHours();
var mm=now.getMinutes();
var ss=now.getSeconds();
var ampm="";
while(i_format<format.length){
c=format.charAt(i_format);
token="";
while((format.charAt(i_format)==c)&&(i_format<format.length)){
token+=format.charAt(i_format++);
}
if(token=="yyyy"||token=="yy"||token=="y"){
if(token=="yyyy"){x=4;y=4;}
if(token=="yy"){x=2;y=2;}
if(token=="y"){x=2;y=4;}
year=NetEase.DateTime._getInt(val,i_val,x,y);
if(year==null){return 0;}
i_val+=year.length;
if(year.length==2){
if(year>70){year=1900+(year-0);}
else{year=2000+(year-0);}
}
}
else if(token=="MMM"||token=="NNN"){
month=0;
for(var i=0;i<NetEase.DateTime.MONTH_NAMES.length;i++){
var month_name=NetEase.DateTime.MONTH_NAMES[i];
if(val.substring(i_val,i_val+month_name.length).toLowerCase()==month_name.toLowerCase()){
if(token=="MMM"||(token=="NNN"&&i>11)){
month=i+1;
if(month>12){month-=12;}
i_val+=month_name.length;
break;
}
}
}
if((month<1)||(month>12)){return 0;}
}
else if(token=="EE"||token=="E"){
for(var i=0;i<NetEase.DateTime.DAY_NAMES.length;i++){
var day_name=NetEase.DateTime.DAY_NAMES[i];
if(val.substring(i_val,i_val+day_name.length).toLowerCase()==day_name.toLowerCase()){
i_val+=day_name.length;
break;
}
}
}
else if(token=="MM"||token=="M"){
month=NetEase.DateTime._getInt(val,i_val,token.length,2);
if(month==null||(month<1)||(month>12)){return 0;}
i_val+=month.length;}
else if(token=="dd"||token=="d"){
date=NetEase.DateTime._getInt(val,i_val,token.length,2);
if(date==null||(date<1)||(date>31)){return 0;}
i_val+=date.length;}
else if(token=="hh"||token=="h"){
hh=NetEase.DateTime._getInt(val,i_val,token.length,2);
if(hh==null||(hh<1)||(hh>12)){return 0;}
i_val+=hh.length;}
else if(token=="HH"||token=="H"){
hh=NetEase.DateTime._getInt(val,i_val,token.length,2);
if(hh==null||(hh<0)||(hh>23)){return 0;}
i_val+=hh.length;}
else if(token=="KK"||token=="K"){
hh=NetEase.DateTime._getInt(val,i_val,token.length,2);
if(hh==null||(hh<0)||(hh>11)){return 0;}
i_val+=hh.length;}
else if(token=="kk"||token=="k"){
hh=NetEase.DateTime._getInt(val,i_val,token.length,2);
if(hh==null||(hh<1)||(hh>24)){return 0;}
i_val+=hh.length;hh--;}
else if(token=="mm"||token=="m"){
mm=NetEase.DateTime._getInt(val,i_val,token.length,2);
if(mm==null||(mm<0)||(mm>59)){return 0;}
i_val+=mm.length;}
else if(token=="ss"||token=="s"){
ss=NetEase.DateTime._getInt(val,i_val,token.length,2);
if(ss==null||(ss<0)||(ss>59)){return 0;}
i_val+=ss.length;}
else if(token=="a"){
if(val.substring(i_val,i_val+2).toLowerCase()=="am"){ampm="AM";}
else if(val.substring(i_val,i_val+2).toLowerCase()=="pm"){ampm="PM";}
else{return 0;}
i_val+=2;}
else{
if(val.substring(i_val,i_val+token.length)!=token){return 0;}
else{i_val+=token.length;}
}
}
if(i_val!=val.length){return 0;}
if(month==2){
if(((year%4==0)&&(year%100!=0))||(year%400==0)){
if(date>29){return 0;}
}
else{if(date>28){return 0;}}
}
if((month==4)||(month==6)||(month==9)||(month==11)){
if(date>30){return 0;}
}
if(hh<12&&ampm=="PM"){hh=hh-0+12;}
else if(hh>11&&ampm=="AM"){hh-=12;}
var newdate=new Date(year,month-1,date,hh,mm,ss);
return newdate.getTime();
}
NetEase.DateTime.parseDate=function(val){
var preferEuro=(arguments.length==2)?arguments[1]:false;
generalFormats=new Array('y-M-d','MMM d, y','MMM d,y','y-MMM-d','d-MMM-y','MMM d');
monthFirst=new Array('M/d/y','M-d-y','M.d.y','MMM-d','M/d','M-d');
dateFirst=new Array('d/M/y','d-M-y','d.M.y','d-MMM','d/M','d-M');
var checkList=new Array('generalFormats',preferEuro?'dateFirst':'monthFirst',preferEuro?'monthFirst':'dateFirst');
var d=null;
for(var i=0;i<checkList.length;i++){
var l=window[checkList[i]];
for(var j=0;j<l.length;j++){
d=NetEase.DateTime.getDateFromFormat(val,l[j]);
if(d!=0){return new Date(d);}
}
}
return null;
}
NetEase.DateTime.Min1=1000*60;
NetEase.DateTime.Min5=1000*60*5;
NetEase.DateTime.Min10=NetEase.DateTime.Min5*2;
NetEase.DateTime.Min15=NetEase.DateTime.Min5*3;
NetEase.DateTime.Min30=NetEase.DateTime.Min10*3;
NetEase.DateTime.Min45=NetEase.DateTime.Min15*3;
NetEase.DateTime.Hour1=NetEase.DateTime.Min30*2;
NetEase.DateTime.Hour1Min30=NetEase.DateTime.Min45*2;
NetEase.DateTime.Hour2=NetEase.DateTime.Hour1*2;
NetEase.DateTime.Hour2Min30=NetEase.DateTime.Min30*5;
NetEase.DateTime.Hour3=NetEase.DateTime.Hour1*3;
NetEase.DateTime.Hour4=NetEase.DateTime.Hour1*4;
NetEase.DateTime.Hour5=NetEase.DateTime.Hour1*5;
NetEase.DateTime.Hour6=NetEase.DateTime.Hour1*6;
NetEase.DateTime.Hour7=NetEase.DateTime.Hour1*7;
NetEase.DateTime.Hour8=NetEase.DateTime.Hour1*8;
NetEase.DateTime.Hour9=NetEase.DateTime.Hour1*9;
NetEase.DateTime.Hour10=NetEase.DateTime.Hour1*10;
NetEase.DateTime.Hour11=NetEase.DateTime.Hour1*11;
NetEase.DateTime.Hour12=NetEase.DateTime.Hour6*2;
NetEase.DateTime.Day1=NetEase.DateTime.Hour12*2;
NetEase.DateTime.Day2=NetEase.DateTime.Day1*2;
NetEase.DateTime.Day3=NetEase.DateTime.Day1*3;
NetEase.DateTime.Day4=NetEase.DateTime.Day2*2;
NetEase.DateTime.formatRecent=function(_time,prefix,suffix){
var pastDate=new Date(_time);
var pastTime=pastDate.getTime();
var pastYear=pastDate.getFullYear();
var pastMonth=pastDate.getMonth();
var pastDay=pastDate.getDate();
var pastDateZero=new Date(pastYear,pastMonth,pastDay);
var pastTimeZero=pastDateZero.getTime();
var nowDate=new Date();
var nowTime=nowDate.getTime();
var nowYear=nowDate.getFullYear();
var nowMonth=nowDate.getMonth();
var nowDay=nowDate.getDate();
var nowDateZero=new Date(nowYear,nowMonth,nowDay);
var nowTimeZero=pastDateZero.getTime();
var timeDiff=nowTime-pastTime;
var timeDiffZero=nowTimeZero-pastTimeZero;
if(!prefix)
prefix="";
if(!suffix)
suffix="";
if(timeDiffZero>=NetEase.DateTime.Day1){
if(timeDiffZero<NetEase.DateTime.Day2)
return prefix+"昨天"+suffix;
if(timeDiff<NetEase.DateTime.Day3)
return prefix+"前天"+suffix;
if(timeDiff<NetEase.DateTime.Day4)
return prefix+"3天前"+suffix;
}
if(timeDiff<=NetEase.DateTime.Min5)
return prefix+"1分钟前"+suffix;
if(timeDiff<=NetEase.DateTime.Min10)
return prefix+"5分钟前"+suffix;
if(timeDiff<=NetEase.DateTime.Min15)
return prefix+"10分钟前"+suffix;
if(timeDiff<=NetEase.DateTime.Min30)
return prefix+"1刻钟前"+suffix;
if(timeDiff<=NetEase.DateTime.Min45)
return prefix+"半小时前"+suffix;
if(timeDiff<=NetEase.DateTime.Hour1)
return prefix+"45分钟前"+suffix;
if(timeDiff<=NetEase.DateTime.Hour1Min30)
return prefix+"1小时前"+suffix;
if(timeDiff<=NetEase.DateTime.Hour2)
return prefix+"1.5小时前"+suffix;
if(timeDiff<=NetEase.DateTime.Hour2Min30)
return prefix+"2小时前"+suffix;
if(timeDiff<=NetEase.DateTime.Hour3)
return prefix+"2.5小时前"+suffix;
if(timeDiff<=NetEase.DateTime.Hour6)
return prefix+"3小时前"+suffix;
if(timeDiff<=NetEase.DateTime.Hour12)
return prefix+"6小时前"+suffix;
if(timeDiff<=NetEase.DateTime.Day1)
return prefix+"12小时前"+suffix;
return"";
}
NetEase.DateTime.formatRecentDate=function(_time,format){
var pastDate=new Date(_time);
var pastTime=pastDate.getTime();
var nowDate=new Date();
var nowTime=nowDate.getTime();
var timeDiff=nowTime-pastTime;
if(timeDiff<=NetEase.DateTime.Min5)
return"1分钟前";
if(timeDiff<=NetEase.DateTime.Min10)
return"5分钟前";
if(timeDiff<=NetEase.DateTime.Min15)
return"10分钟前";
if(timeDiff<=NetEase.DateTime.Min30)
return"1刻钟前";
if(timeDiff<=NetEase.DateTime.Hour1)
return"半小时前";
if(timeDiff<=NetEase.DateTime.Hour2)
return"1小时前";
if(timeDiff<=NetEase.DateTime.Hour3)
return"2小时前";
if(timeDiff<=NetEase.DateTime.Hour4)
return"3小时前";
if(timeDiff<=NetEase.DateTime.Hour5)
return"4小时前";
if(timeDiff<=NetEase.DateTime.Hour6)
return"5小时前";
if(timeDiff<=NetEase.DateTime.Hour7)
return"6小时前";
if(timeDiff<=NetEase.DateTime.Hour8)
return"7小时前";
if(timeDiff<=NetEase.DateTime.Hour9)
return"8小时前";
if(timeDiff<=NetEase.DateTime.Hour10)
return"9小时前";
if(timeDiff<=NetEase.DateTime.Hour11)
return"10小时前";
if(timeDiff<=NetEase.DateTime.Hour12)
return"11小时前";
var pastYear=pastDate.getFullYear();
var nowYear=nowDate.getFullYear();
if(pastYear<nowYear){
return NetEase.DateTime.formatDate(_time,"yyyy-M-dd HH:mm");
}else
return NetEase.DateTime.formatDate(_time,"M-dd HH:mm");
}
if(NetEase==undefined){
var NetEase={};
}
NetEase.SimplePageLayer=Class.create();
NetEase.SimplePageLayer.prototype={
initialize:function(observerId){
this.observer=(observerId==null)?document:$(observerId);
this.pageLayerArray=[];
this.observeHandler=this._observeHandler.bind(this);
Event.observe(this.observer,'click',this.observeHandler);
},
destory:function(){
Event.stopObserving(this.observer,'click',this.observeHandler);
this.pageLayerArray=null;
},
addPageLayer:function(id,openId,menuId){
var _layer={};
_layer.id=id;
_layer.options=Object.extend(
{
openHandler:Prototype.emptyFunction,
closeHandler:Prototype.emptyFunction,
delay:false,
forceClose:false,
isOpen:false
},arguments[3]||{}
);
_layer.openHandler=this._openHandler.bind(this,_layer,"open");
if(_layer.options.delay){
_layer.menuHandler=this._delayOpenMenuHandler.bind(this,_layer);
}else{
_layer.menuHandler=this._openHandler.bind(this,_layer,"menu");
}
_layer.closeHandler=this._closeHandler.bind(this,_layer);
_layer.blockCloseHandler=this._blockCloseHandler.bind(this,_layer);
if(openId!=null){
_layer.opener=$(openId);
Event.observe(_layer.opener,'click',_layer.openHandler);
}
if(menuId!=null){
_layer.menuer=$(menuId);
Event.observe(_layer.menuer,'mouseover',_layer.menuHandler);
Event.observe(_layer.menuer,'mouseout',_layer.closeHandler);
Event.observe(_layer.id,'mouseover',_layer.blockCloseHandler);
Event.observe(_layer.id,'mouseout',_layer.closeHandler);
}
this.pageLayerArray.push(_layer);
},
removePageLayer:function(id){
this.pageLayerArray=this.pageLayerArray.reject(
function(e){
if(e.id==id){
if(e.opener!=null)
Event.stopObserving(e.opener,'click',e.openHandler);
if(e.menuer!=null){
Event.stopObserving(e.menuer,'mouseover',e.menuHandler);
Event.stopObserving(e.menuer,'mouseout',e.closeHandler);
Event.stopObserving(e.id,'mouseover',e.blockCloseHandler);
Event.stopObserving(e.id,'mouseout',e.closeHandler);
}
return true;
}
return false;
}.bind(this)
);
},
_delayOpenMenuHandler:function(layer,event){
event=event||window.event;
Event.stop(event);
if(!this.delayTask)
this.delayTask=window.setTimeout(this._openHandler.bind(this,layer,"menu"),layer.options.delay);
},
_openHandler:function(layer,type,event){
event=event||window.event;
this.delayTask=null;
if(type=="menu"){
if(event)
Event.stop(event);
layer.blockClose=true;
this._observeHandler();
if(!layer.options.isOpen){
layer.options.isOpen=true;
layer.options.openHandler(layer);
return;
}
}else{
layer.stopEvent=true;
if(layer.options.isOpen){
layer.options.isOpen=false;
layer.options.closeHandler(layer);
}else{
layer.options.isOpen=true;
layer.options.openHandler(layer);
}
}
},
_blockCloseHandler:function(layer){
layer.blockClose=true;
},
_closeHandler:function(layer){
if(this.delayTask){
window.clearTimeout(this.delayTask);
this.delayTask=null;
}
layer.blockClose=false;
window.setTimeout(this._observeHandler.bind(this),100);
},
_observeHandler:function(){
var _layer;
for(var i=0;i<this.pageLayerArray.length;i++){
_layer=this.pageLayerArray[i];
if(_layer.blockClose)continue;
if(_layer.stopEvent==true&&!_layer.options.forceClose){
_layer.stopEvent=false;
continue;
}
if(_layer.options.isOpen||_layer.options.forceClose){
_layer.options.isOpen=false;
_layer.options.closeHandler(_layer);
}
}
}
}
if(NECtrl==undefined){
var NECtrl={};
}
NECtrl.AbstractEditor={};
NECtrl.AbstractEditor.prototype={
bHarm:false,
bExceedMaxLen:false,
getContent:function(){
var _sContent=this._getPrimitiveData();
var _sContent=this._stripData(_sContent);
this.bExceedMaxLen=this._exceedMaxLen(_sContent);
if(this._doAfterGetContent)
_sContent=this._doAfterGetContent(_sContent);
return _sContent;
},
hasHarmCode:function(){
return this.bHarm;
},
IsExceedMaxLen:function(){
return this.bExceedMaxLen;
},
_stripData:function(_sContent){
_sContent=_sContent.replace(/<\\?\?xml[^>]*>/ig,"");
_sContent=_sContent.replace(/<\/?\w+:[^>]*>/ig,"");
var _oResult=stripData(_sContent,this._getReserveTag!=null?this._getReserveTag():[]);
this.bHarm=_oResult.isHarm;
_sContent=_oResult.content;
return _sContent;
}
}
if(NetEase==undefined){
var NetEase={};
}
NetEase.PlainEditor=Class.create();
NetEase.PlainEditor.prototype={
initialize:function(parentId,editorElemId){
this.options=Object.extend({
advEdtCrt:null,
disabled:false,
escapeHtml:true,
width:0,
height:280,
maxlen:65535,
defaultStyle:true
},arguments[2]||{});
this.parentId=parentId;
this.editorElemId=editorElemId;
this.editor=null;
this.hasSwitched=false;
this.finishSwitch=false;
this.advanceEditor=null;
this._load();
return this;
},
focus:function(){
this.editor.focus();
},
_load:function(){
var editorElem;
if((editorElem=$(this.editorElemId))!=null){
var widthStr="width:99%;";
if(this.options.width>0){
widthStr="width:"+(this.options.width-4)+"px;";
editorElem.style.width=this.options.width+"px";
}
var disabledStr="";
if(this.options.disabled)
disabledStr=' disabled=\'disabled\' ';
var ihtml='<div id="plainDiv'+this.parentId+'"';
if(this.options.width>0)
ihtml+=' style="width:'+this.options.width+'px;">';
else
ihtml+='>';
if(this.options.advEdtCrt!=null)
ihtml+='<table class="nEdt ccEdt"><tr><td class="td6"><div class="menu"><a id="edtsw'+this.parentId+'" href="#">全部功能</a></div></td></tr></table>';
ihtml+='<textarea id="plainEditor'+this.parentId+'" style="'+widthStr+'height:'+this.options.height+'px;overflow-y:auto;';
if(this.options.defaultStyle){
ihtml+='border:none;padding:2px;font-size:14px;color:#bbb;line-height:135%;';
}
ihtml+='" '+disabledStr+'></textarea></div>';
editorElem.innerHTML=ihtml;
this.editor=$("plainEditor"+this.parentId);
if(this.options.advEdtCrt!=null&&$("edtsw"+this.parentId))
Event.observe($("edtsw"+this.parentId),"click",this._switchEditor.bindAsEventListener(this));
}
},
_exceedMaxLen:function(content){
if(content.length>this.options.maxlen){
return true;
}else
return false;
},
_switchEditor:function(e){
if(!this.hasSwitched){
if(!this.editor.isFocused){
this.editor.value="";
}
this.hasSwitched=true;
NECtrl.DynamicLoader.load(NECtrl.DynamicLoader.AdvanceEditorJSUrl,this._switchToAdvanceEditor.bind(this));
}
if(e){
Event.stop(e);
}
},
_switchToAdvanceEditor:function(){
var _data=this.getContent();
this.advanceEditor=this.options.advEdtCrt(this._afterLoadAdvanceEditor.bind(this,_data));
},
_afterLoadAdvanceEditor:function(_content){
if(!this.finishSwitch){
if(this.advanceEditor){
this.advanceEditor.setData(_content);
this.finishSwitch=true;
this.advanceEditor=null;
}
}
},
_getPrimitiveData:function(){
var content=this.editor.value;
return this.options.escapeHtml?toDHTML(content):content;
},
setContent:function(content){
this.editor.value=content;
},
emptyContent:function(){
this.setContent("");
}
}
Object.extend(NetEase.PlainEditor.prototype,NECtrl.AbstractEditor.prototype);
if(NetEase==undefined){
var NetEase={};
}
NetEase.PlainEditorClone=Class.create();
NetEase.PlainEditorClone.prototype=Object.extend(NetEase.PlainEditorClone.prototype,NetEase.PlainEditor.prototype);
NetEase.PlainRichEditor=Class.create();
NetEase.PlainRichEditor.prototype=Object.extend(NetEase.PlainEditorClone.prototype,{
initialize:function(parentId,editorElemId,richTags,richElementMap){
this.options=Object.extend({
advEdtCrt:null,
disabled:false,
escapeHtml:true,
width:0,
height:280,
lineHeight:17,
maxlen:65535,
limitWrite:false,
checkCount:false,
countChangeFun:null,
calCountFun:null
},arguments[4]||{});
this.parentId=parentId;
this.editorElemId=editorElemId;
this.richTags=richTags;
this.richElementMap=richElementMap;
this.editor=null;
this.hasSwitched=false;
this.finishSwitch=false;
this.advanceEditor=null;
this.richContent="";
this.elementNum=0;
this.selectionStart=0;
this._load();
this.regex=NetEase.PlainRichEditor.Utils.buildRichRegex(this.richTags);
Event.observe(this.editor,"blur",this._onBlurEvent.bind(this));
if(this.options.checkCount){
this.textAreaCount=new NetEase.TextAreaCount('plainEditor'+this.parentId,{countFun:this.countContent.bind(this)});
}
return this;
},
focus:function(){
this.editor.isFocused=true;
this.editor.focusAction=true;
this.editor.focus();
this.selectionStart=NetEase.PlainRichEditor.Utils.getCursorPosition(this.editor);
if(!this.selectionStart)this.selectionStart=0;
},
insertPlainContent:function(content){
this.withoutEvent=true;
this.editor.focusAction=true;
if(document.selection){
this.editor.value=this.editor.value.substring(0,this.selectionStart)+content+this.editor.value.substring(this.selectionStart);
this.editor.focus();
var rng=this.editor.createTextRange();
rng.moveStart("character",this.selectionStart+content.length);
rng.collapse(true);
rng.select();
}
else if(document.getBoxObjectFor){
var prevValue=this.editor.value.substring(0,this.selectionStart);
var nextValue=this.editor.value.substring(this.selectionStart);
var scrollTop=this.editor.scrollTop;
this.editor.value=prevValue+content;
var scrollHeight=this.editor.scrollHeight;
this.editor.value+=nextValue;
this.editor.focus();
if(scrollHeight-scrollTop<=this.editor.clientHeight)this.editor.scrollTop=scrollTop;
else this.editor.scrollTop=scrollHeight-this.options.lineHeight;
this.editor.selectionStart=this.selectionStart+content.length;
this.editor.selectionEnd=this.editor.selectionStart;
}
else{
this.editor.value=this.editor.value.substring(0,this.selectionStart)+content+this.editor.value.substring(this.selectionStart);
this.editor.focus();
this.editor.selectionStart=this.selectionStart+content.length;
this.editor.selectionEnd=this.editor.selectionStart;
}
this.withoutEvent=false;
this.countContent();
},
getRichContent:function(){
this.richContent=this.getContent();
this._parseRichElements();
return this.richContent;
},
countContent:function(){
if(this.withoutEvent)return;
this._resetParse();
this._parseRichElements();
if(this.options.checkCount&&this.options.countChangeFun){
this.options.countChangeFun(this.elementNum);
}
},
_parseRichElements:function(){
var results=NetEase.PlainRichEditor.Utils.getRichContentAndLength(this.richTags,this.richElementMap,this.richContent,this.regex,this.options.calCountFun,this.options.limitWrite,this.options.maxlen);
this.richContent=results[0];
this.elementNum=results[1];
if(this.options.limitWrite&&results[2]<this.editor.value.length){
this.withoutEvent=true;
this.editor.value=this.editor.value.substring(0,results[2]);
this.withoutEvent=false;
}
},
_resetParse:function(){
this.regex.lastIndex=0;
this.richContent=this.editor.value;
this.elementNum=0;
},
_switchToAdvanceEditor:function(){
var _data=this.getRichContent();
this.advanceEditor=this.options.advEdtCrt(this._afterLoadAdvanceEditor.bind(this,_data));
},
_onBlurEvent:function(){
this.editor.focusAction=false;
}
});
NetEase.PlainRichEditor.Utils={
getURLContent:function(content){
var urlRegex=new RegExp('<img(\\s)*src=\\"[\\w\\d:\\.\\/]+\\"(\\s)*\\/>|(((https?|ftp|telnet):\\/\\/)|(www\\.))([\\u4e00-\\u9fa5|\\w\\d:#@%/;$()~_?\\+-=\\\\\.&]+)',"gi");
var urlContent="";
var type=1;
var preIndex=0,nextIndex=0;
while((parseResult=urlRegex.exec(content))!=null){
if(type==0){type=1;urlContent+=content.substring(preIndex,urlRegex.lastIndex);preIndex=urlRegex.lastIndex;continue;}
var index=parseResult[0].indexOf("<img");
var url=parseResult[0];
if(index==0)continue;
if(index>0){type=0;url=parseResult[0].substring(0,index);nextIndex=urlRegex.lastIndex-4;}
else{nextIndex=urlRegex.lastIndex}
if(url.indexOf("www.")==0)urlContent+=content.substring(preIndex,nextIndex).replace(url,"<a href='http://"+url+"' target='_blank' onmouseover='this.className=\"c05\"' onmouseout='this.className=\"\"' style='font-size:12px;font-weight:normal;'>"+url+"</a>");
else urlContent+=content.substring(preIndex,nextIndex).replace(url,"<a href='"+url+"' target='_blank' onmouseover='this.className=\"c05\"' onmouseout='this.className=\"\"' style='font-size:12px;font-weight:normal;'>"+url+"</a>");
preIndex=nextIndex;
}
urlContent+=content.substring(preIndex);
return urlContent;
},
buildRichRegex:function(richTags){
var regex=null;
var regexStr="";
if(richTags!=null&&richTags.length>0){
richTags.each(function(value,index){
if(index>0){
regexStr+="|";
}
regexStr+="\\["+value+"\\]([\\u4e00-\\u9fa5|\\w]+)\\[\\/"+value+"\\]";
});
regex=new RegExp(regexStr,"gi");
}
return regex;
},
getRichContent:function(richTags,richElementMap,plainContent,isEscape,isURL){
if(isEscape)plainContent=plainContent.escape();
var results=NetEase.PlainRichEditor.Utils.getRichContentAndLength(richTags,richElementMap,plainContent,null,null,false,0);
if(isURL)results[0]=NetEase.PlainRichEditor.Utils.getURLContent(results[0]);
return results[0];
},
getRichContentAndLength:function(richTags,richElementMap,plainContent,regex,calCountFun,limitWrite,maxlen){
if(regex==null){
regex=NetEase.PlainRichEditor.Utils.buildRichRegex(richTags);
}
var results=[];
var count=0;
var lastIndex=0;
var nextIndex=0;
var parseResult=null;
var richContent="";
while((parseResult=regex.exec(plainContent))!=null){
var richTag=parseResult[0].substring(1,parseResult[0].indexOf(parseResult[1])-1);
var richCollection=richElementMap[richTag.toUpperCase()];
if(richCollection){
var richValue=richCollection[parseResult[1]];
if(richValue){
nextIndex=plainContent.indexOf(parseResult[0],lastIndex);
var previousCount=count;
if(calCountFun){
count+=nextIndex-lastIndex+calCountFun(richTag,richValue);
}
else{
count+=nextIndex-lastIndex+1;
}
if(limitWrite){
if(count==maxlen){
richContent+=plainContent.substring(lastIndex,nextIndex)+richValue;
lastIndex=nextIndex+parseResult[0].length;
break;
}
else if(count>maxlen){
richContent+=plainContent.substring(lastIndex,lastIndex+(maxlen-previousCount));
count=maxlen;
lastIndex+=(maxlen-previousCount);
break;
}
else{
richContent+=plainContent.substring(lastIndex,nextIndex)+richValue;
}
}
else{
richContent+=plainContent.substring(lastIndex,nextIndex)+richValue;
}
lastIndex=nextIndex+parseResult[0].length;
}
}
}
if(limitWrite&&count<maxlen){
var value=lastIndex+(maxlen-count);
if(value>plainContent.length)value=plainContent.length;
richContent+=plainContent.substring(lastIndex,value);
count+=plainContent.substring(lastIndex,value).length;
lastIndex=value;
}
else if(!limitWrite&&lastIndex<plainContent.length){
richContent+=plainContent.substring(lastIndex);
count+=plainContent.substring(lastIndex).length;
lastIndex=plainContent.length;
}
results.push(richContent);
results.push(count);
results.push(lastIndex);
return results;
},
getCursorPosition:function(textArea){
if(textArea.selectionStart){
return textArea.selectionStart;
}
else if(document.selection&&textArea.focusAction==true){
var isFinished=false;
var originalText,untrimmedText;
var sel=document.selection.createRange().duplicate();
var range=document.body.createTextRange();
range.moveToElementText(textArea);
range.setEndPoint("EndToStart",sel);
originalText=untrimmedText=range.text;
do{
if(!isFinished){
if(range.compareEndPoints("StartToEnd",range)==0)isFinished=true;
else{
range.moveEnd("character",-1);
if(range.text==originalText)untrimmedText+="\r\n";
else isFinished=true;
}
}
}while(!isFinished);
return untrimmedText.length;
}
}
};
NetEase.TextAreaCount=Class.create();
NetEase.TextAreaCount.prototype={
initialize:function(textAreaId){
this.options=Object.extend({
countFun:this.getCount.bind(this)
},arguments[1]||{});
this.countNumber=0;
this.textAreaId=textAreaId;
this.textAreaObj=$(this.textAreaId);
if(document.all){
this.pasteObserver=this.onPaste.bind(this);
Event.observe(this.textAreaObj,"propertychange",this.options.countFun);
Event.observe(this.textAreaObj,"keyup",this.options.countFun);
Event.observe(this.textAreaObj,"paste",this.pasteObserver);
}
else if(window.MessageEvent&&!document.getBoxObjectFor){
Event.observe(this.textAreaObj,"keyup",this.options.countFun);
Event.observe(this.textAreaObj,"paste",this.options.countFun);
}
else{
Event.observe(this.textAreaObj,"input",this.options.countFun);
}
},
getCount:function(){
if(this.textAreaObj.value){
this.countNumber=this.textAreaObj.value.length;
}
return this.countNumber;
},
onPaste:function(){
Event.stopObserving(this.textAreaObj,"paste",this.pasteObserver);
this.pasteObserver=null;
if(this.textAreaObj.value==""){
this.textAreaObj.value=window.clipboardData.getData("Text");
}
this.options.countFun();
}
};
NetEase.PlainRichEditor.RichUtils={
moodRichElements:{微笑:['bf_icn_1_1','face0.gif'],难过:['bf_icn_5_8','face47.gif'],开怀笑:['bf_icn_1_2','face1.gif'],哭泣:['bf_icn_1_3','face2.gif'],失望:['bf_icn_1_4','face3.gif'],
崩溃:['bf_icn_3_3','face22.gif'],生气:['bf_icn_5_5','face44.gif'],好爱你:['bf_icn_6_2','face51.gif'],太阳:['bf_icn_8_4','face73.gif'],下雨:['bf_icn_8_5','face74.gif'],
YES:['bf_icn_6_6','face55.gif'],玫瑰:['bf_icn_6_1','face50.gif']},
moodRichTags:["P"],
buildMoodRichElementMap:function(richTag,richElements,richElementMap){
var elements={};
for(var property in richElements){
elements[property]='<img src="http://b.bst.126.net/style/common/htmlEditor/portrait/face/preview/face.gif"/>';
elements[property]=elements[property].replace("face.gif",richElements[property][1]);
}
richElementMap[richTag]=elements;
return richElementMap;
},
buildMoodRichContent:function(richTags,richElements){
var str="<ul>";
for(var i=0;i<richTags.length;i++){
for(var property in richElements[i]){
str+='<li><a href="#" title="'+property+'" class="bf_icn '+richElements[i][property][0]
+'" onclick="${objectName}.insertRichContent(\'['+richTags[i]+']'+property+'[/'+richTags[i]+']\');return false;">'+property+'</a></li>';
}
}
str+="</ul>";
return str;
}
};
if(NetEase==undefined){
var NetEase={};
}
NetEase.PageLayer=Class.create();
NetEase.PageLayer.prototype={
initialize:function(){
this.register();
this.layers=[];
this.freezeLayer=[];
},
addLayer:function(options){
var options=Object.extend({
layerID:false,
oneLayer:false,
openFunc:Prototype.emptyFunction,
openParam:null,
closeFunc:Prototype.emptyFunction,
closeParam:null,
zIndex:0},options);
this.removeLayer(options.layerID);
if(options.oneLayer)
this._hiddenAllLayers();
options.stopEvent=true;
this.layers.push(options);
this._showOneLayer(options);
},
removeLayer:function(layerID){
if(layerID!=0){
var iteraotr=this._hiddenOneLayer.bind(this);
this.layers=this.layers.reject(function(e){
if(e.layerID==layerID)
iteraotr(e);
return e.layerID==layerID});
this.layers.each(function(e){e.stopEvent=true});
}
else
this._hiddenAllLayers();
},
controlLayer:function(layerID){
var layers=this.layers;
this.freezeLayer=this.freezeLayer.reject(function(e){
if(e.layerID==layerID)
layers.push(e);
return e.layerID==layerID;});
this.layers.each(function(e){e.stopEvent=true});
},
unControlLayer:function(layerID){
var freezeLayer=this.freezeLayer;
this.layers=this.layers.reject(function(e){
if(e.layerID==layerID)
freezeLayer.push(e);
return e.layerID==layerID});
this.layers.each(function(e){e.stopEvent=true});
},
register:function(){
this._register4Doc();
},
_register4Doc:function(){
Event.observe(document,"click",this._clickOnDoc.bind(this));
},
_clickOnDoc:function(event){
var temp=this.layers.select(function(e){
return e.stopEvent});
if(temp.length!=0){
this.layers.each(function(e){e.stopEvent=false});
Event.stop(event);
return false;
}
var element=Event.element(event);
var onLayer=false;
while(element!=document.body){
temp=this.layers.select(function(e){
if(element.id==undefined)
return false;
return e.layerID==element.id});
if(temp.length!=0){
onLayer=true;
break;
}
element=element.parentNode;
if(element==null||element==undefined)
break;
}
if(!onLayer)
this._hiddenAllLayers();
else{
var iteraotr=this._hiddenOneLayer.bind(this);
this.layers.each(function(e){
if(e.zIndex>temp[0].zIndex)
iteraotr(e);
});
}
},
_hiddenAllLayers:function(){
try{
this.layers.each(function(e){
Element.setStyle(e.layerID,{display:'none'});
e.closeFunc(e.closeParam);
});
}catch(e){}
this.layers.clear();
},
_hiddenOneLayer:function(e){
try{
if($(e.layerID)){
Element.setStyle(e.layerID,{display:'none'});
}
}catch(e){};
e.closeFunc(e.closeParam);
},
_showOneLayer:function(e){
Element.setStyle(e.layerID,{display:''});
e.openFunc(e.openParam);
}
}
NetEase.ResizeObserver=Class.create();
NetEase.ResizeObserver.prototype={
initialize:function(){
},
layerList:new Array(),
addListener:function(srcId,referId,xoff){
var lsn=new Object();
lsn.element=srcId;
lsn.refer=referId;
if(xoff!=null&&xoff!=undefined)
lsn.xoff=xoff;
else
lsn.xoff=0;
this.removeListener(srcId);
this.layerList.push(lsn);
},
onResize:function(){
for(var i=0;i<this.layerList.length;i++)
{
var src=$(this.layerList[i].element);
var ref=$(this.layerList[i].refer);
if(src!=undefined&&src!=null&&ref!=undefined&&ref!=null){
src.style.left=(Position.cumulativeOffset(ref)[0]+this.layerList[i].xoff)+'px';
}
}
},
removeListener:function(src){
this.layerList=this.layerList.reject(function(e){
return e.element.id==src.id;
});
}
}
if(NetEase==undefined){
var NetEase={};
}
NetEase.JSWindowManager=Class.create();
NetEase.JSWindowManager.prototype={
initialize:function(){
this.options=Object.extend(
{
prefix:"$_",
systemBarPostfix:"_system_bar",
panelPostfix:"_panel",
titlePostfix:"_title",
closePostfix:"_close",
allowDrag:true,
useDragOpacity:true,
simpleDrag:false,
delSelect:true,
noUD:false
},arguments[0]||{});
this.jsWindowList=[];
this.baseIndex=10000;
this.indexAdd=0;
this.topIndex=99999;
if(this.options.allowDrag)
this.simpleDragDrop=new NetEase.SimpleDragDrop({useDragOpacity:this.options.useDragOpacity,simpleDrag:this.options.simpleDrag});
this.curWindow=null;
},
existWindow:function(id){
var jsWindow=this.jsWindowList.detect(this._detectIter.bind(this,id));
return jsWindow?true:false;
},
getWindow:function(id){
return this.jsWindowList.detect(this._detectIter.bind(this,id));
},
createWindow:function(id,params){
if($(id)!=null){
alert("该窗口已经存在!");
return;
}
var options=Object.extend(
{
className:false,
left:false,
top:false,
width:600,
height:400,
allowDrag:true,
notKeepPos:true,
onTop:false,
hasSystemBar:true,
systemBarClassName:'titlebar',
handleClass:'$$_handle_class',
titleId:false,
title:'JSWindow',
hasCloseId:true,
closeId:false,
hiddenOnClose:true,
panelClassName:'content',
useShadow:true,
needCover:false,
allowScroll:false,
opacity:0.25,
beforShowFunc:Prototype.emptyFunction,
afterShowFunc:Prototype.emptyFunction,
beforeHiddenFunc:Prototype.emptyFunction,
afterHiddenFunc:Prototype.emptyFunction,
beforeCloseFunc:Prototype.emptyFunction,
afterCloseFunc:Prototype.emptyFunction
},params||{});
if(!this.options.allowDrag)options.allowDrag=false;
this._buildPos(options);
if(options.onTop){
options.zIndex=this.topIndex;
}else{
options.zIndex=this.baseIndex+(this.indexAdd++);
}
if(options.titleId==false)
options.titleId=this.options.prefix+id+this.options.systemBarPostfix+this.options.titlePostfix;
if(options.hasSystemBar&&options.hasCloseId&&options.closeId==false)
options.closeId=this.options.prefix+id+this.options.systemBarPostfix+this.options.closePostfix;
var jsWindow=this._createJSWindow(id,options);
jsWindow.windowHtml=this._createWindowHtml(id,options);
if(options.hasSystemBar)
jsWindow.systemBar=this._createSystemBar(jsWindow.windowHtml,id,options);
jsWindow.panel=this._createPanel(jsWindow.windowHtml,id,options);
this.jsWindowList.push(jsWindow);
return jsWindow;
},
_getContainer:function(options){
if(this.options.noUD||options.noUD)
return document.body;
var conDiv=(options.notKeepPos)?UD.layer:UD.body;
if(conDiv==null)conDiv=document.body;
return conDiv;
},
_getLeft:function(width){
var left=(document.documentElement.clientWidth-width)/2;
if(left<10)left=10;
return left;
},
_getTop:function(height,container){
var top=0;
if(container==UD.layer||container==document.body){
top=document.documentElement.scrollTop+
(document.documentElement.clientHeight-height)/2;
}
else{
top=UD.body.parentNode.scrollTop+
(document.documentElement.clientHeight-height)/2;
}
if(top<10)top=10;
return top;
},
_buildPos:function(options){
if(!options.left){
options.left=this._getLeft(options.width);
options._caluLeft=true;
}
if(!options.top){
options.top=this._getTop(options.height,this._getContainer(options));
options._caluTop=true;
}
},
setPos:function(id,pos){
var jsWindow=this.jsWindowList.detect(this._detectIter.bind(this,id));
this._setPos(jsWindow,pos);
return jsWindow;
},
_setPos:function(jsWindow,pos){
if(jsWindow){
Object.extend(jsWindow.options,pos);
jsWindow.options.notKeepPos=true;
this._buildPos(jsWindow.options);
}
},
showWindow:function(id){
var jsWindow=this.jsWindowList.detect(this._detectIter.bind(this,id));
this._showWindow(jsWindow);
return jsWindow;
},
_showWindow:function(jsWindow){
if(jsWindow){
this._showMode(jsWindow,true);
jsWindow.options.beforShowFunc(jsWindow);
if(jsWindow.options.notKeepPos){
if(jsWindow.options._caluLeft){
jsWindow.options.left=this._getLeft(jsWindow.options.width);;
}
jsWindow.windowHtml.style.left=jsWindow.options.left+"px";
if(jsWindow.options._caluTop){
jsWindow.options.top=this._getTop(jsWindow.options.height,jsWindow.containerDiv);
}
jsWindow.windowHtml.style.top=jsWindow.options.top+"px";
}
jsWindow.windowHtml.style.display="";
if(this.options.delSelect)
this._hideSelect(true,jsWindow.windowHtml);
jsWindow.options.afterShowFunc(jsWindow);
this.curWindow=jsWindow;
}
},
_showMode:function(jsWindow,show){
if(!jsWindow.options.needCover)return;
var conDiv=jsWindow.containerDiv;
if(jsWindow.options.allowScroll)
conDiv=UD.layer;
var gapDiv=$(conDiv.id+"_gap");
if(!gapDiv){
gapDiv=document.createElement('div');
gapDiv.id=conDiv.id+"_gap"
gapDiv.style.position='absolute';
gapDiv.style.display='none';
gapDiv.style.left='0px';
gapDiv.style.top='0px';
gapDiv.style.backgroundColor="#ffffff";
gapDiv.style.MozOpacity=""+jsWindow.options.opacity;
gapDiv.style.opacity=""+jsWindow.options.opacity;
gapDiv.style.filter="alpha(opacity="+jsWindow.options.opacity*100+")";
gapDiv.style.width=conDiv.parentNode.scrollWidth+'px';
gapDiv.style.height=conDiv.parentNode.scrollHeight+'px';
gapDiv.style.zIndex=this.baseIndex-1;
if(conDiv==document.body){
conDiv.appendChild(gapDiv);
}else{
conDiv.parentNode.appendChild(gapDiv);
}
}
gapDiv.style.display=show?'block':'none';
},
updateTitle:function(id,title){
var jsWindow=this.jsWindowList.detect(this._detectIter.bind(this,id));
this._updateTitle(jsWindow,title);
return jsWindow;
},
_updateTitle:function(jsWindow,title){
if(jsWindow){
jsWindow.options.title=title;
$(jsWindow.options.titleId).innerHTML=title;
}
},
hiddenWindow:function(id){
var jsWindow=this.jsWindowList.detect(this._detectIter.bind(this,id));
this._hiddenWindow(jsWindow);
return jsWindow
},
_hiddenWindow:function(jsWindow){
if(jsWindow){
this._showMode(jsWindow,false);
jsWindow.options.beforeHiddenFunc(jsWindow);
jsWindow.windowHtml.style.display="none";
if(this.options.delSelect)
this._hideSelect(false,jsWindow.windowHtml);
jsWindow.options.afterHiddenFunc(jsWindow);
if(this.curWindow==jsWindow)this.curWindow=null;
}
},
closeWindow:function(id){
var jsWindow=this.jsWindowList.detect(this._detectIter.bind(this,id));
return this._closeWindow(jsWindow);
},
_closeWindow:function(jsWindow){
if(jsWindow){
this._showMode(jsWindow,false);
jsWindow.options.beforeCloseFunc(jsWindow);
jsWindow.windowHtml.style.display="none";
if(this.options.delSelect)
this._hideSelect(false,jsWindow.windowHtml);
if(jsWindow.options.allowDrag)
this.simpleDragDrop.removeDraggable(jsWindow.windowHtml.id);
if(jsWindow.options.hasSystemBar){
Element.removeChild(jsWindow.systemBar);
jsWindow.systemBar=null;
}
Element.removeChild(jsWindow.panel);
jsWindow.panel=null;
Element.removeChild(jsWindow.windowHtml);
jsWindow.windowHtml=null;
this.jsWindowList=this.jsWindowList.reject(this._detectIter.bind(this,jsWindow.id));
jsWindow.options.afterCloseFunc();
if(this.curWindow==jsWindow)this.curWindow=null;
}
},
focusWindow:function(jsWindow){
if(jsWindow){
this._focusWindow(jsWindow.id);
}
},
_focusWindow:function(id){
var pos=-1;
this.indexAdd=0;
for(var i=0;i<this.jsWindowList.length;i++){
if(this.jsWindowList[i].id!=id){
if(!this.jsWindowList[i].options.onTop){
this.jsWindowList[i].options.zIndex=this.baseIndex+(this.indexAdd++);
this.jsWindowList[i].windowHtml.style.zIndex=this.jsWindowList[i].options.zIndex;
}
}else{
pos=i;
}
}
if(pos>-1){
this.jsWindowList[pos].options.zIndex=this.baseIndex+(this.indexAdd++);
this.jsWindowList[pos].windowHtml.style.zIndex=this.jsWindowList[pos].options.zIndex;
this.curWindow=this.jsWindowList[pos];
}
},
_detectIter:function(id,element){
if(id==element.id){
return true;
}
return false;
},
_createWindowHtml:function(id,options){
var windowHtml=document.createElement('div');
windowHtml.id=this.options.prefix+id;
windowHtml.className='g_lay_com '+(options.className?options.className:'')+(options.useShadow?' g_f_shw':'');
windowHtml.style.display="none";
windowHtml.style.position="absolute";
windowHtml.style.left=options.left+"px";
windowHtml.style.top=options.top+"px";
windowHtml.style.width=options.width+"px";
if(!options.notKeepPos)
windowHtml.container='in';
if(options.height!="auto"){
if(isIE){
if(IEVer>=7){
windowHtml.style.minHeight=options.height+"px";
windowHtml.style.height="auto";
}else{
windowHtml.style.height=options.height+"px";
}
}else{
windowHtml.style.minHeight=options.height+"px";
windowHtml.style.height="auto";
}
}
windowHtml.style.zIndex=options.zIndex;
this._getContainer(options).appendChild(windowHtml);
Event.observe(windowHtml.id,'click',this._focusWindow.bind(this,id));
return windowHtml;
},
_createSystemBar:function(windowHtml,id,options){
var systemBar=document.createElement('div');
systemBar.id=this.options.prefix+id+this.options.systemBarPostfix;
if(options.systemBarClassName)
systemBar.className=options.systemBarClassName;
var g_c_move=options.allowDrag?'g_c_move':'';
var html='<div>';
if(options.hasCloseId){
html+='<span id ="'+options.closeId+'" class="r" title="关闭">&nbsp;</span>';
}
html+='<span style="display:block;" class="g_t_hide $$_handle_class '+g_c_move+'" id="'+options.titleId+'">'+options.title+'</span></div>';
systemBar.innerHTML=html;
windowHtml.appendChild(systemBar);
if(options.hasCloseId){
if(options.hiddenOnClose){
Event.observe(options.closeId,'click',this.hiddenWindow.bind(this,id));
}else{
Event.observe(options.closeId,'click',this.closeWindow.bind(this,id));
}
}
if(options.allowDrag){
this.simpleDragDrop.removeDraggable(windowHtml.id);
this.simpleDragDrop.addDraggable(windowHtml.id,{handle:'$$_handle_class',zindex:this.topIndex-1});
}
return systemBar;
},
_createPanel:function(windowHtml,id,options){
var panel=document.createElement('div');
panel.id=this.options.prefix+id+this.options.panelPostfix;
if(options.panelClassName)
panel.className=options.panelClassName;
windowHtml.appendChild(panel);
return panel;
},
_hideSelect:function(hide,noHideParent){
if(isIE&&IEVer<7){
var selectArray=document.getElementsByTagName("select");
var noHideSelectArray=noHideParent?noHideParent.getElementsByTagName("select"):null;
noHideSelectArray=$A(noHideSelectArray||[]);
if(selectArray){
for(var i=0;i<selectArray.length;i++){
if(selectArray[i].getAttribute("nohide")!="true"&&!noHideSelectArray.include(selectArray[i])){
selectArray[i].style.visibility=(hide==true)?'hidden':'inherit';
}
}
}
}
},
_createJSWindow:function(id,options){
var jsWindow={};
jsWindow.id=id;
jsWindow.options=options;
jsWindow.containerDiv=this._getContainer(options);
jsWindow.setPos=function(pos){this._setPos(jsWindow,pos);}.bind(this);
jsWindow.showWindow=function(){this._showWindow(jsWindow);}.bind(this);
jsWindow.updateTitle=function(title){this._updateTitle(jsWindow,title);}.bind(this);
jsWindow.hiddenWindow=function(){this._hiddenWindow(jsWindow);}.bind(this);
jsWindow.closeWindow=function(){this._closeWindow(jsWindow);}.bind(this);
jsWindow.focusWindow=function(){this.focusWindow(jsWindow);}.bind(this);
return jsWindow;
}
}
