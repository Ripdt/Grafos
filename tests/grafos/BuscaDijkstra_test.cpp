#include "AlgoritmoDijkstra_test.h"

#include "grafos/AlgoritmoDijkstra.h"
#include "grafos/GrafoMatriz.h"
#include "grafos/Vertice.h"

void AlgoritmoDijkstraTest::SetUp() {}
void AlgoritmoDijkstraTest::TearDown() {}

TEST_F(AlgoritmoDijkstraTest, TESTA_DIJKSTRA_GRAFO_1)
{
  GrafoMatriz grafo(true, true); // direcionado, ponderado

  grafo.inserirVertice("A"); // 0
  grafo.inserirVertice("B"); // 1
  grafo.inserirVertice("C"); // 2
  grafo.inserirAresta(0, 1, 2.0f);
  grafo.inserirAresta(1, 2, 3.0f);
  grafo.inserirAresta(0, 2, 10.0f);

  AlgoritmoDijkstra dijkstra(grafo);
  auto caminhos = dijkstra.rodar(0);

  ASSERT_EQ(caminhos.size(), 3);
  EXPECT_FLOAT_EQ(caminhos[0]->distancia, 0.0f);
  EXPECT_FLOAT_EQ(caminhos[1]->distancia, 2.0f);
  EXPECT_FLOAT_EQ(caminhos[2]->distancia, 5.0f);

  ASSERT_EQ(caminhos[2]->caminho.size(), 3);
  EXPECT_EQ(caminhos[2]->caminho[0].getIndice(), 0);
  EXPECT_EQ(caminhos[2]->caminho[1].getIndice(), 1);
  EXPECT_EQ(caminhos[2]->caminho[2].getIndice(), 2);
}

TEST_F(AlgoritmoDijkstraTest, TESTA_DIJKSTRA_VERTICE_ISOLADO)
{
  GrafoMatriz grafo(true, true);
  grafo.inserirVertice("A"); // 0
  grafo.inserirVertice("B"); // 1 (isolado)

  AlgoritmoDijkstra dijkstra(grafo);
  auto caminhos = dijkstra.rodar(0);

  EXPECT_EQ(caminhos.size(), 1);
  EXPECT_TRUE(caminhos.find(0) != caminhos.end());
  EXPECT_EQ(caminhos.at(0)->distancia, 0.0f);
}

TEST_F(AlgoritmoDijkstraTest, TESTA_DIJKSTRA_COM_MULTIPLOS_CAMINHOS)
{
  GrafoMatriz grafo(true, true);
  grafo.inserirVertice("A"); // 0
  grafo.inserirVertice("B"); // 1
  grafo.inserirVertice("C"); // 2
  grafo.inserirVertice("D"); // 3

  grafo.inserirAresta(0, 1, 1.0f);
  grafo.inserirAresta(0, 2, 5.0f);
  grafo.inserirAresta(1, 2, 1.0f);
  grafo.inserirAresta(2, 3, 1.0f);

  AlgoritmoDijkstra dijkstra(grafo);
  auto caminhos = dijkstra.rodar(0);

  EXPECT_FLOAT_EQ(caminhos[2]->distancia, 2.0f); // 0->1->2
  EXPECT_FLOAT_EQ(caminhos[3]->distancia, 3.0f); // 0->1->2->3
}

TEST_F(AlgoritmoDijkstraTest, TESTA_DIJKSTRA_AUTO_LACO)
{
  GrafoMatriz grafo(true, true);
  grafo.inserirVertice("A"); // 0
  grafo.inserirAresta(0, 0, 1.0f); // laço

  AlgoritmoDijkstra dijkstra(grafo);
  auto caminhos = dijkstra.rodar(0);

  ASSERT_EQ(caminhos.size(), 1);
  EXPECT_FLOAT_EQ(caminhos[0]->distancia, 0.0f);
}
