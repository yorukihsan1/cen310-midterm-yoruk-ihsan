#include "gtest/gtest.h"
#include "../../calculator/header/calculator.h"

using namespace Coruh::Calculator;

class CalculatorTest : public ::testing::Test {
 protected:
  void SetUp() override {}

  void TearDown() override {}
};

// === Test: Basic Arithmetic Operations ===
TEST_F(CalculatorTest, TestAdd) {
  EXPECT_DOUBLE_EQ(Calculator::add(2.0, 3.0), 5.0);
  EXPECT_DOUBLE_EQ(Calculator::add(-2.0, 3.0), 1.0);
  EXPECT_DOUBLE_EQ(Calculator::add(0.0, 0.0), 0.0);
}

TEST_F(CalculatorTest, TestSubtract) {
  EXPECT_DOUBLE_EQ(Calculator::subtract(5.0, 3.0), 2.0);
  EXPECT_DOUBLE_EQ(Calculator::subtract(-2.0, 3.0), -5.0);
  EXPECT_DOUBLE_EQ(Calculator::subtract(0.0, 0.0), 0.0);
}

TEST_F(CalculatorTest, TestMultiply) {
  EXPECT_DOUBLE_EQ(Calculator::multiply(2.0, 3.0), 6.0);
  EXPECT_DOUBLE_EQ(Calculator::multiply(-2.0, 3.0), -6.0);
  EXPECT_DOUBLE_EQ(Calculator::multiply(0.0, 5.0), 0.0);
}

TEST_F(CalculatorTest, TestDivide) {
  EXPECT_DOUBLE_EQ(Calculator::divide(6.0, 2.0), 3.0);
  EXPECT_DOUBLE_EQ(Calculator::divide(-6.0, 2.0), -3.0);
  EXPECT_DOUBLE_EQ(Calculator::divide(0.0, 5.0), 0.0);
  EXPECT_THROW(Calculator::divide(5.0, 0.0), std::invalid_argument);
}

// === Test: isInsideCircle ===
TEST_F(CalculatorTest, TestIsInsideCircle) {
  // Points on the circle (x^2 + y^2 = 1)
  EXPECT_TRUE(Calculator::isInsideCircle(1.0, 0.0));
  EXPECT_TRUE(Calculator::isInsideCircle(0.0, 1.0));
  EXPECT_FALSE(Calculator::isInsideCircle(1.0, 1.0));
  EXPECT_TRUE(Calculator::isInsideCircle(0.5, 0.5));
  EXPECT_FALSE(Calculator::isInsideCircle(1.1, 0.0));
}

// === Test: generatePoints ===
TEST_F(CalculatorTest, TestGeneratePointsSizeAndRange) {
  int numPoints = 1000;
  auto points = Calculator::generatePoints(numPoints);
  EXPECT_EQ(points.size(), numPoints);

  for (const auto& p : points) {
    EXPECT_GE(p.first, -1.0);
    EXPECT_LE(p.first, 1.0);
    EXPECT_GE(p.second, -1.0);
    EXPECT_LE(p.second, 1.0);
  }
}

// === Test: calculatePiSequential ===
TEST_F(CalculatorTest, TestCalculatePiSequential) {
  double pi = Calculator::calculatePiSequential(100000);
  EXPECT_NEAR(pi, 3.1415, 0.05);  // Monte Carlo 0.05 tolerans
}

// === Test: calculatePiParallel ===
TEST_F(CalculatorTest, TestCalculatePiParallel) {
  double pi = Calculator::calculatePiParallel(100000, 4);
  EXPECT_NEAR(pi, 3.1415, 0.05);
}

// === Test: calculateConvergence ===
TEST_F(CalculatorTest, TestCalculateConvergence) {
  auto points = Calculator::generatePoints(10000);
  auto convergence = Calculator::calculateConvergence(points);
  EXPECT_GT(convergence.size(), 5);  // 10000/1000 = 10 veri noktas beklenir

  for (double piVal : convergence) {
    EXPECT_GT(piVal, 2.5);
    EXPECT_LT(piVal, 4.0);
  }
}

// === Main ===
int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
