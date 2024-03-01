#include <list>
#include "../data_structures/Graph.h"
#include "stack"

using namespace std;

template<typename T>
list<list<T>> sccTarjan(Graph<T> *g) {
    list<list<T>> res;
    int index = 1;

    for (Vertex<int> *v: g->getVertexSet())
        v->setVisited(false);

    for (Vertex<int> *v: g->getVertexSet()) {
        if (v->getNum() == 0) {
            stack<int> s = {};
            dfs_scc(g, v, s, res, index);
        }
    }

    return res;
}

template<typename T>
void dfs_scc(Graph<T> *g, Vertex<T> *v, stack<T> &s, list<list<T>> &l, int &i) {
    v->setVisited(true);
    v->setNum(i);
    v->setLow(i);
    i++;
    s.push(v->getInfo());

    for (const Edge<T> &e: v->getAdj()) {
        Vertex<T> *neighbor = e.getDest();

        if (!neighbor->isVisited()) {
            dfs_scc(g, neighbor, s, l, i);
            v->setLow(min(v->getLow(), neighbor->getLow()));
        }

        bool flag = false;
        stack<int> aux_s = s;
        while (!aux_s.empty()) {
            if (aux_s.top() == neighbor->getInfo()) {
                flag = true;
                break;
            } else {
                aux_s.pop();
            }
        }

        if (flag)
            v->setLow(min(v->getLow(), neighbor->getNum()));
    }

    if (v->getNum() == v->getLow()) {
        list<int> new_scc;

        int w;
        do {
            w = s.top();
            s.pop();
            new_scc.push_back(w);
        } while (w != v->getInfo());

        l.push_back(new_scc);
    }
}