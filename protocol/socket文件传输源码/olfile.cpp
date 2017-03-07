                                  
/**
	Offload file transfer module using socket to test TCP offload engine(TOE).
	By Vino @ 9th, June 2004.
	Email: rtc@eyou.com
	All copyrights reserved.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#ifdef WIN32
	#include <io.h>
	#include <winsock2.h>
#else
	#include <sys/socket.h>
	#include <sys/un.h>
	#include <unistd.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
#endif
#include <time.h>

#include "olfile.h"

const char str_usg[] = 
	"\nTransfer a file from data source to data sink through network.\n\n"
	"  olfile -src sourcefile -snk sinkfile -ip dotip [-y]\n"
	"     Copy sourcefile on local to sinkfile on ip dotip.\n\n"
	"  olfile -snk sinkfile -src sourcefile -ip dotip [-y]\n"
	"     Copy sourcefile on ip dotip to sinkfile on local.\n\n"
	"  olfile -server\n"
	"     Start olfile service.\n\n"
	"Options:\n"
	"    -src + sourcefile      Data source file full path\n"
	"    -snk + sinkfile        Data sink file full path\n"
	"    -ip  + dotip           Dot divided ip address\n"
	"    -y                     Default to delete exists file.\n\n"
	"Example:\n"
	"     -snk f:/data.txt -src f:/datarcv.txt -ip 10.190.5.179 -y\n\n"
	"By Vino.Cui @ 9th, June 2004 from Inventec.\n"
	"Revision:\n"
	"1. 13th, June 2004 Completed the original version: Transfering file \nfrom data source to data sink via ip specified by -ip argument. \n";

const size_t OP_HEAD_SIZE = sizeof(struct st_op_head);
struct st_reg_sem s_reg_sem;
/** these 4 buffer pools are dynamic allocated in the program.
  file -> read-File Buffer Pool -> send-NIC Buffer Pool -> NIC
  file <- write-File Buffer Pool <- receive-NIC Buffer Pool <- NIC
but this implementation needs buffer copy(copy read-file Buffer to send-NIC Buffer pool and back-forth).
  char *rdFileBufPool, *wrFileBufPool;
  char *sendNicBufPool, *recvNicBufPool;
*/
char *lanin_buf, *lanout_buf;
char *gfin_buf, *gfout_buf;
float ftop_spd = 0.0; // top speed, bytes/s
/***/

int
init_socket()
{
#ifdef WIN32
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
	if (iResult != NO_ERROR)
	{
		printf("Error at WSAStartup()\n");
		return -1;
	}
	return 0;
#else
	return 0;
#endif
}

int
create_conn(){
	SOCKET s;
	struct sockaddr_in local;
	BOOL bOptVal = TRUE;
	int bOptLen = sizeof(BOOL);
	int iOptLen = sizeof(int);

	if((s = socket(AF_INET_NORMAL, SOCK_STREAM, 0)) == -1){
		perror("socket");
		return -1;
	}

	int a= setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (char*)&bOptVal, bOptLen);

	memset(&(local), 0, sizeof(struct sockaddr_in));

	local.sin_family = AF_INET;      /* host byte order */
	local.sin_port = htons(SERVER_PORT);
	local.sin_addr.s_addr = INADDR_ANY;
	if ( -1 == bind(s, (struct sockaddr*)&local, sizeof(struct sockaddr)) )
	{
		fprintf(stderr, "bind error\n");
		show_err();
		return (-1);
	}
	
	if ( -1 == listen(s, 5)) {
		fprintf(stderr, "Listening error.");
		show_err();
		return (-1);
	}

	return s;	
}

// create a connection with the remote peer
int open_conn(char *str_ip){
	SOCKET s;
	struct sockaddr_in local, remote;
	int ret = 0;
	BOOL bOptVal = TRUE;
	int bOptLen = sizeof(BOOL);
	int iOptLen = sizeof(int);

	if (NULL == str_ip) {
		fprintf(stderr, "No destination IP!\n");
		return (-1);
	}

	if((s = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		perror("socket");
		return -1;
	}

	int a=setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (char*)&bOptVal, bOptLen);

	memset(&(local), 0, sizeof(struct sockaddr_in));

//	local.sin_family = AF_INET;
//	local.sin_port = htons(CLIENT_PORT);
//	local.sin_addr.s_addr = INADDR_ANY;
//	if ( -1 == bind(s, (struct sockaddr*)&local, sizeof(struct sockaddr)) )
	{
//		fprintf(stderr, "bind error\n");
//		show_err();
//		return (-1);
	}


	memset(&(remote), 0, sizeof(struct sockaddr_in));
	remote.sin_family = AF_INET;
	remote.sin_port = htons(SERVER_PORT);
	remote.sin_addr.s_addr = inet_addr(str_ip);

	fprintf(stderr, "Connecting to %s\n\n", str_ip);

	int retry = 10;
	do {
		if (-1 == (ret = connect(s, (struct sockaddr *)&remote, sizeof(struct sockaddr)))) {
	#ifdef WIN32
			show_err();
	#endif
			fprintf(stderr, "Connect error. Retry %d times\r", 11-retry);
			retry--;
#ifdef WIN32
			Sleep(1000);
#else
			sleep(1);
#endif
			if (retry == 0) {
				return -1;
			}
		}
	} while( -1 == ret );

	fprintf(stderr, "\n");
	return s;
}

// close the connection with the daemon
void close_conn(int sfd){
#ifdef WIN32
	closesocket(sfd);
	WSACleanup();
	fprintf(stderr, "Connection context released.\n");
#else
	close(sfd);
#endif
}

// Give the head and the message buffer buf, 
// send the `big buffer'
// +-----------+----------------------+
// |  head     |      buffer          |
// +-----------+----------------------+
// send_ptocol_buf

// receive the head and the message buf: head, buf
// recv_ptocol_buf
// send a request with the type: 
// send_request
// receive_reply
// receive_result

// server functions:
// response to client function: send_request
// receive_request
// response to client function: receive_reply
// send_reply
// responst to client function: receive_result 
// send_result

struct st_con_arg*
parse_arg(int argc, char** argv){
	char **pargv = argv;
	size_t len;
	struct st_con_arg *s_con = new struct st_con_arg;
	int i;

	memset(s_con, 0, sizeof(struct st_con_arg));
	s_con->flag = 1; // make valid
	//	"olfile -src sourcefile -sink ip/sinkfile [-y]\n"
	if (argc < 7) {
		if (argc == 2) {
			// maybe service mode
			s_con->flag = 1;
		}
		else
		{
			s_con->flag = 0; // make valid
		}
	}

	for ( i=0, s_con->str_ip = NULL; i<argc-1 && s_con->flag!=0; i++)
	{
		pargv++;
		if (0 == memcmp(*pargv, ARG_SRV, sizeof(ARG_SRV))) {
			s_con->peer_mode = SERVER;
			continue;
		}
		else{
			if (argc == 2) {
				// only -server has 1 argument.
				s_con->flag = 0;
				continue;
			}
			s_con->peer_mode = CLIENT;
			// must not continue;
		}

		if (0 == memcmp(*pargv, ARG_SNK, sizeof(ARG_SNK))) 
		{
			if (0 < s_con->sink_addr.pathlen) {
				// the -snk has been specified, no src available
				fprintf(stderr, "No -src available.\n");
				s_con->flag = 0;
			}

			if ( DATA_SRC != s_con->con_mode) {
				s_con->con_mode = DATA_SNK;
			}
			
			pargv++; i++;
			len = strlen(*pargv);
			s_con->sink_addr.ppath = new char[len + 1];
			memcpy(s_con->sink_addr.ppath, *pargv, len);
			s_con->sink_addr.ppath[len] = 0;
			s_con->sink_addr.pathlen = len;
		}
		else if (0 == memcmp(*pargv, ARG_SRC, sizeof(ARG_SRC))) 
		{
			if (0 < s_con->src_addr.pathlen) {
				// the -snk has been specified, no src available
				fprintf(stderr, "No -snk available.\n");
				s_con->flag = 0;
			}

			if ( DATA_SNK != s_con->con_mode) {
				s_con->con_mode = DATA_SRC;
			}

			pargv++; i++;
			len = strlen(*pargv);
			s_con->src_addr.ppath = new char[len + 1];
			memcpy(s_con->src_addr.ppath, *pargv, len);
			s_con->src_addr.ppath[len] = 0;
			s_con->src_addr.pathlen = len;
		}
		else if (0 == memcmp(*pargv, ARG_IP, sizeof(ARG_IP))) 
		{
			pargv++; i++;
			len = strlen(*pargv);
			s_con->str_ip = new char[len+1];
			memcpy(s_con->str_ip, *pargv, len);
			s_con->str_ip[len] = 0;
		}
		else if (0 == memcmp(*pargv, ARG_Y, sizeof(ARG_Y))) {
			s_con->cfm_mode = OVERIDE;
		}
		else if (0 == memcmp(*pargv, ARG_MAGGIE, sizeof(ARG_MAGGIE))) {
			s_con->flag = 0;
			fprintf(stderr, "--< Hello , Maggy !>--\n");
		}
		else
		{
			s_con->flag = 0;
		}
	}

	if (s_con->sink_addr.pathlen == 0 || s_con->src_addr.pathlen == 0) {
		if (s_con->peer_mode == SERVER) {
			s_con->flag = 1;
		}
		else
		{
			s_con->flag = 0;
		}
	}

	return s_con;
}


time_t t_start; // starting time
int main(int argc, char** argv)
{
	struct st_con_arg *s_con_arg;
	unsigned int s;		// original socket fd
	int ret = 0;

	time_t t_end, t_interval;
	time_t t_hou, t_min, t_sec;

	t_start = time(&t_start);

	lanin_buf = new char [MAX_MSG_LEN + OP_HEAD_SIZE + 1];
	lanout_buf = new char [MAX_MSG_LEN + OP_HEAD_SIZE + 1];
	
	if (NULL == lanin_buf || NULL == lanout_buf) {
		fprintf(stderr, "Low memory to alloc lan buffer.\n");
		return -1;
	}
	
	gfin_buf = new char [FILE_BUF_LEN + 1];
	gfout_buf = new char [FILE_BUF_LEN + 1];
	if ( NULL == gfin_buf || NULL == gfout_buf ) {
		fprintf(stderr, "Low memory to alloc file buffer.\n");
		return -1;
	}

	s_con_arg = parse_arg(argc, argv);
	if (s_con_arg->flag == 0) {
		printf(str_usg);
		delete s_con_arg;
		return -1;
	}

	init_socket();

	if (s_con_arg->peer_mode == SERVER) {
		// entered service mode
		if (-1 == (s = create_conn())) {
			delete s_con_arg;
			return -1;
		}

		unsigned int ns; // new socket fd.
		struct sockaddr remote;
		int len;
		len = sizeof(struct sockaddr);

		// Listening ...
		fprintf(stderr, "%s\n", "Listening...");
		ns = accept(s, (struct sockaddr *)&remote, (socklen_t *)&len);
		
		// make a new thread here.
		// folk();
		struct sockaddr_in *si = (struct sockaddr_in *)&remote;
//	remote.sin_addr.s_addr = inet_addr(str_ip);

		fprintf(stderr, "Client connected from %s.\n", inet_ntoa(si->sin_addr));
		
		// Connection attemption accepted..
        if (-1 == ns)
		{
			fprintf(stderr, "Listening error.\n");
			ret = -1;
		}
		else
		{
			ret = srv_op(s_con_arg, ns);
		}

		close_conn(ns);
	}
	else if ( CLIENT == s_con_arg->peer_mode )
	{
		// entered client mode
		ret = clt_op(s_con_arg);
	}

	t_end = time(&t_end);
	t_interval  = t_end - t_start;


	t_hou = t_interval/3600;
	t_min = (t_interval%3600)/60;
	t_sec = (t_interval%3600)%60;
	fprintf(stderr, "\nOperation consumes %02dh:%02dm:%02ds\n", t_hou, t_min, t_sec);
	
	DEL_CHAR_BUF(lanin_buf);
	DEL_CHAR_BUF(lanout_buf);
	DEL_CHAR_BUF(gfin_buf);
	DEL_CHAR_BUF(gfout_buf);

	if ( s_con_arg->sfd > 0 ) {
		close_conn(s_con_arg->sfd);
	}
	
	delete s_con_arg;

	return ret;
}

/** send hello message.
	out_buf format:
	[operation head + file path]
*/
int 
send_hello(struct st_con_arg *con,			// connection context
		   struct st_op_head *s_op_head,	// operation head
		   char *out_buf,					// send buffer pool
		   int buflen)						// 0, this value is calculated in the function.
{
	char *pbuf = out_buf;

	s_op_head->msg_type = MSG_HELLO;
	s_op_head->cfm_mode = con->cfm_mode;

	if ( DATA_SNK == con->con_mode) 
		s_op_head->len = OP_HEAD_SIZE + con->src_addr.pathlen;
	else{
		s_op_head->len = OP_HEAD_SIZE + con->sink_addr.pathlen;
		s_op_head->filelen = con->fstat.st_size;
	}

	memcpy(pbuf, s_op_head, OP_HEAD_SIZE);
	pbuf = out_buf + OP_HEAD_SIZE;

	if ( DATA_SNK == con->con_mode ) {
		// local peer is data source, so need the destination file path in remote peer
		memcpy(pbuf, con->src_addr.ppath, con->src_addr.pathlen);
	}
	else
	{ // local peer is data source, so need the destination file path in remote peer
		memcpy(pbuf, con->sink_addr.ppath, con->sink_addr.pathlen);
	}
	
	fprintf(stderr, "Hello message sent.\n");
	// tell the remote a read operation is attempted.
	return send(con->sfd, out_buf, s_op_head->len, 0);
}

/** process hello message.
	hello message format:
	[operation head + file path]
*/
int 
recv_hello(struct st_con_arg *s_con_arg, struct st_op_head *s_op_head, char *in_buf, int buflen)
{
	char *phead, *ppayload;
	int in_len;
	int ret = 0;

	fprintf(stderr, "Receiveing Hello message...");
	in_len = recv(s_con_arg->sfd, in_buf, MAX_MSG_LEN, MSG_PARTIAL);
	fprintf(stderr, "done.\n");

	s_con_arg->tot_recv += in_len;
	phead = in_buf;
	ppayload = in_buf + OP_HEAD_SIZE;
	memcpy(s_op_head, phead, OP_HEAD_SIZE);
	if ( MSG_HELLO == s_op_head->msg_type ) {
		fprintf(stderr, "Hello message received.\n");
		// hello message received
		switch(s_op_head->op_type) {
		case OP_READ:
			fprintf(stderr, "A read operation is scheduled.\n");
			s_con_arg->con_mode = DATA_SRC;
			s_con_arg->src_addr.pathlen = s_op_head->len - OP_HEAD_SIZE;
			s_con_arg->src_addr.ppath = new char [s_con_arg->src_addr.pathlen];
			memcpy(s_con_arg->src_addr.ppath, ppayload, s_con_arg->src_addr.pathlen);
			s_con_arg->src_addr.ppath[s_con_arg->src_addr.pathlen] = 0;
			//s_con_arg->fd = open(s_con_arg->src_addr.ppath, O_RDONLY|O_BINARY);
			s_con_arg->fp = fopen(s_con_arg->src_addr.ppath, "r+b");
			if (NULL == s_con_arg->fp){//(0 > s_con_arg->fd) {
				fprintf(stderr, "File %s can't be opened for read.\n", s_con_arg->src_addr.ppath);
				s_op_head->ret_val = OP_SRCFILEOPEN;
				ret = -1;
			}
			else{
				fprintf(stderr, "File %s opened for read.\n", s_con_arg->src_addr.ppath);
				s_con_arg->fd = open(s_con_arg->src_addr.ppath, O_RDONLY);
				if (s_con_arg->fd > 0) {
					fstat(s_con_arg->fd, &(s_con_arg->fstat));
					s_op_head->filelen = s_con_arg->fstat.st_size;
				}
			}

			break;
		case OP_WRITE:
			fprintf(stderr, "A write operation is scheduled.\n");
			s_con_arg->con_mode = DATA_SNK;
			s_con_arg->sink_addr.pathlen = s_op_head->len - OP_HEAD_SIZE;
			s_con_arg->sink_addr.ppath = new char [s_con_arg->sink_addr.pathlen];
			memcpy(s_con_arg->sink_addr.ppath, ppayload, s_con_arg->sink_addr.pathlen);
			s_con_arg->sink_addr.ppath[s_con_arg->sink_addr.pathlen] = 0;
			//s_con_arg->fd = open(s_con_arg->sink_addr.ppath, O_WRONLY|O_CREAT|O_TRUNC|O_BINARY);
			s_con_arg->fp = fopen(s_con_arg->sink_addr.ppath, "w+b");
			if(NULL == s_con_arg->fp ){ //( 0 > s_con_arg->fd) {
				fprintf(stderr, "File %s can't be opened for write.\n", s_con_arg->sink_addr.ppath);
				s_op_head->ret_val = OP_SNKFILEOPEN;
				ret = -1;
			}
			else{
				fprintf(stderr, "File %s opened for write.\n", s_con_arg->sink_addr.ppath);
				s_con_arg->fstat.st_size = s_op_head->filelen;
			}
			
			break;
		default:
			fprintf(stderr, "Unspecified operation.\n");
		}
	}
	else
	{
		fprintf(stderr, "A hello message is needed.\n");
		ret = -1;
	}
	
	return ret;
}

/** send helloack message.
*/
int 
send_helloack(struct st_con_arg *con, struct st_op_head *s_op_head, char *out_buf, int buflen)
{
	int ret = 0;

	s_op_head->msg_type = MSG_HELLOACK;
	s_op_head->len = OP_HEAD_SIZE;

	memcpy(out_buf,  s_op_head, OP_HEAD_SIZE);
	fprintf(stderr, "HelloAck message sent.\n");
	return send(con->sfd, out_buf, s_op_head->len, 0);
}

/** process helloack message.
*/
int 
recv_helloack(struct st_con_arg *con, struct st_op_head *s_op_head, char *in_buf, int buflen)
{
	char *pbuf;
	int ret = 0;
	
	ret = recv(con->sfd, in_buf, buflen, MSG_PARTIAL);
	if (-1 != ret) {
		pbuf = in_buf;
		memcpy(s_op_head, in_buf, OP_HEAD_SIZE);
		if (s_op_head->msg_type == MSG_HELLOACK) {
			fprintf(stderr, "HelloAck message received.\n");
			con->fstat.st_size = s_op_head->filelen;
			if ( OP_SUCCESS != s_op_head->ret_val) {
				ret = -1;
				if ( OP_SNKFILEOPEN == s_op_head->ret_val ) {
					fprintf(stderr, "Data sink can't open file %s for write.\n", con->sink_addr.ppath);
				}else if ( OP_SRCFILEOPEN == s_op_head->ret_val) {
					fprintf(stderr, "Data source can't open file %s for read.\n", con->src_addr.ppath);
				}
			}
		}
		else
		{
			fprintf(stderr, "HelloAck message is needed.\n");
			ret = -1;
		}
	}

	return ret;
}

/** send data to LLP.
	out_buf format:
	operation head + payload]
*/
int 
send_data(struct st_con_arg *con,		// connection context
		  struct st_op_head *s_op_head, // operation head
		  char *out_buf,				// send buffer pool
		  int buflen)					// desired send buffer length
{
	s_op_head->len = buflen;
	s_op_head->msg_type = MSG_DATA;

	memcpy(out_buf, s_op_head, OP_HEAD_SIZE);

	return send(con->sfd, out_buf, buflen, 0);
}

/** receive data from LLP.
	in_buf format:
	[operation head + payload]
*/
int 
recv_data(struct st_con_arg *con,		// connection context
		  struct st_op_head *s_op_head, // operation head
		  char *in_buf,					// receive buffer pool
		  int buflen)					// received buffer length.
{
	int recv_len = recv(con->sfd, in_buf, buflen, MSG_PARTIAL);

	if (recv_len >= 0) {
		memcpy(s_op_head, in_buf, OP_HEAD_SIZE);
		if (MSG_DATA != s_op_head->msg_type) {
			recv_len = -1;
		}
	}
	return recv_len;
}

/** when one peer received a data message, it should send out a data ack message to 
   inform the remote peer that the data is received.
*/
int 
send_dataack(struct st_con_arg *con, 
			 struct st_op_head *s_op_head, 
			 char *out_buf, 
			 int buflen)
{
	// the return value of the received data is setted out side.
	s_op_head->len = OP_HEAD_SIZE; // the dataack message only has a op head.
	s_op_head->msg_type = MSG_DATAACK;

	memcpy(out_buf, s_op_head, OP_HEAD_SIZE);

	return send(con->sfd, out_buf, s_op_head->len, 0);
}

/** when one peer received a dataack message, it should continue to send out a data message
    to remote peer.
*/
int 
recv_dataack(struct st_con_arg *con, 
			 struct st_op_head *s_op_head, 
			 char *in_buf, 
			 int buflen)
{
	int recv_len = recv(con->sfd, in_buf, OP_HEAD_SIZE, MSG_PARTIAL);

	if (recv_len >= 0) {
		memcpy(s_op_head, in_buf, OP_HEAD_SIZE);
		if (MSG_DATAACK != s_op_head->msg_type) {
			recv_len = -1;
		}
	}
	return recv_len;
}

/** server side operations, send hello message, 
	and receive the helloack message to handing, 
	or receive hello messages, and send helloack message to handing,
	then send/receive data to/from the remote peer.
*/
int srv_op(struct st_con_arg* s_con_arg, unsigned int s)
{
	s_con_arg->sfd = s;

	return proc_op(s_con_arg);
}

/** client side operations, send hello messages, 
	and receive the helloack message to handing,
	or receive hello messages, and send helloack message to handling,
	then send/receive data to/from the remote peer.
*/
int clt_op(struct st_con_arg* s_con_arg)
{
	unsigned int s; // socket fd
	int ret = 0;
	char *ftopen; // file to open
	//int openflg;
	char *openflag;
	// Open the file for write.
	if ( DATA_SNK == s_con_arg->con_mode) {
		ftopen = s_con_arg->sink_addr.ppath;
		if (OVERIDE == s_con_arg->cfm_mode) {
			//openflg = O_WRONLY|O_CREAT|O_TRUNC|O_BINARY;
			openflag = "w+b";
		}
	}else{
		ftopen = s_con_arg->src_addr.ppath;
		//openflg = O_RDONLY|O_BINARY;
		openflag = "r+b";
		s_con_arg->fd = open(s_con_arg->src_addr.ppath, O_RDONLY);
		if (s_con_arg->fd > 0) {
			fstat(s_con_arg->fd, &(s_con_arg->fstat));
		}
	}

	//s_con_arg->fd = open(ftopen, openflg);
	s_con_arg->fp = fopen(ftopen, openflag);
	if (NULL == s_con_arg->fp){//(s_con_arg->fd < 0) {
		fprintf(stderr, "File %s can't be opened.\n", ftopen);
		return -1;
	}

	// attempt to connect to remote service
	if (-1 == (s = open_conn(s_con_arg->str_ip)))
	{
		return -1;
	}

	s_con_arg->sfd = s;
	ret = proc_op(s_con_arg);

	return ret;
}

/** process operations either server side or client side.
*/
int
proc_op(struct st_con_arg *s_con_arg)
{
	char *phead, *ppayload;
	int in_len; // bytes read from the nic.
	int payload_len; // bytes followed the st_op_head.
	int out_len; // bytes send to nic.
	struct st_op_head s_op_head;
	int ret =0;
	/** treat below 4 buffer pointer as buffer pool.*/
	char *in_buf = lanin_buf;
	char *out_buf = lanout_buf;
	char *fin_buf = gfin_buf;
	char *fout_buf = gfout_buf;

	s_con_arg->tot_file_recv = 0;
	s_con_arg->tot_file_send = 0;
	s_con_arg->tot_recv = 0;
	s_con_arg->tot_send = 0;

	if (s_con_arg->peer_mode == SERVER) {
		// wait for hello message.
		ret = recv_hello(s_con_arg, &s_op_head, in_buf, MAX_MSG_LEN);
	}

	if (s_con_arg->con_mode == DATA_SNK) {
		// the local peer is data sink, perform a reading operation from remote peer.
		if (CLIENT == s_con_arg->peer_mode) {
			s_reg_sem.send = send_hello;
			s_reg_sem.con = s_con_arg;
			s_op_head.op_type = OP_READ;
			s_op_head.ret_val = OP_SUCCESS;

			/** 1. send the hello message. */
			ret = s_reg_sem.send(s_con_arg, &s_op_head, out_buf, 0);
			if (-1 != ret) {
				s_con_arg->tot_send += ret; 
				s_reg_sem.recv = recv_helloack;
			}
			else{
				//close(s_con_arg->fd);
				fclose(s_con_arg->fp);
			}

			/** 2. receive helloack message. */
			ret = s_reg_sem.recv(s_con_arg, &s_op_head, in_buf, OP_HEAD_SIZE);
			s_con_arg->tot_recv += ret;
		}
		else
		{
			// server side:
			/** hello message is processed upper. */
			s_reg_sem.send = send_helloack;

			/** 2. send the hello ack message*/
			ret = s_reg_sem.send(s_con_arg, &s_op_head, out_buf, OP_HEAD_SIZE);
			s_con_arg->tot_send += ret;
		}

		if (-1 != ret && OP_SUCCESS == s_op_head.ret_val) {
			s_reg_sem.recv = recv_data;
			s_reg_sem.send = send_data;
			s_con_arg->cfm_mode = s_op_head.cfm_mode;
		}
		else{
			//close(s_con_arg->fd);
			fclose(s_con_arg->fp);
			return -1;
		}

		/** 3. reading data from remote peer */
		// in_buf format: operation head + payload.
		phead = in_buf;
		ppayload = in_buf + OP_HEAD_SIZE;
		s_con_arg->tot_send = 0;

		/** reading pieces of data from the net of remote peer
		   and put them to the gfin_buf (file buffer pool) then 
		   write the mass of data to the file.  
		*/
		char *pdyn_fin = fin_buf; // dynamic pointer to the current position in the file in buffer pool.
		int dyn_fin_len = 0; // current valid data size of the file in buffer pool.
		payload_len = 0;

		fprintf(stderr, "Starting transfer data...\n");

		/** receive data from remote peer and write them to 
			the sink file.
		*/
		while( -1 != ret ){
			in_len = MAX_MSG_LEN + OP_HEAD_SIZE; // desired receive length
			/** receive a data message from the remote peer, 
				and fill the s_op_head struct.
			*/
			if ( -1 == (in_len = s_reg_sem.recv(s_con_arg, &s_op_head, in_buf, in_len)))
			{
				fprintf(stderr, "\nReceive data message fail. Server may be exited abnormally\n");
				ret = -1;
				in_len = fwrite(fin_buf, sizeof(char), dyn_fin_len, s_con_arg->fp);
				show_transfer(s_con_arg);
				break;
			}
			
			payload_len = in_len - OP_HEAD_SIZE;
			s_con_arg->tot_recv += in_len;
			s_con_arg->tot_file_recv += payload_len;

			if (s_op_head.ret_val == OP_CMPOK) {
				ret = 0;
				//in_len = write(s_con_arg->fd, fin_buf, dyn_fin_len);
				in_len = fwrite(fin_buf, sizeof(char), dyn_fin_len, s_con_arg->fp);
				show_transfer(s_con_arg);
				break;
			}

			if (s_op_head.ret_val != OP_SUCCESS) {
				ret = -1;
				break;
			}

			/** send the dataack message to inform the remote peer a successful transfering of 
			   data message is completed, prepare for the next one. 
			*/
			if ( 0 <= payload_len ) {
				s_op_head.ret_val = OP_SUCCESS;
				if (-1 == send_dataack(s_con_arg, &s_op_head, out_buf, OP_HEAD_SIZE)) {
					ret = -1;
					break;
				};
				s_con_arg->tot_send += OP_HEAD_SIZE;
			}

			
			if (0 > payload_len ) {
				ret = -1;
				break;
			}

			if (0 == payload_len) {
				ret = 0;
				break;
			}

			/** put the piece of buffer into the in-bound file buffer pool 
				dyn_fin_len indicates current total data putted in.
			*/
			if (payload_len < (FILE_BUF_LEN - dyn_fin_len)) {
				// still has enough space for the payload.
				memcpy(pdyn_fin, ppayload, payload_len);
				pdyn_fin += payload_len;
				dyn_fin_len += payload_len;
			}
			else 
			{
				// write the received useful data to file opened.
				// actually this in_len stores the actual written bytes.
				//in_len = write(s_con_arg->fd, fin_buf, dyn_fin_len);
				in_len = fwrite(fin_buf, sizeof(char), dyn_fin_len, s_con_arg->fp);
				// put the remain data to the file buffer pool from the very beginning.
				pdyn_fin = fin_buf;
				dyn_fin_len = payload_len;
				memcpy(pdyn_fin, ppayload, dyn_fin_len);
				pdyn_fin += payload_len; // point to next start of segment.
				show_transfer(s_con_arg);
			}
		} // end of while 

//		if (0 == ret) {
			// operation completed successfully
			//close(s_con_arg->fd);
			fclose(s_con_arg->fp);
//		}
	}
	else if ( DATA_SRC == s_con_arg->con_mode ) {
		// the local peer is data source, perform a reading operation for the remote peer.
		if (CLIENT == s_con_arg->peer_mode) {
			s_reg_sem.send = send_hello;
			s_reg_sem.con = s_con_arg;
			s_op_head.op_type = OP_WRITE;
			s_op_head.ret_val = OP_SUCCESS;
			/** 1. send the hello message. */
			ret = s_reg_sem.send(s_con_arg, &s_op_head, out_buf, OP_HEAD_SIZE);
			if (-1 != ret) {
				s_con_arg->tot_send += ret;
				s_reg_sem.recv = recv_helloack;
			}
			else{
				//close(s_con_arg->fd);
				fclose(s_con_arg->fp);
			}
		
			/** 2. receive helloack message. */
			ret = s_reg_sem.recv(s_con_arg, &s_op_head, in_buf, OP_HEAD_SIZE);
			s_con_arg->tot_recv += ret;
		}
		else
		{
			// server side:
			/** the hello message is processed upper. */
			s_reg_sem.send = send_helloack;

			/** 2. send the hello ack message*/
			ret = s_reg_sem.send(s_con_arg, &s_op_head, out_buf, OP_HEAD_SIZE);
			s_con_arg->tot_send += ret;
		}

		if (-1 != ret && OP_SUCCESS == s_op_head.ret_val) {
			s_reg_sem.recv = recv_data;
			s_reg_sem.send = send_data;
		}
		else{
			//close(s_con_arg->fd);
			fclose(s_con_arg->fp);
			return -1;
		}

		/** 3. writing data to the remote peer */
		// in_buf format: operation head + payload.
		char *phead = out_buf;
		char *ppayload = out_buf + OP_HEAD_SIZE;
		s_op_head.msg_type = MSG_DATA;

		/** reading pieces of data from the file of local peer
		and put them to the gfout_buf (file buffer pool) then 
		write(send) the mass of data to the remote peer.  
		*/
		char *pdyn_fout = fout_buf; // dynamic pointer to the current position in the out-bound file buffer pool.
		int dyn_fout_len = 0; // current valid data size of the out-bound file buffer pool.
		int fout_len;	// one mass length read from the file.
		payload_len = 0;
		
		fprintf(stderr, "Starting transfer data...\n");
		while( -1 != ret ){
			// read a mass form file.
			//fout_len = read(s_con_arg->fd, fout_buf, FILE_BUF_LEN);
			fout_len = fread(fout_buf, sizeof(char), FILE_BUF_LEN, s_con_arg->fp);
			if ( fout_len < 0 ) {
				ret = -1;
				s_op_head.ret_val = OP_RDERR;
			}

			show_transfer(s_con_arg);

			if ( fout_len == 0) {
				ret = 0;
				s_op_head.ret_val = OP_CMPOK;
				// send the COMPK return value.
				s_con_arg->tot_send += OP_HEAD_SIZE;
				if ( -1 == (out_len = s_reg_sem.send(s_con_arg, &s_op_head, phead, OP_HEAD_SIZE)))
				{
					fprintf(stderr, "Send completion data message fail.\n");
					ret = -1;
				}
				break;
			}

			// send pieces of data
			pdyn_fout = fout_buf;
			dyn_fout_len = 0; // how many bytes has been sent out.
			while(fout_len > dyn_fout_len)
			{
				if (fout_len - dyn_fout_len > MAX_MSG_LEN ) 
					out_len = MAX_MSG_LEN;
				else
					out_len = fout_len - dyn_fout_len;

				memcpy(ppayload, pdyn_fout, out_len);
				/** 1. there could be a hidden trouble: originaly out_len buffer will be sent, 
				  but if uses send function and returns a value less than the out_len,
				  so the pointer should pull back to the gap of the out_len - value;
				*/
				// send data to remote peer
				if ( -1 == (out_len = s_reg_sem.send(s_con_arg, &s_op_head, phead, out_len + OP_HEAD_SIZE)))
				{
					fprintf(stderr, "Send data message fail.\n");
					ret = -1;
					break;
				}
				
				payload_len = out_len - OP_HEAD_SIZE;
				s_con_arg->tot_send += out_len;
				s_con_arg->tot_file_send += payload_len;
				// point to the next segment in the send file pool.
				/** 2. so the pointer added at an actural offset responds to the send data length. */
				pdyn_fout += payload_len;
				dyn_fout_len += payload_len;

				/** wait until the remote send back a dataack message to inform a successful data
				   message transferring.
				*/
				if (out_len >= 0) {
					if (-1 == recv_dataack(s_con_arg, &s_op_head, in_buf, OP_HEAD_SIZE)) {
						ret = -1;
						break;
					};
					s_con_arg->tot_recv += OP_HEAD_SIZE;
				}

				if (s_op_head.ret_val != OP_SUCCESS) {
					ret = -1;
					break;
				}
			} // end of while of send mass data
			
			if (s_op_head.ret_val != OP_SUCCESS) {
				ret = -1;
				break;
			}
		} 

//		if (0 == ret) {
			// operation completed successfully
			//close(s_con_arg->fd);
			fclose(s_con_arg->fp);
//		}
	}
	else {
		ret = -1;
	}

	return ret;
}

void show_err()
{
#ifdef WIN32
	int err = GetLastError();
	switch(err) {
	case WSAEHOSTUNREACH:
		fprintf(stderr, "Host unreachable.\n");
		break;
	case WSAECONNREFUSED:
		fprintf(stderr, "Connection refused on host. \nMaybe the service is inactive.\n");
		break;
	case WSAEADDRINUSE:
		fprintf(stderr, "Address already in use. ");
		break;
	default:
		fprintf(stderr, "Unspecfic error # %d.\n", err);
	}
#endif
}

void show_transfer(struct st_con_arg *s_con)
{
	time_t t_elaps, t_hou, t_min, t_sec;
	int samp_val;
	long fsize = s_con->fstat.st_size; 
	long lspeed;  // bytes/s
	float fspeed, fspeed2; // bytes/s
	float fcmp = 0.0;		// completed percent
	system(CLR_SCR);
	time(&t_elaps);
	t_elaps -= t_start;

	fprintf(stderr, "File %s, total %ld Bytes.\n", s_con->src_addr.ppath, fsize);
	fprintf(stderr, "-------------------------------------------------\n");
	fprintf(stderr, "Total send\tTotal recv\tTotal file");
	if (s_con->con_mode == DATA_SNK) {
		fprintf(stderr, " recv (Bytes)\n %8d\t%8d\t%8d\n", s_con->tot_send, s_con->tot_recv, s_con->tot_file_recv);	
		samp_val = s_con->tot_recv;
		fcmp = 100*((float)s_con->tot_file_recv/fsize);
	}
	else
	{
		fprintf(stderr, " send (Bytes)\n %8d\t%8d\t%8d\n", s_con->tot_send, s_con->tot_recv, s_con->tot_file_send);	
		samp_val = s_con->tot_send;
		fcmp = 100*((float)s_con->tot_file_send/fsize);
	}

	if (t_elaps!=0) {
		fprintf(stderr, "Data transfer speed: ");
		fspeed2 = (float)samp_val/t_elaps;
		if (s_con->tot_send<1024) {
			fspeed = fspeed2;
			fprintf(stderr, "%8.2f Bytes/s\n", fspeed);
		}
		else{
			fspeed = fspeed2/1024;
			fprintf(stderr, "%8.2f KB/s\n", fspeed);
		}
	}

	if ( fspeed2 > ftop_spd) {
		ftop_spd = fspeed2;
	}

	if (ftop_spd > 1024) 
		fprintf(stderr, "Top transfer speed: %8.2f KBytes/s\n", ftop_spd/1024);
	else
		fprintf(stderr, "Top transfer speed: %8.2f Bytes/s\n", ftop_spd);

	t_hou = t_elaps/3600;
	t_min = (t_elaps%3600)/60;
	t_sec = (t_elaps%3600)%60;
	fprintf(stderr, "Total time elapse %02dh:%02dm:%02ds\n", t_hou, t_min, t_sec);
	if (t_elaps>0) {
		lspeed = samp_val/t_elaps;
		if (lspeed>0) 
			t_elaps = (s_con->fstat.st_size - samp_val)/ lspeed;
		else
			t_elaps = 1;
	}

	t_hou = t_elaps/3600;
	t_min = (t_elaps%3600)/60;
	t_sec = (t_elaps%3600)%60;
	fprintf(stderr, "Total time remain %02dh:%02dm:%02ds\n", t_hou, t_min, t_sec);
	fprintf(stderr, "\t %3.2f%% Completed.\n", fcmp);
}

/** endif olfile.cpp */
