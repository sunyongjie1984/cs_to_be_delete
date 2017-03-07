var t_DialogX = 0;
var t_DialogY = 0;
var t_DialogW = 0;
var t_DialogH = 0;
	
function centralizedPopup(url, w, h) {

	if (window.innerWidth) {
		var ww = window.innerWidth;
		var wh = window.innerHeight;
		var bgX = window.pageXOffset;
		var bgY = window.pageYOffset;
	} else {
		var ww = document.documentElement.offsetWidth;
		var wh = document.documentElement.offsetHeight;
		var bgX = document.documentElement.scrollLeft;
		var bgY = document.documentElement.scrollTop;
	}
	x = (bgX + ((ww - w)/2));
	y = (bgY + ((wh - h)/2));

	popup_window = window.open(url, '', 'width='+w+',height='+h);
//	popup_window.moveTo(x, y);
//	Google Toolbar will block any popups using moveTo method
}

function popupEditInterest(subject_id) {

	centralizedPopup('/subject/'+subject_id+'/?edit_interest&popup=1', 460, 345);
}

function popupEditInterestEnableRate() {

	document.getElementById("popupEditInterestRate").style.display = "block";
	document.getElementById("popupEditInterestRateLabel").style.display = "block";
}

function popupEditInterestDisableRate() {

	document.getElementById("popupEditInterestRate").style.display = "none";
	document.getElementById("popupEditInterestRateLabel").style.display = "none";
}

function popupSubjectResource(subject_id, subject_resource_id, t_type) {

	if (t_type == 2) {
		centralizedPopup('/subject_resource_playback.php?subject_id='+subject_id+'&subject_resource_id='+subject_resource_id+'&t_type='+t_type, 480, 250);
	}
}
