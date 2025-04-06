#include "grafos/BuscaProfundidade.h"

#include "grafos/Vertice.h"

#include <iostream>

BuscaProfundidade::BuscaProfundidade(
  const Grafo& _grafo
) :
  grafo(_grafo)
{
}

void BuscaProfundidade::percorrerTodosOsVertices(
  const int origem
) const
{
  std::set<Vertice> caminho;
  caminho.insert(grafo.getVertice(origem));

  percorrerTodosOsVertices(origem, caminho);
}


void BuscaProfundidade::percorrerTodosOsVertices(
  const int origem,
  std::set<Vertice>& verticesVisitados,
  const int profundidade
) const
{
  if (verticesVisitados.size() > 1) {
    for (int i = 0; i < profundidade; i++)
      std::cout << "\t";
  }

  const Vertice& vertice = grafo.getVertice(origem);
  std::cout << vertice.getIndice() << " - " << vertice.getLabel() << std::endl;

  for (const Vertice& vertice : grafo.vizinhosVertice(origem)) {
    auto& resultado = verticesVisitados.insert(vertice);
    if (resultado.second)
      percorrerTodosOsVertices(vertice.getIndice(), verticesVisitados, profundidade + 1);
  }
}