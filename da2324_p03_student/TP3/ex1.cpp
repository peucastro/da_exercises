// Original code by Gonçalo Leão
// Updated by DA 2023/2024 Team

#include "../data_structures/Graph.h"

template<class T>
bool findAugmentingPath(Graph<T> *g, Vertex<T> *s, Vertex<T> *t) {
    for (Vertex<T> *v: g->getVertexSet())
        v->setVisited(false);

    s->setVisited(true);
    std::queue<Vertex<T> *> q;
    q.push(s);

    while (!q.empty() && !t->isVisited()) {
        Vertex<T> *v = q.front();
        q.pop();

        for (Edge<T> *e: v->getAdj()) {
            Vertex<T> *w = e->getDest();
            if (!w->isVisited() && e->getWeight() - e->getFlow() > 0) {
                w->setVisited(true);
                w->setPath(e); // Set forward edge as path
                q.push(w);
            }
        }

        for (Edge<T> *e: v->getIncoming()) {
            Vertex<T> *w = e->getOrig();
            if (!w->isVisited() && e->getFlow() > 0) {
                w->setVisited(true);
                w->setPath(e); // Set reverse edge as path
                q.push(w);
            }
        }
    }

    return t->isVisited();
}

template<class T>
double findBottleNeckAlongPath(Vertex<T> *s, Vertex<T> *t) {
    double bottleneck = INF;

    for (Vertex<T> *v = t; v != s;) {
        Edge<T> *e = v->getPath();
        if (e->getDest() == v) {
            bottleneck = std::min(bottleneck, e->getWeight() - e->getFlow());
            v = e->getOrig();
        } else {
            bottleneck = std::min(bottleneck, e->getFlow());
            v = e->getDest();
        }
    }

    return bottleneck;
}

template<class T>
void augmentFlowAlongPath(Vertex<T> *s, Vertex<T> *t, const double &bottleNeck) {
    for (Vertex<T> *v = t; v != s;) {
        Edge<T> *e = v->getPath();
        double flow = e->getFlow();
        if (e->getDest() == v) {
            e->setFlow(flow + bottleNeck);
            v = e->getOrig();
        } else {
            e->setFlow(flow - bottleNeck);
            v = e->getDest();
        }
    }
}

template<class T>
void edmondsKarp(Graph<T> *g, int source, int target) {
    Vertex<T> *s = g->findVertex(source);
    Vertex<T> *t = g->findVertex(target);

    if (s == nullptr || t == nullptr || s == t)
        throw std::logic_error("Invalid source and/or target vertex");

    for (Vertex<T> *v: g->getVertexSet()) {
        v->setPath(nullptr);
        for (Edge<T> *e: v->getAdj())
            e->setFlow(0.0);
    }

    double bottleNeck;
    while (findAugmentingPath(g, s, t)) {
        bottleNeck = findBottleNeckAlongPath(s, t);
        augmentFlowAlongPath(s, t, bottleNeck);
    }
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP3_Ex1, test_edmondsKarp) {
    Graph<int> myGraph;

    for (int i = 1; i <= 6; i++)
        myGraph.addVertex(i);

    myGraph.addEdge(1, 2, 3);
    myGraph.addEdge(1, 3, 2);
    myGraph.addEdge(2, 5, 4);
    myGraph.addEdge(2, 4, 3);
    myGraph.addEdge(2, 3, 1);
    myGraph.addEdge(3, 5, 2);
    myGraph.addEdge(4, 6, 2);
    myGraph.addEdge(5, 6, 3);

    edmondsKarp(&myGraph, 1, 6);

    std::stringstream ss;
    for (auto v: myGraph.getVertexSet()) {
        ss << v->getInfo() << "-> (";
        for (const auto e: v->getAdj())
            ss << (e->getDest())->getInfo() << "[Flow: " << e->getFlow() << "] ";
        ss << ") || ";
    }

    std::cout << ss.str() << std::endl << std::endl;

    EXPECT_EQ(
            "1-> (2[Flow: 3] 3[Flow: 2] ) || 2-> (5[Flow: 1] 4[Flow: 2] 3[Flow: 0] ) || 3-> (5[Flow: 2] ) || 4-> (6[Flow: 2] ) || 5-> (6[Flow: 3] ) || 6-> () || ",
            ss.str());

}