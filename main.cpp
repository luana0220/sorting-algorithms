#include <iostream>
#include <vector>
#include "Ordenacao.hpp"
#include "Gerenciador.hpp"
#include "GeradorVetor.hpp"


/*std::vector<std::vector<int>> iteracaoVetorAleatorio(int tam) {
    std::vector<std::vector<int>> vetoresAleatorios;
    for(int i = 0; i < 2; i++) {
        vetoresAleatorios.push_back(GeradorVetor::gerarVetorAleatorio(tam));
    }
    return vetoresAleatorios;
}

double rodar10vzs(std::vector<int> vetor, Resultados& r) {
    double somaTempos = 0.0;
    for(int i = 0; i < 10; i++) {
        std::vector<int> copiaVetor = vetor; // cria uma cópia do vetor original para cada iteração
        r.tempo = Ordenacao::medirTempo(Ordenacao::selectionSort, vetor, r);
        somaTempos += r.tempo;
    }
    return somaTempos / 10.0;
}*/

int main()
{
    /*
    std::vector<int> vec = {2, 1, 4, 3};
    Resultados resultados;
    resultados.tempo = Ordenacao::medirTempo(Ordenacao::bubbleSort, vec, resultados);
    std::cout << resultados.comparacoes << " comparacoes, " << resultados.trocas << " trocas." << std::endl;
    std::cout << "Tempo de execucao: " << resultados.tempo << " microsegundos." << std::endl;
    for(int num : vec) {
        std::cout << num << " ";
    }

    std::vector<int> vecCrescente = GeradorVetor::gerarVetorCrescente(10);
    std::cout << "\nVetor Crescente: ";
    for(int num : vecCrescente) {
        std::cout << num << " ";
    }
    std::vector<int> vecDecrescente = GeradorVetor::gerarVetorDecrescente(10);
    std::cout << "\nVetor Decrescente: ";
    for(int num : vecDecrescente) {
        std::cout << num << " ";
    }
    std::vector<int> vecAleatorio = GeradorVetor::gerarVetorAleatorio(10);
    std::cout << "\nVetor Aleatorio: ";
    for(int num : vecAleatorio) {
        std::cout << num << " ";
    }
    std::vector<int> vecQuaseOrdenado = GeradorVetor::gerarVetorQuaseOrdenado(10);
    std::cout << "\nVetor Quase Ordenado: ";
    for(int num : vecQuaseOrdenado) {
        std::cout << num << " ";
    }*/
    /*std::vector<std::vector<int>> vetores = Gerenciador::gerarVetorDeVetorerIguais(10, GeradorVetor::gerarVetorCrescente);
    for(int i = 0; i < vetores.size(); i++) {
        std::cout << "Vetor " << i + 1 << ": ";
        for(int num : vetores[i]) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }

    std::vector<std::vector<int>> vetorTeste = Gerenciador::gerarVetorDeVetores(10, GeradorVetor::gerarVetorAleatorio);
    for(int i = 0; i < vetorTeste.size(); i++) {
        std::cout << "Vetor " << i + 1 << ": ";
        for(int num : vetorTeste[i]) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }

    std::vector<int> vt = {5,1,2,3,9,4};
    Ordenacao::medirTempo(Ordenacao::bubbleSort, vt);
    for(int num : vt) {
        std::cout << num << " ";
    }
    std::cout << "Trocas: " << Ordenacao::getTrocas() << std::endl;
    std::vector<int> vc = {1,2,3,4,5,6};
    Ordenacao::medirTempo(Ordenacao::bubbleSort, vc);
    std::cout << "Trocas: " << Ordenacao::getTrocas() << std::endl;
    Gerenciador::executarTestes();*/
    Gerenciador ordenar;
    ordenar.executarTestes();
    return 0;
}