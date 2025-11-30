#include <iostream>
#include <vector>
#include "Ordenacao.hpp"
#include "Gerenciador.hpp"
#include "GeradorVetor.hpp"


int main() {
    Gerenciador eu;
    Gerenciador ger;



    //eu.executarTestes("resultados.csv");
    //std::cout << "Teste para algoritmos que causaram stack overflow:" << std::endl;
    //std::cout << "-Quick lomuto - TAM: 100000 -- Vetor Ordenado" << "\n-Quick Sort Hoare - TAM: 100000 - Vetor Inversamnete Ordenado" << std::endl;
    //std::cout << "Quick Sort Lomuto - TAM: 50000" << std::endl;
    //eu.testarAlgoritmoEmCenario(Ordenacao::quickSortLomuto, "Quick Sort Lomuto", 50000, "Vetor Ordenado");
    //eu.testarAlgoritmoEmCenario(Ordenacao::quickSortLomuto, "Quick Sort Lomuto", 50000, "Vetor Inversamente Ordenado");
    //eu.testarAlgoritmoEmCenario(Ordenacao::quickSortLomuto, "Quick Sort Hoare", 100000, "Vetor Inversamente Ordenado");
   // eu.testarAlgoritmoEmCenario(Ordenacao::mergeSort,"Merge Sort", 100000, "Vetor Inversamente Ordenado");//dá certo
   //dá eu.testarAlgoritmoEmCenario(Ordenacao::quickSortLomuto, "Quick Sort Lomuto", 100000, "Vetor aleatório");
   //dá eu.testarAlgoritmoEmCenario(Ordenacao::quickSortHoare, "Quick Sort Hoare", 100000, "Vetor aleatório");
    //eu.testarAlgoritmoEmCenario(Ordenacao::quickSortLomuto, "Quick Sort Lomuto", 100000, "Vetor quase ordenado");
    //eu.testarAlgoritmoEmCenario(Ordenacao::quickSortHoare, "Quick Sort Hoare", 100000, "Vetor quase ordenado");
   // eu.testarAlgoritmoEmCenario(Ordenacao::bubbleSort, "Bubble Sort", 20000, "Vetor aleatório");
   // eu.testarAlgoritmoEmCenario(Ordenacao::bubbleSort, "Bubble Sort", 100000, "Vetor quase ordenado");
    //eu.testarAlgoritmoEmCenario(Ordenacao::insertionSort, "Insertion Sort", 100000, "Vetor aleatório");
     //eu.testarAlgoritmoEmCenario(Ordenacao::insertionSort, "Insertion Sort", 100000, "Vetor quase ordenado");
     eu.testarAlgoritmoEmCenario(Ordenacao::selectionSort, "Selection Sort", 100000, "Vetor aleatório");
     eu.testarAlgoritmoEmCenario(Ordenacao::selectionSort, "Selection Sort", 100000, "Vetor quase ordenado");
     eu.testarAlgoritmoEmCenario(Ordenacao::mergeSort, "Merge Sort",100000, "Vetor aleatório");
     eu.testarAlgoritmoEmCenario(Ordenacao::mergeSort, "Merge Sort", 100000, "Vetor quase ordenado");
    return 0;
}


