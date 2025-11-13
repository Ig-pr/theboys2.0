#ifndef EVENTOS
#define EVENTOS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "entidades.h"

struct base_dis
{
    int id_b;
    int dist;
};

void inicia_hero(struct mundo *w);

void primeiros_eve(struct mundo *w);

void *cria_evento(int t, int id_h, int id_b, int id_m);

int deslocamento(struct coor *a, struct coor *b);

void chega(struct mundo *w, int t, int id_h, int id_b);

void espera(struct mundo *w, int t, int id_h, int id_b);

void desiste(struct mundo *w, int t, int id_h, int id_b);

void avisa(struct mundo *w, int t, int id_b);

void entra(struct mundo *w, int t, int id_h, int id_b);

void sai(struct mundo *w, int t, int id_h, int id_b);

void viaja(struct mundo *w, int t, int id_h, int id_b, int id_D);

void morre(struct mundo *w, int t, int id_h, int id_b, int id_m);

void missao(struct mundo *w, int t, int id_m);

void fim(struct mundo *w);

#endif