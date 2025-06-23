#include <gtest/gtest.h>

#include "grafos/ArvoreGeradoraCustoMinimo.h"

#include "grafos/GrafoLista.h"

TEST(ArvoreGeradoraCustoMinimoTest, TestKruskal) {
  GrafoLista grafo(false, true); // Grafo não direcionado e com pesos
  grafo.inserirVertice("0");
  grafo.inserirVertice("1");
  grafo.inserirVertice("2");
  grafo.inserirVertice("3");

  grafo.inserirAresta(0, 1, 10);
  grafo.inserirAresta(0, 2, 6);
  grafo.inserirAresta(0, 3, 5);
  grafo.inserirAresta(1, 3, 15);
  grafo.inserirAresta(2, 3, 4);

  ArvoreGeradoraCustoMinimo arvore(grafo);
  EXPECT_EQ(arvore.kruskal(), 19); // custoTotal
  EXPECT_EQ(arvore.prim(2), 19);   // custoTotal
}