#include "GrafoLista.h"

#include "grafos/Aresta.h"

#include <algorithm>
#include <iostream>
#include <vector>

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
  ArestasPorVertice p(new Vertice(numeroVerticesAdicionados, label), ListaArestas());
  listaAdjacencia.insert(p);
  numeroVerticesAdicionados++;
  return true;
}

//------------------------------------------------------------

bool GrafoLista::removerVertice(const int indice) {
  Pointer<Vertice> vertice = buscaVertice(indice);
  if (vertice == nullptr) return false;

  for (auto& par : listaAdjacencia) {
      ListaArestas& arestas = par.second;
      for (auto it = arestas.begin(); it != arestas.end(); ) {
          if (it->getDestino()->getIndice() == indice) {
              it = arestas.erase(it);
          } else {
              ++it;
          }
      }
  }

  listaAdjacencia.erase(vertice);

  return true;
}

//------------------------------------------------------------

std::string GrafoLista::labelVertice(
  const int indice
)
{
  for (auto& pair : listaAdjacencia) {
    const Vertice* vertice = pair.first;
    if (vertice->getIndice() == indice)
      return vertice->getLabel();
  }

  return std::string();
}

//------------------------------------------------------------

bool GrafoLista::inserirAresta(const int origem, const int destino, const int peso) {
  Pointer<Vertice> verticeOrigem = buscaVertice(origem);
  Pointer<Vertice> verticeDestino = buscaVertice(destino);

  if (!verticeOrigem || !verticeDestino) return false;

  auto atualizarAresta = [](ListaArestas& arestas, Vertice* origem, Vertice* destino, int peso) {
      for (auto it = arestas.begin(); it != arestas.end(); ) {
          if (it->getDestino()->getIndice() == destino->getIndice()) {
              it = arestas.erase(it);
          } else {
              ++it;
          }
      }
      arestas.insert(Aresta(origem, destino, peso));
  };

  atualizarAresta(listaAdjacencia[verticeOrigem], verticeOrigem.getRaw(), verticeDestino.getRaw(), peso);

  if (!ehDirecionado) {
      atualizarAresta(listaAdjacencia[verticeDestino], verticeDestino.getRaw(), verticeOrigem.getRaw(), peso);
  }

  return true;
}

//------------------------------------------------------------

const Pointer<Vertice>& GrafoLista::buscaVertice(
  const int indice
) const
{
  for (auto& pair : listaAdjacencia) {
    if (pair.first->getIndice() == indice) 
      return pair.first;
  }
  return nullptr;
}

//------------------------------------------------------------

const Aresta* GrafoLista::buscaAresta(const Pointer<Vertice>& origem, const int destino) {
  auto it = listaAdjacencia.find(origem);
  if (it == listaAdjacencia.end()) return nullptr;

  for (const Aresta& aresta : it->second) {
      if (aresta.getDestino()->getIndice() == destino) {
          return &aresta;
      }
  }
  return nullptr;
}

//------------------------------------------------------------

bool GrafoLista::removerAresta(const int origem, const int destino) {
  Pointer<Vertice> verticeOrigem = buscaVertice(origem);
  if (!verticeOrigem) return false;

  const Aresta* aresta = buscaAresta(verticeOrigem, destino);
  if (!aresta) return false;

  listaAdjacencia[verticeOrigem].erase(*aresta);

  // Se não for direcionado, remover aresta destino -> origem
  if (!ehDirecionado) {
      Pointer<Vertice> verticeDestino = buscaVertice(destino);
      if (verticeDestino) {
          const Aresta* arestaInversa = buscaAresta(verticeDestino, origem);
          if (arestaInversa) {
              listaAdjacencia[verticeDestino].erase(*arestaInversa);
          }
      }
  }

  return true;
}

//------------------------------------------------------------

bool GrafoLista::existeAresta(
  const int origem, 
  const int destino
)
{
  return buscaAresta(buscaVertice(origem), destino) != nullptr;
}

//------------------------------------------------------------

int GrafoLista::pesoAresta(
  const int origem, 
  const int destino
)
{
  const Aresta* aresta = buscaAresta(buscaVertice(origem), destino);
  return aresta != nullptr ? aresta->getPeso() : 0;
}

//------------------------------------------------------------

std::vector<Vertice> GrafoLista::vizinhosVertice(const int indice) {
  Pointer<Vertice> vertice = buscaVertice(indice);
  if (!vertice) return {};

  std::vector<Vertice> vizinhos;
  auto it = listaAdjacencia.find(vertice);
  if (it == listaAdjacencia.end()) return {};

  for (const Aresta& aresta : it->second) {
      vizinhos.push_back(*aresta.getDestino());
  }

  return vizinhos;
}


//------------------------------------------------------------

void GrafoLista::imprime() {
  std::cout << "Grafo:" << std::endl;
  for (const auto& pair : listaAdjacencia) {
      const Vertice* vertice = pair.first;
      std::cout << "Vertice " << vertice->getIndice() << " (" << vertice->getLabel() << ") -> ";
      for (const Aresta& aresta : pair.second) {
          std::cout << "[ " << aresta.getDestino()->getIndice() << " (" << aresta.getDestino()->getLabel() << ")";
          if (ehPonderado) {
              std::cout << " - Peso: " << aresta.getPeso();
          }
          std::cout << " ] ";
      }
      std::cout << std::endl;
  }
}