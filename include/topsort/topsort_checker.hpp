//
// Created by kathy on 07.01.25.
//

#ifndef TOPSORT_CHECKER_HPP
#define TOPSORT_CHECKER_HPP
#include "abstract_algorithm.hpp"
#include "basic_topsort.hpp"


class TopSortChecker : public AbstractAlgorithm {
    public:
        explicit TopSortChecker(Graph& g, std::vector<node> proposedCertificate, int ProposedK ): AbstractAlgorithm(g)
        {
            proposedResult_=proposedCertificate;
            proposedK_ = ProposedK;
        }
        void run() override;
        //virtual bool hasRun() const override{ return hasRun_;}
        bool certificateIsCorrect() const;
        std::map<std::string, std::variant<double, unsigned long>> getStats() const override;

private:
    std::vector<node> proposedResult_;
    bool proposedResultIsCorrect_=false;
    int proposedK_;

};



#endif //TOPSORT_CHECKER_HPP
