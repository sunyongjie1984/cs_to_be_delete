#include "Job.h"
#include "time.h"
#include "ThreadManage.h"


class CXJob:public CJob
{
private:
    int i;	
    CThreadMutex mutex;
public:
    CXJob(){i=0;}
    ~CXJob(){}
    void Run(void* jobdata)
    {
	mutex.Lock();
	i++;
	mutex.Unlock();
	printf("%d\n",i);
    }
};

class CYJob:public CJob
{
private:
    int i;
    CThreadMutex mutex;
public:
    CYJob(){i=0;}
    ~CYJob(){}
    void Run(void* jobdata)
    {
        mutex.Lock();
        printf("==========================\n");
        mutex.Unlock();
    }
};


main()
{
    CThreadManage* manage = new CThreadManage(3);
   
    int i=0;
	
    for(i=0;i<4;i++)
    {
        CXJob*   job = new CXJob();
	manage->Run(job,NULL);
    }

    CYJob* job = new CYJob();
    manage->Run(job,NULL);
    manage->TerminateAll();
}
