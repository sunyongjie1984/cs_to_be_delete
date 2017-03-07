
function okForXMLHTTPREQUESTandResponseXML(){
	if (global_fakeOperaXMLHttpRequestSupport) return false; // this is set in xmlhtttprequest.js
	return okForXMLHTTPREQUEST();
}

function okForXMLHTTPREQUEST(){
	if (!window.XMLHttpRequest) return false;
	if (navigator.appVersion.toLowerCase().indexOf("mac") > 0 && navigator.userAgent.indexOf('MSIE') > 0 && navigator.userAgent.indexOf('Opera') == -1) return false;
	return true;
}

function insertMarketBankerScript(divholder, div) {
	var mb_holderdiv = document.getElementById(divholder);
	var mb_scriptdiv = document.getElementById(div);
	if (!mb_scriptdiv || !mb_holderdiv) {
		return;
	}
	mb_scriptdiv.innerHTML = mb_holderdiv.innerHTML;
		
	//alert(mb_scriptdiv.innerHTML)
}


function escape_utf8(data) {

	if (data == '' || data == null){
		return '';
	}
	data = data.toString();
	var buffer = '';
	for(var i=0; i<data.length; i++){
		var c = data.charCodeAt(i);
		var bs = new Array();

		if (c > 0x10000){
			// 4 bytes
			bs[0] = 0xF0 | ((c & 0x1C0000) >>> 18);
			bs[1] = 0x80 | ((c & 0x3F000) >>> 12);
			bs[2] = 0x80 | ((c & 0xFC0) >>> 6);
			bs[3] = 0x80 | (c & 0x3F);

		}else if (c > 0x800){
			// 3 bytes
			bs[0] = 0xE0 | ((c & 0xF000) >>> 12);
			bs[1] = 0x80 | ((c & 0xFC0) >>> 6);
			bs[2] = 0x80 | (c & 0x3F);

		}else if (c > 0x80){
			// 2 bytes
			bs[0] = 0xC0 | ((c & 0x7C0) >>> 6);
			bs[1] = 0x80 | (c & 0x3F);

		}else{
			// 1 byte
			bs[0] = c;
		}

		for(var j=0; j<bs.length; j++){
			var b = bs[j];
			var hex = nibble_to_hex((b & 0xF0) >>> 4) + nibble_to_hex(b & 0x0F);
			buffer += '%'+hex;
		}
	}

	return buffer;
}

function nibble_to_hex(nibble){
	var chars = '0123456789ABCDEF';
	return chars.charAt(nibble);
}




// srcElement getter courtesy Erik Arvidsson
// http://www.webfx.nu/dhtml/ieemu/eventobject.html
if (!document.all) {
	Event.prototype.__defineGetter__("srcElement", function () {
		var node = this.target;
		while (node.nodeType != 1) node = node.parentNode;
		return node;
	});
}


// findPosX & findPosY courtesy PPK
// http://www.quirksmode.org/js/findpos.html
function findPosX(obj) {
	var curleft = 0;
	if (obj.offsetParent) {
		while (obj.offsetParent) {
			curleft += obj.offsetLeft
			obj = obj.offsetParent;
		}
	}
	else if (obj.x) curleft += obj.x;
	return curleft;
}

function findPosY(obj) {
	var curtop = 0;
	if (obj.offsetParent) {
		while (obj.offsetParent) {
			curtop += obj.offsetTop
			obj = obj.offsetParent;
		}
	}
	else if (obj.y) curtop += obj.y;
	return curtop;
}

_pi = function(str) {
	return parseInt(str);
}
_ge = function(id) {
	return document.getElementById(id);
}

function decorate() {
	var el = arguments[0];
	if (!el) return;
	arguments[0] = el;
	if (window['decorate_'+el.className]) return window['decorate_'+el.className](arguments);
}



