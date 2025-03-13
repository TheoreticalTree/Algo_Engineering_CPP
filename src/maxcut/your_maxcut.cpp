#include "maxcut/your_maxcut.hpp"

#include <vector>


void YourMaxCut::run()
{

}

double YourMaxCut::getMaxCutValue() const
{
    if (hasRun_)
    {
        return MCValue_;
    }
    else
    {
        throw std::runtime_error("No results yet. Run algorithm first.");
    }
}

const std::vector<bool>& YourMaxCut::getResult() const
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

std::map<std::string, std::variant<double, unsigned long>> YourMaxCut::getStats() const
{
    return {
        {"Hier könnten Ihre Stats stehen", 0.0}
    };
}
