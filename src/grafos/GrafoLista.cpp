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
  ArestasPorVertice p(new Vertice(numeroVerticesAdicionados, label), ListaArestas());
  listaAdjacencia.insert(p);
  numeroVerticesAdicionados++;
  return true;
}

//------------------------------------------------------------

bool GrafoLista::removerVertice(
  const int indice
)
{
  //auto it = std::remove_if(listaAdjacencia.begin(), listaAdjacencia.end(), [&indice](const ArestasPorVertice& arestasPVertice) {
  //  const Vertice* vertice = arestasPVertice.first.getRaw();
  //  return vertice->getIndice() == indice;
  //});

  //listaAdjacencia.erase(it, listaAdjacencia.end());

  //for (auto& pair : listaAdjacencia) {
  //  ListaArestas& lista = pair.second;

  //  auto it = std::remove_if(lista.begin(), lista.end(), [&indice](const Pointer<Aresta>& a) {
  //    return a->getDestino()->getIndice() == indice;
  //    });
  //  lista.erase(it, lista.end());
  //}

//  --- Possibilidade de imp ---

//   bool GrafoLista::removerVertice(const int indice) {
//     // Remover o vértice da lista de adjacência
//     auto it = std::find_if(listaAdjacencia.begin(), listaAdjacencia.end(),
//         [&indice](const auto& par) {
//             return par.first->getIndice() == indice;
//         });

//     if (it != listaAdjacencia.end()) {
//         listaAdjacencia.erase(it);  // Remove o vértice do mapa
//     }

//     // Remover todas as arestas que têm o vértice como destino
//     for (auto& [_, lista] : listaAdjacencia) {
//         lista.erase(
//             std::remove_if(lista.begin(), lista.end(),
//                 [&indice](const Pointer<Aresta>& aresta) {
//                     return aresta->getDestino()->getIndice() == indice;
//                 }),
//             lista.end()
//         );
//     }

//     return true;
// }

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

void GrafoLista::imprime()
{
  for (auto& pair : listaAdjacencia) {
    const Vertice* vertice = pair.first;
    std::cout << "\tVertice " << vertice->getIndice() << " - " << vertice->getLabel().c_str() << ": ";
    for (const Pointer<Aresta>& aresta : pair.second) {
      std::cout << aresta->getDestino()->getIndice() << " - " << aresta->getDestino()->getLabel().c_str() << " - " << aresta->getPeso() << "; ";
    }
    std::cout << std::endl;
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
  const Pointer<Vertice>& verticeOrigem = buscaVertice(origem), verticeDestino = buscaVertice(destino);

  if (verticeDestino == nullptr || verticeOrigem == nullptr)
    return false;

  const int pesoAresta = ehPonderado ? peso : 1;

  Aresta aresta(verticeOrigem, verticeDestino, pesoAresta);
  listaAdjacencia[verticeOrigem].insert(aresta);

  if (!ehDirecionado) {
    Aresta arestaInvertida(verticeDestino, verticeOrigem, pesoAresta);
    listaAdjacencia[verticeDestino].insert(arestaInvertida);
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

bool GrafoLista::removerAresta(
  const int origem, 
  const int destino
)
{
  const Pointer<Vertice>& verticeOrigem = buscaVertice(origem);
  if (verticeOrigem == nullptr)
    return false;

  listaAdjacencia[verticeOrigem].erase(*buscaAresta(verticeOrigem, destino));

  if (!ehDirecionado) {
    const Pointer<Vertice>& verticeDestino = buscaVertice(destino);
    if (verticeDestino != nullptr)
      listaAdjacencia[verticeDestino].erase(*buscaAresta(verticeDestino, origem));
  }

  return true;
}

//------------------------------------------------------------

const Aresta* GrafoLista::buscaAresta(
  const Pointer<Vertice>& origem,
  const int destino
)
{
  for (const Aresta& aresta : listaAdjacencia[origem]) {
    if (aresta.getDestino()->getIndice() == destino) {
      return &aresta;
    }
  }

  return nullptr;
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

std::vector<Vertice> GrafoLista::vizinhosVertice(
  const int indice
)
{
  //Vertice* buscaVertice(indice);
  return std::vector<Vertice>();
}

//------------------------------------------------------------

bool GrafoLista::removerAresta(
  const int origem, 
  const int destino
) {
  const Pointer<Vertice>& verticeOrigem = buscaVertice(origem);
  if (!verticeOrigem) return false;

  auto& listaOrigem = listaAdjacencia[verticeOrigem];
  listaOrigem.erase(
    std::remove_if(listaOrigem.begin(), listaOrigem.end(),
      [&destino](const Pointer<Aresta>& aresta) {
        return aresta->getDestino()->getIndice() == destino;
      }),
    listaOrigem.end()
  );

  if (!ehDirecionado) {
    const Pointer<Vertice>& verticeDestino = buscaVertice(destino);
    if (verticeDestino) {
      auto& listaDestino = listaAdjacencia[verticeDestino];
      listaDestino.erase(
        std::remove_if(listaDestino.begin(), listaDestino.end(),
          [&origem](const Pointer<Aresta>& aresta) {
            return aresta->getDestino()->getIndice() == origem;
          }),
        listaDestino.end()
      );
    }
  }
  
  return true;
}

//------------------------------------------------------------

bool GrafoLista::removerAresta(
  const int origem, 
  const int destino
) {
  const Pointer<Vertice>& verticeOrigem = buscaVertice(origem);
  if (!verticeOrigem) return false;

  auto& listaOrigem = listaAdjacencia[verticeOrigem];
  listaOrigem.erase(
    std::remove_if(listaOrigem.begin(), listaOrigem.end(),
      [&destino](const Pointer<Aresta>& aresta) {
        return aresta->getDestino()->getIndice() == destino;
      }),
    listaOrigem.end()
  );

  if (!ehDirecionado) {
    const Pointer<Vertice>& verticeDestino = buscaVertice(destino);
    if (verticeDestino) {
      auto& listaDestino = listaAdjacencia[verticeDestino];
      listaDestino.erase(
        std::remove_if(listaDestino.begin(), listaDestino.end(),
          [&origem](const Pointer<Aresta>& aresta) {
            return aresta->getDestino()->getIndice() == origem;
          }),
        listaDestino.end()
      );
    }
  }
  
  return true;
}

//------------------------------------------------------------

void GrafoLista::imprime() {
  std::cout << "Grafo:" << std::endl;
  for (const auto& pair : listaAdjacencia) {
    const Vertice* vertice = pair.first;
    std::cout << "Vertice " << vertice->getIndice() << " (" << vertice->getLabel() << ") -> ";
    
    for (const Pointer<Aresta>& aresta : pair.second) {
      std::cout << "[ " << aresta->getDestino()->getIndice() << " (" << aresta->getDestino()->getLabel() ")";
      if (ehPonderado) {
        std::cout << " - Peso: " << aresta->getPeso();
      }
      std::cout << " ] ";
    }
    std::cout << std::endl;
  }
}
