#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void limparBufferStr(char * str) {
    int tam = strlen(str);

    if ( str[tam-1] == '\n') {
        str[tam-1] = '\0';
    } else {
        limparBuffer();
    }
}

struct Cliente {
    char nome[50];   
    int telefone;
    char email[50];
};
typedef struct Cliente  Cliente;

struct Conta {
    int numero;
    float saldo;
    Cliente clientes;
};
typedef struct Conta  Conta;


struct Vetorconta {
    Conta vetContas[200];
    int total;
};
typedef struct Vetorconta  Vetorconta;

void lerCliente ( Cliente *cl) {
    printf("Nome: ");
    fgets(cl->nome, 50, stdin );
    limparBufferStr(cl->nome);

    printf("Tel: ");
    while(scanf("%d",&cl->telefone) !=1){
        printf("Entrada invalida, Digite apenas numeros.\n");
        limparBuffer();
        printf("Tel: ");
    }
    limparBuffer();

    printf("Email: ");
    fgets(cl->email, 50, stdin );
    limparBufferStr(cl->email);
}

void lerConta( Conta *c) {
    printf("Codigo: ");
    while(scanf("%d",&c->numero) !=1){
        printf("Entrada invalida, Digite apenas numeros.\n");
        limparBuffer();
        printf("Codigo: ");
    }
    limparBuffer();
    printf("Informe seus dados: \n");
    lerCliente( & c->clientes );
}


void inserirconta(Vetorconta *vetorconta ) {
    Conta c;   // NOVO produto 
    lerConta(&c);     // LÊ APENAS UM produto

    while(validarcodigo(vetorconta, c.numero)){
        printf("esse codigo ja esta cadastrado\n");
        printf("os dados inseridos estão guardados e salvos, apenas digite um novo codigo.\n");
        printf("Digite outro codigo: ");

        scanf("%d", &c.numero);
        limparBuffer();
    }
    // Inserir um NOVO produto no vetor
    vetorconta->vetContas[vetorconta->total] = c;
    (vetorconta->total)++;
    printf("Conta cadastrada com sucesso.\n");
}
 
int validarcodigo(Vetorconta *vetorconta, int codigo){
    int i;
    for(i=0; i < vetorconta->total; i++ ) {
        if (vetorconta->vetContas[i].numero == codigo) {
            return 1;
        }
    }
    return 0;
}

int pesquisarPorCodigo(Conta vetor[], int qtde) {
    Conta elem;
    int i;
    limparBuffer();
    printf("digite o codigo do cliente: ");
    while(scanf("%d",&elem) !=1){
        printf("Entrada invalida, Digite apenas numeros.\n");
        limparBuffer();
        printf("Codigo: ");
    }
    limparBuffer();

    for(i=0; i < qtde; i++ ) {
        if (vetor[i].numero == elem.numero ) {
            return i;   // Retorna a posicao
        }
    }
    return -1;  // Não encontrou
}

int pesquisarPorNome(Conta vetor[], int qtde) {
    Conta elem;
    int i;
    limparBuffer();
    printf("digite o nome do cliente: ");
    fgets(elem.clientes.nome, 50, stdin);
    limparBufferStr(elem.clientes.nome);

    for(i=0; i < qtde; i++ ) {
        if ( strcmp( vetor[i].clientes.nome,elem.clientes.nome) == 0 ) {
            return i;   // Retorna a posicao
        }
    }
    return -1;  // Não encontrou
}

void imprimir(Conta *c) {
    printf("\n-------------------------------------\n");
    printf("Codigo: %d\n", c->numero);
    printf("Saldo: R$ %.2f\n", c->saldo);
    printf("Nome: %s\n", c->clientes.nome);
    printf("Telefone: %d\n", c->clientes.telefone);
    printf("Email: %s\n", c->clientes.email);
    printf("-------------------------------------\n");
}

void atualizar(Conta *c){
    int op;
    float top;
    printf("1 - para sacar\n2 - para depositar\n");
    while(scanf("%d",&op) !=1){
        printf("Entrada invalida, Digite apenas numeros.\n");
        limparBuffer();
        printf("1 - para sacar\n2 - para depositar\n");
    }
    limparBuffer();
    if(op == 1){
        printf("informe o valor a sacar da conta, caso saque mais doque sua conta atualmente possui, você ficará negativado.\n");
        while(scanf("%f",&top) !=1){
            printf("Entrada invalida, Digite apenas numeros.\n");
            limparBuffer();
            printf("valor a sacar: ");
        }
        limparBuffer();
        top = c->saldo - top;
        c->saldo = top;
        printf("Saldo: R$ %.2f\n", c->saldo);
    }else{
        printf("informe o valor a depositar da conta :)\n");
        while(scanf("%f",&top) !=1){
            printf("Entrada invalida, Digite apenas numeros.\n");
            limparBuffer();
            printf("valor a depositar: ");
        }
        limparBuffer();
        top = c->saldo + top;
        c->saldo = top;
        printf("Saldo: R$ %.2f\n", c->saldo);
    }
}

int maior(Conta vetor[], int qtde){
    int aux;
    int i, top1;
    top1 = 0;
    for(i=0; i < qtde; i++ ) {
        if (vetor[i].saldo >= top1) {
            top1 = vetor[i].saldo;
            aux = i;
        }
    }
    printf("conta com maior saldo: ");
    return aux;
}

void excluir(Vetorconta *vetorconta){
    int cod;
    printf("digite o codigo da conta a ser excluida: ");
    while(scanf("%d",&cod) !=1){
        printf("Entrada invalida, Digite apenas numeros.\n");
        limparBuffer();
        printf("Codigo da conta: ");
    }
    limparBuffer();

    int posicao;
    int i;
    int j;
    for(i=0; i < vetorconta->total; i++ ) {
        if (vetorconta->vetContas[i].numero == cod) {
            posicao = i;
            break;
        }
    }
    if (posicao == -1) {
        printf("Conta nao encontrada!\n");
        return;
    }

    for(j = posicao; j<vetorconta->total - 1; j++){
        vetorconta->vetContas[j] = vetorconta->vetContas[j+1];
    }
    vetorconta->total--;
    printf("conta excluida");
}

void listarconta(Vetorconta *vetorconta){
    int i = 0;
    if(vetorconta->total == 0){
        printf("\nnenhuma conta cadastrada no sistema\n");
        return;
    }

    for(i=0; i < vetorconta->total; i++ ) {
        imprimir(&vetorconta->vetContas[i]);
    }
}

int menu() {
	int op;
	system("@cls||clear");  // LIMPA A TELA
	printf("\n\nSISTEMA BANCARIO\n\n");
	printf("1 - Inserir\n");
	printf("2 - Pesquisar por número\n");
	printf("3 - Pesquisar por nome\n");
	printf("4 - Atualizar\n");
	printf("5 - Maior\n");
	printf("6 - Excluir\n");
	printf("7 - Listar\n");
	printf("0 - Sair\n");
	do {
		printf("Escolha sua opção: ");
		scanf(" %d", &op);
	} while(op < 0 || op > 7);
	return op;
}

int main() {
    SetConsoleOutputCP(65001);
    Vetorconta vetorconta;
    vetorconta.total = 0;
	int op;
    int posicao;
	do {
		op = menu();
		switch ( op ) {
			case 0:
				// SAIR. NÃO PRECISA FAZER NADA
				break;
			case 1:
				// INSERIR
                inserirconta(&vetorconta);
				break;
			case 2:
				posicao = pesquisarPorCodigo(vetorconta.vetContas,vetorconta.total);
                if(posicao != -1){
                    imprimir(&vetorconta.vetContas[posicao]);
                }else{
                    printf("usuario não encontrado.\n");
                }
				break;
			case 3:
				posicao = pesquisarPorNome(vetorconta.vetContas,vetorconta.total);
                if(posicao != -1){
                    imprimir(&vetorconta.vetContas[posicao]);
                }else{
                    printf("usuario não encontrado.\n");
                }
				break;
			case 4:
                posicao = pesquisarPorCodigo(vetorconta.vetContas,vetorconta.total);
                if(posicao != -1){
                    atualizar(&vetorconta.vetContas[posicao]);
                }else{
                    printf("usuario não encontrado.\n");
                }
				break;
			case 5:
				// MAIOR
                posicao = maior(vetorconta.vetContas,vetorconta.total);
                imprimir(&vetorconta.vetContas[posicao]);
				break;
			case 6:
				excluir(&vetorconta);
				break;
			case 7:
				listarconta(&vetorconta);
				break;
			default:
				printf ("\n\nOpção inválida!\n\n");
		}

		system("PAUSE");  // Windows
	} while (op != 0);
	
	return 0;
}