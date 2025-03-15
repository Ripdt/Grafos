#include "grafos/Aresta.h"

//------------------------------------------------------------

Aresta::Aresta(
  const Vertice* _origem, 
  const Vertice* _destino, 
  const int _peso
) :
  origem(_origem),
  destino(_destino),
  peso(_peso)
{
}

//------------------------------------------------------------

bool Aresta::operator==(
  const Aresta& aresta
  ) const
{
  return origem == aresta.getOrigem() && destino == aresta.getDestino() && peso == aresta.getPeso();
}

//------------------------------------------------------------

bool Aresta::operator<(
  const Aresta& aresta
  ) const
{
  return origem->getIndice() < aresta.getOrigem()->getIndice() &&
         destino->getIndice() < aresta.getDestino()->getIndice();
}

//------------------------------------------------------------

const Vertice* Aresta::getOrigem() const
{
  return origem;
}

//------------------------------------------------------------

const Vertice* Aresta::getDestino() const
{
  return destino;
}

//------------------------------------------------------------

int Aresta::getPeso() const
{
  return peso;
}

//------------------------------------------------------------
