  
/**
	Offload file transfer module using socket to test TCP offload engine(TOE).
	By Vino @ 9th, June 2004.
	Email: rtc@eyou.com
	All copyrights reserved.
*/
  
#ifndef __OLFILE_H
#define __OLFILE_H

#define MAX_MSG_LEN		512//for my pc(1024*4-380) is stady, for linyx, 1 is steady
#define FILE_BUF_LEN	(1024*1024)

#ifdef UNM_OFFLOAD
	#define AF_INET_NORMAL AF_UNM
#else
	#define AF_INET_NORMAL AF_INET
#endif

#ifdef WIN32
	typedef size_t pid_t;
	typedef int socklen_t;
	#define CLR_SCR "cls"
#else
	typedef unsigned int SOCKET;
	typedef int BOOL;
	#define  TRUE true
	#define closesocket close
	#define MSG_PARTIAL 0
	#define CLR_SCR "clear"
#endif

#define SERVER_PORT 6600 // outbound port
#define CLIENT_PORT 6601 // inbound port

enum econ_mode{DATA_SRC=1, DATA_SNK}; // the local is data source or data sink
enum ecfm_mode{CONFIRM, OVERIDE};
enum epeer_mode{SERVER=1, CLIENT};
enum evalid{INVALID, VALID};

#define DEL_CHAR_BUF(x) 	if (NULL != (x)) { delete [] (x);}

/** operation result code */
enum eop_res{
	OP_SUCCESS = 100,
	OP_CMPOK,	// operation completed successfully
	OP_SRCFILEOPEN, // can't open source file
	OP_SNKFILEOPEN, // can't open sink file
	OP_WTERR,
	OP_RDERR,
	OP_UNKNOWN	// unknown error
};

/** operation type/ message type */
enum emsg_type{
	MSG_HELLO=1, 
	MSG_HELLOACK, 
	MSG_DATA,
	MSG_DATAACK
};

enum eop_type{OP_READ=1, OP_WRITE};

#define ARG_SRV "-server"
#define ARG_SRC	"-src"
#define ARG_SNK	"-snk"
#define ARG_IP	"-ip"
#define ARG_Y	"-y"
#define ARG_MAGGIE	"-maggie"

struct st_con_arg
{
	unsigned int sfd;
	int fd;
	FILE *fp;
	unsigned char flag; // INVALID or VALID of this node.
	int con_mode;		// DATA_SRC or DATA_SNK
	int cfm_mode;		// CONFIRM or OVERIDE
	int peer_mode;		// SERVER or CLIENT.
	struct{
		char *ppath;	// data source file path
		size_t pathlen;	// srcpath
	}src_addr;
	
	struct {
		char *ppath;	// data sink file path
		size_t pathlen;	// file path length
	}sink_addr;

	char *str_ip;		// remote peer ip
	struct stat fstat;	// file status struct;
	unsigned long ip;
	unsigned long tot_send;			// total bytes sended.
	unsigned long tot_file_send;	// total bytes of file data sended.
	unsigned long tot_recv;			// total bytes received.
	unsigned long tot_file_recv;	// total bytes of file data received.
};

/** register connection sementics
*/
struct st_reg_sem
{
	struct st_con_arg *con;
	int (*send)(struct st_con_arg *con, struct st_op_head *s_op_head, char *buf, int buflen);
	int (*recv)(struct st_con_arg *con, struct st_op_head *s_op_head, char *buf, int buflen);
};

/** 
   +-----------+----------------------+
   |   head    |      payload         |
   +-----------+----------------------+
*/

/** Operation head.
  4 bytes allignment.
*/
struct st_op_head
{
	int len;						// the length of transaction
	int msg_type;						// message type
	int cfm_mode;					// confirm or overide
//	char user[USER_NAME_LEN];		// who made the operation
//	int ssn_id;						// session ID
	int op_type;					// operation type
	int ret_val;					// functions return value
	long filelen;					// file length
//	int seq;						// sequence
//	int chksum;						// payload checksum
};

int send_hello(struct st_con_arg *con, struct st_op_head *s_op_head, char *buf, int buflen);
int recv_hello(struct st_con_arg *con, struct st_op_head *s_op_head, char *buf, int buflen);
int send_helloack(struct st_con_arg *con, struct st_op_head *s_op_head, char *buf, int buflen);
int recv_helloack(struct st_con_arg *con, struct st_op_head *s_op_head, char *buf, int buflen);
int send_data(struct st_con_arg *con, struct st_op_head *s_op_head, char *out_buf, int buflen);
int recv_data(struct st_con_arg *con, struct st_op_head *s_op_head, char *in_buf, int buflen);

int srv_op(struct st_con_arg* s_con_arg, unsigned int s);
int clt_op(struct st_con_arg* s_con_arg);

int proc_op(struct st_con_arg *s_con_arg);

void show_err();
void show_transfer(struct st_con_arg *s_con);

/**

*/
#endif // __OLFILE_H

/** End of olfile.h*/
