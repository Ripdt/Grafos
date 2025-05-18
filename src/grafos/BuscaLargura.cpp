#include "grafos/BuscaLargura.h"

#include "grafos/Vertice.h"

#include <iostream>
#include <queue>
#include <set>

BuscaLargura::BuscaLargura(
  const Grafo& _grafo
) :
  grafo(_grafo)
{
}

std::vector<int> BuscaLargura::caminhoTodosOsVertices(
  const int origem
) const
{
  std::queue<Vertice*> pendentes;
  std::set<Vertice*> visitados;
  std::vector<int> caminho;

  pendentes.push(grafo.getVertice(origem));
  visitados.insert(grafo.getVertice(origem));

  while (!pendentes.empty()) {
    const Vertice* vertice = pendentes.front();
    caminho.push_back(vertice->getIndice());

    std::cout << vertice->getIndice() << " - " << vertice->getLabel() << std::endl;

    for (Vertice* vizinho : grafo.vizinhosVertice(vertice->getIndice())) {
      auto& resultado = visitados.insert(vizinho);
      if (resultado.second)
        pendentes.push(vizinho);
    }
    pendentes.pop();
  }

  return caminho;
}