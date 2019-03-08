#pragma once




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