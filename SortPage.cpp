#include "SortPage.h"
#include "Drawing.h"
#include "ValueWithFunction.h"

// 素因数分解
inline std::vector<int> prime(int n);
inline void initSettingPage();
inline void drawChangingElementsCountButton(std::vector<int>& primes, int& size, int& cnt, const int& buttonHeight); 
inline void upDateSettingPage();

void settingPage() {
	initSettingPage();
	while (System::Update()) {
		upDateSettingPage();
	}
}

void sortPage(const int size, const int sleepTime) { // TODO: ソートの計算量と種類を表示する

	const int height = Scene::Height() / size; // 要素の高さの最小値
	const int width = Scene::Width() / size; // 要素一つ当たりの幅
	int counter = 0;

	std::vector<ValueWithFunc> vwfs;
	auto onChanged = [&](ValueWithFunc& vwf, int position1, int position2) { // 代入された時の処理
		if (!System::Update())return 0;
		drawValues(vwfs, height, width, position1, position2);
		++counter;
		System::Sleep(sleepTime);
	};

	auto onCompared = [&](ValueWithFunc& vwf, int position1, int position2) {
		if (!System::Update())return 0;
		drawValues(vwfs, height, width, position1, position2);
		++counter;
		System::Sleep(sleepTime);
	}; // 比較したときの処理

	for (int i = 0; i < size; ++i)vwfs.push_back(ValueWithFunc(0, i, onChanged, onCompared));
	setRandValues(vwfs, size);

	while (System::Update()) {
		counter = 0;
		static bool isOpend = false;
		drawValues(vwfs, height, width);

		// ボタンが押されたらソートのリストを表示する
		if (SimpleGUI::Button(U"Sort", Vec2(400, 0)))isOpend = !isOpend;
		if (isOpend)drawButtons(vwfs, counter);

		// ボタンが押されたらランダムな値を入れる
		if (SimpleGUI::Button(U"Rand", Vec2(200, 0)))setRandValues(vwfs, (int)vwfs.size());

		if (SimpleGUI::Button(U"設定画面に戻る", Vec2(600, 0)))return;
	}
}


inline void initSettingPage() {
	// 背景を水色にする
	Scene::SetBackground(ColorF(0.8, 0.9, 1.0));
}

void upDateSettingPage() {
	static const Font kFont(60);
	static const int kButtonHeight = 40;
	static const int kButtonWidth = 200;

	static std::vector<int> primes = prime(Scene::Width());
	static int size = 1;
	static int cnt = 0;

	drawChangingElementsCountButton(primes, size, cnt, kButtonHeight);

	static int sleepTime = 1;
	if (SimpleGUI::Button(U"待ち時間を1増やす", Vec2(kButtonWidth, 0)) && sleepTime < 1000)++sleepTime;
	if (SimpleGUI::Button(U"待ち時間を100増やす", Vec2(kButtonWidth, kButtonHeight))) {
		sleepTime += 100;
		if (sleepTime > 1000)sleepTime = 1000;
	}
	if (SimpleGUI::Button(U"待ち時間を1減らす", Vec2(kButtonWidth, kButtonHeight * 2)) && 1 < sleepTime)--sleepTime;
	if (SimpleGUI::Button(U"待ち時間を100減らす", Vec2(kButtonWidth, kButtonHeight * 3))) {
		sleepTime -= 100;
		if (sleepTime < 1)sleepTime = 1;
	}

	kFont(U"要素数 : " + ToString(size)).drawAt(kButtonWidth * 3, kButtonHeight * 3);
	kFont(U"待ち時間 : " + ToString(sleepTime)).drawAt(kButtonWidth * 3, kButtonHeight * 5);

	if (SimpleGUI::Button(U"ソート画面へ行く", Vec2(kButtonWidth * 2, 0))) {
		sortPage(size, sleepTime);
	}

}



inline void drawChangingElementsCountButton(std::vector<int>& primes, int& size, int& cnt, const int& buttonHeight) {
	if (SimpleGUI::Button(U"要素数を増やす", Vec2(0, 0))) {
		if (cnt < primes.size() - 1) {
			size *= primes.at(cnt);
			cnt++;
		}
	}
	if (SimpleGUI::Button(U"要素数を減らす", Vec2(0, buttonHeight))) {
		if (cnt > 0) {
			--cnt;
			size /= primes.at(cnt);
		}
	}
}

inline std::vector<int> prime(int n) {
	std::vector<int> primes;
	for (int i = 2; n >= i * i; ++i) {
		while (!(n % i)) {
			n /= i;
			primes.push_back(i);
		}
	}
	if (n != 1)primes.push_back(n);
	return primes;
}
