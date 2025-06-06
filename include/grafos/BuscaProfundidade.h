#ifndef BUSCA_PROFUNDIDADE_H
#define BUSCA_PROFUNDIDADE_H

#include "grafos/Grafo.h"

#include <set>
#include <vector>

class Vertice;

class BuscaProfundidade
{
  private:
    const Grafo& grafo;

  public:
    BuscaProfundidade(
      const Grafo& _grafo
    );

    std::vector<int> percorrerTodosOsVertices(
      const int origem
    ) const;

  private:
    void percorrerTodosOsVertices(
      const int origem,
      std::set<Vertice*>& verticesVisitados,
      const int profundidade = 0
    ) const;
};
#endif
