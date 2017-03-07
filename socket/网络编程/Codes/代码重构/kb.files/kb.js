function ConfirmAction(msg,url){
	if (confirm(msg)) {
	location.href=url;}
}

function openPopup(url) {
	myPopup = window.open(url,'Popup','width=390,height=300,top=10,left=10,resizable=yes,scrollbars=yes,toolbars=no,statusbar=yes,titlebar=no');
	//if (!myPopup.opener)
	//myPopup.opener = self;
	myPopup.focus();
}

function submitform(action){
	document.myform.action="kb.asp?"+action;
	document.myform.submit();
}

function CheckAll(){
	for (var i=0;i<document.myform.elements.length;i++) {
	var e=document.myform.elements[i];
	if (e.name !='allbox'){e.checked=document.myform.allbox.checked;}
	}
}

function Confirm() {
if(!confirm("Delete this category and all related articles?")){return false;}
}

function ConfirmDel(){
for (var f, n=0, DL=document.myform, i=0; i<DL.elements.length; i++) {if ((DL.elements[i].name.indexOf('ID')> -1)) {if (DL.elements[i].checked){n=n+1; }}}
if (n>0) {
	if(confirm("Are you sure you want to delete all selected articles?")){
	document.myform.action="admin.asp?a=del";
	document.myform.submit();}
	}
else {
	alert("Please select at least one article!")
}}

function ConfirmArchive() {
for (var f, n=0, DL=document.myform, i=0; i<DL.elements.length; i++) {if ((DL.elements[i].name.indexOf('ID')> -1)) {if (DL.elements[i].checked){n=n+1; }}}
if (n>0) {
	if(confirm("Are you sure you want to archive all selected articles?")){
	document.myform.action="admin.asp?a=archive";
	document.myform.submit();}
	}
else {
	alert("Please select at least one article!")
}}

function CheckAll(){
	for (var i=0;i<document.myform.elements.length;i++) {
	var e=document.myform.elements[i];
	if (e.name !='allbox' && e.name !='OnlyTitles' ){e.checked=document.myform.allbox.checked;}
	}
}