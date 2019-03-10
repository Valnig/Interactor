#pragma once


template<typename _SUBJECT, typename _STATUS = bool>
class Tool {
public:

	typedef _STATUS STATUS;

	Tool(_SUBJECT* subject) : subject_(subject) {}
	_STATUS status_;///< default status ? Good really ?
protected:
	_SUBJECT* subject_ = nullptr;
};

