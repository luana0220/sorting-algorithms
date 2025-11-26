#include "Gerenciador.hpp"
#include <vector>
#include "GeradorVetor.hpp"

std::vector<std::vector<int>> Gerenciador::gerarVetorDeVetores(int tam, std::function<std::vector<int>(int tam)> gerarVetor)
{
    std::vector<std::vector<int>> vetorDeVetores;
    for (int i = 0; i < 10; i++)
    {
        vetorDeVetores.push_back(gerarVetor(tam));
    }
    return vetorDeVetores;
}

void Gerenciador::rodar10vzsMesmoVetor(std::function<void(std::vector<int> &vec)> ordenacao, std::vector<int> vetor)
{
    double somaTempos = 0.0;
    double somaComparacoes = 0.0;
    double somaTrocas = 0.0;
    for (int i = 0; i < 10; i++)
    {
        Ordenacao::zerarDados();
        std::vector<int> copiaVetor = vetor; // cria uma cópia do vetor original para cada iteração
        Ordenacao::medirTempo(ordenacao, copiaVetor);
        somaTempos += Ordenacao::tempoExecucao;
        somaTrocas += Ordenacao::trocas;
        somaComparacoes += Ordenacao::comparacoes;
    }
    std::cout << "Media de Trocas: " << somaTrocas / 10 << "\n";
    std::cout << "Media de Comparacoes: " << somaComparacoes / 10 << "\n";
    std::cout << "Media de Tempo: " << somaTempos / 10 << "\n";
}

std::vector<std::vector<int>> Gerenciador::gerarVetorDeVetoresIguais(int tam, std::function<std::vector<int>(int tam)> gerarVetor)
{
    std::vector<std::vector<int>> vetorDeVetores;
    std::vector<int> vetorInicial = gerarVetor(tam);
    for (int i = 0; i < 5; i++)
    {
        vetorDeVetores.push_back(vetorInicial);
    }
    return vetorDeVetores;
}

void Gerenciador::rodar10vzsVetorAletaorio(std::function<void(std::vector<int> &vec)> ordenacao, std::vector<int> vetor)
{
    double somaTrocas = 0.0;
    double somaComparacoes = 0.0;
    double somaTempo = 0.0;

    for (int i = 0; i < 10; i++)
    {
        std::vector<int> copiaVetor = vetor; // cria uma cópia do vetor original
        Ordenacao::zerarDados(); // zera antes de cada execução
        Ordenacao::medirTempo(ordenacao, copiaVetor);

        somaTrocas += Ordenacao::trocas;
        somaComparacoes += Ordenacao::comparacoes;
        somaTempo += Ordenacao::tempoExecucao;
    }
    Ordenacao::trocas = somaTrocas / 10.0;
    Ordenacao::comparacoes = somaComparacoes / 10.0;
    Ordenacao::tempoExecucao = somaTempo / 10.0;
}


void Gerenciador::testarVetoresAleatorios(std::function<void(std::vector<int> &vec)> ordenacao, std::vector<std::vector<int>> vetor)
{
    double somaMediasTrocas = 0.0;
    double somaMediaTempo = 0.0;
    double somaMediaComparacoes = 0.0;
    for (std::vector<int> vet : vetor)
    {
        rodar10vzsVetorAletaorio(ordenacao, vet);
        // medias do vetor individual da iteração
        double mediaTrocas = Ordenacao::trocas / 10.0;
        double mediaComparacoes = Ordenacao::comparacoes / 10.0;
        double mediaTempo = Ordenacao::tempoExecucao / 10.0;

        somaMediasTrocas += mediaTrocas;
        somaMediaTempo += mediaTempo;
        somaMediaComparacoes += mediaComparacoes;
    }
    std::cout << "Media final de Trocas: " << somaMediasTrocas / 10 << "\n";
    std::cout << "Media final de Comparacoes: " << somaMediaComparacoes / 10 << "\n";
    std::cout << "Media final de Tempo: " << somaMediaTempo / 10 << "\n";
}

void Gerenciador::executarTestes()
{
    std::vector<int> vetorOrdenadoTamMil = GeradorVetor::gerarVetorCrescente(1000);
    std::vector<int> vetorInversoTamMil = GeradorVetor::gerarVetorDecrescente(1000);
    std::vector<std::vector<int>> vetoresAleatorioTamMil = gerarVetorDeVetores(1000, GeradorVetor::gerarVetorAleatorio);
    std::vector<std::vector<int>> vetoresQuaseOrdTamMil = gerarVetorDeVetores(1000, GeradorVetor::gerarVetorQuaseOrdenado);
    std::vector<int> copiaInsert = vetorOrdenadoTamMil;
    std::vector<int> copiaSelection = vetorOrdenadoTamMil;
    std::vector<int> copiaQuickL = vetorOrdenadoTamMil;
    std::vector<int> copiaQuickH = vetorOrdenadoTamMil;

    std::cout << " -- TESTE COM VETORES DE TAMANHO 1000 -- " << std::endl;
    std::cout << "-- Vetor ordenado --" << std::endl;
    std::cout << "Bubble Sort" << std::endl;
    rodar10vzsMesmoVetor(Ordenacao::bubbleSort, vetorOrdenadoTamMil);
    std::cout << std::endl;
    std::cout << "Insert Sort" << std::endl;
    rodar10vzsMesmoVetor(Ordenacao::insertionSort, copiaInsert);
    std::cout << std::endl;
    std::cout << "Selection Sort" << std::endl;
    rodar10vzsMesmoVetor(Ordenacao::selectionSort, copiaSelection);
    std::cout << std::endl;
    std::cout << "Quick Sort Lomuto" << std::endl;
    rodar10vzsMesmoVetor(Ordenacao::quickSortLomuto, copiaQuickL);
    std::cout << std::endl;
    std::cout << "Quick Sort Hoare" << std::endl;
    rodar10vzsMesmoVetor(Ordenacao::quickSortHoare, copiaQuickH);
    std::cout << std::endl;

    std::vector<int> copiaBubble = vetorInversoTamMil;
    copiaInsert = vetorInversoTamMil;
    copiaSelection = vetorInversoTamMil;
    copiaQuickL = vetorInversoTamMil;
    copiaQuickH = vetorInversoTamMil;


    std::cout << "-- Vetor inversamente ordenado --" << std::endl;
    std::cout << "Bubble Sort" << std::endl;
    rodar10vzsMesmoVetor(Ordenacao::bubbleSort, copiaBubble);
    std::cout << std::endl;
    std::cout << "Insert Sort" << std::endl;
    rodar10vzsMesmoVetor(Ordenacao::insertionSort, copiaInsert);
    std::cout << std::endl;
    std::cout << "Selection Sort" << std::endl;
    rodar10vzsMesmoVetor(Ordenacao::selectionSort, copiaSelection);
    std::cout << std::endl;
    std::cout << "Quick Sort Lomuto" << std::endl;
    rodar10vzsMesmoVetor(Ordenacao::quickSortLomuto, copiaQuickL);
    std::cout << std::endl;
    std::cout << "Quick Sort Hoare" << std::endl;
    rodar10vzsMesmoVetor(Ordenacao::quickSortHoare, copiaQuickH);
    std::cout << std::endl;

    std::vector<std::vector<int>> copi1 = vetoresAleatorioTamMil;
    std::vector<std::vector<int>> copi2 = vetoresAleatorioTamMil;
    std::vector<std::vector<int>> copi3 = vetoresAleatorioTamMil;
    std::vector<std::vector<int>> copi4 = vetoresAleatorioTamMil;
    std::vector<std::vector<int>> copi5 = vetoresAleatorioTamMil;

    std::cout << "-- Vetor aleatório --" << std::endl;
    std::cout << "Bubble Sort" << std::endl;
    testarVetoresAleatorios(Ordenacao::bubbleSort, copi1);
    std::cout << std::endl;
    std::cout << "Insert Sort" << std::endl;
    testarVetoresAleatorios(Ordenacao::insertionSort, copi2);
    std::cout << std::endl;
    std::cout << "Selection Sort" << std::endl;
    testarVetoresAleatorios(Ordenacao::selectionSort, copi3);
    std::cout << std::endl;
    std::cout << "Quick Sort Lomuto" << std::endl;
    testarVetoresAleatorios(Ordenacao::quickSortLomuto, copi4);
    std::cout << std::endl;
    std::cout << "Quick Sort Hoare" << std::endl;
    testarVetoresAleatorios(Ordenacao::quickSortHoare, copi5);
    std::cout << std::endl;

    copi1 = vetoresQuaseOrdTamMil;
    copi2 = vetoresQuaseOrdTamMil;
    copi3 = vetoresQuaseOrdTamMil;
    copi4 = vetoresQuaseOrdTamMil;
    copi5 = vetoresQuaseOrdTamMil;
    

    std::cout << "-- Vetor quase ordenado --" << std::endl;
    std::cout << "Bubble Sort" << std::endl;
    testarVetoresAleatorios(Ordenacao::bubbleSort, copi1);
    std::cout << std::endl;
    std::cout << "Insert Sort" << std::endl;
    testarVetoresAleatorios(Ordenacao::insertionSort, copi2);
    std::cout << std::endl;
    std::cout << "Selection Sort" << std::endl;
    testarVetoresAleatorios(Ordenacao::selectionSort, copi3);
    std::cout << std::endl;
    std::cout << "Quick Sort Lomuto" << std::endl;
    testarVetoresAleatorios(Ordenacao::quickSortLomuto, copi4);
    std::cout << std::endl;
    std::cout << "Quick Sort Hoare" << std::endl;
    testarVetoresAleatorios(Ordenacao::quickSortHoare, copi5);
    std::cout << std::endl;

}