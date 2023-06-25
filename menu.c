#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <stdbool.h>
#include "main.h"

void listarMarcas(Produto *produtos, int numProdutos) {
    printf("\n--- Lista de Marcas ---\n");

    // Utilizaremos um vetor auxiliar para armazenar as marcas únicas
    char marcas[100][50]; // Supomos que haverá no máximo 100 marcas, com até 50 caracteres cada
    int numMarcas = 0; // Variável para contar o número de marcas diferentes encontradas

    // Percorre os produtos e adiciona as marcas ao vetor auxiliar, evitando duplicações
    int i;
    for (i = 0; i < numProdutos; i++) {
        bool marcaRepetida = false;
        int j;
        for (j = 0; j < numMarcas; j++) {
            if (strcmp(marcas[j], produtos[i].fabricante.marca) == 0) {
                marcaRepetida = true;
                break;
            }
        }
        if (!marcaRepetida) {
            strcpy(marcas[numMarcas], produtos[i].fabricante.marca);
            numMarcas++;
        }
    }

    // Mostra marcas encontradas
    for (i = 0; i < numMarcas; i++) {
        printf("%d. %s\n", i + 1, marcas[i]);
    }
}

// Função para listar todos os produtos de um determinado estado (UF)
void listarProdutosEstado(Produto *produtos, int numProdutos, const char *uf) {
    printf("\n--- Produtos do Estado %s ---\n", uf);

    // Percorremos os produtos e exibimos os que possuem a UF desejada
    int i;
    for (i = 0; i < numProdutos; i++) {
        if (strcmp(produtos[i].fabricante.uf, uf) == 0) {
            printf("Produto %d\n", i + 1);
            printf("Descrição: %s\n", produtos[i].descricao);
            printf("Peso: %.2f\n", produtos[i].peso);
            printf("Valor de Compra: R$ %.2f\n", produtos[i].valorCompra);
            printf("Valor de Venda: R$ %.2f\n", produtos[i].valorVenda);
            printf("Percentual de Lucro: %.2f%%\n", produtos[i].percentualLucro);
            printf("Fabricante:\n");
            printf("Marca: %s\n", produtos[i].fabricante.marca);
            printf("Site: %s\n", produtos[i].fabricante.site);
            printf("Telefone: %s\n", produtos[i].fabricante.telefone);
            printf("UF: %s\n", produtos[i].fabricante.uf);
            printf("\n");
        }
    }
}

// Função para exibir o estado que possui o produto mais caro
void exibirEstadoProdutoMaisCaro(Produto *produtos, int numProdutos) {
    printf("\n--- Estado com o Produto Mais Caro ---\n");

    float maiorValor = 0;
    char estadoMaisCaro[3] = "";

    // Percorremos os produtos e atualizamos o maior valor e o estado correspondente
    int i;
    for (i = 0; i < numProdutos; i++) {
        if (produtos[i].valorVenda > maiorValor) {
            maiorValor = produtos[i].valorVenda;
            strcpy(estadoMaisCaro, produtos[i].fabricante.uf);
        }
    }

    if (maiorValor > 0) {
        printf("O produto mais caro está no estado %s, com valor de venda R$ %.2f\n", estadoMaisCaro, maiorValor);
    } else {
        printf("Não há produtos cadastrados.\n");
    }
}

void listarFabricanteProdutoMaisBarato(Produto *produtos, int numProdutos) {
    if (numProdutos == 0) {
        printf("Nenhum produto encontrado.\n");
        return;
    }

    int indiceMaisBarato = 0;
    float valorMaisBarato = produtos[0].valorVenda;

    int i;
	for (i = 1; i < numProdutos; i++) {
        if (produtos[i].valorVenda < valorMaisBarato) {
            indiceMaisBarato = i;
            valorMaisBarato = produtos[i].valorVenda;
        }
    }

    Fabricante fabricanteMaisBarato = produtos[indiceMaisBarato].fabricante;
    printf("Fabricante do produto mais barato: %s\n", fabricanteMaisBarato.marca);
}

// Função para comparar dois produtos pelo valor de venda
int compararProdutosValor(const void *produto1, const void *produto2) {
    Produto *p1 = (Produto *)produto1;
    Produto *p2 = (Produto *)produto2;

    if (p1->valorVenda < p2->valorVenda) {
        return -1;
    } else if (p1->valorVenda > p2->valorVenda) {
        return 1;
    } else {
        return 0;
    }
}

// Função para listar todos os produtos em ordem crescente de valor de venda
void listarProdutosOrdemCrescenteValor(Produto *produtos, int numProdutos) {
    printf("\n--- Produtos em Ordem Crescente de Valor de Venda ---\n");

    // Utilizamos a função qsort para ordenar os produtos pelo valor de venda
    qsort(produtos, numProdutos, sizeof(Produto), compararProdutosValor);

    // Exibimos os produtos em ordem crescente de valor de venda
    int i;
    for (i = 0; i < numProdutos; i++) {
        printf("Produto %d\n", i + 1);
        printf("Descrição: %s\n", produtos[i].descricao);
        printf("Peso: %.2f\n", produtos[i].peso);
        printf("Valor de Compra: R$ %.2f\n", produtos[i].valorCompra);
        printf("Valor de Venda: R$ %.2f\n", produtos[i].valorVenda);
        printf("Percentual de Lucro: %.2f%%\n", produtos[i].percentualLucro);
        printf("Fabricante:\n");
        printf("Marca: %s\n", produtos[i].fabricante.marca);
        printf("Site: %s\n", produtos[i].fabricante.site);
        printf("Telefone: %s\n", produtos[i].fabricante.telefone);
        printf("UF: %s\n", produtos[i].fabricante.uf);
        printf("\n");
    }
}

int compararProdutosLucro(const void *produto1, const void *produto2) {
    Produto *p1 = (Produto *)produto1;
    Produto *p2 = (Produto *)produto2;

    if (p1->valorLucro < p2->valorLucro) {
        return -1;
    } else if (p1->valorLucro > p2->valorLucro) {
        return 1;
    } else {
        return 0;
    }
}

// Função para listar todos os produtos em ordem crescente de maior valor de lucro
void listarProdutosOrdemCrescenteLucro(Produto *produtos, int numProdutos) {
    printf("\n--- Produtos em Ordem Crescente de Maior Valor de Lucro ---\n");

    // Utilizamos a função qsort para ordenar os produtos pelo valor de lucro
    qsort(produtos, numProdutos, sizeof(Produto), compararProdutosLucro);

    // Exibimos os produtos em ordem crescente de maior valor de lucro
    int i;
    for (i = 0; i < numProdutos; i++) {
        printf("Produto %d\n", i + 1);
        printf("Descrição: %s\n", produtos[i].descricao);
        printf("Peso: %.2f\n", produtos[i].peso);
        printf("Valor de Compra: R$ %.2f\n", produtos[i].valorCompra);
        printf("Valor de Venda: R$ %.2f\n", produtos[i].valorVenda);
        printf("Percentual de Lucro: %.2f%%\n", produtos[i].percentualLucro);
        printf("Fabricante:\n");
        printf("Marca: %s\n", produtos[i].fabricante.marca);
        printf("Site: %s\n", produtos[i].fabricante.site);
        printf("Telefone: %s\n", produtos[i].fabricante.telefone);
        printf("UF: %s\n", produtos[i].fabricante.uf);
        printf("\n");
    }
}
void listarProdutosPorMarca(Produto *produtos, int numProdutos, const char *marca) {
    printf("\n--- Produtos da Marca %s ---\n", marca);

    bool encontrou = false;
    int i;
	for (i = 0; i < numProdutos; i++) {
        if (strcmp(produtos[i].fabricante.marca, marca) == 0) {
            encontrou = true;
            printf("Produto %d\n", i + 1);
            printf("Descrição: %s\n", produtos[i].descricao);
            printf("Peso: %.2f\n", produtos[i].peso);
            printf("Valor de Compra: R$ %.2f\n", produtos[i].valorCompra);
            printf("Valor de Venda: R$ %.2f\n", produtos[i].valorVenda);
            printf("Percentual de Lucro: %.2f%%\n", produtos[i].percentualLucro);
            printf("Fabricante:\n");
            printf("Marca: %s\n", produtos[i].fabricante.marca);
            printf("Site: %s\n", produtos[i].fabricante.site);
            printf("Telefone: %s\n", produtos[i].fabricante.telefone);
            printf("UF: %s\n", produtos[i].fabricante.uf);
            printf("\n");
        }
    }

    if (!encontrou) {
        printf("Nenhum produto encontrado para a marca %s.\n", marca);
    }
}

int menuFinal(Produto *produtos, int numProdutos) {
    int opcao;

    do {
        printf("\n=== Menu Final ===\n");
        printf("1. Listar todas as marcas\n");
        printf("2. Listar todos os produtos\n");
        printf("3. Listar produtos de um determinado estado (UF)\n");
        printf("4. Listar produtos de uma determinada marca\n");
        printf("5. Exibir o estado com o produto mais caro\n");
        printf("6. Exibir o fabricante com o produto mais barato\n");
        printf("7. Listar todos os produtos em ordem crescente de valor de venda\n");
        printf("8. Listar todos os produtos em ordem crescente de maior valor de lucro\n");
        printf("9. Voltar ao menu principal\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                listarMarcas(produtos, numProdutos);
                break;
            case 2:
                exibirRelatorio(produtos, numProdutos);
                break;
            case 3: {
                char uf[3];
                printf("Digite a UF: ");
                scanf("%s", uf);
                listarProdutosEstado(produtos, numProdutos, uf);
                break;
            }
            case 4: {
                char marca[100];
        		printf("Digite a marca: ");
        		scanf(" %[^\n]s", marca);
        		listarProdutosPorMarca(produtos, numProdutos, marca);
                break;
            }
            case 5:
                exibirEstadoProdutoMaisCaro(produtos, numProdutos);
                break;
            case 6:
                listarFabricanteProdutoMaisBarato(produtos, numProdutos);
                break;
            case 7:
                listarProdutosOrdemCrescenteValor(produtos, numProdutos);
                break;
            case 8:
                listarProdutosOrdemCrescenteLucro(produtos, numProdutos);
                break;
            case 9:
                return 0;
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    } while (opcao != 8);
}
