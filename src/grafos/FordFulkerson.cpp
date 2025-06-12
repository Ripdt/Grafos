#include "FordFulkerson.h"
#include <queue>
#include <climits>
#include <algorithm>
#include <type_traits>

const int FordFulkerson::MAX_PASSOS_BUSCA_LOCAL;

ResultadoFordFulkerson FordFulkerson::encontrarFluxoMaximo(Grafo* grafoOriginal, int origem, int destino) {
    auto grafoResidual = clonarGrafo(grafoOriginal);
    int fluxoMaximo = 0;
    int passos = 0;
    std::vector<int> caminho;
    int fluxo;

    while (bfs(grafoResidual.get(), origem, destino, caminho, fluxo)) {
        passos++;
        for (size_t i = 1; i < caminho.size(); i++) {
            int u = caminho[i - 1];
            int v = caminho[i];
            atualizarFluxo(grafoResidual.get(), u, v, fluxo);
        }
        fluxoMaximo += fluxo;
    }

    return {std::move(grafoResidual), fluxoMaximo, passos};
}

SolucaoBuscaLocal FordFulkerson::otimizarFluxoBuscaLocal(Grafo* grafoOriginal, int origem, int destino, int maxIteracoes) {
    auto resultadoInicial = encontrarFluxoMaximo(grafoOriginal, origem, destino);
    auto melhorGrafo = clonarGrafo(grafoOriginal);
    int melhorFluxo = resultadoInicial.fluxoMaximo;
    int melhorias = 0;

    for (int iteracao = 0; iteracao < maxIteracoes; iteracao++) {
        bool melhorou = false;

        for (int u = 0; u < melhorGrafo->numeroVertices(); ++u) {
            auto vizinhos = melhorGrafo->vizinhosVertice(u);
            for (Vertice* vPtr : vizinhos) {
                int v = vPtr->getIndice();
                if (u == v) continue;

                auto vizinho = clonarGrafo(melhorGrafo.get());
                int peso = vizinho->pesoAresta(u, v);
                vizinho->removerAresta(u, v);
                vizinho->inserirAresta(v, u, peso);

                int fluxoVizinho = encontrarFluxoMaximo(vizinho.get(), origem, destino).fluxoMaximo;

                if (fluxoVizinho > melhorFluxo) {
                    melhorGrafo = std::move(vizinho);
                    melhorFluxo = fluxoVizinho;
                    melhorias++;
                    melhorou = true;
                    break;
                }
            }
            if (melhorou) break;
        }
        if (!melhorou) break;
    }

    return {std::move(melhorGrafo), melhorFluxo, melhorias};
}

bool FordFulkerson::bfs(Grafo* grafo, int origem, int destino, std::vector<int>& caminho, int& fluxoMinimo) {
    std::vector<bool> visitado(grafo->numeroVertices(), false);
    std::vector<int> anterior(grafo->numeroVertices(), -1);
    std::vector<int> capacidadeMinima(grafo->numeroVertices(), INT_MAX);
    std::queue<int> fila;

    fila.push(origem);
    visitado[origem] = true;

    while (!fila.empty()) {
        int atual = fila.front();
        fila.pop();

        for (Vertice* vizinho : grafo->vizinhosVertice(atual)) {
            int indiceVizinho = vizinho->getIndice();
            int residual = capacidadeResidual(grafo, atual, indiceVizinho);

            if (!visitado[indiceVizinho] && residual > 0) {
                capacidadeMinima[indiceVizinho] = std::min(capacidadeMinima[atual], residual);
                anterior[indiceVizinho] = atual;
                visitado[indiceVizinho] = true;
                fila.push(indiceVizinho);

                if (indiceVizinho == destino) {
                    fluxoMinimo = capacidadeMinima[destino];
                    caminho.clear();
                    for (int v = destino; v != -1; v = anterior[v]) {
                        caminho.insert(caminho.begin(), v);
                    }
                    return true;
                }
            }
        }
    }
    return false;
}

int FordFulkerson::capacidadeResidual(Grafo* grafo, int u, int v) {
    return grafo->existeAresta(u, v) ? grafo->pesoAresta(u, v) : 0;
}

void FordFulkerson::atualizarFluxo(Grafo* grafo, int u, int v, int fluxo) {
    int capacidadeDireta = capacidadeResidual(grafo, u, v);
    if (capacidadeDireta - fluxo > 0) {
        grafo->inserirAresta(u, v, capacidadeDireta - fluxo);
    } else {
        grafo->removerAresta(u, v);
    }

    int capacidadeReversa = capacidadeResidual(grafo, v, u);
    grafo->inserirAresta(v, u, capacidadeReversa + fluxo);
}

std::unique_ptr<Grafo> FordFulkerson::clonarGrafo(const Grafo* grafo) {
    if (auto* gLista = dynamic_cast<const GrafoLista*>(grafo)) {
        auto copia = std::make_unique<GrafoLista>(true, true);
        copiarEstruturaGrafo(gLista, copia.get());
        return copia;
    } else if (auto* gMatriz = dynamic_cast<const GrafoMatriz*>(grafo)) {
        auto copia = std::make_unique<GrafoMatriz>(true, true);
        copiarEstruturaGrafo(gMatriz, copia.get());
        return copia;
    }
    return nullptr;
}

template<typename T>
void FordFulkerson::copiarEstruturaGrafo(const T* original, T* copia) {
    for (size_t i = 0; i < original->numeroVertices(); ++i) {
        copia->inserirVertice(original->labelVertice(i));
    }
    
    if (dynamic_cast<const GrafoLista*>(original)) {
        auto* origLista = dynamic_cast<const GrafoLista*>(original);
        auto* copiaLista = dynamic_cast<GrafoLista*>(copia);
        for (size_t i = 0; i < origLista->numeroVertices(); ++i) {
            for (Vertice* vizinho : origLista->vizinhosVertice(i)) {
                copiaLista->inserirAresta(i, vizinho->getIndice(),
                    origLista->pesoAresta(i, vizinho->getIndice()));
            }
        }
    } else {
        auto* origMatriz = dynamic_cast<const GrafoMatriz*>(original);
        auto* copiaMatriz = dynamic_cast<GrafoMatriz*>(copia);
        for (size_t i = 0; i < origMatriz->numeroVertices(); ++i) {
            for (size_t j = 0; j < origMatriz->numeroVertices(); ++j) {
                if (origMatriz->existeAresta(i, j)) {
                    copiaMatriz->inserirAresta(i, j, origMatriz->pesoAresta(i, j));
                }
            }
        }
    }
}