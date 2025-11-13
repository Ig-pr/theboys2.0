#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "entidades.h"
#include "fprio.h"




int random(int min, int max)
{
    return min + rand() % (max - min + 1);
}

struct coor *ini_mun()
{

    struct coor *coor_mundo = malloc(sizeof(struct heroi));
    memset(coor_mundo, 0, sizeof(struct heroi));
    return coor_mundo;
}

struct heroi *cria_heroi()
{
    struct heroi *novo_heroi = malloc(sizeof(struct heroi));
    memset(novo_heroi, 0, sizeof(struct heroi));
    return novo_heroi;
}

struct base *cria_base()
{
    struct base *nova_base = malloc(sizeof(struct base));
    memset(nova_base, 0, sizeof(struct base));
    return nova_base;
}

void ini_heroi(int i, struct heroi *h)
{
    h->id_h = i;
    h->xp_h = 0;
    h->hab = cjto_aleat(random(1, 3), 10);
    h->pac = random(0, 100);
    h->vel = random(50, 5000);
    h->status = 1;
    h->bas = random(0, N_BASES - 1);
}

struct coor *cria_local()
{
    struct coor *novo_local = malloc(sizeof(struct coor));
    memset(novo_local, 0, sizeof(struct coor));

    novo_local->x = random(0, N_TAMANHO_MUNDO - 1);
    novo_local->y = random(0, N_TAMANHO_MUNDO - 1);
    return novo_local;
}

struct base *ini_base(int i, struct base *b)
{
    b->id_b = i;
    b->tam = random(3, 10);
    b->local_b = cria_local();
    b->esp = fila_cria();
    b->missoes_c = 0;
    b->id_Hp = cjto_cria(N_HEROIS);
    return b;
}

struct missao *cria_missao()
{
    struct missao *nova_missao = malloc(sizeof(struct missao));
    memset(nova_missao, 0, sizeof(struct missao));

    return nova_missao;
}

struct missao *ini_missao(int i, struct missao *m)
{
    m->id_mis = i;
    m->local_m = cria_local();
    m->hab_n = cjto_aleat(random(6, 10), 10);
    m->tent = 0;
    m->cumprida = 0;
    return m;
}

struct mundo *cria_mundo()
{
    struct mundo *novo_mundo = malloc(sizeof(struct mundo));
    memset(novo_mundo, 0, sizeof(struct mundo));

    ini_mundo(novo_mundo);

    return novo_mundo;
}

void ini_mundo(struct mundo *w)
{
    w->nHerois = N_HEROIS;
    w->nHab = N_HABILIDADES;
    w->nBases = N_BASES;
    w->nMissoes = N_MISSOES;
    w->comp_v = N_COMPOSTOS_V;
    w->clk = 0;
    w->lef = fprio_cria();
    w->eventos = 0;
    w->local_w = ini_mun();
    w->local_w->x = N_TAMANHO_MUNDO;
    w->local_w->y = N_TAMANHO_MUNDO;
    struct heroi *h;
    int i;

    for (i = 0; i < N_HEROIS; i++)
    {
        h = cria_heroi();
        ini_heroi(i, h);
        w->t_herois[i] = h;
    }

    struct base *b;
    for (i = 0; i < N_BASES; i++)
    {
        b = cria_base();
        b = ini_base(i, b);
        w->t_base[i] = b;
    }

    struct missao *m;
    for (i = 0; i < N_MISSOES; i++)
    {
        m = cria_missao();
        m = ini_missao(i, m);
        w->t_missao[i] = m;
    }
}

void destroi_mundo(struct mundo *w)
{
    int i;

    if (!w)
        return;

    /*destroi todos os herois do mundo*/
    for (i = 0; i < N_HEROIS; i++)
    {
        if (w->t_herois[i])
        {
            cjto_destroi(w->t_herois[i]->hab);
            free(w->t_herois[i]);
            w->t_herois[i] = NULL;
        }
    }

    /*destroi todas as bases do mundo*/
    for (i = 0; i < N_BASES; i++)
    {
        if (w->t_base[i])
        {
            cjto_destroi(w->t_base[i]->id_Hp);
            fila_destroi(w->t_base[i]->esp);
            free(w->t_base[i]->local_b);
            w->t_base[i]->local_b = NULL;
            free(w->t_base[i]);
            w->t_base[i] = NULL;
        }
    }

    /*destroi todas as missoes do mundo*/
    for (i = 0; i < N_MISSOES; i++)
    {
        if (w->t_missao[i])
        {
            cjto_destroi(w->t_missao[i]->hab_n);
            free(w->t_missao[i]->local_m);
            w->t_missao[i]->local_m = NULL;
            free(w->t_missao[i]);
            w->t_missao[i] = NULL;
        }
    }

    /*destroi a lista de eventos futuros, o espaço e o mundo*/
    if (w)
    {
        if (w->lef)
        {
            fprio_destroi(w->lef);
            w->lef = NULL;
        }
    }

    free(w);
    w = NULL;
}
