#include "my_unp.h"  
  
void Pthread_create(pthread_t *tid, const pthread_attr_t *attr,  
                    void * (*func)(void *), void *arg)  
{  
    int n = pthread_create(tid, attr, func, arg);  
    if ( n == 0)  
        return;  
    errno = n;  
    error_quit("pthread_create error");  
}  
  
void Pthread_detach(pthread_t tid)  
{  
    int n = pthread_detach(tid);  
    if ( n == 0)  
        return;  
    errno = n;  
    error_quit("pthread_detach error");  
}  
  
void Pthread_join(pthread_t tid, void **status)  
{  
    int n = pthread_join(tid, status);  
    if ( n == 0 )  
        return;  
    errno = n;  
    error_quit("pthread_join error");  
}  
  
void Pthread_kill(pthread_t tid, int signo)  
{  
    int n = pthread_kill(tid, signo);  
    if ( n == 0 )  
        return;  
    errno = n;  
    error_quit("pthread_kill error");  
}  
  
void Pthread_mutex_lock(pthread_mutex_t *mptr)  
{  
    int n = pthread_mutex_lock(mptr);  
    if ( n == 0 )  
        return;  
    errno = n;  
    error_quit("pthread_mutex_lock error");  
}  
  
void Pthread_mutex_unlock(pthread_mutex_t *mptr)  
{  
    int n = pthread_mutex_unlock(mptr);  
    if ( n == 0 )  
        return;  
    errno = n;  
    error_quit("pthread_mutex_unlock error");  
}  
  
void Pthread_setconcurrency(int level)  
{  
    int n = pthread_setconcurrency(level);  
    if ( n == 0 )  
        return;  
    errno = n;  
    error_quit("pthread_mutex_unlock error");  
}  
  
void Pthread_cond_signal(pthread_cond_t *cptr)  
{  
    int n = pthread_cond_signal(cptr);  
    if ( n == 0 )  
        return;  
    errno = n;  
    error_quit("pthread_cond_signal error");  
}  
  
void Pthread_cond_wait(pthread_cond_t *cptr, pthread_mutex_t *mptr)  
{  
    int n = pthread_cond_wait(cptr, mptr);  
    if ( n == 0 )  
        return;  
    errno = n;  
    error_quit("pthread_cond_wait error");  
}  
  
sem_t *Sem_open(const char *name, int oflag,  
                mode_t mode, unsigned int value)  
{  
    sem_t *sem = sem_open(name, oflag, mode, value);  
    if( NULL == sem )  
        error_quit("sem_open error for %s", name);  
    return sem;  
}  
  
void Sem_close(sem_t *sem)  
{  
    if (sem_close(sem) == -1)  
        error_quit("sem_close error");  
}  
  
void Sem_unlink(const char *pathname)  
{  
    if (sem_unlink(pathname) == -1)  
        error_quit("sem_unlink error");  
}  
  
void Sem_init(sem_t *sem, int pshared, unsigned int value)  
{  
    if (sem_init(sem, pshared, value) == -1)  
        error_quit("sem_init error");  
}  
  
void Sem_destroy(sem_t *sem)  
{  
    if (sem_destroy(sem) == -1)  
        error_quit("sem_destroy error");  
}  
  
void Sem_wait(sem_t *sem)  
{  
    if (sem_wait(sem) == -1)  
        error_quit("sem_wait error");  
}  
  
void Sem_post(sem_t *sem)  
{  
    if (sem_post(sem) == -1)  
        error_quit("sem_post error");  
}  
  
void Sem_getvalue(sem_t *sem, int *valp)  
{  
    if (sem_getvalue(sem, valp) == -1)  
        error_quit("sem_getvalue error");  
}  
