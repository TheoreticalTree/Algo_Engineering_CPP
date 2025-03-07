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
    double mstValue_=0;
    std::vector<node> parent_;
    std::vector<edge> sortedEdges_;
    //the number is only correct for the roots, because im lazy
    std::vector<u_int32_t> sizeOfSubtree_;
    node findRoot(node v);
    void setParentToRoot(node root, std::vector<node>& ancestors);
    static bool cmp(edge& first, edge& second);

    void initialize();
};

#endif //BASIC_MST_HPP
