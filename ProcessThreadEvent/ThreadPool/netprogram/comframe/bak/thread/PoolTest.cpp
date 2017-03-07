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
	printf("Result is %d then sleep for 200 secs...\n",i);
	sleep(2);
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
        printf("================================\n");
        printf("================================\n");
        printf("================================\n");
        printf("================================\n");
        mutex.Unlock();
	sleep(1);
    }
};


main()
{
    CThreadManage* manage = new CThreadManage(4);
   
    int i=0;
	
    for(i=0;i<40;i++)
    {
        CXJob*   job = new CXJob();
	manage->Run(job,NULL);
    }

    sleep(5);

    CYJob* job = new CYJob();
    manage->Run(job,NULL);
    manage->TerminateAll();
}
