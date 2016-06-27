#include <apue.h>
#include "pthread_pool.h"

void *print(void  *arg)
{
     char str[20]= {0};
     memcpy((void *)str,arg,strlen(arg) + 1);
     while(1){
         sleep(1);
         printf("%s\n",str);
     }
}


void *print1(void  *arg)
{
     char str[20] = {0};
     memcpy((void *)str,arg,strlen(arg) + 1);
     while(1){
         sleep(1);
         printf("%s\n",str);
     }

}

void *print2(void  *arg)
{
     char str[20] = {0};
     memcpy((void *)str,arg,strlen(arg) + 1);
     while(1){
          //sleep(1);
          printf("%s\n",str);
          sleep(1);
     }
}

int main(int argc,char *argv[])
{
    int i = atoi(argv[1]);
    char *str  = "hello world";
    char *str1 = "i'm cool";
    char *str2 = "wonderful";
    char *str3 = "man";

    if(pthread_pool_create(i) == FALSE){
         fprintf(stderr,"pthread_pool_create error\n");
         exit(1);
    }
    printf("pthread_pool_create  succeed\n");

    if(pthread_pool_mission(print,(void *)str) == FALSE){
         fprintf(stderr,"pthread_pool_mission error\n");
         exit(2);
    }
    printf("pthread_pool_mission succeed\n");


    if(pthread_pool_mission(print1,(void *)str1) == FALSE){
         fprintf(stderr,"pthread_pool_mission error\n");
         exit(2);
    }
    printf("pthread_pool_mission succeed\n");

    if(pthread_pool_mission(print2,(void *)str2) == FALSE){
         fprintf(stderr,"pthread_pool_mission error\n");
         exit(2);
    }
    printf("pthread_pool_mission succeed\n");


#if 1
    sleep(3);
    if(pthread_pool_end() == FALSE){
         fprintf(stderr,"pthread_pool_end error\n");
         exit(3);
    }

    printf("pthread_pool_end  succeed\n");
#endif
    return 0;
}
