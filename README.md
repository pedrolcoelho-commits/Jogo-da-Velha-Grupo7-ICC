Jogo da Velha em C

Jogo da Velha (3x3) para jogar no terminal, jogador contra computador. O computador usa o algoritmo Minimax e, por isso, nunca perde: no pior caso, a partida termina em empate.

Integrantes: Pedro Lucas, Pedro Lemos, Milla

Como compilar

É necessário ter um compilador C instalado ou um compilador online

Sugestão de compilador online: https://www.onlinegdb.com




1. No menu inicial, escolha `1` para um novo jogo ou `2` para sair.
2. Escolha quem começa: `1` para o jogador humano (X) ou `2` para o computador (O).
3. Na sua vez, digite o número da casa (de 1 a 9), conforme o tabuleiro que aparecera na tela;
O jogo recusa números fora do intervalo e casas já ocupadas. A partida termina quando alguém completa uma linha, coluna ou diagonal, ou quando o tabuleiro fica cheio (empate).

Estratégia do computador

O computador usa o algoritmo **Minimax**, uma busca completa em árvore de jogadas. Antes de jogar, ele simula todas as sequências possíveis de jogadas, suas e do adversário, até o fim da partida, e escolhe a jogada que leva ao melhor resultado.

- **Pontuação:** cada tabuleiro final recebe uma nota (função `avaliar`): +10 se o computador vence, -10 se o jogador vence e 0 em caso de empate.
- **Simulação alternada** (função `minimax`): nos turnos do computador, ele escolhe a jogada de maior nota (maximizador). Nos turnos do humano, supõe que o adversário escolherá a de menor nota, ou seja, a pior para o computador (minimizador).
- **Recursão e backtracking:** cada jogada simulada é feita, avaliada recursivamente e depois desfeita, para testar a próxima possibilidade.
- **Escolha da jogada** (função `encontrarMelhorJogada`): o computador testa todas as casas vazias e joga na que recebeu a maior nota.

Como o computador sempre assume que o adversário joga da melhor forma possível, ele nunca perde. Se o humano errar, o computador vence.
