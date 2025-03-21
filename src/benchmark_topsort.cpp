#include <ctime>
#include <string>
#include <fstream>


#include "graph.hpp"
#include "topsort/basic_topsort.hpp"
#include "topsort/your_topsort.hpp"
#include "io.hpp"


std::string runBenchmarkComparison(std::string file) {
  Graph graph(readDimacsFormat(file));

  std::clock_t t_start, t_end;


  t_start = std::clock();
  
  BasicTopsort algo(graph);
  algo.run();

  t_end = std::clock();

  unsigned int time_ns = (t_end - t_start) * 1000000 / CLOCKS_PER_SEC;


  return file + "," + std::to_string(graph.getNumberOfNodes()) + "," + std::to_string(graph.getNumberOfEdges()) + "," + std::to_string(time_ns) + "\n";
}

std::string runBenchmarkYours(std::string file) {
  Graph graph(readDimacsFormat(file));

  std::clock_t t_start, t_end;

  t_start = std::clock();
  
  YourTopsort algo(graph);
  algo.run();

  t_end = std::clock();

  unsigned int time_ns = (t_end - t_start) * 1000000 / CLOCKS_PER_SEC;


  return file + "," + std::to_string(graph.getNumberOfNodes()) + "," + std::to_string(graph.getNumberOfEdges()) + "," + std::to_string(time_ns) + "\n";
}

int main(int argc, char** argv) {
  std::vector<std::string> instances = {"tiny/TinyValid1.txt", "small/SmallValid1.txt", "medium/MediumValid1.txt", "large/LargeValid1.txt", "large/LargeValid2.txt", "large/LargeValid3.txt", "large/LargeValid4.txt", "large/LargeValid5.txt"};

  std::string output = "Algorithm,Instance,N,M,runtime\n";

  for (auto file : instances) {
    output += "Comparison," + runBenchmarkComparison("data/topsort/" + file);
  }

  
  for (auto file : instances) {
    output += "Yours," + runBenchmarkYours("data/topsort/" + file);
  }

  std::cout << output;

  std::ofstream file("output_topsort.csv");

  file << output;

  file.close();
}

