#include "grafos/AlgoritmoDijkstra.h"

#include "grafos/Vertice.h"

#include <iostream>
#include <numeric>

AlgoritmoDijkstra::AlgoritmoDijkstra(
  const Grafo& _grafo
) : 
  grafo(_grafo)
{
}

void AlgoritmoDijkstra::rodar(
  const int origem
) const
{
  const Vertice& verticeOrigem = grafo.getVertice(origem);

  Caminho* caminhoOrigem = new Caminho(verticeOrigem);
  caminhoOrigem->distancia = 0.f;
  caminhoOrigem->marcado = true;
  caminhoOrigem->caminho.push_back(verticeOrigem);

  menorCaminhoAteVertice.insert({ verticeOrigem.getIndice(), caminhoOrigem});

  acharCaminhosAteVizinhos(verticeOrigem, *caminhoOrigem, menorCaminhoAteVertice);

  for (auto pair : menorCaminhoAteVertice) {
    const int indice = pair.first;
    const Pointer<Caminho>& caminho = pair.second;
    std::cout << "Caminho para " << indice << ": ";
    for (const Vertice& vertice : caminho->caminho) {
      std::cout << vertice.getIndice() << " ";
    }
    std::cout << "(Distancia: " << caminho->distancia << ")" << std::endl;
  }
}

void AlgoritmoDijkstra::acharCaminhosAteVizinhos(
  const Vertice& verticeOrigem,
  const Caminho& caminhoAteOrigem,
  std::unordered_map<int, Pointer<Caminho>>& caminhoAteVertice
) const
{
  std::vector<Pointer<Caminho>> caminhosEncontrados;
  acharCaminhosAteVizinhos(verticeOrigem, caminhoAteOrigem, caminhoAteVertice, caminhosEncontrados);

  while (!caminhosEncontrados.empty()) {
    Caminho* menorCaminho = nullptr;

    for (Pointer<Caminho>& caminho : caminhosEncontrados) {
      if (menorCaminho == nullptr || caminho->distancia < menorCaminho->distancia)
        menorCaminho = caminho;

      const int indice = caminho->verticeDestino.getIndice();
      auto& it = caminhoAteVertice.find(indice);
      if (it == caminhoAteVertice.end())
        caminhoAteVertice.insert({ indice, caminho });
      else if (caminhoAteVertice.at(indice)->distancia > caminho->distancia)
        caminhoAteVertice.at(indice) = caminho;
    }

    menorCaminho->marcado = true;
    const Vertice& novaOrigem = menorCaminho->verticeDestino;

    auto ehMenorCaminho = [&menorCaminho](const Pointer<Caminho>& c) { 
      return c.getRaw() == menorCaminho; 
    };
    caminhosEncontrados.erase(std::find_if(caminhosEncontrados.begin(), caminhosEncontrados.end(), ehMenorCaminho));

    acharCaminhosAteVizinhos(novaOrigem, *menorCaminho, caminhoAteVertice, caminhosEncontrados);
  }
}

void AlgoritmoDijkstra::acharCaminhosAteVizinhos(
  const Vertice& verticeOrigem,
  const Caminho& caminhoAteOrigem,
  std::unordered_map<int, Pointer<Caminho>>& caminhoAteVertice,
  std::vector<Pointer<Caminho>>& caminhosEncontrados
) const
{
  for (const Vertice& vertice : grafo.vizinhosVertice(verticeOrigem.getIndice())) {
    auto& it = caminhoAteVertice.find(vertice.getIndice());
    if (it != caminhoAteVertice.end() && it->second->marcado)
      continue;

    Caminho* caminhoVizinho = new Caminho(vertice);
    caminhoVizinho->distancia = caminhoAteOrigem.distancia + grafo.pesoAresta(verticeOrigem.getIndice(), vertice.getIndice());
    caminhoVizinho->caminho = caminhoAteOrigem.caminho;
    caminhoVizinho->caminho.push_back(vertice);

    caminhosEncontrados.push_back(caminhoVizinho);
  }
}