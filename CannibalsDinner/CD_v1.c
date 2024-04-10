#include<stdio.h>
#include<pthread.h>
#include <unistd.h>
// jantar dos canibais
// mutex implementation with Peterson's algorithm

const int c_nNumCanibais   = 5; // numero de canibais
const int c_nNumMaxPanelas = 3; // numero de panelas
const int c_nLevelLength   = c_nNumCanibais + c_nNumMaxPanelas;
const int c_nWaitingLenght = c_nLevelLength - 1;
      int g_nNumPanelas    = 0; // numero de panelas disponiveis

volatile int g_arrLevel  [c_nLevelLength];
volatile int g_arrWaiting[c_nWaitingLenght];

//pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // mutex para acesso a regiao critica
//pthread_cond_t  cond  = PTHREAD_COND_INITIALIZER; // condicao para acordar o cozinheiro

// ---------------------------------------------------------------------------------------------------------------------


void lock(int task_id) {
        for (int l = 0; l < c_nWaitingLenght; l++) {
            level[task_id] = l;
            waiting[l] = task_id;
            for (k = 0; k < N; k++) {
                while (k != task_id && level[k] >= l && waiting[l] == task_id);
            }
        }
}
unlock(task_id) {
        level[task_id] = 0;
}

// ---------------------------------------------------------------------------------------------------------------------

void *cozinheiro(void *arg);
void *canibal(void *arg);

int main(int argc, char **argv)
{
    int success = 0;
    while (!success)
    {
        printf("Insira a quantidade de canibais: ");
        success = scanf("%d", &NumCanibais);
        while (getchar() != '\n');
    }

    success = 0;
    while (!success)
    {
        printf("Insira a quantidade de panelas suportada pela mesa de jantar: ");
        success = scanf("%d", &NumMaxPanelas);
        while (getchar() != '\n');
    }

    pthread_t canibais[NumCanibais], cozinheiro_t;
    int i;
    pthread_create(&cozinheiro_t, NULL, cozinheiro, NULL);
    for(i = 0; i < NumCanibais; i++)
    {
        pthread_create(&canibais[i], NULL, canibal, (void *)i);
    }
    pthread_join(cozinheiro_t, NULL);
    for(i = 0; i < NumCanibais; i++)
    {
        pthread_join(canibais[i], NULL);
    }
    return 0;
}

void *canibal(void *arg)
{
    int id = (int)arg;
    while(1)
    {
        pthread_mutex_lock(&mutex);
        while(NumPanelas == 0)
        {
            printf("Canibal %d esperando\n", id);
            pthread_cond_wait(&cond, &mutex);
        }
        NumPanelas--;
        printf("Canibal %d comendo\n", id);
        pthread_mutex_unlock(&mutex);
        usleep(1);
        pthread_mutex_lock(&mutex);
        NumPanelas++;
        printf("Canibal %d terminou de comer\n", id);
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
    }
}

void *cozinheiro(void *arg)
{
    while(1)
    {
        pthread_mutex_lock(&mutex);
        while(NumPanelas != NumMaxPanelas)
        {
            printf("Cozinheiro esperando\n");
            pthread_cond_wait(&cond, &mutex);
        }
        printf("Cozinheiro enchendo panelas\n");
        NumPanelas = NumMaxPanelas;
        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&mutex);
    }
}
