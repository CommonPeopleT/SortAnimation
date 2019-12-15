#include "SortPage.h"
#include "Drawing.h"
#include "ValueWithFunction.h"

// �f��������
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

void sortPage(const int size, const int sleepTime) { // TODO: �\�[�g�̌v�Z�ʂƎ�ނ�\������

	const int height = Scene::Height() / size; // �v�f�̍����̍ŏ��l
	const int width = Scene::Width() / size; // �v�f�������̕�
	int counter = 0;

	std::vector<ValueWithFunc> vwfs;
	auto onChanged = [&](ValueWithFunc& vwf, int position1, int position2) { // ������ꂽ���̏���
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
	}; // ��r�����Ƃ��̏���

	for (int i = 0; i < size; ++i)vwfs.push_back(ValueWithFunc(0, i, onChanged, onCompared));
	setRandValues(vwfs, size);

	while (System::Update()) {
		counter = 0;
		static bool isOpend = false;
		drawValues(vwfs, height, width);

		// �{�^���������ꂽ��\�[�g�̃��X�g��\������
		if (SimpleGUI::Button(U"Sort", Vec2(400, 0)))isOpend = !isOpend;
		if (isOpend)drawButtons(vwfs, counter);

		// �{�^���������ꂽ�烉���_���Ȓl������
		if (SimpleGUI::Button(U"Rand", Vec2(200, 0)))setRandValues(vwfs, (int)vwfs.size());

		if (SimpleGUI::Button(U"�ݒ��ʂɖ߂�", Vec2(600, 0)))return;
	}
}


inline void initSettingPage() {
	// �w�i�𐅐F�ɂ���
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
	if (SimpleGUI::Button(U"�҂����Ԃ�1���₷", Vec2(kButtonWidth, 0)) && sleepTime < 1000)++sleepTime;
	if (SimpleGUI::Button(U"�҂����Ԃ�100���₷", Vec2(kButtonWidth, kButtonHeight))) {
		sleepTime += 100;
		if (sleepTime > 1000)sleepTime = 1000;
	}
	if (SimpleGUI::Button(U"�҂����Ԃ�1���炷", Vec2(kButtonWidth, kButtonHeight * 2)) && 1 < sleepTime)--sleepTime;
	if (SimpleGUI::Button(U"�҂����Ԃ�100���炷", Vec2(kButtonWidth, kButtonHeight * 3))) {
		sleepTime -= 100;
		if (sleepTime < 1)sleepTime = 1;
	}

	kFont(U"�v�f�� : " + ToString(size)).drawAt(kButtonWidth * 3, kButtonHeight * 3);
	kFont(U"�҂����� : " + ToString(sleepTime)).drawAt(kButtonWidth * 3, kButtonHeight * 5);

	if (SimpleGUI::Button(U"�\�[�g��ʂ֍s��", Vec2(kButtonWidth * 2, 0))) {
		sortPage(size, sleepTime);
	}

}



inline void drawChangingElementsCountButton(std::vector<int>& primes, int& size, int& cnt, const int& buttonHeight) {
	if (SimpleGUI::Button(U"�v�f���𑝂₷", Vec2(0, 0))) {
		if (cnt < primes.size() - 1) {
			size *= primes.at(cnt);
			cnt++;
		}
	}
	if (SimpleGUI::Button(U"�v�f�������炷", Vec2(0, buttonHeight))) {
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
