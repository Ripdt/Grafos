#include "grafos/BuscaProfundidade.h"

#include "grafos/Vertice.h"

#include <unordered_map>

BuscaProfundidade::BuscaProfundidade(
  const Grafo& _grafo
) :
  grafo(_grafo)
{
}

std::vector<Vertice> BuscaProfundidade::buscarCaminhoParaTodosVertices(
  const int origem
) const
{
  std::vector<Vertice> caminho;

  caminho.push_back(grafo.getVertice(origem));
  buscarCaminhoParaTodosVertices(origem, caminho);

  return caminho;
}


void BuscaProfundidade::buscarCaminhoParaTodosVertices(
  const int origem,
  std::vector<Vertice>& verticesVisitados
) const
{
  if (verticesVisitados.size() == grafo.numeroVertices())
    return;

  std::vector<std::vector<Vertice>> caminhos;

  for (const Vertice& vertice : grafo.vizinhosVertice(origem)) {
    if (foiVisitado(vertice, verticesVisitados))
      continue;

    std::vector<Vertice> caminho = verticesVisitados;
    caminho.push_back(vertice);

    buscarCaminhoParaTodosVertices(vertice.getIndice(), caminho);

    caminhos.push_back(caminho);
  }

  for (std::vector<Vertice> caminho : caminhos)
    if (verticesVisitados.size() < caminho.size())
      verticesVisitados = caminho;
}

bool BuscaProfundidade::foiVisitado(
  const Vertice& vertice,
  const std::vector<Vertice>& verticesVisitados
) const
{
  auto ehVertice = [&vertice](const Vertice& v) {
    return v.getIndice() == vertice.getIndice();
  };

  return std::find_if(verticesVisitados.begin(), verticesVisitados.end(), ehVertice) != verticesVisitados.end();
}