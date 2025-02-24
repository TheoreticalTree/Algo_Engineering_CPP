//
// Created by kathy on 07.01.25.
//

#include "topsort/topsort_checker.hpp"

void TopSortChecker::initialize()
{

}

void TopSortChecker::run()
{
    if (certificate_.empty())
    {
        //run basic topsort to check for circles
        BasicTopsort basic_topsort = BasicTopsort(graph_);
        basic_topsort.run();
        if (basic_topsort.getResult().empty())
        {
            certificateIsCorrect_= true;
        }
    }else
    {
        for (node currentNode : certificate_)
        {
            if (graph_.incomingEdges(currentNode).empty())
            {
                graph_.deleteVertex(currentNode);
            }else{
                //Todo: Errormessages? Do we give back the Conflicts?
                hasRun_ = true;
                return;
            }
        }
        certificateIsCorrect_=true;
    }
    hasRun_=true;
    return;
}

bool TopSortChecker::certificateIsCorrect() const
{
 if (hasRun())
 {
     return certificateIsCorrect_;
 }else{
     std::printf("You need to run the algorithm first");
     return false;
 }
}

std::map<std::string, std::variant<double, unsigned long>> TopSortChecker::getStats() const
{
    return {
            {"Hier könnten Ihre Stats stehen", 0.0}
    };
}
std::vector<node> TopSortChecker::getResult() const
{
    return {};
}


