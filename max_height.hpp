#pragma once
#include "graph.hpp"
#include <vector>
#include <climits> 

namespace cs251 {

struct Edge {
    int start;
    int end;
    int weight;
    Edge(int src, int dst, int wgt) : start(src), end(dst), weight(wgt) {}
};

class PriorityQueue {
public:
    explicit PriorityQueue(int capacity);
    void insert(int start, int end, int weight);
    Edge extractMax();
    int currentSize() const;

private:
    std::vector<Edge> data; 
    std::vector<int> indices;
    void bubbleUp(int pos);
    void trickleDown(int index);
};

class Components {
public:
    explicit Components(int count);
    int getRoot(int element);
    void merge(int first, int second);

private:
    std::vector<int> parent;
};

class max_height {
public:
    static int calculate(const graph& g);
};

}
