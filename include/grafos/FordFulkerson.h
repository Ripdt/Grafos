#ifndef FORD_FULKERSON_H
#define FORD_FULKERSON_H

#include "grafos/Grafo.h"
#include "grafos/GrafoLista.h"
#include "grafos/GrafoMatriz.h"
#include <vector>
#include <memory>

struct ResultadoFordFulkerson {
    std::unique_ptr<Grafo> grafoResidual;
    int fluxoMaximo;
    int passosExecucao;
};

struct SolucaoBuscaLocal {
    std::unique_ptr<Grafo> grafoOtimizado;
    int fluxoMaximo;
    int melhoriasEncontradas;
};

class FordFulkerson {
public:
    static const int MAX_PASSOS_BUSCA_LOCAL = 100;

    static ResultadoFordFulkerson encontrarFluxoMaximo(Grafo* grafoOriginal, int origem, int destino);
    static SolucaoBuscaLocal otimizarFluxoBuscaLocal(Grafo* grafoOriginal, int origem, int destino, int maxIteracoes = MAX_PASSOS_BUSCA_LOCAL);

private:
    static bool bfs(Grafo* grafo, int origem, int destino, std::vector<int>& caminho, int& fluxoMinimo);
    static int capacidadeResidual(Grafo* grafo, int u, int v);
    static void atualizarFluxo(Grafo* grafo, int u, int v, int fluxo);
    static std::unique_ptr<Grafo> clonarGrafo(const Grafo* grafo);
    
    template<typename T>
    static void copiarEstruturaGrafo(const T* original, T* copia);
};
#endif