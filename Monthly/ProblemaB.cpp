#include <iostream>
#include <vector>
#include <unordered_map>

#define lli long long int

using namespace std;

// Matrix to store the grid
vector<vector<int>> matrix;

vector<int> remainingColumns;

// Max number of one's in each row and column
int r, c;

// Current number of cards left in each row
int currentR;

// Number of rows and columns in the grid
int nr, nc;

// Number of combinations
lli counter = 0;

// Estrutura para poder usar vetor como key em unordered_map
struct VectorHash
{
    size_t operator()(const vector<int> &vec) const
    {
        size_t hashValue = 0;

        for (int i : vec)
        {
            hashValue ^= hash<int>{}(i);
        }

        return hashValue;
    }
};

// Map para guardar as combinações já feitas
unordered_map<vector<int>, lli, VectorHash> myMap;

// Função para verificar se todas as colunas têm o número de cartas correto
int checkColumns()
{
    int dev = 1;

    for (int i = 0; i < remainingColumns.size(); i++)
    {
        if (remainingColumns[i] < 0)
        {
            return -1;
        }
        if (remainingColumns[i] != 0)
        {
            dev = 0;
        }
    }

    return dev;
}

// Função para contar o número de cartas que faltam em cada coluna
vector<int> countColumns()
{
    vector<int> columns(c, 0);

    for (int i = 0; i < remainingColumns.size(); i++)
    {
        columns[remainingColumns[i]]++;
    }

    return columns;
}

// Função usada recursivamente para contar as combinações possíveis
void countCombinations(int i, int j)
{
    // Verifica se alguma coluna tem algum valor a mais do que o permitido
    if (checkColumns() == -1)
    {
        return;
    }

    // Verifica se já existe uma solução
    if (checkColumns() == 1 && currentR == 0 && i == nr - 1)
    {
        counter++;
        return;
    }

    // Verifica se já ultrapassou a última coluna
    if (j == nc)
    {
        // Se não tiver completado a linha, para a recursividade
        if (currentR != 0)
        {
            return;
        }

        // Se estiver na última linha para a recursividade porque não tem cartas suficientes nas colunas
        if (i == nr - 1)
        {
            return;
        }

        // Passar para a próxima linha
        i++;
        j = 0;
        currentR = r;
    }

    // Verifica se a linha já está completa
    if (currentR == 0)
    {
        // Se estiver na última linha para a recursividade porque não tem cartas suficientes nas colunas
        if (i == nr - 1)
        {
            return;
        }

        // Passar para a próxima linha
        i++;
        j = 0;
        currentR = r;
    }

    // Quando necessário guardar o valor de counter para depois subtrair
    lli countTemp;
    // Vetor para guardar o número de cartas que faltam em cada coluna
    vector<int> remaining;

    // Verificar se é a primeira coluna
    if (j == 0)
    
    {
        // Calcular o número de cartas que faltam em cada coluna
        remaining = countColumns();
        remaining.push_back(i);

        // Verificar se já existe uma combinação igual
        if (myMap.find(remaining) != myMap.end())
        {
            // Incrementar o número de soluções e sair
            counter += myMap[remaining];
            return;
        }
        else
        {
            // Guardar o valor de counter
            countTemp = counter;
        }
    }

    // Marcar e chamar recursividade
    matrix[i][j] = 1;
    remainingColumns[j]--;
    // Necessário guardar porque sempre que se muda de linha damos reset ao currentR
    int temp = currentR;
    currentR--;
    countCombinations(i, j + 1);

    // Desmarcar e chamar recursividade
    matrix[i][j] = 0;
    currentR = temp;
    remainingColumns[j]++;
    countCombinations(i, j + 1);

    // Se for a primeira coluna, guardar a combinação
    if (j == 0)
    {
        myMap.insert({remaining, counter - countTemp});
    }
}

int main()
{
    int rep;

    cin >> rep;

    while (rep--)
    {
        cin >> nc >> nr >> c >> r;

        matrix.resize(nr, vector<int>(nc, 0));
        remainingColumns.resize(nc, c);
        // Numero de solucoes
        counter = 0;
        // numero de cartas que falta colocar na linha
        currentR = r;

        countCombinations(0, 0);

        cout << counter << endl;

        matrix.clear();
        remainingColumns.clear();
        myMap.clear();
    }

    return 0;
}