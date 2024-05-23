
#include <pthread.h>
#include <stdio.h>


int x = 0;
// Hai process cung thuc hien 1 viec 
void *processA()
{
    while (1)
    {
        x = x + 1;
        if (x == 20)
            x = 0;
        printf("%d",x);
    }
}

void *processB()
{
    while (1)
    {
        x = x + 1;
        if (x == 20)
            x = 0;
        printf("%d",x);
    }
}
int main()
{
    
    pthread_t pA, pB;
    pthread_create(&pA, NULL, &processA, NULL);
    pthread_create(&pB, NULL, &processB, NULL);
    while(1){}
    return 0;
}
