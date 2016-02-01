#include <vector>
using std::vector;
typedef unsigned int uint;
void separate(vector<uint> &into, uint num) {

	if (num == 0)
		into.push_back(0);
	else
		into.push_back(1);

	while (num % 2 == 0) {
		into.push_back(2);
		num /= 2;
	}
	uint halfnum = num / 2;
	for (uint i = 3; i <= halfnum; ++i, ++i)
		while (num % i == 0) {

			into.push_back(i);
			num /= i;
		}
}


uint calcBiggestMulti(uint x, uint y) {

	vector<uint> xParts; separate(xParts, x);
	vector<uint> yParts; separate(yParts, y);
	//break x down
	vector<uint> xunter;
	{
		uint tempX = x;

		for (uint i = 2; i <= x / 2; ++i)
			while (tempX % i == 0) {
				xunter.push_back(i);
				std::printf(" %i", i);
				tempX /= i;
			}
	}

	// break y down
	vector<uint> yunter;
	{
		uint tempY = y;
		std::printf("   ");
		for (uint i = 2; i <= y / 2; ++i)
			while (tempY % i == 0) {
				yunter.push_back(i);
				std::printf(" %i", i);
				tempY /= i;
			}

		std::printf("\n");
	}

	const uint sX = (uint)xunter.size();
	const uint sY = (uint)yunter.size();
	if (sX > 0 && sY > 0) {
		vector<uint> gem;
		uint iX = 0;
		uint iY = 0;

		// store same values in gem
		for (; iX < sX && iY < sY;) {
			uint xx = xunter[iX];
			uint yy = yunter[iY];
			if (xx == yy) {
				gem.push_back(xx);
				++iX; ++iY;
			}
			else if (xx < yy)
				++iX;
			else
				++iY;
		}

		// multiply gem values
		uint mul = 1;

		for (uint i = 0; i < gem.size(); ++i) {
			mul *= gem[i];
			std::printf(" %u", gem[i]);
		}
		std::printf("\n");
		return mul;
	}

	return 0;
}


#include <iostream>
using std::cout;
using std::endl;
using std::cin;

int main(int argc, char**argv) {

	char c;

	do {

		uint x, y, result;

		cout << endl << "Calc Biggest Multi";
		cout << endl << "Enter X = "; cin >> x;
		cout << endl << "Enter Y = "; cin >> y;

		result = calcBiggestMulti(x, y);

		cout << endl << "Result = " << result;

		c = 'y';
		cout << endl << "Go again?(y) "; cin >> c;

	} while (c != 'n');

	return 0;
}