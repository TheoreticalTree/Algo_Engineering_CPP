//
// Created by kathy on 07.01.25.
//

#include "topsort/basic_topsort.hpp"


void BasicTopsort::initialize()
{
    result_ = std::vector<node>(0);
    zeroBucket_ = std::vector<node>(0);
    incomingEdgeCount_ = std::vector<int>(graph_.getNumberOfNodes());
    for (node v : graph_.getNodes())
    {
        incomingEdgeCount_[v] = graph_.incomingEdges(v).size();
        if (incomingEdgeCount_[v]==0)
        {
            zeroBucket_.push_back(v);
        }
    }
}


void BasicTopsort::run()
{
    node currentNode;
    int incomingDegree;
    while (graph_.getNumberOfNodes()!=0)
    {
        // there is a circle within the graph!
        if (zeroBucket_.empty())
        {
            //Todo handle circle
            result_.clear();
            return;
        }else{
            currentNode = zeroBucket_.back();
            zeroBucket_.pop_back();
            result_.push_back(currentNode);
            for (edge currentEdge : graph_.outgoingEdges(currentNode))
            {
                incomingDegree = incomingEdgeCount_[currentEdge.w];
                if (incomingDegree==1)
                {
                    zeroBucket_.push_back(currentEdge.w);
                }
                incomingEdgeCount_[currentEdge.w] = incomingEdgeCount_[currentEdge.w]-1;
            }
            graph_.deleteVertex(currentNode);
        }
    }
    return;
}

std::vector<node> BasicTopsort::getResult() const
{
    if (hasRun_)
    {
        return result_;
    }else{
        std::printf("There are no results yet: Start the Algorithm First");
        return {};
    }
}


std::map<std::string, std::variant<double, unsigned long>> BasicTopsort::getStats() const
{
    return {
        {"Hier könnten Ihre Stats stehen", 0.0}
    };
}
