//
// Created by kathy on 26.02.25.
//

#include "mst/basic_mst.hpp"


void BasicMST::initialize()
{
    mstValue_ = 0;
    result_ = std::vector<edge>(0);
}

void BasicMST::run()
{
}

double BasicMST::getMSTValue() const
{
    if (hasRun_)
    {
        return mstValue_;
    }
    else
    {
        throw std::runtime_error("No results yet. Run algorithm first.");
    }
}

std::vector<edge> BasicMST::getResult() const
{
    if (hasRun_)
    {
        return result_;
    }
    else
    {
        throw std::runtime_error("No results yet. Run algorithm first.");
    }
}

std::map<std::string, std::variant<double, unsigned long>> BasicMST::getStats() const
{
    return {
        {"Hier könnten Ihre Stats stehen", 0.0}
    };
}
