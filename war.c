#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define QTD_MISSOES 3
#define TAM_STRING 100

struct Territorio {
    char nome[TAM_STRING];
    int tropas;
    char cor[TAM_STRING];
};

struct Jogador {
    char nome[TAM_STRING];
    char *missao; 
    int territorios_conquistados;
};


void inicializarMissoes(char missoes[QTD_MISSOES][TAM_STRING]);
void listarMissoes(char missoes[QTD_MISSOES][TAM_STRING]);
void atacar(struct Territorio *atacante, struct Territorio *defensor) {
    if (atacante->tropas <= 1) {
        printf("%s não tem tropas suficientes para atacar.\n", atacante->nome);
        return;
    }
    if (defensor->tropas <= 0) {
        printf("%s já não tem tropas para defender.\n", defensor->nome);
        return;
    }

    for (; atacante->tropas > 1 && defensor->tropas > 0;) {
    int dadoAtq = (rand() % 6) + 1; // 1..6
    int dadoDef = (rand() % 6) + 1;
    printf("Atacante jogou um dado... %d\n", dadoAtq);
    printf("Defensor jogou um dado... %d\n", dadoDef);
    

    printf("%s ataca %s!\n", atacante->nome, defensor->nome);
    printf("Dado atacante = %d, Dado defensor = %d\n", dadoAtq, dadoDef);

    if (dadoAtq > dadoDef) {
        defensor->tropas--;
        printf("%s perdeu 1 tropa!\n", defensor->nome);
        strncpy(defensor->cor, atacante->cor, TAM_STRING - 1);
        defensor->cor[TAM_STRING - 1] = '\0';

    } else {
        printf("%s perdeu 1 tropa!\n", atacante->nome);
    }
}
      if (defensor -> tropas == 0) {
       int metade = atacante->tropas / 2;
        defensor->tropas = metade;
        atacante->tropas -= metade;

        printf("Transferidas %d tropas para %s.\n", metade, defensor->nome);
    }

    printf("Tropas finais: %s=%d, %s=%d\n\n",
           atacante->nome, atacante->tropas,
           defensor->nome, defensor->tropas);
    
}

void inicializarMissoes(char missoes[QTD_MISSOES][TAM_STRING]) {
    strcpy(missoes[0], "Conquistar 2 territorios seguidos");
    strcpy(missoes[1], "Eliminar todas as tropas da cor vermelha");
    strcpy(missoes[2], "Controlar dois continentes inteiros");
}

void listarMissoes(char missoes[QTD_MISSOES][TAM_STRING]) {
    for (int i = 0; i < QTD_MISSOES; i++) {
        printf("Missão %d: %s\n", i + 1, missoes[i]);
    }
}

void sortearMissoes(char missoes [QTD_MISSOES] [TAM_STRING]) {
    int indice = rand() % QTD_MISSOES;
    printf("Missão sorteada: %s\n", missoes[indice]);
}



int VerificarMissao(char* missao, struct Territorio* mapa, int tamanho) {
    int conquistados = 0;

    if (strcmp(missao, "Conquistar dois territórios seguidos") == 0) {
        for (int i = 0; i < tamanho; i++) {
           if (mapa[i].tropas > 0) {
                conquistados++;
           }
        }
     if (conquistados >= 2) {
        return 1;
     }
 } 

    if (strcmp(missao, "Eliminar todas as tropas da cor vermelha") == 0) {
        int encontrouVermelho = 0;

        for (int i = 0; i < tamanho; i++) {
            if ((strcmp(mapa[i].cor, "vermelho") == 0 ||
                 strcmp(mapa[i].cor, "vermelho") == 0) &&
                 mapa[i].tropas > 0) {
                encontrouVermelho = 1;
                break;
            }
        }
        if (!encontrouVermelho) {
            return 1;
        }  return 0;
    }
}


int main(){
    srand(time(NULL));
     
    struct Jogador jogador;
    jogador.territorios_conquistados = 0;

    char missoes[QTD_MISSOES][TAM_STRING];
    inicializarMissoes(missoes);

    printf("Missao sorteada: %s\n", missoes);

    printf("Digite o nome do jogador: ");


    int TotalContinentes;
    struct Territorio *Continentes;
    printf("Digite o número de territórios: ");
    scanf("%d", &TotalContinentes);
    getchar();

    Continentes = calloc(TotalContinentes, sizeof(struct Territorio));

    char* missaoJogador = malloc(TAM_STRING * sizeof(char));
    if (missaoJogador == NULL) {
       printf("Erro ao alocar memória");
    return 1;
    }

   for (int i = 0; i < TotalContinentes; i++) {
    printf("\n--- Cadastro do Território %d ---\n", i + 1);


    printf("Digite o nome do Território: ");
          fgets(Continentes[i].nome, TAM_STRING, stdin);
    Continentes[i].nome[strcspn(Continentes[i].nome, "\n")] = '\0';

    printf("Digite o numero de tropas:  ");
          scanf("%d", &Continentes[i].tropas);
    getchar();

    printf("Digite a cor do exército: ");
         fgets(Continentes[i].cor, TAM_STRING, stdin);
    Continentes[i].cor[strcspn(Continentes[i].cor, "\n")] = '\0';
    }

   int iAtacante, iDefensor;
printf("\nEscolha o índice do atacante: ");
scanf("%d", &iAtacante);
printf("Escolha o índice do defensor: ");
scanf("%d", &iDefensor);

iAtacante --;
iDefensor --;

   if (iAtacante >= 0 &&
    iDefensor >= 0 &&
    iAtacante != iDefensor) {
    atacar(&Continentes[iAtacante], &Continentes[iDefensor]);
}  else {
    printf("Índices inválidos!\n");
}


if (VerificarMissao(missaoJogador, Continentes, TotalContinentes)) {
    printf("Missão concluida! \n");
} else {
    printf("Missao ainda nao cumprida \n");
}
    
    free(missaoJogador);
    free(Continentes);

    

    return 0;
}