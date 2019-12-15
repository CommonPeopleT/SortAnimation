#pragma once

#include <Siv3D.hpp>

class ValueWithFunc {
	std::function<void(ValueWithFunc&, int, int)> onChanged;
	std::function<void(ValueWithFunc&, int, int)> onCompared;
public:
	int value;
	int position;

	ValueWithFunc(int value, int position,
		std::function<void(ValueWithFunc&, int, int)> onChanged,
		std::function<void(ValueWithFunc&, int, int)> onCompared);

	ValueWithFunc& operator=(const ValueWithFunc& vwf);
	bool operator< (ValueWithFunc& p);
	bool operator<= (ValueWithFunc& p);
	bool operator> (ValueWithFunc& p);
	bool operator>= (ValueWithFunc& p);
};
