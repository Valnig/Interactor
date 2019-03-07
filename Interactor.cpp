
#include "pch.h"
#include <vector>
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <stdexcept>


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
		return "vertex "+std::to_string(vertex);
	}

	std::string to_string(Edge edge) {
		return "edge ("+std::to_string(edge.first) + "->"+ std::to_string(edge.second)+")";
	}

	~Graph() {
		std::cout << " deleted graph " << this << std::endl;
	}
};



//design pattern prototype


template<typename _SUBJECT, typename _STATUS = bool>
class Tool {
protected:
	_SUBJECT* subject_ = nullptr;
	_STATUS status_;///< default status ? Good really ?
};

template<typename _WHAT>
class Remove : public Tool<Graph, std::string>{
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


template<typename _SUBJECT, typename _TOOL>
class Interaction {
	_TOOL* tool_;
	
public:

	template<typename ... _ARGS>
	Interaction(_ARGS ... args) {
		tool_ = new _TOOL();
		tool_->start(args...);
	}


	template<typename ... _ARGS>
	void tick(_ARGS ... args) {
		if (tool_) {
			tool_->tick(args...);
		}
	}

	template<typename ... _ARGS>
	void stop(_ARGS ... args) {
		if (tool_) {
			tool_->stop(args...);
			delete tool_;
		}
	}

};

template<typename _SUBJECT>
class Interactor {
private:
	_SUBJECT* subject_;
	const bool allocated_subject_;
	
public:

	Interactor(_SUBJECT* subject) : subject_(subject), allocated_subject_(false) {}

	template<typename ... _ARGS>
	Interactor(_ARGS ... args) : subject_(new _SUBJECT(args...)), allocated_subject_(true) {}

	template<typename _TOOL, typename ... _ARGS>
	Interaction<_SUBJECT, _TOOL>* start_operation(_ARGS ... args) const {
		return new Interaction<_SUBJECT, _TOOL>(subject_, args...);
	}

	template<typename _TOOL, typename ... _ARGS>
	void tick_operation(Interaction<_SUBJECT, _TOOL>* op, _ARGS ... args) const {
		if(!op){
			throw std::invalid_argument("ticked nullptr Operation");
		}
		op->tick(args...);
	}
	
	template<typename _TOOL, typename ... _ARGS>
	void stop_operation(Interaction<_SUBJECT, _TOOL>* op, _ARGS ... args) const {
		if (!op) {
			throw std::invalid_argument("stopped nullptr Operation");
		}
		op->stop(args...);
		delete op;
	}

	~Interactor() {
		if (allocated_subject_) {
			delete subject_;
		}
	}
};

#if 0
template<typename ... _SUBJECTS>
class Context {

};

template<typename ... _TOOLS>
class Toolset {

};

template<typename _CONTEXT, typename _TOOLSET, enum INTERACTION_MODE>
class SingleInteractionMouseEventDispatcher {
private:
	_CONTEXT* context_;
	void* current_interaction_ = nullptr;

public:

	SingleInteractionMouseEventDispatcher(_CONTEXT* context) : context_(context) {}

	template<typename _TOOL>
	void set_mode() {

	}
};
#endif


/** This is supposed to be a dispatcher for mouse input events.
* Basically it can contain multiple Interactors to perform any kind of
* operations on any kind of objects.
This class is an example of how to use Interactors*/
class MouseEventDispatcher{
	public:
	
		typedef enum {MOVE, CUT, REMOVE} INTERACTION_MODE;
	
	private:
	Graph* graph_;
	INTERACTION_MODE mode_;
	const Interactor<Graph> interactor_;
	std::vector<void*> interactions_;
	

	public:
	
	MouseEventDispatcher(Graph* graph) : graph_(graph), interactor_(graph) {} //, interactor2_({}, { {},{} }) {}
	
	bool set_mode(INTERACTION_MODE mode) {
		mode_ = mode;
		return true;
	}

	/** _WHAT defines on what the user clicked*/
	template<typename _WHAT>
	void mouse_click(_WHAT what){
		switch (mode_){
			case REMOVE : interactions_.push_back((Interaction<Graph,Remove<_WHAT>>*)interactor_.start_operation<Remove<_WHAT>>(what)); break;
			default : {//do nothing
			break;}
		}
	}
	
	void tick() {}

};


int main()
{
	std::vector<VertexLabel> verts({ 1,2,3 });
	std::vector<Edge> edges({ {1,2},{2,3} });

	Graph graph(verts, edges);

	MouseEventDispatcher dispatcher(&graph);
	dispatcher.set_mode(MouseEventDispatcher::REMOVE);

	dispatcher.mouse_click<Vertex>(1);
	dispatcher.mouse_click<Edge>(Edge({ 1,2 }));
	
#if 0

	Interactor<Graph> interactor(&graph);

	Interactor<Graph> interactor2(verts, edges);

	Interaction<Graph, Remove<Vertex>>* interaction = interactor.start_operation<Remove<Vertex>>(1);
	interaction->tick();
	interaction->stop();

	Interaction<Graph, Remove<Edge>>* interaction2 = interactor.start_operation<Remove<Edge>>(Edge({ 1,2 }));
	
	interaction2->tick();
	interaction2->stop();
#endif

	return 0;

}

