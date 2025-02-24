//
// Created by michaelk on 05.01.25.
//

#include <graph.hpp>
#include <stdexcept>
#include <cassert>

Graph::Graph(std::string fileName, bool directed, bool weighted) : directed(directed), weighted(weighted) {
    // TODO: implement
}

Graph::Graph(std::vector<edge> edges, bool directed, bool weighted) : directed(directed), weighted(weighted) {
    for (edge e : edges) {
        aboveMaxNodeID = std::max(std::max(aboveMaxNodeID, e.v), e.w);
    }

    aboveMaxNodeID++;

    n = aboveMaxNodeID;

    edgesOut.resize(n);
    backPosOut.resize(n);
    alive.resize(n, true);

    if (directed) {
        edgesIn.resize(n);
        backPosIn.resize(n);
    }

    for (edge e : edges) {
        addEdge(e);
    }
}

Graph::Graph(count n, bool directed, bool weighted) : directed(directed), weighted(weighted) {
    aboveMaxNodeID = n;

    edgesOut.resize(n);
    backPosOut.resize(n);
    alive.resize(n, true);

    if (directed) {
        edgesIn.resize(n);
        backPosIn.resize(n);
    }
}

void Graph::addEdge(edge e) {
#ifndef NDEBUG // This code only runs in debug mode
    if (e.v > aboveMaxNodeID || e.w > aboveMaxNodeID || !alive[e.v] || !alive[e.w]) throw std::runtime_error("You inserted an edge for which one of the endpoints does not exist");
    for (edge arc : edgesOut[e.v]) {
        if (arc.w == e.w) {
            throw std::runtime_error("You inserted an edge that already exists");
        }
    }
#endif
    m++;

    if (directed) {
        edgesOut[e.v].emplace_back(e);
        edgesIn[e.w].emplace_back(e);
        backPosOut[e.v].emplace_back(edgesIn[e.w].size() - 1);
        backPosIn[e.w].emplace_back(edgesOut[e.v].size() - 1);
    } else {
        edgesOut[e.v].emplace_back(e);
        edgesOut[e.w].emplace_back(edge {e.w, e.v, e.weight});
        backPosOut[e.v].emplace_back(edgesOut[e.w].size() - 1);
        backPosOut[e.w].emplace_back(edgesOut[e.v].size() - 1);
    }
}

void Graph::deleteEdge(node v, node w) {
    for (count i = 0; i < edgesOut[v].size(); i++) {
        if (edgesOut[v][i].w == w) {
            m--;

            if (directed) {
                // We delete the edge and move the last edge in the spot there
                count backPos = backPosOut[v][i];
                edgesOut[v][i] = edgesOut[v].back();
                backPosOut[v][i] = backPosOut[v].back();
                backPosIn[edgesOut[v][i].w][backPosOut[v][i]] = i;

                edgesIn[w][backPos] = edgesIn[w].back();
                backPosIn[w][backPos] = backPosIn[w].back();
                backPosOut[edgesIn[w][backPos].v][backPosIn[w][backPos]] = backPos;

                edgesOut[v].pop_back();
                backPosOut[v].pop_back();
                edgesIn[w].pop_back();
                backPosIn[w].pop_back();
            } else {
                count backPos = backPosOut[v][i];
                edgesOut[v][i] = edgesOut[v].back();
                backPosOut[v][i] = backPosOut[v].back();
                backPosOut[edgesOut[v][i].w][backPosOut[v][i]] = i;

                edgesOut[w][backPos] = edgesOut[w].back();
                backPosOut[w][backPos] = backPosOut[w].back();
                backPosOut[edgesOut[w][backPos].w][backPosOut[w][backPos]] = backPos;

                edgesOut[v].pop_back();
                backPosOut[v].pop_back();
                edgesOut[w].pop_back();
                backPosOut[w].pop_back();
            }

            return;
        }
    }

    throw std::runtime_error("You tried to delete an edge that does not exist");
}

bool Graph::hasEdge(node v, node w) {
    if (v > aboveMaxNodeID || w > aboveMaxNodeID || !alive[v] || !alive[w]) {
        throw std::runtime_error("Checked if an edge exists for which at least one endpoint does not exist");
    }

    for (edge e : edgesOut[v]) {
        if (e.w == w) {
            return true;
        }
    }

    return false;
}

node Graph::addVertex() {
    n++;

    node v;

    if (openIDSlots.empty()) {
        v = aboveMaxNodeID;
        aboveMaxNodeID++;

        edgesOut.emplace_back();
        backPosOut.emplace_back();
        alive.emplace_back(true);

        if (directed) {
            edgesIn.emplace_back();
            backPosIn.emplace_back();
        }
    } else {
        v = openIDSlots.back();
        openIDSlots.pop_back();
        alive[v] = true;
        
        if (v >= aboveMaxNodeID) {
            aboveMaxNodeID = v + 1;
        }
    }

    return v;
}

void Graph::deleteVertex(node v) {
    // TODO: Implement efficient vertex deletion (more efficient than just calling deleteEgde a bunch of times)

    while (!edgesOut[v].empty()) {
        deleteEdge(v, edgesOut[v].back().w);
    }

    if (directed) {
        while (!edgesIn[v].empty()) {
            deleteEdge(edgesIn[v].back().v, v);
        }
    }

    alive[v] = false;
    n--;
    openIDSlots.emplace_back(v);

    if (v + 1 == aboveMaxNodeID) {
        while (!alive[v] && v > 0) {
            v--;
        }

        if (v == 0) {
            if (alive[0]) {
                aboveMaxNodeID = 1;
            } else {
                aboveMaxNodeID = 0;
            }
        } else {
            aboveMaxNodeID = v + 1;
        }
    }
}

bool Graph::hasVertex(node v) {
    if (v > aboveMaxNodeID) {
        return false;
    }
    return alive[v];
}

Graph::EdgeIterator Graph::getEdges() {
    return {*this, 0, 0};
}

Graph::NodeIterator Graph::getNodes() {
    return {*this, 0};
}

std::vector<edge> &Graph::incidentEdges(node v) {
    return edgesOut[v];
}

std::vector<edge> &Graph::outgoingEdges(node v) {
    return edgesOut[v];
}

std::vector<edge> &Graph::incomingEdges(node v) {
    return edgesIn[v];
}
count Graph::getNumberOfEdges()
{
    return n;
}
count  Graph::getNumberOfNodes()
{
    return m;
}
