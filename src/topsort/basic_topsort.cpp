//
// Created by kathy on 07.01.25.
//

#include "topsort/basic_topsort.hpp"


void BasicTopsort::initialize()
{
    stillExistingNodes_ = graph_.getNumberOfNodes();
    result_ = std::vector<node>(stillExistingNodes_,-1);
    nextZeroBucket_ = std::vector<node>(0);
    incomingDegree_ = std::vector<int>(stillExistingNodes_,0);
    k_=0;
    for (node v : graph_.getNodes())
    {
        incomingDegree_[v] = graph_.degreeIn(v);
        if (incomingDegree_[v]==0)
        {
            nextZeroBucket_.push_back(v);
        }
    }
}


void BasicTopsort::run()
{
    node currentNode;
    int incomingDegree;
    std::vector<node> currentZeroBucket;
    while (stillExistingNodes_!=0)
    {
        k_++;
        // there is a circle within the graph!
        if (nextZeroBucket_.empty())
        {
            //Todo handle circle
            k_=-1;
            result_.clear();
            hasRun_=true;
            return;
        }else{
            std::swap(currentZeroBucket, nextZeroBucket_);
            while (!currentZeroBucket.empty())
            {
                currentNode = currentZeroBucket.back();
                currentZeroBucket.pop_back();
                result_[currentNode]=k_;
                for (edge currentEdge : graph_.outgoingEdges(currentNode))
                {
                    incomingDegree = incomingDegree_[currentEdge.w];
                    if (incomingDegree==1)
                    {
                        nextZeroBucket_.push_back(currentEdge.w);
                    }
                    incomingDegree_[currentEdge.w] = incomingDegree_[currentEdge.w]-1;
                }
                stillExistingNodes_--;
            }
        }
    }
    hasRun_=true;
    return;
}

std::vector<node> BasicTopsort::getResult() const
{
    if (hasRun_)
    {
        return result_;
    }else{
       throw std::runtime_error("There are no results yet: Run the Algorithm First");
        return {};
    }
}
int BasicTopsort::getK() const
{
    if (hasRun_)
    {
        return k_;
    }else
    {
        throw std::runtime_error("There are no results yet: Run the Algorithm First");
        return -1;
    }
}



std::map<std::string, std::variant<double, unsigned long>> BasicTopsort::getStats() const
{
    return {
        {"Hier könnten Ihre Stats stehen", 0.0}
    };
}
