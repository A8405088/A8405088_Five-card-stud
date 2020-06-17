#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdio>
#include <ctime>
using namespace std;

void SHUFFLE(int array[]);
void DEAL(int array[], int low, int high);
int PAIR(int array[], int low, int high);
int FLUSH(int array[]);
int STRAIGHT(int array[]);
int OUT(int i, int j, int k);

int main()
{
	int poker[52];
	char suit[4][5] = { "梅花", "方塊", "紅心", "黑桃" };
	char number[13][3] = { "２","３","４","５","６","７","８","９","10","Ｊ","Ｑ","Ｋ","Ａ" };
	char out[9][7] = { "雜牌","一對","兩對","三條","順子","同花","葫蘆","鐵枝","同花順" };

	srand((unsigned)time(NULL));

	for (int i = 0; i < 52; i++) {
		poker[i] = i;
	}

	SHUFFLE(poker);
	DEAL(poker, 0, 5);
	DEAL(poker, 5, 10);

	int pair = PAIR(poker, 0, 5);
	int pair2 = PAIR(poker, 5, 10);

	int straight = STRAIGHT(poker);
	int flush = 1 - FLUSH(poker);
	int score = OUT(pair, flush, straight);

	cout << "參賽者一的牌為" << endl;
	for (int i = 0; i < 5; i++) {
		cout << suit[poker[i] / 13] << number[poker[i] % 13] << " ";
	}
	cout << endl << "牌型為" << out[score] << endl;


	cout << "參賽者二的牌為" << endl;
	for (int i = 5; i < 10; i++) {
		cout << suit[poker[i] / 13] << number[poker[i] % 13] << " ";
	}
	cout << endl << "牌型為" << out[score] << endl;


	system("PAUSE");
	return 0;
}

/******************************************************************************/

void SHUFFLE(int array[]) {
	for (int i = 0; i < 52; i++) {
		int j = rand() % 52; //將取出的亂數當成索引, 做換值的動作
		int tmp = array[i];
		array[i] = array[j];
		array[j] = tmp;
	}
}

void DEAL(int array[], int low, int high) { //排序手牌大小
	int temp;
	for (int i = low; i < high; i++)
		for (int j = i + 1; j < high; j++)
			if (array[i] % 13 < array[j] % 13 || (array[i] % 13 == array[j] % 13 && array[i] < array[j]))
			{
				temp = array[i]; array[i] = array[j]; array[j] = temp;
			}
}

int PAIR(int array[], int low, int high) { //判斷有幾對牌的點數一樣
	int P = 0;
	for (int i = low; i < high; i++)
		for (int j = i + 1; j < high; j++)
			if ((array[i] - array[j]) % 13 == 0) P++;
	return(P);
}

int FLUSH(int array[]) {
	int F = 0;
	for (int i = 0; i < 4; i++) F = abs(array[i] / 13 - array[i + 1] / 13) + F;
	if (F > 0) F = 1; //F = 0 表示同花, F = 1 表示非同花
	return(F);
}

int STRAIGHT(int array[]) { //判斷順子
	int S = 1;
	for (int i = 1; i < 4; i++) S = (array[i] % 13 - array[i + 1] % 13) * S;
	if (S == 1 && (array[0] % 13 - array[1] % 13 == 1 || array[0] % 13 - array[1] % 13 == 9)) S = 1;
	else S = 0;//若 S = 1, 表示順子
	return(S);
}

int OUT(int i, int j, int k) {
	int o;
	switch (i) {
	case 1:
	case 2:
	case 3: o = i; break;
	case 4: o = 6; break;
	case 6: o = 7; break;
	default: switch (10 * j + k) {
	case 11: o = 8; break;
	case 1: o = 4; break;
	case 10: o = 5; break;
	default: o = 0;
	}
	}
	return o;
}