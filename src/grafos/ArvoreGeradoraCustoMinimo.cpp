#include "grafos/ArvoreGeradoraCustoMinimo.h"

#include "grafos/Aresta.h"

#include <algorithm>
#include <list>

float ArvoreGeradoraCustoMinimo::prim( // usa vertice - grafos densos (muita aresta)
  const int raiz
)
{
  std::list<Vertice*> vertices;
  for (int i = 0; i < g.numeroVertices(); i++) {
    vertices.push_back(g.getVertice(i));
  }
  Vertice* pivo = g.getVertice(raiz);
  vertices.remove(pivo);

  std::vector<Aresta*> arestas = arestasOrdenadas();
  std::vector<Aresta*> solucao;

  float custoTotal = 0;

  while (!vertices.empty()) {
    Aresta* aresta = arestas.back();
    arestas.pop_back();

    Vertice* u = aresta->getOrigem();
    Vertice* v = aresta->getDestino();
    auto itU = std::find(vertices.begin(), vertices.end(), u);
    auto itV = std::find(vertices.begin(), vertices.end(), v);
    if (itU != vertices.end() ^ itV != vertices.end()) {
      solucao.push_back(aresta);
      vertices.erase(itU != vertices.end() ? itU : itV);
      custoTotal += aresta->getPeso();
    }
  }

  return custoTotal;
}

float ArvoreGeradoraCustoMinimo::kruskal() const // usa arestas - grafos esparsos (pouca aresta)
{
  std::vector<Aresta*> arestas = arestasOrdenadas();
  std::vector<Aresta*> solucao;

  std::vector<std::vector<Vertice*>> florestas;
  for (int i = 0; i < g.numeroVertices(); i++) {
    Vertice* v = g.getVertice(i);
    florestas.push_back(std::vector<Vertice*>{ v }); // arvores isoladas
  }

  float custoTotal = 0;

  while (!arestas.empty()) {
    Aresta* aresta = arestas.back();
    arestas.pop_back();

    Vertice* u = aresta->getOrigem();
    Vertice* v = aresta->getDestino();

    auto it_u = florestas.end(), it_v = florestas.end();
    for (auto it = florestas.begin(); it != florestas.end(); ++it) {
      if (std::find(it->begin(), it->end(), u) != it->end()) it_u = it;
      if (std::find(it->begin(), it->end(), v) != it->end()) it_v = it;
    }

    if (it_u != it_v) { // florestas diferentes
      it_u->insert(it_u->end(), it_v->begin(), it_v->end());
      florestas.erase(it_v);
      solucao.push_back(aresta);
      custoTotal += aresta->getPeso();
    }
  }

  return custoTotal;
}

std::vector<Aresta*> ArvoreGeradoraCustoMinimo::arestasOrdenadas() const
{
  std::vector<Aresta*> arestas = g.getArestas();

  std::sort(arestas.begin(), arestas.end(), [](const Aresta* a, const Aresta* b) {
    return a->getPeso() > b->getPeso();
    });

  return arestas;
}