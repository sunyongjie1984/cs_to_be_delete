function showDay(dt,lk,dm) {

    dt=dt+",";
    d = new Date();
    if (strDatesHasPost.indexOf(dt)!=-1) {
        if (dm != d.getDate())
            return "<div class=calendar_posttext><a href=archive."+lk+".html><font class=calendar_daytext>"+dm+"</font></a></div>";
        else {
            if (dm>d.getDate())
                return "<span class=calendar_grid>"+dm+"</span>";
            else
                return "<div class=calendar_today><a href=archive."+lk+".html><font class=calendar_daytext>"+dm+"</font></a></div>";
        }
    } else {
        if (dm == d.getDate())
            return "<div class=calendar_today>"+dm+"</span>";
        else
            return "<span class=calendar_grid>"+dm+"</span>";
    }
}


function showCalendar(argYear, argMonth) {

    currentDate = new Date();
    if (argYear == 0)
        argYear = currentDate.getFullYear();
    argMonth--;
    if (argMonth == -1)
        argMonth = currentDate.getMonth();

    var arrMonthDayNo   = new Array(31,28,31,30,31,30,31,31,30,31,30,31);
    var arrMonthDayName = new Array("一月","二月","三月","四月","五月","六月","七月","八月","九月","十月","十一月","十二月");
    strMonth = arrMonthDayName[argMonth];

    if (argMonth == 1) {
        if ((argYear%400 == 0) || ((argYear%4==0) && (argYear%100 !=0)))
            arrMonthDayNo[1]=29;
        else
            arrMonthDayNo[1]=28;
    }

    calendar_body =

        "<table width=100% border=\"0\" cellspacing=\"1\" cellpadding=2 class=calendar_main id=calendar_main>" +

        "<tr><td colspan=7 class=calendar_title>" +
        "<table width=100% cellspacing=\"0\" cellpadding=\"0\">" +
        "<tr><td align=\"center\" class=calendar_grid><font class=calendar_title>"+argYear+" "+strMonth+"</font></td></tr></table>" +
        "</td></tr>" +

        "<tr class=calendar_grid>" +
        "<td align=\"center\" class=calendar_dayname>日</td>" +
        "<td align=\"center\" class=calendar_dayname>一</td>" +
        "<td align=\"center\" class=calendar_dayname>二</td>" +
        "<td align=\"center\" class=calendar_dayname>三</td>" +
        "<td align=\"center\" class=calendar_dayname>四</td>" +
        "<td align=\"center\" class=calendar_dayname>五</td>" +
        "<td align=\"center\" class=calendar_dayname>六</td></tr>";

    calendar_body += "<tr>";

    currentDate.setFullYear(argYear, argMonth, 1);
    FirstDay=currentDate.getDay();

    CalendarRowMax = 42;
    for (i = 0; i < CalendarRowMax; i++) {

        calendar_body += "<td class=calendar_daybg><center>";

        if (FirstDay<=i && i<FirstDay+arrMonthDayNo[argMonth]) {
            cs = i - FirstDay + 1;
            currentDate = (argYear + "-" + parseInt(argMonth + 1) + "-" + cs).toString();
            dateLink = (argYear + "," + parseInt(argMonth + 1) + "," + cs).toString();
            calendar_body += showDay(currentDate, dateLink, cs);
        }
        calendar_body += "</center></td>";
        if ((i+1) % 7 ==0){
            if(i >= FirstDay + arrMonthDayNo[argMonth]-1)
                break;
            else
                calendar_body += "</tr><tr id=CalendarRow>";
        }
    }

    calendar_body += "</tr>";

    calendar_body += "<tr><td colspan=7 class=calendar_daybg><table width=100% cellspacing=\"0\" cellpadding=\"0\"><tr><td align=\"center\" class=calendar_grid><a href=archive.html>浏览全部网志</a></td></tr></table></td></tr>";

    try
    {
        if (iUId > 0) {
            calendar_body += "<tr><td colspan=7 class=calendar_daybg><table width=100% cellspacing=\"0\" cellpadding=\"0\"><tr><td align=\"center\" class=calendar_grid><a href=\"http://www.ycool.com/space.php?uid="+iUId+"\"><strong>个人主页</strong></a></td></tr></table></td></tr>";
        }
    }
    catch (e)
    {
    }

    calendar_body += "</table>";

    document.getElementById("calendar_container").innerHTML = calendar_body;
}
