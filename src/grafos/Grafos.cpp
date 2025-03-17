#include <iostream>

#include <locale>

#include "grafos/GrafoLista.h"
#include "grafos/GrafoMatriz.h"

const std::string TITULO_GRAFO_LISTA = "Grafo Lista de Adjacência";
const std::string TITULO_GRAFO_MATRIZ = "Grafo Matriz de Adjacência";

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
                std::string label;
                std::cout << "Digite o rótulo do vértice: ";
                std::cin >> label;
                grafo.inserirVertice(label);
                break;
            }
            case 2: {
                int indice;
                std::cout << "Digite o índice do vértice a ser removido: ";
                std::cin >> indice;
                grafo.removerVertice(indice);
                break;
            }
            case 3: {
                int indice;
                std::cout << "Digite o índice do vértice a ser consultado: ";
                std::cin >> indice;
                std::cout << "\t Nome: " << grafo.labelVertice(indice) << std::endl;
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
                grafo.inserirAresta(origem, destino, peso);
                break;
            }
            case 6: {
                int origem, destino;
                std::cout << "Digite os índices de origem e destino da aresta a ser removida: ";
                std::cin >> origem >> destino;
                grafo.removerAresta(origem, destino);
                break;
            }
            case 7: {
                int origem, destino;
                std::cout << "Digite os índices de origem e destino da aresta a ser consultada: ";
                std::cin >> origem >> destino;
                std::cout << "\t Peso: " << grafo.pesoAresta(origem, destino) << std::endl;
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
