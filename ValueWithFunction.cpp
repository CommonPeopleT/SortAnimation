#include "ValueWithFunction.h"


ValueWithFunc::ValueWithFunc(int value, int position, 
		std::function<void(ValueWithFunc&, int, int)> onChanged,
		std::function<void(ValueWithFunc&, int, int)> onCompared) {
	this->value = value;
	this->position = position;
	this->onChanged = onChanged;
	this->onCompared = onCompared;

}

ValueWithFunc& ValueWithFunc::operator=(const ValueWithFunc& vwf) {
	if (this == &vwf)return *this;
	this->value = vwf.value;

	onChanged(*this, this->position, vwf.position);
	return *this;
}

bool ValueWithFunc::operator< (ValueWithFunc& p) {
	onCompared(*this, this->position, p.position);
	return this->value < p.value;
}
bool ValueWithFunc::operator<= (ValueWithFunc& p) {
	onCompared(*this, this->position, p.position);
	return this->value <= p.value;
}
bool ValueWithFunc::operator> (ValueWithFunc& p) {
	onCompared(*this, this->position, p.position);
	return this->value > p.value;
}
bool ValueWithFunc::operator>= (ValueWithFunc& p) {
	onCompared(*this, this->position, p.position);
	return this->value >= p.value;
}


