#ifndef ORDENACAO_HPP
#define ORDENACAO_HPP
#include <iostream>
#include <vector>
#include <functional> // biblioteca para std::function

class Ordenacao
{
private:
    // funções privadas de quick sort lomuto e hoare
    static int particionaLomuto(std::vector<int> &vec, int inicio, int fim);
    static void quickSortLomutoRec(std::vector<int> &vec, int inicio, int fim);
    static int particionaHoare(std::vector<int> &vec, int inicio, int fim);
    static void quickSortHoareRec(std::vector<int> &vec, int inicio, int fim);
    // atributos
public:
    static long long trocas;
    static long comparacoes;
    static long long tempoExecucao;
    static void bubbleSort(std::vector<int> &vec);      // flutua o maior elemento para o final do vetore vai  diminuindo o tamanho do vetor a cada iteração
    static void selectionSort(std::vector<int> &vec);   // seleciona o menor elemento e troca com o primeiro elemento do vetor não ordenado
    static void insertionSort(std::vector<int> &vec);   // insere o elemento na posição correta do vetor ordenado
    static void quickSortLomuto(std::vector<int> &vec); // usa o método de partição de Lomuto(último elemento como pivô)
    static void quickSortHoare(std::vector<int> &vec);
    static void troca(int &a, int &b); // função implementada para facilitar a contagem de trocas
    // std::function é para receber qualquer função de ordenação, e medir o tempo dela
    static void medirTempo(std::function<void(std::vector<int> &)> funcaoOrdenacao, std::vector<int> &vec); // calcula o tempo de execução da função de ordenação
    static long long getTrocas();
    static long long getTempo();
    static long getComparacoes();
    static void zerarDados(); // para os valores de trocas, comparações e resultados não sobreporem a cada método e repetição
};

#endif