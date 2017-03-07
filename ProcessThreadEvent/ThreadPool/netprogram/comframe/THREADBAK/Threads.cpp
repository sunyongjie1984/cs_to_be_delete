#ifndef    _THREAD_H_
#define    _THREAD_H_

#include <pthread.h>
#include "comhead.h"
#include <iostream.h>

//here we should define some exception for thread class
//such as CThreadException

extern "C" void * global_run_thread( void *arg );

class CThread
{
protected:
    pthread_t       m_ThreadId;
    pthread_attr_t  m_ThreadAttr;

    bool            m_IsRunning;
    int             m_ThreadNo;
    
public:
    CThread( int thread_no = -1 );
    virtual ~CThread( );


    int GetThreadNo( ) const { return m_ThreadNo; }
    void SetThreadNo( int threadno );

    void ResetRunning( ) { m_IsRunning = false; }
    virtual void Run( ) = 0;

    virtual void Start( bool detached = false,bool sscope = false ){
	Create( detached, sscope);
    }
    virtual void Stop( ){ Cancel(); }


    void Create( bool detached = false, bool sscope = false );
    void Detach( );
    void WaitForOver( );
    void Exit( );

    void Cancel( );
    void SendSignalToThread( int signo );

    void SetToSleep( long m_sec, long nano_sec );
};

CThread::CThread( int thread_no ):
    m_IsRunning(false),m_ThreadNo(thread_no){}

CThread::~CThread (){
    if( m_IsRunning )
        Cancel();
}

void CThread::SetThreadNo( int threadno ){
    m_ThreadNo = threadno;
}
    
void CThread::Create( bool detached, bool sscope )
{
    //if thread is not running
    if( !m_IsRunning )
    {
        int status;
        
        if ((status = pthread_attr_init( &m_ThreadAttr )) != 0)
        {
            cout << "(CThread) create : pthread_attr_init ("
                 << strerror( status ) << ")" << endl;
            return;
        }

        if ( detached )
	{
            if ((status = pthread_attr_setdetachstate( &m_ThreadAttr, \
		 PTHREAD_CREATE_DETACHED)) != 0)
            {
                cout << "(CThread) create : pthread_attr_setdetachstate("
                     << strerror( status ) << ")" << endl;
                return;
            }
        }

        if ( sscope )
        {
            if ((status = pthread_attr_setscope( &m_ThreadAttr, \
		 PTHREAD_SCOPE_SYSTEM)) != 0 )
            {
                cout << "(CThread) create : pthread_attr_setscope ("
                     << strerror( status ) << ")" << endl;
                return;
            }
        }
        //here create thread with the specia m_ThreadAttr
	//and the task assign to the thread is to run the
	//function global_run_thread 
        if ((status = pthread_create( &m_ThreadId, &m_ThreadAttr, 
	    global_run_thread , this ) != 0))
	{
           cout << "(CThread) create : pthread_create ("
                << strerror( status ) << ")" << endl;
	}
       else
           m_IsRunning = true;
    }
    else
        cerr << "(CThread) create : thread is already running" << endl;
}

void CThread::Detach( )
{
    if( m_IsRunning )
    {
        int status;
        if ((status = pthread_detach( m_ThreadId )) != 0)
            cout << "(CThread) detach : pthread_detach ("
                 << strerror( status ) << ")" << endl;
    }
}

void CThread::WaitForOver( )
{
    if ( m_IsRunning )
    {
        int status;
        if ((status = pthread_join( m_ThreadId, NULL )) != 0)
            cout << "(CThread) join : pthread_join ("
                 << strerror( status ) << ")" << endl;

        m_IsRunning = false;
    }
}

void CThread::Exit( )
{
    if ( m_IsRunning && (pthread_self() == m_ThreadId))
    {
        void  *ret_val = NULL;

        pthread_exit( ret_val );
        
        m_IsRunning = false;
    }
}

void CThread::Cancel ()
{
    if ( m_IsRunning )
    {
        int status;
        
        if ((status = pthread_cancel( m_ThreadId )) != 0)
            cout << "(CThread) cancel : pthread_cancel ("
                 << strerror( status ) << ")" << endl;
    }
}

void CThread::SendSignalToThread ( int signo )
{
    if ( m_IsRunning )
    {
        int status;
        if ((status = pthread_kill( m_ThreadId, signo )) != 0)
            cout << "(CThread) kill : pthread_kill ("
                 << strerror( status ) << ")" << endl;
        else
            m_IsRunning = false;
    }
}

void CThread::SetToSleep ( long m_sec, long nano_sec )
{
    if ( m_IsRunning )
    {
        struct timespec  interval;

        if ( m_sec < 0 )    m_sec = 0;
        if ( nano_sec < 0 ) nano_sec = 0;
        while ( nano_sec >= 1000000 )
        {
            m_sec++;
            nano_sec -= 1000000;
        }
        
        interval.tv_sec  = m_sec / 1000;
        interval.tv_nsec = (m_sec % 1000) * 1000000 + nano_sec;
    
        if (nanosleep( &interval, 0 ) != 0)
            cout << "(CThread) delay : error in nanosleep" << endl;
    }
}

extern "C"
void * global_run_thread( void *arg )
{
    if (arg != NULL)
    {
        ((CThread*) arg)->Run();
        ((CThread*) arg)->ResetRunning();
    }

    return NULL;
}
#endif
main()
{
    printf("%d",100);
}
