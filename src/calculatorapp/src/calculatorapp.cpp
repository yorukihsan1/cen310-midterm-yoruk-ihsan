/**
 * @file calculatorapp.cpp
 * @brief Monte Carlo Pi calculation and visualization application
 *
 * This application demonstrates the use of the Monte Carlo method for calculating Pi.
 * It includes both sequential and parallel implementations, and provides performance
 * analysis and visualization of the results.
 *
 * The application performs the following tasks:
 * 1. Sequential Pi calculation with different point counts
 * 2. Parallel Pi calculation with different thread counts
 * 3. Convergence analysis of Pi approximation
 * 4. Performance analysis and speedup calculation
 * 5. Visualization of results through CSV files
 */

#include <iostream>
#include <iomanip>
#include <chrono>
#include <vector>
#include <fstream>
#include <string>
#include <omp.h>
#include <cmath>
#include "../../calculator/header/calculator.h"

#ifndef M_PI
  #define M_PI 3.14159265358979323846
#endif

using namespace Coruh::Calculator;

/**
 * @brief Structure to hold performance results
 *
 * This structure stores the results of a performance test, including
 * the number of points, number of threads, calculated Pi value, error,
 * and execution time.
 */
struct PerformanceResult {
  int numPoints;      ///< Number of points used in the calculation
  int numThreads;     ///< Number of threads used (1 for sequential)
  double pi;          ///< Calculated Pi value
  double error;       ///< Error percentage compared to actual Pi
  double time;        ///< Execution time in seconds
};

/**
 * @brief Prints the results of a Pi calculation
 *
 * This function prints the calculated Pi value, actual Pi value,
 * error percentage, and execution time.
 *
 * @param pi Calculated Pi value
 * @param actualPi Actual Pi value (M_PI)
 * @param error Error percentage
 * @param time Execution time in seconds
 */
void printResults(double pi, double actualPi, double error, double time) {
  std::cout << std::fixed << std::setprecision(10);
  std::cout << "Calculated Pi: " << pi << std::endl;
  std::cout << "Actual Pi:     " << actualPi << std::endl;
  std::cout << "Error:         " << error << "%" << std::endl;
  std::cout << "Time:          " << time << " seconds" << std::endl;
}

/**
 * @brief Runs a sequential Pi calculation test
 *
 * This function performs a sequential Pi calculation with the specified
 * number of points and measures the execution time.
 *
 * @param numPoints Number of points to use in the calculation
 * @return PerformanceResult containing the test results
 */
PerformanceResult runSequentialTest(int numPoints) {
  std::cout << "\nRunning Sequential Test..." << std::endl;
  auto start = std::chrono::high_resolution_clock::now();
  double pi = Calculator::calculatePiSequential(numPoints);
  auto end = std::chrono::high_resolution_clock::now();
  double time = std::chrono::duration<double>(end - start).count();
  double error = std::abs(pi - M_PI) / M_PI * 100;
  printResults(pi, M_PI, error, time);
  return {numPoints, 1, pi, error, time};
}

/**
 * @brief Runs a parallel Pi calculation test
 *
 * This function performs a parallel Pi calculation with the specified
 * number of points and threads, and measures the execution time.
 *
 * @param numPoints Number of points to use in the calculation
 * @param numThreads Number of threads to use
 * @return PerformanceResult containing the test results
 */
PerformanceResult runParallelTest(int numPoints, int numThreads) {
  std::cout << "\nRunning Parallel Test with " << numThreads << " threads..." << std::endl;
  auto start = std::chrono::high_resolution_clock::now();
  double pi = Calculator::calculatePiParallel(numPoints, numThreads);
  auto end = std::chrono::high_resolution_clock::now();
  double time = std::chrono::duration<double>(end - start).count();
  double error = std::abs(pi - M_PI) / M_PI * 100;
  printResults(pi, M_PI, error, time);
  return {numPoints, numThreads, pi, error, time};
}

/**
 * @brief Runs a convergence test for Pi calculation
 *
 * This function analyzes how the Pi approximation converges as more
 * points are processed. It calculates Pi approximations at regular
 * intervals and saves the results to a CSV file for visualization.
 *
 * @param numPoints Number of points to use in the calculation
 */
void runConvergenceTest(int numPoints) {
  std::cout << "\nRunning Convergence Test..." << std::endl;
  auto points = Calculator::generatePoints(numPoints);
  auto convergence = Calculator::calculateConvergence(points);
  std::cout << "Convergence points:" << std::endl;

  for (size_t i = 0; i < convergence.size(); ++i) {
    std::cout << "Points " << (i + 1) * 1000 << ": " << convergence[i] << std::endl;
  }

  // Save convergence data to file for plotting
  std::ofstream outFile("convergence_data.csv");
  outFile << "Points,Pi_Approximation" << std::endl;

  for (size_t i = 0; i < convergence.size(); ++i) {
    outFile << (i + 1) * 1000 << "," << convergence[i] << std::endl;
  }

  outFile.close();
  std::cout << "Convergence data saved to convergence_data.csv" << std::endl;
}

/**
 * @brief Runs a comprehensive performance analysis
 *
 * This function performs a comprehensive performance analysis by running
 * both sequential and parallel tests with different point counts and
 * thread counts. It calculates the speedup for each configuration and
 * saves the results to a CSV file for visualization.
 */
void runPerformanceAnalysis() {
  std::cout << "\nRunning Performance Analysis..." << std::endl;
  std::vector<int> pointCounts = {100000, 500000, 1000000, 5000000};
  std::vector<int> threadCounts = {1, 2, 4, 8, 16};
  std::vector<PerformanceResult> results;

  // Sequential tests
  for (int points : pointCounts) {
    results.push_back(runSequentialTest(points));
  }

  // Parallel tests
  for (int points : pointCounts) {
    for (int threads : threadCounts) {
      if (threads > 1) {  // Skip thread count 1 as it's already done in sequential
        results.push_back(runParallelTest(points, threads));
      }
    }
  }

  // Save performance data to file for plotting
  std::ofstream outFile("performance_data.csv");
  outFile << "Points,Threads,Pi,Error,Time" << std::endl;

  for (const auto& result : results) {
    outFile << result.numPoints << ","
            << result.numThreads << ","
            << result.pi << ","
            << result.error << ","
            << result.time << std::endl;
  }

  outFile.close();
  std::cout << "Performance data saved to performance_data.csv" << std::endl;
  // Calculate speedup
  std::cout << "\nSpeedup Analysis:" << std::endl;
  std::cout << "Points\tThreads\tSpeedup" << std::endl;

  for (int points : pointCounts) {
    double sequentialTime = 0;

    for (const auto& result : results) {
      if (result.numPoints == points && result.numThreads == 1) {
        sequentialTime = result.time;
        break;
      }
    }

    for (int threads : threadCounts) {
      if (threads > 1) {
        double parallelTime = 0;

        for (const auto& result : results) {
          if (result.numPoints == points && result.numThreads == threads) {
            parallelTime = result.time;
            break;
          }
        }

        double speedup = sequentialTime / parallelTime;
        std::cout << points << "\t" << threads << "\t" << speedup << std::endl;
      }
    }
  }
}

/**
 * @brief Main function
 *
 * This is the entry point of the application. It runs the sequential test,
 * parallel test, convergence test, and performance analysis.
 *
 * @return 0 on successful execution
 */
int main() {
  const int numPoints = 1000000;
  const int numThreads = 4;
  std::cout << "Monte Carlo Pi Calculation" << std::endl;
  std::cout << "=========================" << std::endl;
  // Sequential test
  runSequentialTest(numPoints);
  // Parallel test
  runParallelTest(numPoints, numThreads);
  // Convergence test
  runConvergenceTest(10000);
  // Performance analysis
  runPerformanceAnalysis();
  return 0;
}
