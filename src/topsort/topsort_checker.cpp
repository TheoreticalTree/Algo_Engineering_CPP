//
// Created by kathy on 07.01.25.
//

#include "topsort/topsort_checker.hpp"

void TopSortChecker::run()
{
    if (proposedResult_.empty()||proposedK_==-1)
    {
        if (proposedResult_.empty()&&proposedK_==-1)
        {
            //run basic topsort to check for circles
            BasicTopsort basic_topsort = BasicTopsort(graph_);
            basic_topsort.run();
            if (basic_topsort.getK()==-1)
            {
                proposedResultIsCorrect_= true;
            }
        }
    }else{
        for (edge currentEdge : graph_.getEdges())
        {
            if (proposedResult_[currentEdge.v]>= proposedResult_[currentEdge.w])
            {
                hasRun_=true;
                return;
            }
        }
        BasicTopsort basic_topsort = BasicTopsort(graph_);
        basic_topsort.run();
        if (basic_topsort.getK()==proposedK_)
        {
            proposedResultIsCorrect_=true;
        }
    }
    hasRun_=true;
    return;
}

bool TopSortChecker::certificateIsCorrect() const
{
 if (hasRun())
 {
     return proposedResultIsCorrect_;
 }else{
     throw std::runtime_error("You need to run the algorithm first");
 }
}

std::map<std::string, std::variant<double, unsigned long>> TopSortChecker::getStats() const
{
    return {
            {"Hier könnten Ihre Stats stehen", 0.0}
    };
}


