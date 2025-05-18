#ifndef BUSCAPROFUNDIDADE_TEST_H
#define BUSCAPROFUNDIDADE_TEST_H

//------------------------------------------------------------

#include <gtest/gtest.h>

//------------------------------------------------------------

class GrafoMatriz;

//------------------------------------------------------------

class BuscaProfundidadeTest : public ::testing::Test
{
protected:
  void SetUp() override;
  void TearDown() override;
};

//------------------------------------------------------------

#endif