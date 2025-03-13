#ifndef YOUR_MAXCUT_HPP
#define YOUR_MAXCUT_HPP

#include "base.hpp"
#include "graph.hpp"
#include "abstract_algorithm.hpp"
#include <map>
#include <string>
#include <variant>
#include <vector>

class YourMaxCut : public AbstractAlgorithm{
public:
    explicit YourMaxCut(Graph& g): AbstractAlgorithm(g)
    {
    }
    void run() override;
    bool hasRun() const override{ return hasRun_;}

    std::map<std::string, std::variant<double, unsigned long>> getStats() const override;

    /**
     * @returns a reference to a vector of bools with results[v] == False being one side of the partition and results[v] == True the other
     */
    const std::vector<bool>& getResult() const;

    double getMaxCutValue() const;


private:
    std::vector<bool> result_;
    double MCValue_ = 0;

};

#endif //Your_MAXCUT_HPP
