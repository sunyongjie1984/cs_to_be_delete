#include "buffer.h"

#define CUTEND "\r\n"

bool Buffer::writeBuf(char* buf, int size)
{
	if(size < 0){
		LOG4CXX_INFO(logger, "writeBuf: size < 0");
		return false;
	}
	if(size == 0)
		return true;
	if(((BUFSIZE*BUFMULT) - m_write) < size){
		if(m_write > m_read){
			char *p = m_buf + m_read;
			memcpy(m_tmp, p, (m_write - m_read));
			m_write -= m_read;
			m_read = 0;
			memcpy(m_buf, m_tmp, m_write);
		}else if(m_write == m_read){
			reSet();
			LOG4CXX_INFO(logger, "writeBuf: reset the buffer");
		}
		LOG4CXX_INFO(logger, "writeBuf:m_rite = '" << m_write << "'");
	}
	if(((BUFSIZE*BUFMULT) - m_write) < size){
		LOG4CXX_ERROR(logger, "writeBuf: buf = '" << m_buf << "'");
		return false;
	}
	char* p = m_buf + m_write;
	memcpy(p, buf, size);
	m_write += size;
	return true;
}

int Buffer::readBuf(char* buf)
{
	//package judge and return one package to buf
	if(m_read >= m_write)
		return 0;
	char* p = m_buf + m_read;
	char* q = p;
	char* p_beg = p;
	int len = 0;//sizeof(struct BestQuota);
	p ++;
	while(((*p != '\n') || (*q != '\r')) && (*p != '\0')){
		q = p;
		p ++;
		len ++;
	}
	if(*p == '\0')
		return 0;
	len += 2;
	memcpy(buf, p_beg, len);
	m_read += len;
	return len;
}

