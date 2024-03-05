#include "../data_structures/Graph.h"
#include "stack"

using namespace std;

// Helper function to reverse the edges of a directed graph
template<typename T>
void aux_reverseGraphEdges(Graph<T> *g) {
    stack<int> edge_stack;
    for (auto v: g->getVertexSet()) {
        for (auto &e: v->getAdj()) {
            auto w = e.getDest();
            edge_stack.push(w->getInfo());
            edge_stack.push(v->getInfo());
        }
    }

    while (!edge_stack.empty()) {
        int src;
        int dst;
        dst = edge_stack.top();
        edge_stack.pop();
        src = edge_stack.top();
        edge_stack.pop();
        g->removeEdge(dst, src);
        g->addEdge(src, dst, 0);
    }
}

// First depth-first search in Kosaraju-Sharir algorithm
template<typename T>
void firstDFSKosarajuSharir(Vertex<T> *v, stack<Vertex<T> *> *vertexStack) {
    v->setVisited(true);

    for (const Edge<T> &e: v->getAdj()) {
        Vertex<T> *w = e.getDest();
        if (!w->isVisited())
            firstDFSKosarajuSharir(w, vertexStack);
    }

    vertexStack->push(v);
}

// Second depth-first search in Kosaraju-Sharir algorithm
template<typename T>
void secondDFSKosarajuSharir(Vertex<T> *v, std::vector<T> &res) {
    v->setVisited(true);
    res.push_back(v->getInfo());

    for (const Edge<T> &e: v->getAdj()) {
        Vertex<T> *w = e.getDest();

        if (!w->isVisited()) {
            secondDFSKosarajuSharir(w, res);
        }
    }
}

// Kosaraju-Sharir algorithm to find strongly connected components
template<typename T>
vector<vector<T>> SCCkosaraju(Graph<T> *g) {
    vector<vector<T>> sccs;
    stack<Vertex<T> *> s;

    for (Vertex<T> *v: g->getVertexSet())
        v->setVisited(false);

    for (Vertex<T> *v: g->getVertexSet()) {
        if (!v->isVisited()) {
            firstDFSKosarajuSharir(v, &s);
        }
    }

    aux_reverseGraphEdges(g);
    for (Vertex<T> *v: g->getVertexSet())
        v->setVisited(false);

    while (!s.empty()) {
        Vertex<T> *v = s.top();
        s.pop();

        if (!v->isVisited()) {
            vector<T> aux;
            secondDFSKosarajuSharir(v, aux);
            sccs.push_back(aux);
        }
    }

    return sccs;
}
