#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Sala
{
    char nome[30];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

Sala *criarSala(char *nome)
{
    Sala *novaSala = (Sala *)malloc(sizeof(Sala));
    if (novaSala != NULL)
    {
        strcpy(novaSala->nome, nome);
        novaSala->esquerda = NULL;
        novaSala->direita = NULL;
    }
    return novaSala;
}

void explorarSalas(Sala *atual)
{
    char escolha;

    while (atual != NULL)
    {
        printf("\nVoce esta na Sala: %s\n", atual->nome);

        if (atual->esquerda == NULL && atual->direita == NULL)
        {
            printf("voce chegou em uma sala sem saidas... \n");
            break;
        }
        printf("Escolha seu caminho: [e] esquerda ou [d] direita: ");
        scanf(" %c", &escolha);

        switch (escolha)
        {
        case 'e':
        case 'E':
            if (atual->esquerda != NULL)
            {
                atual = atual->esquerda;
            }
            else
            {
                printf("Caminho a esquerda esta bloqueado\n");
            }
            break;
        case 'd':
        case 'D':
            if (atual->direita != NULL)
            {
                atual = atual->direita;
            }
            else
            {
                printf("Caminho a direita esta bloqueado\n");
            }
            break;

        default:
            printf("--- ERRO DE DIGITACAO ---\n\n");
            break;
        }
    }
}

int main(){
    //criacao das salas da mansao
    Sala *hall = criarSala("hall de entrada");     //raiz da arvore o hall
    Sala *salaEstar = criarSala("sala de estar");  //esta a esquerda do hall
    Sala *cozinha = criarSala("cozinha");          //esta a direita do hall
    Sala *biblioteca = criarSala("biblioteca");    //esta a esquerda da sala de estar
    Sala *jardim = criarSala("jardim");            //esta a esquerda da cozinha
    Sala *sotao = criarSala("sotao abandonado");   //esta a direita da cozinha

    //montando conexoes
    hall->esquerda = salaEstar;
    hall->direita = cozinha;
    salaEstar->esquerda = biblioteca;
    cozinha->esquerda = jardim;
    cozinha->direita = sotao;

    explorarSalas(hall);

    return 0;
}