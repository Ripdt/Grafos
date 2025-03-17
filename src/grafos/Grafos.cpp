#include <iostream>

#include <locale>

#include "grafos/GrafoLista.h"
#include "grafos/GrafoMatriz.h"

const std::string TITULO_GRAFO_LISTA = "Grafo Lista de Adjacência";
const std::string TITULO_GRAFO_MATRIZ = "Grafo Matriz de Adjacência";

template <typename T>
struct FeedbackArgs {
    const T item;
    const std::string action;
};

void menuGrafo(Grafo& grafo, const std::string& tituloGrafo) {
    int op;
    do {
        std::cout << "\n--- " << tituloGrafo << " ---\n";
        std::cout << "1 - Adicionar vértice\n";
        std::cout << "2 - Remover vértice\n";
        std::cout << "3 - Consultar nome do vértice\n";
        std::cout << "4 - Consultar vizinhos do vértice\n";
        std::cout << "5 - Adicionar aresta\n";
        std::cout << "6 - Remover aresta\n";
        std::cout << "7 - Consultar aresta\n";
        std::cout << "8 - Exibir grafo\n";
        std::cout << "9 - Voltar\n";
        std::cout << "Escolha: ";
        std::cin >> op;

        switch (op) {
            case 1: {
                std::string input;
                std::cout << "Digite o rótulo do vértice: ";
                std::cin >> input;


                const bool response = grafo.inserirVertice(input);;

                makeFeedbackResponse<std::string>(response, { input, action: "ADICAO" });

                break;
            }
            case 2: {
                int input;
                std::cout << "Digite o índice do vértice a ser removido: ";
                std::cin >> input;

                const bool response = grafo.removerVertice(input);

                makeFeedbackResponse<int>(response, { input, action: "REMOCAO" });
                break;
            }
            case 4: {
                int indice;
                std::cout << "Digite o índice do vértice a ser consultado: ";
                std::cin >> indice;
                for (const Vertice& vertice : grafo.vizinhosVertice(indice)) {
                    std::cout << "\t Nome: " << vertice.getLabel() << std::endl;
                }
                std::cout << std::endl;
                break;
            }
            case 5: {
                int origem, destino, peso;
                std::cout << "Digite o índice de origem, destino e o peso da aresta: ";
                std::cin >> origem >> destino >> peso;

                const bool response = grafo.inserirAresta(origem, destino, peso);
                makeFeedbackResponse<std::string>(response, { item: origem + " - " + destino, action: "INSERCAO" });

                break;
            }
            case 6: {
                int origem, destino;
                std::cout << "Digite os índices de origem e destino da aresta a ser removida: ";
                std::cin >> origem >> destino;

                const bool response = grafo.removerAresta(origem, destino);
                makeFeedbackResponse<std::string>(response, { item: origem + " - " + destino, action: "REMOCAO" });

                break;
            }
            case 8:
                grafo.imprime();
                break;
            case 9:
                std::cout << "Voltando...\n";
                break;
            default:
                std::cout << "Opção inválida! Tente novamente.\n";
        }
    } while (op != 9);
}

template <typename T>
void makeFeedbackResponse(const bool response, const FeedbackArgs<T> &args) {
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

int main() {
  setlocale(LC_ALL, "pt_BR.UTF-8");

  int escolha = 0;

  std::cout << "\n===== CONFIGURAÇÃO DO GRAFO =====\n";
    
  std::cout << "Escolha o tipo de grafo:\n";

  std::string direcionado, ponderado;
  std::cout << "\tDirecionado (S/N)? ";
  std::cin >> direcionado;
  std::cout << "\tPonderado (S/N)? ";
  std::cin >> ponderado;

  const bool ehDirecionado = direcionado == "S";
  const bool ehPonderado = ponderado == "S";
    
  GrafoLista grafoLista(ehDirecionado, ehPonderado);
  GrafoMatriz grafoMatriz(ehDirecionado, ehPonderado);

  do {
      std::cout << "\n===== MENU PRINCIPAL =====\n";
      std::cout << "1 - Usar Lista de Adjacência\n";
      std::cout << "2 - Usar Matriz de Adjacência\n";
      std::cout << "3 - Sair\n";
      std::cout << "Escolha uma opção: ";
      std::cin >> escolha;

      switch (escolha) {
          case 1:
              menuGrafo(grafoLista, TITULO_GRAFO_LISTA);
              break;
          case 2:
              menuGrafo(grafoMatriz, TITULO_GRAFO_MATRIZ);
              break;
          case 3:
              std::cout << "Saindo do programa...\n";
              break;
          default:
              std::cout << "Opção inválida! Tente novamente.\n";
      }
  } while (escolha != 3);

  return 0;
}
