var focus_width=319
var focus_height=229
var text_height=25
var swf_height = focus_height+text_height+text_height
var pics='swfimg/yh_ative.jpg|swfimg/101_block.jpg|swfimg/102.jpg|swfimg/yiyue.jpg|swfimg/hacker_study.jpg|swfimg/safe_tools.jpg';

var links='http://www.chkh.com/sdpxx/20685.html|http://vip.enet.org.cn/Article/HTML/8.html|http://vip.enet.org.cn/Article/HTML/10.html|/sdpxx/20685.html|/subjcet/hacker_study.asp|/classicsoft/';

var texts='C语言网络安全编程|Snort入侵检测系统配置与应用|实地强化就业班|黑客基础知识|网络安全工具100强'

document.write('<object classid="clsid:d27cdb6e-ae6d-11cf-96b8-444553540000" codebase="http://fpdownload.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=6,0,0,0" width="'+ focus_width +'" height="'+ swf_height +'">');

document.write('<param name="allowScriptAccess" value="sameDomain"><param name="movie" value="./swf/slider.swf"><param name=wmode value=transparent><param name="quality" value="high">');

document.write('<param name="menu" value="false"><param name=wmode value="opaque">');

document.write('<param name="FlashVars" value="pics='+pics+'&links='+links+'&texts='+texts+'&borderwidth='+focus_width+'&borderheight='+focus_height+'&textheight='+text_height+'">');

document.write('<embed src="./swf/slider.swf" wmode="opaque" FlashVars="pics='+pics+'&links='+links+'&texts='+texts+'&borderwidth='+focus_width+'&borderheight='+focus_height+'&textheight='+text_height+'" menu="false" bgcolor="#DADADA" quality="high" width="'+ focus_width +'" height="'+ swf_height +'" allowScriptAccess="sameDomain" type="application/x-shockwave-flash" pluginspage="http://www.macromedia.com/go/getflashplayer" />');  
document.write('</object>');	

document.write('<embed src="ad.swf" width="635" height="210" quality="high" pluginspage="http://www.macromedia.com/go/getflashplayer" type="application/x-shockwave-flash" wmode="transparent"></embed>');