#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define QUEUE_LENGTH 50
#define CONSUMERS    50
#define PRODUCERS    50
#define COLOR_RED   "\x1b[31m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_RESET "\x1b[0m"

const int g_nLevelLength   = CONSUMERS + QUEUE_LENGTH;
const int g_nWaitingLenght = CONSUMERS + QUEUE_LENGTH - 1;

volatile int g_arrLevel  [CONSUMERS + QUEUE_LENGTH];
volatile int g_arrWaiting[CONSUMERS + QUEUE_LENGTH - 1];

void Mutex_Unlock(int task_id);
void Mutex_Lock  (int task_id);

void Mutex_Unlock(int task_id)
{
    g_arrLevel[task_id] = 0;
}

void Mutex_Lock(int task_id)
{
    for (int l = 0; l < g_nWaitingLenght; l++)
    {
        g_arrLevel[task_id] = l;
        g_arrWaiting[l] = task_id;
        for (int k = 0; k < g_nLevelLength; k++)
        {
            while (k != task_id && g_arrLevel[k] >= l && g_arrWaiting[l] == task_id);
        }
    }
}

void Mutex_Init()
{
    for (int i = 0; i < g_nLevelLength; i++)
    {
        g_arrLevel[i] = 0;
    }
    for (int i = 0; i < g_nWaitingLenght; i++)
    {
        g_arrWaiting[i] = 0;
    }
}

typedef struct queue_s
{
    int  nCapacity;
    int  nLength;
    int  arValues [QUEUE_LENGTH];
    int  nStart;
    int  nEnd;
    void (*Init)    (struct queue_s *);
    int  (*Insert)  (struct queue_s *);
    int  (*Consume) (struct queue_s *);
    void (*Print)   (struct queue_s *);
}TQueue;

void QueueInit    (struct queue_s * q);
void QueuePrint   (struct queue_s * q);
int  QueueInsert  (struct queue_s * q);
int  QueueConsume (struct queue_s * q);

void QueueInit(struct queue_s * q)
{
    q->nStart    = -1;
    q->nEnd      = -1;
    q->nCapacity = QUEUE_LENGTH;
    q->nLength   = 0;
    for (int i = 0; i < QUEUE_LENGTH; i++)
        q->arValues[i] = -1;
    q->Insert  = QueueInsert;
    q->Consume = QueueConsume;
    q->Print   = QueuePrint;
}

int QueueInsert(struct queue_s * q)
{
    int nResult = (q->nLength + 1 <= q->nCapacity);
    if (nResult){
        if (q->nStart < 0)
            q->nStart = 0;
        q->arValues[++q->nEnd % q->nCapacity] = rand() % 100;
        q->nLength++;
    }
    return nResult;
}

int QueueConsume(struct queue_s * q)
{
    int nResult = q->nLength - 1 >= 0;
    if (nResult){
        q->arValues[q->nStart++] = -1;
        q->nLength--;
    }
    return nResult;
}

void QueuePrint(struct queue_s * q)
{
    printf("Queue [ ");
    for (int i = 0; i<q->nCapacity; i++)
    {
        if (i == 0 )
        {
            printf("%d", q->arValues[i]);
        } else
        {
            printf(", %d", q->arValues[i]);
        }
    }
    printf(" ]\n");
}

///////////////////////////////////////////
TQueue          g_Queue;

void *TaskConsumer(void *arg)
{
    TQueue *Queue = &g_Queue;
    int nSuccess;
    int nId = (int) arg;
    while(1)
    {
        Mutex_Lock(nId);
        nSuccess = Queue->Consume(Queue);
        Queue->Print(Queue);
        if (nSuccess)
        {
            printf(COLOR_GREEN "TaskConsumer: Thread: %d consume a resource\n" COLOR_RESET, nId);
        } else
        {
            printf(COLOR_RED "TaskConsumer: Thread: %d couldn't consume the resource\n" COLOR_RESET, nId);
        }
        Mutex_Unlock(nId);
        usleep(1);
    }
}

void *TaskProducer(void *arg)
{
    TQueue *Queue = &g_Queue;
    int nSuccess;
    int nId = (int) arg;
    while(1)
    {
        Mutex_Lock(nId);
        nSuccess = Queue->Insert(Queue);
        Queue->Print(Queue);
        if (nSuccess)
        {
            printf( COLOR_GREEN "TaskProducer: Thread: %d insert a resource\n" COLOR_RESET, nId);
        } else
        {
            printf(COLOR_RED "TaskProducer: Thread: %d couldn't insert a resource\n" COLOR_RESET, nId);
        }
        Mutex_Unlock(nId);
        usleep(1);
    }
}

int main(){
    int nThreadID = 0;

    TQueue *ptrQueue = &g_Queue;
    ptrQueue->Init=QueueInit;
    ptrQueue->Init(ptrQueue);

    pthread_t producers [PRODUCERS];
    pthread_t consumers [CONSUMERS];

    Mutex_Init();

    for (int i = 0; i < CONSUMERS; i++)
        pthread_create(&consumers[i], NULL, TaskConsumer, (void*)nThreadID++);

    for (int j = 0; j < PRODUCERS; j++)
        pthread_create(&producers[j], NULL, TaskProducer, (void*)nThreadID++);

    pthread_exit(NULL);
    return 0;
}