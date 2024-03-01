#include <iostream>
#include "../data_structures/Graph.h"

using namespace std;

template<typename T>

/****************** toposort ********************/
/*
 * Performs a topological sorting of the vertices of a graph.
 * Returns a vector with the contents of the vertices by topological order.
 * If the graph has cycles, returns an empty vector.
 * Follows the algorithm described in theoretical classes.
 */
vector<T> topsort(const Graph<T> *g) {
    vector<T> res;
    queue<Vertex<T> *> q;

    for (Vertex<T> *v: g->getVertexSet()) {
        v->setIndegree(0);
    }

    for (Vertex<T> *v: g->getVertexSet()) {
        for (const Edge<T> &e: v->getAdj()) {
            e.getDest()->setIndegree(e.getDest()->getIndegree() + 1);
        }

    }

    for (Vertex<T> *v: g->getVertexSet()) {
        if (v->getIndegree() == 0)
            q.push(v);
    }

    while (!q.empty()) {
        Vertex<T> *u = q.front();
        for (auto e: u->getAdj()) {
            Vertex<T> *w = e.getDest();
            w->setIndegree(w->getIndegree() - 1);
            if (w->getIndegree() == 0)
                q.push(w);
        }
        q.pop();
        res.push_back(u->getInfo());
    }

    if (res.size() != g->getVertexSet().size()) {
        res.empty();
    }

    return res;
}