#include <cstdlib>
#include <iostream>
#include <cmath>
#include <cstdio>
#include <ctime>
using namespace std;

void SHUFFLE(int array[]);
void DEAL(int array[], int low, int high);
int PAIR(int array[], int low, int high);
int FLUSH(int array[], int low, int high);
int STRAIGHT(int array[], int low, int high);
int OUT(int i, int j, int k);
void SHOWDOWN(int array[],int score, int score2);

int main()
{
	int poker[52];
	char suit[4][5] = { "梅花", "方塊", "紅心", "黑桃" };
	char number[13][3] = { "２","３","４","５","６","７","８","９","10","Ｊ","Ｑ","Ｋ","Ａ" };
	char out[9][7] = { "雜牌","一對","兩對","三條","順子","同花","葫蘆","鐵枝","同花順" };
	char out2[9][7] = { "雜牌","一對","兩對","三條","順子","同花","葫蘆","鐵枝","同花順" };

	srand((unsigned)time(NULL));

	for (int i = 0; i < 52; i++) {
		poker[i] = i;
	}
	
	SHUFFLE(poker);
	DEAL(poker, 0, 5);
	DEAL(poker, 5, 10);

	int pair = PAIR(poker, 0, 5);
	int pair2 = PAIR(poker, 5, 10);

	int straight = STRAIGHT(poker, 0, 5);
	int straight2 = STRAIGHT(poker, 5, 10);

	int flush = 1 - FLUSH(poker, 0, 5);
	int flush2 = 1 - FLUSH(poker, 5, 10);
	
	int score = OUT(pair, flush, straight);
	int score2 = OUT(pair2, flush2, straight2);

	cout << "參賽者一的牌為" << endl;
	for (int i = 0; i < 5; i++) {
		cout << suit[poker[i] / 13] << number[poker[i] % 13] << " ";
	}
	cout << endl << "牌型為" << out[score] << endl << endl;


	cout << "參賽者二的牌為" << endl;
	for (int i = 5; i < 10; i++) {
		cout << suit[poker[i] / 13] << number[poker[i] % 13] << " ";
	}
	cout << endl << "牌型為" << out[score2] << endl << endl;

	SHOWDOWN(poker,score, score2);

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

int FLUSH(int array[], int low, int high) {
	int F = 0;
	for (int i = low; i < high-1; i++) F = abs(array[i] / 13 - array[i + 1] / 13) + F;
	if (F > 0) F = 1; //F = 0 表示同花, F = 1 表示非同花
	return(F);
}

int STRAIGHT(int array[], int low, int high) { //判斷順子
	int S = 1;
	for (int i = low+1; i < high-1; i++) S = (array[i] % 13 - array[i + 1] % 13) * S;
	if (S == 1 && (array[0] % 13 - array[1] % 13 == 1 || array[0] % 13 - array[1] % 13 == 9)) S = 1;
	else S = 0;//若 S = 1, 表示順子
	return(S);
}

int OUT(int i, int j, int k) { //判斷牌型
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

void SHOWDOWN(int array[],int score, int score2) { //判斷勝負

	int number1=0, number2=0;
	for (int i = 0; i < 5; i++)
		for (int j = i + 1; j < 5; j++)
			if ((array[i] - array[j]) % 13 == 0)
				number1 = array[i];

	for (int i = 5; i < 10; i++)
		for (int j = i + 1; j < 10; j++)
			if ((array[i] - array[j]) % 13 == 0)
				number2 = array[i];

	if (score > score2) { //比牌型
		cout << "玩家一獲勝" << endl << endl;
	}
	else if (score < score2) {
		cout << "玩家二獲勝" << endl << endl;
	}
	else if (number1 % 13 > number2 % 13) { //比對子數字
		cout << "玩家一獲勝" << endl << endl;
	}
	else if (number1 % 13 < number2 % 13) {
		cout << "玩家二獲勝" << endl << endl;
	}
	else if (number1 / 13 > number2 / 13) { //比對子花色
		cout << "玩家一獲勝" << endl << endl;
	}
	else if (number1 / 13 < number2 / 13) {
		cout << "玩家二獲勝" << endl << endl;
	}
	else if (array[0] % 13 > array[5] % 13){ //比單張數字
		cout << "玩家一獲勝" << endl << endl;
	}
	else if (array[0] % 13 < array[5] % 13) {
		cout << "玩家二獲勝" << endl << endl;
	}
	else if (array[0] / 13 > array[5] / 13) { //比單張花色
		cout << "玩家一獲勝" << endl << endl;
	}
	else if (array[0] / 13 < array[5] / 13) {
		cout << "玩家二獲勝" << endl << endl;
	}
	else {
		cout << "出bug了!" << endl;
	}
}