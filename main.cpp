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
int SHOWDOWN(int array[], int score, int score2);

int main()
{
	srand((unsigned)time(NULL));

	int mymoney = 10000;
	int hemoney = 10000;
	int sumbet = 0;
	int mybet = 0;
	int hebet = 0;
	int deepbet = 500;

	int end = 1;
	int end2 = 1;
	int end3 = 1;
	int vord = 0;
	int command = 0;
	int poker[52];
	char suit[4][5] = { "梅花", "方塊", "紅心", "黑桃" };
	char number[13][3] = { "２","３","４","５","６","７","８","９","10","Ｊ","Ｑ","Ｋ","Ａ" };
	char out[9][7] = { "雜牌","一對","兩對","三條","順子","同花","葫蘆","鐵枝","同花順" };
	char out2[9][7] = { "雜牌","一對","兩對","三條","順子","同花","葫蘆","鐵枝","同花順" };

	cout << "遊戲底注已預設為500，下注請輸入500,1000,2000其中一個值" << endl << endl;

	while (end == 1) { //回合發牌+下注系統
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

		for (int t = 0; t < 5; t++) {
			cout << "若你準備好了，請輸入任意數進行發牌。讓你想放棄賭局，請輸入-1。";
			cin >> command;
			cout << endl;
			if (command != -1 && mybet != -1) {
				mybet = 0;
				hebet = 0;
				cout << "你的牌為:" << endl << "{ ";
				for (int ti = 0; ti < t + 1; ti++) {
					cout << suit[poker[ti] / 13] << number[poker[ti] % 13] << " ";
				}
				cout << "}" << endl;
				cout << "對手的牌為:" << endl << "{ " << "底牌" << "   ";
				for (int ti = 6; ti < t + 6; ti++) {
					cout << suit[poker[ti] / 13] << number[poker[ti] % 13] << " ";
				}
				cout << "}" << endl << endl;
				if (t >= 1) {
					if (poker[t] % 13 > poker[t + 5] % 13) {					//你的牌數字大於對手的牌時
						while (end3 == 1) {
							cout << "你獲得下注權! 請決定下注金額為: ";
							cin >> mybet;
							switch (mybet) {
								case 2000:
									end3 = 0;
									break;
								case 1000:
									end3 = 0;
									break;
								case 500:
									end3 = 0;
									break;
								default:
									cout << endl << "請輸入500,1000,2000的金額!" << endl;
									break;
							}
						}
						end3 = 1;
						mymoney -= mybet;
						while (end3 == 1 || mybet > hebet) {
							hebet = rand() % 5;
							switch (hebet) {
							case 4:
								end3 = 0;
								break;
							case 2:
								end3 = 0;
								break;
							case 1:
								end3 = 0;
								break;
							default:
								break;
							}
							hebet *= 500;
						}
						end3 = 1;
						hemoney -= hebet;
						sumbet += mybet + hebet;
						cout << endl << "對手跟注: " << hebet << endl;
					}
					else if (poker[t] % 13 < poker[t + 5] % 13) {					//對手的牌數字大於你的牌時
						cout << "對手獲得下注權! 對手決定下注金額為: ";
						while (end3 == 1 || mybet > hebet) {
							hebet = rand() % 5;
							switch (hebet) {
							case 4:
								end3 = 0;
								break;
							case 2:
								end3 = 0;
								break;
							case 1:
								end3 = 0;
								break;
							default:
								break;
							}
							hebet *= 500;
						}
						end3 = 1;
						hemoney -= hebet;
						cout << hebet << endl;
						cout << "請決定是否跟注(若想放棄賭局，請輸入-1)，你決定跟注: ";
						cin >> mybet;
						if (mybet == -1) {
							end3 = 2;
						}
							else {
								while (end3 == 1) {
									switch (mybet) {
									case 2000:
										end3 = 0;
										break;
									case 1000:
										end3 = 0;
										break;
									case 500:
										end3 = 0;
										break;
									default:
										cout << endl << "請輸入500,1000,2000的金額!" << endl;
										cout << "請決定是否跟注(若想放棄賭局，請輸入-1)，你決定跟注: ";
										cin >> mybet;
										if (mybet == -1) {
											end3 = 2;
										}
										break;
									}
									if (mybet < hebet) {
										cout << endl << "跟注金額不可低於對手下注金額!";
										cout << "請決定是否跟注(若想放棄賭局，請輸入-1)，你決定跟注: ";
										cin >> mybet;
										if (mybet == -1) {
											end3 = 2;
										}
									}
								}
								if (end3 == 0) {
									mymoney -= mybet;
									sumbet += hebet + mybet;
									cout << endl;
								}
							}
						end3 = 1;
					}
					else if (poker[t] / 13 > poker[t + 5] / 13) {					//你們的牌數字一樣，你的牌花色大於對手的牌時
						while (end3 == 1) {
							cout << "你獲得下注權! 請決定下注金額為: ";
							cin >> mybet;
							switch (mybet) {
							case 2000:
								end3 = 0;
								break;
							case 1000:
								end3 = 0;
								break;
							case 500:
								end3 = 0;
								break;
							default:
								cout << endl << "請輸入500,1000,2000的金額!" << endl;
								break;
							}
						}
						end3 = 1;
						mymoney -= mybet;
						while (end3 == 1 || mybet > hebet) {
							hebet = rand() % 5;
							switch (hebet) {
							case 4:
								end3 = 0;
								break;
							case 2:
								end3 = 0;
								break;
							case 1:
								end3 = 0;
								break;
							default:
								break;
							}
							hebet *= 500;
						}
						end3 = 1;
						hemoney -= hebet;
						sumbet += mybet + hebet;
						cout << endl << "對手跟注: " << hebet << endl;
					}
					else if (poker[t] / 13 < poker[t + 5] / 13) {					//你們的牌數字一樣，對手的牌花色大於你的牌時
						cout << "對手獲得下注權! 對手決定下注金額為: ";
						while (end3 == 1 || mybet > hebet) {
							hebet = rand() % 5;
							switch (hebet) {
							case 4:
								end3 = 0;
								break;
							case 2:
								end3 = 0;
								break;
							case 1:
								end3 = 0;
								break;
							default:
								break;
							}
							hebet *= 500;
						}
						end3 = 1;
						hemoney -= hebet;
						cout << hebet << endl;
						cout << "請決定是否跟注(若想放棄賭局，請輸入-1)，你決定跟注: ";
						cin >> mybet;
						if (mybet == -1) {
							end3 = 2;
						}
						else {
							while (end3 == 1) {
								switch (mybet) {
								case 2000:
									end3 = 0;
									break;
								case 1000:
									end3 = 0;
									break;
								case 500:
									end3 = 0;
									break;
								default:
									cout << endl << "請輸入500,1000,2000的金額!" << endl;
									cout << "請決定是否跟注(若想放棄賭局，請輸入-1)，你決定跟注: ";
									cin >> mybet;
									if (mybet == -1) {
										end3 = 2;
									}
									break;
								}
								if (mybet < hebet) {
									cout << endl << "跟注金額不可低於對手下注金額!";
									cout << "請決定是否跟注(若想放棄賭局，請輸入-1)，你決定跟注: ";
									cin >> mybet;
									if (mybet == -1) {
										end3 = 2;
									}
								}
							}
							if (end3 == 0) {
								mymoney -= mybet;
								sumbet += hebet + mybet;
								cout << endl;
							}
						}
						end3 = 1;
					}
					else {
						cout << "出bug了!" << endl;
					}
					cout << "目前賭注累計為: " << sumbet - mybet - hebet << " + " << mybet << " + " << hebet << " = " << sumbet << endl << "你尚有金額為: " << mymoney << " ，對手尚有金額為: " << hemoney << endl << endl;
				}
			}
			else {
				cout << "你放棄了賭局!" << endl;
				hemoney += sumbet;
				end2 = 0;
				cout << "你目前金額為: " << mymoney << " ， 對手金額為: " << hemoney << endl << endl;
				break;
			}
		}
		if (end2 == 1) {
			cout << "你的牌為:" << endl << "{ "; //最終結果
			for (int i = 0; i < 5; i++) {
				cout << suit[poker[i] / 13] << number[poker[i] % 13] << " ";
			}
			cout << "}" << endl << "牌型為" << out[score] << endl << endl;


			cout << "對手的牌為:" << endl << "{ ";
			for (int i = 5; i < 10; i++) {
				cout << suit[poker[i] / 13] << number[poker[i] % 13] << " ";
			}
			cout << "}" << endl << "牌型為" << out[score2] << endl << endl;

			vord = SHOWDOWN(poker, score, score2);
			if (vord == 0) {
				cout << "你輸了賭局!" << endl;
				hemoney += sumbet;
				cout << "你目前金額為: " << mymoney << " ， 對手金額為: " << hemoney << endl;
			}
			else if (vord == 1) {
				cout << "你贏了賭局!" << endl;
				mymoney += sumbet;
				cout << "你目前金額為: " << mymoney << " ， 對手金額為: " << hemoney << endl;
			}
		}

		if (mymoney <= 0) {
			cout << "你沒錢了!輸的一蹋糊塗!" << endl;
			end = 0;
		}
		else if (hemoney <= 0) {
			cout << "對手沒錢了!你賺到翻掉!" << endl;
			end = 0;
		}
		sumbet = 0;
	}
	system("PAUSE");
	return 0;
}

/******************************************************************************/

void SHUFFLE(int array[]) { //洗牌
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
	for (int i = low; i < high - 1; i++) F = abs(array[i] / 13 - array[i + 1] / 13) + F;
	if (F > 0) F = 1; //F = 0 表示同花, F = 1 表示非同花
	return(F);
}

int STRAIGHT(int array[], int low, int high) { //判斷順子
	int S = 1;
	for (int i = low + 1; i < high - 1; i++) S = (array[i] % 13 - array[i + 1] % 13) * S;
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

int SHOWDOWN(int array[], int score, int score2) { //判斷勝負

	int number1 = 0, number2 = 0;
	for (int i = 0; i < 5; i++)
		for (int j = i + 1; j < 5; j++)
			if ((array[i] - array[j]) % 13 == 0)
				number1 = array[i];

	for (int i = 5; i < 10; i++)
		for (int j = i + 1; j < 10; j++)
			if ((array[i] - array[j]) % 13 == 0)
				number2 = array[i];

	if (score > score2) { //比牌型
		return 1;
	}
	else if (score < score2) {
		return 0;
	}
	else if (number1 % 13 > number2 % 13) { //比對子數字
		return 1;
	}
	else if (number1 % 13 < number2 % 13) {
		return 0;
	}
	else if (number1 / 13 > number2 / 13) { //比對子花色
		return 1;
	}
	else if (number1 / 13 < number2 / 13) {
		return 0;
	}
	else if (array[0] % 13 > array[5] % 13) { //比單張數字
		return 1;
	}
	else if (array[0] % 13 < array[5] % 13) {
		return 0;
	}
	else if (array[0] / 13 > array[5] / 13) { //比單張花色
		return 1;
	}
	else if (array[0] / 13 < array[5] / 13) {
		return 0;
	}
}