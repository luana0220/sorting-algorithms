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
    // não é necessario incializar pois na classe vector os vetores já são inicializados vazios
    std::vector<int> vetorOrdenado;
    std::vector<int> vetorInverso;
    std::vector<std::vector<int>> vetoresAleatorios;
    std::vector<std::vector<int>> vetoresQuaseOrd;
    static std::ofstream resultados;

    // a função executa um mesmo vetor 10 vezes, aramazena a média das trocas, tempo de execução e comparações nos contadores da classe Ordenação e imprime
    //OBS: vai ser utilizada apenas paara vetores ordenados e inversamente ordenados
    void rodar10vzsMesmoVetor(std::function<void(std::vector<int> &vec)> ordenacao, std::vector<int> vetor, const std::string& cenario, const std::string& algoritmo);

    // retorna um vetor de vetores para testar cada um em outra função
    std::vector<std::vector<int>> gerarVetorDeVetores(int tam, std::function<std::vector<int>(int tam)> gerarVetor);
    void testarVetoresAleatorios(std::function<void(std::vector<int> &vec)> ordenacao, std::vector<std::vector<int>> vetor, const std::string& cenario, const std::string& algoritmo);

    //foi necessário criar outra função que possui um comportamento semelhante para os vetores aleatórios e quase ordenados, devido a forma de execução dos testes
    void rodar10vzsVetorAleatorio(std::function<void(std::vector<int> &vec)> ordenacao, std::vector<int> vetor, double& mediaTrocas, double& mediaComp, double& mediaTempo);

    //função para gerar um vetor que contém cópias de vetores 
    std::vector<std::vector<int>> fazerCopias(const std::vector<int>& vec, int quant);

    //função para gerar um vetor que contém cópias de vetores de vetores
    std::vector<std::vector<std::vector<int>>> fazerCopias(const std::vector<std::vector<int>>& vec, int quant);

    //chama as funções auxiliares que testam todos os cenários
    void rodarTodosOsAlgoritmos(int tam, const std::vector<std::string>& nomesAlgoritmos, const std::vector<std::function<void(std::vector<int> &vec)>>& vetorDefuncoes);

    // testa vetores ordenados e inversamente ordenados
    void vetoresOrdenadosEinversamente(std::vector<std::vector<int>>& copiasVec, const std::vector<std::string>& nomesAlgoritmos, const std::vector<std::function<void(std::vector<int> &vec)>>& vetorDefuncoes, const std::string& cenario);

    //testam vetores aleatórios e quase ordenados
    void vetoresAleatoriosEquaseOrd(std::vector<std::vector<std::vector<int>>>& copiasVec, const std::vector<std::string>& nomesAlgoritmos, const std::vector<std::function<void(std::vector<int> &vec)>>& vetorDefuncoes, const std::string& cenario);
    static void escrever(const std::string& algoritmo, const std::string& cenario, double trocas, double comparacoes, double tempo, int tam);
    static void abrirArq(const std::string& nomeArq);
    static void fecharArq();
public:
    // função geral para executar testes
    void executarTestes(const std::string& nomeArq);
    
void testarAlgoritmoEmCenario(const std::function<void(std::vector<int>&)> &algoritmo,const std::string &nomeAlgoritmo,int tam, const std::string &cenario);
};

#endif