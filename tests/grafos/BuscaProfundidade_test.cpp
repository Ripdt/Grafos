#include "BuscaProfundidade_test.h"

#include "grafos/BuscaProfundidade.h"
#include "grafos/GrafoMatriz.h"
#include "grafos/GrafoLista.h"
#include "grafos/Vertice.h"

void BuscaProfundidadeTest::SetUp() {}
void BuscaProfundidadeTest::TearDown() {}

TEST_F(BuscaProfundidadeTest, TESTA_BUSCA_MATRIZ_DIRECIONADA_1)
{
  GrafoMatriz grafo(true, false);
  grafo.inserirVertice("A");
  grafo.inserirVertice("B");
  grafo.inserirVertice("C");
  grafo.inserirAresta(0, 1);
  grafo.inserirAresta(1, 2);

  BuscaProfundidade busca(grafo);

  std::vector<int> resultado = busca.percorrerTodosOsVertices(0);
  ASSERT_EQ(resultado.size(), 3);
  EXPECT_EQ(resultado[0], 0);
  EXPECT_EQ(resultado[1], 1);
  EXPECT_EQ(resultado[2], 2);

  resultado = busca.percorrerTodosOsVertices(1);
  ASSERT_EQ(resultado.size(), 2);
  EXPECT_EQ(resultado[0], 1);
  EXPECT_EQ(resultado[1], 2);

  resultado = busca.percorrerTodosOsVertices(2);
  ASSERT_EQ(resultado.size(), 1);
  EXPECT_EQ(resultado[0], 2);

  grafo.inserirAresta(1, 0); // cria ciclo
  resultado = busca.percorrerTodosOsVertices(1);
  ASSERT_EQ(resultado.size(), 3);
}

TEST_F(BuscaProfundidadeTest, TESTA_BUSCA_MATRIZ_DIRECIONADA_2)
{
  GrafoMatriz grafo(true, true);

  grafo.inserirVertice("A");
  grafo.inserirVertice("B");
  grafo.inserirVertice("C");
  grafo.inserirVertice("D");
  grafo.inserirVertice("E");

  grafo.inserirAresta(0, 1, 7.5f);
  grafo.inserirAresta(0, 2, 9.1f);
  grafo.inserirAresta(1, 3, 10.f);
  grafo.inserirAresta(2, 3, 2.3f);
  grafo.inserirAresta(2, 4, 1.0f);
  grafo.inserirAresta(2, 1, 1.0f);
  grafo.inserirAresta(3, 4, 4.0f);

  BuscaProfundidade busca(grafo);
  auto resultado = busca.percorrerTodosOsVertices(0);
  EXPECT_EQ(resultado.size(), 5);

  resultado = busca.percorrerTodosOsVertices(1);
  EXPECT_EQ(resultado.size(), 3);

  resultado = busca.percorrerTodosOsVertices(2);
  EXPECT_EQ(resultado.size(), 4);

  resultado = busca.percorrerTodosOsVertices(3);
  EXPECT_EQ(resultado.size(), 2);

  resultado = busca.percorrerTodosOsVertices(4);
  EXPECT_EQ(resultado.size(), 1);
}

TEST_F(BuscaProfundidadeTest, TESTA_BUSCA_COM_CICLO)
{
  GrafoMatriz grafo(true, false);
  grafo.inserirVertice("A");
  grafo.inserirVertice("B");
  grafo.inserirVertice("C");

  grafo.inserirAresta(0, 1);
  grafo.inserirAresta(1, 2);
  grafo.inserirAresta(2, 0); // ciclo

  BuscaProfundidade busca(grafo);
  auto resultado = busca.percorrerTodosOsVertices(0);
  EXPECT_EQ(resultado.size(), 3);
}

TEST_F(BuscaProfundidadeTest, TESTA_BUSCA_COM_AUTO_LACO)
{
  GrafoMatriz grafo(true, false);
  grafo.inserirVertice("A");
  grafo.inserirVertice("B");

  grafo.inserirAresta(0, 1);
  grafo.inserirAresta(1, 1); // auto-laço

  BuscaProfundidade busca(grafo);
  auto resultado = busca.percorrerTodosOsVertices(0);
  EXPECT_EQ(resultado.size(), 2);
}

TEST_F(BuscaProfundidadeTest, TESTA_VERTICE_ISOLADO)
{
  GrafoMatriz grafo(true, false);
  grafo.inserirVertice("A"); // 0
  grafo.inserirVertice("B"); // 1 isolado

  BuscaProfundidade busca(grafo);
  auto resultado = busca.percorrerTodosOsVertices(1);
  ASSERT_EQ(resultado.size(), 1);
  EXPECT_EQ(resultado [0], 1);
}

TEST_F(BuscaProfundidadeTest, TESTA_COMPONENTES_DESCONECTADOS)
{
  GrafoMatriz grafo(true, false);
  grafo.inserirVertice("A"); // 0
  grafo.inserirVertice("B"); // 1
  grafo.inserirVertice("C"); // 2
  grafo.inserirVertice("D"); // 3

  grafo.inserirAresta(0, 1); // componente 1
  grafo.inserirAresta(2, 3); // componente 2

  BuscaProfundidade busca(grafo);

  auto resultado = busca.percorrerTodosOsVertices(0);
  EXPECT_EQ(resultado.size(), 2);

  resultado = busca.percorrerTodosOsVertices(2);
  EXPECT_EQ(resultado.size(), 2);
}

TEST_F(BuscaProfundidadeTest, TESTA_GRAFO_LISTA_DIRECIONADO)
{
  GrafoLista grafo(true, false);
  grafo.inserirVertice("A");
  grafo.inserirVertice("B");
  grafo.inserirVertice("C");

  grafo.inserirAresta(0, 1);
  grafo.inserirAresta(1, 2);

  BuscaProfundidade busca(grafo);
  auto resultado = busca.percorrerTodosOsVertices(0);
  EXPECT_EQ(resultado.size(), 3);
}
