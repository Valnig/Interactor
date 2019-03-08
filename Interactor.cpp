
#include "pch.h"
#include "Include/Interactor.hpp"
#include "Include/ExperimentalClasses.hpp"


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

