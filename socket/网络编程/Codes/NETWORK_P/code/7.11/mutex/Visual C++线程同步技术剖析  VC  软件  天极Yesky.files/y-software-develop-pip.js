
<!--
  function google_ad_request_done(google_ads) {
    /*
     * This function is required and is used to display
     * the ads that are returned from the JavaScript
     * request. You should modify the document.write
     * commands so that the HTML they write out fits
     * with your desired ad layout.
     */
    var s = '';
    var i;

    /*
     * Verify that there are actually ads to display.
     */
    if (google_ads.length == 0) {
      return;
    }

    /*
     * If an image or Flash ad is returned, display that ad.
     * Otherwise, build a string containing all of the ads and
     * then use a document.write() command to print that string.
     */

    if (google_ads[0].type == "flash") {
      s += '<object classid="clsid:D27CDB6E-AE6D-11cf-96B8-444553540000"' +
              ' codebase="http://download.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=6,0,0,0"' +
              ' WIDTH="' + google_ad.image_width +
              '" HEIGHT="' + google_ad.image_height + '">' +
              '<PARAM NAME="movie" VALUE="' + google_ad.image_url + '">'
              '<PARAM NAME="quality" VALUE="high">'
              '<PARAM NAME="AllowScriptAccess" VALUE="never">'
              '<EMBED src="' + google_ad.image_url +
              '" WIDTH="' + google_ad.image_width +
              '" HEIGHT="' + google_ad.image_height + 
              '" TYPE="application/x-shockwave-flash"' + 
              ' AllowScriptAccess="never" ' + 
              ' PLUGINSPAGE="http://www.macromedia.com/go/getflashplayer"></EMBED></OBJECT>';

    } else if (google_ads[0].type == "image") {
      s += '<a href="' + google_ads[0].url +
              '" target="_top" title="go to ' + google_ads[0].visible_url +
              '"><img border="0" src="' + google_ads[0].image_url +
              '"width="' + google_ads[0].image_width +
              '"height="' + google_ads[0].image_height + '"></a>';

    } else {
      s += '<div align=left style="text-align:left;font-weight:bold;font-size:10pt">Google提供的广告</div><br>';
      if (google_ads.length == 1) {
        /*
         * Partners should adjust text sizes
         * so ads occupy the majority of ad space.
         */
        s += '<br><a href="' + google_ads[0].url + '" ' +
                          'onmouseout="window.status=\'\'" ' +
                          'onmouseover="window.status=\'go to ' +
                          google_ads[0].visible_url + '\'" ' +
                          'style="text-decoration:none">' +
                          '<span style="text-decoration:underline;font-size:20pt">' +
                          '<b>' + google_ads[0].line1 + '</b><br></span>' + 
                          '<span style="color:#000000;font-size:16pt">' +
                          google_ads[0].line2 + '&nbsp;' +
                          google_ads[0].line3 + '<br></span>' +
                          '<span style="color:#008000;font-size:14pt">' +
                          google_ads[0].visible_url + '</span></a>';
      } else if (google_ads.length > 1) {
        /*
         * For text ads, append each ad to the string.
         */

        for(i=0; i < google_ads.length; ++i) {
          s += '<a href="' + google_ads[i].url + '" ' +
                            'onmouseout="window.status=\'\'" ' +
                            'onmouseover="window.status=\'go to ' +
                            google_ads[i].visible_url + '\'" ' +
                            'style="text-decoration:none">' +
                            '<span align=left style="text-decoration:underline">' +
                            '<b>' + google_ads[i].line1 + '</b><br></span>' + 
                            '<span style="color:#000000">' +
                            google_ads[i].line2 + '<br>' +
                            google_ads[i].line3 + '<br></span>' +
                            '<span align=left style="color:#008000">' +
                            google_ads[i].visible_url + '</span></a><br><br>';
        }

        
      }
    }
    document.write("<div style='text-align:left'>");
    document.write(s);
    document.write("</div>");
    return;
  }

     google_ad_client = 'ca-chinabyte_js'; // substitute your client_id
     google_ad_channel = 'data';
     google_ad_output = 'js';
     google_max_num_ads = '3';
     google_language = 'zh-CN';
     google_encoding = 'gb';
     google_gl = 'CN';
     google_safe = 'high';
 

  // -->

document.write("<script language=JavaScript src=http:\/\/pagead2.googlesyndication.com\/pagead\/show_ads.js><\/script> ");
  // -->








<!--Adsunion AD Code Begin Here. AD Place:pl-20-pip-software-->
document.write(navigator.userAgent.indexOf('MSIE')==-1?"<SCRIPT src='http://219.239.88.50:80/adsunion/get/;pl=pl-20-pip-software;tp=js;sk=0;ck=0;/?'><\/SCRIPT>":"<IFRAME MARGINHEIGHT=0 MARGINWIDTH=0 FRAMEBORDER=0 BORDER=0 VSPACE=0 WIDTH=1 NORESIZE HEIGHT=1 SCROLLING=NO SRC='http://219.239.88.50:80/adsunion/get/;pl=pl-20-pip-software;tp=if;sk=0;ck=0;/?'></IFRAME>");
<!--Adsunion AD Code End Here. AD Place:pl-20-pip-software-->
