#include "GrafoLista.h"

#include "grafos/Aresta.h"

#include <algorithm>
#include <iostream>

//------------------------------------------------------------

GrafoLista::GrafoLista(
  const bool _ehDirecionado,
  const bool _ehPonderado
) : 
  Grafo(_ehDirecionado, _ehPonderado)
{
}

//------------------------------------------------------------

bool GrafoLista::inserirVertice(
  const std::string label
)
{
  ArestasPorVertice p(new Vertice(numeroVerticesAdicionados, label), std::list<Pointer<Aresta>>());
  listaAdjacencia.insert(p);
  numeroVerticesAdicionados++;
  return true;
}

//------------------------------------------------------------

bool GrafoLista::removerVertice(
  const int indice
)
{
  std::remove_if(listaAdjacencia.begin(), listaAdjacencia.end(), [&indice](const ArestasPorVertice& arestasPVertice) {
    const Vertice* vertice = arestasPVertice.first.getRaw();
    return vertice->getIndice() == indice;
  });

  for (auto& pair : listaAdjacencia) {
    std::list<Pointer<Aresta>>& lista = pair.second;
    std::remove_if(lista.begin(), lista.end(), [&indice](const Pointer<Aresta>& a) {
      return a->getDestino()->getIndice() == indice;
    });
  }

  return true;
}

//------------------------------------------------------------

std::string GrafoLista::labelVertice(
  const int indice
)
{
  for (auto& pair : listaAdjacencia) {
    const Vertice* vertice = pair.first.getRaw();
    if (vertice->getIndice() == indice)
      return vertice->getLabel();
  }

  return std::string();
}

//------------------------------------------------------------

void GrafoLista::imprime()
{
  for (auto& pair : listaAdjacencia) {
    const Vertice* vertice = pair.first.getRaw();
    std::cout << "\tVertice: " << vertice->getIndice() << " - " << vertice->getLabel().c_str() << std::endl;
    for (const Pointer<Aresta>& aresta : pair.second) {
      std::cout << "\t\t" << aresta->getDestino()->getIndice() << " - " << aresta->getDestino()->getLabel().c_str() << std::endl;
    }
  }
  std::cout << std::endl;
}

//------------------------------------------------------------

bool GrafoLista::inserirAresta(
  const int origem, 
  const int destino, 
  const int peso
)
{
  Vertice* verticeOrigem = nullptr, *verticeDestino = nullptr;
  for (auto& pair : listaAdjacencia) {
    verticeOrigem  = verticeOrigem == nullptr && pair.first->getIndice() == origem ? pair.first.getRaw() : nullptr;
    verticeDestino = verticeDestino == nullptr && pair.first->getIndice() == origem ? pair.first.getRaw() : nullptr;
    if (verticeOrigem != nullptr && verticeDestino != nullptr)
      break;
  }

  if (verticeDestino == nullptr || verticeOrigem == nullptr)
    return false;

  const int pesoAresta = ehPonderado ? peso : 1;
  listaAdjacencia[verticeOrigem].push_back(new Aresta(verticeOrigem, verticeDestino, pesoAresta));
  if (!ehDirecionado) {
    listaAdjacencia[verticeDestino].push_back(new Aresta(verticeDestino, verticeOrigem, pesoAresta));
  }

  return true;
}

//------------------------------------------------------------

bool GrafoLista::removerAresta(
  const int origem, 
  const int destino
)
{
  return false;
}

//------------------------------------------------------------

bool GrafoLista::existeAresta(
  const int origem, 
  const int destino
)
{
  return false;
}

//------------------------------------------------------------

int GrafoLista::pesoAresta(
  const int origem, 
  const int destino
)
{
  return 0;
}

//------------------------------------------------------------

std::vector<Vertice> GrafoLista::vizinhosVertice(
  const int indice
)
{
  return std::vector<Vertice>();
}

//------------------------------------------------------------
