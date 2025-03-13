#include "maxcut/basic_maxcut.hpp"

#include <vector>


void BasicMaxCut::run()
{
    hasRun_ = true;
    
    unsigned int n = graph_.getNumberOfNodes();
    std::vector<double> gainFromA(n, 0.0);
    result_.resize(n, false);

    for (node v: graph_.getNodes()) {
        if (gainFromA[v] > 0) {
            result_[v] = true;
           
            for (edge e : graph_.incidentEdges(v)) {
                gainFromA[e.w] -= e.weight;
            }
        }
        else {
            for (edge e : graph_.incidentEdges(v)) {
                gainFromA[e.w] += e.weight;
            }
        }
    }

    for (edge e : graph_.getEdges()) {
        if (result_[e.v] != result_[e.w]) {
            MCValue_ += e.weight;
        }
    }

    bool improvementOccured;

    for (unsigned int i = 0; i < numLocalSearchRounds_; i++) {
        improvementOccured = false;

        for (node v: graph_.getNodes()) {
            // Check if flipping the node yields an improvement to the maxcut value
            if ((gainFromA[v] != 0.0) && (result_[v] != (gainFromA[v] > 0.0))) {
                improvementOccured = true;
                
                result_[v] = !result_[v];

                if (result_[v]) {
                    MCValue_ += gainFromA[v];
                }
                else {
                    MCValue_ -= gainFromA[v];
                }

                if (result_[v]) {
                    for (edge e : graph_.incidentEdges(v)) {
                        gainFromA[e.w] -= 2.0 * e.weight;
                    }
                }
                else {
                    for (edge e : graph_.incidentEdges(v)) {
                        gainFromA[e.w] += 2.0 * e.weight;
                    }
                }
            }
        }

        if (!improvementOccured)
            break;
    }
}

double BasicMaxCut::getMaxCutValue() const
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

const std::vector<bool>& BasicMaxCut::getResult() const
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

std::map<std::string, std::variant<double, unsigned long>> BasicMaxCut::getStats() const
{
    return {
        {"Hier könnten Ihre Stats stehen", 0.0}
    };
}
