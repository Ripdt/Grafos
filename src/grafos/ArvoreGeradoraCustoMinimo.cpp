#include "grafos/ArvoreGeradoraCustoMinimo.h"

#include "grafos/Aresta.h"

#include <algorithm>
#include <list>
#include <set>

float ArvoreGeradoraCustoMinimo::prim(const int raiz)
{
  std::list<Vertice*> vertices;
  for (int i = 0; i < g.numeroVertices(); i++) {
    vertices.push_back(g.getVertice(i));
  }
  Vertice* pivo = g.getVertice(raiz);
  vertices.remove(pivo);

  std::set<Vertice*> visitados; // evita buscas lineares pela lista (não é necessário para funcionamento, apenas desempenho)
  visitados.insert(pivo);

  std::vector<Aresta*> arestas = g.getArestas();

  std::sort(arestas.begin(), arestas.end(), [](const Aresta* a, const Aresta* b) {
    return a->getPeso() < b->getPeso();
  });

  std::vector<Aresta*> solucao;

  float custoTotal = 0;

  while (!vertices.empty()) {
    std::list<Vertice*>::iterator itNovo;
    std::vector<Aresta*>::iterator itAresta = arestas.begin();
    for (; itAresta != arestas.end(); ++itAresta) {
      Vertice* u = (*itAresta)->getOrigem();
      Vertice* v = (*itAresta)->getDestino();
      const bool uVisitado = visitados.count(u) > 0;
      const bool vVisitado = visitados.count(v) > 0;
      const auto itU = std::find(vertices.begin(), vertices.end(), u);
      const auto itV = std::find(vertices.begin(), vertices.end(), v);
      if (uVisitado && itV != vertices.end()) {
        itNovo = itV;
        break;
      }
      if (vVisitado && itU != vertices.end()) {
        itNovo = itU;
        break;
      }
    }

    if (itAresta == arestas.end()) break; // sem arestas elegíveis

    Aresta* aresta = *itAresta;
    Vertice* novo = *itNovo;
    solucao.push_back(aresta);
    vertices.erase(itNovo);
    visitados.insert(novo);
    custoTotal += aresta->getPeso();

    arestas.erase(itAresta);
  }

  return custoTotal;
}

float ArvoreGeradoraCustoMinimo::kruskal() const // usa arestas - grafos esparsos (pouca aresta)
{
  std::vector<Aresta*> arestas = g.getArestas();

  std::sort(arestas.begin(), arestas.end(), [](const Aresta* a, const Aresta* b) {
    return a->getPeso() > b->getPeso();
    });
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