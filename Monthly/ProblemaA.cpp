// @authors Diogo Mota 2021238235 || Jóni Pereira 2021223430

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

// guarda o menor numero de rotacoes
int best;
int posMain;

int rows;
int columns;

// numero de moves disponiveis inicialmente
int moves;

// matriz com os numeros
vector<vector<int>> vault;

// vetor com as linhas que estao corretas
vector<bool> locks;

int checkSolution(int movesToUse)
{
    bool top = true;

    vector<int> movesToSolve(rows, 0);

    for (int i = 0; i < rows; i++)
    {
        // se a linha estiver certa avança uma iteracao do for
        if (locks[i])
        {
            continue;
        }

        for (int j = 0; j < columns; j++)
        {
            // se o numero nao estiver na linha certa nao bloqueia mais linhas
            if (vault[i][j] != (i + 1))
            {
                movesToSolve[vault[i][j] - 1] += abs(i - (vault[i][j] - 1));

                // se com o numero de moves ainda disponiveis for menor que o numero de moves necessarios sai
                if (movesToSolve[vault[i][j] - 1] > movesToUse)
                {
                    return -1;
                }

                top = false;
            }
        }

        if (top)
        {
            locks[i] = true;
        }
    }

    if (!top)
    {
        for (int i = rows - 1; i > 0; i--)
        {
            // se a linha estiver certa avança uma iteracao do for
            if (locks[i])
            {
                continue;
            }

            for (int j = 0; j < columns; j++)
            {
                if (vault[i][j] != i + 1)
                {
                    return 0;
                }
            }

            locks[i] = true;
        }
    }

    return top;
}

void moveHandle(int l, int c)
{
    posMain = vault[l][c];

    vault[l][c] = vault[l + 1][c];
    vault[l + 1][c] = vault[l + 1][c + 1];
    vault[l + 1][c + 1] = vault[l][c + 1];
    vault[l][c + 1] = posMain;
}

// funcao de recursividade
void func(int usedMoves, int l, int c)
{
    // verifica se já usamos mais moves do que a melhor solucao
    if (best <= usedMoves)
    {
        return;
    }


    // verificar estado atual do vault
    int check = checkSolution(moves - usedMoves);

    if (check == 1)
    {
        // vault esta correto
        best = usedMoves;
        return; // interromper este ramo recursivo
    }
    else if (check == -1)
    {
        // vault impossivel de resolver
        return;
    }

    // -1 já garante valores validos para handles
    for (int i = 0; i < rows - 1; ++i)
    {
        // se a linha atual estiver bloqueada avanca para a proxima
        if (locks[i])
        {
            continue;
        }

        if (locks[i + 1])
        {
            break;
        }

        for (int j = 0; j < columns - 1; ++j)
        {
            // avanca este handle porque foi rodado antes da chamada da recursao
            if (i == l && j == c)
            {
                continue;
            }

            if (!(vault[i][j] == vault[i][j + 1] && vault[i][j] == vault[i + 1][j] && vault[i][j] == vault[i + 1][j + 1]))
            {
                if (vault[i][j] == vault[i + 1][j + 1] && vault[i][j + 1] == vault[i + 1][j])
                {
                    // handle com numeros das diagonais iguais
                    // roda uma vez a direita
                    moveHandle(i, j);
                    func(usedMoves + 1, i, j);
                    // desfaz locks feitos na recursao
                    if (locks[i])
                    {
                        locks[i] = false;
                    }
                    if (locks[i + 1])
                    {
                        locks[i + 1] = false;
                    }

                    // como esta na diagonal rodar 4x e 2x é a mesma coisa
                    moveHandle(i, j);
                }
                else
                {
                    // handle sem nenhum caso especial
                    // roda uma vez a direita
                    moveHandle(i, j);
                    func(usedMoves + 1, i, j);

                    // desfaz loccks feitos na recursao
                    if (locks[i])
                    {
                        locks[i] = false;
                    }
                    if (locks[i + 1])
                    {
                        locks[i + 1] = false;
                    }

                    // segunda rotacao a direita
                    moveHandle(i, j);
                    func(usedMoves + 2, i, j);

                    // desfaz loccks feitos na recursao
                    if (locks[i])
                    {
                        locks[i] = false;
                    }
                    if (locks[i + 1])
                    {
                        locks[i + 1] = false;
                    }

                    // rotacao a esquerda
                    moveHandle(i, j);
                    func(usedMoves + 1, i, j);

                    // desfaz loccks feitos na recursao
                    if (locks[i])
                    {
                        locks[i] = false;
                    }
                    if (locks[i + 1])
                    {
                        locks[i + 1] = false;
                    }

                    // volta a posicao original
                    moveHandle(i, j);
                }
            }
        }
    }
}

int main()
{
    clock_t start;
    clock_t end;

    int nTestCases;

    cin >> nTestCases;

    // O(n)
    for (int k = 0; k < nTestCases; ++k)
    {
        int num;
        int validInput = 1;

        cin >> rows >> columns >> moves;

        // vetor que guarda o numero de repeticoes de cada numero
        vector<int> input(rows);

        // vault.resize(0);
        vault.resize(rows, vector<int>(columns));
        locks.resize(rows, false);

        // Preenche o vault atual - O(n)
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < columns; ++j)
            {
                cin >> num;

                // se o numero de repeticoes já for igual ao numero de colunas nao adiciona e coloca validInput a 0
                if (input[num - 1] == columns)
                {
                    validInput = 0;
                }

                // incrementa o numero de repeticoes
                input[num - 1]++;
                // adiciona o numero ao vault
                vault[i][j] = num;
            }
        }

        // inicializa a variavel com numero superior ao dos moves disponiveis
        best = moves + 1;

        // start = clock();
        if (validInput)
        {
            //  Executar algoritmo
            func(0, -1, -1); // Seleciona a posicao -1, -1 e executa sem rotação
        }
        // end = clock();

        // se best for menor que moves quer dizer que encontrou solucao
        if (best <= moves)
        {
            cout << best << "\n";
        }
        else
        {
            cout << "the treasure is lost!\n";
        }

        // cout << "Time: " << ((float)end - start) / CLOCKS_PER_SEC << endl;
        vault.clear();
        locks.clear();
    }

    return 0;
}