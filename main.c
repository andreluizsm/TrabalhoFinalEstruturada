#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "main.h"
#include "menu.h"


void adicionarProduto(Produto *produtos, int *numProdutos) {
    Produto novoProduto;

    printf("\n--- Adicionar Produto ---\n");

    printf("Descrição: ");
    scanf(" %[^\n]s", novoProduto.descricao);

    printf("Peso (g): ");
    scanf("%f", &novoProduto.peso);

    printf("Valor de Compra: ");
    scanf("%f", &novoProduto.valorCompra);

    printf("Valor de Venda: ");
    scanf("%f", &novoProduto.valorVenda);

	novoProduto.valorLucro = novoProduto.valorVenda - novoProduto.valorCompra;
    novoProduto.percentualLucro = (novoProduto.valorLucro / novoProduto.valorCompra) * 100;

    printf("\n--- Dados do Fabricante ---\n");
    printf("Marca: ");
    scanf(" %[^\n]s", novoProduto.fabricante.marca);

    printf("Site: ");
    scanf(" %[^\n]s", novoProduto.fabricante.site);

    printf("Telefone: ");
    scanf(" %[^\n]s", novoProduto.fabricante.telefone);
	
	do{
	   	printf("UF <AC, AM, AP, SP, TO>: ");
    	scanf(" %[^\n]s", novoProduto.fabricante.uf);
    }while (strcmp(novoProduto.fabricante.uf, "AC") != 0 && strcmp(novoProduto.fabricante.uf, "AM") != 0 &&strcmp(novoProduto.fabricante.uf, "AP") != 0 &&
    strcmp(novoProduto.fabricante.uf, "SP") != 0 && strcmp(novoProduto.fabricante.uf, "TO") != 0);
    	


    produtos[*numProdutos] = novoProduto;
    (*numProdutos)++;

    printf("Produto adicionado com sucesso!\n\n");
}


int encontrarProduto(Produto *produtos, int numProdutos, const char *descricao) {
    int i;
 	for (i = 0; i < numProdutos; i++) {
        if (strcmp(produtos[i].descricao, descricao) == 0) {
            return i;
        }
    }
    return -1; 
}


void excluirProduto(Produto *produtos, int *numProdutos) {
    char descricao[100];
    printf("Digite a descrição do produto que deseja excluir: ");
    scanf(" %[^\n]s", descricao);

    int indice = encontrarProduto(produtos, *numProdutos, descricao);
    if (indice != -1) {
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

void exibirRelatorio(Produto *produtos, int numProdutos) {
    printf("=== Relatório de Produtos ===\n");
	
	int i;
    for ( i = 0; i < numProdutos; i++) {
        printf("Produto %d\n", i + 1);
        printf("Descrição: %s\n", produtos[i].descricao);
        printf("Peso: %.2f\n", produtos[i].peso);
        printf("Valor de Compra: R$ %.2f\n", produtos[i].valorCompra);
        printf("Valor de Venda: R$ %.2f\n", produtos[i].valorVenda);
        printf("Percentual de Lucro: %.2f%%\n", produtos[i].percentualLucro);
        printf("Fabricante: %s\n", produtos[i].fabricante);
        printf("\n");
    }
}

void alterarProduto(Produto *produtos, int numProdutos) {
    char descricao[100];
    printf("Digite a descrição do produto que deseja alterar: ");
    scanf(" %[^\n]s", descricao);

    int indice = encontrarProduto(produtos, numProdutos, descricao);
    if (indice != -1) {
        Produto novoProduto;

        printf("--- Alterar Produto ---\n");

        printf("Nova Descrição: ");
        scanf(" %[^\n]s", novoProduto.descricao);

        printf("Novo Peso (g): ");
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

int menuEstatico() {
	int opcao;

    printf("=== Menu ===\n");
    printf("1. Adicionar Produto\n");
    printf("2. Excluir Produto\n");
    printf("3. Alterar Produto\n");
    printf("4. Exibir Menu Final\n");
	printf("5. Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    
    return opcao;
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    Produto produtos[100];
    int numProdutos = 0;
	int opcao; 
	
    do {
		if (numProdutos == 0) {
			printf("=== Menu ===\n");
	        printf("1. Adicionar Produto\n");
	        printf("2. Sair\n");
	        printf("Escolha uma opção: ");
	        scanf("%d", &opcao);

            if (opcao == 1) {
                adicionarProduto(produtos, &numProdutos);
            } else if (opcao > 2) {
              printf("Opção inválida! Tente novamente!\n");
            } else if (opcao == 2){
            	return;
			}
        } else {
			opcao = menuEstatico();
	
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
                    menuFinal(produtos, numProdutos);
                    break;
				case 5:
                    printf("Encerrando o programa. Até mais!\n");
                    return 0;
                default:
                    printf("Opção inválida. Tente novamente.\n");
                    break;
            }
		}
    } while (1);

    return 0;
}



