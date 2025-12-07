#include "Ordenacao.hpp"
#include <chrono>
#include <random>

std::random_device rd;
std::mt19937 gen(rd());


// inicialização dos contadores
long long Ordenacao::trocas = 0;
long Ordenacao::comparacoes = 0;
long long Ordenacao::tempoExecucao = 0;

void Ordenacao::troca(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
    trocas++;
}

// metodos privados quick Sort Lomuto
int Ordenacao::particionaLomuto(std::vector<int> &vec, int inicio, int fim)
{
    std::uniform_int_distribution<> intervalo (inicio, fim);
    int Indpivo = intervalo(gen); // sorteia um indice para o pivô aleatório para ajudar nos piores casos
    troca(vec[fim], vec[Indpivo]); // coloca o pivô na posição final para usar o método de Lomuto
    int pivo = vec[fim]; // pivô é o último elemento
    int i = inicio - 1;
    for (int j = inicio; j < fim; j++)

    {
        comparacoes++;
        if (vec[j] <= pivo) // troca se o elemento for menor ou igual ao pivô
        {
            i++;
            if( i != j) {
                troca(vec[i], vec[j]);
            }
            
        }
    }
    if (i + 1 != fim)
        troca(vec[i + 1], vec[fim]); // evita troca final inútil
    return i + 1;
}

void Ordenacao::quickSortLomutoRec(std::vector<int> &vec, int inicio, int fim)
{
    if (inicio < fim) // condição de parada
    {
        int pivoIndice = particionaLomuto(vec, inicio, fim);
        quickSortLomutoRec(vec, inicio, pivoIndice - 1);
        quickSortLomutoRec(vec, pivoIndice + 1, fim);
    }
}

// metodo public quick Sort Lomuto
void Ordenacao::quickSortLomuto(std::vector<int> &vec)
{
    quickSortLomutoRec(vec, 0, vec.size() - 1);
}

void Ordenacao::selectionSort(std::vector<int> &vec)
{
    int tam = vec.size();
    for (int i = 0; i < tam - 1; i++)
    {
        int indiceMenor = i;
        for (int j = i + 1; j < tam; j++) // encontra o menor elemento no vetor não ordenado
        {
            comparacoes++;
            if (vec[j] < vec[indiceMenor])
            {
                indiceMenor = j;
            }
        }
        if (indiceMenor != i) // troca o menor elemento encontrado com o primeiro elemento do vetor
        {
            troca(vec[i], vec[indiceMenor]);
        }
    }
}

void Ordenacao::bubbleSort(std::vector<int> &vec)
{
    int tam = vec.size();
    // percorre todo o vetor
    for (int i = 0; i < tam - 1; i++)
    {
        bool trocou = false;
        for (int j = 0; j < tam - i - 1; j++)
        {
            comparacoes++;
            if (vec[j] > vec[j + 1])
            {
                troca(vec[j], vec[j + 1]);
                trocou = true;
            }
        }
        if (!trocou) // se não houve troca, o vetor já está ordenado
            break;
    }
}

void Ordenacao::insertionSort(std::vector<int> &vec)
{
    int tam = vec.size();

    for (int i = 1; i < tam; i++)
    {
        int chave = vec[i];
        int j = i - 1;
        // primeira comparação para entrar no while
        comparacoes += 2;
        while (j >= 0 && vec[j] > chave)
        {
            // Deslocamento NÃO é troca
            vec[j + 1] = vec[j];
            trocas++; // consideramos essa movimentação como troca para facilitar
            j--;
        }
        vec[j + 1] = chave;
    }
}
void Ordenacao::merge(std::vector<int> &vec, int esq, int meio, int dir)
{
    int tam1 = meio - esq + 1; // tamanho do sub vetor esquerdo
    int tam2 = dir - meio;     // tamanho do sub vetor direito

    std::vector<int> subL(tam1), subR(tam2); // vetores temporários

    // copiando valores do vetor original para o subvetor esquerdo
    for (int i = 0; i < tam1; i++)
    {
        subL[i] = vec[esq + i];
    }
    // copiando valores do vetor original para o subvetor direito
    for (int j = 0; j < tam2; j++)
    {
        subR[j] = vec[meio + 1 + j];
    }

    int i = 0, j = 0, k = esq;

    // Merge das duas metades
    while (i < tam1 && j < tam2)
    {
        comparacoes++; // comparação subL[i] <= subR[j]

        // procura o menor valor entre os primeiros elementos de cad sub vetor
        if (subL[i] <= subR[j])
        {
            vec[k] = subL[i];
            i++;
        }
        else
        {
            vec[k] = subR[j];
            j++;
        }

        k++;
    }

    // caso sobre elementos nos subvetores, preenche as posições do vetor original
    while (i < tam1)
    {
        vec[k] = subL[i];
        i++;
        k++;
    }

    // Copia resto de subR
    while (j < tam2)
    {
        vec[k] = subR[j];
        j++;
        k++;
    }
}
void Ordenacao::mergeSortRec(std::vector<int> &vec, int esq, int dir)
{
    if (esq >= dir)
        return;

    int meio = esq + (dir - esq) / 2; // para dividir o vetor da forma mais igual possível
    // obs: seria possível usar (esq+dir)/ 2 porém pode ocorrer overflow com valores maiores
    mergeSortRec(vec, esq, meio);
    mergeSortRec(vec, meio + 1, dir);
    merge(vec, esq, meio, dir);
}

void Ordenacao::mergeSort(std::vector<int> &vec)
{
    if (vec.size() > 1)
        mergeSortRec(vec, 0, vec.size() - 1);
}
// função para medir tempo de execução
void Ordenacao::medirTempo(std::function<void(std::vector<int> &)> funcaoOrdenacao, std::vector<int> &vec)
{
    // marca o tempo inicial em que a funç~zo foi chamada
    auto inicio = std::chrono::high_resolution_clock::now();
    funcaoOrdenacao(vec);
    auto fim = std::chrono::high_resolution_clock::now();
    // calcula a diferença
    tempoExecucao = std::chrono::duration_cast<std::chrono::microseconds>(fim - inicio).count();
}

// quick Sort Hoare - métodos privados
int Ordenacao::particionaHoare(std::vector<int> &vec, int inicio, int fim)
{
    // escolhe elemento incial como pivo
    std::uniform_int_distribution<> intervalo (inicio, fim);
    int Indpivo = intervalo(gen); // sorteia um indice para o pivô aleatório para ajudar nos piores casos
    troca(vec[inicio], vec[Indpivo]); // coloca o pivô na posição inicial paar usar o método de Hoare
    int pivo = vec[inicio];
    int i = inicio - 1;
    int j = fim + 1;
    while (true)
    {
        do
        {
            i++;
            comparacoes++;
        } while (vec[i] < pivo);
        do
        {
            j--;
            comparacoes++;
        } while (vec[j] > pivo);
        if (i >= j)
        {
            return j;
        }
        troca(vec[i], vec[j]);
    }
}

void Ordenacao::quickSortHoareRec(std::vector<int> &vec, int inicio, int fim)
{
    if (inicio < fim) // condição de parada, pois o índice inicial deve ser menor que o final
    {
        int pivoIndice = particionaHoare(vec, inicio, fim); // retorna o indice do pivô
        // partição do vetor a partir do índice do pivô
        quickSortHoareRec(vec, inicio, pivoIndice);
        quickSortHoareRec(vec, pivoIndice + 1, fim);
    }
}

// método público quick Sort Hoare
void Ordenacao::quickSortHoare(std::vector<int> &vec)
{
    quickSortHoareRec(vec, 0, vec.size() - 1);
}

// função para zerar os dados e não acumular para cada cenério
void Ordenacao::zerarDados()
{
    trocas = 0;
    comparacoes = 0;
    tempoExecucao = 0;
}

