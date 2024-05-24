#include "max_height.hpp"

using namespace cs251;

PriorityQueue::PriorityQueue(int capacity) : indices(capacity, -1) {
    data.reserve(capacity);
}

void PriorityQueue::insert(int start, int end, int weight) {
    data.push_back(Edge(start, end, weight));
    bubbleUp(data.size() - 1);
}

Edge PriorityQueue::extractMax() {
    Edge maximum = data.front();
    data[0] = data.back();
    data.pop_back();
    indices[maximum.start] = -1;
    if (!data.empty()) {
        indices[data[0].start] = 0;
        trickleDown(0);
    }
    return maximum;
}

void PriorityQueue::bubbleUp(int pos) {
    while (pos > 0 && data[(pos - 1) / 2].weight < data[pos].weight) {
        std::swap(data[(pos - 1) / 2], data[pos]);
        indices[data[pos].start] = pos;
        pos = (pos - 1) / 2;
    }
}

void PriorityQueue::trickleDown(int idx) {
    int best = idx;
    if ((2 * idx + 1) < this->currentSize() && data[2 * idx + 1].weight > data[best].weight) {
        best = 2 * idx + 1;
    }
    if ((2 * idx + 2) < this->currentSize() && data[2 * idx + 2].weight > data[best].weight) {
        best = 2 * idx + 2;
    }
    if (best != idx) {
        std::swap(data[idx], data[best]);
        trickleDown(best);
    }
}

int PriorityQueue::currentSize() const {
    return data.size();
}

Components::Components(int count) : parent(count) {
    for (int i = 0; i < count; ++i) {
        parent[i] = i;
    }
}

int Components::getRoot(int element) {
    if (parent[element] != element) {
        parent[element] = getRoot(parent[element]);
    }
    return parent[element];
}

void Components::merge(int first, int second) {
    int rootFirst = getRoot(first);
    int rootSecond = getRoot(second);
    if (rootFirst != rootSecond) {
        parent[rootFirst] = rootSecond;
    }
}

int max_height::calculate(const graph &graph) {
    const auto &nodes = graph.get_m_vertices();
    if (nodes.empty()) return -1; 

    PriorityQueue edges(nodes.size());
    Components forest(nodes.size());

    for (size_t i = 0; i < nodes.size(); ++i) {
        for (const auto &edge : nodes[i].m_edges) {
            if (i < edge.m_destinationHandle) {
                edges.insert(i, edge.m_destinationHandle, edge.m_weight);
            }
        }
    }

    int maximumHeight = INT_MAX;
    while (edges.currentSize() > 0) {
        Edge current = edges.extractMax();
        if (forest.getRoot(current.start) != forest.getRoot(current.end)) {
            forest.merge(current.start, current.end);
            maximumHeight = std::min(maximumHeight, current.weight);
        }
    }

    return maximumHeight;
}
