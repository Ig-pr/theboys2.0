#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "fprio.h"



// Cria uma fila vazia.
// Retorno: ponteiro para a fila criada ou NULL se erro.
struct fprio_t *fprio_cria()
{
    struct fprio_t *nova_lista = malloc(sizeof(struct fprio_t));
    memset(nova_lista, 0, sizeof(struct fprio_t));
    return nova_lista;
}

// Libera todas as estruturas de dados da fila, inclusive os itens.
// Retorno: NULL.
struct fprio_t *fprio_destroi(struct fprio_t *f)
{
    struct fpnodo_t *aux;
    for (int i = 0; i < f->num; i++)
    {
        aux = f->prim;
        f->prim = aux->prox;
        free(aux);
        f->num--;
    }
    // no fim da um free na lista e lista recebe NULL por preocaução
    free(f);
    return NULL;
}

// Insere o item na fila, mantendo-a ordenada por prios crescentes.
// Itens com a mesma prio devem respeitar a politica FIFO (retirar
// na ordem em que inseriu).
// Inserir duas vezes o mesmo item (o mesmo ponteiro) é um erro.
// Retorno: número de itens na fila após a operação ou -1 se erro.
int fprio_insere(struct fprio_t *f, void *item, int tipo, int prio)
{
    struct fpnodo_t *novo_item = malloc(sizeof(struct fpnodo_t));
    if (!f || !novo_item || !item)
        return -1;

    memset(novo_item, 0, sizeof(struct fpnodo_t));

    if (!f->num)
    {
        f->prim = novo_item;
        f->fim = novo_item;
    }
    else
    {
        struct fpnodo_t *aux = f->prim;
        while (aux)
        {
            if (item == aux->item)
                return -1;
            aux = aux->prox;
        }
        aux = f->prim;
        if (aux->prio > prio)
        {
            novo_item->prox = aux;
            f->prim = novo_item;
        }
        else if (f->fim->prio <= prio)
        {
            f->fim->prox = novo_item;
            f->fim = novo_item;
        }
        else
        {
            for (int i = 0; aux->prox->prio <= prio; i++)
                aux = aux->prox;

            novo_item->prox = aux->prox;
            aux->prox = novo_item;
        }
    }
    novo_item->item = item;
    novo_item->prio = prio;
    novo_item->tipo = tipo;
    f->num++;
    return f->num;
}

// Retira o primeiro item da fila e o devolve; o tipo e a prio
// do item são devolvidos nos parâmetros "tipo" e "prio".
// Retorno: ponteiro para o item retirado ou NULL se fila vazia ou erro.
void *fprio_retira(struct fprio_t *f, int *tipo, int *prio)
{
    if (!f || !tipo || !prio)
        return NULL;
    if (f->num > 1)
    {
        struct fpnodo_t *aux = f->prim;
        f->prim = aux->prox;
        *tipo = aux->tipo;
        *prio = aux->prio;
        void *item = aux->item;
        f->num--;
        free(aux);
        return item;
    }
    if (f->num == 1)
    {
        *tipo = f->prim->tipo;
        *prio = f->prim->prio;
        void *item = f->prim->item;
        f->num--;
        free(f->prim);
        return item;
    }
    f->num--;
    return NULL;
}

// Informa o número de itens na fila.
// Retorno: N >= 0 ou -1 se erro.
int fprio_tamanho(struct fprio_t *f)
{
    if (!f)
        return -1;
    return f->num;
}

// Imprime o itemeúdo da fila no formato "(tipo prio) (tipo prio) ..."
// Para cada item deve ser impresso seu tipo e sua prio, com um
// espaço entre valores, sem espaços antes ou depois e sem nova linha.
void fprio_imprime(struct fprio_t *f)
{
    if (f && f->num == 1)
        printf("(%d %d)", f->prim->tipo, f->prim->prio);
    else
    {
        // Se a lista é válida e o tamanho é maior que 1 então um auxiliar vai percorrendo a lista e sendo impresso em cada laço
        if (f && f->num > 1)
        {
            struct fpnodo_t *aux = f->prim;
            for (int i = 0; i < f->num - 1; i++)
            {
                printf("(%d %d) ", aux->tipo, aux->prio);
                aux = aux->prox;
            }
            printf("(%d %d)", f->fim->tipo, f->fim->prio);
        }
    }
}