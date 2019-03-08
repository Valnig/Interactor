#pragma once
#include <vector>
#include <iostream>
#include <string>

/** prototype stuff*/
typedef int Vertex;
typedef std::pair<Vertex, Vertex> Edge;
typedef int VertexLabel;

class Graph {
private:
	std::vector<VertexLabel> vertices_;
	std::vector<Edge> edges_;

public:

	Graph(std::vector<VertexLabel> vertices, std::vector<Edge> edges) : vertices_(vertices), edges_(edges) {
		std::cout << "created graph with " << vertices_.size() << " vertices and " << edges_.size() << " edges" << std::endl;

	}

	bool update_vertex(Vertex vertex, VertexLabel label) {
		vertices_[vertex] = label;
		std::cout << "updated vertex " << vertex << " as " << label << std::endl;
		return true;
	}

	bool remove(Vertex vertex) {
		//TODO : remove vertex
		std::cout << "removed vertex " << vertex << std::endl;
		return true;
	}

	bool remove(Edge edge) {
		std::cout << "removed edge " << to_string(edge) << std::endl;
		return true;
	}

	std::string to_string(Vertex vertex) {
		return "vertex " + std::to_string(vertex);
	}

	std::string to_string(Edge edge) {
		return "edge (" + std::to_string(edge.first) + "->" + std::to_string(edge.second) + ")";
	}

	~Graph() {
		std::cout << " deleted graph " << this << std::endl;
	}
};



//design pattern prototype

template<typename _WHAT>
class Remove : public Tool<Graph, std::string> {
	_WHAT graph_element_;

public:

	void start(Graph* graph, _WHAT graph_element) {
		subject_ = graph;
		graph_element_ = graph_element;
		std::cout << graph->to_string(graph_element) << " of graph " << graph << " will be removed " << std::endl;
		status_ = "started";
	}

	void tick() {
		status_ = "ticking";
	}

	void stop() {
		//TODO: do something interesting
		subject_->remove(graph_element_);
		status_ = "stopped";
	}
};


