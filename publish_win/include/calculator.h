/**
 * @file calculator.h
 *
 * @brief Provides functions for Monte Carlo Pi calculation and visualization
 *
 * This file contains the implementation of the Monte Carlo method for calculating Pi.
 * The Monte Carlo method uses random sampling to approximate the value of Pi by
 * comparing the ratio of points inside a unit circle (radius 1) to the total number
 * of points in a square that contains the circle.
 *
 * The implementation includes both sequential and parallel versions using OpenMP.
 * The parallel version distributes the work across multiple threads to improve
 * performance on multi-core systems.
 */

#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "../../utility/header/commonTypes.h"
#include <vector>
#include <random>

namespace Coruh {
namespace Calculator {
/**
    @class Calculator
    @brief Provides Monte Carlo Pi calculation and visualization functions.

    This class implements the Monte Carlo method for calculating Pi using
    both sequential and parallel approaches. The parallel implementation
    uses OpenMP to distribute the work across multiple threads.

    The Monte Carlo method works by:
    1. Generating random points in a 2x2 square centered at the origin
    2. Counting how many points fall inside a unit circle (radius 1)
    3. Calculating Pi as 4 * (points inside circle) / (total points)

    The accuracy of the result improves with more points, but so does
    the computation time. The parallel implementation can significantly
    reduce computation time on multi-core systems.
*/
class Calculator {
 public:
  /**
   * Checks if a point lies inside the unit circle.
   *
   * This function determines if a given point (x,y) lies inside the unit circle (radius 1)
   * centered at the origin.
   *
   * @param x X coordinate of the point
   * @param y Y coordinate of the point
   * @return true if point is inside the circle, false otherwise
   *
   * @note A point is inside the unit circle if x^2 + y^2 <= 1.
   */
  static bool isInsideCircle(double x, double y);

  /**
   * Calculates Pi using Monte Carlo method sequentially.
   *
   * This function implements the sequential version of the Monte Carlo
   * method for calculating Pi. It generates random points and counts
   * how many fall inside a unit circle.
   *
   * @param numPoints Number of points to generate.
   * @return The calculated value of Pi.
   *
   * @note The accuracy improves with more points, but computation time
   *       increases linearly with the number of points.
   */
  static double calculatePiSequential(int numPoints);

  /**
   * Calculates Pi using Monte Carlo method in parallel using OpenMP.
   *
   * This function implements the parallel version of the Monte Carlo
   * method using OpenMP. It distributes the work across multiple threads
   * to improve performance on multi-core systems.
   *
   * @param numPoints Number of points to generate.
   * @param numThreads Number of threads to use.
   * @return The calculated value of Pi.
   *
   * @note The speedup depends on the number of available CPU cores and
   *       the overhead of thread creation and synchronization.
   */
  static double calculatePiParallel(int numPoints, int numThreads);

  /**
   * Generates random points for Monte Carlo Pi calculation.
   *
   * This function generates random points in a 2x2 square centered at
   * the origin. The points are used for the Monte Carlo Pi calculation.
   *
   * @param numPoints Number of points to generate.
   * @return Vector of points (x,y coordinates).
   *
   * @note The points are generated using a uniform distribution in the
   *       range [-1, 1] for both x and y coordinates.
   */
  static std::vector<std::pair<double, double>> generatePoints(int numPoints);

  /**
   * Calculates the convergence rate of Pi calculation.
   *
   * This function analyzes how the Pi approximation converges as more
   * points are processed. It calculates Pi approximations at regular
   * intervals to show the convergence behavior.
   *
   * @param points Vector of points to analyze.
   * @return Vector of Pi approximations at different stages.
   *
   * @note The approximations are calculated every 1000 points to show
   *       the convergence behavior over time.
   */
  static std::vector<double> calculateConvergence(const std::vector<std::pair<double, double>> &points);

  /**
   * Adds two numbers.
   * @param a First number
   * @param b Second number
   * @return Sum of a and b
   */
  static double add(double a, double b);

  /**
   * Subtracts second number from first number.
   * @param a First number
   * @param b Second number
   * @return Difference of a and b
   */
  static double subtract(double a, double b);

  /**
   * Multiplies two numbers.
   * @param a First number
   * @param b Second number
   * @return Product of a and b
   */
  static double multiply(double a, double b);

  /**
   * Divides first number by second number.
   * @param a First number
   * @param b Second number
   * @return Quotient of a and b
   * @throw std::invalid_argument if b is zero
   */
  static double divide(double a, double b);

 private:
  // ... existing code ...
};
}
}

#endif // CALCULATOR_H
