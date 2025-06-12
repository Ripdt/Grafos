#include "FordFulkerson.h"
#include <queue>
#include <climits>

int FordFulkerson::encontrarFluxoMaximo(Grafo* grafoOriginal, int origem, int destino) {
    Grafo* grafoResidual = clonarGrafo(grafoOriginal);
    int fluxoMaximo = 0;
    std::vector<int> caminho;

    while (bfs(grafoResidual, origem, destino, caminho)) {
        int fluxo = INT_MAX;

        for (size_t i = 1; i < caminho.size(); i++) {
            int u = caminho[i - 1];
            int v = caminho[i];
            fluxo = std::min(fluxo, capacidadeResidual(grafoResidual, u, v));
        }

        for (size_t i = 1; i < caminho.size(); i++) {
            int u = caminho[i - 1];
            int v = caminho[i];
            atualizarFluxo(grafoResidual, u, v, fluxo);
        }

        fluxoMaximo += fluxo;
    }

    delete grafoResidual;
    return fluxoMaximo;
}

bool FordFulkerson::bfs(Grafo* grafo, int origem, int destino, std::vector<int>& caminho) {
    std::vector<bool> visitado(grafo->numeroVertices(), false);
    std::vector<int> anterior(grafo->numeroVertices(), -1);
    std::queue<int> fila;

    fila.push(origem);
    visitado[origem] = true;

    while (!fila.empty()) {
        int atual = fila.front();
        fila.pop();

        for (Vertice* vizinho : grafo->vizinhosVertice(atual)) {
            int indiceVizinho = vizinho->getIndice();

            if (!visitado[indiceVizinho] && capacidadeResidual(grafo, atual, indiceVizinho) > 0) {
                fila.push(indiceVizinho);
                visitado[indiceVizinho] = true;
                anterior[indiceVizinho] = atual;

                if (indiceVizinho == destino)
                    break;
            }
        }
    }

    caminho.clear();
    if (!visitado[destino]) return false;

    for (int v = destino; v != -1; v = anterior[v])
        caminho.insert(caminho.begin(), v);

    return true;
}

int FordFulkerson::capacidadeResidual(Grafo* grafo, int u, int v) {
    if (grafo->existeAresta(u, v)) {
        return grafo->pesoAresta(u, v);
    }
    return 0;
}

void FordFulkerson::atualizarFluxo(Grafo* grafo, int u, int v, int fluxo) {
    int capacidade = grafo->pesoAresta(u, v);
    grafo->removerAresta(u, v);
    if (capacidade - fluxo > 0) {
        grafo->inserirAresta(u, v, capacidade - fluxo);
    }

    int reversa = grafo->existeAresta(v, u) ? grafo->pesoAresta(v, u) : 0;
    grafo->removerAresta(v, u);
    grafo->inserirAresta(v, u, reversa + fluxo);
}

Grafo* FordFulkerson::clonarGrafo(const Grafo* grafo) {
    Grafo* copia = nullptr;

    if (auto* gLista = dynamic_cast<const GrafoLista*>(grafo)) {
        copia = new GrafoLista(true, true); // direcionado e ponderado
        for (size_t i = 0; i < gLista->numeroVertices(); ++i)
            copia->inserirVertice(gLista->labelVertice(i));

        for (size_t i = 0; i < gLista->numeroVertices(); ++i) {
            Vertice* v = gLista->getVertice(i);
            for (Vertice* vizinho : gLista->vizinhosVertice(i)) {
                int peso = gLista->pesoAresta(i, vizinho->getIndice());
                copia->inserirAresta(i, vizinho->getIndice(), peso);
            }
        }
    } else if (auto* gMatriz = dynamic_cast<const GrafoMatriz*>(grafo)) {
        copia = new GrafoMatriz(true, true);
        for (size_t i = 0; i < gMatriz->numeroVertices(); ++i)
            copia->inserirVertice(gMatriz->labelVertice(i));

        for (size_t i = 0; i < gMatriz->numeroVertices(); ++i) {
            for (size_t j = 0; j < gMatriz->numeroVertices(); ++j) {
                if (gMatriz->existeAresta(i, j)) {
                    int peso = gMatriz->pesoAresta(i, j);
                    copia->inserirAresta(i, j, peso);
                }
            }
        }
    }

    return copia;
}
