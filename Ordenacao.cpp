#include "Ordenacao.hpp"
#include <chrono>

long long Ordenacao::trocas = 0;
long Ordenacao::comparacoes = 0;
long long Ordenacao::tempoExecucao = 0;

void Ordenacao::troca(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
    trocas++;
}

//metodos privados quick Sort Lomuto
int Ordenacao::particionaLomuto(std::vector<int>& vec, int inicio, int fim)
{
   int pivo = vec[fim]; //pivô é o último elemento
   int i = inicio - 1; 
   for(int j = inicio; j < fim; j++)

   {
       comparacoes++;
       if(vec[j] <= pivo) //troca se o elemento for menor ou igual ao pivô
       {
           i++;
           troca(vec[i], vec[j]);
       }
   }
   troca(vec[i + 1], vec[fim]);
   return i + 1;
}

void Ordenacao::quickSortLomutoRec(std::vector<int>& vec, int inicio, int fim)
{
   if(inicio < fim)
   {
       int pivoIndice = particionaLomuto(vec, inicio, fim);
       quickSortLomutoRec(vec, inicio, pivoIndice - 1);
       quickSortLomutoRec(vec, pivoIndice + 1, fim);
   }
}

// metodo public quick Sort Lomuto
void Ordenacao::quickSortLomuto(std::vector<int>& vec)
{
   quickSortLomutoRec(vec, 0, vec.size() - 1);
}

void Ordenacao::selectionSort(std::vector<int> &vec)
{
    int tam = vec.size();
    for (int i = 0; i < tam - 1; i++)
    {
        int indiceMenor = i;
        for (int j = i + 1; j < tam; j++) //encontra o menor elemento no vetor não ordenado 
        {
            comparacoes++;
            if (vec[j] < vec[indiceMenor])
            {
                indiceMenor = j;
            }
        }
        if (indiceMenor != i) //troca o menor elemento encontrado com o primeiro elemento do vetor
        {
            troca(vec[i], vec[indiceMenor]);
        }
    }
}

void Ordenacao::bubbleSort(std::vector<int> &vec)
{
    int tam = vec.size();
    //percorre todo o vetor
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
        if (!trocou) //se não houve troca, o vetor já está ordenado
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

        // Comparação que entra no while (j >= 0)
        comparacoes++;

        while (j >= 0 && vec[j] > chave)
        {
            // Comparação vec[j] > chave
            comparacoes++;

            // Deslocamento NÃO é troca
            vec[j + 1] = vec[j];

            j--;

            // Nova comparação j>=0 para repetir o while
            comparacoes++;
        }

        // Coloca o elemento na posição correta (não é troca)
        vec[j + 1] = chave;
    }
}

//função para medir tempo de execução
void  Ordenacao::medirTempo(std::function<void(std::vector<int>&)> funcaoOrdenacao, std::vector<int>& vec)
{
    auto inicio = std::chrono::high_resolution_clock::now();
    funcaoOrdenacao(vec);
    auto fim = std::chrono::high_resolution_clock::now();
    tempoExecucao = std::chrono::duration_cast<std::chrono::microseconds>(fim - inicio).count();
}

//quick Sort Hoare - métodos privados
int Ordenacao::particionaHoare(std::vector<int>& vec, int inicio, int fim)
{
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
        if (i >= j) {
            return j;
        }
        troca(vec[i], vec[j]);
    }
}

void Ordenacao::quickSortHoareRec(std::vector<int>& vec, int inicio, int fim)
{
    if (inicio < fim) // condição de parada, pois o índice inicial deve ser menor que o final
    {
        int pivoIndice = particionaHoare(vec, inicio, fim);// retorna o indice do pivô
        // partição do vetor a partir do índice do pivô
        quickSortHoareRec(vec, inicio, pivoIndice);
        quickSortHoareRec(vec, pivoIndice + 1, fim);
    }
}

// método público quick Sort Hoare
void Ordenacao::quickSortHoare(std::vector<int>& vec)
{
    quickSortHoareRec(vec, 0, vec.size() - 1);
}

long long Ordenacao::getTempo()
{
    return tempoExecucao;
}

long Ordenacao::getComparacoes()
{
    return comparacoes;
}
long long Ordenacao::getTrocas()
{
    return trocas;
}

void Ordenacao::zerarDados() {
    trocas = 0;
    comparacoes = 0;
    tempoExecucao = 0;
}