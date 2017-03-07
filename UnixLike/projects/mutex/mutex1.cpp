#include <stdlib.h>
#include <iostream>
#include <pthread.h>
#include "foo.h"


/*foo a;     */

extern pthread_mutex_t lock_cout;

struct foo * foo_alloc(void) /* allocate the object */
{
    struct foo *fp;

    if ((fp = (foo*)malloc(sizeof(struct foo))) != NULL)
    {
        fp->f_count = 1;
        if (pthread_mutex_init(&fp->f_lock, NULL) != 0)
        {
            free(fp);
            return(NULL);
        }
        /* ... continue initialization ... */
    }
    // return(fp);
    return fp;
}

void foo_hold(struct foo *fp, unsigned int const & thread_id) /* add a reference to the object */
{
    pthread_mutex_lock(&fp->f_lock);
    fp->f_count++;
    pthread_mutex_lock(&lock_cout);
    std::cout << "I am in thread " << fp->f_count << " " << thread_id << std::endl;
    pthread_mutex_unlock(&lock_cout);
    pthread_mutex_unlock(&fp->f_lock);
}

void foo_rele(struct foo *fp) /* release a reference to the object */
{
    pthread_mutex_lock(&fp->f_lock);
    if (--fp->f_count == 0)
    { /* last reference */
        pthread_mutex_unlock(&fp->f_lock);
        pthread_mutex_destroy(&fp->f_lock);
        free(fp);
    }
    else
    {
        pthread_mutex_unlock(&fp->f_lock);
    }
}
