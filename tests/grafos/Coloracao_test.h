#ifndef COLORACAO_TEST_H
#define COLORACAO_TEST_H

//------------------------------------------------------------

#include <gtest/gtest.h>

//------------------------------------------------------------

class ColoracaoTest : public ::testing::Test
{
protected:
  void SetUp() override;
  void TearDown() override;
};

//------------------------------------------------------------

#endif