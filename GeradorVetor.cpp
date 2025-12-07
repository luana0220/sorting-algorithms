#include "GeradorVetor.hpp"
#include <numeric>   //std::iota para gerar uma sequência de números
#include <algorithm> //std::swap
#include<iostream>

std::vector<int> GeradorVetor::gerarVetorCrescente(int tamanho)
{

    std::vector<int> vetor(tamanho);
    std::iota(vetor.begin(), vetor.end(), 0); // preenche com valores crescentes a partir de 0

    return vetor;
}

std::vector<int> GeradorVetor::gerarVetorDecrescente(int tamanho)
{

    std::vector<int> vetor(tamanho);
    std::iota(vetor.begin(), vetor.end(), 0); // gera núemros em ordem crescente
    std::reverse(vetor.begin(), vetor.end());

    return vetor;
}

std::vector<int> GeradorVetor::gerarVetorAleatorio(int tamanho)
{
    std::vector<int> vetor(tamanho);
    std::random_device seed; // usado para gerar uma seed pro gerador, para iniciar
    static std::mt19937 gerador(seed()); // gerador de numeros aleatorios
    std::uniform_int_distribution<> intervalo(0, tamanho); // distribuicao uniforme entre 0 e tamanho

    for (int &num : vetor)
    {
        num = intervalo(gerador); // atribui um numero aleatorio a cada posicao do vetor
    }
 
    return vetor;
}

std::vector<int> GeradorVetor::gerarVetorQuaseOrdenado(int tamanho)
{

    std::vector<int> vetor = gerarVetorCrescente(tamanho);
    std::random_device seed;
    static std::mt19937 gerador(seed());
    std::uniform_int_distribution<> intervalo(0, tamanho);

    int numTrocas = tamanho / 10; // 10% dos elementos vao ser trocados para bagunçar o vetor
    for (int i = 0; i < numTrocas; i++)
    {
        int ele1 = intervalo(gerador);
        // escolhe duas posicoes aleatorias no vetor
        int ele2 = intervalo(gerador);
        std::swap(vetor[ele1], vetor[ele2]); // troca os elementos nas posicoes escolhidas
    }

    return vetor;
}
