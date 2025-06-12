#include <iostream>
#include <locale>
#include <chrono>
#include <set>
#include <functional>

#include "grafos/GrafoLista.h"
#include "grafos/GrafoMatriz.h"
#include "grafos/GrafoStreamer.h"

#include "grafos/AlgoritmoDijkstra.h"
#include "grafos/BuscaLargura.h"
#include "grafos/BuscaProfundidade.h"
#include "grafos/Coloracao.h"

#include "grafos/FordFulkerson.h"

const std::string TITULO_GRAFO_LISTA = "Grafo Lista de Adjacência";
const std::string TITULO_GRAFO_MATRIZ = "Grafo Matriz de Adjacência";

template <typename T>
struct RespostaArgs {
    const T item;
    const std::string action;
};

template <typename T>
void estruturaResposta(const bool response, const RespostaArgs<T> &args) {
    if (!response) {
        std::cout << "\n[ERRO] Ocorreu um erro durante a operação! Tente novamente.\n";
        return;
    }

    std::cout << "\n=======================================\n"
              << "            RESULTADOS\n"
              << "=======================================\n"
              << " Item: " << args.item << "\n"
              << " Ação: " << args.action << "\n"
              << "=======================================\n";
}

void executarFordFulkerson(Grafo& grafo) {
  int op;
  do
  {
    std::cout << "\n--- Ford-Fulkerson ---\n";
    std::cout << "1 - Encontrar fluxo máximo\n";
    std::cout << "2 - Otimizar fluxo máximo\n";
    std::cout << "3 - Voltar\n";
    std::cout << "Escolha: ";
    std::cin >> op;
    int origem, destino;
    std::cout << "Digite o índice do vértice de origem: ";
    std::cin >> origem;
    std::cout << "Digite o índice do vértice de destino: ";
    std::cin >> destino;

    switch (op) {
      case 1:
        FordFulkerson::encontrarFluxoMaximo(&grafo, origem, destino);
        break;
      case 2:
        FordFulkerson::otimizadoFluxoBuscaLocal(&grafo, origem, destino);
        break;
    }

    std::cout << "Voltando...\n";
  } while (op != 2);
}

template <typename T>
void menuGrafo(T& grafo, const std::string& tituloGrafo) {
    int op;
    do {
        std::cout << "\n--- " << tituloGrafo << " ---\n";
        std::cout << "1 - Adicionar vértice\n";
        std::cout << "2 - Remover vértice\n";
        std::cout << "3 - Consultar vizinhos do vértice\n";
        std::cout << "4 - Adicionar aresta\n";
        std::cout << "5 - Remover aresta\n";
        std::cout << "6 - Exibir grafo\n";
        std::cout << "7 - Ford-Fulkerson \n";
        std::cout << "8 - Voltar\n";
        std::cout << "Escolha: ";
        std::cin >> op;

        switch (op) {
            case 1: {
                std::string input;
                std::cout << "Digite o rótulo do vértice: ";
                std::cin >> input;

                const bool response = grafo.inserirVertice(input);;

                estruturaResposta<std::string>(response, { input, "ADICAO" });
                break;
            }
            case 2: {
                int input;
                std::cout << "Digite o índice do vértice a ser removido: ";
                std::cin >> input;

                const bool response = grafo.removerVertice(input);

                estruturaResposta<int>(response, { input, "REMOCAO" });
                break;
            }
            case 3: {
                int indice;
                std::cout << "Digite o índice do vértice a ser consultado: ";
                std::cin >> indice;
                for (const Vertice* vertice : grafo.vizinhosVertice(indice)) {
                    std::cout << "\t Nome: " << vertice->getLabel() << std::endl;
                }
                std::cout << std::endl;
                break;
            }
            case 4: {
              int origem, destino;
              float peso;
              std::cout << "Digite o índice de origem, destino e o peso da aresta: ";
              std::cin >> origem >> destino >> peso;

              const bool response = grafo.inserirAresta(origem, destino, peso);
              estruturaResposta<std::string>(response, { origem + " - " + destino, "INSERCAO" });

              break;
            }
            case 5: {
                int origem, destino;
                std::cout << "Digite os índices de origem e destino da aresta a ser removida: ";
                std::cin >> origem >> destino;

                const bool response = grafo.removerAresta(origem, destino);
                estruturaResposta<std::string>(response, { origem + " - " + destino, "REMOCAO" });

                break;
            }
            case 6:
                grafo.imprime();
                break;
            case 7:
                executarFordFulkerson(grafo);
                break;
            case 8:
                std::cout << "Voltando...\n";
                break;
            default:
                std::cout << "Opção inválida! Tente novamente.\n";
        }
    } while (op != 9);
}

void executarColoracao(
  Grafo& grafo,
  const std::string& nomeAlgoritmo,
  const std::function<void(Coloracao&)>& algoritmo
) {
  grafo.resetarCores();
  auto start = std::chrono::high_resolution_clock::now();
  Coloracao coloracao(grafo);
  algoritmo(coloracao);
  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

  std::set<int> cores;
  for (size_t i = 0; i < grafo.numeroVertices(); i++) {
    cores.insert(grafo.getVertice(i)->getCor());
  }

  std::cout << "Algoritmo: " << nomeAlgoritmo << "\n";
  std::cout << "Tempo de execução: " << duration.count() << "ms\n";
  std::cout << "Número de cores: " << cores.size() << "\n";

  if (grafo.numeroVertices() < 10) {
    std::cout << "\nColoração dos vértices:\n";
    for (size_t i = 0; i < grafo.numeroVertices(); i++) {
      std::cout << "Vértice " << i << " (" << grafo.labelVertice(i) << "): Cor " 
                << grafo.getVertice(i)->getCor() << "\n";
    }
  }

  std::cout << "\n";
}

void lerGrafo()
{
  std::cout << "\n========================================\n";
  std::cout << "         CONFIGURAÇÃO DO GRAFO\n";
  std::cout << "========================================\n";
  std::cout << "Escolha o tipo de grafo:\n";
  std::cout << "  1 - Matriz de Adjacência\n";
  std::cout << "  2 - Lista de Adjacência\n";
  std::cout << ">> ";
  
  int tipo;
  std::cin >> tipo;
  Adjacencia adjacencia = tipo == 1 ? Adjacencia::MATRIZ : Adjacencia::LISTA;

  std::cout << "\nInsira o caminho do arquivo (ex: ex001): ";
  std::string caminho;
  std::cin >> caminho;

  if (caminho.substr(0,2).compare("ex") == 0) {
    caminho = "res/exemplo" + caminho.substr(2,3) + ".txt";
  }

  std::cout << "\nLendo grafo do arquivo: " << caminho << "...\n";

  GrafoStreamer grafoStreamer(adjacencia);
  if (Pointer<Grafo> grafo = grafoStreamer.ler(caminho)) {
    std::cout << "\n========================================\n";
    std::cout << "             GRAFO CARREGADO\n";
    std::cout << "========================================\n";
    grafo->imprime();
    std::cout << "\n";

    executarFordFulkerson(*grafo);

    int origem;
    std::cout << "Digite o índice do vértice de origem: ";
    std::cin >> origem;

    std::cout << "\n========================================\n";
    std::cout << "       BUSCA EM PROFUNDIDADE (DFS)\n";
    std::cout << "========================================\n";
    BuscaProfundidade buscaProfundidade(*grafo);
    buscaProfundidade.percorrerTodosOsVertices(origem);

    std::cout << "\n========================================\n";
    std::cout << "        BUSCA EM LARGURA (BFS)\n";
    std::cout << "========================================\n";
    BuscaLargura buscaLargura(*grafo);
    buscaLargura.caminhoTodosOsVertices(origem);

    std::cout << "\n========================================\n";
    std::cout << "     ALGORITMO DE DIJKSTRA (Caminhos)\n";
    std::cout << "========================================\n";
    AlgoritmoDijkstra algoritmo(*grafo);
    algoritmo.rodar(origem);

    std::cout << "\n========================================\n";
    std::cout << "     COLORAÇÃO DO GRAFO\n";
    std::cout << "========================================\n";

    executarColoracao(*grafo, "Welsh-Powell", [](Coloracao& c) { c.colorir_WelshPowell(); });
    executarColoracao(*grafo, "DSatur", [](Coloracao& c) { c.colorir_DSatur(); });
    executarColoracao(*grafo, "Greedy", [](Coloracao& c) { c.colorir_Greedy(); });
    executarColoracao(*grafo, "Força Bruta", [](Coloracao& c) { c.colorir_BruteForce(); });
  } else {
    std::cout << "\n[Erro] Não foi possível ler o grafo do arquivo.\n";
  }
}

int main() {
  setlocale(LC_ALL, "pt_BR.UTF-8");

  int escolha = 0;
    
  Pointer<GrafoLista> grafoLista = nullptr;
  Pointer<GrafoMatriz> grafoMatriz = nullptr;

  do {
    std::cout << "\n===== MENU PRINCIPAL =====\n";
    std::cout << "1 - Usar Lista de Adjacência\n";
    std::cout << "2 - Usar Matriz de Adjacência\n";
    std::cout << "3 - Carregar grafo\n";
    std::cout << "4 - Sair\n";
    std::cout << "Escolha uma opção: ";
    std::cin >> escolha;

    switch (escolha) {
      case 1:
        if (grafoLista == nullptr) {
          std::cout << "\n===== CONFIGURAÇÃO DO GRAFO =====\n";

          std::cout << "Escolha o tipo de grafo:\n";

          std::string direcionado, ponderado;
          std::cout << "\tDirecionado (S/N)? ";
          std::cin >> direcionado;
          std::cout << "\tPonderado (S/N)? ";
          std::cin >> ponderado;

          const bool ehDirecionado = direcionado == "S";
          const bool ehPonderado = ponderado == "S";
          grafoLista = new GrafoLista(ehDirecionado, ehPonderado);
        }
        menuGrafo(*grafoLista, TITULO_GRAFO_LISTA);
        break;
      case 2:
        if (grafoMatriz == nullptr) {
          std::cout << "\n===== CONFIGURAÇÃO DO GRAFO =====\n";

          std::cout << "Escolha o tipo de grafo:\n";

          std::string direcionado, ponderado;
          std::cout << "\tDirecionado (S/N)? ";
          std::cin >> direcionado;
          std::cout << "\tPonderado (S/N)? ";
          std::cin >> ponderado;

          const bool ehDirecionado = direcionado == "S";
          const bool ehPonderado = ponderado == "S";
          grafoMatriz = new GrafoMatriz(ehDirecionado, ehPonderado);
        }
        menuGrafo(*grafoMatriz, TITULO_GRAFO_MATRIZ);
        break;
      case 3:
        lerGrafo();
        break;
      case 4:
        std::cout << "Saindo do programa...\n";
        break;
      default:
        std::cout << "Opção inválida! Tente novamente.\n";
      }
  } while (escolha != 4);

  return 0;
}
