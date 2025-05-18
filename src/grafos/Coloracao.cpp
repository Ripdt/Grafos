#include "Coloracao.h"

#include "grafos/Grafo.h"
#include "grafos/Vertice.h"

//------------------------------------------------------------

Coloracao::Coloracao(const Grafo& _grafo) : grafo(_grafo)
{
}

//------------------------------------------------------------

std::vector<int> Coloracao::colorir() const
{
  const size_t numVertices = grafo.numeroVertices();
  if (numVertices == 0) {
    return std::vector<int>();
  }

  int numCores = 2;
  while (true) {
    // Inicializa com a primeira combinação (todos vértices com cor 0)
    std::vector<int> cores(numVertices, 0);

    do {
      if (coloracaoValida(cores)) {
        return cores;
      }
    } while (proximaCombinacao(cores, numCores));

    numCores++;
  }

  return std::vector<int>();
}

//------------------------------------------------------------

bool Coloracao::coloracaoValida(const std::vector<int>& cores) const 
{
  for (int idxVertice = 0; idxVertice < grafo.numeroVertices(); idxVertice++) {
    for (const Vertice& vizinho : grafo.vizinhosVertice(idxVertice)) {
      if (cores[idxVertice] == cores[vizinho.getIndice()]) {
        return false;
      }
    }
  }

  return true;
}

//------------------------------------------------------------

bool Coloracao::proximaCombinacao(std::vector<int>& cores, int numCores) const {

  for (int i = 0; i < cores.size(); i++) {
    if (cores[i] < numCores - 1) {
      cores[i]++;
      // Reseta todos os vértices anteriores para 0
      for (int j = 0; j < i; j++) {
        cores[j] = 0;
      }
      return true;
    }
  }
  return false;
}

//------------------------------------------------------------



//------------------------------------------------------------