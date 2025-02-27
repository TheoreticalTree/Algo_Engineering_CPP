//
// Created by kathy on 26.02.25.
//

#ifndef MST_CHECKER_HPP
#define MST_CHECKER_HPP

#include "abstract_algorithm.hpp"
#include "basic_mst.hpp"

class MSTChecker : public AbstractAlgorithm
{
public:
    explicit MSTChecker(Graph& g, std::vector<edge>& proposedMST, double proposedMSTValue): AbstractAlgorithm(g),
        proposedMST_(proposedMST)
    {
        proposedMSTValue_ = proposedMSTValue;
    }
    void run() override;
    //virtual bool hasRun() const override{ return hasRun_;}
    bool proposedMSTIsCorrect() const;
    std::map<std::string, std::variant<double, unsigned long>> getStats() const override;

private:

    Graph proposedMST_;
    bool proposedMSTIsCorrect_ = false;
    double proposedMSTValue_;
    bool largerEdgeInMSTExists(edge mstEdge) const;
};


#endif //MST_CHECKER_HPP
