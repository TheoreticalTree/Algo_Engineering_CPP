//
// Created by kathy on 26.02.25.
//

#ifndef BASIC_MST_HPP
#define BASIC_MST_HPP

#include "base.hpp"
#include "graph.hpp"
#include "abstract_algorithm.hpp"
#include <map>
#include <string>
#include <variant>

class BasicMST : public AbstractAlgorithm{
public:
    explicit BasicMST(Graph& g): AbstractAlgorithm(g)
    {
        initialize();
    }
    void run() override;
    bool hasRun() const override{ return hasRun_;}

    std::map<std::string, std::variant<double, unsigned long>> getStats() const override;

    //returns an empty vector if graph contains a cycle
    std::vector<edge> getResult() const;
    double getMSTValue() const;

private:
    std::vector<edge> result_;
    double mstValue_;
    void initialize();
};

#endif //BASIC_MST_HPP
