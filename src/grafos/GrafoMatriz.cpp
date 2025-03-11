#include "GrafoMatriz.h"

#include "grafos/Aresta.h"
#include "primitives/Matrix.h"


//------------------------------------------------------------

GrafoMatriz::GrafoMatriz(
  const bool _ehDirecionado, 
  const bool _ehPonderado
) :
  Grafo(_ehDirecionado, _ehPonderado),
  matriz(nullptr)
{
}

//------------------------------------------------------------

bool GrafoMatriz::inserirVertice(
  const std::string label
)
{
  return false;
}

//------------------------------------------------------------

bool GrafoMatriz::removerVertice(const int indice)
{
  return false;
}

//------------------------------------------------------------

std::string GrafoMatriz::labelVertice(const int indice)
{
  return std::string();
}

//------------------------------------------------------------

void GrafoMatriz::imprime()
{
}

//------------------------------------------------------------

bool GrafoMatriz::inserirAresta(const int origem, const int destino, const int peso)
{
  return false;
}

//------------------------------------------------------------

bool GrafoMatriz::removerAresta(const int origem, const int destino)
{
  return false;
}

//------------------------------------------------------------

bool GrafoMatriz::existeAresta(const int origem, const int destino)
{
  return false;
}

//------------------------------------------------------------

int GrafoMatriz::pesoAresta(const int origem, const int destino)
{
  return 0;
}

//------------------------------------------------------------

std::vector<Vertice> GrafoMatriz::vizinhosVertice(const int indice)
{
  return std::vector<Vertice>();
}

//------------------------------------------------------------
