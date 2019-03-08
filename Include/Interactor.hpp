#pragma once

#include "Interaction.hpp"
#include "Tool.hpp"

#include <utility>
#include <stdexcept>



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
		if (!op) {
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
