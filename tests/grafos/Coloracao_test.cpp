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

TEST_F(ColoracaoTest, Coloracao_ForcaBruta_GrafoListaVazio)
{
  GrafoLista grafo(false, false);

  Coloracao coloracao(grafo);
  std::vector<int> cores = coloracao.colorir();
  EXPECT_TRUE(cores.empty());
}

//------------------------------------------------------------

TEST_F(ColoracaoTest, Coloracao_ForcaBruta_GrafoListaSimples)
{
  GrafoLista grafo(false, false);
  grafo.inserirVertice("A");
  grafo.inserirVertice("B");
  grafo.inserirAresta(0, 1);

  Coloracao coloracao(grafo);
  std::vector<int> cores = coloracao.colorir();
  EXPECT_TRUE(cores.size() == 2);
  EXPECT_TRUE(cores[0] != cores[1]);
}

//------------------------------------------------------------

TEST_F(ColoracaoTest, Coloracao_ForcaBruta_GrafoMatrizVazio)
{
  GrafoMatriz grafo(false, false);

  Coloracao coloracao(grafo);
  std::vector<int> cores = coloracao.colorir();
  EXPECT_TRUE(cores.empty());
}

//------------------------------------------------------------

TEST_F(ColoracaoTest, Coloracao_ForcaBruta_GrafoMatrizSimples)
{
  GrafoMatriz grafo(false, false);
  grafo.inserirVertice("A");
  grafo.inserirVertice("B");
  grafo.inserirAresta(0, 1);

  Coloracao coloracao(grafo);
  std::vector<int> cores = coloracao.colorir();
  EXPECT_TRUE(cores.size() == 2);
  EXPECT_TRUE(cores[0] != cores[1]);
}

//------------------------------------------------------------

