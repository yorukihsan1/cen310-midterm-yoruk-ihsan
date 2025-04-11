#include <gtest/gtest.h>
#include "../calculator/header/calculator.h"
#include <cmath>

using namespace Coruh::Calculator;

TEST(CalculatorTest, SequentialPiCalculation) {
  const int numPoints = 1000000;
  double pi = Calculator::calculatePiSequential(numPoints);
  EXPECT_NEAR(pi, M_PI, 0.01);  // Allow 1% error
}

TEST(CalculatorTest, ParallelPiCalculation) {
  const int numPoints = 1000000;
  const int numThreads = 4;
  double pi = Calculator::calculatePiParallel(numPoints, numThreads);
  EXPECT_NEAR(pi, M_PI, 0.01);  // Allow 1% error
}

TEST(CalculatorTest, PointGeneration) {
  const int numPoints = 1000;
  auto points = Calculator::generatePoints(numPoints);
  EXPECT_EQ(points.size(), numPoints);

  for (const auto& point : points) {
    EXPECT_GE(point.first, -1.0);
    EXPECT_LE(point.first, 1.0);
    EXPECT_GE(point.second, -1.0);
    EXPECT_LE(point.second, 1.0);
  }
}

TEST(CalculatorTest, ConvergenceCalculation) {
  const int numPoints = 10000;
  auto points = Calculator::generatePoints(numPoints);
  auto convergence = Calculator::calculateConvergence(points);
  EXPECT_FALSE(convergence.empty());
  EXPECT_NEAR(convergence.back(), M_PI, 0.1);  // Allow 10% error for convergence
}

TEST(CalculatorTest, InsideCircleCheck) {
  EXPECT_TRUE(Calculator::isInsideCircle(0.0, 0.0));  // Center
  EXPECT_TRUE(Calculator::isInsideCircle(1.0, 0.0));  // Right edge
  EXPECT_TRUE(Calculator::isInsideCircle(0.0, 1.0));  // Top edge
  EXPECT_FALSE(Calculator::isInsideCircle(1.1, 0.0)); // Outside
  EXPECT_FALSE(Calculator::isInsideCircle(0.0, 1.1)); // Outside
}
