#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

// Cria uma fila vazia.
// Retorno: ponteiro para a fila criada ou NULL se erro.
struct fila_t *fila_cria()
{
    struct fila_t *nova_lista = malloc(sizeof(struct fila_t));
    memset(nova_lista, 0, sizeof(struct fila_t));
    return nova_lista;
}

// Libera todas as estruturas de dados da fila, inclusive os itens.
// Retorno: NULL.
struct fila_t *fila_destroi(struct fila_t *f)
{
    struct fila_nodo_t *aux;
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

// Insere o item na fila
// Inserir duas vezes o mesmo item (o mesmo ponteiro) é um erro.
// Retorno: número de itens na fila após a operação ou -1 se erro.
int fila_insere(struct fila_t *f, void *item)
{

    if (!f || !item)
        return -1;

    struct fila_nodo_t *aux = f->prim;
    while (aux)
    {
        if (item == aux->item)
            return -1;
        aux = aux->prox;
    }

    struct fila_nodo_t *novo_item = malloc(sizeof(struct fila_nodo_t));
    if (!novo_item)
        return -1;

    memset(novo_item, 0, sizeof(struct fila_nodo_t));

    if (!f->num)
    {
        f->prim = novo_item;
        f->fim = novo_item;
    }
    else
    {

        f->fim->prox = novo_item;
        f->fim = novo_item;
    }
    novo_item->item = item;
    f->num++;
    return f->num;
}

// Retira o primeiro item da fila e o devolve
// Retorno: ponteiro para o item retirado ou NULL se fila vazia ou erro.
void *fila_retira(struct fila_t *f)
{
    if (!f || f->num == 0)
        return NULL;
    if (f->num > 1)
    {
        struct fila_nodo_t *aux = f->prim;
        f->prim = aux->prox;

        void *item = aux->item;
        f->num--;
        free(aux);
        return item;
    }
    if (f->num == 1)
    {

        void *item = f->prim->item;
        f->num--;
        free(f->prim);
        return item;
    }
}

// Informa o número de itens na fila.
// Retorno: N >= 0 ou -1 se erro.
int fila_tamanho(struct fila_t *f)
{
    if (!f)
        return -1;
    return f->num;
}

// Imprime o conteúdo da fila
void fila_imprime(struct fila_t *f)
{
    if (f)
    {
        if (f->num == 1)
            printf("(%d)", *(int *)f->prim->item);
        if (f->num > 1)
        {
            struct fila_nodo_t *aux = f->prim;
            for (int i = 0; i < f->num - 1; i++)
            {
                printf("(%d) ", *(int *)aux->item);
                aux = aux->prox;
            }
            printf("(%d)", *(int *)f->fim->item);
        }
    }
}
