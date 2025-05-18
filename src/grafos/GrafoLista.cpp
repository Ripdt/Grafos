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

bool GrafoLista::inserirVertice(const std::string label) {
  // Usar o tamanho atual da lista como índice (garante índices sequenciais)
  int novoIndice = vertices.size();
  auto vertice = new Vertice(novoIndice, label);
  vertices.push_back(vertice);
  listaAdjacencia[vertice] = ListaArestas();
  return true;
}

//------------------------------------------------------------

std::string GrafoLista::labelVertice(
  const int indice
) const
{
  for (auto& pair : listaAdjacencia) {
    const Vertice* vertice = pair.first;
    if (vertice->getIndice() == indice)
      return vertice->getLabel();
  }

  return std::string();
}

//------------------------------------------------------------

bool GrafoLista::inserirAresta(const int origem, const int destino, const float peso) {
  Vertice* verticeOrigem = buscaVertice(origem);
  Vertice* verticeDestino = buscaVertice(destino);

  if (!verticeOrigem || !verticeDestino) return false;

  // Criar a nova aresta
  const float pesoAresta = ehPonderado ? peso : 1;
  Aresta novaAresta(verticeOrigem, verticeDestino, pesoAresta);

  // Remover a aresta antiga, se existir
  ListaArestas* arestasOrigem = &listaAdjacencia[verticeOrigem];
  if (!arestasOrigem->erase(novaAresta)) {
    verticeOrigem->aumentarGrau();
  } 

  // Inserir a nova aresta
  arestasOrigem->insert(novaAresta);

  // Se o grafo não for direcionado, inserir a aresta inversa
  if (!ehDirecionado) {
      Aresta arestaInversa(verticeDestino, verticeOrigem, peso);
      ListaArestas& arestasDestino = listaAdjacencia[verticeDestino];
      if (!arestasDestino.erase(arestaInversa)) {
        verticeDestino->aumentarGrau();
      }
      arestasDestino.insert(arestaInversa);
  }

  return true;
}

//------------------------------------------------------------

Vertice* GrafoLista::buscaVertice(const size_t indice) const {
  for (const auto& pair : listaAdjacencia) {
      if (pair.first->getIndice() == indice) {
          return pair.first;
      }
  }
  return nullptr; // Retorna nullptr por valor
}

//------------------------------------------------------------

const Aresta* GrafoLista::buscaAresta(Vertice* origem, const int destino) const {
  auto it = listaAdjacencia.find(origem);
  if (it == listaAdjacencia.end()) return nullptr;

  // Procurar a aresta com o destino especificado
  for (const Aresta& aresta : it->second) {
      if (aresta.getDestino()->getIndice() == destino) {
          return &aresta;
      }
  }
  return nullptr;
}

//------------------------------------------------------------

bool GrafoLista::removerAresta(const int origem, const int destino) {
  Vertice* verticeOrigem = buscaVertice(origem);
  if (!verticeOrigem) return false;

  const Aresta* aresta = buscaAresta(verticeOrigem, destino);
  if (!aresta) return false;

  if (listaAdjacencia[verticeOrigem].erase(*aresta)) {
    verticeOrigem->diminuirGrau();
  }

  // Se não for direcionado, remover aresta destino -> origem
  if (!ehDirecionado) {
      Vertice* verticeDestino = buscaVertice(destino);
      if (verticeDestino) {
          const Aresta* arestaInversa = buscaAresta(verticeDestino, origem);
          if (arestaInversa) {
            if (listaAdjacencia[verticeDestino].erase(*arestaInversa)) {
              verticeDestino->diminuirGrau();
            }
          }
      }
  }

  return true;
}

//------------------------------------------------------------

bool GrafoLista::existeAresta(const int origem, const int destino) const {
  Vertice* verticeOrigem = buscaVertice(origem);
  if (!verticeOrigem) return false;

  return buscaAresta(verticeOrigem, destino) != nullptr;
}

//------------------------------------------------------------

float GrafoLista::pesoAresta(const int origem, const int destino) const {
  Vertice* verticeOrigem = buscaVertice(origem);
  if (!verticeOrigem) return 0;

  const Aresta* aresta = buscaAresta(verticeOrigem, destino);
  return aresta ? aresta->getPeso() : 0;
}

//------------------------------------------------------------

std::vector<Vertice*> GrafoLista::vizinhosVertice(const int indice) const {
  Vertice* vertice = buscaVertice(indice);
  if (vertice == nullptr) return {};

  std::vector<Vertice*> vizinhos;
  auto it = listaAdjacencia.find(vertice);
  if (it == listaAdjacencia.end()) return {};

  for (const Aresta& aresta : it->second) {
    vizinhos.push_back(aresta.getDestino());
  }

  return vizinhos;
}

//------------------------------------------------------------

void GrafoLista::imprime() const {
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

//------------------------------------------------------------

bool GrafoLista::removerVertice(const int indice) {
    Vertice* vertice = buscaVertice(indice);
    if (vertice == nullptr) return false;

    // Remover todas as arestas que apontam para este vértice
    for (auto& par : listaAdjacencia) {
      ListaArestas& arestas = par.second;
      for (auto it = arestas.begin(); it != arestas.end(); ) {
        if (it->getDestino()->getIndice() == indice) {
          it->getOrigem()->diminuirGrau();
          it = arestas.erase(it);
        } else {
          ++it;
        }
      }
    }

    // Remover o vértice da lista de adjacência
    listaAdjacencia.erase(vertice);
    vertices.erase(vertices.begin() + indice);

    // Reindexar os vértices restantes
    int novoIndice = 0;
    ListaAdjacencia novaListaAdj;

    for (auto& par : listaAdjacencia) {
        Vertice* v = par.first;
        v->setIndice(novoIndice); // Atualiza o índice do vértice
        novaListaAdj[v] = std::move(par.second);
        novoIndice++;
    }

    // Atualizar a lista de adjacência
    listaAdjacencia = std::move(novaListaAdj);

    return true;
}

//------------------------------------------------------------

Vertice* GrafoLista::getVertice(
  const size_t indice
) const
{
  return buscaVertice(indice);
}

//------------------------------------------------------------

size_t GrafoLista::numeroVertices() const
{
  return listaAdjacencia.size();
}

//------------------------------------------------------------