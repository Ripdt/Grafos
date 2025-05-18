#ifndef BUSCALARGURA_TEST_H
#define BUSCALARGURA_TEST_H

//------------------------------------------------------------

#include <gtest/gtest.h>

//------------------------------------------------------------

class GrafoMatriz;

//------------------------------------------------------------

class BuscaLarguraTest : public ::testing::Test
{
protected:
  void SetUp() override;
  void TearDown() override;
};

//------------------------------------------------------------

#endif