// programa principal do projeto "The Boys - 2024/2"
// Autor: xxxxx, GRR xxxxxx

// seus #includes vão aqui

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fprio.h"
#include "entidades.h"
#include "eventos.h"

// seus #defines vão aqui

#define T_FIM_DO_MUNDO 525600
#define N_TAMANHO_MUNDO 20000
#define N_HABILIDADES 10
#define N_HEROIS (N_HABILIDADES * 5)
#define N_BASES (N_HEROIS / 5)
#define N_MISSOES (T_FIM_DO_MUNDO / 100)
#define N_COMPOSTOS_V (N_HABILIDADES * 3)

// minimize o uso de variáveis globais

// programa principal
int main ()
{
  // iniciar o mundo
  srand(time(NULL));
  struct mundo *w;
  w = cria_mundo();

  primeiros_eve(w);
  struct evento *evento;
  int tipo;

  // executar o laço de simulação

   while (w->clk < T_FIM_DO_MUNDO)
  {
    evento = fprio_retira(w->lef, &tipo, &w->clk);

    

    switch (tipo)
    {
    case 1:
      chega(w, evento->tempo, evento->inf_2, evento->inf_3);
      destroi_evento(evento); 
      break;
    case 2:
      espera(w, evento->tempo, evento->inf_2, evento->inf_3);
      destroi_evento(evento); 
      break;
    case 3:
      desiste(w, evento->tempo, evento->inf_2, evento->inf_3);
      destroi_evento(evento); 
      break;
    case 4:
      avisa(w, evento->tempo, evento->inf_3);
      destroi_evento(evento); 
      break;
    case 5:
      entra(w, evento->tempo, evento->inf_2, evento->inf_3);
      destroi_evento(evento); 
      break;
    case 6:
      sai(w, evento->tempo, evento->inf_2, evento->inf_3);
      destroi_evento(evento); 
      break;
    case 7:
      viaja(w, evento->tempo, evento->inf_2, evento->inf_3, evento->inf_4);
      destroi_evento(evento); 
      break;
    case 8:
      morre(w, evento->tempo, evento->inf_2, evento->inf_3, evento->inf_4);
      destroi_evento(evento); 
      break;
    case 9:
      missao(w, evento->tempo, evento->inf_4);
      destroi_evento(evento); 
      break;
    case 10:
      fim(w);
      destroi_evento(evento); 
      break;
    }
  }

  // destruir o mundo

    destroi_mundo(w);

  return (0) ;
}

