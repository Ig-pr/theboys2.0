#ifndef ENTIDADES
#define ENTIDADES

#include "fila.h"
#include "conjunto.h"
#include "definicoes.h"

struct heroi
{
    int id_h;
    int xp_h;
    int pac;
    int vel;
    struct cjto_t *hab;
    int bas;
    int status;
};

struct coor
{
    int x;
    int y;
};

struct base
{
    //ID da base
    int id_b;
    //Número máximo de heróis
    int tam;
    //Conjunto dos IDs dos heróis na base
    struct cjto_t *id_Hp;
    //Fila onde os heróis esperam para poder entrar na base
    struct fila_t *esp;
    //Localização (x, y)
    struct coor *local_b;
    int missoes_c;
};

struct missao
{
    int id_mis;
    struct cjto_t *hab_n;
    struct coor *local_m;
    int cumprida;
    int tent;
};

struct mundo
{
    int nHerois;
    struct heroi *t_herois[N_HEROIS];
    int nBases;
    struct base *t_base[N_BASES];
    int nMissoes;
    struct missao *t_missao[N_MISSOES];
    int nHab;
    int comp_v;
    struct coor *local_w;
    int clk;
    struct fprio_t *lef;
    int eventos;
    int missoes_cumpridas;
};

struct evento
{
    int tempo;
    int inf_2;
    int inf_3;
    int inf_4;
};

int random(int min, int max);



struct heroi *cria_heroi();

void ini_heroi(int i, struct heroi *h);

struct base *cria_base();

struct base *ini_base(int i, struct base *b);

struct missao *cria_missao();

struct missao *ini_missao(int i, struct missao *m);

struct mundo *cria_mundo();

void ini_mundo(struct mundo *w);

void destroi_evento(struct evento *evento);

void destroi_mundo(struct mundo *w);

#endif