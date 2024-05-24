#include "color_walk.hpp"
#include <vector>
#include <climits> // For INT_MAX
#include <exception>

namespace cs251 {

    struct WalkPair {
        char startColor = '-';
        int walkWeight = 0;
    };

    int color_walk::minIndex(const std::vector<int> &distTo, const std::vector<bool> &visited) {
        int minVal = INT_MAX;
        int minIndex = -1;
        for (int i = 0; i < distTo.size(); ++i) {
            if (!visited[i] && distTo[i] <= minVal) {
                minVal = distTo[i];
                minIndex = i;
            }
        }
        return minIndex;
    }

    std::vector <std::pair<char, int>> color_walk::calculate(const graph &g, handle startHandle) {
        int numVert = g.get_m_vertices().size();
        std::vector <std::vector<int>> colorNodes(3 * numVert, std::vector<int>(3 * numVert, 0));

        //for (const auto &vertex: g.get_m_vertices()) {
        for (int i = 0; i < g.get_m_vertices().size(); i++) {
            for (const auto &edge: g.get_m_vertices()[i].m_edges) {
                if (edge.col == RED) {
                    int sourceIndex = 3 * i;
                    int destIndex = 3 * edge.m_destinationHandle + 1;
                    //fprintf(stderr, "%d, %d, %d \n", 3 * numVert, sourceIndex, destIndex);
                    //fprintf(stderr, "reached 1 red\n");
                    if (colorNodes[sourceIndex][destIndex] != 0) {
                        // should this be > 0???
                        //fprintf(stderr, "reached 2 red\n");
                        if (colorNodes[sourceIndex][destIndex] > edge.m_weight) {
                            colorNodes[sourceIndex][destIndex] = edge.m_weight;
                        }
                        //fprintf(stderr, "reached red\n");
                        continue;
                    }
                    //fprintf(stderr, "reached 3 red \n");
                    colorNodes[sourceIndex][destIndex] = edge.m_weight;
                    //fprintf(stderr, "reached 4 red \n");
                } else if (edge.col == GREEN) {
                    int sourceIndex = 3 * i + 1;
                    int destIndex = 3 * edge.m_destinationHandle + 2;
                    //fprintf(stderr, "%d, %d, %d \n", 3 * numVert, sourceIndex, destIndex);
                    //fprintf(stderr, "reached 1 green\n");
                    if (colorNodes[sourceIndex][destIndex] != 0) { // should this be > 0???
                        //fprintf(stderr, "reached 2 green\n");
                        if (colorNodes[sourceIndex][destIndex] > edge.m_weight) {
                            colorNodes[sourceIndex][destIndex] = edge.m_weight;
                        }
                        //fprintf(stderr, "reached green \n");
                        continue;
                    }
                    //fprintf(stderr, "reached 3 green \n");
                    colorNodes[sourceIndex][destIndex] = edge.m_weight;
                    //fprintf(stderr, "reached 4 green \n");
                } else { // Assuming BLUE
                    int sourceIndex = 3 * i + 2;
                    int destIndex = 3 * edge.m_destinationHandle;
                    //fprintf(stderr, "%d, %d, %d \n", 3 * numVert, sourceIndex, destIndex);
                    //fprintf(stderr, "reached 1 blue\n");
                    if (colorNodes[sourceIndex][destIndex] != 0) { // should this be > 0???
                        //fprintf(stderr, "reached 2 blue\n");
                        if (colorNodes[sourceIndex][destIndex] > edge.m_weight) {
                            colorNodes[sourceIndex][destIndex] = edge.m_weight;
                        }
                        //fprintf(stderr, "reached blue\n");
                        continue;
                    }
                    //fprintf(stderr, "reached 3 blue \n");
                    colorNodes[sourceIndex][destIndex] = edge.m_weight;
                    //fprintf(stderr, "reached 4 blue \n");
                }
            }
        }


        std::vector<int> distances(numVert, INT_MAX);
        std::vector<char> colors(numVert, '-');

        for (int n = 0; n < 3; n++) {
            std::vector<int> distTo(3 * numVert, INT_MAX);
            std::vector<bool> visited(3 * numVert, false);
            distTo[3 * (int) startHandle + n] = 0;

            for (int i = 0; i < 3 * numVert; i++) {
                int u = minIndex(distTo, visited);
                visited[u] = true;
                for (int v = 0; v < 3 * numVert; v++) {
                    if (!visited[v] && colorNodes[u][v] != 0) {
                        if ((distTo[u] < INT_MAX) && (distTo[u] + colorNodes[u][v] < distTo[v])) {
                            distTo[v] = distTo[u] + colorNodes[u][v];
                        }
                    }
                }
                for (int j = 0; j < distTo.size(); j++) {
                    if (distances[j / 3] > distTo[j]) {
                        distances[j / 3] = distTo[j];
                        if (n % 3 == 0) {
                            colors[j / 3] = 'R';
                        } else if (n % 3 == 1) {
                            colors[j / 3] = 'G';
                        } else {
                            colors[j / 3] = 'B';
                        }
                    }
                }
            }
        }
        std::vector <WalkPair> results(numVert);
        for (int i = 0; i < numVert; i++) {
            if (i == (int) startHandle) {
                results[i].startColor = '-';
                results[i].walkWeight = 0;
                //continue;
            }
            else {
                results[i].startColor = (distances[i] == INT_MAX) ? '-' : colors[i];
                results[i].walkWeight = (handle)(distances[i] == INT_MAX) ? -1 : distances[i];
            }
        }

        std::vector <std::pair<char, int>> pairResults;
        pairResults.reserve(numVert);
        for (const auto &wp: results) {
            pairResults.emplace_back(wp.startColor, wp.walkWeight);
        }
        return pairResults;


    }
}
