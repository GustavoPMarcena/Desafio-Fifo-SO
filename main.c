#include <stdio.h>
#include <stdlib.h>

typedef struct nodo
{
    int num;
    struct nodo *proximo;
} Nodo;

typedef struct
{
    Nodo *inicio;
} Fila;

Fila *criarFila()
{
    Fila *F = (Fila *)malloc(sizeof(Fila));
    F->inicio = NULL;
    return F;
}

void inserir(Fila *F, int num)
{
    Nodo *novo = (Nodo *)malloc(sizeof(Nodo));
    novo->num = num;
    novo->proximo = NULL;
    if (F->inicio == NULL)
    {
        F->inicio = novo;
    }
    else
    {
        Nodo *aux = F->inicio;
        while (aux->proximo != NULL)
        {
            aux = aux->proximo;
        }
        aux->proximo = novo;
    }
}

int remover(Fila *F)
{
    Nodo *aux = F->inicio;
    int num = aux->num;
    F->inicio = aux->proximo;
    free(aux);
    return num;
}

int estaVazia(Fila *F)
{
    if (F->inicio == NULL)
    {
        return 1;
    }
    return 0;
}

int estaCheia(Fila *F, int tamanho)
{
    Nodo *aux = F->inicio;
    int quantidade = 0;
    while (aux != NULL)
    {
        quantidade++;
        aux = aux->proximo;
    }
    return quantidade >= tamanho;
}

int valorExistente(Fila *F, int valor)
{
    Nodo *aux = F->inicio;
    while (aux != NULL)
    {
        if (aux->num == valor)
        {
            return 1;
        }
        aux = aux->proximo;
    }
    return 0;
}

int controleDeFilaEQuantidadeDeFalhasDePagina(Fila *F, int tamanho, int valor)
{
    int falhasDePagina = 0;
    if (!valorExistente(F, valor))
    {
        if (!estaCheia(F, tamanho))
        {
            inserir(F, valor);
            falhasDePagina++;
        }
        else
        {
            remover(F);
            inserir(F, valor);
            falhasDePagina++;
        }
    }

    return falhasDePagina;
}

void imprimirFIla(Fila *F)
{
    Nodo *aux = F->inicio;
    printf("Estado final: ");
    while (aux != NULL)
    {
        printf("%i, ", aux->num);
        aux = aux->proximo;
    }
    printf("\n");
}

void imprimirSequencia(int *sequencia, int tamanhoSequencia)
{
    printf("Valores que serão inseridos: ");
    for (int i = 0; i < tamanhoSequencia; i++)
    {
        printf("%d ", sequencia[i]);
    }
    printf("\n");
}

void executarSequencia(int *sequencia, int tamanhoSequencia, int numMolduras)
{
    Fila *F = criarFila();
    int quantidadeFalhas = 0;
    
    imprimirSequencia(sequencia, tamanhoSequencia);

    for (int i = 0; i < tamanhoSequencia; i++)
    {
        quantidadeFalhas += controleDeFilaEQuantidadeDeFalhasDePagina(F, numMolduras, sequencia[i]);
    }

    printf("Quantidade de falhas de pagina: %d\n", quantidadeFalhas);
    imprimirFIla(F);
}

void imprimirLinha(char caractere, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("%c", caractere);
    }
    printf("\n");
}

void main()
{
    Fila *F = criarFila();
    int tamanho, num = 0, quantidadeFalhas = 0, dec;
    printf("Inserir manualmente ou verificar os desafios automaticamente? (1, 2)");
    scanf("%d", &dec);
    if (dec == 1)
    {
        printf("Digite a quantidade de molduras: ");
        scanf("%d", &tamanho);

        printf("\nA seguir, voce vai escrever uma quantidade de páginas que quer inserir\n");
        // Dessa forma, você deve inserir um por um os valores, como por exemplo o array
        // [4, 1, 2, 4, 5, 1, 2, 3, 4], e quando tiver terminado, insira -1 para parar o loop.
        while (1)
        {
            printf("Insira um numero (-1 para sair): ");
            scanf("%d", &num);

            if (num == -1)
                break;

            quantidadeFalhas += controleDeFilaEQuantidadeDeFalhasDePagina(F, tamanho, num);
        }

        printf("Quantidade de falhas de pagina: %d\n", quantidadeFalhas);
        imprimirFIla(F);
    } else if (dec == 2)
    {
        int sequencia01[] = {1, 3, 0, 3, 5, 6, 3, 1, 6, 1, 2};
        int sequencia02[] = {5, 6, 7, 8, 5, 6, 8, 9, 7, 6};
        int sequencia03[] = {0, 2, 1, 6, 4, 0, 1, 0, 2, 1, 4};
        int sequencia04[] = {9, 3, 4, 2, 5, 6, 4, 9, 7, 1, 3};
        int sequencia05[] = {0, 2, 1, 6, 4, 0, 1, 0, 2, 1, 4};
        int sequencia06[] = {8, 5, 7, 5, 4, 6, 8, 6, 1, 4, 8, 7};

        imprimirLinha('-', 40);
        printf("Entrada 01:\n");
        executarSequencia(sequencia01, 11, 3);
        
        imprimirLinha('-', 40);
        printf("Entrada 02:\n");
        executarSequencia(sequencia02, 10, 4);
        
        imprimirLinha('-', 40);
        printf("Entrada 03:\n");
        executarSequencia(sequencia03, 11, 3);
        
        imprimirLinha('-', 40);
        printf("Entrada 04:\n");
        executarSequencia(sequencia04, 11, 4);
        
        imprimirLinha('-', 40);
        printf("Entrada 05:\n");
        executarSequencia(sequencia05, 11, 3);
        
        imprimirLinha('-', 40);
        printf("Entrada 06:\n");
        executarSequencia(sequencia06, 12, 2);
    }
}