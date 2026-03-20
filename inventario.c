#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define CAPACIDADE_MAXIMA 10

int comparador_sequencial = 0; // comparadores para analise futuras
int comparador_binario = 0;

typedef struct
{
    int id;         // identificador do item
    char nome[50];  // nome do item
    char tipo[20];  // tipo de item
    int quantidade; // quantidade do mesmo item
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

// chamado de bublle sort, ele ordena meu vetor de acordo com a tabela ASCII
void ordenarVetor(MochilaVetor *m)
{
    for (int i = 0; i < m->quantidade - 1; i++)
    {
        for (int j = 0; j < m->quantidade - i - 1; j++)
        {
            if (strcmp(m->itens[j].nome, m->itens[j + 1].nome) > 0)
            {
                Item temp = m->itens[j];
                m->itens[j] = m->itens[j + 1];
                m->itens[j + 1] = temp;
            }
        }
    }
    printf("\n Mochila (vetor) ordenada por nome\n");
}

int buscaBinariaVetor(MochilaVetor *m, char *nome_buscado)
{
    comparador_binario = 0;
    int esquerda = 0;
    int direita = m->quantidade - 1;

    while (esquerda <= direita)
    {
        comparador_binario++;
        int meio = esquerda + (direita - esquerda) / 2;
        int res = strcmp(m->itens[meio].nome, nome_buscado);

        if (res == 0)
            return meio; // encontrou
        if (res < 0)
            esquerda = meio + 1; // busca na metade direita
        else
            direita = meio - 1; // busca na metade esquerda
    }
    return -1;
}

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
    comparador_sequencial = 0;
    No *atual = mochila->inicio;
    while (atual != NULL)
    {
        comparador_sequencial++;
        if (strcmp(atual->dado.nome, nome_buscado) == 0)
            return 1;
        atual = atual->proximo;
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
        printf("A busca falhou, o item %d  nao encontrado\n", id_para_remover);
        return 0;
    }

    if (anterior == NULL)
    {
        mochila->inicio = atual->proximo; // aogra a mochila aponta para o segundo item
    }
    else
    {
        anterior->proximo = atual->proximo;
    }

    printf("O item %s com id  %d foi destruido\n", atual->dado.nome, id_para_remover);
    free(atual); // item apagado
    mochila->quantidade--;

    return 1;
}
//
//
//
//

// parte da mochila estatica
int inserir_vetor(MochilaVetor *mochila, Item novo_item)
{
    // verifica se tem espaço
    if (mochila->quantidade >= CAPACIDADE_MAXIMA)
    {
        printf("A mochila esta cheia. Nao ha espaco para '%s'\n", novo_item.nome);
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
    comparador_sequencial = 0; // Reseta antes de começar
    for (int i = 0; i < mochila->quantidade; i++)
    {
        comparador_sequencial++; // Conta cada comparação do strcmp
        if (strcmp(mochila->itens[i].nome, nome_buscado) == 0)
        {
            return i;
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
        printf("ERRO: o item ID %d nao esta na mochila\n", id_para_remover);
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
    MochilaVetor minha_mochila;
    minha_mochila.quantidade = 0;

    MochilaLista mochila_magica;
    mochila_magica.inicio = NULL;
    mochila_magica.quantidade = 0;

    int opcao, estrutura;
    Item novo;
    char nome_busca[50];
    int id_remover;

    do
    {
        printf("\n===== MENU =====\n");
        printf("1 - Inserir item\n");
        printf("2 - Listar itens\n");
        printf("3 - Buscar item por nome\n");
        printf("4 - Remover item\n");
        printf("5 - Ordenar vetor (necessario para busca binaria)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        printf("\nEscolha a estrutura:\n");
        printf("1 - Mochila (Vetor)\n");
        printf("2 - Mochila Magica (Lista)\n");
        printf("Opcao: ");
        scanf("%d", &estrutura);

        switch (opcao)
        {
        case 1:
            printf("ID: ");
            scanf("%d", &novo.id);

            printf("Nome: ");
            scanf(" %[^\n]", novo.nome);

            printf("Tipo: ");
            scanf(" %[^\n]", novo.tipo);

            printf("Quantidade: ");
            scanf("%d", &novo.quantidade);

            if (estrutura == 1)
                inserir_vetor(&minha_mochila, novo);
            else
                inserir_lista_inicio(&mochila_magica, novo);
            break;

        case 2:
            if (estrutura == 1)
                listar_vetor(&minha_mochila);
            else
                listar_lista(&mochila_magica);
            break;

        case 3:
            printf("Digite o nome do item: ");
            scanf(" %[^\n]", nome_busca);

            if (estrutura == 1)
            {
                int pos = buscar_por_nome(&minha_mochila, nome_busca);
                printf("Comparacoes (busca sequencial): %d\n", comparador_sequencial);

                if (pos != -1)
                    printf("Encontrado na posicao %d\n", pos);

                if (minha_mochila.quantidade > 0)
                {
                    int pos_bin = buscaBinariaVetor(&minha_mochila, nome_busca);
                    printf("Comparacoes (busca binaria): %d\n", comparador_binario);

                    if (pos_bin != -1)
                        printf("Encontrado (binaria) na posicao %d\n", pos_bin);
                }
            }
            else
            {
                int achou = buscar_lista_nome(&mochila_magica, nome_busca);
                printf("Comparacoes (lista sequencial): %d\n", comparador_sequencial);

                if (achou)
                    printf("Item encontrado na lista!\n");
            }
            break;

        case 4:
            printf("Digite o ID para remover: ");
            scanf("%d", &id_remover);

            if (estrutura == 1)
                remover_vetor(&minha_mochila, id_remover);
            else
                remover_lista(&mochila_magica, id_remover);
            break;

        case 5:
            if (estrutura == 1)
                ordenarVetor(&minha_mochila);
            else
                printf("Ordenacao nao se aplica a lista\n");
            break;

        case 0:
            printf("Saindo...\n");
            break;

        default:
            printf("Opcao invalida\n");
        }

    } while (opcao != 0);

    return 0;
}