#ifndef BUSCA_LARGURA_H
#define BUSCA_LARGURA_H

#include "grafos/Grafo.h"

#include <vector>

class Vertice;

class BuscaLargura
{
  private:
    const Grafo& grafo;

  public:
    BuscaLargura(
      const Grafo& _grafo
    );

    std::vector<int> caminhoTodosOsVertices(
      const int origem
    ) const;
};
#endif
