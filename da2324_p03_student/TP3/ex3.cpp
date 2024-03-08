// Original code by Gonçalo Leão
// Updated by DA 2023/2024 Team

#include "MSTTestAux.h"
#include "../data_structures/UFDS.h"

template<class T>
void dfsKruskalPath(Vertex<T> *v) {
    v->setVisited(true);

    for (Edge<T> *e: v->getAdj()) {
        Vertex<T> *w = e->getDest();
        if (e->isSelected() && !w->isVisited()) {
            w->setPath(e);
            dfsKruskalPath(w);
        }
    }
}

template<class T>
std::vector<Vertex<T> *> kruskal(Graph<T> *g) {
    if (g->getVertexSet().empty())
        return g->getVertexSet();

    vector<Edge<T> *> edges;
    UFDS ufds(g->getNumVertex());
    int id = 0;
    unsigned int edgesCount = 0;

    for (Vertex<T> *v: g->getVertexSet()) {
        v->setVisited(false);
        v->setPath(nullptr);
        v->setInfo(id++);

        for (Edge<T> *e: v->getAdj()) {
            e->setSelected(false);
            if (e->getOrig()->getInfo() < e->getDest()->getInfo())
                edges.push_back(e);
        }
    }

    sort(edges.begin(), edges.end(),
         [](const Edge<T> *e1, const Edge<T> *e2) -> bool { return e1->getWeight() < e2->getWeight(); });

    for (Edge<T> *e: edges) {
        Vertex<T> *u = e->getOrig();
        Vertex<T> *v = e->getDest();

        if (!ufds.isSameSet(u->getInfo(), v->getInfo())) {
            ufds.linkSets(u->getInfo(), v->getInfo());

            e->setSelected(true);
            e->getReverse()->setSelected(true);

            if (++edgesCount == g->getNumVertex() - 1)
                break;
        }
    }

    g->getVertexSet()[0]->setPath(nullptr);
    dfsKruskalPath(g->getVertexSet()[0]);

    return g->getVertexSet();
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP3_Ex3, test_kruskal) {
    Graph<int> graph = createMSTTestGraph<int>();
    std::vector<Vertex<int> *> res = kruskal(&graph);

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