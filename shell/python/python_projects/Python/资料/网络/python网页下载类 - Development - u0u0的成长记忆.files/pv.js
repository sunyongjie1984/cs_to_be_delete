document.write('<div style="display:none"><img id="pv_img" width="1" height="1" /></div>');
var PvTrack = function(){

    this.p1 = 0;
    this.p2 = 0;
    this.p3 = 0;
    this.p4 = 0;
    this.type = 0;
    this.pageType = 0;
    this.channel = 0;
    this.page = "http://stat.it168.com/count.ashx";
    this.referrer = "";
    this.location = "";

   
    var ref = document.referrer;
    var loc = document.location.href;
    var ver = "2.0";
    var now = new Date();
    var tzone = Math.round(now.getTimezoneOffset() / -60);
    var url = "";
    var exp = " expires=Fri, 1 Jan 2038 00:00:00 GMT;";
    var domain = " domain=it168.com;";
    var path = " path=/;"
    
    var cooEna = navigator.cookieEnabled?1:0;
    var javaEna = navigator.javaEnabled()?1:0;
    
    var lang = "";
    if (navigator.language){
        lang = navigator.language.toLowerCase();
    }
    else if (navigator.browserLanguage){
        lang = navigator.browserLanguage.toLowerCase();
    }
    
    var last = "";
  
    if (cooEna == 1){
        last = getCoo("pv_last");
    }
 
    this.track = function(){

        if (!isVS()) 
	        return;

        this.location = fix(this.location);
        this.referrer = fix(this.referrer);

        url += this.page + "?v=" + ver;  
        c("p1", this.p1);
        c("p2", this.p2);
        c("p3", this.p3);
        c("p4", this.p4);
        c("t", this.type);
        c("pt", this.pageType);
        c("cl", this.channel);
        c("b", last);
        c("c", tzone);
        c("d", lang);
        c("e", 0);
        c("f", cooEna);
        c("g", javaEna);
        c("h", flashVer());
        c("i", encodeURIComponent((this.referrer)?this.referrer:ref));
        c("k", encodeURIComponent((this.location)?this.location:loc));
        c("r", (new Date()).getTime().toString(16));
            
        document.getElementById("pv_img").src = url;   
    }
    
    function fix(s){
        s = s + "";
        if (s == "undefined")
        	s = "";  
        return s; 		
    }
    
    function c(n, v){
		url+="&"+n+"="+v;
	}
    
    function flashVer(){
        var f = "-", n = navigator;
        if (n.plugins && n.plugins.length){
            for (var i = 0;i < n.plugins.length;i++){
                if (n.plugins[i].name.indexOf('Shockwave Flash') != -1){
                    f = n.plugins[i].description.split('Shockwave Flash ')[1];
                    break;
                }
            }
        }
        else if (window.ActiveXObject){
            for (var i = 10;i >= 2;i--){
                try{
                    var fl = eval("new ActiveXObject('ShockwaveFlash.ShockwaveFlash." + i + "');");
                    if (fl){
                        f = i + '.0';
                        break;
                    }
                }
                catch (e)
                {}
            }
        }
        return f;
    }

    function getCoo(n){
        var v = '';
        var pe;
        var ps = document.cookie.indexOf(n);
        if (ps != -1){
            ps += n.length + 1 ;
            pe = document.cookie.indexOf(";", ps);
            if (pe == -1){
                pe = document.cookie.length;
            }
            v = unescape(document.cookie.substring(ps, pe));
        }
        return v;
    }
    
    function setCoo(n, v){
        document.cookie = n + "=" + escape(v) + ";" + domain + exp + path;
    }
    
    function isVS(){
        var w,h;
        if (document.body){
            w = document.body.clientWidth | document.documentElement.clientWidth;
            h = document.body.clientHeight | document.documentElement.clientHeight;
        }else{
            w = document.documentElement.clientWidth;
            h = document.documentElement.clientHeight;    
        }
    
        if (w > 300 && h > 300)
            return true;
    
        return false;
    }
}