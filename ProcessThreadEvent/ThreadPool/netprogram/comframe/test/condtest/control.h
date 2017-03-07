#include <pthread.h>
#include "../sync.h"

typedef struct data_control {
  //pthread_mutex_t mutex;
  //pthread_cond_t cond;
  CCondition cond;
  //CThreadMutex mutex;  
  int active;
} data_control;

extern int control_init(data_control *mycontrol);
extern int control_destroy(data_control *mycontrol);
extern int control_activate(data_control *mycontrol);
extern int control_deactivate(data_control *mycontrol);

