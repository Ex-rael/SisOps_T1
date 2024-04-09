# Explicação do Algoritmo de Peterson
> O algoritmo de Peterson’ é usado para sincronizar dois processos. Ele usa duas variáveis, uma matriz bool bandeira tamanho 2 e uma variável int virarpara realizá-lo. Na solução, i representa o Consumidor e j representa o Produtor. Inicialmente, as bandeiras são falsas. Quando um processo quer executar itilits seção crítica, ele define seu sinalizador para true e se transforma no índice do outro processo. Isso significa que o processo quer ser executado, mas permitirá que o outro processo seja executado primeiro. O processo executa ocupado esperando até que o outro processo tenha terminado it“s própria seção crítica. Depois disso, o processo atual entra em sua seção crítica e adiciona ou remove um número aleatório do buffer compartilhado. Depois de completar a seção crítica, ele define it“s própria bandeira para false, indicando que não deseja mais executar. O programa é executado por um período fixo de tempo antes de sair. Esse tempo pode ser alterado alterando o valor da macro RT.

```c
// code for producer (j)

// producer j is ready
// to produce an item
flag[j] = true;

// but consumer (i) can consume an item
turn = i;

// if consumer is ready to consume an item
// and if its consumer's turn
while (flag[i] == true &amp;&amp; turn == i)

    { /* then producer will wait*/ }

    // otherwise producer will produce
    // an item and put it into buffer (critical Section)

    // Now, producer is out of critical section
    flag[j] = false;
    // end of code for producer

    //--------------------------------------------------------
    // code for consumer i

    // consumer i is ready
    // to consume an item
    flag[i] = true;

    // but producer (j) can produce an item
    turn = j;

    // if producer is ready to produce an item
    // and if its producer's turn
    while (flag[j] == true &amp;&amp; turn == j)

        { /* then consumer will wait */ }

        // otherwise consumer will consume
        // an item from buffer (critical Section)

        // Now, consumer is out of critical section
        flag[i] = false;
// end of code for consumer
```