#pragma once
#include <iostream>
#include <fstream>
#include <vector>

namespace cs251
{
	typedef int handle;

	enum color
	{
		RED, GREEN, BLUE, NONE
	};

	struct graph_edge
	{
		int m_weight = -1;
		handle m_destinationHandle = -1;
		color col;
        handle m_source = -1;
	};

	struct graph_vertex
	{
		std::vector<graph_edge> m_edges{};
		handle m_handle = -1;
	};
 
    /*struct new_vertex
    {
        std::vector<graph_edge> m_edges{};
        handle m_handle = -1;
        int distance = 9999;
    };*/



	class graph
	{
		std::vector<graph_vertex> m_vertices;
	public:
		void read_edge_weights(const std::string& filePath);
		void read_edge_colors(const std::string& filePath);
        const std::vector<graph_vertex>& get_m_vertices() const;
        };
}
