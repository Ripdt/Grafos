#include "Coloracao_test.h"

#include "grafos/Coloracao.h"

#include "grafos/GrafoLista.h"
#include "grafos/GrafoMatriz.h"

//------------------------------------------------------------
// ColoracaoTest
//------------------------------------------------------------

void ColoracaoTest::SetUp()
{
}

//------------------------------------------------------------

void ColoracaoTest::TearDown()
{
}

//------------------------------------------------------------
// FORCA BRUTA
//------------------------------------------------------------

TEST_F(ColoracaoTest, Coloracao_BruteForce_GrafoListaVazio)
{
  GrafoLista grafo(false, false);

  Coloracao coloracao(grafo);
  coloracao.colorir_BruteForce();
  EXPECT_TRUE(true);
}

//------------------------------------------------------------

TEST_F(ColoracaoTest, Coloracao_BruteForce_GrafoListaSimples)
{
  GrafoLista grafo(false, false);
  grafo.inserirVertice("A");
  grafo.inserirVertice("B");
  grafo.inserirAresta(0, 1);

  Coloracao coloracao(grafo);
  coloracao.colorir_BruteForce();

  EXPECT_EQ(grafo.getVertice(0)->getCor(), 1);
  EXPECT_EQ(grafo.getVertice(1)->getCor(), 0);
}

//------------------------------------------------------------

TEST_F(ColoracaoTest, Coloracao_BruteForce_GrafoMatrizVazio)
{
  GrafoMatriz grafo(false, false);

  Coloracao coloracao(grafo);
  coloracao.colorir_BruteForce();
  EXPECT_TRUE(true);
}

//------------------------------------------------------------

TEST_F(ColoracaoTest, Coloracao_BruteForce_GrafoMatrizSimples)
{
  GrafoMatriz grafo(false, false);
  grafo.inserirVertice("A");
  grafo.inserirVertice("B");
  grafo.inserirAresta(0, 1);

  Coloracao coloracao(grafo);
  coloracao.colorir_BruteForce();

  EXPECT_EQ(grafo.getVertice(0)->getCor(), 1);
  EXPECT_EQ(grafo.getVertice(1)->getCor(), 0);
}

//------------------------------------------------------------

TEST_F(ColoracaoTest, Coloracao_BruteForce_GrafoDesconexo)
{
  GrafoMatriz grafo(false, false);
  grafo.inserirVertice("A");
  grafo.inserirVertice("B");
  grafo.inserirVertice("C");

  Coloracao coloracao(grafo);
  coloracao.colorir_BruteForce();

  // Todos os vértices podem ter a mesma cor
  int corA = grafo.getVertice(0)->getCor();
  int corB = grafo.getVertice(1)->getCor();
  int corC = grafo.getVertice(2)->getCor();

  EXPECT_EQ(corA, corB);
  EXPECT_EQ(corB, corC);
}

//------------------------------------------------------------

TEST_F(ColoracaoTest, Coloracao_BruteForce_Triangulo)
{
  GrafoMatriz grafo(false, false);
  grafo.inserirVertice("A");
  grafo.inserirVertice("B");
  grafo.inserirVertice("C");

  grafo.inserirAresta(0, 1);
  grafo.inserirAresta(1, 2);
  grafo.inserirAresta(2, 0);

  Coloracao coloracao(grafo);
  coloracao.colorir_BruteForce();

  EXPECT_NE(grafo.getVertice(0)->getCor(), grafo.getVertice(1)->getCor());
  EXPECT_NE(grafo.getVertice(1)->getCor(), grafo.getVertice(2)->getCor());
  EXPECT_NE(grafo.getVertice(2)->getCor(), grafo.getVertice(0)->getCor());
}

//------------------------------------------------------------

TEST_F(ColoracaoTest, Coloracao_BruteForce_GrafoCompleto4)
{
  GrafoMatriz grafo(false, false);
  for (int i = 0; i < 4; ++i)
    grafo.inserirVertice(std::string(1, 'A' + i));

  for (int i = 0; i < 4; ++i)
    for (int j = i + 1; j < 4; ++j)
      grafo.inserirAresta(i, j);

  Coloracao coloracao(grafo);
  coloracao.colorir_BruteForce();

  std::set<int> cores;
  for (int i = 0; i < 4; ++i)
    cores.insert(grafo.getVertice(i)->getCor());

  EXPECT_EQ(cores.size(), 4);
}

//------------------------------------------------------------
// WELSH & POWELL
//------------------------------------------------------------

TEST_F(ColoracaoTest, Coloracao_WelshPowell_GrafoListaVazio)
{
  GrafoLista grafo(false, false);

  Coloracao coloracao(grafo);
  coloracao.colorir_WelshPowell();
  EXPECT_TRUE(true);
}

//------------------------------------------------------------

TEST_F(ColoracaoTest, Coloracao_WelshPowell_GrafoListaSimples)
{
  GrafoLista grafo(false, false);
  grafo.inserirVertice("A");
  grafo.inserirVertice("B");
  grafo.inserirAresta(0, 1);

  Coloracao coloracao(grafo);
  coloracao.colorir_WelshPowell();

  EXPECT_EQ(grafo.getVertice(0)->getCor(), 2);
  EXPECT_EQ(grafo.getVertice(1)->getCor(), 1);
}

//------------------------------------------------------------

TEST_F(ColoracaoTest, Coloracao_WelshPowell_GrafoMatrizVazio)
{
  GrafoMatriz grafo(false, false);

  Coloracao coloracao(grafo);
  coloracao.colorir_WelshPowell();
  EXPECT_TRUE(true);
}

//------------------------------------------------------------

TEST_F(ColoracaoTest, Coloracao_WelshPowell_GrafoMatrizSimples)
{
  GrafoMatriz grafo(false, false);
  grafo.inserirVertice("A");
  grafo.inserirVertice("B");
  grafo.inserirAresta(0, 1);

  Coloracao coloracao(grafo);
  coloracao.colorir_WelshPowell();

  EXPECT_EQ(grafo.getVertice(0)->getCor(), 2);
  EXPECT_EQ(grafo.getVertice(1)->getCor(), 1);
}

//------------------------------------------------------------

TEST_F(ColoracaoTest, Coloracao_WelshPowell_GrafoDesconexo)
{
  GrafoMatriz grafo(false, false);
  grafo.inserirVertice("A");
  grafo.inserirVertice("B");
  grafo.inserirVertice("C");

  Coloracao coloracao(grafo);
  coloracao.colorir_WelshPowell();

  // Todos os vértices podem ter a mesma cor
  int corA = grafo.getVertice(0)->getCor();
  int corB = grafo.getVertice(1)->getCor();
  int corC = grafo.getVertice(2)->getCor();

  EXPECT_EQ(corA, corB);
  EXPECT_EQ(corB, corC);
}

//------------------------------------------------------------

TEST_F(ColoracaoTest, Coloracao_WelshPowell_Triangulo)
{
  GrafoMatriz grafo(false, false);
  grafo.inserirVertice("A");
  grafo.inserirVertice("B");
  grafo.inserirVertice("C");

  grafo.inserirAresta(0, 1);
  grafo.inserirAresta(1, 2);
  grafo.inserirAresta(2, 0);

  Coloracao coloracao(grafo);
  coloracao.colorir_WelshPowell();

  EXPECT_NE(grafo.getVertice(0)->getCor(), grafo.getVertice(1)->getCor());
  EXPECT_NE(grafo.getVertice(1)->getCor(), grafo.getVertice(2)->getCor());
  EXPECT_NE(grafo.getVertice(2)->getCor(), grafo.getVertice(0)->getCor());
}

//------------------------------------------------------------

TEST_F(ColoracaoTest, Coloracao_WelshPowell_GrafoCompleto4)
{
  GrafoMatriz grafo(false, false);
  for (int i = 0; i < 4; ++i)
    grafo.inserirVertice(std::string(1, 'A' + i));

  for (int i = 0; i < 4; ++i)
    for (int j = i + 1; j < 4; ++j)
      grafo.inserirAresta(i, j);

  Coloracao coloracao(grafo);
  coloracao.colorir_WelshPowell();

  std::set<int> cores;
  for (int i = 0; i < 4; ++i)
    cores.insert(grafo.getVertice(i)->getCor());

  EXPECT_EQ(cores.size(), 4);
}

//------------------------------------------------------------
// DSatur
//------------------------------------------------------------

TEST_F(ColoracaoTest, Coloracao_DSatur_GrafoListaVazio)
{
  GrafoLista grafo(false, false);

  Coloracao coloracao(grafo);
  coloracao.colorir_DSatur();
  EXPECT_TRUE(true);
}

//------------------------------------------------------------

TEST_F(ColoracaoTest, Coloracao_DSatur_GrafoListaSimples)
{
  GrafoLista grafo(false, false);
  grafo.inserirVertice("A");
  grafo.inserirVertice("B");
  grafo.inserirAresta(0, 1);

  Coloracao coloracao(grafo);
  coloracao.colorir_DSatur();

  EXPECT_EQ(grafo.getVertice(0)->getCor(), 2);
  EXPECT_EQ(grafo.getVertice(1)->getCor(), 1);
}

//------------------------------------------------------------

TEST_F(ColoracaoTest, Coloracao_DSatur_GrafoMatrizVazio)
{
  GrafoMatriz grafo(false, false);

  Coloracao coloracao(grafo);
  coloracao.colorir_DSatur();
  EXPECT_TRUE(true);
}

//------------------------------------------------------------

TEST_F(ColoracaoTest, Coloracao_DSatur_GrafoMatrizSimples)
{
  GrafoMatriz grafo(false, false);
  grafo.inserirVertice("A");
  grafo.inserirVertice("B");
  grafo.inserirAresta(0, 1);

  Coloracao coloracao(grafo);
  coloracao.colorir_DSatur();

  EXPECT_EQ(grafo.getVertice(0)->getCor(), 2);
  EXPECT_EQ(grafo.getVertice(1)->getCor(), 1);
}

//------------------------------------------------------------

TEST_F(ColoracaoTest, Coloracao_DSatur_GrafoDesconexo)
{
  GrafoMatriz grafo(false, false);
  grafo.inserirVertice("A");
  grafo.inserirVertice("B");
  grafo.inserirVertice("C");

  Coloracao coloracao(grafo);
  coloracao.colorir_DSatur();

  // Todos os vértices podem ter a mesma cor
  int corA = grafo.getVertice(0)->getCor();
  int corB = grafo.getVertice(1)->getCor();
  int corC = grafo.getVertice(2)->getCor();

  EXPECT_EQ(corA, corB);
  EXPECT_EQ(corB, corC);
}

//------------------------------------------------------------

TEST_F(ColoracaoTest, Coloracao_DSatur_Triangulo)
{
  GrafoMatriz grafo(false, false);
  grafo.inserirVertice("A");
  grafo.inserirVertice("B");
  grafo.inserirVertice("C");

  grafo.inserirAresta(0, 1);
  grafo.inserirAresta(1, 2);
  grafo.inserirAresta(2, 0);

  Coloracao coloracao(grafo);
  coloracao.colorir_DSatur();

  EXPECT_NE(grafo.getVertice(0)->getCor(), grafo.getVertice(1)->getCor());
  EXPECT_NE(grafo.getVertice(1)->getCor(), grafo.getVertice(2)->getCor());
  EXPECT_NE(grafo.getVertice(2)->getCor(), grafo.getVertice(0)->getCor());
}

//------------------------------------------------------------

TEST_F(ColoracaoTest, Coloracao_DSatur_GrafoCompleto4)
{
  GrafoMatriz grafo(false, false);
  for (int i = 0; i < 4; ++i)
    grafo.inserirVertice(std::string(1, 'A' + i));

  for (int i = 0; i < 4; ++i)
    for (int j = i + 1; j < 4; ++j)
      grafo.inserirAresta(i, j);

  Coloracao coloracao(grafo);
  coloracao.colorir_DSatur();

  std::set<int> cores;
  for (int i = 0; i < 4; ++i)
    cores.insert(grafo.getVertice(i)->getCor());

  EXPECT_EQ(cores.size(), 4);
}

//------------------------------------------------------------

