#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "main.h"

void adicionarProduto(Produto *produtos, int *numProdutos) {
    Produto novoProduto;

    printf("--- Adicionar Produto ---\n");

    printf("Descrição: ");
    scanf(" %[^\n]s", novoProduto.descricao);

    printf("Peso: ");
    scanf("%f", &novoProduto.peso);

    printf("Valor de Compra: ");
    scanf("%f", &novoProduto.valorCompra);

    printf("Valor de Venda: ");
    scanf("%f", &novoProduto.valorVenda);

	novoProduto.valorLucro = novoProduto.valorVenda - novoProduto.valorCompra;
    novoProduto.percentualLucro = (novoProduto.valorLucro / novoProduto.valorCompra) * 100;

    printf("Fabricante:\n");
    printf("Marca: ");
    scanf(" %[^\n]s", novoProduto.fabricante.marca);

    printf("Site: ");
    scanf(" %[^\n]s", novoProduto.fabricante.site);

    printf("Telefone: ");
    scanf(" %[^\n]s", novoProduto.fabricante.telefone);

    printf("UF: ");
    scanf(" %[^\n]s", novoProduto.fabricante.uf);

    produtos[*numProdutos] = novoProduto;
    (*numProdutos)++;

    printf("Produto adicionado com sucesso!\n\n");
}


void exibirRelatorio(Produto *produtos, int numProdutos) {
    printf("\n--- Relatório de Produtos ---\n");
	
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

// Função para encontrar o índice de um produto pelo nome
int encontrarProduto(Produto *produtos, int numProdutos, const char *descricao) {
    int i;
 	for (i = 0; i < numProdutos; i++) {
        if (strcmp(produtos[i].descricao, descricao) == 0) {
            return i;
        }
    }
    return -1; // Retorna -1 se o produto não for encontrado
}

// Função para excluir um produto
void excluirProduto(Produto *produtos, int *numProdutos) {
    char descricao[100];
    printf("Digite a descrição do produto que deseja excluir: ");
    scanf(" %[^\n]s", descricao);

    int indice = encontrarProduto(produtos, *numProdutos, descricao);
    if (indice != -1) {
        // Desloca os produtos seguintes para preencher a posição do produto excluído
        int i;
		for ( i = indice; i < (*numProdutos) - 1; i++) {
            produtos[i] = produtos[i + 1];
        }
        (*numProdutos)--;
        printf("Produto excluído com sucesso!\n");
    } else {
        printf("Produto não encontrado.\n");
    }
}

// Função para alterar um produto
void alterarProduto(Produto *produtos, int numProdutos) {
    char descricao[100];
    printf("Digite a descrição do produto que deseja alterar: ");
    scanf(" %[^\n]s", descricao);

    int indice = encontrarProduto(produtos, numProdutos, descricao);
    if (indice != -1) {
        Produto novoProduto;

        printf("=== Alterar Produto ===\n");

        printf("Nova Descrição: ");
        scanf(" %[^\n]s", novoProduto.descricao);

        printf("Novo Peso: ");
        scanf("%f", &novoProduto.peso);

        printf("Novo Valor de Compra: ");
        scanf("%f", &novoProduto.valorCompra);

        printf("Novo Valor de Venda: ");
        scanf("%f", &novoProduto.valorVenda);

		novoProduto.valorLucro = novoProduto.valorVenda - novoProduto.valorCompra;
        novoProduto.percentualLucro = (novoProduto.valorLucro / novoProduto.valorCompra) * 100;	

        printf("Novo Fabricante:\n");
        printf("Nova Marca: ");
        scanf(" %[^\n]s", novoProduto.fabricante.marca);

        printf("Novo Site: ");
        scanf(" %[^\n]s", novoProduto.fabricante.site);

        printf("Novo Telefone: ");
        scanf(" %[^\n]s", novoProduto.fabricante.telefone);

        printf("Nova UF: ");
        scanf(" %[^\n]s", novoProduto.fabricante.uf);

        produtos[indice] = novoProduto;
        printf("Produto alterado com sucesso!\n");
    } else {
        printf("Produto não encontrado.\n");
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese");
	int opcao;
    Produto produtos[100];
    int numProdutos = 0;

    do {
        printf("=== Menu ===\n");
        printf("1. Adicionar Produto\n");
        printf("2. Excluir Produto\n");
        printf("3. Alterar Produto\n");
        printf("4. Exibir Relatório de Produtos\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarProduto(produtos, &numProdutos);
                break;
            case 2:
                excluirProduto(produtos, &numProdutos);
                break;
            case 3:
                alterarProduto(produtos, numProdutos);
                break;
            case 4:
                exibirRelatorio(produtos, numProdutos);
                break;
            case 5:
                printf("Encerrando o programa. Até mais!\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    } while (opcao != 5);

    return 0;
}












