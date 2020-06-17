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
	char suit[4][5] = { "����", "���", "����", "�®�" };
	char number[13][3] = { "��","��","��","��","��","��","��","��","10","��","��","��","��" };
	char out[9][7] = { "���P","�@��","���","�T��","���l","�P��","��Ī","�K�K","�P�ᶶ" };
	char out2[9][7] = { "���P","�@��","���","�T��","���l","�P��","��Ī","�K�K","�P�ᶶ" };

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

	cout << "���ɪ̤@���P��" << endl;
	for (int i = 0; i < 5; i++) {
		cout << suit[poker[i] / 13] << number[poker[i] % 13] << " ";
	}
	cout << endl << "�P����" << out[score] << endl << endl;


	cout << "���ɪ̤G���P��" << endl;
	for (int i = 5; i < 10; i++) {
		cout << suit[poker[i] / 13] << number[poker[i] % 13] << " ";
	}
	cout << endl << "�P����" << out[score2] << endl << endl;

	SHOWDOWN(poker,score, score2);

	system("PAUSE");
	return 0;
}

/******************************************************************************/

void SHUFFLE(int array[]) {
	for (int i = 0; i < 52; i++) {
		int j = rand() % 52; //�N���X���üƷ�����, �����Ȫ��ʧ@
		int tmp = array[i];
		array[i] = array[j];
		array[j] = tmp;
	}
}

void DEAL(int array[], int low, int high) { //�ƧǤ�P�j�p
	int temp;
	for (int i = low; i < high; i++)
		for (int j = i + 1; j < high; j++)
			if (array[i] % 13 < array[j] % 13 || (array[i] % 13 == array[j] % 13 && array[i] < array[j]))
			{
				temp = array[i]; array[i] = array[j]; array[j] = temp;
			}
}

int PAIR(int array[], int low, int high) { //�P�_���X��P���I�Ƥ@��
	int P = 0;
	for (int i = low; i < high; i++)
		for (int j = i + 1; j < high; j++)
			if ((array[i] - array[j]) % 13 == 0) P++;
	return(P);
}

int FLUSH(int array[], int low, int high) {
	int F = 0;
	for (int i = low; i < high-1; i++) F = abs(array[i] / 13 - array[i + 1] / 13) + F;
	if (F > 0) F = 1; //F = 0 ��ܦP��, F = 1 ��ܫD�P��
	return(F);
}

int STRAIGHT(int array[], int low, int high) { //�P�_���l
	int S = 1;
	for (int i = low+1; i < high-1; i++) S = (array[i] % 13 - array[i + 1] % 13) * S;
	if (S == 1 && (array[0] % 13 - array[1] % 13 == 1 || array[0] % 13 - array[1] % 13 == 9)) S = 1;
	else S = 0;//�Y S = 1, ��ܶ��l
	return(S);
}

int OUT(int i, int j, int k) { //�P�_�P��
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

void SHOWDOWN(int array[],int score, int score2) { //�P�_�ӭt
	if (score > score2) {
		cout << "���a�@���" << endl << endl;
	}
	else if (score < score2) {
		cout << "���a�G���" << endl << endl;
	}
	else if (array[0] % 13 > array[5] % 13){
		cout << "���a�@���" << endl << endl;
	}
	else if (array[0] % 13 < array[5] % 13) {
		cout << "���a�G���" << endl << endl;
	}
	else if (array[0] / 13 > array[5] / 13) {
		cout << "���a�@���" << endl << endl;
	}
	else if (array[0] / 13 < array[5] / 13) {
		cout << "���a�G���" << endl << endl;
	}
	else {
		cout << "�Xbug�F!" << endl;
	}
}