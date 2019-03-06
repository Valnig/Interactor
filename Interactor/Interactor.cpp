#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <stdexcept>


//Boy Is It Ever Fun To Publish Stuff On Your Own -> BIIEFTPSOYO



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



//design pattern prototype


template<typename _SUBJECT, typename _STATUS = bool>
class Tool {
	public:
	typedef _STATUS STATUS;
protected:
	_SUBJECT* subject_ = nullptr;
	_STATUS status_;///< default status ? Good really ?
};


class MoveVertex : public Tool<Graph, std::string>{
	Vertex vertex_;

public:
	
	void start(Graph* graph, Vertex vertex) {
		subject_ = graph;
		vertex_ = vertex;
		std::cout << "vertex " << vertex << " of graph " << graph << " will be updated " << std::endl;
		status_ = true;
	}

	void tick(VertexLabel label) {
		subject_->update_vertex(vertex_, label);
		status_ = true;
	}

	void stop() {
		//TODO: do something interesting
		status_ = true;
	}
};


template<typename _SUBJECT, typename _TOOL>
class Operation {
	_TOOL* tool_;
	
public:

	template<typename ... _ARGS>
	Operation(_ARGS ... args) {
		tool_ = new _TOOL();
		tool_->start(args...);
	}


	template<typename ... _ARGS>
	void tick(_ARGS ... args) {
		tool_->tick(args...);
	}

	template<typename ... _ARGS>
	void stop(_ARGS ... args) {
		tool_->stop(args...);
	}

};

template<typename _SUBJECT>
class Interactor {
private:
	_SUBJECT* subject_;
	
public:

	Interactor(_SUBJECT* subject) : subject_(subject) {}

	template<typename _TOOL, typename ... _ARGS>
	Operation<_SUBJECT, _TOOL>* start_operation(_ARGS ... args) {
		return new Operation<_SUBJECT, _TOOL>(subject_, args...);
	}

	template<typename _TOOL, typename ... _ARGS>
	void tick_operation(Operation<_SUBJECT, _TOOL>* op, _ARGS ... args) {
		if(!op){
			throw std::invalid_argument("ticked nullptr Operation");
		}
		op->tick(args...);
	}
	
	template<typename _TOOL, typename ... _ARGS>
	void stop_operation(Operation<_SUBJECT, _TOOL>* op, _ARGS ... args) {
		op->stop(args...);
	}
};



int main()
{
	
	
	Graph graph({ 1,2,3 }, { {1,2},{2,3} });

	Interactor<Graph> interactor(&graph);
	Operation<Graph, MoveVertex>* op = interactor.start_operation<MoveVertex>(1);
	
	interactor.tick_operation(op,10);
	
	interactor.stop_operation(op);

	return 0;

	/*Operation<Graph, MoveVertex> op;
	bool result = op.start<bool,Graph*,Vertex>(&graph, 1);


	
	for (int i(0); i < 3; i++) {
		op.tick<bool, VertexLabel>(i);
	}

	op.stop<bool>();
	
	return 0;*/
}

