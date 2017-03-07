///定义CThread线程基类
/***********************************************************************
系统名称: NEEQ1.0
模块名称:
文 件 名: thread.h
功能说明:
作    者: 柳正龙
开发日期: 2013-9-7   9:14:45
修改记录:
***********************************************************************/
#ifndef _THREAD_H_
#define _THREAD_H_

#include "config_env.h"

/// 线程基类定义
/**
   @note 线程自身
   1，线程执行体Run()通过IsTerminated()来检测线程是否需要终止
   2，线程检测是否需要终止的时间间隔最好在100ms或更小，这样能更快的检测到线程是否需要终止
       ，防止Stop()的调用者等待超时而杀线程
       ，如果应用需要1000ms干一次活，可以将检测间隔设为100ms，每检测10次干一次活，来缩短检测时间
   3，线程不能调用自身的Stop()函数来达到终止自己的目的

   @note 调用者
   1，启动线程，调用Start()方法，函数返回成功时，线程已经被创建并启动
   2，终止线程，调用Stop()方法，可以设置超时时间(ms)，如Stop(200)，超时时间默认为无限等待
       ，注意超时时间最好大于线程检测停止的时间间隔，否则可能导致杀线程（线程杀掉后资源不能释放：如锁）

    @example:
	class CMyThread: public CThread
	{
	public:
		CMyThread();
		virtual ~CMyThread();

		virtual long Run();
	};

	long CMyThread::Run()
	{
		while (!IsTerminated())
		{
            // wait(100)
			... // do something
		}

		return 0;
	}

    @usage:
    CMyThread Thread;
    Thread.Start();
    //... 
    Thread.Stop(200);
*/
class CThread
{
	friend void OnThreadExit(void* pArg);
	friend void * thread_function(void* pArg);

public:
	/// 构造函数
	CThread();

	/// 析构函数，终止线程并释放资源
	virtual ~CThread();

    /// 启动线程
    /**
     * @return 0成功 其他失败
     */
	int32_t Start();		

    /// 终止线程，线程自身不能调用Stop()来终止
	/**
	 * @param iWait 超时时间,<0表示无限等待,默认为-1
     * @return 0成功 其他失败 
     * @note 失败可能的情况：Run()实现里 1，线程死锁；2，线程循环中不存在cancel点
	 */
	int32_t Stop(int iWait = INFINITE);

	/// 线程是否已经启动
	/**
	 * @return true 表示线程已经启动，false表示线程未启动
	 */
	inline bool IsRunning() const
	{
	 	return m_bStarted;
	}

    /// 线程是否需要终止
	/**
	 * @note Run()中可以检测该值以结束线程
	 * @return true表示需要终止,false表示不终止
	 */
	inline bool IsTerminated() const
	{
		return m_bTerminateRequest;
	}

    /// 设置线程需要终止标识
	/**
     * @note 线程执行体一般有任务时处理任务，没有任务时阻塞等候任务，类似下面流程:
     * while (!IsTerminated())
     * {
     *    task = wait_task(100ms);
     *    proc(task);
     * }
     * 任务生产者执行:push(task)放入任务，从而触发上面的wait_task(100ms)返回
     *
     * 在停止线程时，可以按照下面调用步骤，来加快线程停止：
     * 1，Terminate();      // 设置停止标识
     * 2，push_task(null);  // 激活线程
     * 3，Stop();           // 停止线程
	 */
	inline void Terminate()
	{
		m_bTerminateRequest = true;
        __sync_synchronize();
	}

protected:
	/// 线程执行体，使用者需重载该函数，加入线程执行体
	virtual long Run() = 0;

private:
	/// 禁止复制和赋值
	CThread(const CThread& one);
	CThread& operator=(const CThread& one);

    /// 等待信号
    /**
     * @param iWait 超时时间 <0表示无限等待，默认为-1
     * @return 0成功 其他失败
     */
    int WaitCond(int iWait = INFINITE);

private:
    pthread_mutex_t		m_CondMutex;		/**< 线程信号量锁 */
    pthread_cond_t		m_Cond;				/**< 线程信号量 */
    pthread_t           m_hThread;		    /**< 线程句柄 */
	bool volatile		m_bStarted;			/**< 是否已经启动 */
	bool volatile       m_bTerminateRequest;/**< 是否停止线程 */
};

#endif
