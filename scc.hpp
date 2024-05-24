#pragma once
#include "graph.hpp"
#include <vector>
#include <iostream>
#include <climits>

namespace cs251 {
    class scc {
    public:
        static int search(const graph& g);
    private:
        static void dfs(int v, const graph& g, std::vector<int>& disc, std::vector<int>& low, 
                        std::vector<int>& st, std::vector<bool>& stackMember, int& time, int& count);
    };
}
