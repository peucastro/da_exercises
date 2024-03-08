// Original code by Gonçalo Leão
// Updated by DA 2023/2024 Team

#include "../data_structures/Graph.h"
#include "MSTTestAux.h"

template<class T>
std::vector<Vertex<T> *> prim(Graph<T> *g) {
    if (g->getVertexSet().empty())
        return g->getVertexSet();

    for (Vertex<T> *v: g->getVertexSet()) {
        v->setDist(INF);
        v->setPath(nullptr);
        v->setVisited(false);
    }

    Vertex<T> *r = g->getVertexSet().front();
    r->setDist(0.0);

    MutablePriorityQueue<Vertex<T>> q;
    q.insert(r);

    while (!q.empty()) {
        Vertex<T> *u = q.extractMin();
        u->setVisited(true);

        for (Edge<T> *e: u->getAdj()) {
            Vertex<T> *v = e->getDest();

            if (v->getDist() == INF)
                q.insert(v);

            if (!v->isVisited() && e->getWeight() < v->getDist()) {
                v->setPath(e);
                v->setDist(e->getWeight());
                q.decreaseKey(v);
            }
        }
    }

    return g->getVertexSet();
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP3_Ex2, test_prim) {
    Graph<int> graph = createMSTTestGraph<int>();
    std::vector<Vertex<int> *> res = prim(&graph);

    std::stringstream ss;
    for (const auto v: res) {
        ss << v->getInfo() << "<-";
        if (v->getPath() != nullptr) {
            ss << v->getPath()->getOrig()->getInfo();
        }
        ss << "|";
    }
    std::cout << ss.str() << std::endl;

    EXPECT_TRUE(isSpanningTree(res));
    EXPECT_EQ(spanningTreeCost(res), 11);
}