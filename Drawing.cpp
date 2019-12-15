#include "Drawing.h"
#include "Sort.h"

void drawValues(std::vector<ValueWithFunc>& vwfs, int height, int width, int position1, int position2) {
	const double colorUnit = (255) / (double)vwfs.size();
	double r, g, b; r = g = b = 0;
	r = 200;
	for (auto& vwf : vwfs) {
		const double color = colorUnit * vwf.value;
		g = vwf.value * colorUnit;
		b = vwf.value * colorUnit / 2;
		auto&& rect = Rect(vwf.position * width, Scene::Height(), width, -vwf.value * height);
		if (vwf.position == position1 || vwf.position == position2)
			rect.draw(Color(255, 0, 0));
		else
			rect.draw(Color(255 - (int)r, 255 - (int)g, 255 - (int)b));
	}
}

void drawValues(std::vector<ValueWithFunc>& vwfs, int height, int width) {
	drawValues(vwfs, height, width, -1, -1);
}


void setRandValues(std::vector<ValueWithFunc>& vwfs, int max) {
	std::vector<int> n(max);
	for (int i = 0; i < max; ++i)n.at(i) = i;
	for (int i = 0; i < max; ++i) {
		std::swap(n.at(i), n.at(rand() % max));
	}
	for (int i = 0; i < vwfs.size(); ++i) {
		vwfs[i].value = n.at(i);
	}
}


void drawButtons(std::vector<ValueWithFunc>& vwfs, int& counter) {
	const int buttonWidth = 200;
	const int buttonHeight = 40;

	if (SimpleGUI::Button(U"クイックソート", Vec2(buttonWidth, buttonHeight))) {
		std::sort(vwfs.begin(), vwfs.end());
		Print << counter;
	}
	if (SimpleGUI::Button(U"マージソート", Vec2(buttonWidth, buttonHeight * 2))) {
		std::stable_sort(vwfs.begin(), vwfs.end(), [](ValueWithFunc vwf1, ValueWithFunc vwf2) {return vwf1 < vwf2; });
		Print << counter;
	}
	if (SimpleGUI::Button(U"バブルソート", Vec2(buttonWidth, buttonHeight * 3))) {
		bubbleSort(vwfs, (int)vwfs.size());
		Print << counter;
	}
	if (SimpleGUI::Button(U"シェルソート", Vec2(buttonWidth, buttonHeight * 4))) {
		shellSort(vwfs, (int)vwfs.size());
		Print << counter;
	}
	if (SimpleGUI::Button(U"シェルカーソート", Vec2(buttonWidth, buttonHeight * 5))) {
		shakerSort(vwfs, (int)vwfs.size());
		Print << counter;
	}
	if (SimpleGUI::Button(U"挿入ソート", Vec2(buttonWidth, buttonHeight * 6))) {
		insertionSort(vwfs, (int)vwfs.size());
		Print << counter;
	}
	if (SimpleGUI::Button(U"選択ソート", Vec2(buttonWidth, buttonHeight * 7))) {
		selectionSort(vwfs, (int)vwfs.size());
		Print << counter;
	}
}

