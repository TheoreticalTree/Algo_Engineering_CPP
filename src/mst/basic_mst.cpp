//
// Created by kathy on 26.02.25.
//

#include "mst/basic_mst.hpp"

#include <algorithm>
#include <numeric>

void BasicMST::initialize()
{
    mstValue_ = 0;
    result_ = std::vector<edge>(0);
    sizeOfSubtree_ = std::vector<u_int32_t>(graph_.getNumberOfNodes(),1);
    parent_ =std::vector<node>(graph_.getNumberOfNodes());
    std::iota(parent_.begin(),parent_.end(),0);
    sortedEdges_ = std::vector<edge>();
    for (edge currentEdge : graph_.getEdges())
    {
        sortedEdges_.push_back(currentEdge);
    }
    std::sort(sortedEdges_.begin(), sortedEdges_.end(), firstEdgeWeightIsLargerThanSecond);
}

bool BasicMST::firstEdgeWeightIsLargerThanSecond(edge& first, edge& second)
{
    if (first.weight>second.weight)
    {
        return true;
    }else
        return false;
}


node BasicMST::findRoot(node v)
{
    node parent = v;
    std::vector<node> ancestors = {v};
    while (parent!=parent_[parent])
    {
        parent = parent_[parent];
        ancestors.push_back(parent);
    }
    setParentToRoot(parent, ancestors);
    return parent;
}

void BasicMST::setParentToRoot(node root, std::vector<node>& ancestors)
{
    for (node v: ancestors)
    {
        parent_[v]=root;
    }
}

void BasicMST::run()
{
    edge currentEdge;
    node vRoot;
    node wRoot;
    //todo: alternatively just iterate through edges? would that be faster?
    while (result_.size()<graph_.getNumberOfNodes()&&!sortedEdges_.empty())
    {
        currentEdge= sortedEdges_.back();
        sortedEdges_.pop_back();
        vRoot = findRoot(parent_[currentEdge.v]);
        wRoot = findRoot(parent_[currentEdge.w]);
        if (vRoot!=wRoot)
        {
            result_.push_back(currentEdge);
            mstValue_+=currentEdge.weight;
            if (sizeOfSubtree_[wRoot]>sizeOfSubtree_[vRoot])
            {
                sizeOfSubtree_[wRoot]+=sizeOfSubtree_[vRoot];
                parent_[vRoot]=wRoot;
            }else{
                sizeOfSubtree_[vRoot]+=sizeOfSubtree_[wRoot];
                parent_[wRoot]=vRoot;
            }
        }
    }
    hasRun_=true;
    return;
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
