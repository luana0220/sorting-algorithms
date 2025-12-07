#include "Gerenciador.hpp"
#include <vector>
#include "GeradorVetor.hpp"
#include <iomanip> // biblioteca para a manipulação da sáida em notação cientifíca(std::fixed e std::setprecision)

std::ofstream Gerenciador::resultados;

std::vector<std::vector<int>> Gerenciador::gerarVetorDeVetores(int tam, std::function<std::vector<int>(int tam)> gerarVetor)
{
    std::vector<std::vector<int>> vetorDeVetores;
    for (int i = 0; i < 10; i++)
    {
        // preenche o vetor com 10 vetores aleatórios/quase ordenados de tamanho tam
        vetorDeVetores.push_back(gerarVetor(tam));
    }
    return vetorDeVetores;
}

void Gerenciador::rodar10vzsMesmoVetor(std::function<void(std::vector<int> &vec)> ordenacao, std::vector<int> vetor, const std::string &cenario, const std::string &algoritmo)
{
    int tam = vetor.size();
    // variaveis para acumular os valores de tempo, comparações e trocas de cada execução
    double somaTempos = 0.0;
    double somaComparacoes = 0.0;
    double somaTrocas = 0.0;
    for (int i = 0; i < 10; i++)
    {
        Ordenacao::zerarDados();             // zera os dados antes de cada execução
        std::vector<int> copiaVetor = vetor; // cria uma cópia do vetor original para cada iteração
        Ordenacao::medirTempo(ordenacao, copiaVetor);
        somaTempos += Ordenacao::tempoExecucao;
        somaTrocas += Ordenacao::trocas;
        somaComparacoes += Ordenacao::comparacoes;
    }
    // imprime as medias das 10 execuções do vetor
    std::cout << std::fixed << std::setprecision(3) << "   " << "-Media de Trocas: " << somaTrocas / 10 << "\n";
    std::cout << std::fixed << std::setprecision(3) << "   " << "-Media de Comparacoes: " << somaComparacoes / 10 << "\n";
    std::cout << std::fixed << std::setprecision(3) << "   " << "-Media de Tempo: " << somaTempos / 10 << " milissegundos" << "\n";
    std::cout.unsetf(std::ios::floatfield);
    escrever(algoritmo, cenario, somaTrocas / 10, somaComparacoes / 10, somaTempos / 10, tam);
}

void Gerenciador::rodar10vzsVetorAleatorio(std::function<void(std::vector<int> &vec)> ordenacao, std::vector<int> vetor, double &mediaTrocas, double &mediaComp, double &mediaTempo)
{
    double somaTrocas = 0.0;
    double somaComparacoes = 0.0;
    double somaTempo = 0.0;

    for (int i = 0; i < 10; i++)
    {
        std::vector<int> copiaVetor = vetor; // cria uma cópia do vetor original
        Ordenacao::zerarDados();             // zera antes de cada execução
        Ordenacao::medirTempo(ordenacao, copiaVetor);

        somaTrocas += Ordenacao::trocas;
        somaComparacoes += Ordenacao::comparacoes;
        somaTempo += Ordenacao::tempoExecucao;
    }
    // médias das execuções individual de um vetor dentro do vetor de vetores através da passagem por referência
    mediaTrocas = somaTrocas / 10.0;
    mediaComp = somaComparacoes / 10.0;
    mediaTempo = somaTempo / 10.0;
}

void Gerenciador::testarVetoresAleatorios(std::function<void(std::vector<int> &vec)> ordenacao, std::vector<std::vector<int>> vetor, const std::string &cenario, const std::string &algoritmo)
{
    int tam = vetor[0].size();
    double somaMediasTrocas = 0.0;
    double somaMediaTempo = 0.0;
    double somaMediaComparacoes = 0.0;

    // as variaveis vão ser passadas por referência para a função rodar10vzsVetorAleatorio(...) e lá vão receber valores das médias dos vetores individuais
    double mTrocas = 0.0;
    double mComp = 0.0;
    double mTempo = 0.0;
    for (std::vector<int> vet : vetor)
    {
        rodar10vzsVetorAleatorio(ordenacao, vet, mTrocas, mComp, mTempo);
        somaMediasTrocas += mTrocas;
        somaMediaTempo += mTempo;
        somaMediaComparacoes += mComp;
    }
    // depois de testar todos os vetores 10 vzs cada imprime a média final
    std::cout << std::fixed << "   " << "-Media final de Trocas: " << somaMediasTrocas / vetor.size() << "\n";
    std::cout << std::fixed << "   " << "-Media final de Comparacoes: " << somaMediaComparacoes / vetor.size() << "\n";
    std::cout << std::fixed << std::setprecision(3) << "   " << "-Media final de Tempo: " << somaMediaTempo / vetor.size() << " milissegundos" << "\n";
    std::cout.unsetf(std::ios::floatfield);
    escrever(algoritmo, cenario, somaMediasTrocas / vetor.size(), somaMediaComparacoes / vetor.size(), somaMediaTempo / vetor.size(), tam);
}

void Gerenciador::abrirArq(const std::string &nomeArq)
{
    resultados.open(nomeArq, std::ios::out);
    if (!resultados.is_open())
        std::cerr << "Erro ao abrir arquivo " << nomeArq << std::endl;
    resultados << "Cenario, Tamanho,  Algoritmo, trocas, comparações, tempo" << std::endl;
}

void Gerenciador::fecharArq()
{
    if (resultados.is_open())
        resultados.close();
}

void Gerenciador::escrever(const std::string &algoritmo, const std::string &cenario, double trocas, double comparacoes, double tempo, int tam)
{
    resultados << cenario << "," << tam << "," << algoritmo << "," << std::fixed << trocas << "," << std::fixed << comparacoes << "," << std::fixed << std::setprecision(3) << tempo << std::endl;
}
void Gerenciador::executarTestes(const std::string &nomeArq)
{
    //abrirArq(nomeArq);
    // vetor que armazena os nomes dos algoritmos para serem usados na impressão e para testar cada algoritmo
    std::vector<std::string> nomesAlgoritmos = {"Bubble Sort", "Insertion Sort", "Selection Sort", "Quick Sort Lomuto", "Quick Sort Hoare", "Merge Sort"};
    // armazena as funções de ordenação para serem testadas
    std::vector<std::function<void(std::vector<int> & vec)>> vetorDeFuncoes = {Ordenacao::bubbleSort, Ordenacao::insertionSort, Ordenacao::selectionSort, Ordenacao::quickSortLomuto, Ordenacao::quickSortHoare, Ordenacao::mergeSort};
    // vetor que armazena os nomes do cenarios para serem usados na imprensão e para testar cada cenario
    std::vector<std::string> cenarios = {"Vetor Ordenado", "Vetor Inversamente Ordenado", "Vetor aleatorio", "Vetor quase ordenado"};

    // inicia o tamanho dos vetores com 10 e aumenta até 100000
    int tam = 10;
    while (tam <= 100000)
    {
        vetorOrdenado = GeradorVetor::gerarVetorCrescente(tam);
        vetorInverso = GeradorVetor::gerarVetorDecrescente(tam);
        vetoresAleatorios = gerarVetorDeVetores(tam, GeradorVetor::gerarVetorAleatorio);
        vetoresQuaseOrd = gerarVetorDeVetores(tam, GeradorVetor::gerarVetorQuaseOrdenado);

        for (int i = 0; i < nomesAlgoritmos.size(); i++)
        {
            std::cout << "==================================================================\n";
            std::cout << "                " << nomesAlgoritmos[i] << "\n";
            std::cout << "==================================================================\n\n";
            for (const std::string &cenario : cenarios)
            {
                if ((cenario == "Vetor aleatorio" || cenario == "Vetor quase ordenado") && nomesAlgoritmos[i] == "Bubble Sort" && tam == 100000 || ((cenario == "Vetor aleatorio" || cenario == "Vetor quase ordenado") && nomesAlgoritmos[i] == "Selection Sort" && tam == 100000) || ((cenario == "Vetor aleatorio" || cenario == "Vetor quase ordenado") && nomesAlgoritmos[i] == "Insertion Sort" && tam == 100000))
                {
                    std::cout << "Pulando teste: " << cenario << " com " << nomesAlgoritmos[i] << " de tamanho " << tam << " (muito lento)\n";
                    continue;
                }
                testarAlgoritmoEmCenario(vetorDeFuncoes[i], nomesAlgoritmos[i], tam, cenario);
            }
        }

        tam = tam * 10;
    }
    //fecharArq();
    resultados.open(nomeArq, std::ios::app); //std::ios::app para não sobrescrever o arquivo ao testar os que foram pulados por serem muito lentos
    resultados << "\n\n";
    std::cout << "==========================================================================\n";
    std::cout << "         TESTES SEPARADOS PARA VETORES QUE GERARAM STACK OVERFLOW\n";
    std::cout << "==========================================================================\n";
    // Testes manuais para os casos que geraram stack overflow
    vetorOrdenado = GeradorVetor::gerarVetorCrescente(20000);;
    vetorInverso = GeradorVetor::gerarVetorDecrescente(20000);;
    vetoresAleatorios = gerarVetorDeVetores(20000, GeradorVetor::gerarVetorAleatorio);
    vetoresQuaseOrd = gerarVetorDeVetores(20000, GeradorVetor::gerarVetorQuaseOrdenado);
    std::cout << "Vetor aleatorio - Bubble Sort - TAM: 20000\n";
    testarAlgoritmoEmCenario(Ordenacao::bubbleSort, "Bubble Sort", 20000, "Vetor aleatorio");
    std::cout << "Vetor quase ordenado - Bubble Sort - TAM: 20000\n";
    testarAlgoritmoEmCenario(Ordenacao::bubbleSort, "Bubble Sort", 20000, "Vetor quase ordenado");
    std::cout << "Vetor aleatorio - Selection Sort - TAM: 20000\n";
    testarAlgoritmoEmCenario(Ordenacao::selectionSort, "Selection Sort", 20000, "Vetor aleatorio");
    std::cout << "Vetor quase ordenado - Selection Sort - TAM: 20000\n";
    testarAlgoritmoEmCenario(Ordenacao::selectionSort, "Selection Sort", 20000, "Vetor quase ordenado");
    std::cout << "Vetor aleatorio - Insertion Sort - TAM: 20000\n";
    testarAlgoritmoEmCenario(Ordenacao::insertionSort, "Insertion Sort", 20000, "Vetor aleatorio");
    std::cout << "Vetor quase ordenado - Insertion Sort - TAM:  20000\n";
    testarAlgoritmoEmCenario(Ordenacao::insertionSort, "Insertion Sort", 20000, "Vetor quase ordenado");
    fecharArq();
}

void Gerenciador::testarAlgoritmoEmCenario(const std::function<void(std::vector<int> &)> &algoritmo, const std::string &nomeAlgoritmo, int tam, const std::string &cenario)
{
    if (cenario == "Vetor Ordenado")
    {
        std::cout << cenario << " -- TAM: " << tam << " -- " << std::endl;
        rodar10vzsMesmoVetor(algoritmo, vetorOrdenado, cenario, nomeAlgoritmo);
    }
    else if (cenario == "Vetor Inversamente Ordenado")
    {
        std::cout << cenario << " -- TAM: " << tam << " -- " << std::endl;
        rodar10vzsMesmoVetor(algoritmo, vetorInverso, cenario, nomeAlgoritmo);
    }
    else if (cenario == "Vetor aleatorio")
    {
        std::cout << cenario << " -- TAM: " << tam << " -- " << std::endl;
        testarVetoresAleatorios(algoritmo, vetoresAleatorios, cenario, nomeAlgoritmo);
    }
    else if (cenario == "Vetor quase ordenado")
    {
        std::cout << cenario << " -- TAM: " << tam << " -- " << std::endl;
        testarVetoresAleatorios(algoritmo, vetoresQuaseOrd, cenario, nomeAlgoritmo);
    }
    else
    {
        std::cerr << "Cenario desconhecido: " << cenario << std::endl;
    }
}