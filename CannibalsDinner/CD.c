#include<stdio.h>
#include<pthread.h>
#include <unistd.h>
#include <malloc.h>
// Jantar dos Canibais
// Implementacao mutex com algoritmo de Peterson

int g_nNumCanibais   = 0; // numero de canibais
int g_nNumMaxPorcoes = 0; // numero de panelas
int g_nLevelLength   = 0; // c_nNumCanibais + c_nNumMaxPanelas;
int g_nWaitingLenght = 0; // c_nLevelLength - 1;
int g_nNumPorcoes    = 0; // numero de panelas disponiveis

volatile int *g_arrLevel;
volatile int *g_arrWaiting;

pthread_t Cheff_t;
// ---------------------------------------------------------------------------------------------------------------------
void Mutex_Init  ();
void Mutex_Unlock(int task_id);
void Mutex_Lock  (int task_id);
void *Cheff      (void *arg);
void *Cannibal   (void *arg);

int main(int argc, char **argv)
{
    int success = 0;
    while (!success)
    {
        printf("Insira a quantidade de Cannibals: ");
        success = scanf("%d", &g_nNumCanibais);
        while (getchar() != '\n');
    }

    success = 0;
    while (!success)
    {
        printf("Insira a quantidade de porcoes suportada pela mesa de jantar: ");
        success = scanf("%d", &g_nNumMaxPorcoes);
        while (getchar() != '\n');
    }

    // inicia com o numero maximo de porcoes
    g_nNumPorcoes    = g_nNumMaxPorcoes;
    g_nLevelLength   = g_nNumCanibais + g_nNumMaxPorcoes;
    g_nWaitingLenght = g_nLevelLength - 1;

    g_arrLevel   = (int *) malloc(g_nLevelLength   * sizeof(int));
    g_arrWaiting = (int *) malloc(g_nWaitingLenght * sizeof(int));

    // Inicia o mutex
    Mutex_Init();

    pthread_t Cannibals[g_nNumCanibais];
    int i;

    for(i = 0; i < g_nNumCanibais; i++)
    {
        pthread_create(&Cannibals[i], NULL, Cannibal, (void *) i);
    }
    for(i = 0; i < g_nNumCanibais; i++)
    {
        pthread_join(Cannibals[i], NULL);
    }
    return 0;
}

void *Cannibal(void *arg)
{
    int id = (int)arg;
    while(1)
    {
        Mutex_Lock(id);
        if(g_nNumPorcoes == 0)
        {
            printf("Acabaram as porcoes! Canibal %d chamou o cozinheiro\n", id);
            // acordar Cheff
            pthread_create(&Cheff_t, NULL, Cheff, NULL);
            pthread_join(Cheff_t, NULL);
            Mutex_Unlock(id);
        } else {
            g_nNumPorcoes--;
            printf("Canibal %d comendo...\n %d porcoes disponiveis\n", id, g_nNumPorcoes);
            Mutex_Unlock(id);
            usleep(1);
        }
    }
}

void *Cheff(void *arg)
{
    if (g_nNumPorcoes == 0)
    {
        printf("Cozinheiro acordou! Enchendo a mesa...\n ");
        g_nNumPorcoes = g_nNumMaxPorcoes;
        printf("Cozinheiro terminou de colocar a mesa e voltou a dormir...\n ");
    }
}

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