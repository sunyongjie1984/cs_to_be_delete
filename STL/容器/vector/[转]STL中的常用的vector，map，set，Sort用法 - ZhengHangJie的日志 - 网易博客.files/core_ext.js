var PositionExt={};
PositionExt._baseIndex=50;
Object.extend(Object.extend(PositionExt,Position),{
within:function(element,x,y){
this.xcomp=x;
this.ycomp=y;
var pos=Sortable.containerPos[element.id];
if(pos==null){
if(element.parentNode&&element.parentNode.id)
pos=Sortable.containerPos[element.parentNode.id];
if(pos!=null){
if(x<pos[0]||x>(pos[0]+element.offsetWidth[0]))
return false;
pos=[pos[0]+element.offsetLeft||0,pos[1]+element.offsetTop];
}
}
if(pos==null)
this.offset=this.cumulativeOffset(element);
else
this.offset=pos;
if(PositionExt.allowVerticalScroll==true&&element.parentNode)
this.offset[1]-=element.parentNode.scrollTop;
return(y>=this.offset[1]&&
y<this.offset[1]+element.offsetHeight&&
x>=this.offset[0]&&
x<this.offset[0]+element.offsetWidth);
}
});
var Droppables={
drops:[],
remove:function(element){
this.drops=this.drops.reject(function(d){return d.element==$(element)});
},
add:function(element){
element=$(element);
var options=Object.extend({
greedy:true,
hoverclass:null
},arguments[1]||{});
if(options.containment){
options._containers=[];
var containment=options.containment;
if((typeof containment=='object')&&
(containment.constructor==Array)){
containment.each(function(c){options._containers.push($(c))});
}else{
options._containers.push($(containment));
}
options._containers.each(function(e){Element.setStyle(e,{zIndex:Element.getStyle(element,'zIndex')||'1'})});
}
if(options.accept)options.accept=[options.accept].flatten();
Element.makePositioned(element);
options.element=element;
this.drops.push(options);
},
isContained:function(element,drop){
var parentNode=element.parentNode;
return drop._containers.detect(function(c){return parentNode==c});
},
isAffected:function(point,element,drop){
if(!PositionExt.within(drop.element,point[0],point[1]))
return false;
return((drop.element!=element)&&
((!drop._containers)||
this.isContained(element,drop))&&
((!drop.accept)||
(Element.classNames(element).detect(
function(v){return drop.accept.include(v)})))
);
},
deactivate:function(drop){
if(drop.hoverclass)
Element.removeClassName(drop.element,drop.hoverclass);
this.last_active=null;
},
activate:function(drop){
if(drop.hoverclass)
Element.addClassName(drop.element,drop.hoverclass);
this.last_active=drop;
},
show:function(point,element){
if(!this.drops.length)return;
if(this.last_active)this.deactivate(this.last_active);
this.drops.each(function(drop){
if(Droppables.isAffected(point,element,drop)){
if(drop.onHover){
drop.onHover(element,drop.element,PositionExt.overlap(drop.overlap,drop.element));
Droppables.activate(drop);
}
if(drop.greedy){
Droppables.activate(drop);
throw $break;
}
}
});
},
fire:function(event,drag){
if(!this.last_active)return;
if(this.isAffected([Event.cursorX(event),Event.cursorY(event)],drag.element,this.last_active))
if(this.last_active.onDrop)
this.last_active.onDrop(drag,this.last_active.element,event);
},
reset:function(){
if(this.last_active)
this.deactivate(this.last_active);
}
}
var Draggables={
drags:[],
observers:[],
register:function(draggable){
if(this.drags.length==0){
this.eventMouseUp=this.endDrag.bindAsEventListener(this);
this.eventMouseMove=this.updateDrag.bindAsEventListener(this);
this.eventKeypress=this.keyPress.bindAsEventListener(this);
Event.observe(document,"mouseup",this.eventMouseUp);
Event.observe(document,"mousemove",this.eventMouseMove);
Event.observe(document,"keypress",this.eventKeypress);
}
this.drags.push(draggable);
},
unregister:function(draggable){
this.drags=this.drags.reject(function(d){return d==draggable});
if(this.drags.length==0){
Event.stopObserving(document,"mouseup",this.eventMouseUp);
Event.stopObserving(document,"mousemove",this.eventMouseMove);
Event.stopObserving(document,"keypress",this.eventKeypress);
}
},
activate:function(draggable){
window.focus();
this.activeDraggable=draggable;
},
deactivate:function(){
this.activeDraggable=null;
},
updateDrag:function(event){
if(!this.activeDraggable)return;
var _isScrolling=this.activeDraggable.checkScroll(Event.pointerY(event));
if(_isScrolling)return;
var pointer=[Event.cursorX(event),Event.cursorY(event)];
if(this._lastPointer&&(this._lastPointer.inspect()==pointer.inspect()))return;
this._lastPointer=pointer;
this.activeDraggable.updateDrag(event,pointer);
},
endDrag:function(event){
if(!this.activeDraggable)return;
this._lastPointer=null;
this.activeDraggable.endDrag(event);
this.activeDraggable=null;
},
keyPress:function(event){
if(this.activeDraggable)
this.activeDraggable.keyPress(event);
},
addObserver:function(observer){
this.observers.push(observer);
this._cacheObserverCallbacks();
},
removeObserver:function(element){
this.observers=this.observers.reject(function(o){return o.element==element});
this._cacheObserverCallbacks();
},
notify:function(eventName,draggable,event){
if(this[eventName+'Count']>0)
this.observers.each(function(o){
if(o[eventName])o[eventName](eventName,draggable,event);
});
},
_cacheObserverCallbacks:function(){
['onStart','onEnd','onDrag'].each(function(eventName){
Draggables[eventName+'Count']=Draggables.observers.select(
function(o){return o[eventName];}
).length;
});
}
}
var Draggable=Class.create();
Draggable.prototype={
initialize:function(element){
var options=Object.extend({
handle:false,
starteffect:function(element){
new Effect.Opacity(element,{duration:0.2,from:1.0,to:0.7});
},
reverteffect:function(element,top_offset,left_offset){
var dur=Math.sqrt(Math.abs(top_offset^2)+Math.abs(left_offset^2))*0.02;
element._revert=new Effect.Move(element,{x:-left_offset,y:-top_offset,duration:dur});
},
endeffect:function(element){
new Effect.Opacity(element,{duration:0.2,from:0.7,to:1.0});
},
zindex:1000,
revert:false,
scroll:false,
scrollSensitivity:20,
scrollSpeed:15,
snap:false,
bodyScroll:null
},arguments[1]||{});
this.element=$(element);
if(options.handle&&(typeof options.handle=='string'))
this.handle=Element.childrenWithClassName(this.element,options.handle)[0];
if(!this.handle)this.handle=$(options.handle);
if(!this.handle)this.handle=this.element;
if(options.scroll)options.scroll=$(options.scroll);
Element.makePositioned(this.element);
this.delta=options.currentDelta?options.currentDelta:this.currentDelta();
this.options=options;
this.dragging=false;
this._bodyScroll=options.bodyScroll||null;
this.eventMouseDown=this.initDrag.bindAsEventListener(this);
Event.observe(this.handle,"mousedown",this.eventMouseDown);
Draggables.register(this);
},
destroy:function(){
Event.stopObserving(this.handle,"mousedown",this.eventMouseDown);
Draggables.unregister(this);
this.element._revert=null;
this.element=null;
this.options.starteffect=null;
this.options.reverteffect=null;
this.options.endeffect=null;
this.options=null;
},
currentDelta:function(){
return([
parseInt(Element.getStyle(this.element,'left')||'0'),
parseInt(Element.getStyle(this.element,'top')||'0')]);
},
initDrag:function(event){
if(Event.isLeftClick(event)){
var src=Event.element(event);
if(src.tagName&&(
src.tagName=='INPUT'||
src.tagName=='SELECT'||
src.tagName=='OPTION'||
src.tagName=='BUTTON'||
src.tagName=='TEXTAREA'))return;
if(this.element._revert){
this.element._revert.cancel();
this.element._revert=null;
}
var pointer=[Event.cursorX(event),Event.cursorY(event)];
var pos=PositionExt.cumulativeOffset(this.element);
this.offset=[0,1].map(function(i){return(pointer[i]-pos[i])});
Draggables.activate(this);
Event.stop(event);
}
},
startDrag:function(event){
this.dragging=true;
if(this._bodyScroll)
document.ondrag=document.onselectstart=function(){return false;};
if(this.options.ghosting){
this._clone=this.element.cloneNode(true);
PositionExt.absolutize(this.element);
this.element.parentNode.insertBefore(this._clone,this.element);
}
if(this.options.scroll){
this.originalScrollLeft=this.options.scroll.scrollLeft;
this.originalScrollTop=this.options.scroll.scrollTop;
}
if(this.options.targeting){
this.element.parentNode.style.zIndex=PositionExt._baseIndex++;
}
if(this.options.zindex){
this.originalZ=parseInt(Element.getStyle(this.element,'z-index')||0);
this.element.style.zIndex=this.options.zindex;
}
Draggables.notify('onStart',this,event);
if(this.options.starteffect)this.options.starteffect(this.element);
},
updateDrag:function(event,pointer){
if(!this.dragging)this.startDrag(event);
Droppables.show(pointer,this.element);
Draggables.notify('onDrag',this,event);
this.draw(pointer);
if(this.options.change)this.options.change(this);
if(this.options.scroll){
this.stopScrolling();
var p=PositionExt.page(this.options.scroll);
p[0]+=this.options.scroll.scrollLeft;
p[1]+=this.options.scroll.scrollTop;
p.push(p[0]+this.options.scroll.offsetWidth);
p.push(p[1]+this.options.scroll.offsetHeight);
var speed=[0,0];
if(pointer[0]<(p[0]+this.options.scrollSensitivity))speed[0]=pointer[0]-(p[0]+this.options.scrollSensitivity);
if(pointer[1]<(p[1]+this.options.scrollSensitivity))speed[1]=pointer[1]-(p[1]+this.options.scrollSensitivity);
if(pointer[0]>(p[2]-this.options.scrollSensitivity))speed[0]=pointer[0]-(p[2]-this.options.scrollSensitivity);
if(pointer[1]>(p[3]-this.options.scrollSensitivity))speed[1]=pointer[1]-(p[3]-this.options.scrollSensitivity);
this.startScrolling(speed);
}
if(navigator.appVersion.indexOf('AppleWebKit')>0)window.scrollBy(0,0);
Event.stop(event);
},
checkScroll:function(_pointerY){
if(!this._bodyScroll)return false;
if(_pointerY>20&&_pointerY<this._bodyScroll.body.offsetHeight-20){
this.clearScroll();return false;
}
Draggable.___Step=(_pointerY<20?-1:1)*this._bodyScroll.step;
if(Draggable.___Timer)return true;
Draggable.___Timer=window.setInterval(this.scrollBody.bind(this),this._bodyScroll.interval);
return true;
},
scrollBody:function(){
var _body=this._bodyScroll.body,
_scrollTop=parseInt(_body.scrollTop)||0;
_curSTop=_scrollTop+Draggable.___Step;
if(_scrollTop<0||_curSTop==Draggable.___ScrTop){
this.clearScroll();return;
}
var _style=this.element.style,
_top=parseInt(_style.top)||0;
_style.top=(_top+Draggable.___Step)+'px';
_body.scrollTop=_curSTop;
Draggable.___ScrTop=_curSTop;
},
clearScroll:function(){
if(!Draggable.___Timer)return;
Draggable.___Step=0;
Draggable.___Timer=window.clearInterval(Draggable.___Timer);
},
finishDrag:function(event,success){
this.dragging=false;
if(this.options.ghosting){
PositionExt.relativize(this.element);
Element.remove(this._clone);
this._clone=null;
}
if(success)Droppables.fire(event,this);
Draggables.notify('onEnd',this,event);
if(this.options.targeting&&this.element._lastPointerPos){
PositionExt.relativize(this.element);
this.draw(this.element._lastPointerPos);
}
var revert=this.options.revert;
if(revert&&typeof revert=='function')revert=revert(this.element);
var d=this.currentDelta();
if(revert&&this.options.reverteffect){
this.options.reverteffect.apply(this,[this.element,
d[1]-this.delta[1],d[0]-this.delta[0]]);
}else{
this.delta=d;
}
Sortable.resize(this.element);
if(this.options.zindex){
this.element.style.zIndex=this.originalZ;
}
if(this.options.endeffect)
this.options.endeffect(this.element);
Draggables.deactivate(this);
Droppables.reset();
},
keyPress:function(event){
if(event.keyCode!=Event.KEY_ESC)return;
this.finishDrag(event,false);
Event.stop(event);
},
endDrag:function(event){
if(!this.dragging)return;
if(this._bodyScroll)
document.ondrag=document.onselectstart=null;
this.stopScrolling();
this.finishDrag(event,true);
Event.stop(event);
},
draw:function(point){
this.element._lastPointerPos=[point[0],point[1]];
var pos;
if(this.element.parentNode&&this.element.parentNode.id)
pos=Sortable.containerPos[this.element.parentNode.id];
if(pos==null)
pos=PositionExt.cumulativeOffset(this.element);
else
pos=[pos[0]+this.element.offsetLeft||0,pos[1]+this.element.offsetTop];
var d=this.currentDelta();
pos[0]-=d[0];pos[1]-=d[1];
if(this.options.scroll){
pos[0]-=this.options.scroll.scrollLeft-this.originalScrollLeft;
pos[1]-=this.options.scroll.scrollTop-this.originalScrollTop;
}
var p=[0,1].map(function(i){
return(point[i]-pos[i]-this.offset[i])
}.bind(this));
if(this.options.snap){
if(typeof this.options.snap=='function'){
p=this.options.snap(p[0],p[1]);
}else{
if(this.options.snap instanceof Array){
p=p.map(function(v,i){
return Math.round(v/this.options.snap[i])*this.options.snap[i]}.bind(this))
}else{
p=p.map(function(v){
return Math.round(v/this.options.snap)*this.options.snap}.bind(this))
}
}}
var style=this.element.style;
if((!this.options.constraint)||(this.options.constraint=='horizontal'))
style.left=p[0]+"px";
if((!this.options.constraint)||(this.options.constraint=='vertical'))
style.top=p[1]+"px";
if(style.visibility=="hidden")style.visibility="";
},
stopScrolling:function(){
if(this.scrollInterval){
clearInterval(this.scrollInterval);
this.scrollInterval=null;
}
},
startScrolling:function(speed){
this.scrollSpeed=[speed[0]*this.options.scrollSpeed,speed[1]*this.options.scrollSpeed];
this.lastScrolled=new Date();
this.scrollInterval=setInterval(this.scroll.bind(this),10);
},
scroll:function(){
var current=new Date();
var delta=current-this.lastScrolled;
this.lastScrolled=current;
this.options.scroll.scrollLeft+=this.scrollSpeed[0]*delta/1000;
this.options.scroll.scrollTop+=this.scrollSpeed[1]*delta/1000;
Droppables.show(Draggables._lastPointer,this.element);
Draggables.notify('onDrag',this);
this.draw(Draggables._lastPointer);
if(this.options.change)this.options.change(this);
}
}
var SortableObserver=Class.create();
SortableObserver.prototype={
initialize:function(element,observer){
this.element=$(element);
this.observer=observer;
this.lastValue=Sortable.serialize(this.element);
},
onStart:function(){
this.lastValue=Sortable.serialize(this.element);
},
onEnd:function(){
Sortable.unmark();
Sortable.untarget();
if(this.lastValue!=Sortable.serialize(this.element))
this.observer(this.element)
}
}
var Sortable={
sortables:new Array(),
containerPos:{},
options:function(element){
element=$(element);
return this.sortables.detect(function(s){return s.element==element});
},
destroy:function(element){
element=$(element);
this.sortables.findAll(function(s){return s.element==element||s.element.id==element.id}).each(function(s){
Draggables.removeObserver(s.element);
s.droppables.each(function(d){Droppables.remove(d)});
s.draggables.invoke('destroy');
});
this.sortables=this.sortables.reject(function(s){return s.element==element||s.element.id==element.id});
},
clear:function(){
this.sortables=this.sortables.reject(function(s){return $(s.element.id)==null});
},
resize:Prototype.emptyFunction
,
create:function(element){
element=$(element);
this.containerPos[element.id]=PositionExt.cumulativeOffset(element);
if(element==null)return;
var options=Object.extend({
element:element,
tag:'li',
dropOnEmpty:false,
tree:false,
overlap:'vertical',
constraint:'vertical',
containment:element,
handle:false,
only:false,
hoverclass:null,
ghosting:false,
scroll:false,
format:/^[^_]*_(.*)$/,
targeting:false,
allowVerticalScroll:false,
bodyScroll:null,
resize:Prototype.emptyFunction,
onChange:Prototype.emptyFunction,
onUpdate:Prototype.emptyFunction
},arguments[1]||{});
PositionExt.allowVerticalScroll=options.allowVerticalScroll;
this.destroy(element);
this.resize=options.resize;
var options_for_draggable={
targeting:options.targeting,
revert:true,
scroll:options.scroll,
ghosting:options.ghosting,
constraint:options.constraint,
handle:options.handle,
bodyScroll:options.bodyScroll
};
if(options.starteffect)
options_for_draggable.starteffect=options.starteffect;
if(options.reverteffect)
options_for_draggable.reverteffect=options.reverteffect;
else
if(options.ghosting)options_for_draggable.reverteffect=function(element){
element.style.top=0;
element.style.left=0;
};
if(options.endeffect)
options_for_draggable.endeffect=options.endeffect;
if(options.zindex)
options_for_draggable.zindex=options.zindex;
if(options.currentDelta)
options_for_draggable.currentDelta=options.currentDelta;
var options_for_droppable={
overlap:options.overlap,
containment:options.containment,
hoverclass:options.hoverclass,
onHover:Sortable.onHover,
onDrop:Sortable.onDrop,
greedy:!options.dropOnEmpty
}
Element.cleanWhitespace(element);
options.draggables=[];
options.droppables=[];
if(options.dropOnEmpty){
Droppables.add(element,
{containment:options.containment,onHover:Sortable.onEmptyHover,onDrop:Sortable.onDrop,greedy:false});
options.droppables.push(element);
}
(this.findElements(element,options)||[]).each(function(e){
var handle=options.handle?
Element.childrenWithClassName(e,options.handle)[0]:e;
options.draggables.push(
new Draggable(e,Object.extend(options_for_draggable,{handle:handle})));
Droppables.add(e,options_for_droppable);
options.droppables.push(e);
});
this.sortables.push(options);
Draggables.addObserver(new SortableObserver(element,options.onUpdate));
},
clearOffset:function(){
Sortable.containerPos={};
},
findElements:function(element,options){
if(!element.hasChildNodes())return null;
var elements=[];
$A(element.childNodes).each(function(e){
if(e.tagName&&e.tagName.toUpperCase()==options.tag.toUpperCase()&&
(!options.only||(Element.hasClassName(e,options.only))))
elements.push(e);
if(options.tree){
var grandchildren=this.findElements(e,options);
if(grandchildren)elements.push(grandchildren);
}
}.bind(this));
return(elements.length>0?elements.flatten():null);
},
onHover:function(dragElem,dropon,overlap){
var element=Sortable.target(dragElem,dropon.parentNode)||dragElem;
if(overlap>0.5){
Sortable.mark(dropon,'before');
if(dropon.previousSibling!=element){
var oldParentNode=element.parentNode;
dropon.parentNode.insertBefore(element,dropon);
if(dropon.parentNode!=oldParentNode)
Sortable.options(oldParentNode).onChange(element);
Sortable.options(dropon.parentNode).onChange(element);
}
}else{
Sortable.mark(dropon,'after');
var nextElement=dropon.nextSibling||null;
if(nextElement!=element){
if(!Sortable._targeter||nextElement!=Sortable._targeter){
var oldParentNode=element.parentNode;
dropon.parentNode.insertBefore(element,nextElement);
if(dropon.parentNode!=oldParentNode)
Sortable.options(oldParentNode).onChange(element);
Sortable.options(dropon.parentNode).onChange(element);
}
}
}
},
onEmptyHover:function(dragElem,dropon){
var element=Sortable.target(dragElem,dropon)||dragElem;
if(element.parentNode!=dropon){
var oldParentNode=element.parentNode;
if(dropon.parentNode.childNodes[dropon.parentNode.childNodes.length-1]!=element)
dropon.appendChild(element);
Sortable.options(oldParentNode).onChange(element);
Sortable.options(dropon).onChange(element);
}
},
onDrop:function(drag,dropon,event){
var _dropon=Sortable.options(dropon)?dropon:(Sortable.options(dropon.parentNode)?dropon.parentNode:null);
var element=drag.element;
if(_dropon){
if(Sortable._targeter){
Sortable._targeter.parentNode.insertBefore(element,Sortable._targeter);
if(typeof element._originalWidth=='undefined'||typeof element._originalHeight=='undefined'){
element._originalWidth='';
element._originalHeight='';
}
drag.delta=[0,0];
PositionExt.relativize(drag.element);
}
}
},
target:function(element,dropon){
var sortable=Sortable.options(dropon);
if(sortable==null||sortable.ghosting||!sortable.targeting)return null;
if(!Sortable._targeter){
Sortable._targeter=document.createElement(element.tagName);
element.parentNode.insertBefore(Sortable._targeter,element);
PositionExt.absolutize(element);
Element.setStyle(Sortable._targeter,{position:'relative',margin:Element.getStyle(element,'margin'),left:'0px',top:'0px',width:element._originalWidth||'',height:(element._originalHeight?element._originalHeight:(element.offsetHeight?(element.offsetHeight+'px'):'')),border:'1px dotted red'});
}
return Sortable._targeter;
},
untarget:function(){
if(Sortable._targeter){
Element.removeChild(Sortable._targeter);
Sortable._targeter=null;
}
},
unmark:function(){
if(Sortable._marker)Element.hide(Sortable._marker);
},
mark:function(dropon,position){
var sortable=Sortable.options(dropon.parentNode);
if(sortable&&!sortable.ghosting)return;
if(!Sortable._marker){
Sortable._marker=$('dropmarker')||document.createElement('DIV');
Element.hide(Sortable._marker);
Element.addClassName(Sortable._marker,'dropmarker');
Sortable._marker.style.position='absolute';
document.getElementsByTagName("body").item(0).appendChild(Sortable._marker);
}
var offsets=PositionExt.cumulativeOffset(dropon);
Sortable._marker.style.left=offsets[0]+'px';
Sortable._marker.style.top=offsets[1]+'px';
if(position=='after')
if(sortable.overlap=='horizontal')
Sortable._marker.style.left=(offsets[0]+dropon.clientWidth)+'px';
else
Sortable._marker.style.top=(offsets[1]+dropon.clientHeight)+'px';
Element.show(Sortable._marker);
},
sequence:function(element){
element=$(element);
var options=Object.extend(this.options(element),arguments[1]||{});
return $(this.findElements(element,options)||[]).map(function(item){
return item.id.match(options.format)?item.id.match(options.format)[1]:item.id;
});
},
serialize:function(element){
element=$(element);
var name=encodeURIComponent(
(arguments[1]&&arguments[1].name)?arguments[1].name:element.id);
return Sortable.sequence(element,arguments[1]).map(function(item){
return encodeURIComponent(item);
}).join(',');
}
}
if(NetEase==undefined){
var NetEase={};
}
NetEase.PlaceEdit=Class.create();
NetEase.PlaceEdit.prototype={
initialize:function(element,resourceId,saveFunc){
element=$(element);
this.element=element;
this.resourceId=resourceId;
this.options=Object.extend({
saveText:'保　存',
cancelText:'取　消',
savaButStyle:'Butt',
cancelButStyle:'CancelButt',
orText:'&nbsp;',
savingText:'<i>保存中...</i>&nbsp;',
clickToEditText:'点击并编辑',
emptyText:'<i style="color:#999">点击这里添加描述</i>',
loadingText:'Loading...',
editType:'input',
textrows:4,
maxLength:-1,
btnBelow:true,
editStyle:'inputEdit',
highLightColor:'#FFFFE1',
dataStream:null,
itemIdx:null,
afterFinishedFunc:Prototype.emptyFunction,
param:false,
dofirst:Prototype.emptyFunction,
canBeNull:true,
space:false,
spaceHeight:'16px',
userCallBack:Prototype.emptyFunction,
editIcon:null,
editIconElem:null,
attchEventToParent:false,
bExtendText:false,
extendText:'&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;'
},arguments[3]||{});
this._convertForSpaceAndEmpty();
if(this.options.maxLength<=0){
if(this.options.editType=='input')
this.options.maxLength=30;
else
this.options.maxLength=200;
}
this.saveFunc=saveFunc;
this.eventReg();
},
resetAll:function(){
window.should_I_ignore_stuff_because_is_editing=0;
window.should_I_ignore_stuff_because_of_button_action=0;
},
_getInput:function(){
var editString='';
if(this.options.editType=='input')
editString='<input type="text" id="content'+this.element.id+'" class="'+this.options.editStyle+' input_textbox" style="padding:2px;" maxlength="'+this.options.maxLength+'"/>';
else
editString='<textarea id="content'+this.element.id+'" class="'+this.options.editStyle+'" style="padding:4px;" maxlength="'+this.options.maxLength+'" cols="20" rows="'+this.options.textrows+'"></textarea>';
if(this.options.btnBelow)
editString+='<br/>';
else
editString+='&nbsp;';
editString+='<input type="button" class="'+this.options.savaButStyle+' input_button" value="'+this.options.saveText+'" id="submit'+this.element.id+'"/>'+
this.options.orText+'<input type="button" '+'class="'+this.options.cancelButStyle+' input_button" value="'+this.options.cancelText+'" id="reset'+this.element.id+'"/>';
return editString;
},
startEditing:function(){
if(window.should_I_ignore_stuff_because_is_editing||window.should_I_ignore_stuff_because_of_button_action)
return;
window.should_I_ignore_stuff_because_is_editing=1;
this.options.dofirst();
this.isEditing=true;
this.unhighLight();
this.text=this._getInputCharsFromDisplayHTML(this.element.innerHTML);
if((this.options.space)&&(this.text==this.options.space))
this.text='';
else if(this.text==this.options.emptyText)
this.text='';
this.element.innerHTML=this._getInput();
var content=$('content'+this.element.id);
content.value=TrimSBCandDBC(this.text);
content.focus();
content.select();
$('submit'+this.element.id).onclick=this.savingChanges.bindAsEventListener(this);
$('reset'+this.element.id).onclick=this.endEditing.bindAsEventListener(this);
},
savingChanges:function(event){
event&&Event.stop(event);
var editValue='';
if(this.options.editType=='input')
editValue=$('content'+this.element.id).value;
else
editValue=$('content'+this.element.id).value;
if(TrimSBCandDBC(editValue)==''&&editValue!=''){
editValue=' ';
}
if(editValue==this.text){
this.endEditing();
return;
}
else{
if((!this.options.canBeNull)&&(editValue=='')){
this.endEditing();
return;
}
this.editValue=editValue;
this.element.innerHTML=this.options.savingText;
if(this.saveFunc){
var saveString=editValue.replace(/\r/g,'');
if(saveString.length>this.options.maxLength){
alert('输入的内容过长，请不要超过'+this.options.maxLength+'个字');
this.endEditing();
return false;
}
this.saveFunc(this.resourceId,saveString,this.callBackFunc.bind(this));
}
else{
this.endEditing();
return;
}
}
},
callBackFunc:function(success){
if(success){
if(this.editValue=='')
this._handleForEmptyInput();
else{
var chars=this._getDisplayHTMLFromInputChars(this.editValue);
if(this.options.bExtendText){
if(chars=='&nbsp;')
chars=this.options.extendText;
}
this.element.innerHTML=chars;
}
if(typeof this.options.dataStream==Array){
var value=this.editValue;
if(this.options.itemIdx){
var item=this.options.itemIdx;
this.options.dataStream.each(function(e){e[item]=value});
}
else
this.options.dataStream.each(function(e){e=value});
}
else if(this.options.dataStream){
if(this.options.itemIdx)
this.options.dataStream[this.options.itemIdx]=this.editValue;
else
this.options.dataStream=this.editValue;
}
}
else{
if(this.text=='')
this._handleForEmptyInput();
else
this.element.innerHTML=this.text;
}
window.should_I_ignore_stuff_because_is_editing=0;
this.isEditing=false;
this.options.afterFinishedFunc(this.options.param);
this.options.userCallBack({success:success,value:this.editValue});
},
endEditing:function(event){
event&&Event.stop(event);
window.should_I_ignore_stuff_because_is_editing=0;
this.isEditing=false;
if(this.text=='')
this._handleForEmptyInput();
else{
var xx=this._getDisplayHTMLFromInputChars(this.text);
this.element.innerHTML=xx;
}
},
onMouseover:function(){
if(window.should_I_ignore_stuff_because_is_editing||window.should_I_ignore_stuff_because_of_button_action)
return;
this.highLight();
},
onMouseout:function(){
this.unhighLight();
},
highLight:function(){
if(!$(this.options.editIcon)){
this.element.style.backgroundColor=this.options.highLightColor;
}else{
$(this.options.editIcon).style.display='';
}
},
unhighLight:function(){
if(!$(this.options.editIcon)){
this.element.style.backgroundColor="";
}else{
$(this.options.editIcon).style.display='none';
}
},
eventReg:function(){
this.element.onclick=this.startEditing.bind(this);
this.element.onmouseover=this.onMouseover.bind(this);
this.element.onmouseout=this.onMouseout.bind(this);
if($(this.options.editIcon)){
$(this.options.editIcon).style.position='absolute';
$(this.options.editIcon).innerHTML='&nbsp;<span class="c05" style="cursor:pointer;font:normal 14px \'宋体\';">[编辑]</span>';
$(this.options.editIcon).style.width='80px';
$(this.options.editIcon).style.display='none';
var node=$(this.options.editIcon);
if(this.options.attchEventToParent){
node=this.element.parentNode;
}
node.onclick=this.startEditing.bind(this);
node.onmouseover=this.onMouseover.bind(this);
node.onmouseout=this.onMouseout.bind(this);
}
},
_getInputCharsFromDisplayHTML:function(sHTML){
var chars=sHTML;
chars=chars.replace(/<br>/ig,(Browser.isFirefox()?"\n":"\r\n"));
chars=chars.replace(/&lt;/g,"<");
chars=chars.replace(/&gt;/g,">");
chars=chars.replace(/&quot;/g,"\"");
chars=chars.replace(/&#039;/g,"'");
chars=chars.replace(/&amp;/g,"&");
chars=chars.replace(/&nbsp;/g," ");
return chars;
},
_getDisplayHTMLFromInputChars:function(sChars){
var html=sChars;
html=html.replace(/&/g,"&amp;");
html=html.replace(/</g,"&lt;");
html=html.replace(/>/g,"&gt;");
html=html.replace(/"/g,"&quot;");
html=html.replace(/'/g,"&#039;");
html=html.replace(/ /g,"&nbsp;");
html=html.replace((Browser.isFirefox()?/\n/g:/\r\n/g),"<br>");
return html;
},
_handleForEmptyInput:function(){
if(this.options.space)
this.element.innerHTML=this.options.space;
else
this.element.innerHTML=this.options.emptyText;
},
_convertForSpaceAndEmpty:function(){
var tempNode=$('__$$__temp__$$__');
if(tempNode==null){
tempNode=document.createElement('div');
tempNode.style.display='none';
UD.body.appendChild(tempNode);
tempNode.id='__$$__temp__$$__';
}
if(this.options.space){
tempNode.innerHTML=this.options.space;
this.options.space=tempNode.innerHTML;
}
if(this.options.emptyText){
tempNode.innerHTML=this.options.emptyText;
this.options.emptyText=tempNode.innerHTML;
}
}
};
if(NetEase==undefined){
var NetEase={};
}
NetEase.CachePage=Class.create();
NetEase.CachePage.prototype={
initialize:function(){
this.options=Object.extend({
loadFunc:Prototype.emptyFunction,
loadParam:{},
presentFunc:Prototype.emptyFunction,
presentSlideFunc:Prototype.emptyFunction,
filterFunc:Prototype.emptyFunction,
organizeFunc:function(list){return list},
userPresentFuncParam:{},
pageSize:0,
prefetchMulti:1,
prefetch:false,
markID:'',
customPageIds:false,
totalSize:-1,
onlyLoadOnce:false,
beforeID:'',
beforePrev:Prototype.emptyFunction,
beforeNext:Prototype.emptyFunction,
detSlideIterator:Prototype.emptyFunction,
delIterator:Prototype.emptyFunction,
updateIterator:Prototype.emptyFunction,
needRefreshAfterUpdate:true,
RefreshAfterAdd:true,
initData:false
},arguments[0]||{});
this.cacheData=[];
this.markIDArray=[];
this._initial();
this.bMarkFirst=true;
},
reset:function(){
this.cacheData=[];
if(this.options.totalSize!=-1)
this.lastPage=1;
else
this.lastPage=0;
this.curPage=0;
this.canNext=false;
this.canPrev=false;
this.getState=1;
this.isEnd=true;
this.loadCount=0;
this._generateMark();
},
_loadMoreDataFunc:function(type){
if(this.curPage<0)
this.curPage=0;
this.options.loadParam.offset=this.cacheData.length
this.options.loadParam.limit=((this.options.prefetch)?this.options.prefetchMulti:0)*this.options.pageSize+((this.curPage+1)*this.options.pageSize-this.cacheData.length);
if(type==0)
this.options.loadFunc(this.options.loadParam,this._mergeDataFunc.bind(this));
else
this.options.loadFunc(this.options.loadParam,this._mergeMoreDataFunc.bind(this));
},
_mergeDataFunc:function(dataList){
dataList=this.options.organizeFunc(dataList);
if(dataList==null||dataList.length==0){
this.canNext=false;
this.getState=0;
if(this.isEnd==true){
this._generateMark();
return false;
}
}
else if(dataList.length<((this.curPage+1)*this.options.pageSize-this.cacheData.length)){
this.canNext=false;
this.getState=0;
}else if(dataList.length<this.options.loadParam.limit){
this.canNext=true;
this.getState=0;
}else{
this.canNext=true;
this.getState=1;
}
this.curPage++;
if(this.lastPage&&this.curPage>this.lastPage)
this.lastPage=this.curPage;
this.options.filterFunc(dataList);
if(dataList)
dataList.each(this._iterator.bind(this));
this._generateMark();
this._presentTemplate();
},
_mergeMoreDataFunc:function(dataList){
dataList=this.options.organizeFunc(dataList);
if(dataList==null||dataList.length<=this.curPage*this.options.pageSize-this.cacheData.length){
this.canNext=false;
this.getState=0;
}else if(dataList.length<((this.curPage+1)*this.options.pageSize-this.cacheData.length)){
this.canNext=true;
this.getState=0;
}else if(dataList.length<this.options.loadParam.limit){
this.canNext=true;
this.getState=0;
}else{
this.canNext=true;
this.getState=1;
}
this.options.filterFunc(dataList);
dataList.each(this._iterator.bind(this));
this._generateMark();
this._presentTemplate();
},
_iterator:function(e){
this.cacheData.push(e);
},
nextPage:function(){
if(!this.canNext)
return false;
this.canNext=false;
var canGetMore=true;
if(this.options.onlyLoadOnce&&this.loadCount>=1)
canGetMore=false;
if((this.curPage+1)*this.options.pageSize>this.cacheData.length&&this.getState==1&&canGetMore){
this.loadCount++;
this._loadMoreDataFunc(0);
}else{
if(this.curPage*this.options.pageSize<this.cacheData.length){
this.canNext=true;
if(this.getState==0&&(this.curPage+1)*this.options.pageSize>=this.cacheData.length)
this.canNext=false;
this.curPage++;
}
this._generateMark();
this._presentTemplate();
}
},
prevPage:function(){
if(!this.canPrev)
return false;
this.canPrev=false;
this.curPage--;
if(this.curPage<=1)
this.curPage=1;
this.canNext=true;
this._generateMark();
this._presentTemplate();
},
refreshCurPage:function(bRefreshPage){
this._setSlideMode(false);
if(bRefreshPage==true){
this.is_first_load=null;
}
this._generateMark();
this._presentTemplate();
},
selectPage:function(page){
if(page<1)
page=1;
if(page>this.curPage){
this._setSlideMode(false);
this.nextPage();
return;
}
if(page<this.curPage){
if(page>1)
this.canPrev=true;
else
this.canPrev=false;
this.canNext=true;
this.curPage=page;
}
this.refreshCurPage();
},
_generateMark:function(){
this._generateMarkData();
this._generateMarkHTML();
this._registerCachePageEvent();
},
_presentTemplate:function(){
if(this.slideMode==true){
this.options.presentSlideFunc(this.cacheData[this.curDataIndex],this.options.userPresentFuncParam);
}else{
this.options.presentFunc(this._prepareForPresent(),this.options.userPresentFuncParam);
}
},
_prepareForPresent:function(){
var result=[];
if(this.cacheData.length<=(this.curPage-1)*this.options.pageSize){
if(this.curPage>1){
this.curPage--;
this._generateMark();
}
}
var i=0;
for(i=(this.curPage-1)*this.options.pageSize;i<this.curPage*this.options.pageSize&&i<this.cacheData.length;i++)
result.push(this.cacheData[i]);
if(i==this.cacheData.length)
this.isEnd=true;
else
this.isEnd=false;
return result;
},
_clickPrev:function(sId){
if(sId!=null&&this.beforeIDArray!=null){
for(var i=0;i<this.beforeIDArray.length;i++){
if(this.beforeIDArray[i]==sId){
this.options.beforePrev();
}
}
}
this.op="prev";
this.prevPage();
return false;
},
_clickNext:function(sId){
if(sId!=null&&this.beforeIDArray!=null){
for(var i=0;i<this.beforeIDArray.length;i++){
if(this.beforeIDArray[i]==sId){
this.options.beforeNext();
}
}
}
this.op="next";
this.nextPage();
return false;
},
removeOne:function(item,notRefresh){
var removed=this.cacheData.select(this._rejectIter.bind(this,item));
this._removeItem(item);
this._afterRemove(1,notRefresh);
return removed;
},
removeItems:function(itemList,notRefresh){
itemList.each(this._removeItem.bind(this));
this._afterRemove(itemList.length,notRefresh);
},
_removeItem:function(item){
this.cacheData=this.cacheData.reject(this._rejectIter.bind(this,item));
},
_afterRemove:function(count,notRefresh){
if(this.curPage>1&&this.cacheData.length%this.options.pageSize==0){
this.curPage--;
}
if(this.options.totalSize>0&&this.options.totalSize>(-1)*count){
this.options.totalSize-=count;
this.lastPage=this._getTotalSize();
}
if(this.canNext){
if(this.isEnd&&this.getState==1){
this._loadMoreDataFunc(1);
}else{
if(notRefresh!=true){
this._generateMark();
this._presentTemplate();
}
}
}else{
if(notRefresh!=true){
this._generateMark();
this._presentTemplate();
}
}
},
_rejectIter:function(item,e){
return this.options.delIterator(item,e);
},
getSelectSlide:function(){
return this.cacheData[this.curDataIndex];
},
changeToSlideMode:function(item){
var data=this.cacheData.detect(this._detectItr.bind(this,item));
if(data){
this._setSlideMode(true);
this._generateMark();
this._presentTemplate();
}
},
_detectItr:function(item,e,index){
var value=this.options.detSlideIterator(item,e);
if(value){
this.curDataIndex=index;
return true;
}
return false;
},
_slideNext:function(){
if(!this.canNextSlide)
return false;
this.canNextSlide=false;
if(this.options.totalSize>-1){
if(this.curDataIndex>=(this.options.totalSize-1)){
this._generateMark();
return false;
}
}
this.curDataIndex++;
this._setSlideMode(true);
if(this.curDataIndex%this.options.pageSize==0){
this.nextPage();
}else{
this._generateMark();
this._presentTemplate();
}
return false;
},
_slidePrev:function(){
if(!this.canPrevSlide)
return false;
this.canPrevSlide=false;
if(this.curDataIndex<=0){
this._generateMark();
return false;
}
this.curDataIndex--;
this._setSlideMode(true);
if(this.curDataIndex%this.options.pageSize==(this.options.pageSize-1)){
this.prevPage();
}else{
this._generateMark();
this._presentTemplate();
}
return false;
},
_setSlideMode:function(isSlide){
if(isSlide==true){
this.slideMode=true;
}else{
this.slideMode=false;
}
},
addOne:function(item,head,notRefresh){
if(head){
var temp=[];
temp.push(item);
this.options.filterFunc(temp);
this.cacheData.unshift(item);
}
else{
var temp=[];
temp.push(item);
this.options.filterFunc(temp);
this.cacheData.push(item);
}
if(this.cacheData.length>this.curPage*this.options.pageSize){
if(!this.canNext){
this.canNext=true;
}
}
if(this.options.totalSize>-1){
this.options.totalSize++;
this.lastPage=this._getTotalSize();
}
if(this.options.RefreshAfterAdd){
if(notRefresh!=true){
this._generateMark();
this._presentTemplate();
}
}
},
getAllCachedData:function(){
return this.cacheData;
},
updateOne:function(item,notRefresh){
this.cacheData.each(this._updateIter.bind(this,item));
if(notRefresh!=true){
this._generateMark();
if(this.options.needRefreshAfterUpdate)
this._presentTemplate();
}
},
_updateIter:function(item,e,index){
if(this.options.updateIterator(item,e)){
Object.extend(this.cacheData[index],item);
}
},
getCurPage:function(){
return this.curPage;
},
getTotalSize:function(){
return this.options.totalSize;
},
_getTotalSize:function(){
var d=(this.options.totalSize%this.options.pageSize==0)?0:1;
var r=parseInt(this.options.totalSize/this.options.pageSize+d+'');
if(r<1)
r=1;
return r;
},
_initial:function(){
if(this.options.totalSize>-1)
this.lastPage=this._getTotalSize();
this.curPage=0;
this.canNext=true;
this.canPrev=false;
this.getState=1;
this.isEnd=false;
this.loadCount=0;
if(this.options.markID)
this.markIDArray=this.options.markID.split(":");
if(this.options.beforeID)
this.beforeIDArray=this.options.beforeID.split(":");
if(this.options.initData){
this.options.initData.each(this._iterator.bind(this));
}
},
initCacheData:function(dataList,isListEnd){
dataList=this.options.organizeFunc(dataList);
if(dataList==null||dataList.length==0){
this.canNext=false;
this.getState=0;
}
else if(dataList.length<((this.curPage+1)*this.options.pageSize-this.cacheData.length)){
this.canNext=false;
this.getState=0;
}else{
this.canNext=true;
if(isListEnd)
this.getState=0;
else
this.getState=1;
}
this.curPage++;
if(this.lastPage&&this.curPage>this.lastPage)
this.lastPage=this.curPage;
this.options.filterFunc(dataList);
dataList.each(this._iterator.bind(this));
this._generateMark();
this._presentTemplate();
},
_generateMarkData:function(){
if(this.curPage>1)
this.canPrev=true;
else
this.canPrev=false;
if(this.curPage<1)
this.curPage=1;
if(this.lastPage&&this.curPage>this.lastPage)
this.curPage=this.lastPage;
if(this.lastPage){
if(!this.canNext)
this.lastPage=this.curPage;
if(this.curPage==this.lastPage)
this.canNext=false;
}
if(this.slideMode==true){
if(this.canNext)
this.canNextSlide=true;
else{
if(this.cacheData[this.curDataIndex+1]==null)
this.canNextSlide=false;
else
this.canNextSlide=true;
}
if(this.canPrev)
this.canPrevSlide=true;
else{
if(this.cacheData[this.curDataIndex-1]==null)
this.canPrevSlide=false;
else
this.canPrevSlide=true;
}
}
},
_generateMarkHTML:function(){
if(this.options.customPageIds){
if(this.slideMode==true){
if(this.canPrevSlide)
$(this.options.customPageIds[0]).style.visibility="visible";
else
$(this.options.customPageIds[0]).style.visibility="hidden";
if(this.canNextSlide)
$(this.options.customPageIds[1]).style.visibility="visible";
else
$(this.options.customPageIds[1]).style.visibility="hidden";
}else{
if(this.canPrev)
$(this.options.customPageIds[0]).style.visibility="visible";
else
$(this.options.customPageIds[0]).style.visibility="hidden";
if(this.canNext)
$(this.options.customPageIds[1]).style.visibility="visible";
else
$(this.options.customPageIds[1]).style.visibility="hidden";
}
}
if(this.options.markID){
if(this.is_first_load==null){
this.markIDArray.each((function(a){return function(markId){
if($(markId)){
var innerHTML='<div class="c09">\
           <span id="$$_prev_img_'+markId+'"></span>&nbsp;\
           <span id="$$_num'+markId+'" class="c07">&nbsp;</span>&nbsp;\
           <span id="$$_next_img_'+markId+'"></span></div>';
$(markId).innerHTML=innerHTML;
var _i=a.curPage;
if(a.lastPage){
_i+='/'+a.lastPage;
}
$('$$_num'+markId).innerHTML=_i;
}
};})(this));
this.is_first_load=true;
}else{
this.markIDArray.each((function(a){return function(markId){
if($(markId)){
var _i=a.curPage;
if(a.lastPage){
_i+='/'+a.lastPage;
}
$('$$_num'+markId).innerHTML=_i;
}
};})(this));
}
this._adjustStyle();
}
},
_adjustStyle:function(){
this.markIDArray.each((function(a){return function(markId){
if($(markId)){
$('$$_prev_img_'+markId).innerHTML=(a.canPrev)?'<span class="a_a c_c c06">上页</span>':'上页';
$('$$_next_img_'+markId).innerHTML=(a.canNext)?'<span class="a_a c_c c06">下页</span>':'下页';
}
};})(this));
},
_registerCachePageEvent:function(){
if(this.slideMode==true){
if(this.options.customPageIds){
if(this.register_custom_event_is!="slideevent"){
$(this.options.customPageIds[0]).onclick=this._slidePrev.bind(this);
$(this.options.customPageIds[1]).onclick=this._slideNext.bind(this);
this.register_custom_event_is="slideevent";
}
}
if(this.options.markID){
if(this.register_mark_event_is!="slideevent"){
this.markIDArray.each((function(a){return function(markId){
if($(markId)){
$('$$_prev_img_'+markId).onclick=a._slidePrev.bind(a,markId);
$('$$_next_img_'+markId).onclick=a._slideNext.bind(a,markId);
this.register_mark_event_is="slideevent";
}
};})(this));
}
}
}else{
if(this.options.customPageIds){
if(this.register_custom_event_is!="notslideevent"){
$(this.options.customPageIds[0]).onclick=this._clickPrev.bind(this);
$(this.options.customPageIds[1]).onclick=this._clickNext.bind(this);
this.register_custom_event_is="notslideevent";
}
}
if(this.options.markID){
if(this.register_mark_event_is!="notslideevent"){
this.markIDArray.each((function(a){return function(markId){
if($(markId)){
$('$$_prev_img_'+markId).onclick=a._clickPrev.bind(a,markId);
$('$$_next_img_'+markId).onclick=a._clickNext.bind(a,markId);
this.register_mark_event_is="notslideevent";
}
};})(this));
}
}
}
},
resetCachePageEvent:function(){
this.register_mark_event_is=null;
this.register_custom_event_is=null;
}
}
if(NetEase==undefined){
var NetEase={};
}
NetEase.PageNumber=Class.create();
NetEase.PageNumber.prototype={
initialize:function(sObjectName){
this.options=Object.extend({
loadFunc:Prototype.emptyFunction,
loadParam:{},
presentFunc:Prototype.emptyFunction,
filterFunc:Prototype.emptyFunction,
userPresentFuncParam:{},
pageSize:0,
prefetchMulti:1,
markID:'',
totalSize:-1,
beforeID:'',
beforePrev:Prototype.emptyFunction,
beforeNext:Prototype.emptyFunction,
beforeChange:Prototype.emptyFunction,
delIterator:Prototype.emptyFunction,
updateIterator:Prototype.emptyFunction,
needRefreshAfterUpdate:true,
RefreshAfterAdd:true,
RefreshAfterDel:true,
useCache:true,
isDiv:false,
changeLocationHash:true,
showLastPage:true,
popupSize:5
},arguments[1]||{});
this.totalPages=0;
this.objName=sObjectName;
this.curPage;
this.cacheData=[];
this.markIDArray=[];
this.beforeIDArray=[];
this._iTextSpanWidth;
this._init();
},
_init:function(){
if(this.options.totalSize>-1)
this.totalPages=this._getTotalPages();
this.curPage=1;
if(this.options.markID)
this.markIDArray=this.options.markID.split(":");
this._getContainer();
if(this.options.beforeID)
this.beforeIDArray=this.options.beforeID.split(":");
},
_getContainer:function(){
if(UD==undefined||UD.body==undefined){
this.container=window.document.body;
return;
}
var ele=$(this.markIDArray[0]);
this.container=UD.body;
if(this.options.isDiv&&ele){
while(ele!=UD.body&&ele.id!='blog-163-com-body'&&ele!=UD.body&&ele!=document.body)
ele=ele.parentNode;
if(ele==UD.body||ele.id==document.body)this.container=UD.body;
}
},
reset:function(){
this.cacheData=[];
this.curPage=1;
this.options.totalSize=0;
this.totalPages=1;
this._generateMarks();
},
initCacheData:function(oData){
this.options.filterFunc(oData);
if(this.options.useCache){
for(var i=0;i<oData.length;i++){
this.cacheData[i]=oData[i];
}
}
},
getAllCachedData:function(){
var datas=[];
this.cacheData.each(function(e){if(e!=null){datas.push(e)}})
return datas;
},
getTotalPages:function(){
return this.totalPages;
},
getCurPageNum:function(){
return this.curPage;
},
getCurOffset:function(){
return this.options.pageSize*(this.curPage-1);
},
getTotalSize:function(){
return this.options.totalSize;
},
setTotalSize:function(iSize){
this.options.totalSize=iSize;
this.totalPages=this._getTotalPages();
},
refreshMarks:function(){
this._generateMarks();
},
refreshCurPage:function(){
this.show();
},
nextPage:function(){
this.curPage++;
if(this.curPage>this.totalPages)
this.curPage=this.totalPages;
this.show();
return false;
},
prevPage:function(){
this.curPage--;
if(this.curPage<1)
this.curPage=1;
this.show();
return false;
},
setPageSize:function(iSize){
this.options.pageSize=iSize;
this.totalPages=this._getTotalPages();
},
show:function(){
var _iOffset=this.options.pageSize*(this.curPage-1);
var _iLimit=this.options.pageSize;
if(this.options.useCache){
var _data=this._hasFullData(_iOffset,_iLimit)
if(_data!=null){
this._display(_data);
}else{
this.options.loadParam.offset=_iOffset;
this.options.loadParam.limit=_iLimit*(this.options.prefetchMulti?this.options.prefetchMulti:1);
this.options.loadFunc(this.options.loadParam,this._display.bind(this));
}
}else{
this.options.loadParam.offset=_iOffset;
this.options.loadParam.limit=_iLimit;
this.options.loadFunc(this.options.loadParam,this._display.bind(this));
}
},
_display:function(oData){
if(oData==null||oData.length==0){
if(this.curPage>1){
this.curPage--;
this.options.totalSize=this.curPage*this.options.pageSize;
this.totalPages=this._getTotalPages();
this.cacheData=[];
this.show();
return false;
}
}
this.options.filterFunc(oData);
if(this.options.useCache){
var _iOffset=this.options.pageSize*(this.curPage-1);
for(var i=0;i<oData.length;i++){
this.cacheData[_iOffset+i]=oData[i];
}
}
this.options.presentFunc(oData.slice(0,this.options.pageSize),this.options.userPresentFuncParam);
this._generateMarks();
},
_hasFullData:function(iOffset,iLimit){
var _oDataDisplay=[];
var _iLen=iOffset+iLimit>this.options.totalSize?this.options.totalSize-iOffset:iLimit;
for(var i=0;i<_iLen;i++){
var _oData=this.cacheData[iOffset+i];
if(_oData==undefined||_oData==null)
return null;
_oDataDisplay[i]=_oData;
}
return _oDataDisplay;
},
_generateMarks:function(){
var _iMarkLen=this.markIDArray.length;
for(var i=0;i<_iMarkLen;i++){
var markId=this.markIDArray[i];
var _oMark=$(markId);
if(_oMark){
_oMark.innerHTML=this._generateHTML(markId);
this._setUIEvent(markId);
}
}
return false;
},
_getTotalPages:function(){
if(this.options.pageSize==0){
return 1;
}
var _iLast=(this.options.totalSize%this.options.pageSize==0)?0:1;
var _iPages=parseInt(this.options.totalSize/this.options.pageSize+_iLast+'');
if(_iPages<1)
_iPages=1;
return _iPages;
},
goToPage:function(iPageIndex){
if(iPageIndex>this.totalPages||iPageIndex<1)
return;
this.curPage=iPageIndex;
this.show();
},
addOne:function(item,head,notRefresh){
if(this.options.totalSize>-1){
this.options.totalSize++;
this.totalPages=this._getTotalPages();
}
if(this.options.useCache){
if(head){
this.cacheData.unshift(item);
}else{
this.cacheData[this.options.totalSize-1]=item;
}
}
if(this.options.RefreshAfterAdd&&notRefresh!=true){
this.show();
}
},
removeOne:function(item,notRefresh){
var removed=null;
if(this.options.useCache){
removed=this._removeItem(item);
}
this._afterRemove(1,notRefresh);
return removed;
},
removeItems:function(items,notRefresh){
if(this.options.useCache){
items.each(this._removeItem.bind(this));
}
this._afterRemove(items.length,notRefresh);
},
_removeItem:function(item){
var index=-1;
for(var i=0;i<this.options.totalSize;i++){
if(this.cacheData[i]==undefined||this.cacheData[i]==null)
continue;
if(this.options.delIterator(item,this.cacheData[i])){
index=i;
break;
}
}
if(index==-1){
return null;
}
var removed=this.cacheData[index];
if(index+1<this.options.totalSize){
this.cacheData[index]=this.cacheData[index+1];
this.cacheData[index+1]=null;
}else{
this.cacheData[index]=null;
}
for(++index;index<this.options.totalSize-1;index++){
if(this.cacheData[index+1]!=undefined&&this.cacheData[index+1]!=null){
this.cacheData[index]=this.cacheData[index+1];
this.cacheData[index+1]=null;
}
}
return removed;
},
_afterRemove:function(len,notRefresh){
if(this.options.totalSize>-1){
this.options.totalSize-=len;
this.totalPages=this._getTotalPages();
}
if(this.curPage==this.totalPages+1&&this.options.totalSize%this.options.pageSize==0){
this.curPage--;
}
if(this.options.RefreshAfterDel&&notRefresh!=true){
this.show();
}
},
updateOne:function(oItem,bNotRefresh){
if(this.options.useCache){
var _iOffset=this.options.pageSize*(this.curPage-1);
var index=-1;
for(var i=0;i<this.options.pageSize;i++){
if(!this.cacheData[i+_iOffset])
continue;
if(this.options.updateIterator(oItem,this.cacheData[i+_iOffset])){
index=i+_iOffset;
break;
}
}
if(index==-1){
this.cacheData=[];
return;
}
Object.extend(this.cacheData[index],oItem);
}
if(bNotRefresh!=true&&this.options.needRefreshAfterUpdate){
this.show();
}
},
emptyCache:function(){
this.cacheData=[];
},
_generateHTML:function(sMarkId){
var s=[];
s.push('<div class="pnc">');
if(this.curPage==1){
if(this.options.isDiv==false)
s.push('<div class="l c09">上页</div>');
else
s.push('<div class="l off">上页</div>');
}else{
if(this.options.isDiv==false)
s.push('<div class="l c06" id="$$_prev_'+sMarkId+'" onmouseover="'+this.objName+'.overL(\'$$_prev_'+sMarkId+'\');" onmouseout="'+this.objName+'.outL(\'$$_prev_'+sMarkId+'\');" onclick="'+this.objName+'.clickPrev(\''+sMarkId+'\');">上页</div>');
else
s.push('<div class="l dcolr" id="$$_prev_'+sMarkId+'" onmouseover="'+this.objName+'.overL(\'$$_prev_'+sMarkId+'\');" onmouseout="'+this.objName+'.outL(\'$$_prev_'+sMarkId+'\');" onclick="'+this.objName+'.clickPrev(\''+sMarkId+'\');">上页</div>');
}
s.push('<div class="b" id="$$_textBorder_'+sMarkId+'" onmouseover="'+this.objName+'.overM(\''+sMarkId+'\');" onmouseout="'+this.objName+'.outM(\''+sMarkId+'\');" onclick="'+this.objName+'.clickTextBorder(\''+sMarkId+'\', event);">');
if(this.options.isDiv==false)
s.push('<div class="txt c06" id="$$_pageText_'+sMarkId+'">'+this.curPage+'/'+this.totalPages+'</div>');
else
s.push('<div class="txt dcolr" id="$$_pageText_'+sMarkId+'">'+this.curPage+'/'+this.totalPages+'</div>');
s.push('<div class="arw">&nbsp;</div>');
s.push('</div>');
if(this.totalPages==this.curPage){
if(this.options.isDiv==false)
s.push('<div class="l c09">下页</div>');
else
s.push('<div class="l off">下页</div>');
}else{
if(this.options.isDiv==false)
s.push('<div class="l c06" id="$$_next_'+sMarkId+'" onmouseover="'+this.objName+'.overL(\'$$_next_'+sMarkId+'\');" onmouseout="'+this.objName+'.outL(\'$$_next_'+sMarkId+'\');" onclick="'+this.objName+'.clickNext(\''+sMarkId+'\');">下页</div>');
else
s.push('<div class="l dcolr" id="$$_next_'+sMarkId+'" onmouseover="'+this.objName+'.overL(\'$$_next_'+sMarkId+'\');" onmouseout="'+this.objName+'.outL(\'$$_next_'+sMarkId+'\');" onclick="'+this.objName+'.clickNext(\''+sMarkId+'\');">下页</div>');
}
s.push('</div>');
this._addList2Container(sMarkId);
return s.join('');
},
_addList2Container:function(sMarkId){
var _oChildren=this.container.childNodes;
var _iChildLen=_oChildren.length;
var m=null;
for(var k=_iChildLen-1;k>=0;k--){
if('$$_opt_'+sMarkId==_oChildren[k].id){
m=_oChildren[k];
break;
}
}
if(m!=null){
Element.removeChild(m);
delete m;
}
var o=document.createElement("DIV");
o.id='$$_opt_'+sMarkId;
if(this.options.isDiv==false)
o.className='opt bd01';
else
o.className='opt bdblack';
o.style.display='none';
o.onmouseover=this.optMouseOver.bind(this,sMarkId);
var t=[];
var _iStart=1;
var _iEnd=this.totalPages;
var _totalPop=this.options.popupSize*2+1;
if(this.totalPages>_totalPop){
if(this.curPage-this.options.popupSize<=1){
_iStart=1;
_iEnd=_totalPop;
}else if(this.curPage+this.options.popupSize>=this.totalPages){
_iStart=this.totalPages-_totalPop+1;
_iEnd=this.totalPages;
}else{
_iStart=this.curPage-this.options.popupSize;
_iEnd=this.curPage+this.options.popupSize;
}
}
if(_iStart>1){
this.pop_index=this.curPage-_iStart+1;
t.push('<a href="#" onclick="'+this.objName+'.clickPageNumber(\''+sMarkId+'\', '+1+', \'$$_opt_'+sMarkId+'\', \'$$_textBorder_'+sMarkId+'\');return false;">');
t.push('首页');
t.push('</a>');
}else{
this.pop_index=this.curPage-1;
}
for(var i=_iStart;i<=_iEnd;i++){
t.push('<a href="#" onclick="'+this.objName+'.clickPageNumber(\''+sMarkId+'\', '+i+', \'$$_opt_'+sMarkId+'\', \'$$_textBorder_'+sMarkId+'\');return false;">');
t.push(i);
t.push('</a>');
}
if(_iEnd<this.totalPages&&this.options.showLastPage){
t.push('<a href="#" onclick="'+this.objName+'.clickPageNumber(\''+sMarkId+'\', '+this.totalPages+', \'$$_opt_'+sMarkId+'\', \'$$_textBorder_'+sMarkId+'\');return false;">');
t.push('末页');
t.push('</a>');
}
o.innerHTML=t.join('');
this.container.appendChild(o);
},
_setUIEvent:function(sMarkId){
var _opt=$('$$_opt_'+sMarkId);
_opt.style.width=6+13+(1+this.computeNumber(this.curPage)+this.computeNumber(this.totalPages))*7+"px";
Event.observe(window.document,"click",this._clickDocument.bind(this,sMarkId));
},
computeNumber:function(iNum){
var n=0,c=iNum;
while(c>=1){
n++;
c=c/10;
}
return n;
},
_clickDocument:function(sMarkId){
var _opt=$('$$_opt_'+sMarkId);
var _textBorder=$('$$_textBorder_'+sMarkId);
if(_opt)
_opt.style.display="none";
if(_textBorder){
_textBorder.className="b";
}
},
optMouseOver:function(sMarkId){
var _opt=$('$$_opt_'+sMarkId);
var _optA=_opt.getElementsByTagName("a");
var _oA=_optA[this.pop_index];
_oA.className="";
},
clickTextBorder:function(sMarkId,event){
event=event||window.event;
var _opt=$('$$_opt_'+sMarkId);
if(_opt.style.display=="none"){
this.closeAllPopup();
_opt.style.display="block";
_opt.scrollTop=(this.curPage-1)*14;
var _oA=_opt.getElementsByTagName("a")[this.pop_index];
_oA.className="ttt";
var _oPageOffset=Position.cumulativeOffset($('$$_textBorder_'+sMarkId));
var w;
if(UD==undefined||UD.window==undefined)
w=window;
else
w=UD.window;
var iPageTopOffset=_oPageOffset[1]-w.scrollTop;
var iPageBottomOffset=document.documentElement.clientHeight-iPageTopOffset;
if(_opt.offsetHeight>iPageBottomOffset){
_opt.style.left=_oPageOffset[0]+"px";
_opt.style.top=_oPageOffset[1]-_opt.offsetHeight+"px";
}else{
_opt.style.left=_oPageOffset[0]+"px";
_opt.style.top=_oPageOffset[1]+22+"px";
}
Event.stop(event);
}else{
_opt.style.display="none";
}
return false;
},
clickPrev:function(sMarkId){
if(this.options.changeLocationHash){
window.location.hash='pn'+(this.curPage-1);
}
if(sMarkId!=null&&this.beforeIDArray!=null){
for(var i=0;i<this.beforeIDArray.length;i++){
if(this.beforeIDArray[i]==sMarkId){
this.options.beforePrev();
}
}
}
this.closeAllPopup();
this.prevPage();
return false;
},
clickNext:function(sMarkId){
if(this.options.changeLocationHash){
window.location.hash='pn'+(this.curPage+1);
}
if(sMarkId!=null&&this.beforeIDArray!=null){
for(var i=0;i<this.beforeIDArray.length;i++){
if(this.beforeIDArray[i]==sMarkId){
this.options.beforeNext();
}
}
}
this.closeAllPopup();
this.nextPage();
return false;
},
closeAllPopup:function(){
var _iMarkLen=this.markIDArray.length;
for(var i=0;i<_iMarkLen;i++){
var markId=this.markIDArray[i];
var _opt=$('$$_opt_'+markId);
_opt.style.display="none";
}
},
clickPageNumber:function(sMarkId,iIndex,sOpt,sTextBorder){
var oOpt=$(sOpt);
var oTextBorder=$(sTextBorder);
if(this.options.changeLocationHash){
window.location.hash='pn'+iIndex;
}
oOpt.style.display="none";
oTextBorder.className="b";
if(iIndex==this.curPage){
return false;
}
if(sMarkId!=null&&this.beforeIDArray!=null){
for(var i=0;i<this.beforeIDArray.length;i++){
if(this.beforeIDArray[i]==sMarkId){
this.options.beforeChange();
}
}
}
this.goToPage(iIndex);
return false;
},
overM:function(sMarkId){
var oElem=$("$$_textBorder_"+sMarkId);
if(!oElem)return;
if(this.options.isDiv==false)
oElem.className="bover bd01";
else
oElem.className="bover bdblack";
},
outM:function(sMarkId){
var oElem=$("$$_textBorder_"+sMarkId);
if(!oElem)return;
var _opt=$('$$_opt_'+sMarkId);
if(_opt.style.display=="none"){
oElem.className="b";
}
},
overL:function(sElemName){
var oElem=$(sElemName);
if(!oElem)return;
if(this.options.isDiv==false)
oElem.className="lover bd01";
else
oElem.className="lover bdblack";
},
outL:function(sElemName){
var oElem=$(sElemName);
if(!oElem)return;
if(this.options.isDiv==false)
oElem.className="l c06";
else
oElem.className="l dcolr";
}
}
if(NetEase==undefined){
var NetEase={};
}
NetEase.CommentPublish=Class.create();
NetEase.CommentPublish.commentShowTemplate=null;
NetEase.CommentPublish.commentPubTemplate=null;
NetEase.CommentPublish.prototype={
initialize:function(oCommentArray,sParentId,iTotalCommentCount,sComShowElemId,sComPubElemId){
this._oOptions=Object.extend({
bCanClose:true,
bHasCancelBtn:false,
bNeedCheckLogin:false,
bNeedCheckRight:false,
bDefaultPubClose:false,
iAllowComment:0,
bSupportDeleteComment:false,
iPageSize:10,
iMainCommentCount:0,
iHostId:null,
sHostName:'匿名',
iVisitorId:null,
sVisitorName:'匿名',
sVisitorNickname:'匿名',
sVisitorAvatar:'',
sVisitorIP:'',
iEditorWidth:0,
iEditorHeight:90,
iEditorMaxLen:65535,
sLoginRedirect:'',
fnOpenCommentEffect:null,
fnAddComment:null,
oAddCommentParams:null,
fnAfterAddComment:null,
oAfterAddCommentParams:null,
fnDelComment:null,
oDelCommentParams:null,
fnAfterDelComment:null,
oAfterDelCommentParams:null,
fnMoreData:null,
fnCloseComments:null,
fnReportBad:null,
sObjName:null,
sUrlPrefix:'',
sCircleBaseUrl:'http://q.163.com',
fnCloseCommentDiv:null,
isHomeModule:false
},arguments[5]||{});
this._sParentId=sParentId;
this._sOrigParentId=sParentId;
this._oCommentArray=oCommentArray;
this._iTotalCommentCount=iTotalCommentCount;
this._sComShowElemId=sComShowElemId;
this._sCmPubElemId=sComPubElemId;
if(this._oOptions.iPageSize<=0)
this._oOptions.iPageSize=10;
this._bStatusNotLogin=false;
this._bStatusNoRight=false;
this._sDefaultVisitorAvatarUrl=Const.STDomain+'/style/common/stranger.gif';
this._iCurrPageIndex=1;
this._iTotalPageNumber=0;
this.htmleditor;
this.htmleditorfloat;
this._mainComId="-1";
this._replyComId="-1";
this._replyToUserName="";
this._replyToUserNick="";
this.subComments;
this._comPubFloatElemId="comPubContainer";
this._load();
this._sCurrentActDivId="";
return this;
},
_load:function(){
this._computePageNumber();
if(this._oOptions.bNeedCheckLogin){
if(UD.visitorRank<=-100){
this._bStatusNotLogin=true;
}else{
this._bStatusNotLogin=false;
}
}
if(this._oOptions.bNeedCheckRight){
if(UD.visitorRank>=this._oOptions.iAllowComment){
this._bStatusNoRight=false;
}else{
this._bStatusNoRight=true;
}
}
if(NetEase.CommentPublish.commentShowTemplate==null)
NetEase.CommentPublish.commentShowTemplate=createJSTAndParse("jst_global_comment_show",jst_global_comment_show);
if(NetEase.CommentPublish.commentPubTemplate==null)
NetEase.CommentPublish.commentPubTemplate=createJSTAndParse("jst_global_comment_pub",jst_global_comment_pub);
this.displayCommentArea();
},
reload:function(oCommentArray,sParentId,iTotalCommentCount,iAllowComment){
this._oCommentArray=oCommentArray;
if(!this._bStatusNoRight){
this.hideValidCodeImg(this._sOrigParentId);
this.htmleditor.emptyContent();
}
this._sParentId=sParentId;
this._oOptions.iAllowComment=iAllowComment;
this._iTotalCommentCount=iTotalCommentCount;
this._iCurrPageIndex=1;
this._computePageNumber();
this._setCommentShowArea();
},
displayCommentArea:function(){
this._setCommentShowArea();
this._setCommentPubArea();
var disable=false;
if(this._bStatusNotLogin||this._bStatusNoRight)
disable=true;
if(!this._bStatusNoRight)
this._setHtmlEditor(disable);
if(this._oOptions.fnOpenCommentEffect!=null){
this._oOptions.fnOpenCommentEffect(this._sParentId,this._initEditor.bind(this));
}else{
if(this._oOptions.bDefaultPubClose==false){
this._blindDownComments(this._sCmPubElemId,this._initEditor.bind(this));
}
}
},
_blindDownComments:function(sElemId,fnInit){
var _oSucc={success:false};
$(sElemId).style.display="";
fnInit();
},
_setCommentShowArea:function(){
var _oData={coms:this._oCommentArray,parentId:this._sParentId,pageNum:this._iCurrPageIndex,totalPageNum:this._iTotalPageNumber,
comCount:this._oOptions.iMainCommentCount,canClose:this._oOptions.bCanClose,
containerObjName:this._oOptions.sObjName,noCommentRight:this._bStatusNoRight,
commentRange:this._oOptions.iPageSize,visitorAvatar:this._oOptions.sVisitorAvatar,defaultVisitorAvatarUrl:this._sDefaultVisitorAvatarUrl,
hostId:this._oOptions.iHostId,
visitorId:this._oOptions.iVisitorId,visitorName:this._oOptions.sVisitorName,hostName:this._oOptions.sHostName,
supportDeleteComment:this._oOptions.bSupportDeleteComment,prefix:this._oOptions.sUrlPrefix,
circleBaseUrl:this._oOptions.sCircleBaseUrl,isHomeModule:this._oOptions.isHomeModule};
var _sShowResult=NetEase.CommentPublish.commentShowTemplate.process(_oData);
var _oComShow=$(this._sComShowElemId);
if(Trim(_sShowResult)!=""){
_oComShow.innerHTML=_sShowResult;
_oComShow.style.display="";
}
else{
_oComShow.style.display="none";
}
},
_setCommentPubArea:function(){
var _bVisitorAvatarDefault=false;
if(this._oOptions.sVisitorAvatar.length<7||this._oOptions.sVisitorAvatar.substr(0,7)=="/style/"||this._oOptions.sVisitorAvatar=="-1000")
_bVisitorAvatarDefault=true;
var _sUserName;
if(this._oOptions.iVisitorId!=0)
_sUserName=this._oOptions.sVisitorNickname.replace(/[\u0000-\u001F]/g,'');
else
_sUserName="网易博友"+this._getLastIPPart(this._oOptions.sVisitorIP);
var _oData={parentId:this._sParentId,editorId:this._sParentId,hostId:this._oOptions.iHostId,
allowComment:this._oOptions.iAllowComment,needCheckLogin:this._oOptions.bNeedCheckLogin,needCheckRight:this._oOptions.bNeedCheckRight,
disabled:this._bStatusNotLogin||this._bStatusNoRight,notLogin:this._bStatusNotLogin,noCommentRight:this._bStatusNoRight,
canClose:this._oOptions.bCanClose,userName:_sUserName,
hasCancelBtn:this._oOptions.bHasCancelBtn,
containerObjName:this._oOptions.sObjName,fnOpenCommentEffect:this._oOptions.sLoginRedirect,
visitorAvatar:this._oOptions.sVisitorAvatar,hostName:this._oOptions.sHostName,visitorRank:UD.visitorRank,
visitorId:this._oOptions.iVisitorId,visitorName:this._oOptions.sVisitorName,visitorNickname:this._oOptions.sVisitorNickname,
editorMaxLen:this._oOptions.iEditorMaxLen,
defaultVisitorAvatarUrl:this._sDefaultVisitorAvatarUrl,visitorAvatarDefault:_bVisitorAvatarDefault,isHomeModule:this._oOptions.isHomeModule,isAudit:true};
var _sPubresult=jst_global_comment_pub.processUseCache(_oData);
$(this._sCmPubElemId).innerHTML=_sPubresult;
},
_setCommentPubFloatArea:function(){
var _bVisitorAvatarDefault=false;
if(this._oOptions.sVisitorAvatar.length<7||this._oOptions.sVisitorAvatar.substr(0,7)=="/style/"||this._oOptions.sVisitorAvatar=="-1000")
_bVisitorAvatarDefault=true;
var _sUserName;
if(this._oOptions.iVisitorId!=0)
_sUserName=this._oOptions.sVisitorNickname;
else
_sUserName="网易博友"+this._getLastIPPart(this._oOptions.sVisitorIP);
var _oData={parentId:this._sParentId+"_float",oldParentId:this._sParentId,editorId:this._sParentId,hostId:this._oOptions.iHostId,
allowComment:this._oOptions.iAllowComment,needCheckLogin:this._oOptions.bNeedCheckLogin,needCheckRight:this._oOptions.bNeedCheckRight,
disabled:this._bStatusNotLogin||this._bStatusNoRight,notLogin:this._bStatusNotLogin,noCommentRight:this._bStatusNoRight,
canClose:this._oOptions.bCanClose,userName:_sUserName,
hasCancelBtn:true,
containerObjName:this._oOptions.sObjName,fnOpenCommentEffect:this._oOptions.sLoginRedirect,
visitorAvatar:this._oOptions.sVisitorAvatar,hostName:this._oOptions.sHostName,visitorRank:UD.visitorRank,
visitorId:this._oOptions.iVisitorId,visitorName:this._oOptions.sVisitorName,visitorNickname:this._oOptions.sVisitorNickname,
editorMaxLen:this._oOptions.iEditorMaxLen,
defaultVisitorAvatarUrl:this._sDefaultVisitorAvatarUrl,visitorAvatarDefault:_bVisitorAvatarDefault,isHomeModule:this._oOptions.isHomeModule};
var _sPubFloatResult=jst_global_comment_pub_float.process(_oData);
if($(this._comPubFloatElemId))
$(this._comPubFloatElemId).innerHTML=_sPubFloatResult;
},
_setHtmlEditor:function(bDisable){
var advEdtCrt=this._createAdvanceEditor.bind(this);
this.htmleditor=new NetEase.PlainEditor(this._sParentId,"edt"+this._sParentId,
{disabled:bDisable,width:this._oOptions.iEditorWidth,height:this._oOptions.iEditorHeight,
maxlen:this._oOptions.iEditorMaxLen,advEdtCrt:advEdtCrt});
this.htmleditor._switchEditor();
if(UD.visitorRank<0){
if(!bDisable){
}
}else if(this.htmleditor.editor){
if(isIE){
this.htmleditor.editor.attachEvent("onfocus",function(){
this._saveCommentPublish();
}.bind(this));
}else{
this.htmleditor.editor.addEventListener("focus",function(){
this._saveCommentPublish();
}.bind(this),false);
}
}
},
_computePageNumber:function(){
this._iTotalPageNumber=parseInt(this._oOptions.iMainCommentCount/this._oOptions.iPageSize)+
((this._oOptions.iMainCommentCount%this._oOptions.iPageSize!=0)?1:0);
},
moveToPage:function(iPageIndex,noScroll){
if(this._oOptions.fnMoreData!=null){
if(iPageIndex<=0)
alert("页码不能小于等于0");
this._iCurrPageIndex=iPageIndex;
this._oOptions.fnMoreData(this._sParentId,this._oOptions.iPageSize,(iPageIndex-1)*this._oOptions.iPageSize,
this._postPageComment.bind(this));
if(noScroll==true){
Element.scrollTo("comShowHeader_"+this._sParentId);
}
}
},
_postPageComment:function(oCommentArray){
this._oCommentArray=oCommentArray;
this._setCommentShowArea();
},
closeComments:function(sParentId){
if(this._oOptions.fnCloseComments!=null){
this._oOptions.fnCloseComments(sParentId);
}
if(this._oOptions.fnCloseCommentDiv!=null){
this._oOptions.fnCloseCommentDiv(sParentId);
}
},
_disablePubBtn:function(sParentId,bDisable){
var _oPubbtn=$("$$_pubbtn"+sParentId);
if(_oPubbtn==null)return;
if(bDisable){
_oPubbtn.disabled=true;
this._disabledFun=_oPubbtn.onclick;
_oPubbtn.onclick="";
}else{
if(this._disabledFun!=null)
_oPubbtn.onclick=this._disabledFun;
_oPubbtn.disabled=false;
this._disabledFun=null;
}
},
addComment:function(sParentId){
this._disablePubBtn(sParentId,true);
$("$$_comsubmithint"+sParentId)&&($("$$_comsubmithint"+sParentId).style.top="5px");
if(!this._isFloatParentId(sParentId)){
this._saveCommentPublish();
}
var _oUserName=$("username"+sParentId);
var _sUsrname=Trim(_oUserName.value);
if(_sUsrname==''){
UD.isAudit=true;
showInfo("$$_comsubmithint"+sParentId,UD.isAudit?"请输入姓名":"请输入昵称","info");
_oUserName.focus();
this._disablePubBtn(sParentId,false);
return false;
}
if(UD.visitorRank<=-100){
var _sValCode=$("valcode"+sParentId);
if(_sValCode==null){
showInfo("$$_comsubmithint"+sParentId,"请输入评论","info");
this._disablePubBtn(sParentId,false);
return false;
}else{
if($("valcode"+sParentId).value==""){
showInfo("$$_comsubmithint"+sParentId,"请输入验证码","info");
this._disablePubBtn(sParentId,false);
return false;
}else if($("valcode"+sParentId).value.length!=4){
showInfo("$$_comsubmithint"+sParentId,"验证码为4位","info");
this._disablePubBtn(sParentId,false);
return false;
}
}
}
var _sContent=this.htmleditor.getContent();
if(this._isFloatParentId(sParentId)){
_sContent=this.htmleditorfloat.getContent();
}
if(this.htmleditor.editor&&!this.htmleditor.editor.isFocused){
_sContent="";
}
if(isEmptyContent(_sContent)){
showInfo("$$_comsubmithint"+sParentId,"请输入评论","info");
this._disablePubBtn(sParentId,false);
return false;
}
if((this._isFloatParentId(sParentId)&&this.htmleditorfloat.IsExceedMaxLen())||
(!this._isFloatParentId(sParentId)&&this.htmleditor.IsExceedMaxLen())){
$("$$_comsubmithint"+sParentId)&&($("$$_comsubmithint"+sParentId).style.top="-53px");
showInfo("$$_comsubmithint"+sParentId,"输入内容超过最大字数"+this._oOptions.iEditorMaxLen+"，请重新编辑后提交","info");
this._disablePubBtn(sParentId,false);
return false;
}
var _oNewComment=new Object();
_oNewComment.parentId=this._sParentId;
_oNewComment.publisherId=this._oOptions.iVisitorId;
_oNewComment.publisherName=this._oOptions.sVisitorName;
_oNewComment.content=_sContent;
_oNewComment.publishTime=new Date();
_oNewComment.publisherNickname=_oUserName.value;
_oNewComment.ip=this._oOptions.sVisitorIP;
var _oEmail=$("email"+sParentId);
var _sEmail="";
if(_oEmail){
_sEmail=Trim(_oEmail.value);
}
_oNewComment.publisherEmail=_sEmail;
_oNewComment.publisherUrl="";
_oNewComment.replyToUserId=this.sReplyToUserId;
_oNewComment.sReplyToUserName=this.sReplyToUserName;
_oNewComment.publisherAvatarUrl=this._oOptions.sVisitorAvatar;
_oNewComment.mainComId=this._mainComId;
_oNewComment.replyComId=this._replyComId;
_oNewComment.replyToUserName=this._replyToUserName;
_oNewComment.replyToUserNick=this._replyToUserNick;
if(this._oOptions.fnAddComment!=null){
if(this._oOptions.oAddCommentParams!=null){
this._oOptions.oAddCommentParams.valcodeid=sParentId;
}
this._oOptions.fnAddComment(_oNewComment,this._oOptions.oAddCommentParams,this._postAddComment.bind(this,sParentId));
}else{
this._disablePubBtn(sParentId,false);
}
},
_postAddComment:function(sParentId,oNewComment){
if(UD.visitorRank<0){
this._genValidCodeImg(sParentId,false);
}
if(oNewComment==null){
dwrlog('评论添加失败','error');
this._disablePubBtn(sParentId,false);
return;
}
if(oNewComment.spam>0){
alert("你在短时间内发布了过多的评论，评论受限。");
dwrlog('评论添加失败','error');
this._disablePubBtn(sParentId,false);
return;
}
if(this._isFloatParentId(sParentId)){
this.htmleditorfloat.emptyContent();
}else{
this.htmleditor.emptyContent();
}
this._iTotalCommentCount+=1;
if(oNewComment.mainComId==-1)
this._oOptions.iMainCommentCount+=1;
this._computePageNumber();
this._saveCommentPublish();
if(this._iCurrPageIndex!=1){
this.moveToPage(1,false);
}
else{
var _oNewArray=[];
var _mainComId=oNewComment.mainComId;
if(_mainComId=="-1"){
_oNewArray.push(oNewComment);
for(var i=0;i<this._oCommentArray.length;i++){
_oNewArray.push(this._oCommentArray[i]);
}
}else{
if(this._oCommentArray!=null&&this._oCommentArray.length>0){
for(var i=0;i<this._oCommentArray.length;i++){
if(this._oCommentArray[i].id==_mainComId){
if(this._oCommentArray[i].subComments==null){
this._oCommentArray[i].subComments=[];
}
this._oCommentArray[i].subComments.push(oNewComment);
_oNewArray.push(this._oCommentArray[i]);
this._oCommentArray[i]=null;
break;
}
}
for(var i=0;i<this._oCommentArray.length;i++){
if(this._oCommentArray[i]){
_oNewArray.push(this._oCommentArray[i]);
}
}
}else{
_oNewArray.push(oNewComment);
}
}
while(_oNewArray.length>this._oOptions.iPageSize){
_oNewArray.pop();
}
this._oCommentArray=_oNewArray;
this._setCommentShowArea();
}
dwrlog('评论添加成功','ok');
this._disablePubBtn(sParentId,false);
if(this._oOptions.fnAfterAddComment!=null){
this._oOptions.fnAfterAddComment(oNewComment,this._oOptions.oAfterAddCommentParams);
}
},
_postAddRecommend:function(sParentId,oNewComment){
if(oNewComment.spam>0){
alert("你在短时间内发布了过多的评论，评论受限。");
dwrlog('评论添加失败','error');
this._disablePubBtn(sParentId,false);
this.htmleditor.emptyContent();
return;
}
this._iTotalCommentCount+=1;
this._oOptions.iMainCommentCount+=1;
this._computePageNumber();
if(this._iCurrPageIndex!=1){
this.moveToPage(1,false);
}
else{
var _oNewArray=[];
_oNewArray.push(oNewComment);
for(var i=0;i<this._oCommentArray.length;i++){
_oNewArray.push(this._oCommentArray[i]);
}
while(_oNewArray.length>this._oOptions.iPageSize){
_oNewArray.pop();
}
this._oCommentArray=_oNewArray;
this._setCommentShowArea();
}
this.sReplayData=null;
this.sReplyToUserId=null;
this.sReplyToUserName=null;
this._disablePubBtn(sParentId,false);
if(this._oOptions.fnAfterAddComment!=null){
this._oOptions.fnAfterAddComment(oNewComment,this._oOptions.oAfterAddCommentParams);
}
},
deleteComment:function(sCommentId,isMainComment){
var msg="";
if(isMainComment){
msg="你确定要删除该条评论和它的所有子评论吗？";
}else{
msg="你确定要删除该条子评论吗？";
}
var areusure=window.confirm(msg);
if(this._oOptions.fnDelComment!=null&&areusure){
this._oOptions.fnDelComment(sCommentId,this._oOptions.oDelCommentParams,isMainComment,this._postDelComment.bind(this));
}
},
_postDelComment:function(iSuccCount,sCommentId,isMainComment){
if(iSuccCount<=0)
return;
this._iTotalCommentCount-=iSuccCount;
if(!!isMainComment){
this._oOptions.iMainCommentCount--;
}
this._computePageNumber();
if(this._iCurrPageIndex>1&&this._oCommentArray.length<=1)
this._iCurrPageIndex--;
this.moveToPage(this._iCurrPageIndex,false);
dwrlog('评论删除成功','ok');
if(this._oOptions.fnAfterDelComment!=null){
this._oOptions.oAfterDelCommentParams.iSuccCount=iSuccCount;
this._oOptions.fnAfterDelComment(this._oOptions.oAfterDelCommentParams);
}
},
_clearReply:function(){
this.sReplyToUsername="";
this.sReplyToUserId="";
this._mainComId="-1";
this._replyComId="-1";
this._replyToUserName="";
this._replyToUserNick="";
},
_saveCommentPublish:function(){
this._clearReply();
var _comDiv=$("bcomPub");
if(_comDiv){
_comDiv.style.display="none";
$(this._comPubFloatElemId).appendChild(_comDiv);
}
if(this._sCurrentActDivId!=""&&$('act_'+this._sCurrentActDivId)){
$('act_'+this._sCurrentActDivId).style.display='';
$('bcomReplyDiv_'+this._sCurrentActDivId).style.display="none";
}
},
_initEditor:function(){
if(!this._bStatusNoRight){
if(this.htmleditor!=null&&typeof(this.htmleditor.hasSwitched)=='undefined'){
var _oHtmlEditor=$("designEditor"+this._sParentId);
if(_oHtmlEditor!=null){
var _iWidth=$("designEditorDiv"+this._sParentId).offsetWidth;
if(_iWidth>0){
_oHtmlEditor.style.width=_iWidth+"px";
}
}
}else{
var _oPlainEditor=$("plainEditor"+this._sParentId);
if(_oPlainEditor!=null){
var _iWidth=$("plainDiv"+this._sParentId).offsetWidth;
if(_iWidth>4){
_oPlainEditor.style.width=(_iWidth-4)+"px";
}
}
}
}
},
_initEditorFloat:function(){
if(!this._bStatusNoRight){
if(this.htmleditorfloat!=null){
var _oHtmlEditor=$("designEditor"+this._sParentId+"_float");
if(_oHtmlEditor!=null){
var _designDiv=$("designEditorDiv"+this._sParentId+"_float");
var _iWidth=_designDiv.offsetWidth;
if(_iWidth>0){
_oHtmlEditor.style.width=_iWidth+"px";
}
}
}else{
var _oPlainEditor=$("plainEditor"+this._sParentId+"_float");
if(_oPlainEditor!=null){
var _iWidth=$("plainDiv"+this._sParentId+"_float").offsetWidth;
if(_iWidth>4){
_oPlainEditor.style.width=(_iWidth-4)+"px";
}
}
}
}
},
_refreshEditor:function(){
if(!this._bStatusNoRight){
var isDesignEditor=$("designEditor"+this._sParentId);
if(this.htmleditor!=null&&isDesignEditor){
var _oHtmlEditor=isDesignEditor;
if(_oHtmlEditor!=null){
_oHtmlEditor.style.width=0+"px";
$("editorWrap"+this._sParentId).style.width=0+"px";
var _iWidth=$("edt"+this._sParentId).offsetWidth;
if(_iWidth>0){
_oHtmlEditor.style.width=(_iWidth-2)+"px";
$("editorWrap"+this._sParentId).style.width=(_iWidth-3)+"px";
}
}
}else{
var _oPlainEditor=$("plainEditor"+this._sParentId);
if(_oPlainEditor!=null){
_oPlainEditor.style.width=0+"px";
var _iWidth=$("plainDiv"+this._sParentId).offsetWidth;
if(_iWidth>4){
_oPlainEditor.style.width=(_iWidth-4)+"px";
}
}
}
}
},
_getLastIPPart:function(sIP){
var _iIndex=sIP.lastIndexOf('.');
if(_iIndex>0)
return sIP.substr(_iIndex+1);
else
return"";
},
_isFloatParentId:function(sParentId){
if(sParentId==0||sParentId.indexOf("_float")==-1){
return false;
}
return true;
},
_showValidCodeImg:function(sParentId){
var _oPlaineditor=this.htmleditor.editor;
if(this._isFloatParentId(sParentId)){
_oPlaineditor=this.htmleditorfloat.designEditor;
}
if(_oPlaineditor!=null){
if(isIE){
_oPlaineditor.attachEvent("onfocus",function(){
this._genValidCodeImg(sParentId,true);
if(!this._isFloatParentId(sParentId)){
this._saveCommentPublish();
}
}.bind(this));
}else{
_oPlaineditor.addEventListener("focus",function(){
this._genValidCodeImg(sParentId,true);
if(!this._isFloatParentId(sParentId)){
this._saveCommentPublish();
}
}.bind(this),false);
}
}
},
_genValidCodeImg:function(sParentId,bForce){
var _oCodeDiv=$("validCode"+sParentId);
if(bForce){
if(_oCodeDiv!=null&&_oCodeDiv.innerHTML==""){
_oCodeDiv.innerHTML=
'<label for="txtVC">验证码:&nbsp;</label><input type="text" class="bd01 g_f_focus g_c_input valid-input" value="" style="width:50px;" maxlength="4" id="valcode'+sParentId+'" />'+
'<img class="g_t_middle" style="margin-left:5px;" id="captchaimg${parentId}" alt="验证码" src="'+this._getCaptchaImgSrc(sParentId)+'" />';
_oCodeDiv.style.display="block";
}
}else{
if(_oCodeDiv!=null){
_oCodeDiv.innerHTML=
'<label for="txtVC">验证码:&nbsp;</label><input type="text" class="bd01 g_f_focus g_c_input valid-input" value="" style="width:50px;" maxlength="4" id="valcode'+sParentId+'" />'+
'<img class="g_t_middle" style="margin-left:5px;" id="captchaimg${parentId}" alt="验证码" src="'+this._getCaptchaImgSrc(sParentId)+'" />';
_oCodeDiv.style.display="block";
}
}
},
hideValidCodeImg:function(sParentId){
var _oCodeDiv=$("validCode"+sParentId);
if(_oCodeDiv!=null&&_oCodeDiv.innerHTML!=""){
_oCodeDiv.innerHTML="";
_oCodeDiv.style.display="none";
}
},
_getCaptchaImgSrc:function(sParentId){
var temp=sParentId;
if(this._isFloatParentId(temp)){
temp=temp.substring(0,temp.length-6);
}
var _iRandom=Math.floor(Math.random()*10001);
var _sId=(_iRandom+"_"+new Date().getTime()).toString();
var preUrl="/cap/captcha.jpgx?parentId=";
if(typeof window._$_is_in_album!='undefined'&&typeof UD!='undefined'&&UD.migStat==3){
preUrl="http://photo.163.com/photo/cap/captcha.jpgx?parentId=";
}
return preUrl+encodeURIComponent(sParentId)+"&"+_sId;
},
reply:function(sComId,bLogin,sName,vPara,sReplyToUserId,sReplyToUserName,mainComId){
this.sReplyToUserId=sReplyToUserId;
this.sReplyToUserName=sReplyToUserName;
if(mainComId<0){
this._mainComId=sComId;
}else
{
this._mainComId=mainComId;
}
this._replyComId=sComId;
this._replyToUserName=sReplyToUserName;
this._replyToUserNick=sName;
if(this.htmleditorfloat==null&&$('bcomPub')){
Element.remove('bcomPub');
}
if(this.htmleditorfloat==null||!$('bcomPub')){
this._setCommentPubFloatArea();
this.htmleditorfloat=this._createAdvanceEditorFloat();
}
if($("$_replyToUserNick")){
$("$_replyToUserNick").innerHTML='&nbsp;'+sName.escapeHTML();
}
if(UD.visitorRank<0){
this._genValidCodeImg(this._sParentId+"_float",true);
}
$('bcomReplyDiv_'+sComId).appendChild($('bcomPub'));
$('bcomPub').style.display='';
if(this._sCurrentActDivId){
$('act_'+this._sCurrentActDivId)&&($('act_'+this._sCurrentActDivId).style.display='');
$('bcomReplyDiv_'+this._sCurrentActDivId)&&($('bcomReplyDiv_'+this._sCurrentActDivId).style.display='none');
}
this._sCurrentActDivId=sComId;
$('act_'+this._sCurrentActDivId).style.display='none';
$('bcomReplyDiv_'+this._sCurrentActDivId).style.display='';
if(this.htmleditorfloat){
if(this.htmleditorfloat.oFrameBody){
this.htmleditorfloat.emptyContent();
}
}
},
_afterLoadAdvanceEditor:function(oParams){
var _emotion=$("_emotionDiv_"+this._sParentId);
if(_emotion&&$("PortraitBtn_s"+this._sParentId)){
_emotion.appendChild($("PortraitBtn_s"+this._sParentId));
_emotion.style.display="inline";
}
},
_afterLoadAdvanceEditorFloat:function(oParams){
var _emotionF=$("_emotionFloatDiv_"+this._sParentId+"_float");
if(_emotionF&&$("PortraitBtn_s"+this._sParentId+"_float")){
_emotionF.appendChild($("PortraitBtn_s"+this._sParentId+"_float"));
_emotionF.style.display="inline";
}
},
_createAdvanceEditor:function(_afterLoadAdvanceEditor){
var _bFriend=false;
if(UD.visitorRank>=Const.Rank.Friend)
_bFriend=true;
this.htmleditor=new NECtrl.AdvancedEditor(this._sParentId,"edt"+this._sParentId,
{sEditorSrc:"/blank.html",iWidth:this._oOptions.iEditorWidth,iHeight:this._oOptions.iEditorHeight,iMaxLen:this._oOptions.iEditorMaxLen,bSimpleEditor:true,bFriend:_bFriend,
sObjName:this._oOptions.sObjName+".htmleditor",fnAfterLoad:this._afterLoadAdvanceEditor.bind(this),bNewCommentEditor:true,fnOnCommentFocus:this._fnOnCommentFocus.bind(this)});
this._initEditor();
return this.htmleditor;
},
_createAdvanceEditorFloat:function(){
var _bFriend=false;
if(UD.visitorRank>=Const.Rank.Friend)
_bFriend=true;
this.htmleditorfloat=new NECtrl.AdvancedEditor(this._sParentId+"_float","edt"+this._sParentId+"_float",
{sEditorSrc:"/blank.html",iWidth:444,iHeight:90,iMaxLen:this._oOptions.iEditorMaxLen,bSimpleEditor:true,bFriend:_bFriend,
sObjName:this._oOptions.sObjName+".htmleditorfloat",fnAfterLoad:this._afterLoadAdvanceEditorFloat.bind(this),oAfterLoadParams:{"parentId":this._sParentId},bNewCommentEditor:true});
return this.htmleditorfloat;
},
_fnOnCommentFocus:function(){
if(UD.visitorRank<0){
this._genValidCodeImg(this._sParentId,true);
}
if($('bcomPub')){
$('bcomPub').style.display="none";
if(this._sCurrentActDivId){
$('act_'+this._sCurrentActDivId).style.display='';
$('bcomReplyDiv_'+this._sCurrentActDivId).style.display='none';
this._sCurrentActDivId=null;
}
}
}
}
