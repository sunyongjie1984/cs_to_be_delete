// $Id: doubleclick_ads.js 25464 2010-03-22 18:34:34Z bbuckman $

// Doubleclick ad support

// a comment to test caching

// make sure global namespace exists
OPG = window.OPG || {};

// Doubleclick namespace
OPG.Doubleclick = OPG.Doubleclick || {};

// is this an article page? (use standard var for cross-compat)
// doubleclick_article_page can be set to true before or after this file
if (typeof(window.doubleclick_article_page)=='undefined') window.doubleclick_article_page = false;


OPG.Doubleclick = function() {

  // PUBLIC
  return {
    
    extraAdKeys: Array(),   // filled w/ demandbase, etc as needed
    
    ord: Math.random()*10000000000000000,     // random # for ads, client-side to avoid caching
    
    // get any referrer
    referrerValue: function() {
       var domain = "";
       var referrer = document.referrer;

       if (referrer == "") return "";
       if (referrer.indexOf("http://www.google.com/cse") > -1) return ""; // custom search - exception

       rPieces = referrer.split("/");
       dPieces = rPieces[2].split(".");

       if(dPieces.length >= 2) {
         domain = dPieces[dPieces.length-2];
         //return "referrer=" + domain;
         return domain;
       }
       return "";
    },
    
    
    // add one-time conditional keys
    extraKeysAdded: false,
    
    addExtraKeys: function() {
      try {
        if (OPG.Doubleclick.extraKeysAdded==true) return;   // only once
        OPG.Doubleclick.extraKeysAdded = true;

        // get referrer separately (otherwise adds every time)
        // but only on article pages
        if (window.doubleclick_article_page == true) {
          OPG.Doubleclick.extraAdKeys[OPG.Doubleclick.extraAdKeys.length] = "referrer=" + OPG.Doubleclick.referrerValue();
        }

      } catch(e) {
        OPG.Doubleclick.extraAdKeys[OPG.Doubleclick.extraAdKeys.length] = "ERROR=addExtraKeys";   // so it's noticed
        //console.log(e);
      }
    },
    
    
    processAdUrl: function(url) {
      // console.log("processing ad url ["+url+"]");

      // add extra keys (runs once)
      OPG.Doubleclick.addExtraKeys();

      // add ad keys
      var adKeys = OPG.Doubleclick.extraAdKeys.join(';');
      if (adKeys != '') {
        if (url.charAt(url.length-1) != ";") url = url + ";"; // separator
        url = url + adKeys;
      }

      // add 'ord' if not already
      if (url.indexOf("ord=") == -1) {
        if (url.charAt(url.length-1) != ";") url = url + ";"; // separator
        url = url + "ord="+ OPG.Doubleclick.ord +"?";
      }
      // console.log("modified ad url ["+url+"]");
      return url;
    },
    
    
    processReferer: function(url) {    // legacy (remove?)
      return OPG.Doubleclick.processAdUrl(url); 
    }
    
    
  };
}();



// for legacy (set by demandbase callback)
window._rval = '';
window.rval = '';   // always set both together

// random # for ads, client-side to avoid caching
window.ord = OPG.Doubleclick.ord;


// for legacy/transition
window.processAdUrl = function(url) {
  return OPG.Doubleclick.processAdUrl(url);
};
