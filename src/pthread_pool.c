#include "pthread_pool.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define  IDLE    (0)
#define  BUSY    (1)
#define  SIG     SIGUSR1
#define  NO      (0)
#define  YES     (1)
#define  FREE    (0)


Pthread_ctl *pthread_ctl;
typedef void *(*Func)(void *);



void exe(int sig)
{
   printf("I am signal  ,I will work..............................\n");
}
void *fn(void *arg)
{
    Pthread pthread;
    Func func;
    void *argv;

    signal(SIG,exe);
    pause();
    argv = malloc(100);
    memcpy((void *)&pthread,arg,sizeof(Pthread));

    if(func = pthread.fn){
        argv = pthread.arg;
        func(argv);               // cb
        (*((Pthread *)arg)).flag = IDLE;
        (*((Pthread *)arg)).is_wait = NO;
    }

    pthread_exit(NULL);

    return (void *)0;
}

Boolean pthread_pool_mission(void *(*fn)(void *arg),void *arg)
{
       int i = 0;
       Pthread  *pthread = NULL;

       for(i = 0; i < pthread_ctl->thnum; i++){
           pthread = (Pthread *)(pthread_ctl + 1) + i;

           if(pthread->flag == IDLE){
               pthread->flag = BUSY;
               pthread->fn   = fn;
               pthread->arg  = arg;
               pthread_kill(pthread->thid, SIG); // send signal
               break;
           }

       }

       return TRUE;
}

Boolean pthread_pool_create(int thnum)
{
    int loop = 0;
    Pthread  *pthread;

    pthread_ctl = (Pthread_ctl *) malloc(sizeof(Pthread_ctl) + thnum * sizeof(Pthread));
    pthread_ctl->thnum = thnum;

    for(loop = 0; loop < thnum; loop++){
        pthread =(Pthread *)(pthread_ctl + 1) + loop;
        pthread->flag = IDLE;
        pthread->is_wait = YES;
        pthread_create(&(pthread->thid),NULL,fn,(void *)pthread);
    }

    return TRUE;

}

Boolean pthread_pool_end(void)
{
    int      loop = 0;
    Pthread  *pthread;

    for(loop = 0; loop < pthread_ctl->thnum; loop++){
        pthread = (Pthread *)(pthread_ctl + 1) + loop;
        if(pthread->flag == IDLE){
            continue;
        }else{
            printf("please wait,one thread is running\n");
            sleep(3);
            if(pthread->flag == BUSY){
                  pthread_cancel(pthread->thid);
            }
        }
    }

    for(loop = 0; loop < pthread_ctl->thnum; loop++){
           pthread = (Pthread *)(pthread_ctl + 1) + loop;
           if(pthread->is_wait == YES){
               pthread_kill(pthread->thid,SIG);
           }
           if(pthread_join(pthread->thid,NULL)){
                printf(" pthread_join error\n");
                return FALSE;
           }
    }

    return TRUE;

}








