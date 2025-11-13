#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "eventos.h"
#include "entidades.h"
#include "fprio.h"

void inicia_hero(struct mundo *w)
{

    int i, t;
    struct evento *evento;
    struct heroi *h;

    w->eventos++;

    for (i = 0; i < N_HEROIS; i++)
    {
        h = cria_heroi();
        ini_heroi(i, h);

        w->t_herois[i] = h;

        t = random(0, 4320);
        evento = cria_evento(t, i, w->t_herois[i]->bas, 0);
        if (fprio_insere(w->lef, evento, 1, t) == -1)
        {
            printf("%6d: ERRO AO ADICIONAR CHEGA NA LEF", t);
            printf("\n");
        }
    }
}

void inicia_base(struct mundo *w)
{
    int i;
    struct base *b;
    for (i = 0; i < N_BASES; i++)
    {
        b = cria_base();
        ini_base(i, b);
        w->t_base[i] = b;
    }
}

void inicia_missao(struct mundo *w)
{
    int t;
    struct missao *m;
    struct evento *evento;
    for (int i = 0; i < N_MISSOES; i++)
    {
        t = random(0, T_FIM_DO_MUNDO);
        m = cria_missao();
        ini_missao(i, m);
        w->t_missao[i] = m;
        evento = cria_evento(t, 0, 0, i);
        if (fprio_insere(w->lef, evento, 9, t) == -1)
        {
            printf("%6d: ERRO AO ADICIONAR MISSAO NA LEF", t);
            printf("\n");
        }
    }
}

void primeiros_eve(struct mundo *w)
{
    struct evento *evento = malloc(sizeof(struct evento));
    inicia_hero(w);
    inicia_base(w);
    inicia_missao(w);
    evento = cria_evento(T_FIM_DO_MUNDO, 0, 0, 0);
    if (fprio_insere(w->lef, evento, 10, T_FIM_DO_MUNDO) == -1)
        printf("ERRO AO INSERIR EVENTO FIM DO MUNDO");
}

void *cria_evento(int t, int id_h, int id_b, int id_m)
{

    struct evento *evento = malloc(sizeof(struct evento));

    evento->tempo = t;
    evento->inf_2 = id_h;
    evento->inf_3 = id_b;
    evento->inf_4 = id_m;

    return evento;
}

void destroi_evento(struct evento *evento)
{
    free(evento);
    evento = NULL;
}

void ordenavet(struct base_dis basesdis[], int n)
{
    int i, j;
    struct base_dis aux;
    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (basesdis[i].dist > basesdis[j].dist)
            {
                aux = basesdis[i];
                basesdis[i] = basesdis[j];
                basesdis[j] = aux;
            }
        }
    }
}

int deslocamento(struct coor *a, struct coor *b)
{
    double des;

    des = sqrt(pow(b->x - a->x, 2) + pow(b->y - a->y, 2));

    return (int)round(des);
}

void chega(struct mundo *w, int t, int id_h, int id_b)
{
    w->eventos++;
    int espera = 0;
    struct evento *evento;
    if (w->t_herois[id_h]->status)
    {
        w->t_herois[id_h]->bas = id_b;
        if ((w->t_base[id_b]->id_Hp->num < w->t_base[id_b]->tam) && !(fila_tamanho(w->t_base[id_b]->esp)))
            espera = 1;
        else
        {
            if (w->t_herois[id_h]->pac > 10 * w->t_base[id_b]->esp->num)
                espera = 1;
        }
    }
    evento = cria_evento(t, id_h, id_b, 0);
    if (espera)
    {
        if (fprio_insere(w->lef, evento, 2, t) == -1)

        {
            printf("%6d: ERRO AO ADICIONAR ESPERA NA LEF", t);
            printf("\n");
        }
        else
        {
            printf("%6d: CHEGA HEROI %2d BASE %d (%2d/%2d) ESPERA", t, id_h, id_b, cjto_card(w->t_base[id_b]->id_Hp), w->t_base[id_b]->tam);
            printf("\n");
        }
    }
    else
    {
        if (fprio_insere(w->lef, evento, 3, t) == -1)
        {
            printf("%6d: ERRO AO ADICIONAR DESISTE NA LEF", t);
            printf("\n");
        }
        else
        {
            printf("%6d: CHEGA HEROI %2d BASE %d (%2d/%2d) DESISTE", t, id_h, id_b, cjto_card(w->t_base[id_b]->id_Hp), w->t_base[id_b]->tam);
            printf("\n");
        }
    }
}

void espera(struct mundo *w, int t, int id_h, int id_b)
{
    int temp = id_h;
    int *h = malloc(sizeof(int));
    *h = temp;

    w->eventos++;
    if (w->t_herois[id_h]->status)

    {

        struct evento *evento;
        fila_insere(w->t_base[id_b]->esp, h);
        

        // Adiciona na LEF o evento avisa
        evento = cria_evento(t, 0, id_b, 0);
        if (fprio_insere(w->lef, evento, 4, t) == -1)
        {
            printf("%6d: ERRO AO ADICIONAR AVISA NA LEF", t);
            printf("\n");
        }
        else
        {
            printf("%6d: ESPERA HEROI %2d BASE %d (%2d)", t, id_h, id_b, fila_tamanho(w->t_base[id_b]->esp));
            printf("\n");
        }
    }
    
}

void desiste(struct mundo *w, int t, int id_h, int id_b)
{
    w->eventos++;
    struct evento *evento;
    int D = -1;
    if (w->t_herois[id_h]->status)
    {
        D = random(0, N_BASES - 1);
        // Inserir evento viaja na LEF
        evento = cria_evento(t, id_h, D, 0);
        if (fprio_insere(w->lef, evento, 7, t) == -1)
        {
            printf("%6d: ERRO AO ADICIONAR VIAJA NA LEF", t);
            printf("\n");
        }
        else
        {
            printf("%6d: DESIST HEROI %2d BASE %d", t, id_h, id_b);
            printf("\n");
        }
    }
}

void avisa(struct mundo *w, int t, int id_b)
{
    w->eventos++;
    struct evento *evento;
    int item;
    

    printf("%6d: AVISA O PORTEIRO BASE %d (%d/%d) FILA [ ", t, id_b, cjto_card(w->t_base[id_b]->id_Hp), w->t_base[id_b]->tam);
    fila_imprime(w->t_base[id_b]->esp);
    printf(" ]\n");

    while ((w->t_base[id_b]->id_Hp->num < w->t_base[id_b]->tam) && (fila_tamanho(w->t_base[id_b]->esp)))
    {

        item = *(int *)fila_retira(w->t_base[id_b]->esp);
       

        cjto_insere(w->t_base[id_b]->id_Hp, item);

        evento = cria_evento(t, item, id_b, 0);
        if (fprio_insere(w->lef, evento, 5, t) == -1)
        {
            printf("%6d: ERRO AO ADICIONAR ENTRA NA LEF", t);
            printf("\n");
        }
        else
        {
            printf("%6d: AVISA PORTEIRO BASE %d ADMITE %2d", t, id_b, item);
            printf("\n");
        }
    }
}

void entra(struct mundo *w, int t, int id_h, int id_b)
{
    w->eventos++;
    struct evento *evento;
    int tpb;
    int i = random(1, 20);
    tpb = 15 + w->t_herois[id_h]->pac * i;
    evento = cria_evento(t + tpb, id_h, id_b, 0);
    // Cria e insere o evento SAI na LEF
    if (fprio_insere(w->lef, evento, 6, t + tpb) == -1)
    {
        printf("%6d: ERRO AO ADICIONAR SAI NA LEF", t);
        printf("\n");
    }
    else
    {
        printf("%6d: ENTRA HEROI %2d BASE %d (%2d/%2d) SAI %d", t, id_h, id_b, cjto_card(w->t_base[id_b]->id_Hp), w->t_base[id_b]->tam, t + tpb);
        printf("\n");
    }
}

void sai(struct mundo *w, int t, int id_h, int id_b)
{
    w->eventos++;
    struct evento *evento;
    int D;
    cjto_retira(w->t_base[id_b]->id_Hp, id_h);
    D = random(0, N_BASES - 1);
    printf("%6d: SAI HEROI %2d BASE %d (%2d/%2d)", t, id_h, id_b, cjto_card(w->t_base[id_b]->id_Hp), w->t_base[id_b]->tam);
    printf("\n");

    // Insere na LEF, VIAJA e AVISA
    evento = cria_evento(t, id_h, id_b, D);
    if (fprio_insere(w->lef, evento, 7, t) == -1)
    {
        printf("%6d: ERRO AO ADICIONAR VIAJA NA LEF", t);
        printf("\n");
    }
    evento = cria_evento(t, 0, id_b, 0);
    if (fprio_insere(w->lef, evento, 4, t) == -1)
    {
        printf("%6d: ERRO AO ADICIONAR AVISA NA LEF", t);
        printf("\n");
    }
}

void viaja(struct mundo *w, int t, int id_h, int id_b, int id_D)
{
    w->eventos++;
    struct evento *evento;
    int dist;
    double tempo;
    int tempo_t;
    dist = deslocamento(w->t_base[id_b]->local_b, w->t_base[id_D]->local_b);
    tempo = dist / w->t_herois[id_h]->vel;
    tempo_t = (int)round(tempo);
    // Insere o evento chega
    evento = cria_evento(t + tempo_t, id_h, id_D, 0);
    if (fprio_insere(w->lef, evento, 1, t + tempo_t) == -1)
    {
        printf("%6d: ERRO AO ADICIONAR CHEGA NA LEF", t);
        printf("\n");
    }
    else
    {
        printf("%6d: VIAJA HEROI %2d BASE %d BASE %d DIST %d VEL %d CHEGA %d", t, id_h, id_b, id_D, dist, w->t_herois[id_h]->vel, t + tempo_t);
        printf("\n");
    }
}

void morre(struct mundo *w, int t, int id_h, int id_b, int id_m)
{
    w->eventos++;
    struct evento *evento;
    cjto_retira(w->t_base[id_b]->id_Hp, id_h);
    w->t_herois[id_h]->status = false;
    // Insere AVISA na LEF
    evento = cria_evento(t, 0, id_b, 0);
    if (fprio_insere(w->lef, evento, 4, t) == -1)
    {
        printf("%6d: ERRO AO ADICIONAR AVISA NA LEF", t);
        printf("\n");
    }
    else
    {
        printf("%6d: MORRE HEROI %2d MISSAO %d", t, id_h, id_m);
        printf("\n");
    }
}

void missao(struct mundo *w, int t, int id_m)
{
    w->eventos++;
    struct evento *evento;
    w->t_missao[id_m]->tent++;

    struct base_dis basesdis[N_BASES];

    int i, j;
    int esta = 0;
    int bpm = -1;
    struct cjto_t *cjto_hab;
    

    printf("%6d: MISSAO %d TENT %d HAB REQ: [ ", t, id_m, w->t_missao[id_m]->tent);
    cjto_imprime(w->t_missao[id_m]->hab_n);
    printf(" ]\n");

    for (i = 0; i < N_BASES; i++)
    {
        basesdis[i].id_b = i;
        basesdis[i].dist = deslocamento(w->t_missao[id_m]->local_m, w->t_base[i]->local_b);
    }

    ordenavet(basesdis, N_BASES);
    bpm = basesdis[0].id_b;
    for (i = 0; i < N_BASES; i++)
    {
        cjto_hab = cjto_cria(N_HABILIDADES);

        printf("%6d: MISSAO %d BASE %d DIST %d HEROIS [ ", t, id_m, basesdis[i].id_b, basesdis[i].dist);
        cjto_imprime(w->t_base[basesdis[i].id_b]->id_Hp);
        printf(" ]\n");

        for (j = 0; j < N_HEROIS; j++)
        {
            esta = cjto_pertence(w->t_base[basesdis[i].id_b]->id_Hp, j);
            if (esta == 1)
            {
                printf("%6d: MISSAO %d HAB HEROI %2d: [ ", t, id_m, j);
                cjto_imprime(w->t_herois[j]->hab);
                printf(" ]\n");
                struct cjto_t *temp_cjto = cjto_uniao(cjto_hab, w->t_herois[j]->hab);
                cjto_destroi(cjto_hab); // LIBERA O CONJUNTO ANTIGO
                cjto_hab = temp_cjto;
            }
        }

        if (cjto_contem(cjto_hab, w->t_missao[id_m]->hab_n))
        {
            w->t_missao[id_m]->cumprida = 1;
            w->t_base[basesdis[i].id_b]->missoes_c++;
            w->missoes_cumpridas++;
            printf("%6d: MISSÃO %d CUMPRIDA BASE %d HABS [", t, id_m, basesdis[i].id_b);
            cjto_imprime(cjto_hab);
            printf("]\n");

            for (j = 0; j < N_HEROIS; j++)
            {
                if (cjto_pertence(w->t_base[basesdis[i].id_b]->id_Hp, j) == 1)
                {
                    w->t_herois[j]->xp_h += 1;
                }
            }
            return;
        }
    }
    int mais_exp = -1;
    int maior_xp = -1;
    for (i = 0; i < N_BASES; i++)
    {
        if (w->comp_v > 0 && t % 2500 == 0 && cjto_card(w->t_base[basesdis[i].id_b]->id_Hp) > 0)
        {

            w->comp_v--;
            w->t_base[basesdis[i].id_b]->missoes_c++;
            w->missoes_cumpridas++;
            w->t_missao[id_m]->cumprida = 1;
            for (j = 0; j < N_HEROIS; j++)
            {
                esta = cjto_pertence(w->t_base[basesdis[i].id_b]->id_Hp, j);
                if (esta == 1)
                {
                    if (maior_xp < w->t_herois[j]->xp_h)
                    {
                        mais_exp = j;
                        maior_xp = w->t_herois[j]->xp_h;
                    }
                }
            }
            for (j = 0; j < N_HEROIS; j++)
            {
                esta = cjto_pertence(w->t_base[basesdis[i].id_b]->id_Hp, j);
                if (esta == 1 && j != mais_exp)
                {
                    w->t_herois[j]->xp_h += 1;
                }
            }
            // Adiciona na LEF o evento MORRE w->t_herois[mais_exp]->id_h
            evento = cria_evento(t, mais_exp, bpm, id_m);
            if (fprio_insere(w->lef, evento, 8, t) == -1)
            {
                printf("%6d: ERRO AO ADICIONAR MORRE NA LEF", t);
                printf("\n");
            }
            return;
        }
    }

    // cria evento MISSAO (T + 24*60, M) para o dia seguinte
    evento = cria_evento(t + 24 * 60, 0, 0, id_m);
    if (fprio_insere(w->lef, evento, 9, t + 24 * 60) == -1)
    {
        printf("%6d: ERRO AO ADICIONAR MISSAO NA LEF", t);
        printf("\n");
    }
    else
    {
        printf("%6d: MISSAO %d IMPOSSIVEL", t, id_m);
        printf("\n");
    }
}

void fim(struct mundo *w)
{
    float taxa;
    int i;
    w->eventos++;
    w->clk = T_FIM_DO_MUNDO;
    printf("%6d: FIM\n", w->clk);
    printf("\n");

    for (i = 0; i < N_HEROIS; i++)
    {
        if (w->t_herois[i]->status == 1)
        {
            printf("HEROI %2d VIVO  PAC %3d VEL %4d EXP %4d HABS [ ", w->t_herois[i]->id_h, w->t_herois[i]->pac, w->t_herois[i]->vel, w->t_herois[i]->xp_h);
            cjto_imprime(w->t_herois[i]->hab);
            printf(" ]\n");
        }
        else
        {
            printf("HEROI %2d MORTO PAC %3d VEL %4d EXP %4d HABS [ ", w->t_herois[i]->id_h, w->t_herois[i]->pac, w->t_herois[i]->vel, w->t_herois[i]->xp_h);
            cjto_imprime(w->t_herois[i]->hab);
            printf(" ]\n");
        }
    }
    for (i = 0; i < N_BASES; i++)
    {
        printf("BASE %2d LOT %2d MISSOES %d\n", w->t_base[i]->id_b, w->t_base[i]->tam, w->t_base[i]->missoes_c);
        printf("\n");
    }

    taxa = (float)w->missoes_cumpridas / N_MISSOES * 100;
    printf("EVENTOS TRATADOS: %d \n", w->eventos);
    printf("MISSOES CUMPRIDAS: %d/%d (%.1f%%)", w->missoes_cumpridas, N_MISSOES, taxa);
    // printf("TENTATIVAS/MISSAO: MIN %d, MAX %d, MEDIA %.1f");
    // printf("TAXA MORTALIDADE: %.1f%%");
}