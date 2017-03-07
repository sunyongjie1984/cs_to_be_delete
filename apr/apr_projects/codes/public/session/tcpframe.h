#pragma once



#include "session.h"
#include <memory.h>


class CAbstractBuffer
{
public:
	CAbstractBuffer() : m_buff_len(sizeof(m_buff)-1)
	{
		clear();
	}
	virtual ~CAbstractBuffer()
	{
		
	}
	/*
	inline bool write(char * buf, const int len)
	{
		int inlen = m_write_pos - m_read_pos;
		if (0 < inlen)
		{
			if (inlen < m_read_pos)
			{
				move(inlen);
				return copy(buf, len);
			}
			else
			{
				return copy(buf, len);
			}
		}
		else if (0 == inlen)
		{
			clear();
			return copy(buf, len);
		}
		//error
		return false;
	}
	*/
	inline bool write(char * buf, const int len)
	{
		const int inlen = m_write_pos - m_read_pos;
		
		if (0 < inlen)
		{
			//未读长度大于0
			if (m_buff_len - m_write_pos < len)
			{
				//BUFF剩余长度小于输入长度
				if (inlen < m_read_pos)
				{
					//未读长度小于已读长度，将未读数据移至BUFF头部
					move(inlen);
					return copy(buf, len);
				}
			}
			else
			{
				//BUFF剩余长度大于输入长度，直接拷贝
				return copy(buf, len);
			}
		}
		else if (0 == inlen)
		{
			//未读长度等于0时，直接清空buff，然后拷贝
			clear();
			return copy(buf, len);
		}
		return false;
	}
	
	inline bool read(char ** buf, int * len)
	{
		return read_tactic(buf, len);
	}
protected:
	
	inline void move(int move_len)
	{
		memcpy(m_buff, m_buff+m_read_pos, move_len);
		m_write_pos = move_len;
		memset(m_buff+m_write_pos, 0, m_buff_len-m_write_pos);
		m_read_pos = 0;
	}
	inline bool copy(char * buf, int len)
	{
		if (len < m_buff_len)
		{
			memcpy(m_buff+m_write_pos, buf, len);
			m_write_pos += len;
			return true;
		}
		return false;
	}
	inline void clear(void)
	{
		memset(m_buff, 0, m_buff_len);
		m_read_pos	= 0;
		m_write_pos = 0;
	}
	virtual bool read_tactic(char ** buf, int * len) = 0;
	
protected:
	int			m_read_pos;
	int			m_write_pos;
	const int	m_buff_len;
	char		m_buff[__IO_BUFFER_LEN__];
	
	
private:
};



class CSessionBuffer : public CAbstractBuffer
{
public:
	CSessionBuffer() : m_flag(__END_FLAG__), m_flag_len(strlen(m_flag))
	{

	}
	virtual ~CSessionBuffer()
	{

	}
protected:
	virtual bool read_tactic(char ** buf, int * len)
	{
		*buf = m_buff+m_read_pos;
		char * pos = find(*buf, m_flag);

		if (pos)
		{
			*len = &pos[m_flag_len] - *buf - 2;//这里-2是为了去掉__END_FLAG__的字符串
			m_read_pos = pos - m_buff + m_flag_len;

			return true;
		}
		*len = 0;
		*buf = NULL;
		return false;
	}
	char * find(const char * buf, const char * flag)
	{
 		char * pos = NULL;

		if (buf)
		{
			int find_len = m_write_pos - m_flag_len + 1;
			for (int i=0; i<find_len; i++)
			{
				pos = NULL;
				if (buf[i] == flag[0])
				{
					pos = (char *)&buf[i];
					if (0 == strncmp(pos+1, flag+1, m_flag_len-1))
						return pos;
					else
						pos = NULL;
				}
			}
		}
		return pos;
	}
private:
	const char * m_flag;
	const int  m_flag_len;
};


class CAbstractTcp
{
public:
	CAbstractTcp();
	virtual ~CAbstractTcp();
	
	inline apr_socket_t * get_acceptor(void)		{ return m_acceptor;	}
	inline apr_pollset_t * get_reactor(void)		{ return m_reactor;		}
	
	apr_status_t run(void * data, apr_pool_t * mp, apr_interval_time_t timeout = APR_USEC_PER_SEC * 50, int listen_port = 9198, int size = 512);

protected:
	static apr_status_t __reactor_entry(apr_pool_t * mp, apr_socket_t * descriptor, apr_pollset_t * reactor, apr_socket_t * acceptor, void * data);

	static bool			__is_reject(void * data, apr_socket_t * channel, apr_pool_t * mp_child);
	static apr_status_t __accept(apr_pool_t * mp, apr_socket_t * channel, apr_pollset_t * reactor, void * data);
	static apr_status_t __recv(apr_pool_t * mp, apr_socket_t * channel, apr_pollset_t * reactor, void * data);

protected:
	inline bool read(char ** buf, int * len)		{ return m_buffer.read(buf, len);	}
	inline bool write(char * buf, const int len)	{ return m_buffer.write(buf, len);	}

	virtual bool is_reject(void) = 0;
	virtual bool check_interrupt_request(void) = 0;
	virtual void start_worker(char * buff, apr_size_t len, apr_socket_t * channel) = 0;
	virtual void session_close( apr_pool_t * mp, apr_pollset_t * reactor, apr_socket_t * s) = 0;
	virtual void addtree(apr_socket_t * channel, CHANNEL * tc) = 0;

public:
	double m_d0_;
	double m_d1_;
	double m_d2_;
	
protected:
	apr_socket_t	* m_acceptor;
	apr_pollset_t	* m_reactor;
	CSessionBuffer	m_buffer;
	int				m_size;
};



class CAbstractIOCPTcp
{
public:
	CAbstractIOCPTcp();
	virtual ~CAbstractIOCPTcp();
	
	inline apr_socket_t * get_acceptor(void)	{ return m_acceptor;	}
	inline apr_pollcb_t * get_reactor(void)		{ return m_reactor;		}
	
	apr_status_t run(void * data, apr_pool_t * mp, apr_interval_time_t timeout = APR_USEC_PER_SEC * 50, int listen_port = 9198, int size = 512);
	
protected:
	static apr_status_t reactor_entry(void *baton, apr_pollfd_t *descriptor);
	static apr_status_t accept_entry(apr_pool_t * mp, apr_socket_t * channel, apr_pollset_t * reactor, void * data);
	static apr_status_t recv_entry(apr_pool_t * mp, apr_socket_t * channel, apr_pollset_t * reactor, void * data);
	
protected:
	virtual bool check_interrupt_request(void) = 0;
	virtual void start_worker(char * cmd_break_point, char * buff, apr_size_t len, apr_socket_t * channel) = 0;
	virtual void session_close( apr_pool_t * mp, apr_pollset_t * reactor, apr_socket_t * s) = 0;
	virtual void addtree(apr_socket_t * channel) = 0;
	
public:
	double m_d0_;
	double m_d1_;
	double m_d2_;
	
protected:
	apr_socket_t	* m_acceptor;
	apr_pollcb_t	* m_reactor;
};