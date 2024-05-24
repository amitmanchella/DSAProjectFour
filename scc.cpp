#include "scc.hpp"

using namespace cs251;

int scc::search(const graph& g) {
    int V = g.get_m_vertices().size();
    std::vector<int> disc(V, -1), low(V, -1);
    std::vector<bool> stackMember(V, false);
    std::vector<int> st;

    int time = 0;
    int count = 0;

    for (int i = 0; i < V; i++) {
        if (disc[i] == -1) {
            dfs(i, g, disc, low, st, stackMember, time, count);
        }
    }
    return count;
}

void scc::dfs(int u, const graph& g, std::vector<int>& disc, std::vector<int>& low, 
              std::vector<int>& st, std::vector<bool>& stackMember, int& time, int& count) {
    disc[u] = low[u] = ++time;
    st.push_back(u);
    stackMember[u] = true;

    for (const auto& edge : g.get_m_vertices()[u].m_edges) {
        int v = edge.m_destinationHandle;
        if (disc[v] == -1) {
            dfs(v, g, disc, low, st, stackMember, time, count);
            low[u] = std::min(low[u], low[v]);
        } else if (stackMember[v]) {
            low[u] = std::min(low[u], disc[v]);
        }
    }

    int w = 0;
    if (low[u] == disc[u]) {
        while (st.back() != u) {
            w = st.back();
            st.pop_back();
            stackMember[w] = false;
        }
        w = st.back();
        st.pop_back();
        stackMember[w] = false;
        count++;
    }
}
