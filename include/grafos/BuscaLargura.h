#ifndef BUSCA_LARGURA_H
#define BUSCA_LARGURA_H

#include "grafos/Grafo.h"

class Vertice;

class BuscaLargura
{
  private:
    const Grafo& grafo;

  public:
    BuscaLargura(
      const Grafo& _grafo
    );

    void percorrerTodosOsVertices(
      const int origem
    ) const;
};
#endif
