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
  int novoIndice = listaAdjacencia.size();
  Pointer<Vertice> novoVertice(new Vertice(novoIndice, label));
  listaAdjacencia[novoVertice] = ListaArestas();
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

  // Criar a nova aresta
  Aresta novaAresta(verticeOrigem.getRaw(), verticeDestino.getRaw(), peso);

  // Remover a aresta antiga, se existir
  ListaArestas& arestasOrigem = listaAdjacencia[verticeOrigem];
  arestasOrigem.erase(novaAresta); // Remove a aresta antiga (se existir)

  // Inserir a nova aresta
  arestasOrigem.insert(novaAresta);

  // Se o grafo não for direcionado, inserir a aresta inversa
  if (!ehDirecionado) {
      Aresta arestaInversa(verticeDestino.getRaw(), verticeOrigem.getRaw(), peso);
      ListaArestas& arestasDestino = listaAdjacencia[verticeDestino];
      arestasDestino.erase(arestaInversa); // Remove a aresta inversa antiga (se existir)
      arestasDestino.insert(arestaInversa);
  }

  return true;
}

//------------------------------------------------------------

Pointer<Vertice> GrafoLista::buscaVertice(const int indice) const {
  for (const auto& pair : listaAdjacencia) {
      if (pair.first->getIndice() == indice) {
          return pair.first; // Retorna uma cópia do shared_ptr/unique_ptr
      }
  }
  return nullptr; // Retorna nullptr por valor
}

//------------------------------------------------------------

const Aresta* GrafoLista::buscaAresta(const Pointer<Vertice>& origem, const int destino) {
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

bool GrafoLista::existeAresta(const int origem, const int destino) {
  Pointer<Vertice> verticeOrigem = buscaVertice(origem);
  if (!verticeOrigem) return false;

  return buscaAresta(verticeOrigem, destino) != nullptr;
}

//------------------------------------------------------------

int GrafoLista::pesoAresta(const int origem, const int destino) {
  Pointer<Vertice> verticeOrigem = buscaVertice(origem);
  if (!verticeOrigem) return 0;

  const Aresta* aresta = buscaAresta(verticeOrigem, destino);
  return aresta ? aresta->getPeso() : 0;
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

// -

bool GrafoLista::removerVertice(const int indice) {
    Pointer<Vertice> vertice = buscaVertice(indice);
    if (vertice == nullptr) return false;

    // Remover todas as arestas que apontam para este vértice
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

    // Remover o vértice da lista de adjacência
    listaAdjacencia.erase(vertice);

    // Reindexar os vértices restantes
    int novoIndice = 0;
    std::map<Pointer<Vertice>, ListaArestas> novaListaAdj;

    for (auto& par : listaAdjacencia) {
        Pointer<Vertice> v = par.first;
        v->setIndice(novoIndice); // Atualiza o índice do vértice
        novaListaAdj[v] = std::move(par.second);
        novoIndice++;
    }

    // Atualizar a lista de adjacência
    listaAdjacencia = std::move(novaListaAdj);

    // Atualizar o contador de vértices
    numeroVerticesAdicionados = listaAdjacencia.size(); // Correção crítica

    return true;
}