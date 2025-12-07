#ifndef GERENDIADOR_HPP
#define GERENDIADOR_HPP
#include <iostream>
#include <vector>
#include "Ordenacao.hpp"
#include "GeradorVetor.hpp"
#include <functional>
#include <iostream>
#include <fstream>
#include <string>

class Gerenciador
{
    private:
    // não é necessario inicializar pois na classe vector os vetores já são inicializados vazios
    std::vector<int> vetorOrdenado;
    std::vector<int> vetorInverso;
    std::vector<std::vector<int>> vetoresAleatorios;
    std::vector<std::vector<int>> vetoresQuaseOrd;
    static std::ofstream resultados;

    // a função executa um mesmo vetor 10 vezes, aramazena a média das trocas, tempo de execução e comparações nos contadores da classe Ordenação e imprime
    //OBS: vai ser utilizada apenas para vetores ordenados e inversamente ordenados
    void rodar10vzsMesmoVetor(std::function<void(std::vector<int> &vec)> ordenacao, std::vector<int> vetor, const std::string& cenario, const std::string& algoritmo);

    // retorna um vetor de vetores para testar cada um na função rodar10vzsVetorAleatorio(...)
    std::vector<std::vector<int>> gerarVetorDeVetores(int tam, std::function<std::vector<int>(int tam)> gerarVetor);
    void testarVetoresAleatorios(std::function<void(std::vector<int> &vec)> ordenacao, std::vector<std::vector<int>> vetor, const std::string& cenario, const std::string& algoritmo);

    //função que recebe um vetor de vetores aleatórios e executa o algoritmo 10 vzs para cada vetor e incrementa as médias passadas por referência
    void rodar10vzsVetorAleatorio(std::function<void(std::vector<int> &vec)> ordenacao, std::vector<int> vetor, double& mediaTrocas, double& mediaComp, double& mediaTempo);

   //manipula o arquivo  de resultados
    static void escrever(const std::string& algoritmo, const std::string& cenario, double trocas, double comparacoes, double tempo, int tam);
    static void abrirArq(const std::string& nomeArq);
    static void fecharArq();
public:
    // função geral para executar testes
    void executarTestes(const std::string& nomeArq);
    // função para testar um algoritmo em um cenário especifíco
    //OBS: a função precisa ser pública para depois os cenários que geraram stack overflow possam ser testados manualmente
    void testarAlgoritmoEmCenario(const std::function<void(std::vector<int>&)> &algoritmo,const std::string &nomeAlgoritmo,int tam, const std::string &cenario);
};

#endif