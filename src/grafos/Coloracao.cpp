#include "Coloracao.h"

#include "grafos/Grafo.h"
#include "grafos/Vertice.h"

#include <algorithm>
#include <list>

//------------------------------------------------------------

Coloracao::Coloracao(Grafo& _grafo) : grafo(_grafo)
{
  grafo.resetarCores();
}

//------------------------------------------------------------

void Coloracao::colorir_BruteForce() const
{
  const size_t numVertices = grafo.numeroVertices();
  if (numVertices == 0) {
    return;
  }

  int numCores = 2;
  while (true) {
    // Inicializa com a primeira combina��o (todos v�rtices com cor 0)
    std::vector<int> corPorIndice(numVertices /*idx*/, 0 /*cor*/);

    do {
      if (coloracaoValida(corPorIndice)) {
        for (int idx = 0; idx < numVertices; idx++) {
          const int cor = corPorIndice[idx];
          grafo.getVertice(idx)->setCor(cor);
        }
        return;
      }
    } while (proximaCombinacao(corPorIndice, numCores));

    numCores++;
  }
}

//------------------------------------------------------------

bool Coloracao::coloracaoValida(const std::vector<int>& corPorIndice) const
{
  for (int idxVertice = 0; idxVertice < grafo.numeroVertices(); idxVertice++) {
    for (const Vertice* vizinho : grafo.vizinhosVertice(idxVertice)) {
      if (corPorIndice[idxVertice] == corPorIndice[vizinho->getIndice()]) {
        return false;
      }
    }
  }

  return true;
}

//------------------------------------------------------------

bool Coloracao::proximaCombinacao(std::vector<int>& corPorIndice, int numCores) const {

  for (int i = 0; i < corPorIndice.size(); i++) {
    if (corPorIndice[i] < numCores - 1) {
      corPorIndice[i]++;
      // Reseta todos os v�rtices anteriores para 0
      for (int j = 0; j < i; j++) {
        corPorIndice[j] = 0;
      }
      return true;
    }
  }
  return false;
}

//------------------------------------------------------------

void Coloracao::colorir_WelshPowell() const
{
  std::list<Vertice*> vertices = verticesOrdenadosPorGrau();
  int corBckp = static_cast<int>(vertices.size());
  int cor = corBckp;
  while (!vertices.empty()) {
    Vertice* v = vertices.front();
    bool corValida = true;
    for (Vertice* vizinho : grafo.vizinhosVertice(v->getIndice())) {
      if (vizinho->getCor() == cor) {
        corValida = false;
        break;
      }
    }

    if (corValida) {
      v->setCor(cor);
      vertices.pop_front();
      cor = corBckp;
    }
    else {
      cor--;
    }
  }
}

//------------------------------------------------------------

std::list<Vertice*> Coloracao::verticesOrdenadosPorGrau() const
{
  std::list<Vertice*> vertices;
  for (int i = 0; i < grafo.numeroVertices(); i++) {
    vertices.push_back(grafo.getVertice(i));
  }
  vertices.sort([&](Vertice* v1, Vertice* v2) {
    return v1->getGrau() > v2->getGrau();
  });

  return vertices;
}

//------------------------------------------------------------

void Coloracao::colorir_DSatur() const
{
  std::list<Vertice*> vertices = verticesOrdenadosPorGrau();

  while (!vertices.empty()) {
    Vertice* v = verticeComMaiorSaturacao(vertices);

    std::vector<bool> coresUsadas(grafo.numeroVertices(), false);
    for (Vertice* vizinho : grafo.vizinhosVertice(v->getIndice())) {
      int corVizinho = vizinho->getCor();
      if (corVizinho != -1) {
        coresUsadas[corVizinho] = true;
      }
    }

    int corEscolhida = 0;
    while (corEscolhida < (int)coresUsadas.size() && coresUsadas[corEscolhida]) {
      corEscolhida++;
    }
    v->setCor(corEscolhida);

    for (Vertice* vizinho : grafo.vizinhosVertice(v->getIndice())) {
      if (vizinho->getCor() == -1) {
        vizinho->aumentarSaturacao();
      }
    }

    vertices.remove(v);
  }
}

//------------------------------------------------------------

Vertice* Coloracao::verticeComMaiorSaturacao(
  const std::list<Vertice*>& vertices
) const
{
  Vertice* verticeMaiorSaturacao = nullptr;
  int maiorSaturacao = -1;
  for (Vertice* v : vertices) {
    if (v->getSaturacao() > maiorSaturacao) {
      maiorSaturacao = v->getSaturacao();
      verticeMaiorSaturacao = v;
    }
  }
  return verticeMaiorSaturacao;
}

//------------------------------------------------------------

void Coloracao::colorir_Greedy() const
{
  const int nVertices = static_cast<int>(grafo.numeroVertices());

  for (int idx = 0; idx < nVertices; idx++) {
    Vertice* v = grafo.getVertice(idx);

    std::vector<bool> coresUsadas(nVertices, false);

    for (Vertice* vizinho : grafo.vizinhosVertice(v->getIndice())) {
      int corVizinho = vizinho->getCor();
      if (corVizinho != -1) {
        coresUsadas[corVizinho] = true;
      }
    }

    int corEscolhida = 0;
    while (corEscolhida < nVertices && coresUsadas[corEscolhida]) {
      corEscolhida++;
    }

    v->setCor(corEscolhida);
  }
}

//------------------------------------------------------------