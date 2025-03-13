#include <ctime>
#include <string>
#include <fstream>
#include <vector>


#include "graph.hpp"
#include "maxcut/basic_maxcut.hpp"
#include "maxcut/your_maxcut.hpp"
#include "io.hpp"


std::string runBenchmarkComparison(std::string file, int localSearchIterations) {
  Graph graph(readDimacsFormat(file));

  std::clock_t t_start, t_end;


  t_start = std::clock();
  
  BasicMaxCut algo(graph, localSearchIterations);
  algo.run();

  t_end = std::clock();

  unsigned int time_ns = (t_end - t_start) * 1000000 / CLOCKS_PER_SEC;

  return file + "," + std::to_string(graph.getNumberOfNodes()) + "," + std::to_string(graph.getNumberOfEdges()) + "," + std::to_string(time_ns) + "," + std::to_string(algo.getMaxCutValue()) + "\n";
}

std::string runBenchmarkYours(std::string file) {
  Graph graph(readDimacsFormat(file));

  std::clock_t t_start, t_end;

  t_start = std::clock();
  
  YourMaxCut algo(graph);
  algo.run();

  t_end = std::clock();

  unsigned int time_ns = (t_end - t_start) * 1000000 / CLOCKS_PER_SEC;

  return file + "," + std::to_string(graph.getNumberOfNodes()) + "," + std::to_string(graph.getNumberOfEdges()) + "," + std::to_string(time_ns) + "," + std::to_string(algo.getMaxCutValue()) + "\n";
}

int main(int argc, char** argv) {
  std::vector<std::string> instances = {"tiny/TinyValid1.txt", "small/SmallValid1.txt", "medium/MediumValid1.txt", "large/LargeValid1.txt", "large/LargeValid2.txt", "large/LargeValid3.txt", "large/LargeValid4.txt", "large/LargeValid5.txt"};

  std::string output = "Algorithm,Instance,N,M,runtime,quality\n";

  for (auto file : instances) {
    output += "Comparison[0]," + runBenchmarkComparison("data/maxcut/" + file, 0);
  }

  for (auto file : instances) {
    output += "Comparison[1]," + runBenchmarkComparison("data/maxcut/" + file, 1);
  }

  for (auto file : instances) {
    output += "Comparison[10]," + runBenchmarkComparison("data/maxcut/" + file, 10);
  }

  
  for (auto file : instances) {
    output += "Yours," + runBenchmarkYours("data/maxcut/" + file);
  }

  std::cout << output;

  std::ofstream file("output_maxcut.csv");

  file << output;

  file.close();
}

