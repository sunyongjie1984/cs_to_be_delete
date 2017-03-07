#include "Thread.h"
#include <time.h>

class CJobThread:public CThread
{
public:
    CJobThread() : CThread(){};
    CJobThread(bool createsuspended,bool detach): CThread(createsuspended,detach){};
    ~CJobThread() {};

    void Execute()
    {
	printf("Thread %d print\n",Self());
    }
  private:
   unsigned int id;
};

main()
{
    for(int i=0;i<10;i++)
    {
	CJobThread* thr = new CJobThread();
	thr->Start();
    }
}

