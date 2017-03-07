#ifndef BUFFER_H_
#define BUFFER_H_

#include <log4cxx/propertyconfigurator.h>

#define BUFSIZE 4096
#define BUFMULT 5

extern log4cxx::LoggerPtr logger;

class Buffer{
	public:
		Buffer(){
			m_len = 0;
			reSet();
		}
		~Buffer(){}
		//write data to buffer
		bool writeBuf(char* buf, int size);
		//read data from buffer, return value is buf size
		int readBuf(char* buf);
		//set buf to 0
		inline void reSet();
	private:
		//Buffer
		char m_buf[BUFSIZE*BUFMULT];
		char m_tmp[BUFSIZE*BUFMULT];
		//read len of buf, write len of buf
		int m_read, m_write;
		//data lengh
		int m_len;
};

inline void Buffer::reSet()
{
	m_read = 0;
	m_write = 0;
	memset(m_buf, '\0', BUFSIZE*BUFMULT);
	memset(m_tmp, '\0', BUFSIZE*BUFMULT);
}
#endif
