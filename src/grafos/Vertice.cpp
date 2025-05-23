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

bool Vertice::operator<(
  const Vertice& other
  ) const
{
  return indice < other.indice || indice == other.indice && label < other.label;
}

//------------------------------------------------------------

bool Vertice::operator==(
  const Vertice& other
  ) const
{
  return indice == other.indice && label == other.label;
}

//------------------------------------------------------------

Vertice& Vertice::operator=(
  const Vertice& other
)
{
  indice = other.indice;
  label = other.label;
  return *this;
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

void Vertice::setIndice(int novoIndice) {
  indice = novoIndice;
}

//------------------------------------------------------------

void Vertice::setCor(int novaCor)
{
  cor = novaCor;
}

//------------------------------------------------------------

int Vertice::getCor() const
{
  return cor;
}

//------------------------------------------------------------

void Vertice::aumentarGrau()
{
  ++grau;
}

//------------------------------------------------------------

void Vertice::diminuirGrau()
{
  --grau;
}

//------------------------------------------------------------

int Vertice::getGrau() const
{
    return grau;
}

//------------------------------------------------------------

void Vertice::aumentarSaturacao()
{
  ++saturacao;
}

//------------------------------------------------------------

int Vertice::getSaturacao() const
{
  return saturacao;
}

//------------------------------------------------------------
