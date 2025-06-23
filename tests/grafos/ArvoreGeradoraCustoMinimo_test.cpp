#include <gtest/gtest.h>

#include "grafos/ArvoreGeradoraCustoMinimo.h"
#include "grafos/GrafoLista.h"

TEST(ArvoreGeradoraCustoMinimoTest, GrafoComPesosIguais) {
  GrafoLista grafo(false, true);
  grafo.inserirVertice("A");
  grafo.inserirVertice("B");
  grafo.inserirVertice("C");
  grafo.inserirAresta(0, 1, 1);
  grafo.inserirAresta(1, 2, 1);
  grafo.inserirAresta(0, 2, 1);

  ArvoreGeradoraCustoMinimo arvore(grafo);
  EXPECT_EQ(arvore.kruskal(), 2);
  EXPECT_EQ(arvore.prim(0), 2);
  EXPECT_EQ(arvore.prim(1), 2);
  EXPECT_EQ(arvore.prim(2), 2);
}

TEST(ArvoreGeradoraCustoMinimoTest, GrafoDesconexo) {
  GrafoLista grafo(false, true);
  grafo.inserirVertice("A");
  grafo.inserirVertice("B");
  grafo.inserirVertice("C");
  // Nenhuma aresta

  ArvoreGeradoraCustoMinimo arvore(grafo);
  EXPECT_EQ(arvore.kruskal(), 0);
  EXPECT_EQ(arvore.prim(0), 0);
}

TEST(ArvoreGeradoraCustoMinimoTest, GrafoComUmVertice) {
  GrafoLista grafo(false, true);
  grafo.inserirVertice("A");

  ArvoreGeradoraCustoMinimo arvore(grafo);
  EXPECT_EQ(arvore.kruskal(), 0);
  EXPECT_EQ(arvore.prim(0), 0);
}

TEST(ArvoreGeradoraCustoMinimoTest, GrafoCompleto) {
  GrafoLista grafo(false, true);
  for (int i = 0; i < 4; ++i) {
    grafo.inserirVertice(std::to_string(i));
  }
  grafo.inserirAresta(0, 1, 1);
  grafo.inserirAresta(0, 2, 2);
  grafo.inserirAresta(0, 3, 3);
  grafo.inserirAresta(1, 2, 4);
  grafo.inserirAresta(1, 3, 5);
  grafo.inserirAresta(2, 3, 6);

  ArvoreGeradoraCustoMinimo arvore(grafo);
  EXPECT_EQ(arvore.kruskal(), 6); // 1+2+3
  EXPECT_EQ(arvore.prim(0), 6);
  EXPECT_EQ(arvore.prim(1), 6);
  EXPECT_EQ(arvore.prim(2), 6);
  EXPECT_EQ(arvore.prim(3), 6);
}

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