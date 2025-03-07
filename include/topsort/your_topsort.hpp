
#ifndef YOUR_TOPSORT_HPP
#define YOUR_TOPSORT_HPP

#include "base.hpp"
#include "graph.hpp"
#include "abstract_algorithm.hpp"
#include <map>
#include <string>
#include <variant>


class YourTopsort : public AbstractAlgorithm {
public:
    explicit YourTopsort(Graph& g) : AbstractAlgorithm(g)
    {
      
    }
    void run() override;
    bool hasRun() const override{ return hasRun_;}

    std::map<std::string, std::variant<double, unsigned long>> getStats() const override;

    //returns an empty vector if graph contains a cycle
    std::vector<node> getResult() const;
    int getK() const;

private:
  // TODO Feel free to add your own cariables etc. here
};
#endif //YOUR_TOPSORT_HPP
