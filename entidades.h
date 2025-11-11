#include "definicoes.h"

struct heroi
{
    int id_h;
    int xp_h;
    int pac;
    int vel;
    int hab;
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