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
  Buscar o vértice na lista de adjacência
  Pointer<Vertice> vertice = buscaVertice(indice);
  if (vertice == nullptr) return false; // O vértice não existe

  // Remover todas as arestas que têm esse vértice como destino
  for (auto& par : listaAdjacencia) {
      ListaArestas& arestas = par.second;
      for (auto it = arestas.begin(); it != arestas.end(); ) {
          if (it->getDestino()->getIndice() == indice) {
              it = arestas.erase(it);  // Remove e avança o iterador
          } else {
              ++it;
          }
      }
  }

  // Remover o vértice da lista de adjacência
  listaAdjacencia.erase(vertice);

  // Reindexação dos vértices restantes
  std::map<int, Pointer<Vertice>> novoIndiceMap;
  std::map<Pointer<Vertice>, ListaArestas> novaListaAdj;
  int novoIndice = 0;

  for (auto& par : listaAdjacencia) {
      Pointer<Vertice> v = par.first;
      novoIndiceMap[novoIndice] = v; // Mapear novo índice
      novaListaAdj[v] = std::move(par.second);
      ++novoIndice;
  }

  // Atualizar os destinos das arestas com os novos índices
  for (auto& par : novaListaAdj) {
    ListaArestas& arestas = par.second;
    for (auto& aresta : arestas) {  // A aresta não é mais const
        int indiceDestino = aresta.getDestino()->getIndice();
        if (novoIndiceMap.find(indiceDestino) != novoIndiceMap.end()) {
            // Encontramos o novo destino correspondente ao índice reindexado
            Pointer<Vertice> novoDestino = novoIndiceMap[indiceDestino];
            // Agora podemos modificar o destino da aresta
            aresta.setDestino(novoDestino);  // Chama o setDestino sem erro <- Olhar essa linha
        }
    }
  }


  // Substituir a lista de adjacência com os novos índices
  listaAdjacencia = std::move(novaListaAdj);

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

bool GrafoLista::inserirAresta(const int origem, const int destino, const int peso)
{
    Pointer<Vertice> verticeOrigem = buscaVertice(origem);
    Pointer<Vertice> verticeDestino = buscaVertice(destino);

    // Se algum vértice não for encontrado, retornamos false
    if (verticeOrigem == nullptr || verticeDestino == nullptr) {
        return false;  // Falha ao encontrar os vértices
    }

    // Procurar se já existe uma aresta entre os vértices
    ListaArestas& arestasOrigem = listaAdjacencia[verticeOrigem]; // <- Olhar essa linha
    for (auto it = arestasOrigem.begin(); it != arestasOrigem.end(); ++it) {
        // Se já existir uma aresta entre origem e destino, removemos a anterior
        if (it->getDestino()->getIndice() == destino) {
            arestasOrigem.erase(it);  // Remove a aresta antiga
            break;  // Não precisamos continuar verificando
        }
    }

    // Agora inserimos a nova aresta com o novo peso
    arestasOrigem.push_back(Aresta(verticeOrigem.getRaw(), verticeDestino.getRaw(), peso));

    return true;  // Sucesso ao inserir a aresta
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

std::vector<Vertice> GrafoLista::vizinhosVertice(const int indice)
{
  // Buscar o vértice na lista de adjacência
  Pointer<Vertice> vertice = buscaVertice(indice);
  if (vertice == nullptr) {
    return {}; // Se o vértice não existir, retorna uma lista vazia
  }

  std::vector<Vertice> vizinhos;
  
  // Percorrer as arestas para encontrar os vizinhos
  for (auto& par : listaAdjacencia) {
    ListaArestas& arestas = par.second; // <- olhar essa linha
    for (auto& aresta : arestas) {
      // Verificar se o vértice é a origem da aresta
      if (aresta.getOrigem()->getIndice() == indice) {
        vizinhos.push_back(*aresta.getDestino()); // Adiciona o destino como vizinho
      }
      // Verificar se o vértice é o destino da aresta
      else if (aresta.getDestino()->getIndice() == indice) {
        vizinhos.push_back(*aresta.getOrigem()); // Adiciona a origem como vizinho
      }
    }
  }

  return vizinhos;
}


//------------------------------------------------------------

void GrafoLista::imprime() {
  std::cout << "Grafo:" << std::endl;
  for (const auto& pair : listaAdjacencia) {
    const Vertice* vertice = pair.first;
    std::cout << "Vertice " << vertice->getIndice() << " (" << vertice->getLabel() << ") -> ";
    
    for (const Pointer<Aresta>& aresta : pair.second) {
      std::cout << "[ " << aresta->getDestino()->getIndice() << " (" << aresta->getDestino()->getLabel() << ")";
      if (ehPonderado) {
        std::cout << " - Peso: " << aresta->getPeso();
      }
      std::cout << " ] ";
    }
    std::cout << std::endl;
  }
}
