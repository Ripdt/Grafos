#include "BuscaLargura_test.h"

#include "grafos/BuscaLargura.h"
#include "grafos/GrafoMatriz.h"
#include "grafos/GrafoLista.h"
#include "grafos/Vertice.h"

void BuscaLarguraTest::SetUp() {}
void BuscaLarguraTest::TearDown() {}

TEST_F(BuscaLarguraTest, TESTA_BUSCA_MATRIZ_1)
{
  GrafoMatriz grafo(true, false);
  grafo.inserirVertice("A"); // 0
  grafo.inserirVertice("B"); // 1
  grafo.inserirVertice("C"); // 2

  grafo.inserirAresta(0, 1);
  grafo.inserirAresta(1, 2);

  BuscaLargura busca(grafo);

  std::vector<int> resultado = busca.caminhoTodosOsVertices(0);
  ASSERT_EQ(resultado.size(), 3);
  EXPECT_EQ(resultado[0], 0);
  EXPECT_EQ(resultado[1], 1);
  EXPECT_EQ(resultado[2], 2);
}

TEST_F(BuscaLarguraTest, TESTA_BUSCA_COM_CICLO)
{
  GrafoMatriz grafo(true, false);
  grafo.inserirVertice("A");
  grafo.inserirVertice("B");
  grafo.inserirVertice("C");

  grafo.inserirAresta(0, 1);
  grafo.inserirAresta(1, 2);
  grafo.inserirAresta(2, 0); // ciclo

  BuscaLargura busca(grafo);
  auto resultado = busca.caminhoTodosOsVertices(0);
  ASSERT_EQ(resultado.size(), 3);
}

TEST_F(BuscaLarguraTest, TESTA_BUSCA_COM_AUTO_LACO)
{
  GrafoMatriz grafo(true, false);
  grafo.inserirVertice("A");
  grafo.inserirVertice("B");

  grafo.inserirAresta(0, 1);
  grafo.inserirAresta(1, 1); // auto-laço

  BuscaLargura busca(grafo);
  auto resultado = busca.caminhoTodosOsVertices(0);
  EXPECT_EQ(resultado.size(), 2);
}

TEST_F(BuscaLarguraTest, TESTA_VERTICE_ISOLADO)
{
  GrafoMatriz grafo(true, false);
  grafo.inserirVertice("A"); // 0
  grafo.inserirVertice("B"); // 1 isolado

  BuscaLargura busca(grafo);
  auto resultado = busca.caminhoTodosOsVertices(1);
  ASSERT_EQ(resultado.size(), 1);
  EXPECT_EQ(resultado[0], 1);
}

TEST_F(BuscaLarguraTest, TESTA_COMPONENTES_DESCONECTADOS)
{
  GrafoMatriz grafo(true, false);
  grafo.inserirVertice("A"); // 0
  grafo.inserirVertice("B"); // 1
  grafo.inserirVertice("C"); // 2
  grafo.inserirVertice("D"); // 3

  grafo.inserirAresta(0, 1);
  grafo.inserirAresta(2, 3);

  BuscaLargura busca(grafo);

  auto resultado = busca.caminhoTodosOsVertices(0);
  EXPECT_EQ(resultado.size(), 2); // A e B

  resultado = busca.caminhoTodosOsVertices(2);
  EXPECT_EQ(resultado.size(), 2); // C e D
}

TEST_F(BuscaLarguraTest, TESTA_BUSCA_GRAFO_LISTA)
{
  GrafoLista grafo(true, false);
  grafo.inserirVertice("A");
  grafo.inserirVertice("B");
  grafo.inserirVertice("C");
  grafo.inserirVertice("D");

  grafo.inserirAresta(0, 1);
  grafo.inserirAresta(0, 2);
  grafo.inserirAresta(1, 3);
  grafo.inserirAresta(2, 3);

  BuscaLargura busca(grafo);
  auto resultado = busca.caminhoTodosOsVertices(0);

  ASSERT_EQ(resultado.size(), 4);
  EXPECT_EQ(resultado[0], 0);
  EXPECT_EQ(resultado[1], 1);
  EXPECT_EQ(resultado[2], 2);
  EXPECT_EQ(resultado[3], 3);
}
