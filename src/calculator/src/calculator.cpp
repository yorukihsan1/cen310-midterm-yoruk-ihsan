/**
 * @file calculator.cpp
 * @brief Implementation of Monte Carlo Pi calculation methods
 *
 * This file contains the implementation of the Monte Carlo method for calculating Pi.
 * It includes both sequential and parallel versions using OpenMP.
 */

#include "../header/calculator.h"
#include <stdexcept>
#include <random>
#include <cmath>
#include <omp.h>

using namespace Coruh::Calculator;

double Calculator::add(double a, double b) {
  return a + b;
}

double Calculator::subtract(double a, double b) {
  return a - b;
}

double Calculator::multiply(double a, double b) {
  return a * b;
}

double Calculator::divide(double a, double b) {
  if (b == 0) {
    throw std::invalid_argument("Division by zero is not allowed.");
  }

  return a / b;
}

/**
 * @brief Calculates Pi using Monte Carlo method sequentially
 *
 * This function implements the sequential version of the Monte Carlo method.
 * It generates random points and counts how many fall inside a unit circle.
 *
 * @param numPoints Number of points to generate
 * @return The calculated value of Pi
 */
double Calculator::calculatePiSequential(int numPoints) {
  auto points = generatePoints(numPoints);
  int pointsInside = 0;

  for (const auto& point : points) {
    if (isInsideCircle(point.first, point.second)) {
      pointsInside++;
    }
  }

  return 4.0 * pointsInside / numPoints;
}

/**
 * @brief Calculates Pi using Monte Carlo method in parallel using OpenMP
 *
 * This function implements the parallel version of the Monte Carlo method.
 * It distributes the work across multiple threads using OpenMP.
 *
 * @param numPoints Number of points to generate
 * @param numThreads Number of threads to use
 * @return The calculated value of Pi
 */
double Calculator::calculatePiParallel(int numPoints, int numThreads) {
  int pointsInside = 0;
  #pragma omp parallel num_threads(numThreads)
  {
    std::vector<std::pair<double, double>> localPoints = generatePoints(numPoints / numThreads);
    int localPointsInside = 0;

    for (const auto& point : localPoints) {
      if (isInsideCircle(point.first, point.second)) {
        localPointsInside++;
      }
    }

    #pragma omp critical
    {
      pointsInside += localPointsInside;
    }
  }

  return 4.0 * pointsInside / numPoints;
}

/**
 * @brief Generates random points for Monte Carlo Pi calculation
 *
 * This function generates random points in a 2x2 square centered at the origin.
 * The points are used for the Monte Carlo Pi calculation.
 *
 * @param numPoints Number of points to generate
 * @return Vector of points (x,y coordinates)
 */
std::vector<std::pair<double, double>> Calculator::generatePoints(int numPoints) {
  std::vector<std::pair<double, double>> points;
  points.reserve(numPoints);
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(-1.0, 1.0);

  for (int i = 0; i < numPoints; ++i) {
    points.emplace_back(dis(gen), dis(gen));
  }

  return points;
}

/**
 * @brief Calculates the convergence rate of Pi calculation
 *
 * This function analyzes how the Pi approximation converges as more points are processed.
 * It calculates Pi approximations at regular intervals to show the convergence behavior.
 *
 * @param points Vector of points to analyze
 * @return Vector of Pi approximations at different stages
 */
std::vector<double> Calculator::calculateConvergence(const std::vector<std::pair<double, double>> &points) {
  std::vector<double> approximations;
  int pointsInside = 0;

  for (size_t i = 0; i < points.size(); ++i) {
    if (isInsideCircle(points[i].first, points[i].second)) {
      pointsInside++;
    }

    if ((i + 1) % 1000 == 0) {  // Calculate approximation every 1000 points
      approximations.push_back(4.0 * pointsInside / (i + 1));
    }
  }

  return approximations;
}

/**
 * @brief Checks if a point lies inside the unit circle
 *
 * This function determines if a given point (x,y) lies inside the unit circle (radius 1)
 * centered at the origin.
 *
 * @param x X coordinate of the point
 * @param y Y coordinate of the point
 * @return true if point is inside the circle, false otherwise
 */
bool Calculator::isInsideCircle(double x, double y) {
  return (x * x + y * y) <= 1.0;
}
