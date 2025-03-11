#include "Vertice.h"

//------------------------------------------------------------

Vertice::Vertice(
  const int _indice, 
  const std::string _label
) :
  indice(_indice),
  label(_label)
{
}

//------------------------------------------------------------

int Vertice::getIndice() const
{
  return indice;
}

//------------------------------------------------------------

std::string Vertice::getLabel() const
{
  return label;
}

//------------------------------------------------------------
