#include <iostream>
#include <fstream>
#include <exception>
#include <vector>
#include "graph.hpp"
#include <climits>

using namespace cs251;


void graph::read_edge_weights(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Corrupted file");
    }
    int n_vertices = 0, m_edges = 0;
    file >> n_vertices >> m_edges;

    m_vertices.resize(n_vertices);
    int source, destination, weight;
    char checkForWeight;

    for (int i = 0; i < m_edges; i++) {
        file >> source >> destination;
        weight = 1;
        file.get(checkForWeight);

        if (checkForWeight == ' ' || checkForWeight == '\t') {
            if (file >> weight) {
            }
            file.ignore(INT_MAX, '\n');
        } else {
            file.unget();
        }

        graph_edge edge;
        edge.m_weight = weight;
        edge.m_destinationHandle = destination;
        m_vertices[source].m_edges.push_back(edge);
    }
    file.close();
}

void graph::read_edge_colors(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Corrupted file");
    }
    int n_vertices = 0;
    int m_edges = 0;
    file >> n_vertices >> m_edges;
    m_vertices.resize(n_vertices);
    int source, destination, weight;
    char colorChar;
    for (int i = 0; i < m_edges; ++i) {
        file >> source >> destination >> weight >> colorChar;
        color edgeColor;
        switch (colorChar) {
            case 'R':
                edgeColor = RED;
                break;
            case 'G':
                edgeColor = GREEN;
                break;
            case 'B':
                edgeColor = BLUE;
                break;
            default:
                edgeColor = NONE;
                break;
        }
        graph_edge edge;
        edge.m_weight = weight;
        edge.m_destinationHandle = destination;
        edge.col = edgeColor;
        m_vertices[source].m_edges.push_back(edge);
        edge.m_source = source;
    }
    file.close();
}
const std::vector<graph_vertex>& graph::get_m_vertices() const {
    return m_vertices;
}

