#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define COMPUTADOR 1
#define HUMANO 2
#define LADO 3
#define JOGADA_COMPUTADOR 'O'
#define JOGADA_HUMANO 'X'

// ---------------- Início das jogadas inteligentes

struct Jogada {
	int linha, coluna;
};

char jogador = 'x', oponente = 'o';

// Esta função retorna verdadeiro se ainda há jogadas
// disponíveis no tabuleiro. Retorna falso se não
// houver mais jogadas a fazer.
bool temJogadasRestantes(char tabuleiro[3][3])
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (tabuleiro[i][j] == '_')
				return true;
	return false;
}

// Esta é a função de avaliação
int avaliar(char t[3][3])
{
	// Verificando as linhas para vitória de X ou O.
	for (int linha = 0; linha < 3; linha++) {
		if (t[linha][0] == t[linha][1]
			&& t[linha][1] == t[linha][2]) {
			if (t[linha][0] == jogador)
				return +10;
			else if (t[linha][0] == oponente)
				return -10;
		}
	}

	// Verificando as colunas para vitória de X ou O.
	for (int coluna = 0; coluna < 3; coluna++) {
		if (t[0][coluna] == t[1][coluna]
			&& t[1][coluna] == t[2][coluna]) {
			if (t[0][coluna] == jogador)
				return +10;

			else if (t[0][coluna] == oponente)
				return -10;
		}
	}

	// Verificando as diagonais para vitória de X ou O.
	if (t[0][0] == t[1][1] && t[1][1] == t[2][2]) {
		if (t[0][0] == jogador)
			return +10;
		else if (t[0][0] == oponente)
			return -10;
	}

	if (t[0][2] == t[1][1] && t[1][1] == t[2][0]) {
		if (t[0][2] == jogador)
			return +10;
		else if (t[0][2] == oponente)
			return -10;
	}

	// Caso contrário, se ninguém venceu, retorna 0
	return 0;
}

// Esta é a função minimax. Ela considera todas as
// maneiras possíveis de o jogo se desenrolar e retorna
// o valor do tabuleiro
int minimax(char tabuleiro[3][3], int profundidade, bool ehMaximizador)
{
	int pontuacao = avaliar(tabuleiro);

	// Se o Maximizador venceu o jogo, retorna a
	// pontuação avaliada dele(a)
	if (pontuacao == 10)
		return pontuacao;

	// Se o Minimizador venceu o jogo, retorna a
	// pontuação avaliada dele(a)
	if (pontuacao == -10)
		return pontuacao;

	// Se não há mais jogadas e nenhum vencedor,
	// então é um empate
	if (temJogadasRestantes(tabuleiro) == false)
		return 0;

	// Se é a vez do maximizador
	if (ehMaximizador) {
		int melhor = -1000;

		// Percorre todas as células
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				// Verifica se a célula está vazia
				if (tabuleiro[i][j] == '_') {
					// Faz a jogada
					tabuleiro[i][j] = jogador;
					int valor
						= minimax(tabuleiro, profundidade + 1, !ehMaximizador);
					if (valor > melhor) {
						melhor = valor;
					}

					// Desfaz a jogada
					tabuleiro[i][j] = '_';
				}
			}
		}
		return melhor;
	}

	// Se é a vez do minimizador
	else {
		int melhor = 1000;

		// Percorre todas as células
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				// Verifica se a célula está vazia
				if (tabuleiro[i][j] == '_') {
					// Faz a jogada
					tabuleiro[i][j] = oponente;

					// Chama o minimax recursivamente e escolhe
					int valor
						= minimax(tabuleiro, profundidade + 1, !ehMaximizador);
					if (valor < melhor) {
						melhor = valor;
					}
					// Desfaz a jogada
					tabuleiro[i][j] = '_';
				}
			}
		}
		return melhor;
	}
}

// Esta função retorna a melhor jogada possível para o jogador
struct Jogada encontrarMelhorJogada(char tabuleiro[3][3])
{
	int melhorValor = -1000;
	struct Jogada melhorJogada;
	melhorJogada.linha = -1;
	melhorJogada.coluna = -1;

	// Percorre todas as células, avalia a função minimax para
	// todas as células vazias e retorna a célula com o
	// valor ótimo.
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			// Verifica se a célula está vazia
			if (tabuleiro[i][j] == '_') {
				// Faz a jogada
				tabuleiro[i][j] = jogador;

				// calcula a função de avaliação para esta
				// jogada.
				int valorJogada = minimax(tabuleiro, 0, false);

				// Desfaz a jogada
				tabuleiro[i][j] = '_';

				// Se o valor da jogada atual for
				// maior que o melhor valor, então atualiza
				// o melhor.
				if (valorJogada > melhorValor) {
					melhorJogada.linha = i;
					melhorJogada.coluna = j;
					melhorValor = valorJogada;
				}
			}
		}
	}

	// printf("O valor da melhor jogada e : %d\n\n",
	//	 melhorValor);

	return melhorJogada;
}

// -----------------------------------Fim das jogadas inteligentes

// Função para exibir o tabuleiro do jogo
void mostrarTabuleiro(char tabuleiro[][LADO])
{
	printf("\n\n");
	printf("\t\t\t %c | %c | %c \n", tabuleiro[0][0],
		tabuleiro[0][1], tabuleiro[0][2]);
	printf("\t\t\t--------------\n");
	printf("\t\t\t %c | %c | %c \n", tabuleiro[1][0],
		tabuleiro[1][1], tabuleiro[1][2]);
	printf("\t\t\t--------------\n");
	printf("\t\t\t %c | %c | %c \n\n", tabuleiro[2][0],
		tabuleiro[2][1], tabuleiro[2][2]);
}

// Função para mostrar as instruções
void mostrarInstrucoes()
{
	printf("\t\t\t Jogo da Velha\n\n");
	printf("Escolha uma celula numerada de 1 a 9 como abaixo "
		"e jogue\n\n");

	printf("\t\t\t 1 | 2 | 3 \n");
	printf("\t\t\t--------------\n");
	printf("\t\t\t 4 | 5 | 6 \n");
	printf("\t\t\t--------------\n");
	printf("\t\t\t 7 | 8 | 9 \n\n");

	printf("-\t-\t-\t-\t-\t-\t-\t-\t-\t-\n\n");
}

// Função para inicializar o jogo
void inicializar(char tabuleiro[][LADO], int jogadas[])
{
	srand(time(NULL));

	// Inicialmente, o tabuleiro está vazio
	for (int i = 0; i < LADO; i++) {
		for (int j = 0; j < LADO; j++)
			tabuleiro[i][j] = ' ';
	}

	// Preenche as jogadas com números
	for (int i = 0; i < LADO * LADO; i++)
		jogadas[i] = i;

	// Embaralha as jogadas
	for (int i = 0; i < LADO * LADO; i++) {
		int indiceAleatorio = rand() % (LADO * LADO);
		int temporario = jogadas[i];
		jogadas[i] = jogadas[indiceAleatorio];
		jogadas[indiceAleatorio] = temporario;
	}
}

// Função para declarar o vencedor do jogo
void declararVencedor(int deQuemEhAVez)
{
	if (deQuemEhAVez == COMPUTADOR)
		printf("O COMPUTADOR venceu\n");
	else
		printf("O HUMANO venceu\n");
}

// Função para verificar se alguma linha foi completada com
// jogadas do mesmo jogador
int linhaCompleta(char tabuleiro[][LADO])
{
	for (int i = 0; i < LADO; i++) {
		if (tabuleiro[i][0] == tabuleiro[i][1]
			&& tabuleiro[i][1] == tabuleiro[i][2]
			&& tabuleiro[i][0] != ' ')
			return 1;
	}
	return 0;
}

// Função para verificar se alguma coluna foi completada com
// jogadas do mesmo jogador
int colunaCompleta(char tabuleiro[][LADO])
{
	for (int i = 0; i < LADO; i++) {
		if (tabuleiro[0][i] == tabuleiro[1][i]
			&& tabuleiro[1][i] == tabuleiro[2][i]
			&& tabuleiro[0][i] != ' ')
			return 1;
	}
	return 0;
}

// Função para verificar se alguma diagonal foi completada com
// jogadas do mesmo jogador
int diagonalCompleta(char tabuleiro[][LADO])
{
	if ((tabuleiro[0][0] == tabuleiro[1][1]
		&& tabuleiro[1][1] == tabuleiro[2][2]
		&& tabuleiro[0][0] != ' ')
		|| (tabuleiro[0][2] == tabuleiro[1][1]
			&& tabuleiro[1][1] == tabuleiro[2][0]
			&& tabuleiro[0][2] != ' '))
		return 1;

	return 0;
}

// Função para verificar se o jogo terminou
int fimDeJogo(char tabuleiro[][LADO])
{
	return (linhaCompleta(tabuleiro) || colunaCompleta(tabuleiro)
			|| diagonalCompleta(tabuleiro));
}

// Função para jogar o Jogo da Velha
void jogarJogoDaVelha(int deQuemEhAVez)
{
	// Um tabuleiro 3*3 de Jogo da Velha para jogar
	char tabuleiro[LADO][LADO];
	int jogadas[LADO * LADO];

	// Inicializa o jogo
	inicializar(tabuleiro, jogadas);

	// Mostra as instruções antes de jogar
	mostrarInstrucoes();

	int indiceJogada = 0, x, y;

	// Continua jogando até o jogo acabar ou dar empate
	while (!fimDeJogo(tabuleiro) && indiceJogada != LADO * LADO) {
		if (deQuemEhAVez == COMPUTADOR) {

			char tabuleiroTemp[3][3];
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					if (tabuleiro[i][j] == 'X') {
						tabuleiroTemp[i][j] = 'x';
					}
					else if (tabuleiro[i][j] == 'O') {
						tabuleiroTemp[i][j] = 'o';
					}
					else {
						tabuleiroTemp[i][j] = '_';
					}
				}
			}
			struct Jogada estaJogada = encontrarMelhorJogada(tabuleiroTemp);
			x = estaJogada.linha;
			y = estaJogada.coluna;

			tabuleiro[x][y] = JOGADA_COMPUTADOR;
			printf("O COMPUTADOR colocou um %c na celula %d %d\n",
				JOGADA_COMPUTADOR, x, y);
			mostrarTabuleiro(tabuleiro);
			indiceJogada++;
			deQuemEhAVez = HUMANO;
		}
		else if (deQuemEhAVez == HUMANO) {
			int jogada;
			printf("Digite sua jogada (1-9): ");
			scanf("%d", &jogada);
			if (jogada < 1 || jogada > 9) {
				printf("Entrada invalida! Por favor, digite um "
					"numero entre 1 e 9.\n");
				continue;
			}
			x = (jogada - 1) / LADO;
			y = (jogada - 1) % LADO;
			if (tabuleiro[x][y] == ' ') {
				tabuleiro[x][y] = JOGADA_HUMANO;
				mostrarTabuleiro(tabuleiro);
				indiceJogada++;
				if (fimDeJogo(tabuleiro)) {
					declararVencedor(HUMANO);
					return;
				}
				deQuemEhAVez = COMPUTADOR;
			}
			else {
				printf("A celula %d ja esta ocupada. Tente "
					"novamente.\n",
					jogada);
			}
		}
	}

	// Se o jogo empatou
	if (!fimDeJogo(tabuleiro) && indiceJogada == LADO * LADO)
		printf("Deu empate\n");
	else {
		// Alternando o jogador para declarar o vencedor real
		if (deQuemEhAVez == COMPUTADOR)
			deQuemEhAVez = HUMANO;
		else if (deQuemEhAVez == HUMANO)
			deQuemEhAVez = COMPUTADOR;

		// Declara o vencedor
		declararVencedor(deQuemEhAVez);
	}
}

// Programa principal
int main()
{
	// Vamos jogar com o COMPUTADOR começando primeiro
	jogarJogoDaVelha(COMPUTADOR);

	return 0;
}