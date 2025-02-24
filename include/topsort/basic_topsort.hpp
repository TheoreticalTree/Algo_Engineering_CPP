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
    explicit BasicTopsort(Graph &g): AbstractAlgorithm(g)
    {
    initialize();
    }
    void initialize();
    virtual void run() override;
    virtual bool hasRun() const override{ return hasRun_;}

    //returns an empty vector if graph contains a cycle
    virtual std::vector<node> getResult() const override;
    virtual std::map<std::string, std::variant<double, unsigned long>> getStats() const override;

protected:
   std::vector<node> result_;
private:
    std::vector<int> incomingEdgeCount_;
    std::vector<node> zeroBucket_;

};
#endif //BASIC_TOPSORT_HPP
