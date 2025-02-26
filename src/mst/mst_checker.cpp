//
// Created by kathy on 26.02.25.
//

#include "mst/mst_checker.hpp"

void MSTChecker::run()
{
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
