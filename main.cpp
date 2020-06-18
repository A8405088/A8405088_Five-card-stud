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
	char suit[4][5] = { "����", "���", "����", "�®�" };
	char number[13][3] = { "��","��","��","��","��","��","��","��","10","��","��","��","��" };
	char out[9][7] = { "���P","�@��","���","�T��","���l","�P��","��Ī","�K�K","�P�ᶶ" };
	char out2[9][7] = { "���P","�@��","���","�T��","���l","�P��","��Ī","�K�K","�P�ᶶ" };

	cout << "�C�����`�w�w�]��500�A�U�`�п�J500,1000,2000�䤤�@�ӭ�" << endl << endl;

	while (end == 1) { //�^�X�o�P+�U�`�t��
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
			cout << "�Y�A�ǳƦn�F�A�п�J���N�ƶi��o�P�C���A�Q���䧽�A�п�J-1�C";
			cin >> command;
			cout << endl;
			if (command != -1 && mybet != -1) {
				mybet = 0;
				hebet = 0;
				cout << "�A���P��:" << endl << "{ ";
				for (int ti = 0; ti < t + 1; ti++) {
					cout << suit[poker[ti] / 13] << number[poker[ti] % 13] << " ";
				}
				cout << "}" << endl;
				cout << "��⪺�P��:" << endl << "{ " << "���P" << "   ";
				for (int ti = 6; ti < t + 6; ti++) {
					cout << suit[poker[ti] / 13] << number[poker[ti] % 13] << " ";
				}
				cout << "}" << endl << endl;
				if (t >= 1) {
					if (poker[t] % 13 > poker[t + 5] % 13) {					//�A���P�Ʀr�j���⪺�P��
						while (end3 == 1) {
							cout << "�A��o�U�`�v! �ШM�w�U�`���B��: ";
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
									cout << endl << "�п�J500,1000,2000�����B!" << endl;
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
						cout << endl << "����`: " << hebet << endl;
					}
					else if (poker[t] % 13 < poker[t + 5] % 13) {					//��⪺�P�Ʀr�j��A���P��
						cout << "�����o�U�`�v! ���M�w�U�`���B��: ";
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
						cout << "�ШM�w�O�_��`(�Y�Q���䧽�A�п�J-1)�A�A�M�w��`: ";
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
										cout << endl << "�п�J500,1000,2000�����B!" << endl;
										cout << "�ШM�w�O�_��`(�Y�Q���䧽�A�п�J-1)�A�A�M�w��`: ";
										cin >> mybet;
										if (mybet == -1) {
											end3 = 2;
										}
										break;
									}
									if (mybet < hebet) {
										cout << endl << "��`���B���i�C����U�`���B!";
										cout << "�ШM�w�O�_��`(�Y�Q���䧽�A�п�J-1)�A�A�M�w��`: ";
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
					else if (poker[t] / 13 > poker[t + 5] / 13) {					//�A�̪��P�Ʀr�@�ˡA�A���P���j���⪺�P��
						while (end3 == 1) {
							cout << "�A��o�U�`�v! �ШM�w�U�`���B��: ";
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
								cout << endl << "�п�J500,1000,2000�����B!" << endl;
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
						cout << endl << "����`: " << hebet << endl;
					}
					else if (poker[t] / 13 < poker[t + 5] / 13) {					//�A�̪��P�Ʀr�@�ˡA��⪺�P���j��A���P��
						cout << "�����o�U�`�v! ���M�w�U�`���B��: ";
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
						cout << "�ШM�w�O�_��`(�Y�Q���䧽�A�п�J-1)�A�A�M�w��`: ";
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
									cout << endl << "�п�J500,1000,2000�����B!" << endl;
									cout << "�ШM�w�O�_��`(�Y�Q���䧽�A�п�J-1)�A�A�M�w��`: ";
									cin >> mybet;
									if (mybet == -1) {
										end3 = 2;
									}
									break;
								}
								if (mybet < hebet) {
									cout << endl << "��`���B���i�C����U�`���B!";
									cout << "�ШM�w�O�_��`(�Y�Q���䧽�A�п�J-1)�A�A�M�w��`: ";
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
						cout << "�Xbug�F!" << endl;
					}
					cout << "�ثe��`�֭p��: " << sumbet - mybet - hebet << " + " << mybet << " + " << hebet << " = " << sumbet << endl << "�A�|�����B��: " << mymoney << " �A���|�����B��: " << hemoney << endl << endl;
				}
			}
			else {
				cout << "�A���F�䧽!" << endl;
				hemoney += sumbet;
				end2 = 0;
				cout << "�A�ثe���B��: " << mymoney << " �A �����B��: " << hemoney << endl << endl;
				break;
			}
		}
		if (end2 == 1) {
			cout << "�A���P��:" << endl << "{ "; //�̲׵��G
			for (int i = 0; i < 5; i++) {
				cout << suit[poker[i] / 13] << number[poker[i] % 13] << " ";
			}
			cout << "}" << endl << "�P����" << out[score] << endl << endl;


			cout << "��⪺�P��:" << endl << "{ ";
			for (int i = 5; i < 10; i++) {
				cout << suit[poker[i] / 13] << number[poker[i] % 13] << " ";
			}
			cout << "}" << endl << "�P����" << out[score2] << endl << endl;

			vord = SHOWDOWN(poker, score, score2);
			if (vord == 0) {
				cout << "�A��F�䧽!" << endl;
				hemoney += sumbet;
				cout << "�A�ثe���B��: " << mymoney << " �A �����B��: " << hemoney << endl;
			}
			else if (vord == 1) {
				cout << "�AĹ�F�䧽!" << endl;
				mymoney += sumbet;
				cout << "�A�ثe���B��: " << mymoney << " �A �����B��: " << hemoney << endl;
			}
		}

		if (mymoney <= 0) {
			cout << "�A�S���F!�骺�@�Ͻk��!" << endl;
			end = 0;
		}
		else if (hemoney <= 0) {
			cout << "���S���F!�A�Ȩ�½��!" << endl;
			end = 0;
		}
		sumbet = 0;
	}
	system("PAUSE");
	return 0;
}

/******************************************************************************/

void SHUFFLE(int array[]) { //�~�P
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
	for (int i = low; i < high - 1; i++) F = abs(array[i] / 13 - array[i + 1] / 13) + F;
	if (F > 0) F = 1; //F = 0 ��ܦP��, F = 1 ��ܫD�P��
	return(F);
}

int STRAIGHT(int array[], int low, int high) { //�P�_���l
	int S = 1;
	for (int i = low + 1; i < high - 1; i++) S = (array[i] % 13 - array[i + 1] % 13) * S;
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

int SHOWDOWN(int array[], int score, int score2) { //�P�_�ӭt

	int number1 = 0, number2 = 0;
	for (int i = 0; i < 5; i++)
		for (int j = i + 1; j < 5; j++)
			if ((array[i] - array[j]) % 13 == 0)
				number1 = array[i];

	for (int i = 5; i < 10; i++)
		for (int j = i + 1; j < 10; j++)
			if ((array[i] - array[j]) % 13 == 0)
				number2 = array[i];

	if (score > score2) { //��P��
		return 1;
	}
	else if (score < score2) {
		return 0;
	}
	else if (number1 % 13 > number2 % 13) { //���l�Ʀr
		return 1;
	}
	else if (number1 % 13 < number2 % 13) {
		return 0;
	}
	else if (number1 / 13 > number2 / 13) { //���l���
		return 1;
	}
	else if (number1 / 13 < number2 / 13) {
		return 0;
	}
	else if (array[0] % 13 > array[5] % 13) { //���i�Ʀr
		return 1;
	}
	else if (array[0] % 13 < array[5] % 13) {
		return 0;
	}
	else if (array[0] / 13 > array[5] / 13) { //���i���
		return 1;
	}
	else if (array[0] / 13 < array[5] / 13) {
		return 0;
	}
}