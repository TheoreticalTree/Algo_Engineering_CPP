
#ifndef YOUR_TOPSORT_HPP
#define YOUR_TOPSORT_HPP

#include "base.hpp"
#include "graph.hpp"
#include "abstract_algorithm.hpp"
#include <map>
#include <string>
#include <variant>


class YourTopsort : public AbstractAlgorithm {
public:
    explicit YourTopsort(Graph& g) : AbstractAlgorithm(g)
    {
      
    }
    void run() override;

    /**
     * Run the algorithm
     * @return
     */
    bool hasRun() const override{ return hasRun_;}

    std::map<std::string, std::variant<double, unsigned long>> getStats() const override;

    /**
     * This function should throw an exception if called before the algorithm is run
     * @returna vector giving compressed topsort values for graph (starting at 1), empty vector if no topsort exists
     */
    std::vector<node> getResult() const;

    /**
     *  Returns the smallest value k such that the instance has a compressed topsort with k steps
     * This function shopuld throw an error if called before the algorithm is run
     * @return The smallest possible k, -1 of none exists
     */
    int getK() const;

private:
  // TODO Feel free to add your own cariables etc. here
};
#endif //YOUR_TOPSORT_HPP
