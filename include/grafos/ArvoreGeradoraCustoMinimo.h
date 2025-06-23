#ifndef ARVORE_GERADORA_CUSTO_MINIMO_H
#define ARVORE_GERADORA_CUSTO_MINIMO_H

#include "grafos/Grafo.h"

class ArvoreGeradoraCustoMinimo {
public:
  ArvoreGeradoraCustoMinimo(
    Grafo& _grafo
  ) : g(_grafo) 
  {};

  ~ArvoreGeradoraCustoMinimo() = default;

  float kruskal() const;
  float prim(int raiz = 0);

private:
  Grafo& g;
};

#endif