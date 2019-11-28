#include <iostream>
#include "windows.h"
#include <conio.h>
#include <map>
#include <cmath>
#include <string>
#include <LIMITS.H>
#include <set>
#include <iomanip>


using namespace std;

map <char, int> s = {
		{'0', 0},
		{'1', 1},
		{'2', 2},
		{'3', 3},
		{'4', 4},
		{'5', 5},
		{'6', 6},
		{'7', 7},
		{'8', 8},
		{'9', 9},
		{'A', 10},
		{'B', 11},
		{'C', 12},
		{'D', 13},
		{'E', 14},
		{'F', 15},
		{'G', 16},
		{'H', 17},
		{'I', 18},
		{'J', 19},
		{'K', 20},
		{'L', 21},
		{'M', 22},
		{'N', 23},
		{'O', 24},
		{'P', 25},
		{'Q', 26},
		{'R', 27},
		{'S', 28},
		{'T', 29},
		{'U', 30},
		{'V', 31},
		{'W', 32},
		{'X', 33},
		{'Y', 34},
		{'Z', 35},
		{'-', 36},
		
};

template <typename T>
union bites {
	T number = 0;
	char ch[sizeof(T)];
	long long int num;
};

enum ConsoleColor { Black, Blue, Green, LightBlue, Red, Magenta, Yellow, White };

BOOL Line(HDC hdc, int x1, int y1, int x2, int y2) {
	MoveToEx(hdc, x1, y1, NULL);
	return LineTo(hdc, x2, y2);
}


void graphicRender(char* bit, int sizE) {

	
	int* mas = new int[sizE * 8];
	int j = 0, k;
	for (int z = sizE - 1; z >= 0; z--) {
		for (int i = 7; i >= 0; i--) {
			k = bool(bit[z] & (1 << i));
			mas[j] = k;
			j++;
		}
	}



	HWND hWnd = GetConsoleWindow();
	HDC hDc = GetDC(hWnd);
	COLORREF color = RGB(255, 255, 255);
	HPEN pen = CreatePen(PS_SOLID, 1, color);
	SelectObject(hDc, pen);


	color = RGB(255, 255, 255);

	int y = 170;
	
	//Line(hDc, 0, y, 5 * 400, y);

	double period = 6.30;

	for (int i = 0; i < 16; i++) {
		if (mas[i] == 0) {
			color = RGB(0, 0, 255);
			for (double x1 = 0; x1 < period; x1 += 0.01) {
				int y1 = sin(2 * x1) * 20;
				SetPixel(hDc, x1 * 5 + i * 32.75, y - y1, color);
			}
		}
		else {
			color = RGB(255, 0, 0);
			for (double x1 = 0; x1 < period; x1 += 0.01) {
				int y1 = sin(4 * x1) * 20;
				SetPixel(hDc, x1 * 5 + i * 32.75, y - y1, color);

			}
		}
	}







}

void clear() {

	HWND hWnd = GetConsoleWindow();
	HDC hDc = GetDC(hWnd);
	int y = 170;

	COLORREF color = RGB(0, 0, 0);
	HPEN pen = CreatePen(PS_SOLID, 1, color);
	SelectObject(hDc, pen);
	//Line(hDc, 0, y, 5 * 400, y);
	for (int i = 130; i < 200; i++) {
		color = RGB(0, 0, 0);
		Line(hDc, 0, i, 5 * 400, i);
	}


}


void SetColor(int text, int background)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

void gotoxy(int xpos, int ypos)
{
	COORD scrn;

	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);

	scrn.X = xpos; scrn.Y = ypos;

	SetConsoleCursorPosition(hOuput, scrn);
}

void render(int position, bool point, int positionOy) {
	for (int i = 0; i < position-1; i++) {
		gotoxy(i, positionOy);
		cout << point;
		Sleep(5);
		gotoxy(i, positionOy);
		cout << ' ';
	}
	gotoxy(position - 1, positionOy);
	cout << point;
}


void animation(char* bit, int colorForBites, int colorForBackground, int colorForChangesBites, int size, set<int> & numberBites, int positionOy) {

	gotoxy(0, positionOy);
	int positionCount = size * 8;
	for (int z = 0; z < size; z++) {
		for (int i = 0; i < 8; i++) {
			if (numberBites.find(z * 8 + i) != numberBites.end()) {
				SetColor(colorForChangesBites, colorForBackground);
			}
			else {
				SetColor(colorForBites, colorForBackground);
			}
			char g = 1 << i;
			char q = bit[z];
			char simb = 0;
			__asm {
				mov al, q
				mov bl, g
				and al, bl
				mov simb, al
			}
			bool num = (bool)simb;
			render(positionCount--, num, positionOy);
						
		}
	}


	

}


void renderForGraphic(int numSymbol, int OXposition, int OYposition) {
	for (int i = 50; i >= OXposition; i--) {
		gotoxy(i, OYposition);
		cout << (char)numSymbol;
		Sleep(0);
		gotoxy(i, OYposition);
		cout << " ";
	}
	gotoxy(OXposition, OYposition);
	cout << (char)numSymbol;

}


void buildGraphic(char* bit, int sizE) {

	gotoxy(0, 14);
	
	int countOxPosition = 0;
	int* mas = new int[sizE*8];
	int j = 0, k;
	for (int z = sizE - 1; z >= 0; z--) {
		for (int i = 7; i >= 0; i--) {
			k = bool(bit[z] & (1 << i));
			mas[j] = k;
			j++;
		}
	}

	bool flag0 = false, flag1 = false;
	for (int i = 0; i < sizE * 8-1; i++) {

		if (mas[i] == 0) {
			//gotoxy(countOxPosition, 16);
			flag0 = true;
			if (flag1) {
				//cout << (char)192;
				renderForGraphic(192, countOxPosition, 16);
				countOxPosition++;
				flag1 = false;
			}
			else {
				renderForGraphic(196, countOxPosition, 16);
				countOxPosition++;
				//cout << (char)196;

			}
			if (mas[i + 1] == 1) {
				renderForGraphic(217, countOxPosition, 16);
				//countOxPosition++;
				//cout << (char)217;
			}
			else {
				renderForGraphic(196, countOxPosition, 16);
				countOxPosition++;
				//cout << (char)196;
			}

		}
		else {
			//gotoxy(countOxPosition, 15);
			flag1 = true;
			if (flag0) {
				renderForGraphic(218, countOxPosition, 15);
				countOxPosition++;
				//cout << (char)218;
				flag0 = false;
			}
			else {
				renderForGraphic(196, countOxPosition, 15);
				countOxPosition++;
				//cout << (char)196;

			}
			if (mas[i + 1] == 0) {
				renderForGraphic(191, countOxPosition, 15);
				//countOxPosition++;
				//cout << (char)191;
			}
			else {
				renderForGraphic(196, countOxPosition, 15);
				countOxPosition++;
				//cout << (char)196;
			}
		
		}

		

	}
	if (mas[sizE * 8 - 1] == 0){
		gotoxy(countOxPosition, 16);
		if (flag1) {
			renderForGraphic(192, countOxPosition, 16);
			countOxPosition++;
			renderForGraphic(196, countOxPosition, 16);
			//cout << (char)192 << (char)196;
		}
		else {
			//cout << (char)196 << (char)196;
			renderForGraphic(196, countOxPosition, 16);
			countOxPosition++;
			renderForGraphic(196, countOxPosition, 16);
		}
	}
	else {
		gotoxy(countOxPosition, 15);
		if (flag0) {
			renderForGraphic(218, countOxPosition, 15);
			countOxPosition++;
			renderForGraphic(196, countOxPosition, 15);
			//cout << (char)218 << (char)196;
		}
		else {
			renderForGraphic(196, countOxPosition, 15);
			countOxPosition++;
			renderForGraphic(196, countOxPosition, 15);
			//cout << (char)196 << (char)196;
		}
	}

	gotoxy(0, 16);
}


void translateOnTypeOfData(int* numberInMass, int typeOfData, int numberSystem, int counterNumber, bool negativeFlag, int* factionalMass, int counterFactionalNumber,int colorForChangesBites, int colorForBackground, int colorForBites) {
	gotoxy(6, 5);
	bool lastNum;
	int count = 0;
	
	if (typeOfData == 1) {
		bites <short int> bit;
		bit.number = 0;
		
		for (int i = 0, j = counterNumber-1; i < counterNumber; i++, j--) {
			bit.number += (numberInMass[i] * pow(numberSystem, j));
		}
		if (negativeFlag) {
			//bit.number*=-1;
			__asm {
				mov ax, bit.number
				neg ax
				mov bit.number, ax
			}
		}
		cout << endl << "In 10 system: " <<  bit.number << endl;


		set <int> numberBites;

		animation(bit.ch, colorForBites, colorForBackground, colorForChangesBites, sizeof(short int), numberBites, 7);
		
		
		
		for (int z = sizeof(short int) - 1; z >= 0; z--) {
			for (int i = 7; i >= 0; i--) {
				if (z == 1 && i == 7) {
					//lastNum = bool(bit.ch[z] & (1 << i));
					char g = 1 << i;
					char q = bit.ch[z];
					char simb = 0;
					__asm {
						mov al, q
							mov bl, g
							and al, bl
							mov simb, al
					}
					lastNum = (bool)simb;
				}
				else {
					if (bool(bit.ch[z] & (1 << i)) != lastNum) {
						count++;
						numberBites.insert(z*8+i);
						numberBites.insert(z*8 + i+1);
						//lastNum = bool(bit.ch[z] & (1 << i));
						char g = 1 << i;
						char q = bit.ch[z];
						char simb = 0;
						__asm {
							mov al, q
							mov bl, g
							and al, bl
							mov simb, al
						}
						lastNum = (bool)simb;
					}
					else{
						//lastNum = bool(bit.ch[z] & (1 << i));
						char g = 1 << i;
						char q = bit.ch[z];
						char simb = 0;
						__asm {
							mov al, q
							mov bl, g
							and al, bl
							mov simb, al
						}
						lastNum = (bool)simb;
					}
				}
			}
		}

		for (auto now : numberBites) {
			bit.number = (bit.number & (1 << now)) ? (bit.number & ~(1 << now)) : (bit.number | (1 << now));
		}


		cout << endl << endl;

	
		animation(bit.ch, colorForBites, colorForBackground, colorForChangesBites, sizeof(short int), numberBites, 9);


		SetColor(White, colorForBackground);
		cout << endl;
		cout << "cout = " << count << " new number = " << bit.number;
		
	
		graphicRender(bit.ch, sizeof(short int));
		//buildGraphic(bit.ch, sizeof(short int));

	}
	// unsigned short int
	else if (typeOfData == 2) {
		bites <unsigned short int> bit;
		bit.number = 0;
		for (int i = 0, j = counterNumber - 1; i < counterNumber; i++, j--) {
			bit.number += (numberInMass[i] * pow(numberSystem, j));
		}

		cout << endl << "In 10 system: " << bit.number << endl;
		
		set <int> numberBites;

		animation(bit.ch, colorForBites, colorForBackground, colorForChangesBites, sizeof(short int), numberBites, 7);

		
		for (int z = sizeof(unsigned short int) - 1; z >= 0; z--) {
			for (int i = 7; i >= 0; i--) {
				if (z == 1 && i == 7) {
					//lastNum = bool(bit.ch[z] & (1 << i));
					char g = 1 << i;
					char q = bit.ch[z];
					char simb = 0;
					__asm {
						mov al, q
						mov bl, g
						and al, bl
						mov simb, al
					}
					lastNum = (bool)simb;
				}
				else {
					if (bool(bit.ch[z] & (1 << i)) != lastNum) {
						count++;
						numberBites.insert(z * 8 + i);
						numberBites.insert(z * 8 + i + 1);
						//lastNum = bool(bit.ch[z] & (1 << i));
						char g = 1 << i;
						char q = bit.ch[z];
						char simb = 0;
						__asm {
							mov al, q
							mov bl, g
							and al, bl
							mov simb, al
						}
						lastNum = (bool)simb;
					}
					else {
						//lastNum = bool(bit.ch[z] & (1 << i));
						char g = 1 << i;
						char q = bit.ch[z];
						char simb = 0;
						__asm {
							mov al, q
							mov bl, g
							and al, bl
							mov simb, al
						}
						lastNum = (bool)simb;
					}
				}
			}
		}
		for (auto now : numberBites) {
			bit.number = (bit.number & (1 << now)) ? (bit.number & ~(1 << now)) : (bit.number | (1 << now));
		}


		cout << endl << endl;
		
		animation(bit.ch, colorForBites, colorForBackground, colorForChangesBites, sizeof(short int), numberBites, 9);

		SetColor(White, colorForBackground);
		cout << endl;
		cout << "cout = " << count << " new number = " << bit.number;

		buildGraphic(bit.ch, sizeof(short int));
	}
	// int
	else if (typeOfData == 3) {
		
		bites <int> bit;
		bit.number = 0;
		for (int i = 0, j = counterNumber - 1; i < counterNumber; i++, j--) {
			bit.number += (numberInMass[i] * pow(numberSystem, j));
		}
		if (negativeFlag) {
			//bit.number *= -1;
			__asm {
				mov eax, bit.number
				neg eax
				mov bit.number, eax
			}
		}
		cout << endl << "In 10 system: " << bit.number << endl;
		
		
		
		
		set <int> numberBites;

		animation(bit.ch, colorForBites, colorForBackground, colorForChangesBites, sizeof(int), numberBites, 7);

		for (int z = sizeof(int) - 1; z >= 0; z--) {
			for (int i = 7; i >= 0; i--) {
				if (z == 3 && i == 7) {
					//lastNum = bool(bit.ch[z] & (1 << i));
					char g = 1 << i;
					char q = bit.ch[z];
					char simb = 0;
					__asm {
						mov al, q
						mov bl, g
						and al, bl
						mov simb, al
					}
					lastNum = (bool)simb;
				}
				else {
					if (bool(bit.ch[z] & (1 << i)) != lastNum) {
						count++;
						numberBites.insert(z * 8 + i);
						numberBites.insert(z * 8 + i + 1);
						//lastNum = bool(bit.ch[z] & (1 << i));
						char g = 1 << i;
						char q = bit.ch[z];
						char simb = 0;
						__asm {
							mov al, q
							mov bl, g
							and al, bl
							mov simb, al
						}
						lastNum = (bool)simb;
					}
					else {
						//lastNum = bool(bit.ch[z] & (1 << i));
						char g = 1 << i;
						char q = bit.ch[z];
						char simb = 0;
						__asm {
							mov al, q
							mov bl, g
							and al, bl
							mov simb, al
						}
						lastNum = (bool)simb;
					}
				}
			}
		}
		for (auto now : numberBites) {
			bit.number = (bit.number & (1 << now)) ? (bit.number & ~(1 << now)) : (bit.number | (1 << now));
		}


		cout << endl << endl;
		
		animation(bit.ch, colorForBites, colorForBackground, colorForChangesBites, sizeof(int), numberBites, 9);

		SetColor(White, colorForBackground);
		cout << endl;
		cout << "cout = " << count << " new number = " << bit.number;

		buildGraphic(bit.ch, sizeof(int));

	}
	// unsigned int
	else if (typeOfData == 4) {
		
		bites<unsigned int> bit;
		bit.number = 0;
		for (int i = 0, j = counterNumber - 1; i < counterNumber; i++, j--) {
			bit.number += (numberInMass[i] * pow(numberSystem, j));
		}
		cout << endl << "In 10 system: " << bit.number << endl;


		set <int> numberBites;

		animation(bit.ch, colorForBites, colorForBackground, colorForChangesBites, sizeof(int), numberBites, 7);

		for (int z = sizeof(unsigned int) - 1; z >= 0; z--) {
			for (int i = 7; i >= 0; i--) {
				if (z == 3 && i == 7) {
					//lastNum = bool(bit.ch[z] & (1 << i));
					char g = 1 << i;
					char q = bit.ch[z];
					char simb = 0;
					__asm {
						mov al, q
						mov bl, g
						and al, bl
						mov simb, al
					}
					lastNum = (bool)simb;
				}
				else {
					if (bool(bit.ch[z] & (1 << i)) != lastNum) {
						count++;
						numberBites.insert(z * 8 + i);
						numberBites.insert(z * 8 + i + 1);
						//lastNum = bool(bit.ch[z] & (1 << i));
						char g = 1 << i;
						char q = bit.ch[z];
						char simb = 0;
						__asm {
							mov al, q
							mov bl, g
							and al, bl
							mov simb, al
						}
						lastNum = (bool)simb;
					}
					else {
						//lastNum = bool(bit.ch[z] & (1 << i));
						char g = 1 << i;
						char q = bit.ch[z];
						char simb = 0;
						__asm {
							mov al, q
							mov bl, g
							and al, bl
							mov simb, al
						}
						lastNum = (bool)simb;
					}
				}
			}
		}
		for (auto now : numberBites) {
			
			bit.number = (bit.number & (1 << now)) ? (bit.number & ~(1 << now)) : (bit.number | (1 << now));
		}


		cout << endl << endl;
		
		animation(bit.ch, colorForBites, colorForBackground, colorForChangesBites, sizeof(int), numberBites, 9);

		SetColor(White, colorForBackground);
		cout << endl;
		cout << "cout = " << count << " new number = " << bit.number;

		buildGraphic(bit.ch, sizeof(int));
		
	}
	// double
	else if (typeOfData == 5) {
		bites<double> bit;
		bit.number = 0;
		for (int i = 0, j = counterNumber - 1; i < counterNumber; i++, j--) {
			bit.number += (numberInMass[i] * pow(numberSystem, j));
		}
		for (int i = 0, j = - 1; i < counterFactionalNumber; i++, j--) {
			bit.number += (factionalMass[i] * pow(numberSystem, j));
		}
		if (negativeFlag) {
			bit.number *= -1;
		}

		
		
		cout << endl << "In 10 system: " <<  setprecision(counterFactionalNumber + counterNumber) << bit.number << endl;
	
		
		set <int> numberBites;

		animation(bit.ch, colorForBites, colorForBackground, colorForChangesBites, sizeof(double), numberBites, 7);

		long long int a = 1;
		cout << endl;
		for (int z = sizeof(double) - 1; z >= 0; z--) {
			for (int i = 7; i >= 0; i--) {
				if (z == 7 && i == 7) {
					//lastNum = bool(bit.ch[z] & (a << i));
					char g = 1 << i;
					char q = bit.ch[z];
					char simb = 0;
					__asm {
						mov al, q
						mov bl, g
						and al, bl
						mov simb, al
					}
					lastNum = (bool)simb;
					
				}
				else {
					if (bool(bit.ch[z] & (a << i)) != lastNum) {
						count++;
						numberBites.insert(z * 8 + i + 1);
						numberBites.insert(z * 8 + i);
						//lastNum = bool(bit.ch[z] & (a << i));
						char g = 1 << i;
						char q = bit.ch[z];
						char simb = 0;
						__asm {
							mov al, q
							mov bl, g
							and al, bl
							mov simb, al
						}
						lastNum = (bool)simb;
						
					}
					else {
						//lastNum = bool(bit.ch[z] & (a << i));
						char g = 1 << i;
						char q = bit.ch[z];
						char simb = 0;
						__asm {
							mov al, q
							mov bl, g
							and al, bl
							mov simb, al
						}
						lastNum = (bool)simb;
						
					}
				}
			}
		}
		
		for (auto now : numberBites) {
			bit.num = (bit.num& (a << now)) ? (bit.num & ~(a << now)) : (bit.num | (a << now));
		}


		cout << endl << endl;
		
		animation(bit.ch, colorForBites, colorForBackground, colorForChangesBites, sizeof(double), numberBites, 9);

		SetColor(White, colorForBackground);
		cout << endl;
		cout << "cout = " << count << " new number = " << bit.number;

		buildGraphic(bit.ch, sizeof(double));

	}
	//long double
	else if (typeOfData == 6) {
		
		bites<long double> bit;
		bit.number = 0;
		for (int i = 0, j = counterNumber - 1; i < counterNumber; i++, j--) {
			bit.number += (numberInMass[i] * pow(numberSystem, j));
		}
		for (int i = 0, j = -1; i < counterFactionalNumber; i++, j--) {
			bit.number += (factionalMass[i] * pow(numberSystem, j));
		}
		if (negativeFlag) {
			bit.number *= -1;
		}

		cout << endl << "In 10 system: " << setprecision(counterFactionalNumber + counterNumber) << bit.number << endl;


		set <int> numberBites;

		animation(bit.ch, colorForBites, colorForBackground, colorForChangesBites, sizeof(long double), numberBites, 7);

		long long int a = 1;
		cout << endl;
		for (int z = sizeof(double) - 1; z >= 0; z--) {
			for (int i = 7; i >= 0; i--) {
				if (z == 7 && i == 7) {
					//lastNum = bool(bit.ch[z] & (a << i));
					char g = 1 << i;
					char q = bit.ch[z];
					char simb = 0;
					__asm {
						mov al, q
						mov bl, g
						and al, bl
						mov simb, al
					}
					lastNum = (bool)simb;

				}
				else {
					if (bool(bit.ch[z] & (a << i)) != lastNum) {
						count++;
						numberBites.insert(z * 8 + i + 1);
						numberBites.insert(z * 8 + i);
						//lastNum = bool(bit.ch[z] & (a << i));
						char g = 1 << i;
						char q = bit.ch[z];
						char simb = 0;
						__asm {
							mov al, q
							mov bl, g
							and al, bl
							mov simb, al
						}
						lastNum = (bool)simb;

					}
					else {
						//lastNum = bool(bit.ch[z] & (a << i));
						char g = 1 << i;
						char q = bit.ch[z];
						char simb = 0;
						__asm {
							mov al, q
							mov bl, g
							and al, bl
							mov simb, al
						}
						lastNum = (bool)simb;

					}
				}
			}
		}

		for (auto now : numberBites) {
			bit.num = (bit.num & (a << now)) ? (bit.num & ~(a << now)) : (bit.num | (a << now));
		}


		cout << endl << endl;
	
		animation(bit.ch, colorForBites, colorForBackground, colorForChangesBites, sizeof(long double), numberBites, 9);

		SetColor(White, Black);
		cout << endl;
		cout << "cout = " << count << " new number = " << bit.number;

		buildGraphic(bit.ch, sizeof(long double));

	}
	//float 
	else if (typeOfData == 7) {
		
		bites<float> bit;
		bit.number = 0;
		for (int i = 0, j = counterNumber - 1; i < counterNumber; i++, j--) {
			bit.number += (numberInMass[i] * pow(numberSystem, j));
		}
		for (int i = 0, j = -1; i < counterFactionalNumber; i++, j--) {
			bit.number += (factionalMass[i] * pow(numberSystem, j));
		}
		if (negativeFlag) {
			bit.number *= -1;
		}

		cout << endl << "In 10 system: " << setprecision(counterFactionalNumber + counterNumber) << bit.number << endl;
		
		
		

		set <int> numberBites;

		animation(bit.ch, colorForBites, colorForBackground, colorForChangesBites, sizeof(float), numberBites, 7);

		long long int a = 1;
		for (int z = sizeof(float) - 1; z >= 0; z--) {
			for (int i = 7; i >= 0; i--) {
				if (z == 3 && i == 7) {
					//lastNum = bool(bit.ch[z] & (a << i));
					char g = 1 << i;
					char q = bit.ch[z];
					char simb = 0;
					__asm {
						mov al, q
						mov bl, g
						and al, bl
						mov simb, al
					}
					lastNum = (bool)simb;
				}
				else {
					if (bool(bit.ch[z] & (a << i)) != lastNum) {
						count++;
						numberBites.insert(z * 8 + i + 1);
						numberBites.insert(z * 8 + i);
						//lastNum = bool(bit.ch[z] & (a << i));
						char g = 1 << i;
						char q = bit.ch[z];
						char simb = 0;
						__asm {
							mov al, q
							mov bl, g
							and al, bl
							mov simb, al
						}
						lastNum = (bool)simb;
					}
					else {
						//lastNum = bool(bit.ch[z] & (a << i));
						char g = 1 << i;
						char q = bit.ch[z];
						char simb = 0;
						__asm {
							mov al, q
							mov bl, g
							and al, bl
							mov simb, al
						}
						lastNum = (bool)simb;
					}
				}
			}
		}

		for (auto now : numberBites) {
			bit.num = (bit.num & (a << now)) ? (bit.num & ~(a << now)) : (bit.num | (a << now));
		}


		cout << endl << endl;
		
		animation(bit.ch, colorForBites, colorForBackground, colorForChangesBites, sizeof(float), numberBites, 9);

		SetColor(White, colorForBackground);
		cout << endl;
		cout << "cout = " << count << " new number = " << bit.number;
		
		buildGraphic(bit.ch, sizeof(float));

	}
	//char
	else if (typeOfData == 8) {
		bites<char> bit;
		bit.number = 0;
		for (int i = 0, j = counterNumber - 1; i < counterNumber; i++, j--) {
			bit.number += (numberInMass[i] * pow(numberSystem, j));
		}
		if (negativeFlag) {
			bit.number *= -1;
		}

		cout << endl << "In 10 sustem: "<< (int)bit.number << " Symbol: " << bit.number << endl;


		set <int> numberBites;

		animation(bit.ch, colorForBites, colorForBackground, colorForChangesBites, sizeof(char), numberBites, 7);

		long long int a = 1;
		for (int z = sizeof(char) - 1; z >= 0; z--) {
			for (int i = 7; i >= 0; i--) {
				if (i == 7) {
					//lastNum = bool(bit.ch[z] & (a << i));
					char g = 1 << i;
					char q = bit.ch[z];
					char simb = 0;
					__asm {
						mov al, q
						mov bl, g
						and al, bl
						mov simb, al
					}
					lastNum = (bool)simb;
				}
				else {
					if (bool(bit.ch[z] & (a << i)) != lastNum) {
						count++;
						numberBites.insert(z * 8 + i + 1);
						numberBites.insert(z * 8 + i);
						//lastNum = bool(bit.ch[z] & (a << i));
						char g = 1 << i;
						char q = bit.ch[z];
						char simb = 0;
						__asm {
							mov al, q
							mov bl, g
							and al, bl
							mov simb, al
						}
						lastNum = (bool)simb;
					}
					else {
						//lastNum = bool(bit.ch[z] & (a << i));
						char g = 1 << i;
						char q = bit.ch[z];
						char simb = 0;
						__asm {
							mov al, q
							mov bl, g
							and al, bl
							mov simb, al
						}
						lastNum = (bool)simb;
					}
				}
			}
		}

		for (auto now : numberBites) {
			bit.num = (bit.num & (a << now)) ? (bit.num & ~(a << now)) : (bit.num | (a << now));
		}


		cout << endl << endl;
		
		animation(bit.ch, colorForBites, colorForBackground, colorForChangesBites, sizeof(char), numberBites, 9);

		SetColor(White, colorForBackground);
		cout << endl;
		cout << "cout = " << count << " new number = " << (int) bit.number << "new symbol: " << bit.number;
				
		buildGraphic(bit.ch, sizeof(char));
		
	}
	// unsigned char
	else if (typeOfData == 9) {
		bites<unsigned char> bit;
		bit.number = 0;
		for (int i = 0, j = counterNumber - 1; i < counterNumber; i++, j--) {
			bit.number += (numberInMass[i] * pow(numberSystem, j));
		}
		
		cout << endl << "In 10 sustem: " << (int)bit.number << " Symbol: " << bit.number << endl;
		
		

		set <int> numberBites;

		animation(bit.ch, colorForBites, colorForBackground, colorForChangesBites, sizeof(char), numberBites, 7);

		long long int a = 1;
		for (int z = sizeof(char) - 1; z >= 0; z--) {
			for (int i = 7; i >= 0; i--) {
				if (i == 7) {
					//lastNum = bool(bit.ch[z] & (a << i));
					char g = 1 << i;
					char q = bit.ch[z];
					char simb = 0;
					__asm {
						mov al, q
						mov bl, g
						and al, bl
						mov simb, al
					}
					lastNum = (bool)simb;
				}
				else {
					if (bool(bit.ch[z] & (a << i)) != lastNum) {
						count++;
						numberBites.insert(z * 8 + i + 1);
						numberBites.insert(z * 8 + i);
						//lastNum = bool(bit.ch[z] & (a << i));
						char g = 1 << i;
						char q = bit.ch[z];
						char simb = 0;
						__asm {
							mov al, q
							mov bl, g
							and al, bl
							mov simb, al
						}
						lastNum = (bool)simb;
					}
					else {
						//lastNum = bool(bit.ch[z] & (a << i));
						char g = 1 << i;
						char q = bit.ch[z];
						char simb = 0;
						__asm {
							mov al, q
							mov bl, g
							and al, bl
							mov simb, al
						}
						lastNum = (bool)simb;
					}
				}
			}
		}

		for (auto now : numberBites) {
			bit.num = (bit.num & (a << now)) ? (bit.num & ~(a << now)) : (bit.num | (a << now));
		}


		cout << endl << endl;

		animation(bit.ch, colorForBites, colorForBackground, colorForChangesBites, sizeof(char), numberBites, 9);

		SetColor(White, colorForBackground);
		cout << endl;
		cout << "cout = " << count << " new number = " << (int) bit.number << "new symbol: " << bit.number;
		
		buildGraphic(bit.ch, sizeof(char));

	}
	

	cout << endl;
	system("pause");
	clear();
	
}

bool cheakTypeOfData(int* numberInMass, int typeOfData, int numberSystem, int counterNumber, bool negativeFlag, int* factionalMass, int counterFactionalNumber) {
	if (typeOfData == 1) {
		
		short int number = 0, maxValue = SHRT_MAX, minValue = SHRT_MIN;
		
		
		for (int i = 0, j = counterNumber - 1; i < counterNumber; i++, j--) {
			
			if (number + (numberInMass[i] * pow(numberSystem, j)) > maxValue && !negativeFlag) {
				return true;
			}
			else if (number + (numberInMass[i] * pow(numberSystem, j)) > maxValue+1 && negativeFlag) {
				return true;
			}
			else {
				number += (numberInMass[i] * pow(numberSystem, j));
			}
		}
	
	}
	else if (typeOfData == 2) {
		unsigned short int number = 0, maxValue = USHRT_MAX;
		


		for (int i = 0, j = counterNumber - 1; i < counterNumber; i++, j--) {

			if (number + (numberInMass[i] * pow(numberSystem, j)) > maxValue && !negativeFlag) {
				return true;
			}
			else {
				number += (numberInMass[i] * pow(numberSystem, j));
			}
		}
	}
	else if (typeOfData == 3) {

		int number = 0, maxValue = 2147483646, minValue = INT_MIN;

		


		for (int i = 0, j = counterNumber - 1; i < counterNumber; i++, j--) {

			if (number + (numberInMass[i] * pow(numberSystem, j)) > maxValue && !negativeFlag) {
				return true;
			}
			else if (number + (numberInMass[i] * pow(numberSystem, j)) > maxValue + 1 && negativeFlag) {
				return true;
			}
			else {
				number += (numberInMass[i] * pow(numberSystem, j));
			}
		}
	}
	else if (typeOfData == 4) {

		unsigned int number = 0, maxValue = UINT_MAX;
	


		for (int i = 0, j = counterNumber - 1; i < counterNumber; i++, j--) {

			if (number + (numberInMass[i] * pow(numberSystem, j)) > maxValue && !negativeFlag) {
				return true;
			}
			else {
				number += (numberInMass[i] * pow(numberSystem, j));
			}
		}
	}
	else if (typeOfData == 5) {
		double number = 0, maxValue = DBL_MAX, minValue = DBL_MIN;
		
	


		for (int i = 0, j = counterNumber - 1; i < counterNumber; i++, j--) {

			if (number + (numberInMass[i] * pow(numberSystem, j)) > maxValue && !negativeFlag) {
				return true;
			}
			else if (number + (numberInMass[i] * pow(numberSystem, j)) > maxValue + 1 && negativeFlag) {
				return true;
			}
			else {
				number += (numberInMass[i] * pow(numberSystem, j));
			}
		}

	}
	else if (typeOfData == 6) {

		long double number = 0, maxValue = LDBL_MAX, minValue = LDBL_MIN;
		


		for (int i = 0, j = counterNumber - 1; i < counterNumber; i++, j--) {

			if (number + (numberInMass[i] * pow(numberSystem, j)) > maxValue && !negativeFlag) {
				return true;
			}
			else if (number + (numberInMass[i] * pow(numberSystem, j)) > maxValue + 1 && negativeFlag) {
				return true;
			}
			else {
				number += (numberInMass[i] * pow(numberSystem, j));
			}
		};

	}
	else if (typeOfData == 7) {
		float number  = 0, maxValue = FLT_MAX, minValue = FLT_MIN;
		


		for (int i = 0, j = counterNumber - 1; i < counterNumber; i++, j--) {

			if (number + (numberInMass[i] * pow(numberSystem, j)) > maxValue && !negativeFlag) {
				return true;
			}
			else if (number + (numberInMass[i] * pow(numberSystem, j)) > maxValue + 1 && negativeFlag) {
				return true;
			}
			else {
				number += (numberInMass[i] * pow(numberSystem, j));
			}
		}


	}
	else if (typeOfData == 8) {
		char number = 0, maxValue = CHAR_MAX, minValue = CHAR_MIN;;
		
		


		for (int i = 0, j = counterNumber - 1; i < counterNumber; i++, j--) {

			if (number + (numberInMass[i] * pow(numberSystem, j)) > maxValue && !negativeFlag) {
				return true;
			}
			else if (number + (numberInMass[i] * pow(numberSystem, j)) > maxValue + 1 && negativeFlag) {
				return true;
			}
			else {
				number += (numberInMass[i] * pow(numberSystem, j));
			}
		}
	}
	else if (typeOfData == 9) {

		unsigned char number = 0, maxValue = UCHAR_MAX;
		


		for (int i = 0, j = counterNumber - 1; i < counterNumber; i++, j--) {

			if (number + (numberInMass[i] * pow(numberSystem, j)) > maxValue && !negativeFlag) {
				return true;
			}
			else {
				number += (numberInMass[i] * pow(numberSystem, j));
			}
		}
	}
	else if (typeOfData == 10) {
		short int number = 0, maxValue = UCHAR_MAX;


		for (int i = 0, j = counterNumber - 1; i < counterNumber; i++, j--) {

			if (number + (numberInMass[i] * pow(numberSystem, j)) > maxValue && !negativeFlag) {
				return true;
			}
			else {
				number += (numberInMass[i] * pow(numberSystem, j));
			}
		}

		
	}



	return false;
}

void input(int numberSystem, int typeOfData, int colorForChangesBites, int colorForBackground, int colorForBites) {
	system("cls");
	cout << "ENTER NUMBER" << endl;
	string availableCharacters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	cout << "Available Characters: -." ;
	for (int i = 0; i < numberSystem; i++) {
		cout << availableCharacters[i];
	}
	cout << endl;
	int keyNumber = _getch();
	int numberInMass[2000];
	int factionalMass[2000];
	int counterNumber = 0;
	int counterFactionalNumber = 0;
	bool negativeFlag = false;
	bool factionalFlag = false;
	//system("cls");
	bool typeOwerflow = false;
	while (keyNumber != 13) {

		if (s.find((char)keyNumber) != s.end() && s[(char)keyNumber] < numberSystem && !factionalFlag) {
			gotoxy(0, 5);
			cout << "                                              ";
			gotoxy(counterNumber+1, 4);
			cout << (char)keyNumber;
			/*gotoxy(0, 4);
			cout << "                                             ";*/
			numberInMass[counterNumber] = s[(char)keyNumber];
			counterNumber++;
		}
		else if (s.find((char)keyNumber) != s.end() && s[(char)keyNumber] < numberSystem && factionalFlag) {
			gotoxy(0, 5); 
			cout << "                                               ";
			gotoxy(counterNumber + counterFactionalNumber + 2, 4);
			cout << (char)keyNumber;
			/*gotoxy(0, 4);
			cout << "                                             ";*/
			factionalMass[counterFactionalNumber] = s[(char)keyNumber];
			counterFactionalNumber++;
		}
		else if (keyNumber == 45) {
			negativeFlag = true;
			gotoxy(counterNumber, 4);
			//system("cls");
			cout << "-";
		}
		else if (keyNumber == 46) {
			factionalFlag = true;
			gotoxy(counterNumber+1, 4);
			cout << ".";
		}
		else {
			gotoxy(0, 5);
			cout << "there is no such symbol in this number system";
		}

		if (cheakTypeOfData(numberInMass, typeOfData, numberSystem, counterNumber, negativeFlag, factionalMass, counterFactionalNumber)) {
			gotoxy(counterNumber + counterFactionalNumber + 1, 4);
			cout << endl << "ERROR";
			system("pause");
			typeOwerflow = true;
			break;
		}


		keyNumber = _getch();
	}
	if (!typeOwerflow) {
		translateOnTypeOfData(numberInMass, typeOfData, numberSystem, counterNumber, negativeFlag, factionalMass, counterFactionalNumber, colorForChangesBites, colorForBackground, colorForBites);
	}

}

int choiceParamMenu() {
	

	cout << endl;
	cout << "short int" << endl;
	cout << "unsigned short int" << endl;
	cout << "int" << endl;
	cout << "unsigned int" << endl;
	cout << "double" << endl;
	cout << "long double" << endl;
	cout << "float" << endl;
	cout << "char" << endl;
	cout << "unsigned char" << endl;
	cout << "color for change bites" << endl;
	cout << "color for background " << endl;
	cout << "color for bites " << endl;
	cout << "exit";


	int positionOnArrow = 1;



	while (true) {
		

		gotoxy(24, positionOnArrow);

		cout << "<----";

		int keyNumber = _getch();

		gotoxy(24, positionOnArrow);

		cout << "     ";

		if (keyNumber == 224) {
			int temp = _getch();
			if (temp == 72) {
			
				if (positionOnArrow == 1) {
					positionOnArrow = 13;
				}
				else {
					positionOnArrow--;
				}
			}
			else if(temp == 80) {
				if (positionOnArrow == 13) {
					positionOnArrow = 1;
				}
				else {
					positionOnArrow++;
				}
			}
		}
		else if (keyNumber == 13) {
			return positionOnArrow;
		}

		

		
	}
	
	
	
}

int choiceSystemNumber() {
	
	int systemNumber;
	do {
		system("cls");
		cout << "ENTER THE SYSTEM NUMBER(2-35): ";
		cin >> systemNumber;

	} while (systemNumber >= 36 || systemNumber <= 1);

	
	return systemNumber;

}

int choiceColor() {
	system("cls");

	//cout << endl;
	cout << "Black" << endl;
	cout << "Blue" << endl;
	cout << "Green" << endl;
	cout << "LightBlue" << endl;
	cout << "Red" << endl;
	cout << "Magenta" << endl;
	cout << "Yellow" << endl;
	cout << "White" << endl;


	int positionOnArrow = 0;



	while (true) {


		gotoxy(10, positionOnArrow);

		cout << "<----";

		int keyNumber = _getch();

		gotoxy(10, positionOnArrow);

		cout << "     ";

		if (keyNumber == 224) {
			int temp = _getch();
			if (temp == 72) {

				if (positionOnArrow == 0) {
					positionOnArrow = 7;
				}
				else {
					positionOnArrow--;
				}
			}
			else if (temp == 80) {
				if (positionOnArrow == 7) {
					positionOnArrow = 0;
				}
				else {
					positionOnArrow++;
				}
			}
		}
		else if (keyNumber == 13) {
			return positionOnArrow;
		}




	}
}






int main() {
	int  colorForChangesBites = 7;
	int colorForBackground = 0;
	int colorForBites = 7;
	
	while(true){
		SetColor(White, colorForBackground);
		system("cls");
		int choice = choiceParamMenu();
		if (choice == 13) {
			exit(0);
		}
		else if (choice == 10) {
			
			colorForChangesBites = choiceColor();
		}
		else if (choice == 11) {
			colorForBackground = choiceColor();
		}
		else if (choice == 12) {
			colorForBites = choiceColor();
		}
		else {
			input(choiceSystemNumber(), choice, colorForChangesBites, colorForBackground, colorForBites);
		}
	}
	
	//double i = 45.000545454554444444444444444444444455555555555555555554545;
   //cout << i;
	//printf("%.1000lf", i);
	
	return 0;
}
