#ifndef ALGORITMODIJKSTRA_TEST_H
#define ALGORITMODIJKSTRA_TEST_H

//------------------------------------------------------------

#include <gtest/gtest.h>

//------------------------------------------------------------

class GrafoMatriz;

//------------------------------------------------------------

class AlgoritmoDijkstraTest : public ::testing::Test
{
protected:
  void SetUp() override;
  void TearDown() override;
};

//------------------------------------------------------------

#endif