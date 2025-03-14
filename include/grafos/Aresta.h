#ifndef ARESTA_H
#define ARESTA_H

//------------------------------------------------------------

#include "grafos/Vertice.h"

//------------------------------------------------------------

class Aresta
{
private:
  const Vertice* origem;
  const Vertice* destino;
  bool estaAtiva = false;
  const int peso;

public:
  Aresta(
    const Vertice* _origem,
    const Vertice* _destino,
    const int _peso
  );

  virtual ~Aresta() = default;

  const Vertice* getOrigem() const;

  const Vertice* getDestino() const;

  int getPeso() const;
};

//------------------------------------------------------------

#endif