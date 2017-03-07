#include "fileop.h"

#define  __PATH "F:\\±¸·Ý\\Ñ§Ï°\\code\\FileOperate\\Debug\\test.txt"
void main()
{
	CFileOp * pF_Op = new CFileOp(__PATH, "ab+", SH_DENYNO);

	char * buf = new char[__MILLION+1];

	strcpy(buf, ">>>>>>>>>>");

	fpos_t pos_t;
	pF_Op->get_file_point_pos(&pos_t);
	pos_t += __MILLION;
	pF_Op->set_file_point_pos(&pos_t);
	pF_Op->write_n(buf, sizeof(char), __MILLION);

	delete buf;

	delete pF_Op;
}
