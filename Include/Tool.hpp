#pragma once


template<typename _SUBJECT, typename _STATUS = bool>
class Tool {
protected:
	_SUBJECT* subject_ = nullptr;
	_STATUS status_;///< default status ? Good really ?
};

