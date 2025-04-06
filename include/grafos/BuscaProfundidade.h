#ifndef BUSCA_PROFUNDIDADE_H
#define BUSCA_PROFUNDIDADE_H

#include "grafos/Grafo.h"

#include <set>

class Vertice;

class BuscaProfundidade
{
  private:
    const Grafo& grafo;

  public:
    BuscaProfundidade(
      const Grafo& _grafo
    );

    void percorrerTodosOsVertices(
      const int origem
    ) const;

  private:
    void percorrerTodosOsVertices(
      const int origem,
      std::set<Vertice>& verticesVisitados,
      const int profundidade = 0
    ) const;
};
#endif
