#ifndef BASIC_MAXCUT_HPP
#define BASIC_MAXCUT_HPP

#include "base.hpp"
#include "graph.hpp"
#include "abstract_algorithm.hpp"
#include <map>
#include <string>
#include <variant>
#include <vector>

class BasicMaxCut : public AbstractAlgorithm{
public:
    explicit BasicMaxCut(Graph& g, unsigned int numLocalSearchRounds = 0): AbstractAlgorithm(g), numLocalSearchRounds_(numLocalSearchRounds)
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

    unsigned int numLocalSearchRounds_ = 0;
};

#endif //BASIC_MAXCUT_HPP
