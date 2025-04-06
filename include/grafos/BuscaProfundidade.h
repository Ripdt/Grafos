#ifndef BUSCA_PROFUNDIDADE_H
#define BUSCA_PROFUNDIDADE_H

#include "grafos/Grafo.h"

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

    std::vector<Vertice> buscarCaminhoParaTodosVertices(
      const int origem
    ) const;

  private:
    void buscarCaminhoParaTodosVertices(
      const int origem,
      std::vector<Vertice>& verticesVisitados
    ) const;

    bool foiVisitado(
      const Vertice& vertice,
      const std::vector<Vertice>& verticesVisitados
    ) const;
};
#endif
