#include "grafos/AlgoritmoDijkstra.h"

#include <queue>
#include <memory>
#include <iostream>

struct CaminhoComparator {
    bool operator()(const Pointer<Caminho>& a, const Pointer<Caminho>& b) const {
        return a->distancia > b->distancia;  // menor distância tem prioridade
    }
};

AlgoritmoDijkstra::AlgoritmoDijkstra(
  const Grafo& _grafo
) : 
  grafo(_grafo)
{
}

void AlgoritmoDijkstra::rodar(
  const int origem
) const
{
  const Vertice* verticeOrigem = grafo.getVertice(origem);
  if (!verticeOrigem) return;

  using CaminhoPtr = Pointer<Caminho>;

  // fila de prioridade para os caminhos (menor distancia primeiro)
  std::priority_queue<CaminhoPtr, std::vector<CaminhoPtr>, CaminhoComparator> fila;

  // Cria o caminho inicial
  CaminhoPtr caminhoOrigem = Pointer<Caminho>(new Caminho(verticeOrigem));
  caminhoOrigem->distancia = 0.f;
  caminhoOrigem->caminho.push_back(verticeOrigem);

  menorCaminhoAteVertice.clear();
  menorCaminhoAteVertice[verticeOrigem->getIndice()] = caminhoOrigem;

  fila.push(caminhoOrigem);

  while (!fila.empty()) {
    CaminhoPtr caminhoAtual = fila.top();
    fila.pop();

    int indiceAtual = caminhoAtual->verticeDestino->getIndice();

    // Se já foi marcado (processado) continue
    if (menorCaminhoAteVertice[indiceAtual]->marcado) continue;

    menorCaminhoAteVertice[indiceAtual]->marcado = true;

    // Explora vizinhos
    for (const Vertice* vizinho : grafo.vizinhosVertice(indiceAtual)) {
      int idxVizinho = vizinho->getIndice();

      if (menorCaminhoAteVertice.find(idxVizinho) != menorCaminhoAteVertice.end() &&
          menorCaminhoAteVertice[idxVizinho]->marcado) {
        continue;  // já processado
      }

      float novaDistancia = caminhoAtual->distancia + grafo.pesoAresta(indiceAtual, idxVizinho);

      bool melhor = false;

      if (menorCaminhoAteVertice.find(idxVizinho) == menorCaminhoAteVertice.end()) {
        melhor = true;
      } else if (menorCaminhoAteVertice[idxVizinho]->distancia > novaDistancia) {
        melhor = true;
      }

      if (melhor) {
        // Cria novo caminho
        CaminhoPtr novoCaminho = Pointer<Caminho>(new Caminho(vizinho));
        novoCaminho->distancia = novaDistancia;
        novoCaminho->caminho = caminhoAtual->caminho;  // copia caminho até agora
        novoCaminho->caminho.push_back(vizinho);

        menorCaminhoAteVertice[idxVizinho] = novoCaminho;
        fila.push(novoCaminho);
      }
    }
  }

  // Impressão dos resultados
  for (const auto& pair : menorCaminhoAteVertice) {
    const int indice = pair.first;
    const Pointer<Caminho>& caminho = pair.second;
    std::cout << "Caminho para " << indice << ": ";
    for (const Vertice* vertice : caminho->caminho) {
      std::cout << vertice->getIndice() << " ";
    }
    std::cout << "(Distancia: " << caminho->distancia << ")" << std::endl;
  }
}
