#include <stdlib.h>
#include "semaphore.h"
#include "globals.h"


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

// indica se o sushi shop está aberto
unsigned int oppened = FALSE;

sem_t semaforo_pegar_comida; 

// @Caio: arrays dos pratos seguem mesma ordem do enum
// array com quantidades produzidas de cada prato
int* pratos_produzidos[5] = {0, 0, 0, 0, 0};

// array com quantidades consumidas de cada prato
int* pratos_consumidos[5] = {0, 0, 0, 0, 0};

int sentados = 0;

int globals_get_sentados(){
    return sentados;
}

sem_t globals_get_semaforo_pegar_comida(){
    return semaforo_pegar_comida;
}

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

void globals_add_prato_consumido(int prato) {
    pratos_consumidos[prato] += 1;
}

/**
 * @brief Finaliza todas as variáveis globais.
 * Se criar alguma variável global que faça uso de mallocs, lembre-se sempre 
 * de usar o free dentro dessa função.
 */
void globals_finalize() {
    virtual_clock_finalize(global_virtual_clock);
    conveyor_belt_finalize(global_conveyor_belt);
}
