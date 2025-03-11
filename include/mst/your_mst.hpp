
#ifndef YOUR_MST_HPP
#define YOUR_MST_HPP

#include "base.hpp"
#include "graph.hpp"
#include "abstract_algorithm.hpp"
#include <map>
#include <string>
#include <variant>

class YourMST : public AbstractAlgorithm{
public:
    explicit YourMST(Graph& g): AbstractAlgorithm(g)
    {
        
    }
    void run() override;
    bool hasRun() const override{ return hasRun_;}

    std::map<std::string, std::variant<double, unsigned long>> getStats() const override;

    /**
     * @return a vector of the edges forming a minimum spanning tree
     */
    std::vector<edge> getResult() const;

    double getMSTValue() const;

private:
  // TODO Feel free to add your own code here

};

#endif //BASIC_MST_HPP
