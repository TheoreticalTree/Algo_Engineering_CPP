//
// Created by kathy on 26.02.25.
//

#include "mst/mst_checker.hpp"

#include <queue>

void MSTChecker::run()
{
    BasicMST basic_mst(graph_);
    basic_mst.run();
    if (basic_mst.getMSTValue()!=proposedMSTValue_)
    {
        hasRun_=true;
        return;
    }
    //todo alternative just check differing edges?
    for (edge currentEdge : graph_.getEdges())
    {
        if (largerEdgeInMSTExists(currentEdge))
        {
            hasRun_=true;
            return;
        }
    }
    proposedMSTIsCorrect_=true;
    hasRun_=true;
    return;

}

bool MSTChecker::proposedMSTIsCorrect() const
{
    if (hasRun_)
    {
        return proposedMSTIsCorrect_;
    }else
    {
        throw std::runtime_error("No result yet. Run the algorithm first");
    }
}

std::map<std::string, std::variant<double, unsigned long>> MSTChecker::getStats() const
{
    return {
                {"Hier könnten Ihre Stats stehen", 0.0}
    };
}

bool MSTChecker::largerEdgeInMSTExists(edge mstEdge) const
{
    std::queue<node> queue;
    queue.push(mstEdge.v);
    node currentNode = mstEdge.v;
    std::vector<double> largestEdgeWeight = std::vector<double>(graph_.getNumberOfNodes(),mstEdge.weight-1);
    while (!queue.empty() && currentNode!=mstEdge.w)
    {
        queue.pop();
        for (edge incident: proposedMST_.incidentEdges(currentNode))
        {
            queue.push(incident.w);
            largestEdgeWeight[incident.w]= std::max(incident.weight, largestEdgeWeight[incident.v]);
        }
        currentNode =queue.front();
    }
    if (queue.empty()|| largestEdgeWeight[mstEdge.w]>mstEdge.weight)
    {
        return true;
    }else{
        return false;
    }

}





