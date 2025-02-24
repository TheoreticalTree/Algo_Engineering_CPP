//
// Created by kathy on 07.01.25.
//

#ifndef TOPSORT_CHECKER_HPP
#define TOPSORT_CHECKER_HPP
#include "abstract_algorithm.hpp"
#include "basic_topsort.hpp"


class TopSortChecker : public AbstractAlgorithm {
    public:
        explicit TopSortChecker(Graph& g, std::vector<node> &certificate): AbstractAlgorithm(g)
        {
            certificate_=certificate;
            initialize();
        }
        void run() override;
        //virtual bool hasRun() const override{ return hasRun_;}
        bool certificateIsCorrect() const;
        std::map<std::string, std::variant<double, unsigned long>> getStats() const override;

private:
    std::vector<node> certificate_;
    bool certificateIsCorrect_=false;


    void initialize();

};



#endif //TOPSORT_CHECKER_HPP
