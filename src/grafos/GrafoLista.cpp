#include "GrafoLista.h"

#include "grafos/Aresta.h"
#include <iostream>

//------------------------------------------------------------

GrafoLista::GrafoLista(
  const bool _ehDirecionado,
  const bool _ehPonderado
) : Grafo(_ehDirecionado, _ehPonderado)
{
}

//------------------------------------------------------------

bool GrafoLista::inserirVertice(
  const std::string label
)
{
  return false;
}

//------------------------------------------------------------

bool GrafoLista::removerVertice(const int indice)
{
  return false;
}

//------------------------------------------------------------

std::string GrafoLista::labelVertice(const int indice)
{
  return std::string();
}

//------------------------------------------------------------

void GrafoLista::imprime()
{
}

//------------------------------------------------------------

bool GrafoLista::inserirAresta(const int origem, const int destino, const int peso)
{
  return false;
}

//------------------------------------------------------------

bool GrafoLista::removerAresta(const int origem, const int destino)
{
  return false;
}

//------------------------------------------------------------

bool GrafoLista::existeAresta(const int origem, const int destino)
{
  return false;
}

//------------------------------------------------------------

int GrafoLista::pesoAresta(const int origem, const int destino)
{
  return 0;
}

//------------------------------------------------------------

std::vector<Vertice> GrafoLista::vizinhosVertice(const int indice)
{
  return std::vector<Vertice>();
}

//------------------------------------------------------------
