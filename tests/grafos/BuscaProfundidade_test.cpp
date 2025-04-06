#include "BuscaProfundidade_test.h"

#include "grafos/BuscaProfundidade.h"
#include "grafos/GrafoMatriz.h"
#include "grafos/GrafoLista.h"
#include "grafos/Vertice.h"

//------------------------------------------------------------
// GrafoMatrizTest
//------------------------------------------------------------

void BuscaProfundidadeTest::SetUp()
{
}

//------------------------------------------------------------

void BuscaProfundidadeTest::TearDown()
{
}

//------------------------------------------------------------

TEST_F(BuscaProfundidadeTest, TESTA_BUSCA_MATRIZ_DIRECIONADA_1)
{
  GrafoMatriz grafo(true, false);
  grafo.inserirVertice("A");
  grafo.inserirVertice("B");
  grafo.inserirVertice("C");
  grafo.inserirAresta(0, 1);
  grafo.inserirAresta(1, 2);

  BuscaProfundidade busca(grafo);

  std::set<Vertice> resultado = busca.percorrerTodosOsVertices(0);
  EXPECT_EQ(resultado.size(), 3);
  int i = 0;
  for (const Vertice& v : resultado) {
    EXPECT_EQ(v.getIndice(), i);
    i++;
  }

  resultado = busca.percorrerTodosOsVertices(1);
  EXPECT_EQ(resultado.size(), 2); 
  
  resultado = busca.percorrerTodosOsVertices(2);
  EXPECT_EQ(resultado.size(), 1);
  i = 2;
  for (const Vertice& v : resultado) {
    EXPECT_EQ(v.getIndice(), i);
    i++;
  }

  grafo.inserirAresta(1, 0); 
  resultado = busca.percorrerTodosOsVertices(1);
  EXPECT_EQ(resultado.size(), 3);
}

//------------------------------------------------------------

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
  std::set<Vertice> resultado = busca.percorrerTodosOsVertices(0);
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

//------------------------------------------------------------