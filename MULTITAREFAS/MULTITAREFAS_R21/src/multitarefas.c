/*
 * Inclusao de arquivos de cabecalhos
 */
#include <asf.h>
#include "stdint.h"
#include "multitarefas.h"

/*
 * Prototipos das tarefas
 */
void tarefa_1(void);
void tarefa_2(void);
void tarefa_periodica(void); // Nova tarefa periódica

/*
 * Configuracao dos tamanhos das pilhas
 */
#define TAM_PILHA_1         (TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_2         (TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_PERIODICA (TAM_MINIMO_PILHA + 24) // Tamanho da pilha da tarefa periódica

/*
 * Declaracao das pilhas das tarefas
 */
uint32_t PILHA_TAREFA_1[TAM_PILHA_1];
uint32_t PILHA_TAREFA_2[TAM_PILHA_2];
uint32_t PILHA_PERIODICA[TAM_PILHA_PERIODICA]; // Pilha da tarefa periódica

/*
 * Funcao principal de entrada do sistema
 */
int main(void)
{
    system_init();

    /* Criacao das tarefas */
    /* Parametros: ponteiro, nome, ponteiro da pilha, tamanho da pilha, prioridade da tarefa */

    CriaTarefa(tarefa_1, "Tarefa 1", PILHA_TAREFA_1, TAM_PILHA_1, 2);

    CriaTarefa(tarefa_2, "Tarefa 2", PILHA_TAREFA_2, TAM_PILHA_2, 3);

    /* Criar tarefa periódica */
    CriaTarefa(tarefa_periodica, "Tarefa Periódica", PILHA_PERIODICA, TAM_PILHA_PERIODICA, 1);

    /* Cria tarefa ociosa do sistema */
    CriaTarefa(tarefa_ociosa, "Tarefa ociosa", PILHA_TAREFA_OCIOSA, TAM_PILHA_OCIOSA, 0);

    /* Configura marca de tempo */
    ConfiguraMarcaTempo();

    /* Inicia sistema multitarefas */
    IniciaMultitarefas();

    /* Nunca chega aqui */
    while (1)
    {
    }
}

/* Tarefas de exemplo */

void tarefa_1(void)
{
    volatile uint16_t a = 0;
    for (;;)
    {
        a++;
        port_pin_set_output_level(LED_0_PIN, LED_0_ACTIVE); /* Liga LED. */
        TarefaContinua(2);
    }
}

void tarefa_2(void)
{
    volatile uint16_t b = 0;
    for (;;)
    {
        b++;
        TarefaSuspende(2);
        port_pin_set_output_level(LED_0_PIN, !LED_0_ACTIVE); /* Desliga LED. */
    }
}

/* Tarefa periódica executada a cada 100 ms */
void tarefa_periodica(void)
{
     static uint32_t contador = 0;
    
    while (1) {
        // Executa o código da tarefa
        
        // Incrementa o contador
        contador++;
        
        // Verifica se passaram 100 iterações (100 ms)
        if (contador == 100) {
            // Reseta o contador
            contador = 0;
            
            port_pin_set_output_level(LED_0_PIN, !LED_0_ACTIVE);
            
            // ...
        }
        
        // Espera um curto período de tempo antes de executar novamente
        delay_ms(1);
    }
}