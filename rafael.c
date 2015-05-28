/* 
LAPRO I - PUCRS
Estrutura básica para o desenvolvimento de um jogo de campo minado
Matheus Moreira - matheus.moreira@pucrs.br
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

//Estrutura básica de cada célula do tabuleiro
struct celula {
	//Membro que deverá conter o valor a ser impresso da célula
	char imprime;
	//Membro que deverá conter o valor de controle da célula
	int valor;
};

//Essa função será executada na main, para que o jogador realize suas jogadas, até o final do jogo
// Ela recebe por parâmetro a referência para o tabuleiro, juntamente com o tamanho do lado do tabuleiro e o número total de bombas
// A função deve retornar 1 enquanto o jogo não acabar e 0 quando ele acabar
int jogada(struct celula *tabuleiro, int lado, int total_bombas){
}


//Essa função facilita funções de abertura de célula e de cálculo de valor de células
// Ela recebe por parâmetro um deslocamento XY (que varia entre -1, 0 e 1), uma célula do tabuleiro, um valor de controle, a referência para o tabuleiro e o lado do tabuleiro
// A função retorna o valor (se controle==0) ou o valor a ser impresso (se controle==1) da célula vizinha 
// Por exemplo:
//  Assumindo coordenadas XY, temos o seguinte tabuleiro 4x4:
//	00 10 20 30
//	01 11 21 31
//  02 12 22 32
//  03 13 23 33
//  Assumindo que o usuário solicite leitura do vizinho x=-1 e y=0, da célula 22, a função deverá retornar o valor ou o caracter a ser impresso da célula 12
int le_vizinho(int x, int y, int posicao, int controle, struct celula *tabuleiro, int lado);


//Essa função é responsável por criar bombas no tabuleiro de forma aleatória (usando uma semente para inicialização da função rand()). Além disso, essa função deve calcular os valores de controle de cada célula do tabuleiro (conforme definido na específicação desse trabalho).
// Ela recebe por parâmetro a referência para o tabuleiro, juntamente com o tamanho do lado do tabuleiro, o número total de bombas e a semente a ser usada na geração das mesmas
int gera_bombas(struct celula *tabuleiro, int lado, int num_bombas, int semente){
	int x, y, bomb=0;
	while(bomb != num_bombas){	
		x = rand()%(lado-1);
		y = rand()%(lado-1);
			
		if (tabuleiro[x*lado + y].valor != -1)
		{
			tabuleiro[x*lado + y].valor = -1;
			bomb++;
		}
	}	
	
}

//Essa função imprime o tabuleiro, mostrando apenas os caracteres de impressão para o jogador
// Ela recebe por parâmetro a referência para o tabuleiro e o tamanho do lado do tabuleiro
int imprime_tabuleiro(struct celula *tabuleiro, int lado){
 	int i,n;
 	
 	for (i=0;i<lado;i=i+2){
		if (i==0)
			printf("\n   %d",i);
		else if (i<10)
 			printf("     %d", i);
 			else
 			printf("    %d", i);
 	}
 	printf("\n");
 	for (i=1;i<lado;i=i+2)
 	if (i==1)
			printf("      %d",i);
		else if (i<10)
 			printf("     %d", i);
 			else
 			printf("    %d", i);
 	
 		
 		
 	printf("\n");
 	for (i=0;i<lado;i++){
 			if (i<10)
 				printf(" ");
 		printf("%d", i);
	 	for (n=0; n<lado;n++){
	 			
				printf(" %c ", tabuleiro[i*lado + n].imprime);
		}
 	printf("\n");
	}		
}


//Essa função solicita uma coordenada XY (usando as funções printf() e scanf()) e abre uma célula no tabuleiro
// Ela recebe por parâmetro a referência para o tabuleiro e o tamanho do lado do tabuleiro
// Caso a célula não esteja próxima a nenhuma bomba (valor=0), a função deve seguir expandindo todas células vizinhas, até chegar nas margens de bombas próximas (células com valor>0)
// Se o usuário abrir uma célula que é uma bomba, ele perde o jogo
// Células marcadas como bombas não podem ser abertas e deverão primeiramente ser desmarcadas, para então serem abertas
int abrir_celula(struct celula *tabuleiro, int lado);


//Essa função solicita uma coordenada XY (usando as funções printf() e scanf()) e marca uma célula no tabuleiro como bomba. Caso a célula já esteja marcada como bomba, a função desmarca a célula
// Ela recebe por parâmetro a referência para o tabuleiro e o tamanho do lado do tabuleiro
int marcar_bomba(struct celula *tabuleiro, int lado){
	int x,y;
	printf("Entre com a posicao desejada\n");
	printf("X=");
	scanf("%d",&x);
	printf("Y=");
	scanf("%d",&y);
	if (tabuleiro[x*lado + y].imprime == 'B'){
		tabuleiro[x*lado + y].imprime = 35;
	}
	else
	tabuleiro[x*lado + y].imprime = 66;
}


//Essa função é executada no final do jogo. Ela escreve a pontuação do jogador no arquivo texto pontos.txt.
// Ela recebe por parâmetro o nome do jogador, o tamanho do lado do tabuleiro, o número de bombas do jogo atual e o número de células abertas até o final do jogo
// O cálculo da pontuação (P) é feito da seguinte forma:
//  P = (lado*lado)*(num_bombas)*(pct_celulas)
//   onde pct_celulas=celulas_abertas/((lado*lado)-num_bombas)
// A pontuação deve ser escrita nesse arquivo em ordem decrescente de pontos (o primeiro colocado é aquele com a maior pontuação)
// Antes de finalizar o jogo, essa função deve imprimir os 10 melhores jogadores
int fim_de_jogo(char jogador[20], int lado, int num_bombas, int celulas_abertas);

int opcoes(){
	printf("\n	COMANDOS:\n");
	printf(" a - Abrir posicao no tabuleiro\n b - Marcar/Desmarcar posicao no tabuleiro como bomba\n");
	printf(" p - Lista pontuacoes\n c - Lista de comandos\n\n");
}

int main (int argc, char *argv[]){
	//Tabuleiro e variáveis para controle
	struct celula *tabuleiro, *tabuleiro_aux;
	int lado_tabuleiro=atoi(argv[2]), num_bombas=atoi(argv[3]), semente;
	//Nome do jogador
	char jogador[20],o;
	//Para controle de laços
	int i,n;
	
	//Escreva aqui um trecho de código para verificar a consistência de dados de entrada do programa (argc e argv)
	if (argc!=4 || lado_tabuleiro < 2 || lado_tabuleiro*lado_tabuleiro <= num_bombas){
		printf("Erro");
		return 0;
	}
	printf("\nJogador %s, Tabuleiro %dx%d com %d Bombas!\n", argv[1],lado_tabuleiro,lado_tabuleiro,num_bombas);
	//Escreva aqui um trecho de código para inicializar as variáveis do jogo
	
	//Escreva aqui um trecho de código para inicialização do tabuleiro e alocação de espaço em memória (usar malloc)
	
	tabuleiro = (struct celula*)malloc(sizeof(struct celula)*lado_tabuleiro*lado_tabuleiro);
	for (i=0;i<lado_tabuleiro;i++)
		for (n=0; n<lado_tabuleiro;n++)
 			 tabuleiro[i*lado_tabuleiro + n].imprime = 35;
 			 
 	opcoes();	
	while(1){
		imprime_tabuleiro(tabuleiro,lado_tabuleiro);
		printf("Insira a opcao (a/b/c/s): ");
		scanf(" %c", &o);
		switch(o){
			case 'a':
				jogada(tabuleiro,lado_tabuleiro,num_bombas);
				 break;
			case 'b':
				marcar_bomba(tabuleiro,lado_tabuleiro);
				break;
			case 'c':
				opcoes();
				break;
			case 's':
				return 0;
		}
	}

	
	//Aqui as bombas devem ser criadas no tabuleiro e os valores de controle de todas células devem ser calculados
	srand(time(NULL));
	semente=rand()%666;
	gera_bombas(tabuleiro,lado_tabuleiro,num_bombas,semente);
	
	//Escreva aqui um trecho de código para controle de rodadas do jogo
	
	//Escreva aqui um trecho de código para finalizar o jogo
	
	return 0;
}
/* IMRPIME TABULEIRO VALORES
for (i=0;i<lado_tabuleiro;i++){
	for (n=0; n<lado_tabuleiro;n++)
	 		 printf(" %d ", tabuleiro[i*lado_tabuleiro + n].valor);
 	printf(" \n ");
	}*/
