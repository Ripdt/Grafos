#include "GrafoMatriz_test.h"

#include "grafos/GrafoMatriz.h"

#include <string>

//------------------------------------------------------------
// GrafoMatrizTest
//------------------------------------------------------------

void GrafoMatrizTest::SetUp()
{
  grafo = new GrafoMatriz(false, true);
}

//------------------------------------------------------------

void GrafoMatrizTest::TearDown()
{
  delete grafo;
}

//------------------------------------------------------------
// Tests
//------------------------------------------------------------

TEST_F(GrafoMatrizTest, InserirVertice)
{
  EXPECT_TRUE(grafo->inserirVertice("A"));
  EXPECT_EQ(grafo->labelVertice(0), "A");

  EXPECT_TRUE(grafo->inserirVertice("B"));
  EXPECT_EQ(grafo->labelVertice(1), "B");
}

//------------------------------------------------------------

TEST_F(GrafoMatrizTest, RemoverVertice)
{
  grafo->inserirVertice("A");
  grafo->inserirVertice("B");
  EXPECT_TRUE(grafo->removerVertice(0));
  EXPECT_EQ(grafo->labelVertice(0), "B");

  grafo->inserirVertice("C");
  EXPECT_TRUE(grafo->removerVertice(1));
  EXPECT_EQ(grafo->labelVertice(0), "B");
}

//------------------------------------------------------------

TEST_F(GrafoMatrizTest, InserirAresta)
{
  grafo->inserirVertice("A");
  grafo->inserirVertice("B");
  EXPECT_TRUE(grafo->inserirAresta(0, 1, 10));
  EXPECT_TRUE(grafo->existeAresta(0, 1));
  EXPECT_EQ(grafo->pesoAresta(0, 1), 10);

  grafo->inserirVertice("C");
  EXPECT_TRUE(grafo->inserirAresta(1, 2, 20));
  EXPECT_TRUE(grafo->existeAresta(1, 2));
  EXPECT_EQ(grafo->pesoAresta(1, 2), 20);
}

//------------------------------------------------------------

TEST_F(GrafoMatrizTest, RemoverAresta)
{
  grafo->inserirVertice("A");
  grafo->inserirVertice("B");
  grafo->inserirAresta(0, 1, 10);
  EXPECT_TRUE(grafo->removerAresta(0, 1));
  EXPECT_FALSE(grafo->existeAresta(0, 1));

  grafo->inserirAresta(0, 1, 15);
  EXPECT_TRUE(grafo->removerAresta(0, 1));
  EXPECT_FALSE(grafo->existeAresta(0, 1));
}

//------------------------------------------------------------

TEST_F(GrafoMatrizTest, ExisteAresta)
{
  grafo->inserirVertice("A");
  grafo->inserirVertice("B");
  grafo->inserirAresta(0, 1, 10);
  EXPECT_TRUE(grafo->existeAresta(0, 1));

  grafo->removerAresta(0, 1);
  EXPECT_FALSE(grafo->existeAresta(0, 1));
}

//------------------------------------------------------------

TEST_F(GrafoMatrizTest, PesoAresta)
{
  grafo->inserirVertice("A");
  grafo->inserirVertice("B");
  grafo->inserirAresta(0, 1, 10);
  EXPECT_EQ(grafo->pesoAresta(0, 1), 10);

  grafo->inserirAresta(0, 1, 20);
  EXPECT_EQ(grafo->pesoAresta(0, 1), 20);
}

//------------------------------------------------------------

TEST_F(GrafoMatrizTest, VizinhosVertice)
{
  grafo->inserirVertice("A");
  grafo->inserirVertice("B");
  grafo->inserirVertice("C");
  grafo->inserirAresta(0, 1, 10);
  grafo->inserirAresta(0, 2, 20);

  std::vector<Vertice> vizinhos = grafo->vizinhosVertice(0);
  ASSERT_EQ(vizinhos.size(), 2);
  EXPECT_STREQ(vizinhos[0].getLabel().c_str(), "B");
  EXPECT_STREQ(vizinhos[1].getLabel().c_str(), "C");

  grafo->removerAresta(0, 1);
  vizinhos = grafo->vizinhosVertice(0);
  ASSERT_EQ(vizinhos.size(), 1);
  EXPECT_STREQ(vizinhos[0].getLabel().c_str(), "C");
}

//------------------------------------------------------------

TEST_F(GrafoMatrizTest, LabelVertice)
{
  grafo->inserirVertice("A");
  EXPECT_EQ(grafo->labelVertice(0), "A");

  grafo->inserirVertice("B");
  EXPECT_EQ(grafo->labelVertice(1), "B");
}

//------------------------------------------------------------

TEST_F(GrafoMatrizTest, Imprime)
{
  grafo->inserirVertice("A");
  grafo->inserirVertice("B");
  grafo->inserirAresta(0, 1, 10);

  testing::internal::CaptureStdout();
  grafo->imprime();
  std::string output = testing::internal::GetCapturedStdout();

  EXPECT_NE(output.find("A"), std::string::npos);
  EXPECT_NE(output.find("B"), std::string::npos);
  EXPECT_NE(output.find("10"), std::string::npos);
}

//------------------------------------------------------------
