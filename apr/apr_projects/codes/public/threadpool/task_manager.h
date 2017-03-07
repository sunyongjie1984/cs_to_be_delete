#pragma once


#include "thread.h"
#include "handle_manager.h"

#include "log.h"

// /* default buffer size */
// #define BUFSIZE			4096
// 
// 
// typedef void (* __PRINT)(char *);
// 
// extern void __cdecl LOG(const int level, const char * f, ...);



class CTaskThread;
class CAbstractTask;
class CThreadManager
{
public:
	CThreadManager();
	virtual ~CThreadManager();

	int get_handle_size(void);
	int get_task_size(void);

	void create(apr_pool_t * mp);
	void clear_task(void);
	void start_create_sem(void);
	void dispatch_exit(CAbstractTask * task);
	void task_interrupt_request(int num);
	void handle_interrupt_request(int num);
	void recovery_thread_handle(CAbstractThread * aw);
	void add_thread_handle(CAbstractThread * handle);

	void set_exit_status(bool f, apr_interval_time_t timeout = 0);
	void get_handle_size(size_t &tree_size, size_t &queue_size);

	apr_status_t await_create_sem(apr_interval_time_t timeout = -1);
	apr_status_t pop_front_handle(CAbstractThread* &handle, apr_interval_time_t timeout = -1);

	static void clear_task_queue(void *task, void * data = NULL);

	inline bool	get_exit_status(void)				{ return m_exit_status; }
	inline void	dispatch(CAbstractTask * task)		{ m_task_queue.push_back(task); m_create_sem.start(); }

	inline apr_pool_t *			get_pool(void)		{ return m_mp; }
	inline apr_interval_time_t	get_timeout(void)	{ return m_timeout; }

	inline CTaskQueue<CAbstractTask*>*	get_task_queue(void)	{ return &m_task_queue; }
	
public:
	void init(void);
	void fini(void);
	
private:
	CHandleManager<CAbstractThread*, CAbstractThread*> m_handle_manager;

	CTaskQueue<CAbstractTask*>	m_task_queue;
	apr_interval_time_t			m_timeout;

	CSemaphore		m_create_sem;
	apr_pool_t *	m_mp;
	bool			m_exit_status;

public:
	long m_thread_count;
};


class CAbstractTask
{
public:
	CAbstractTask()
	{

	}

	virtual ~CAbstractTask() { }
	virtual void start(void * data = NULL) = 0;

	inline void set_handle(CThreadManager * manager, CTaskThread * worker)	{	m_manager = manager;	m_worker = worker;	}	
	inline bool check_interrupt_request(void)	{		return m_manager->get_exit_status();	}
	static void release(CAbstractTask * obj)	{		if (obj) { delete obj; obj = NULL; }	}

protected:
	CThreadManager * m_manager;
	CTaskThread *	m_worker;

public:
	double m_d0_;
	double m_d1_;
	double m_d2_;
	double m_d3_;
	double m_d4_;
	double m_d5_;
private:
};

class CTaskThread : public CAbstractThread
{
public:
	CTaskThread();
	virtual ~CTaskThread();

	apr_status_t create(apr_pool_t * mp, CThreadManager &manager, apr_interval_time_t timeout = -1);

	inline apr_interval_time_t	get_timeout(void)	{ return m_timeout; }
	inline CThreadManager *		get_manager(void)	{ return m_manager; }

	inline bool	check_interrupt_request(void)		{ return m_manager->get_exit_status(); }

protected:
	void run(void);
	void init(void);
	void fini(void);

private:
	CThreadManager *	m_manager;
	apr_interval_time_t m_timeout;
};


