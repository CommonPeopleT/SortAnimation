#pragma once
#include "ValueWithFunction.h"

void drawValues(std::vector<ValueWithFunc>& vwfs, int height, int width);
void drawValues(std::vector<ValueWithFunc>& vwfs, int height, int width, int position1, int position2);
void setRandValues(std::vector<ValueWithFunc>& vwfs, int max);
void drawButtons(std::vector<ValueWithFunc>& vwfs, int& counter);