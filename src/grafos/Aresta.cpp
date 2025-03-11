#include "Aresta.h"

//------------------------------------------------------------

Aresta::Aresta(
  const Vertice& _origem, 
  const Vertice& _destino, 
  const int _peso
) :
  origem(_origem),
  destino(_destino),
  peso(_peso)
{
}

//------------------------------------------------------------

const Vertice& Aresta::getOrigem() const
{
  return origem;
}

//------------------------------------------------------------

const Vertice& Aresta::getDestino() const
{
  return destino;
}

//------------------------------------------------------------

int Aresta::getPeso() const
{
  return peso;
}

//------------------------------------------------------------
