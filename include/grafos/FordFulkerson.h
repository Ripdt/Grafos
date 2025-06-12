#ifndef FORD_FULKERSON_H
#define FORD_FULKERSON_H

#include "grafos/Grafo.h"
#include "grafos/Grafo.h"
#include "grafos/GrafoLista.h"
#include "grafos/GrafoMatriz.h"

class FordFulkerson {
public:
    static int encontrarFluxoMaximo(Grafo* grafoOriginal, int origem, int destino);

private:
    static bool bfs(Grafo* grafo, int origem, int destino, std::vector<int>& caminho);
    static Grafo* clonarGrafo(const Grafo* grafo);
    static int capacidadeResidual(Grafo* grafo, int u, int v);
    static void atualizarFluxo(Grafo* grafo, int u, int v, int fluxo);
};

#endif
