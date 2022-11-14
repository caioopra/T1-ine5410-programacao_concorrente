#include "globals.h"

#include <pthread.h>
#include <stdlib.h>

#include "semaphore.h"

/*
    VOCÊ DEVE CRIAR VARIÁVEIS GLOBAIS PARA ARMAZENAR DADOS SOBRE A SIMULAÇÃO.
    NOTAS:
    1.  OS SEGUINTES DADOS DEVEM SER ARMAZENADOS E PRINTADOS AO FIM DA SIMULAÇÃO:
        a. Quantidade de clientes que sentaram-se no conveyor e consumiram todos os itens desejados
        b. Quantidades produzidas de cada alimento
        c. Quantidades consumidas de cada alimento
    2.  SIGA OS EXEMPLOS DE VARIÁVEIS GLOBAIS JÁ EXISTENTES NESSE ARQUIVO PARA CRIAR AS NOVAS.
*/

virtual_clock_t* global_virtual_clock = NULL;
conveyor_belt_t* global_conveyor_belt = NULL;
queue_t* global_queue = NULL;
pthread_mutex_t consumed_food_mutex, cliente_satisfeito_mutex;
int cliente_satisfeito = 0;

// indica se o sushi shop está aberto
unsigned int oppened = FALSE;



// @Caio: arrays dos pratos seguem mesma ordem do enum
// array com quantidades produzidas de cada prato
int pratos_produzidos[5] = {0, 0, 0, 0, 0};

// array com quantidades consumidas de cada prato
int pratos_consumidos[5] = {0, 0, 0, 0, 0};
int* pratos_consumidos[5] = {0, 0, 0, 0, 0};

void globals_set_virtual_clock(virtual_clock_t* virtual_clock) {
    global_virtual_clock = virtual_clock;
}

virtual_clock_t* globals_get_virtual_clock() {
    return global_virtual_clock;
}

void globals_set_conveyor_belt(conveyor_belt_t* conveyor_belt) {
    global_conveyor_belt = conveyor_belt;
}

conveyor_belt_t* globals_get_conveyor_belt() {
    return global_conveyor_belt;
}

void globals_set_queue(queue_t* queue) {
    global_queue = queue;
}

queue_t* globals_get_queue() {
    return global_queue;
}

void globals_set_oppened(unsigned int state) {
    oppened = state;
}

unsigned int globals_get_oppened() {
    return oppened;
}

int* globals_get_pratos_produzidos() {
    return pratos_produzidos;
}

void globals_add_prato_produzido(int prato) {
    pratos_produzidos[prato] += 1;
}

int* globals_get_prato_consumido() {
    return pratos_consumidos;
}

pthread_mutex_t globals_get_consumed_food_mutex() {
    return consumed_food_mutex;
}

void globals_add_prato_consumido(int prato) {
    pthread_mutex_lock(&consumed_food_mutex);
    pratos_consumidos[prato] += 1;
    pthread_mutex_unlock(&consumed_food_mutex);
}

void finalize_global_mutexes() {
    pthread_mutex_destroy(&consumed_food_mutex);

}

pthread_mutex_t globals_get_cliente_satisfeito_mutex() {
    return cliente_satisfeito_mutex;
}

void globals_add_satisfeito() {
    pthread_mutex_lock(&cliente_satisfeito_mutex);
    cliente_satisfeito++;
    pthread_mutex_unlock(&cliente_satisfeito_mutex);
}

void finalize() {
    fprintf(stdout, "\n" BLUE BAR);
    fprintf(stdout, BLUE "FIM DA SIMULAÇÃO:");
    fprintf(stdout, "\n" BLUE BAR);

    fprintf(stdout, CYAN "\n Quantidade de clientes que consumiram tudo que desejavam: %d\n", cliente_satisfeito);

    // TODO: quantidade está saindo errada
    fprintf(stdout, CYAN " Quantidade de pratos produzidos:\n");
    fprintf(stdout, CYAN " - Sushi   %s: %d\n", SUSHI, pratos_produzidos[0]);
    fprintf(stdout, CYAN " - Dango   %s: %d\n", DANGO, pratos_produzidos[1]);
    fprintf(stdout, CYAN " - Ramen   %s: %d\n", RAMEN, pratos_produzidos[2]);
    fprintf(stdout, CYAN " - Onigiri %s: %d\n", ONIGIRI, pratos_produzidos[3]);
    fprintf(stdout, CYAN " - Tofu    %s: %d\n", TOFU, pratos_produzidos[4]);

    fprintf(stdout, CYAN " Quantidade de pratos consumidos:\n");
    fprintf(stdout, CYAN " - Sushi   %s: %d\n", SUSHI, pratos_consumidos[0]);
    fprintf(stdout, CYAN " - Dango   %s: %d\n", DANGO, pratos_consumidos[1]);
    fprintf(stdout, CYAN " - Ramen   %s: %d\n", RAMEN, pratos_consumidos[2]);
    fprintf(stdout, CYAN " - Onigiri %s: %d\n", ONIGIRI, pratos_consumidos[3]);
    fprintf(stdout, CYAN " - Tofu    %s: %d\n", TOFU, pratos_consumidos[4]);

    fprintf(stdout, "\n" BLUE BAR);
}

/**
 * @brief Finaliza todas as variáveis globais.
 * Se criar alguma variável global que faça uso de mallocs, lembre-se sempre
 * de usar o free dentro dessa função.
 */
void globals_finalize() {
    virtual_clock_finalize(global_virtual_clock);
    conveyor_belt_finalize(global_conveyor_belt);
    finalize_global_mutexes();

    finalize();
}
