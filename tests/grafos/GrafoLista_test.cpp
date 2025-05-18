#include "GrafoLista_test.h"

#include "grafos/GrafoLista.h"

#include <string>

//------------------------------------------------------------
// GrafoListaTest
//------------------------------------------------------------

void GrafoListaTest::SetUp()
{
  grafoNaoDirecionalPonderado = new GrafoLista(false, true);
  grafoNaoDirecionalNaoPonderado = new GrafoLista(false, false);
  grafoDirecionalPonderado = new GrafoLista(true, true);
  grafoDirecionalNaoPonderado = new GrafoLista(true, false);
}

//------------------------------------------------------------

void GrafoListaTest::TearDown()
{
  delete grafoNaoDirecionalPonderado;
  delete grafoNaoDirecionalNaoPonderado;
  delete grafoDirecionalPonderado;
  delete grafoDirecionalNaoPonderado;
}

#ifndef TEST_GRAFO_MATRIZ_NAO_DIRECIONAL_PONDERADO

//------------------------------------------------------------
// TEST_GRAFO_MATRIZ_NAO_DIRECIONAL_PONDERADO 
//------------------------------------------------------------

TEST_F(GrafoListaTest, InserirVertice_NaoDirecional_Ponderado)
{
  EXPECT_TRUE(grafoNaoDirecionalPonderado->inserirVertice("A"));
  EXPECT_EQ(grafoNaoDirecionalPonderado->labelVertice(0), "A");

  EXPECT_TRUE(grafoNaoDirecionalPonderado->inserirVertice("B"));
  EXPECT_EQ(grafoNaoDirecionalPonderado->labelVertice(1), "B");
}

//------------------------------------------------------------

TEST_F(GrafoListaTest, RemoverVertice_NaoDirecional_Ponderado)
{
  grafoNaoDirecionalPonderado->inserirVertice("A");
  grafoNaoDirecionalPonderado->inserirVertice("B");
  EXPECT_TRUE(grafoNaoDirecionalPonderado->removerVertice(0));
  EXPECT_EQ(grafoNaoDirecionalPonderado->labelVertice(0), "B");

  grafoNaoDirecionalPonderado->inserirVertice("C");
  EXPECT_TRUE(grafoNaoDirecionalPonderado->removerVertice(1));
  EXPECT_EQ(grafoNaoDirecionalPonderado->labelVertice(0), "B");
}

//------------------------------------------------------------

TEST_F(GrafoListaTest, InserirAresta_NaoDirecional_Ponderado)
{
  grafoNaoDirecionalPonderado->inserirVertice("A");
  grafoNaoDirecionalPonderado->inserirVertice("B");
  EXPECT_TRUE(grafoNaoDirecionalPonderado->inserirAresta(0, 1, 10));
  EXPECT_TRUE(grafoNaoDirecionalPonderado->existeAresta(0, 1));
  EXPECT_EQ(grafoNaoDirecionalPonderado->pesoAresta(0, 1), 10);
  EXPECT_EQ(grafoNaoDirecionalPonderado->getVertice(0)->getGrau(), 1);
  EXPECT_EQ(grafoNaoDirecionalPonderado->getVertice(1)->getGrau(), 1);

  grafoNaoDirecionalPonderado->inserirVertice("C");
  EXPECT_TRUE(grafoNaoDirecionalPonderado->inserirAresta(1, 2, 20));
  EXPECT_TRUE(grafoNaoDirecionalPonderado->existeAresta(1, 2));
  EXPECT_EQ(grafoNaoDirecionalPonderado->pesoAresta(1, 2), 20);
  EXPECT_EQ(grafoNaoDirecionalPonderado->getVertice(1)->getGrau(), 2);
  EXPECT_EQ(grafoNaoDirecionalPonderado->getVertice(2)->getGrau(), 1);
}

//------------------------------------------------------------

TEST_F(GrafoListaTest, RemoverAresta_NaoDirecional_Ponderado)
{
  grafoNaoDirecionalPonderado->inserirVertice("A");
  grafoNaoDirecionalPonderado->inserirVertice("B");
  grafoNaoDirecionalPonderado->inserirAresta(0, 1, 10);
  EXPECT_TRUE(grafoNaoDirecionalPonderado->removerAresta(0, 1));
  EXPECT_FALSE(grafoNaoDirecionalPonderado->existeAresta(0, 1));
  EXPECT_EQ(grafoNaoDirecionalPonderado->getVertice(0)->getGrau(), 0);
  EXPECT_EQ(grafoNaoDirecionalPonderado->getVertice(1)->getGrau(), 0);

  grafoNaoDirecionalPonderado->inserirAresta(0, 1, 15);
  EXPECT_TRUE(grafoNaoDirecionalPonderado->removerAresta(0, 1));
  EXPECT_FALSE(grafoNaoDirecionalPonderado->existeAresta(0, 1));
  EXPECT_EQ(grafoNaoDirecionalPonderado->getVertice(0)->getGrau(), 0);
  EXPECT_EQ(grafoNaoDirecionalPonderado->getVertice(1)->getGrau(), 0);
}

//------------------------------------------------------------

TEST_F(GrafoListaTest, ExisteAresta_NaoDirecional_Ponderado)
{
  grafoNaoDirecionalPonderado->inserirVertice("A");
  grafoNaoDirecionalPonderado->inserirVertice("B");
  grafoNaoDirecionalPonderado->inserirAresta(0, 1, 10);
  EXPECT_TRUE(grafoNaoDirecionalPonderado->existeAresta(0, 1));

  grafoNaoDirecionalPonderado->removerAresta(0, 1);
  EXPECT_FALSE(grafoNaoDirecionalPonderado->existeAresta(0, 1));
}

//------------------------------------------------------------

TEST_F(GrafoListaTest, PesoAresta_NaoDirecional_Ponderado)
{
  grafoNaoDirecionalPonderado->inserirVertice("A");
  grafoNaoDirecionalPonderado->inserirVertice("B");
  grafoNaoDirecionalPonderado->inserirAresta(0, 1, 10);
  EXPECT_EQ(grafoNaoDirecionalPonderado->pesoAresta(0, 1), 10);

  grafoNaoDirecionalPonderado->inserirAresta(0, 1, 20);
  EXPECT_EQ(grafoNaoDirecionalPonderado->pesoAresta(0, 1), 20);
}

//------------------------------------------------------------

TEST_F(GrafoListaTest, VizinhosVertice_NaoDirecional_Ponderado)
{
  grafoNaoDirecionalPonderado->inserirVertice("A");
  grafoNaoDirecionalPonderado->inserirVertice("B");
  grafoNaoDirecionalPonderado->inserirVertice("C");
  grafoNaoDirecionalPonderado->inserirAresta(0, 1, 10);
  grafoNaoDirecionalPonderado->inserirAresta(0, 2, 20);

  std::vector<Vertice*> vizinhos = grafoNaoDirecionalPonderado->vizinhosVertice(0);
  ASSERT_EQ(vizinhos.size(), 2);
  EXPECT_STREQ(vizinhos[0]->getLabel().c_str(), "B");
  EXPECT_STREQ(vizinhos[1]->getLabel().c_str(), "C");

  grafoNaoDirecionalPonderado->removerAresta(0, 1);
  vizinhos = grafoNaoDirecionalPonderado->vizinhosVertice(0);
  ASSERT_EQ(vizinhos.size(), 1);
  EXPECT_STREQ(vizinhos[0]->getLabel().c_str(), "C");
}

//------------------------------------------------------------

TEST_F(GrafoListaTest, LabelVertice_NaoDirecional_Ponderado)
{
  grafoNaoDirecionalPonderado->inserirVertice("A");
  EXPECT_EQ(grafoNaoDirecionalPonderado->labelVertice(0), "A");

  grafoNaoDirecionalPonderado->inserirVertice("B");
  EXPECT_EQ(grafoNaoDirecionalPonderado->labelVertice(1), "B");
}

//------------------------------------------------------------

TEST_F(GrafoListaTest, Imprime_NaoDirecional_Ponderado)
{
  grafoNaoDirecionalPonderado->inserirVertice("A");
  grafoNaoDirecionalPonderado->inserirVertice("B");
  grafoNaoDirecionalPonderado->inserirAresta(0, 1, 10);

  testing::internal::CaptureStdout();
  grafoNaoDirecionalPonderado->imprime();
  std::string output = testing::internal::GetCapturedStdout();

  EXPECT_NE(output.find("A"), std::string::npos);
  EXPECT_NE(output.find("B"), std::string::npos);
  EXPECT_NE(output.find("10"), std::string::npos);
}

//------------------------------------------------------------

#endif

#ifndef TEST_GRAFO_MATRIZ_NAO_DIRECIONAL_NAO_PONDERADO

TEST_F(GrafoListaTest, InserirVertice_NaoDirecional_NaoPonderado)
{
  EXPECT_TRUE(grafoNaoDirecionalNaoPonderado->inserirVertice("A"));
  EXPECT_EQ(grafoNaoDirecionalNaoPonderado->labelVertice(0), "A");

  EXPECT_TRUE(grafoNaoDirecionalNaoPonderado->inserirVertice("B"));
  EXPECT_EQ(grafoNaoDirecionalNaoPonderado->labelVertice(1), "B");
}

//------------------------------------------------------------

TEST_F(GrafoListaTest, RemoverVertice_NaoDirecional_NaoPonderado)
{
  grafoNaoDirecionalNaoPonderado->inserirVertice("A");
  grafoNaoDirecionalNaoPonderado->inserirVertice("B");
  EXPECT_TRUE(grafoNaoDirecionalNaoPonderado->removerVertice(0));
  EXPECT_EQ(grafoNaoDirecionalNaoPonderado->labelVertice(0), "B");

  grafoNaoDirecionalNaoPonderado->inserirVertice("C");
  EXPECT_TRUE(grafoNaoDirecionalNaoPonderado->removerVertice(1));
  EXPECT_EQ(grafoNaoDirecionalNaoPonderado->labelVertice(0), "B");
}

//------------------------------------------------------------

TEST_F(GrafoListaTest, InserirAresta_NaoDirecional_NaoPonderado)
{
  grafoNaoDirecionalNaoPonderado->inserirVertice("A");
  grafoNaoDirecionalNaoPonderado->inserirVertice("B");
  EXPECT_TRUE(grafoNaoDirecionalNaoPonderado->inserirAresta(0, 1, 10));
  EXPECT_TRUE(grafoNaoDirecionalNaoPonderado->existeAresta(0, 1));
  EXPECT_EQ(grafoNaoDirecionalNaoPonderado->pesoAresta(0, 1), 1);

  grafoNaoDirecionalNaoPonderado->inserirVertice("C");
  EXPECT_TRUE(grafoNaoDirecionalNaoPonderado->inserirAresta(1, 2, 20));
  EXPECT_TRUE(grafoNaoDirecionalNaoPonderado->existeAresta(1, 2));
  EXPECT_EQ(grafoNaoDirecionalNaoPonderado->pesoAresta(1, 2), 1);
}

//------------------------------------------------------------

TEST_F(GrafoListaTest, RemoverAresta_NaoDirecional_NaoPonderado)
{
  grafoNaoDirecionalNaoPonderado->inserirVertice("A");
  grafoNaoDirecionalNaoPonderado->inserirVertice("B");
  grafoNaoDirecionalNaoPonderado->inserirAresta(0, 1, 10);
  EXPECT_TRUE(grafoNaoDirecionalNaoPonderado->removerAresta(0, 1));
  EXPECT_FALSE(grafoNaoDirecionalNaoPonderado->existeAresta(0, 1));

  grafoNaoDirecionalNaoPonderado->inserirAresta(0, 1, 15);
  EXPECT_TRUE(grafoNaoDirecionalNaoPonderado->removerAresta(0, 1));
  EXPECT_FALSE(grafoNaoDirecionalNaoPonderado->existeAresta(0, 1));
}

//------------------------------------------------------------

TEST_F(GrafoListaTest, ExisteAresta_NaoDirecional_NaoPonderado)
{
  grafoNaoDirecionalNaoPonderado->inserirVertice("A");
  grafoNaoDirecionalNaoPonderado->inserirVertice("B");
  grafoNaoDirecionalNaoPonderado->inserirAresta(0, 1, 10);
  EXPECT_TRUE(grafoNaoDirecionalNaoPonderado->existeAresta(0, 1));

  grafoNaoDirecionalNaoPonderado->removerAresta(0, 1);
  EXPECT_FALSE(grafoNaoDirecionalNaoPonderado->existeAresta(0, 1));
}

//------------------------------------------------------------

TEST_F(GrafoListaTest, PesoAresta_NaoDirecional_NaoPonderado)
{
  grafoNaoDirecionalNaoPonderado->inserirVertice("A");
  grafoNaoDirecionalNaoPonderado->inserirVertice("B");
  grafoNaoDirecionalNaoPonderado->inserirAresta(0, 1, 10);
  EXPECT_EQ(grafoNaoDirecionalNaoPonderado->pesoAresta(0, 1), 1);

  grafoNaoDirecionalNaoPonderado->inserirAresta(0, 1, 20);
  EXPECT_EQ(grafoNaoDirecionalNaoPonderado->pesoAresta(0, 1), 1);
}

//------------------------------------------------------------

TEST_F(GrafoListaTest, VizinhosVertice_NaoDirecional_NaoPonderado)
{
  grafoNaoDirecionalNaoPonderado->inserirVertice("A");
  grafoNaoDirecionalNaoPonderado->inserirVertice("B");
  grafoNaoDirecionalNaoPonderado->inserirVertice("C");
  grafoNaoDirecionalNaoPonderado->inserirAresta(0, 1, 10);
  grafoNaoDirecionalNaoPonderado->inserirAresta(0, 2, 20);

  std::vector<Vertice*> vizinhos = grafoNaoDirecionalNaoPonderado->vizinhosVertice(0);
  ASSERT_EQ(vizinhos.size(), 2);
  EXPECT_STREQ(vizinhos[0]->getLabel().c_str(), "B");
  EXPECT_STREQ(vizinhos[1]->getLabel().c_str(), "C");

  grafoNaoDirecionalNaoPonderado->removerAresta(0, 1);
  vizinhos = grafoNaoDirecionalNaoPonderado->vizinhosVertice(0);
  ASSERT_EQ(vizinhos.size(), 1);
  EXPECT_STREQ(vizinhos[0]->getLabel().c_str(), "C");
}

//------------------------------------------------------------

TEST_F(GrafoListaTest, LabelVertice_NaoDirecional_NaoPonderado)
{
  grafoNaoDirecionalNaoPonderado->inserirVertice("A");
  EXPECT_EQ(grafoNaoDirecionalNaoPonderado->labelVertice(0), "A");

  grafoNaoDirecionalNaoPonderado->inserirVertice("B");
  EXPECT_EQ(grafoNaoDirecionalNaoPonderado->labelVertice(1), "B");
}

//------------------------------------------------------------

TEST_F(GrafoListaTest, Imprime_NaoDirecional_NaoPonderado)
{
  grafoNaoDirecionalNaoPonderado->inserirVertice("A");
  grafoNaoDirecionalNaoPonderado->inserirVertice("B");
  grafoNaoDirecionalNaoPonderado->inserirAresta(0, 1, 10);

  testing::internal::CaptureStdout();
  grafoNaoDirecionalNaoPonderado->imprime();
  std::string output = testing::internal::GetCapturedStdout();

  EXPECT_NE(output.find("A"), std::string::npos);
  EXPECT_NE(output.find("B"), std::string::npos);
  EXPECT_NE(output.find("1"), std::string::npos);
}

//------------------------------------------------------------

#endif

#ifndef TEST_GRAFO_MATRIZ_DIRECIONAL_PONDERADO

TEST_F(GrafoListaTest, InserirVertice_Direcional_Ponderado)
{
  EXPECT_TRUE(grafoDirecionalPonderado->inserirVertice("A"));
  EXPECT_EQ(grafoDirecionalPonderado->labelVertice(0), "A");

  EXPECT_TRUE(grafoDirecionalPonderado->inserirVertice("B"));
  EXPECT_EQ(grafoDirecionalPonderado->labelVertice(1), "B");
}

//------------------------------------------------------------

TEST_F(GrafoListaTest, RemoverVertice_Direcional_Ponderado)
{
  grafoDirecionalPonderado->inserirVertice("A");
  grafoDirecionalPonderado->inserirVertice("B");
  EXPECT_TRUE(grafoDirecionalPonderado->removerVertice(0));
  EXPECT_EQ(grafoDirecionalPonderado->labelVertice(0), "B");

  grafoDirecionalPonderado->inserirVertice("C");
  EXPECT_TRUE(grafoDirecionalPonderado->removerVertice(1));
  EXPECT_EQ(grafoDirecionalPonderado->labelVertice(0), "B");
}

//------------------------------------------------------------

TEST_F(GrafoListaTest, InserirAresta_Direcional_Ponderado)
{
  grafoDirecionalPonderado->inserirVertice("A");
  grafoDirecionalPonderado->inserirVertice("B");
  EXPECT_TRUE(grafoDirecionalPonderado->inserirAresta(0, 1, 10));
  EXPECT_TRUE(grafoDirecionalPonderado->existeAresta(0, 1));
  EXPECT_EQ(grafoDirecionalPonderado->pesoAresta(0, 1), 10);
  EXPECT_EQ(grafoDirecionalPonderado->getVertice(0)->getGrau(), 1);
  EXPECT_EQ(grafoDirecionalPonderado->getVertice(1)->getGrau(), 0);

  grafoDirecionalPonderado->inserirVertice("C");
  EXPECT_TRUE(grafoDirecionalPonderado->inserirAresta(1, 2, 20));
  EXPECT_TRUE(grafoDirecionalPonderado->existeAresta(1, 2));
  EXPECT_EQ(grafoDirecionalPonderado->pesoAresta(1, 2), 20);
  EXPECT_EQ(grafoDirecionalPonderado->getVertice(1)->getGrau(), 1);
  EXPECT_EQ(grafoDirecionalPonderado->getVertice(2)->getGrau(), 0);
}

//------------------------------------------------------------

TEST_F(GrafoListaTest, RemoverAresta_Direcional_Ponderado)
{
  grafoDirecionalPonderado->inserirVertice("A");
  grafoDirecionalPonderado->inserirVertice("B");
  grafoDirecionalPonderado->inserirAresta(0, 1, 10);
  EXPECT_TRUE(grafoDirecionalPonderado->removerAresta(0, 1));
  EXPECT_FALSE(grafoDirecionalPonderado->existeAresta(0, 1));
  EXPECT_EQ(grafoDirecionalPonderado->getVertice(0)->getGrau(), 0);
  EXPECT_EQ(grafoDirecionalPonderado->getVertice(1)->getGrau(), 0);

  grafoDirecionalPonderado->inserirAresta(0, 1, 15);
  EXPECT_TRUE(grafoDirecionalPonderado->removerAresta(0, 1));
  EXPECT_FALSE(grafoDirecionalPonderado->existeAresta(0, 1));
  EXPECT_EQ(grafoDirecionalPonderado->getVertice(0)->getGrau(), 0);
  EXPECT_EQ(grafoDirecionalPonderado->getVertice(1)->getGrau(), 0);
}

//------------------------------------------------------------

TEST_F(GrafoListaTest, ExisteAresta_Direcional_Ponderado)
{
  grafoDirecionalPonderado->inserirVertice("A");
  grafoDirecionalPonderado->inserirVertice("B");
  grafoDirecionalPonderado->inserirAresta(0, 1, 10);
  EXPECT_TRUE(grafoDirecionalPonderado->existeAresta(0, 1));

  grafoDirecionalPonderado->removerAresta(0, 1);
  EXPECT_FALSE(grafoDirecionalPonderado->existeAresta(0, 1));
}

//------------------------------------------------------------

TEST_F(GrafoListaTest, PesoAresta_Direcional_Ponderado)
{
  grafoDirecionalPonderado->inserirVertice("A");
  grafoDirecionalPonderado->inserirVertice("B");
  grafoDirecionalPonderado->inserirAresta(0, 1, 10);
  EXPECT_EQ(grafoDirecionalPonderado->pesoAresta(0, 1), 10);

  grafoDirecionalPonderado->inserirAresta(0, 1, 20);
  EXPECT_EQ(grafoDirecionalPonderado->pesoAresta(0, 1), 20);
}

//------------------------------------------------------------

TEST_F(GrafoListaTest, VizinhosVertice_Direcional_Ponderado)
{
  grafoDirecionalPonderado->inserirVertice("A");
  grafoDirecionalPonderado->inserirVertice("B");
  grafoDirecionalPonderado->inserirVertice("C");
  grafoDirecionalPonderado->inserirAresta(0, 1, 10);
  grafoDirecionalPonderado->inserirAresta(0, 2, 20);

  std::vector<Vertice*> vizinhos = grafoDirecionalPonderado->vizinhosVertice(0);
  ASSERT_EQ(vizinhos.size(), 2);
  EXPECT_STREQ(vizinhos[0]->getLabel().c_str(), "B");
  EXPECT_STREQ(vizinhos[1]->getLabel().c_str(), "C");

  grafoDirecionalPonderado->removerAresta(0, 1);
  vizinhos = grafoDirecionalPonderado->vizinhosVertice(0);
  ASSERT_EQ(vizinhos.size(), 1);
  EXPECT_STREQ(vizinhos[0]->getLabel().c_str(), "C");
}

//------------------------------------------------------------

TEST_F(GrafoListaTest, LabelVertice_Direcional_Ponderado)
{
  grafoDirecionalPonderado->inserirVertice("A");
  EXPECT_EQ(grafoDirecionalPonderado->labelVertice(0), "A");

  grafoDirecionalPonderado->inserirVertice("B");
  EXPECT_EQ(grafoDirecionalPonderado->labelVertice(1), "B");
}

//------------------------------------------------------------

TEST_F(GrafoListaTest, Imprime_Direcional_Ponderado)
{
  grafoDirecionalPonderado->inserirVertice("A");
  grafoDirecionalPonderado->inserirVertice("B");
  grafoDirecionalPonderado->inserirAresta(0, 1, 10);

  testing::internal::CaptureStdout();
  grafoDirecionalPonderado->imprime();
  std::string output = testing::internal::GetCapturedStdout();

  EXPECT_NE(output.find("A"), std::string::npos);
  EXPECT_NE(output.find("B"), std::string::npos);
  EXPECT_NE(output.find("10"), std::string::npos);
}

//------------------------------------------------------------

#endif

#ifndef TEST_GRAFO_MATRIZ_DIRECIONAL_NAO_PONDERADO

TEST_F(GrafoListaTest, InserirVertice_Direcional_NaoPonderado)
{
  EXPECT_TRUE(grafoDirecionalNaoPonderado->inserirVertice("A"));
  EXPECT_EQ(grafoDirecionalNaoPonderado->labelVertice(0), "A");

  EXPECT_TRUE(grafoDirecionalNaoPonderado->inserirVertice("B"));
  EXPECT_EQ(grafoDirecionalNaoPonderado->labelVertice(1), "B");
}

//------------------------------------------------------------

TEST_F(GrafoListaTest, RemoverVertice_Direcional_NaoPonderado)
{
  grafoDirecionalNaoPonderado->inserirVertice("A");
  grafoDirecionalNaoPonderado->inserirVertice("B");
  EXPECT_TRUE(grafoDirecionalNaoPonderado->removerVertice(0));
  EXPECT_EQ(grafoDirecionalNaoPonderado->labelVertice(0), "B");

  grafoDirecionalNaoPonderado->inserirVertice("C");
  EXPECT_TRUE(grafoDirecionalNaoPonderado->removerVertice(1));
  EXPECT_EQ(grafoDirecionalNaoPonderado->labelVertice(0), "B");
}

//------------------------------------------------------------

TEST_F(GrafoListaTest, InserirAresta_Direcional_NaoPonderado)
{
  grafoDirecionalNaoPonderado->inserirVertice("A");
  grafoDirecionalNaoPonderado->inserirVertice("B");
  EXPECT_TRUE(grafoDirecionalNaoPonderado->inserirAresta(0, 1, 10));
  EXPECT_TRUE(grafoDirecionalNaoPonderado->existeAresta(0, 1));
  EXPECT_EQ(grafoDirecionalNaoPonderado->pesoAresta(0, 1), 1);

  grafoDirecionalNaoPonderado->inserirVertice("C");
  EXPECT_TRUE(grafoDirecionalNaoPonderado->inserirAresta(1, 2, 20));
  EXPECT_TRUE(grafoDirecionalNaoPonderado->existeAresta(1, 2));
  EXPECT_EQ(grafoDirecionalNaoPonderado->pesoAresta(1, 2), 1);
}

//------------------------------------------------------------

TEST_F(GrafoListaTest, RemoverAresta_Direcional_NaoPonderado)
{
  grafoDirecionalNaoPonderado->inserirVertice("A");
  grafoDirecionalNaoPonderado->inserirVertice("B");
  grafoDirecionalNaoPonderado->inserirAresta(0, 1, 10);
  EXPECT_TRUE(grafoDirecionalNaoPonderado->removerAresta(0, 1));
  EXPECT_FALSE(grafoDirecionalNaoPonderado->existeAresta(0, 1));

  grafoDirecionalNaoPonderado->inserirAresta(0, 1, 15);
  EXPECT_TRUE(grafoDirecionalNaoPonderado->removerAresta(0, 1));
  EXPECT_FALSE(grafoDirecionalNaoPonderado->existeAresta(0, 1));
}

//------------------------------------------------------------

TEST_F(GrafoListaTest, ExisteAresta_Direcional_NaoPonderado)
{
  grafoDirecionalNaoPonderado->inserirVertice("A");
  grafoDirecionalNaoPonderado->inserirVertice("B");
  grafoDirecionalNaoPonderado->inserirAresta(0, 1, 10);
  EXPECT_TRUE(grafoDirecionalNaoPonderado->existeAresta(0, 1));

  grafoDirecionalNaoPonderado->removerAresta(0, 1);
  EXPECT_FALSE(grafoDirecionalNaoPonderado->existeAresta(0, 1));
}

//------------------------------------------------------------

TEST_F(GrafoListaTest, PesoAresta_Direcional_NaoPonderado)
{
  grafoDirecionalNaoPonderado->inserirVertice("A");
  grafoDirecionalNaoPonderado->inserirVertice("B");
  grafoDirecionalNaoPonderado->inserirAresta(0, 1, 10);
  EXPECT_EQ(grafoDirecionalNaoPonderado->pesoAresta(0, 1), 1);

  grafoDirecionalNaoPonderado->inserirAresta(0, 1, 20);
  EXPECT_EQ(grafoDirecionalNaoPonderado->pesoAresta(0, 1), 1);
}

//------------------------------------------------------------

TEST_F(GrafoListaTest, VizinhosVertice_Direcional_NaoPonderado)
{
  grafoDirecionalNaoPonderado->inserirVertice("A");
  grafoDirecionalNaoPonderado->inserirVertice("B");
  grafoDirecionalNaoPonderado->inserirVertice("C");
  grafoDirecionalNaoPonderado->inserirAresta(0, 1, 10);
  grafoDirecionalNaoPonderado->inserirAresta(0, 2, 20);

  std::vector<Vertice*> vizinhos = grafoDirecionalNaoPonderado->vizinhosVertice(0);
  ASSERT_EQ(vizinhos.size(), 2);
  EXPECT_STREQ(vizinhos[0]->getLabel().c_str(), "B");
  EXPECT_STREQ(vizinhos[1]->getLabel().c_str(), "C");

  grafoDirecionalNaoPonderado->removerAresta(0, 1);
  vizinhos = grafoDirecionalNaoPonderado->vizinhosVertice(0);
  ASSERT_EQ(vizinhos.size(), 1);
  EXPECT_STREQ(vizinhos[0]->getLabel().c_str(), "C");
}

//------------------------------------------------------------

TEST_F(GrafoListaTest, LabelVertice_Direcional_NaoPonderado)
{
  grafoDirecionalNaoPonderado->inserirVertice("A");
  EXPECT_EQ(grafoDirecionalNaoPonderado->labelVertice(0), "A");

  grafoDirecionalNaoPonderado->inserirVertice("B");
  EXPECT_EQ(grafoDirecionalNaoPonderado->labelVertice(1), "B");
}

//------------------------------------------------------------

TEST_F(GrafoListaTest, Imprime_Direcional_NaoPonderado)
{
  grafoDirecionalNaoPonderado->inserirVertice("A");
  grafoDirecionalNaoPonderado->inserirVertice("B");
  grafoDirecionalNaoPonderado->inserirAresta(0, 1, 10);

  testing::internal::CaptureStdout();
  grafoDirecionalNaoPonderado->imprime();
  std::string output = testing::internal::GetCapturedStdout();

  EXPECT_NE(output.find("A"), std::string::npos);
  EXPECT_NE(output.find("B"), std::string::npos);
  EXPECT_NE(output.find("1"), std::string::npos);
}

//------------------------------------------------------------

#endif