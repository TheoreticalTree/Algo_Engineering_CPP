//
// Created by kathy on 07.01.25.
//

#ifndef ABSTRACT_ALGORITHM_HPP
#define ABSTRACT_ALGORITHM_HPP

#include "graph.hpp"
#include "base.hpp"
#include <map>
#include <variant>

class AbstractAlgorithm
{
public:
    explicit AbstractAlgorithm(Graph& g ):  graph_(g)
    {

    };

    virtual void run() = 0;

    virtual bool hasRun() const { return hasRun_; }

    virtual std::vector<node> getResult() const;

    virtual std::map<std::string, std::variant<double, unsigned long>> getStats() const;

protected:
    Graph& graph_;
    bool hasRun_ = false;
};

#endif //ABSTRACT_ALGORITHM_HPP
