//
// Created by michaelk on 05.01.25.
//

#include <vector>
#include <string>
#include <iterator>
#include <cstddef>

#include <iostream>

#include "base.hpp"

#ifndef ALGO_ENGINEERING_CPP_GRAPH_HPP
#define ALGO_ENGINEERING_CPP_GRAPH_HPP

class Graph {
public:
    /**
     * Reads a graph from a file using the DIMACS format
     * @param fileName name of the input file
     * @param directed true if the graph is directed, false otherwise (default false)
     * @param weighted true if the graph is weighted, false otherwise (default false)
     */
    explicit Graph(std::string fileName, bool directed = false, bool weighted = false);

    /**
     * Constructs a graph from an existing edge list.
     * @param edges vector of edges (with weights) to construct graph from. For unweighted graphs the weight is ignored
     * @param directed true if the graph is directed, false otherwise (default false)
     * @param weighted true if the graph is weighted, false otherwise (default false)
     */
    explicit Graph(std::vector<edge> edges, bool directed = false, bool weighted = false);

    /**
     * Builds a graph with n vertices and no edges
     * @param edges vector of edges (with weights) to construct graph from. For unweighted graphs the weight is ignored
     * @param directed true if the graph is directed, false otherwise (default false)
     * @param weighted true if the graph is weighted, false otherwise (default false)
     */
    explicit Graph(count n,  bool directed = false, bool weighted = false);

    //! Returns if the graph is marked as weighted
    [[nodiscard]] bool isWeighted() const
    {
        return weighted;
    }

    //! Returns if the graph is marked as directed
    [[nodiscard]] bool isDirected() const
    {
        return directed;
    }

    /**
     * Adds an edge to the graph. If such an edge already exists an error is thrown in debug mode, in release things may just go bad
     * If the edge uses a nodeID that does not exist (too high/was deleted) an error is thrown
     * @param e the edge
     */
    void addEdge(edge e);

    /**
     * Deletes the edge connecting v to w
     * @param v
     * @param w
     */
    void deleteEdge(node v, node w);

    /**
     * Checks if the edge exists
     * @param v
     * @param w
     * @return true of the edge exists, false otherwise
     */
    [[nodiscard]] bool hasEdge(node v, node w) const;

    /**
     * Adds a new vertex
     * @return the id of the new vertex added
     */
    node addVertex();

    /**
     * Deletes a vertex
     * @param v
     */
    void deleteVertex(node v);

    /**
     * Returns of vertex v exists
     * @param v
     * @return true iff v exists
     */
    bool hasVertex(node v);

    //! Number of edges (x, v), in undirected case equal to degree
    [[nodiscard]] count degreeIn(node v) const;

    //! Only for undirected graphs: Returns iterable over incident edges
    [[nodiscard]] const std::vector<edge>& incidentEdges(node v) const;

    //! Number of edges (v, x), in undirected case equal to degree
    [[nodiscard]] count degreeOut(node v) const;

    //!
    [[nodiscard]] const std::vector<edge>& outgoingEdges(node v) const;

    [[nodiscard]] count degree(node v) const;

    [[nodiscard]] const std::vector<edge>& incomingEdges(node v) const;

    /**
     *
     * @return current number of edges
     */
    [[nodiscard]] count getNumberOfEdges() const;

    /**
     *
     * @return currend number of nodes
     */
    [[nodiscard]] count getNumberOfNodes() const;

    struct EdgeIterator {
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type        = edge;
        using pointer           = edge*;
        using reference         = edge&;

        EdgeIterator(Graph& g, node pv, count ppos) : g(g), v(pv), pos(ppos) {
            while (v < g.aboveMaxNodeID && g.edgesOut[v].empty()) {
                v++;
            }
        };

        EdgeIterator begin() {
            return {g, 0, 0};
        }

        EdgeIterator end() {
            return {g, g.aboveMaxNodeID, 0};
        }

        reference operator*() const {
            return g.edgesOut[v][pos];
        }

        pointer operator->() {
            return &g.edgesOut[v][pos];
        }

        EdgeIterator& operator++() {
            if (g.directed) {
                do {
                    if (pos == g.edgesOut[v].size()) {
                        pos = 0;
                        v++;
                    } else {
                        pos++;
                    }

                } while (v < g.aboveMaxNodeID && pos == g.edgesOut[v].size());
            } else {
                do {
                    if (pos == g.edgesOut[v].size()) {
                        pos = 0;
                        v++;
                    } else {
                        pos++;
                    }

                } while ((v < g.aboveMaxNodeID) && ((pos == g.edgesOut[v].size()) || (g.edgesOut[v][pos].w < v)));
            }

            return *this;
        }

        EdgeIterator operator++(int) {
            EdgeIterator tmp = *this;

            pos++;
            if (pos == g.edgesOut[v].size()) {
                pos = 0;
                do {
                    v++;
                } while (v < g.aboveMaxNodeID && !g.alive[v]);
            }

            return tmp;
        }

        friend bool operator==(const EdgeIterator& a, const EdgeIterator& b) {
            return (&a.g == &b.g) && (a.v == b.v) && (a.pos == b.pos);
        }

        friend bool operator!=(const EdgeIterator& a, const EdgeIterator& b) {
            return !((&a.g == &b.g) && (a.v == b.v) && (a.pos == b.pos));
        }

    private:
        Graph& g;

        node v;
        count pos;
    };

    struct NodeIterator {
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type        = node;
        using pointer           = node*;
        using reference         = node&;

        NodeIterator(Graph& g, node pv) : g(g), v(pv) {
            while (v < g.aboveMaxNodeID && !g.alive[v]) {
                v++;
            }
        };

        NodeIterator begin() {
            return {g, 0};
        }

        NodeIterator end() {
            return {g, g.aboveMaxNodeID};
        }

        value_type operator*() const {
            return v;
        }

        pointer operator->() {
            return &v;
        }

        NodeIterator& operator++() {
            do {
                v++;
            } while (v < g.aboveMaxNodeID && !g.alive[v]);

            return *this;
        }

        NodeIterator operator++(int) {
            NodeIterator tmp = *this;

            do {
                v++;
            } while (v < g.aboveMaxNodeID && !g.alive[v]);

            return tmp;
        }

        friend bool operator==(const NodeIterator& a, const NodeIterator& b) {
            return (&a.g == &b.g) && (a.v == b.v);
        }

        friend bool operator!=(const NodeIterator& a, const NodeIterator& b) {
            return !((&a.g == &b.g) && (a.v == b.v));
        }

    private:
        Graph& g;

        node v;
    };

    EdgeIterator getEdges();

    NodeIterator getNodes();


protected:
    bool directed, weighted;

    //! Number of current nodes
    count n=0;
    //! Highest NodeID currently in use plus 1
    count aboveMaxNodeID = 0;
    //! Number of edges
    count m = 0;

    //! If nodes are deleted this stores "gaps" in the nodeIDs
    std::vector<node> openIDSlots;


    //! Stores outgoing edges of a vertex (all edges in undirected graphs) and the position of their other side
    std::vector<std::vector<edge>> edgesOut;
    std::vector<std::vector<count>> backPosOut;
    //! Stores incoming edges (only in directed graphs)
    std::vector<std::vector<edge>> edgesIn;
    std::vector<std::vector<count>> backPosIn;

    //! Stores if a vertex still exists or if it has been deleted
    std::vector<bool> alive;
};

#endif //ALGO_ENGINEERING_CPP_GRAPH_HPP
