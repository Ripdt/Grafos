#include <iostream>
#include "grafos/GrafoLista.h"
#include "grafos/GrafoMatriz.h"

using namespace std;

void menuGrafo(const std::string& titulo, Grafo& grafo) {
    int op;
    do {
        std::cout << "\n--- " << titulo << " ---\n";
        std::cout << "1 - Adicionar vértice\n";
        std::cout << "2 - Remover vértice\n";
        std::cout << "3 - Adicionar aresta\n";
        std::cout << "4 - Remover aresta\n";
        std::cout << "5 - Exibir grafo\n";
        std::cout << "6 - Voltar\n";
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
                int origem, destino, peso;
                std::cout << "Digite o índice de origem, destino e o peso da aresta: ";
                std::cin >> origem >> destino >> peso;
                grafo.inserirAresta(origem, destino, peso);
                break;
            }
            case 4: {
                int origem, destino;
                std::cout << "Digite os índices de origem e destino da aresta a ser removida: ";
                std::cin >> origem >> destino;
                grafo.removerAresta(origem, destino);
                break;
            }
            case 5:
                grafo.imprime();
                break;
            case 6:
                std::cout << "Voltando...\n";
                break;
            default:
                std::cout << "Opção inválida! Tente novamente.\n";
        }
    } while (op != 6);
}

int main() {
    int escolha, op;
    GrafoLista grafoLista(false, false); // Grafo não direcionado e não ponderado
    GrafoMatriz grafoMatriz(false, false);

    do {
        std::cout << "\n===== MENU PRINCIPAL =====\n";
        std::cout << "1 - Usar Lista de Adjacência\n";
        std::cout << "2 - Usar Matriz de Adjacência\n";
        std::cout << "3 - Sair\n";
        std::cout << "Escolha uma opção: ";
        std::cin >> escolha;

        switch (escolha) {
            case 1:
                menuGrafo("Lista de Adjacência", grafoLista);
                break;
            case 2:
                menuGrafo("Matriz de Adjacência", grafoMatriz);
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