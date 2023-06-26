typedef struct {
    char marca[100];
    char site[100];
    char telefone[20];
    char uf[3];
} Fabricante;

typedef struct  {
    char descricao[100];
    float peso;
    float valorCompra;
    float valorVenda;
    float valorLucro;
    float percentualLucro;
    Fabricante fabricante;
}Produto;

void adicionarProduto(Produto *produtos, int *numProdutos);
void alterarProduto(Produto *produtos, int numProdutos);
void excluirProduto(Produto *produtos, int *numProdutos);
int encontrarProduto(Produto *produtos, int numProdutos, const char *descricao);
int menuEstatico();




























