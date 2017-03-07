/********
 * 如果主题风格需要作些处理, 例如添加图片链接, 请在这里添加代码
 */
if (NEPlatform == undefined)
	var NEPlatform = {};
if (NEPlatform.FixedTheme == undefined)
	NEPlatform.FixedTheme = {};
if (NEPlatform.FixedTheme.Initializer == undefined)
	NEPlatform.FixedTheme.Initializer = {};	
if (NEPlatform.FixedTheme.Util == undefined)
	NEPlatform.FixedTheme.Util = {};
 
 /*****
  * @param themeId
  */
var _$$_initFixedTheme = function(themeId){
	/*if(typeof themeId == 'undefined' || themeId == null || themeId < 0){
		return;
	}*/
	/*switch(themeId){
		case 4275: NEPlatform.FixedTheme.Initializer.init4275(); break;
	}*/
};

/******
 * all util functions
 */
NEPlatform.FixedTheme.Util = {	
	/*******
	 * add the link onto the page
	 */
	addLink: function(_left, _top, _width, _height, _link, _parentObjId){
		var _$$_parent_div = document.getElementById(_parentObjId);
		if(_$$_parent_div != null){
			var d = document.createElement("div"); 
			_$$_parent_div.appendChild(d); 
			d.style.border= "0px"; 
			d.style.width= _width + "px"; 
			d.style.height= _height + "px"; 
			d.style.position = "absolute";
			d.style.left= _left + "px";
			d.style.top= _top + "px";
			d.style.cursor = "pointer";
			d.onclick = function(){window.open(_link)};
		}
	}
}; 

/******
 * all fixed theme Initializer
 */
NEPlatform.FixedTheme.Initializer = {	
	/*init4275: function(){
		NEPlatform.FixedTheme.Util.addLink(400, 70, 200, 100, "http://www.163.com", "_$$_Top_Inner");
	}*/
}

