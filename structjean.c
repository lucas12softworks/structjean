#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    scanf("%d", & cl->telefone );
	limparBuffer();

    printf("Email: ");
    fgets(cl->email, 50, stdin );
    limparBufferStr(cl->email);
}

void lerConta( Conta *c) {
    printf("Codigo: ");
    scanf("%d", & c->numero );
	limparBuffer();

    printf("Informe seus dados: \n");
    lerCliente( & c->clientes );
}

void inserirconta(Vetorconta *vetorconta ) {
    Conta c;   // NOVO produto 
    lerConta(&c);     // LÊ APENAS UM produto

    // Inserir um NOVO produto no vetor
    vetorconta->vetContas[vetorconta->total] = c;
    (vetorconta->total)++;
}

int pesquisarPorCodigo(Conta vetor[], int qtde, Conta elem ) {
    int i;
    for(i=0; i < qtde; i++ ) {
        if ( vetor[i].numero == elem.numero ) {
            return i;   // Retorna a posicao
        }
    }
    return -1;  // Não encontrou
}

int pesquisarPorNome(Conta vetor[], int qtde, Conta elem ) {
    int i;
    for(i=0; i < qtde; i++ ) {
        if ( strcmp( vetor[i].clientes.nome,elem.clientes.nome) == 0 ) {
            return i;   // Retorna a posicao
			imprimir(i);
        }
    }
    return -1;  // Não encontrou
}

void imprimir(Conta vetor[]) {
    printf("\n-------------------------------------\n");
    printf("Codigo: %d \nPreco: R$ %.2f \n", vetor->numero, vetor->saldo);
    printf("Data validade: ");
    imprimirData( vetor->clientes);
    printf("-------------------------------------\n");
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
    Vetorconta vetorconta;
    vetorconta.total = 0;
	int op;
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
				// PESQUISAR POR CODIGO/MATRICULA
				break;
			case 3:
				//pesquisarPorNome(vetorconta.total, Conta);
				break;
			case 4:
				// ATUALIZAR
				break;
			case 5:
				// MAIOR
				break;
			case 6:
				// EXCLUIR
				break;
			case 7:
				// LISTAR
				break;
			default:
				printf ("\n\nOpção inválida!\n\n");
		}

		system("PAUSE");  // Windows
	} while (op != 0);
	
	return 0;
}