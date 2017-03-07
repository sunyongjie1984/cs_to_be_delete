// FTPClient.cpp: implementation of the CFTPClient class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SFTP.h"
#include "FTPClient.h"
#include "sftpdoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define SAFEDELTE(x) if(x!=NULL){delete x;x = NULL;}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFTPClient::CFTPClient(CSFTPDoc *pDoc)
{
	m_pCtrlRxarch = NULL;
	m_pCtrlTxarch = NULL;
	m_pCtrlsokfile = NULL;
	m_Ctrlsok = NULL;
	m_pDoc = pDoc;
}

CFTPClient::~CFTPClient()
{
	SAFEDELTE(m_pCtrlRxarch);
	SAFEDELTE(m_pCtrlTxarch);
	SAFEDELTE(m_pCtrlsokfile);
	SAFEDELTE(m_Ctrlsok);
}

void CFTPClient::Receive()
{

}

BOOL CFTPClient::Logon(CString hostname, int hostport, CString username, CString password, CString acct, CString fwhost, CString fwusername, CString fwpassword, int fwport, int logontype)
{
	if(m_dlgMsg.m_hWnd == NULL){
		m_dlgMsg.Create(AfxGetMainWnd());
	}
	else
		m_dlgMsg.ShowWindow(SW_SHOW);
	int port,logonpoint=0;
	const int LO=-2, ER=-1;
	CString buf,temp;
	const int NUMLOGIN=9; // currently supports 9 different login sequences
	int logonseq[NUMLOGIN][100] = {
		// this array stores all of the logon sequences for the various firewalls 
		// in blocks of 3 nums. 1st num is command to send, 2nd num is next point in logon sequence array
		// if 200 series response is rec'd from server as the result of the command, 3rd num is next
		// point in logon sequence if 300 series rec'd
		{0,LO,3, 1,LO,6, 2,LO,ER},							// no firewall
		{3,6,3, 4,6,ER, 5,ER,9, 0,LO,12, 1,LO,15, 2,LO,ER}, // SITE hostname
		{3,6,3, 4,6,ER, 6,LO,9, 1,LO,12, 2,LO,ER},			// USER after logon
		{7,3,3, 0,LO,6, 1,LO,9, 2,LO,ER},					//proxy OPEN
		{3,6,3, 4,6,ER, 0,LO,9, 1,LO,12, 2,LO,ER},			// Transparent
		{6,LO,3, 1,LO,6, 2,LO,ER},							// USER with no logon
		{8,6,3, 4,6,ER, 0,LO,9, 1,LO,12, 2,LO,ER},			//USER fireID@remotehost
		{9,ER,3, 1,LO,6, 2,LO,ER},							//USER remoteID@remotehost fireID
		{10,LO,3, 11,LO,6, 2,LO,ER}							// USER remoteID@fireID@remotehost
	};

	if(logontype<0 || logontype>=NUMLOGIN) 
		return FALSE;		// illegal connect code
	// are we connecting directly to the host (logon type 0) or via a firewall? (logon type>0)
	if(!logontype) {
		temp=hostname;
		port=hostport;
	}
	else {
		temp=fwhost;
		port=fwport;
	}
	if(hostport!=21) 
		hostname.Format(hostname+":%d",hostport); // add port to hostname (only if port is not 21)
	if(!ConnectRemote(temp,port)) 
		return false;
	if(!FTPcommand("")) 
		return FALSE;		// get initial connect msg off server
	// go through appropriate logon procedure
	while(1) {
		switch(logonseq[logontype][logonpoint]) {
		case 0:
			temp="USER "+username;
			break;
		case 1:
			temp="PASS "+password;
			break;
		case 2:
			temp="ACCT "+acct;
			break;
		case 3:
			temp="USER "+fwusername;
			break;
		case 4:
			temp="PASS "+fwpassword;
			break;
		case 5:
			temp="SITE "+hostname;
			break;
		case 6:
			temp="USER "+username+"@"+hostname;
			break;
		case 7:
			temp="OPEN "+hostname;
			break;
		case 8:
			temp="USER "+fwusername+"@"+hostname;
			break;
		case 9:
			temp="USER "+username+"@"+hostname+" "+fwusername;
			break;
		case 10:
			temp="USER "+username+"@"+fwusername+"@"+hostname;
			break;
		case 11:
			temp="PASS "+password+"@"+fwpassword;
			break;
		}
		// send command, get response
		if(!WriteStr(temp))
			return FALSE;
		if(!ReadStr()) 
			return FALSE;
		// only these responses are valid
		if(m_fc!=2 && m_fc!=3) 
			return FALSE;
		logonpoint=logonseq[logontype][logonpoint+m_fc-1]; //get next command from array
		switch(logonpoint) {
		case ER: // ER means summat has gone wrong
			m_retmsg.LoadString(IDS_FTPMSG1);
			return FALSE;
		case LO: // LO means we're fully logged on
			return TRUE;
		}
	}
}

BOOL CFTPClient::ConnectRemote(CString serverhost, int serverport)
{
	SAFEDELTE(m_pCtrlRxarch);
	SAFEDELTE(m_pCtrlTxarch);
	SAFEDELTE(m_pCtrlsokfile);
	SAFEDELTE(m_Ctrlsok);
	if(m_Ctrlsok == NULL)
		m_Ctrlsok = new CFTPSocket;
	if( !(m_Ctrlsok->Create()) )
		return FALSE;
	if(!(m_Ctrlsok->Connect(serverhost,serverport))) 
		return FALSE;
	if(!(m_pCtrlsokfile=new CSocketFile(m_Ctrlsok))) 
		return FALSE;
	if(!(m_pCtrlRxarch=new CArchive(m_pCtrlsokfile,CArchive::load))) 
		return FALSE;
	if(!(m_pCtrlTxarch=new CArchive(m_pCtrlsokfile,CArchive::store)))
		return FALSE;
	return TRUE;
}

BOOL CFTPClient::WriteStr(CString outputstring)
{
	TRY {
		m_pCtrlTxarch->WriteString(outputstring+"\r\n");
		m_pCtrlTxarch->Flush();
	}
	CATCH(CException,e) {
		return FALSE;
	}
	END_CATCH
	return TRUE;
}

int CFTPClient::ReadStr()
{
	int retcode;

	if(!ReadStr2())
		return FALSE;
	if(m_retmsg.GetLength() < 4 || m_retmsg.GetAt(3) != '-') 
		return TRUE;
	retcode=atol(m_retmsg);
	while(1) { //handle multi-line server responses
		if(m_retmsg.GetLength() > 3 && (m_retmsg.GetAt(3) == ' ' && atol(m_retmsg) == retcode)) 
			return TRUE;
		if(!ReadStr2()) return FALSE;
	}
}

BOOL CFTPClient::ReadStr2()
{
	TRY {
		if(!m_pCtrlRxarch->ReadString(m_retmsg)) {
			return FALSE;
		}
	}
	CATCH(CException,e) {
		return FALSE;
	}
	END_CATCH
	if(m_retmsg.GetLength() > 0)
		m_fc = m_retmsg.GetAt(0)-48; 
	m_dlgMsg.TextOut(m_retmsg);
	// get 1st digit of the return code (indicates primary result)
	return TRUE;
}

BOOL CFTPClient::FTPcommand(CString command)
{
	if(command != "" && !WriteStr(command))
		return FALSE;
	if((!ReadStr()) || (m_fc != 2)) 
		return FALSE;
	return TRUE;
}

BOOL CFTPClient::List()
{
	CString lhost,temp,rhost;
	UINT localsock,i;
	CFile datafile;
	CSocket sockSrvr;
	CAsyncSocket datachannel;
	int num, sum;
	const int BUFSIZE = 4096;
	DWORD lpArgument=0;
	
	m_buf.RemoveAll();
	m_buf.SetSize(BUFSIZE);
	if(!FTPcommand("TYPE I")) 
		return FALSE; // request BINARY mode

	m_retmsg.LoadString(IDS_FTPMSG6);
	// get the local IP address off the control channel socket
	if(!m_Ctrlsok->GetSockName(lhost,localsock)) 
		return FALSE;;
	while(1) {
		// convert returned '.' in ip address to ','
		if((i=lhost.Find("."))==-1) break;
		lhost.SetAt(i,',');
	}
	// create listen socket (let MFC choose the port) & start the socket listening
	if((!sockSrvr.Create(0, SOCK_STREAM, NULL))
			|| (!sockSrvr.Listen()))
		return FALSE;
	if(!sockSrvr.GetSockName(temp,localsock))
		return FALSE;// get the port that MFC chose
	// convert the port number to 2 bytes + add to the local IP
	lhost.Format(lhost+",%d,%d", localsock / 256, localsock % 256);
	if(!FTPcommand("PORT "+lhost)) 
		return FALSE;// send PORT cmd to server

	if(!WriteStr("LIST") )
		return FALSE;
	if(!ReadStr())
		return FALSE; // get response to RETR/STOR command
	if(!sockSrvr.Accept(datachannel)) 
		return FALSE; // if !PASV accept inbound data connection from server
	// we're connected & ready to do the data transfer, so set blocking mode on data channel socket
	if((!datachannel.AsyncSelect(0)) || 
		(!datachannel.IOCtl(FIONBIO,&lpArgument))) {
		m_retmsg.LoadString(IDS_FTPMSG6);
		return FALSE;
	}
	sum = 0;
	while(1) { // move data from/to server
		TRY {
			if(!(num = datachannel.Receive(m_buf.GetData() + sum, BUFSIZE, 0)) 
				|| num == SOCKET_ERROR)
				break; // (EOF||network error)
			TRACE("Received :%d\n", num);
			Sleep(0);
			sum += num;
			m_buf.SetSize(sum + BUFSIZE);
		}
		CATCH (CException,e) {
			m_retmsg.LoadString(IDS_FTPMSG5);
			return FALSE;
		}
		END_CATCH
	}
	datachannel.Close();
	ProcessList();
	if(!FTPcommand("")) 
		return FALSE; // check transfer outcome msg from server
	return TRUE; // oh goody it worked.
}

void CFTPClient::ProcessList()
{
	m_pDoc->RemoveAll();
	int ndx = 0;
	while(GetLine(ndx)){
//		m_dlgMsg.TextOut(m_strLine);
		m_pDoc->AddLine(m_strLine);
	}
}

BOOL CFTPClient::GetLine(int& ndx)
{
	m_strLine.Empty();
	int nBytes = m_buf.GetSize();
	BOOL bLine = FALSE;
	while ( bLine == FALSE && ndx < nBytes )
	{
		char ch = (char)(m_buf.GetAt( ndx ));
		switch( ch )
		{
		case '\n': // end-of-line
			bLine = TRUE;
			break;
		default:   // other....
			m_strLine += ch;
			break;
		}
		++ndx;
	}
	m_strLine = m_strLine.Left(m_strLine.GetLength() - 1);
	return bLine;
}

BOOL CFTPClient::MoveFile(CString remotefile, CString localfile, BOOL get, BOOL pasv)
{
	CString lhost,temp,rhost;
	UINT localsock,serversock,i,j;
	CFile datafile;
	CSocket sockSrvr;
	CAsyncSocket datachannel;
	int num,numread,numsent;
	const int BUFSIZE=4096;
	char cbuf[BUFSIZE];
	DWORD lpArgument=0;
	
	// open local file
	if(!datafile.Open(localfile,(get ? CFile::modeWrite | CFile::modeCreate : CFile::modeRead))) {
		m_retmsg.LoadString(IDS_FTPMSG4);
		return FALSE;
	}
	if(!FTPcommand("TYPE I")) 
		return FALSE; // request BINARY mode
	if(pasv) { // set up a PASSIVE type file transfer
		if(!FTPcommand("PASV"))
			return FALSE;
		// extract connect port number and IP from string returned by server
		if((i=m_retmsg.Find("("))==-1 || 
			(j=m_retmsg.Find(")"))==-1)
			return FALSE;
		temp = m_retmsg.Mid(i+1,(j-i)-1);
		i=temp.ReverseFind(',');
		serversock=atol(temp.Right(temp.GetLength()-(i+1))); //get ls byte of server socket
		temp=temp.Left(i);
		i=temp.ReverseFind(',');
		serversock += 256*atol(temp.Right(temp.GetLength()-(i+1))); // add ms byte to server socket
		rhost=temp.Left(i);
		while(1) { // convert commas to dots in IP
			if((i=rhost.Find(","))==-1) 
				break;
			rhost.SetAt(i,'.');
		}
	}
	else { // set up a ACTIVE type file transfer
		m_retmsg.LoadString(IDS_FTPMSG6);
		// get the local IP address off the control channel socket
		if(!m_Ctrlsok->GetSockName(lhost,localsock))
			return FALSE;;
		while(1) { // convert returned '.' in ip address to ','
			if((i=lhost.Find("."))==-1)
				break;
			lhost.SetAt(i,',');
		}
		// create listen socket (let MFC choose the port) & start the socket listening
		if((!sockSrvr.Create(0,SOCK_STREAM,NULL)) || 
			(!sockSrvr.Listen()))
			return FALSE;
		if(!sockSrvr.GetSockName(temp,localsock)) 
			return FALSE;// get the port that MFC chose
		// convert the port number to 2 bytes + add to the local IP
		lhost.Format(lhost+",%d,%d",localsock/256,localsock%256);
		if(!FTPcommand("PORT "+lhost))
			return FALSE;// send PORT cmd to server
	}
	// send RETR/STOR command to server
	if(!WriteStr(( get ? "RETR " : "STOR ") + remotefile)) 
		return FALSE;
	if(pasv) {// if PASV create the socket & initiate outbound data channel connection
		if(!datachannel.Create()) {
			m_retmsg.LoadString(IDS_FTPMSG6);
			return FALSE;
		}
		datachannel.Connect(rhost,serversock); // attempt to connect asynchronously (server will tell us if/when we're connected)
	}
	if(!ReadStr() || m_fc!=1) 
		return FALSE; // get response to RETR/STOR command
	if(!pasv&&!sockSrvr.Accept(datachannel)) 
		return FALSE; // if !PASV accept inbound data connection from server
	// we're connected & ready to do the data transfer, so set blocking mode on data channel socket
	if((!datachannel.AsyncSelect(0))
		|| (!datachannel.IOCtl(FIONBIO,&lpArgument))) {
		m_retmsg.LoadString(IDS_FTPMSG6);
		return FALSE;
	}
	while(1) { // move data from/to server & read/write local file
		TRY {
			if(get) {
				if(!(num=datachannel.Receive(cbuf,BUFSIZE,0)) 
					|| num==SOCKET_ERROR) 
					break; // (EOF||network error)
				else 
					datafile.Write(cbuf,num);
			}
			else {
				if(!(numread=datafile.Read(cbuf,BUFSIZE)))
					break; //EOF
				if((numsent=datachannel.Send(cbuf,numread,0))==SOCKET_ERROR) 
					break;
				// if we sent fewer bytes than we read from file, rewind file pointer
				if(numread != numsent) 
					datafile.Seek(numsent-numread,CFile::current);
			}
		}
		CATCH (CException,e) {
			m_retmsg.LoadString(IDS_FTPMSG5);
			return FALSE;
		}
		END_CATCH
	}
	datachannel.Close();
	datafile.Close();
	if(!FTPcommand("")) 
		return FALSE; // check transfer outcome msg from server
	AfxMessageBox("文件下载成功！");
	return TRUE; // oh goody it worked.
}

CFTPClient::Disconnect()
{
	if(m_Ctrlsok != NULL){
		m_Ctrlsok->Close();
	}
	SAFEDELTE(m_pCtrlRxarch);
	SAFEDELTE(m_pCtrlTxarch);
	SAFEDELTE(m_pCtrlsokfile);
	SAFEDELTE(m_Ctrlsok);
}
