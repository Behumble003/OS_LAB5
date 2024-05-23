/*######################################
# University of Information Technology #
# IT007 Operating System #
# <Tran Quoc Bao>, <22520123> #
# File: example_thread_creation.c #
######################################*/
#include <pthread.h>
#include <stdio.h>
void *thread_print(void *messenge) //chuc nang cua thread - print message 
{
    while (1)
    {
        printf("Hello, How are you?\n");
    }
}
int main()
{
    pthread_t idthread;
    pthread_create(&idthread, NULL, &thread_print, NULL);
    while (1)
    {
        printf("I’m fine, and you?\n");
    }
    return 0;
}

//nho bo sung -lpthread khi bien dich 