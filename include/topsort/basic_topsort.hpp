//
// Created by kathy on 07.01.25.
//
#ifndef BASIC_TOPSORT_HPP
#define BASIC_TOPSORT_HPP

#include "base.hpp"
#include "graph.hpp"
#include "abstract_algorithm.hpp"
#include <map>
#include <string>
#include <variant>


class BasicTopsort : public AbstractAlgorithm {
public:
    explicit BasicTopsort(Graph& g): AbstractAlgorithm(g)
    {
    initialize();
    }
    void run() override;
    bool hasRun() const override{ return hasRun_;}

    std::map<std::string, std::variant<double, unsigned long>> getStats() const override;

    //returns an empty vector if graph contains a cycle
    std::vector<node> getResult() const;

protected:
   std::vector<node> result_;
private:
    std::vector<int> incomingEdgeCount_;
    std::vector<node> zeroBucket_;

    void initialize();

};
#endif //BASIC_TOPSORT_HPP
