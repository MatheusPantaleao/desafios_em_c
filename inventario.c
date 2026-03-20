#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define CAPACIDADE_MAXIMA 10

typedef struct
{
    int id;        // identificador do item
    char nome[50]; // nome do item
} Item;

typedef struct
{
    Item itens[CAPACIDADE_MAXIMA]; // local onde sera amazenado os itens
    int quantidade;                // quantidade guardado
} MochilaVetor;

typedef struct No
{
    Item dado;          // o item em si (ID e NOME)
    struct No *proximo; // ponteiro para proxima capsula
} No;

typedef struct
{
    No *inicio;     // ponteiro aponta pra primeira capsula
    int quantidade; // quantidade de itens
} MochilaLista;

//
//
//

// parte da mochila dinamica
int inserir_lista_inicio(MochilaLista *mochila, Item novo_item)
{
    No *novo_no = (No *)malloc(sizeof(No));

    // verifica se tem memoria disponivel
    if (novo_no == NULL)
    {
        printf("ERRO de memoria, nao foi possivel criar o item '%s' \n", novo_item.nome);
        return 0;
    }
    novo_no->dado = novo_item;          // colocando item dentro da capsula
    novo_no->proximo = mochila->inicio; // aponta para o antigo inicio da capsula
    mochila->inicio = novo_no;          // aponta para o novo no como sendo o primeiro
    mochila->quantidade++;              // atualizando a quantidade de itens da mochila

    printf("item '%s' adicionado na mochila magica (lista)\n", novo_item.nome);
    return 1;
}

void listar_lista(MochilaLista *mochila)
{
    printf("\n--- inventario da mochila magica ---\n");

    if (mochila->inicio == NULL)
    {
        printf("a mochila magica esta vazia\n");
        return;
    }

    No *atual = mochila->inicio;
    int contador_slot = 1;

    while (atual != NULL)
    {
        printf("slot magico %d: [ID: %d] %s\n", contador_slot, atual->dado.id, atual->dado.nome);
        atual = atual->proximo;
        contador_slot++;
    }
    printf("--- FIM DA MOCHILA MAGICA ---\n");
}

int buscar_lista_nome(MochilaLista *mochila, const char *nome_buscado)
{
    No *atual = mochila->inicio;
    int contador_slot = 1;

    while (atual != NULL)
    {
        if (strcmp(atual->dado.nome, nome_buscado) == 0)
        {
            printf("\n busca magica: sucesso! '%s' encontrado no slot magico %d (ID: %d)\n", nome_buscado, contador_slot, atual->dado.id);
            return 1;
        }
        // se nao for o item buscado, ele pula para o proximo
        atual = atual->proximo;
        contador_slot++;
    }
    printf("\n busca magica: o item '%s' nao esta na mochila magica\n", nome_buscado);
    return 0;
}

int remover_lista(MochilaLista *mochila, int id_para_remover)
{
    if (mochila->inicio == NULL)
    {
        printf("A mochila ja esta vazia\n");
        return 0;
    }
    No *atual = mochila->inicio;
    No *anterior = NULL;

    // procura a capsula que tem o id que buscamos
    while (atual != NULL && atual->dado.id != id_para_remover)
    {
        anterior = atual;       // o anterior da um passo e fica onde o atual estava
        atual = atual->proximo; // o atual pula para a proxima capsula
    }
    // se o atual virar NULL , o item nao foi encontrado
    if (atual == NULL)
    {
        printf("A busca falhou, o item %d  nao encontrado", id_para_remover);
        return 0;
    }
    if (anterior == NULL)
    {
        mochila->inicio = atual->proximo; // aogra a mochila aponta para o segundo item
    }
    printf("O item %s com id  %d foi destruido", atual->dado.nome, id_para_remover);
    free(atual);  //item apagado
    mochila->quantidade--;

    return 1;
}
//
//
//

// parte da mochila estatica
int inserir_vetor(MochilaVetor *mochila, Item novo_item)
{
    // verifica se tem espaço
    if (mochila->quantidade >= CAPACIDADE_MAXIMA)
    {
        printf("A mochila esta cheia. Nao ha espaco para '%s\n", novo_item.nome);
        return 0;
    }
    // insere na pisiçao vazia
    mochila->itens[mochila->quantidade] = novo_item;
    // aumenta o contador de itens
    mochila->quantidade++;

    printf("Item '%s' inserido com sucesso\n", novo_item.nome);
    return 1;
}

void listar_vetor(MochilaVetor *mochila)
{
    printf("\n--- Inventario ---\n");

    if (mochila->quantidade == 0)
    {
        printf("A mochila esta vazia\n");
        return;
    }
    for (int i = 0; i < mochila->quantidade; i++)
    {
        printf("Slot %d: [ID: %d] %s\n", i + 1, mochila->itens[i].id, mochila->itens[i].nome);
    }
    printf("--- FIM DA MOCHILA ---\n");
}

int buscar_por_nome(MochilaVetor *mochila, const char *nome_buscado)
{
    for (int i = 0; i < mochila->quantidade; i++)
    {
        if (strcmp(mochila->itens[i].nome, nome_buscado) == 0)
        {
            printf("\nSucesso '%s' foi encontrado no slot %d (ID: %d)\n", nome_buscado, i + 1, mochila->itens[i].id);
            return i; // retorna a posiçao do item
        }
    }

    printf("\n item '%s' nao esta na mochila\n", nome_buscado);
    return -1; // return -1 retorna é padrao para "indice nao encontrado"
}

int remover_vetor(MochilaVetor *mochila, int id_para_remover)
{
    int indice_buraco = -1;

    // busca por qual slot esta o item
    for (int i = 0; i < mochila->quantidade; i++)
    {
        if (mochila->itens[i].id == id_para_remover)
        {
            indice_buraco = i;
            break;
        }
    }

    if (indice_buraco == -1)
    {
        printf("ERRO: o item ID %d nao esta na mochila", id_para_remover);
        return 0;
    }

    // se o item que vamos apagar nao for o ultimo da mochila
    if (indice_buraco != mochila->quantidade - 1)
    {
        int ultimo_indice = mochila->quantidade - 1;
        // copia o ultimo item por cima do item que queremos apagar
        mochila->itens[indice_buraco] = mochila->itens[ultimo_indice];
    }
    // faz com que o ultimo slot original seja esquecido
    mochila->quantidade--;
    return 1;
}

int main()
{
    // criação da mochila e inicializando vazia
    MochilaVetor minha_mochila;
    minha_mochila.quantidade = 0;

    MochilaLista mochila_magica;
    mochila_magica.inicio = NULL;
    mochila_magica.quantidade = 0;

    // criaçao dos itens
    Item item1 = {101, "espada de madeira"};
    Item item2 = {102, "pocao de cura"};
    Item item3 = {103, "escudo de madeira"};

    printf("--- Pegando itens ---\n");
    inserir_vetor(&minha_mochila, item1);
    inserir_vetor(&minha_mochila, item2);
    inserir_vetor(&minha_mochila, item3);

    listar_vetor(&minha_mochila);

    buscar_por_nome(&minha_mochila, "pocao de cura");
    buscar_por_nome(&minha_mochila, "cajado simples");

    printf("\n--- bebendo a pocao ---\n");
    remover_vetor(&minha_mochila, 102);
    listar_vetor(&minha_mochila);

    printf("\n\n-----APARTIR DAQUI REFERENTE A MOCHILA MAGICA-----\n\n");

    printf("\n---guardando itens na mochila magica---\n");
    inserir_lista_inicio(&mochila_magica, item1);
    inserir_lista_inicio(&mochila_magica, item2);
    inserir_lista_inicio(&mochila_magica, item3);

    listar_lista(&mochila_magica);

    buscar_lista_nome(&mochila_magica, "pocao de cura");
    buscar_lista_nome(&mochila_magica, "anel de forca");
    remover_lista(&mochila_magica, 102);
    listar_lista(&mochila_magica);

    return 0;
}
