// Interactor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <utility>
#include <vector>





/** prototype stuff*/
typedef int Vertex;
typedef std::pair<Vertex, Vertex> Edge;
typedef int VertexLabel;

class Graph {
private :
	std::vector<VertexLabel> vertices_;
	std::vector<Edge> edges_;

public:

	Graph(std::vector<VertexLabel> vertices, std::vector<Edge> edges) : vertices_(vertices), edges_(edges) {
		std::cout << "created graph with " << vertices_.size() << " vertices and " << edges_.size() << " edges" << std::endl;

	}

	bool update_vertex(Vertex vertex, VertexLabel label) {
		vertices_[vertex] = label;
		std::cout << "updated vertex " << vertex<< " as "<<label << std::endl;
		return true;
	}
};


template<typename _SUBJECT, typename _START_STATUS, typename _TICK_STATUS, typename _STOP_STATUS>
class Tool {
public:

	typedef _START_STATUS START_STATUS;
	typedef _TICK_STATUS TICK_STATUS;
	typedef _STOP_STATUS STOP_STATUS;

protected:
	_SUBJECT* subject_ = nullptr;

};


class MoveVertex : public Tool<Graph, bool, bool, bool>{
	Vertex vertex_;

public:
	bool start(Graph* graph, Vertex vertex) {
		if (subject_ || !graph) {
			return false;
		}
		subject_ = graph;
		vertex_ = vertex;
		std::cout << "vertex " << vertex << " of graph " << graph << " will be updated " << std::endl;
		return true;
	}

	bool tick(VertexLabel label) {
		return subject_->update_vertex(vertex_, label);
	}

	bool stop() {
		//TODO: do something interesting
		return true;
	}
};


template<typename _SUBJECT, typename _TOOL>
class Operation {
	_TOOL tool_;

public:


	template<typename ... _ARGS>
	Operation(_ARGS ... args) : tool_(args...) {}

	template<typename ... _ARGS>
	typename _TOOL::START_STATUS start(_ARGS ... args) {
		return tool_.start(args...);
	}

	template<typename ... _ARGS>
	typename _TOOL::TICK_STATUS tick(_ARGS ... args) {
		return tool_.tick(args...);
	}

	template<typename ... _ARGS>
	typename _TOOL::STOP_STATUS stop(_ARGS ... args) {
		return tool_.stop(args...);
	}

};

/** Single operation at a time*/
template<typename _SUBJECT>
class Interactor {
private:
	_SUBJECT* subject_;
public:

	Interactor(_SUBJECT* subject) : subject_(subject) {}

	template<typename _TOOL, typename ... _ARGS>
	typename _TOOL::START_STATUS start_operation(_ARGS ... args) {
		Operation<_SUBJECT, _TOOL> op;
		return op.start(subject_, args...);
	}

	template<typename _TOOL, typename ... _ARGS>
	typename _TOOL::START_STATUS stop_operation(_ARGS ... args) {
		Operation<_SUBJECT, _TOOL> op;
		return op.start(subject_, args...);
	}
};



int main()
{
	Graph graph({ 1,2,3 }, { {1,2},{2,3} });

	Interactor<Graph> interactor(&graph);
	bool result2 = interactor.start_operation<MoveVertex>(1);

	return 0;

	/*Operation<Graph, MoveVertex> op;
	bool result = op.start<bool,Graph*,Vertex>(&graph, 1);


	
	for (int i(0); i < 3; i++) {
		op.tick<bool, VertexLabel>(i);
	}

	op.stop<bool>();
	
	return 0;*/
}
