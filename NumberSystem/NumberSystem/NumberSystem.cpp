#include <iostream>
#include "windows.h"
#include <conio.h>
#include <map>
#include <cmath>
#include <string>
#include <LIMITS.H>
#include <set>
//#include <graphics.h>


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

void SetColor(int text, ConsoleColor background)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 0) | text));
}

void gotoxy(int xpos, int ypos)
{
	COORD scrn;

	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);

	scrn.X = xpos; scrn.Y = ypos;

	SetConsoleCursorPosition(hOuput, scrn);
}

void translateOnTypeOfData(int* numberInMass, int typeOfData, int numberSystem, int counterNumber, bool negativeFlag, int* factionalMass, int counterFactionalNumber,int colorForChangesBites) {
	gotoxy(5, 2);
	bool lastNum;
	int count = 0;
	//short int
	if (typeOfData == 1) {
		bites <short int> bit;
		bit.number = 0;
		//bites<short int> number ;
		for (int i = 0, j = counterNumber-1; i < counterNumber; i++, j--) {
			bit.number += (numberInMass[i] * pow(numberSystem, j));
		}
		if (negativeFlag) {
			bit.number*=-1;
		}
		cout << endl <<  bit.number << endl;

		

		for (int z = sizeof(short int) - 1; z >= 0; z--) {
			for (int i = 7; i >= 0; i--) {
				cout << bool(bit.ch[z] & (1 << i));
			}
		}



		cout << endl;

		set <int> numberBites;
		for (int z = sizeof(short int) - 1; z >= 0; z--) {
			for (int i = 7; i >= 0; i--) {
				if (z == 1 && i == 7) {
					lastNum = bool(bit.ch[z] & (1 << i));
				}
				else {
					if (bool(bit.ch[z] & (1 << i)) != lastNum) {
						count++;
						numberBites.insert(z*8+i);
						numberBites.insert(z*8 + i+1);
						lastNum = bool(bit.ch[z] & (1 << i));
					}
					else{
						lastNum = bool(bit.ch[z] & (1 << i));
					}
				}
			}
		}
		for (auto now : numberBites) {
			bit.number = (bit.number & (1 << now)) ? (bit.number & ~(1 << now)) : (bit.number | (1 << now));
		}


		cout << endl << endl;
		for (int z = sizeof(short int) - 1; z >= 0; z--) {
			for (int i = 7; i >= 0; i--) {
				if (numberBites.find(z * 8 + i)!=numberBites.end()) {
					SetColor(colorForChangesBites, Black);
					cout << bool(bit.ch[z] & (1 << i));
				}
				else {
					SetColor(White, Black);
					cout << bool(bit.ch[z] & (1 << i));
				}
			}
		}
		SetColor(White, Black);
		cout << endl;
		cout << "cout = " << count << " new number = " << bit.number;
	

	}
	// unsigned short int
	else if (typeOfData == 2) {
		bites <unsigned short int> bit;
		bit.number = 0;
		for (int i = 0, j = counterNumber - 1; i < counterNumber; i++, j--) {
			bit.number += (numberInMass[i] * pow(numberSystem, j));
		}
		cout << endl << bit.number << endl;
		for (int z = sizeof(unsigned short int) - 1; z >= 0; z--) {
			for (int i = 7; i >= 0; i--) {
				cout << bool(bit.ch[z] & (1 << i));
			}
		}

		set <int> numberBites;
		for (int z = sizeof(unsigned short int) - 1; z >= 0; z--) {
			for (int i = 7; i >= 0; i--) {
				if (z == 1 && i == 7) {
					lastNum = bool(bit.ch[z] & (1 << i));
				}
				else {
					if (bool(bit.ch[z] & (1 << i)) != lastNum) {
						count++;
						numberBites.insert(z * 8 + i);
						numberBites.insert(z * 8 + i + 1);
						lastNum = bool(bit.ch[z] & (1 << i));
					}
					else {
						lastNum = bool(bit.ch[z] & (1 << i));
					}
				}
			}
		}
		for (auto now : numberBites) {
			bit.number = (bit.number & (1 << now)) ? (bit.number & ~(1 << now)) : (bit.number | (1 << now));
		}


		cout << endl << endl;
		for (int z = sizeof(unsigned short int) - 1; z >= 0; z--) {
			for (int i = 7; i >= 0; i--) {
				if (numberBites.find(z * 8 + i) != numberBites.end()) {
					SetColor(Red, Black);
					cout << bool(bit.ch[z] & (1 << i));
				}
				else {
					SetColor(White, Black);
					cout << bool(bit.ch[z] & (1 << i));
				}
			}
		}
		SetColor(White, Black);
		cout << endl;
		cout << "cout = " << count << " new number = " << bit.number;

		
	}
	// int
	else if (typeOfData == 3) {
		
		bites <int> bit;
		bit.number = 0;
		for (int i = 0, j = counterNumber - 1; i < counterNumber; i++, j--) {
			bit.number += (numberInMass[i] * pow(numberSystem, j));
		}
		if (negativeFlag) {
			bit.number *= -1;
		}
		cout << endl << bit.number << endl;
		for (int z = sizeof(int) - 1; z >= 0; z--) {
			for (int i = 7; i >= 0; i--) {
				cout << bool(bit.ch[z] & (1 << i));
			}
		}

		set <int> numberBites;
		for (int z = sizeof(int) - 1; z >= 0; z--) {
			for (int i = 7; i >= 0; i--) {
				if (z == 3 && i == 7) {
					lastNum = bool(bit.ch[z] & (1 << i));
				}
				else {
					if (bool(bit.ch[z] & (1 << i)) != lastNum) {
						count++;
						numberBites.insert(z * 8 + i);
						numberBites.insert(z * 8 + i + 1);
						lastNum = bool(bit.ch[z] & (1 << i));
					}
					else {
						lastNum = bool(bit.ch[z] & (1 << i));
					}
				}
			}
		}
		for (auto now : numberBites) {
			bit.number = (bit.number & (1 << now)) ? (bit.number & ~(1 << now)) : (bit.number | (1 << now));
		}


		cout << endl << endl;
		for (int z = sizeof(int) - 1; z >= 0; z--) {
			for (int i = 7; i >= 0; i--) {
				if (numberBites.find(z * 8 + i) != numberBites.end()) {
					SetColor(Red, Black);
					cout << bool(bit.ch[z] & (1 << i));
				}
				else {
					SetColor(White, Black);
					cout << bool(bit.ch[z] & (1 << i));
				}
			}
		}
		SetColor(White, Black);
		cout << endl;
		cout << "cout = " << count << " new number = " << bit.number;
		
	}
	// unsigned int
	else if (typeOfData == 4) {
		
		bites<unsigned int> bit;
		bit.number = 0;
		for (int i = 0, j = counterNumber - 1; i < counterNumber; i++, j--) {
			bit.number += (numberInMass[i] * pow(numberSystem, j));
		}
		cout << endl << bit.number << endl;

		for (int z = sizeof(unsigned int) - 1; z >= 0; z--) {
			for (int i = 7; i >= 0; i--) {
				cout << bool(bit.ch[z] & (1 << i));
			}
		}

		set <int> numberBites;
		for (int z = sizeof(unsigned int) - 1; z >= 0; z--) {
			for (int i = 7; i >= 0; i--) {
				if (z == 3 && i == 7) {
					lastNum = bool(bit.ch[z] & (1 << i));
				}
				else {
					if (bool(bit.ch[z] & (1 << i)) != lastNum) {
						count++;
						numberBites.insert(z * 8 + i);
						numberBites.insert(z * 8 + i + 1);
						lastNum = bool(bit.ch[z] & (1 << i));
					}
					else {
						lastNum = bool(bit.ch[z] & (1 << i));
					}
				}
			}
		}
		for (auto now : numberBites) {
			
			bit.number = (bit.number & (1 << now)) ? (bit.number & ~(1 << now)) : (bit.number | (1 << now));
		}


		cout << endl << endl;
		for (int z = sizeof(unsigned int) - 1; z >= 0; z--) {
			for (int i = 7; i >= 0; i--) {
				if (numberBites.find(z * 8 + i) != numberBites.end()) {
					SetColor(Red, Black);
					cout << bool(bit.ch[z] & (1 << i));
				}
				else {
					SetColor(White, Black);
					cout << bool(bit.ch[z] & (1 << i));
				}
			}
		}
		SetColor(White, Black);
		cout << endl;
		cout << "cout = " << count << " new number = " << bit.number;

		
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

		cout << endl << bit.number << endl;

		for (int z = sizeof(double) - 1; z >= 0; z--) {
			for (int i = 7; i >= 0; i--) {
				cout << bool(bit.ch[z] & (1 << i));
			}
		}
		
		set <int> numberBites;
		long long int a = 1;
		cout << endl;
		for (int z = sizeof(double) - 1; z >= 0; z--) {
			for (int i = 7; i >= 0; i--) {
				if (z == 7 && i == 7) {
					lastNum = bool(bit.ch[z] & (a << i));
					
				}
				else {
					if (bool(bit.ch[z] & (a << i)) != lastNum) {
						count++;
						numberBites.insert(z * 8 + i + 1);
						numberBites.insert(z * 8 + i);
						lastNum = bool(bit.ch[z] & (a << i));
						
					}
					else {
						lastNum = bool(bit.ch[z] & (a << i));
						
					}
				}
			}
		}
		
		for (auto now : numberBites) {
			bit.num = (bit.num& (a << now)) ? (bit.num & ~(a << now)) : (bit.num | (a << now));
		}


		cout << endl << endl;
		for (int z = sizeof(double) - 1; z >= 0; z--) {
			for (int i = 7; i >= 0; i--) {
				if (numberBites.find(z * 8 + i) != numberBites.end()) {
					SetColor(Red, Black);
					cout << bool(bit.ch[z] & (1 << i));
				}
				else {
					SetColor(White, Black);
					cout << bool(bit.ch[z] & (1 << i));
				}
			}
		}
		SetColor(White, Black);
		cout << endl;
		cout << "cout = " << count << " new number = " << bit.number;
	}
	//long double
	else if (typeOfData == 6) {
		cout << endl << endl << endl;
		
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

		for (int z = sizeof(long double) - 1; z >= 0; z--) {
			for (int i = 7; i >= 0; i--) {
				cout << bool(bit.ch[z] & (1 << i));
			}
		}

		set <int> numberBites;
		long long int a = 1;
		cout << endl;
		for (int z = sizeof(double) - 1; z >= 0; z--) {
			for (int i = 7; i >= 0; i--) {
				if (z == 7 && i == 7) {
					lastNum = bool(bit.ch[z] & (a << i));

				}
				else {
					if (bool(bit.ch[z] & (a << i)) != lastNum) {
						count++;
						numberBites.insert(z * 8 + i + 1);
						numberBites.insert(z * 8 + i);
						lastNum = bool(bit.ch[z] & (a << i));

					}
					else {
						lastNum = bool(bit.ch[z] & (a << i));

					}
				}
			}
		}

		for (auto now : numberBites) {
			bit.num = (bit.num & (a << now)) ? (bit.num & ~(a << now)) : (bit.num | (a << now));
		}


		cout << endl << endl;
		for (int z = sizeof(double) - 1; z >= 0; z--) {
			for (int i = 7; i >= 0; i--) {
				if (numberBites.find(z * 8 + i) != numberBites.end()) {
					SetColor(Red, Black);
					cout << bool(bit.ch[z] & (1 << i));
				}
				else {
					SetColor(White, Black);
					cout << bool(bit.ch[z] & (1 << i));
				}
			}
		}
		SetColor(White, Black);
		cout << endl;
		cout << "cout = " << count << " new number = " << bit.number;

	}
	//float 
	else if (typeOfData == 7) {
		cout << endl << endl << endl;
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

		for (int z = sizeof(float) - 1; z >= 0; z--) {
			for (int i = 7; i >= 0; i--) {
				cout << bool(bit.ch[z] & (1 << i));
			}
		}

		set <int> numberBites;
		long long int a = 1;
		for (int z = sizeof(float) - 1; z >= 0; z--) {
			for (int i = 7; i >= 0; i--) {
				if (z == 3 && i == 7) {
					lastNum = bool(bit.ch[z] & (a << i));
				}
				else {
					if (bool(bit.ch[z] & (a << i)) != lastNum) {
						count++;
						numberBites.insert(z * 8 + i + 1);
						numberBites.insert(z * 8 + i);
						lastNum = bool(bit.ch[z] & (a << i));
					}
					else {
						lastNum = bool(bit.ch[z] & (a << i));
					}
				}
			}
		}

		for (auto now : numberBites) {
			bit.num = (bit.num & (a << now)) ? (bit.num & ~(a << now)) : (bit.num | (a << now));
		}


		cout << endl << endl;
		for (int z = sizeof(float) - 1; z >= 0; z--) {
			for (int i = 7; i >= 0; i--) {
				if (numberBites.find(z * 8 + i) != numberBites.end()) {
					SetColor(Red, Black);
					cout << bool(bit.ch[z] & (1 << i));
				}
				else {
					SetColor(White, Black);
					cout << bool(bit.ch[z] & (1 << i));
				}
			}
		}
		SetColor(White, Black);
		cout << endl;
		cout << "cout = " << count << " new number = " << bit.number;
		
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

		cout << endl <<bit.number << endl;

		for (int z = sizeof(char) - 1; z >= 0; z--) {
			for (int i = 7; i >= 0; i--) {
				cout << bool(bit.ch[z] & (1 << i));
			}
		}

		set <int> numberBites;
		long long int a = 1;
		for (int z = sizeof(char) - 1; z >= 0; z--) {
			for (int i = 7; i >= 0; i--) {
				if (i == 7) {
					lastNum = bool(bit.ch[z] & (a << i));
				}
				else {
					if (bool(bit.ch[z] & (a << i)) != lastNum) {
						count++;
						numberBites.insert(z * 8 + i + 1);
						numberBites.insert(z * 8 + i);
						lastNum = bool(bit.ch[z] & (a << i));
					}
					else {
						lastNum = bool(bit.ch[z] & (a << i));
					}
				}
			}
		}

		for (auto now : numberBites) {
			bit.num = (bit.num & (a << now)) ? (bit.num & ~(a << now)) : (bit.num | (a << now));
		}


		cout << endl << endl;
		for (int z = sizeof(char) - 1; z >= 0; z--) {
			for (int i = 7; i >= 0; i--) {
				if (numberBites.find(z * 8 + i) != numberBites.end()) {
					SetColor(Red, Black);
					cout << bool(bit.ch[z] & (1 << i));
				}
				else {
					SetColor(White, Black);
					cout << bool(bit.ch[z] & (1 << i));
				}
			}
		}
		SetColor(White, Black);
		cout << endl;
		cout << "cout = " << count << " new number = " << bit.number;
																			
		
	}
	// unsigned char
	else if (typeOfData == 9) {
		bites<unsigned char> bit;
		bit.number = 0;
		for (int i = 0, j = counterNumber - 1; i < counterNumber; i++, j--) {
			bit.number += (numberInMass[i] * pow(numberSystem, j));
		}
		
		cout << endl <<bit.number << endl;
		for (int z = sizeof(unsigned char) - 1; z >= 0; z--) {
			for (int i = 7; i >= 0; i--) {
				cout << bool(bit.ch[z] & (1 << i));
			}
		}

		set <int> numberBites;
		long long int a = 1;
		for (int z = sizeof(char) - 1; z >= 0; z--) {
			for (int i = 7; i >= 0; i--) {
				if (i == 7) {
					lastNum = bool(bit.ch[z] & (a << i));
				}
				else {
					if (bool(bit.ch[z] & (a << i)) != lastNum) {
						count++;
						numberBites.insert(z * 8 + i + 1);
						numberBites.insert(z * 8 + i);
						lastNum = bool(bit.ch[z] & (a << i));
					}
					else {
						lastNum = bool(bit.ch[z] & (a << i));
					}
				}
			}
		}

		for (auto now : numberBites) {
			bit.num = (bit.num & (a << now)) ? (bit.num & ~(a << now)) : (bit.num | (a << now));
		}


		cout << endl << endl;
		for (int z = sizeof(char) - 1; z >= 0; z--) {
			for (int i = 7; i >= 0; i--) {
				if (numberBites.find(z * 8 + i) != numberBites.end()) {
					SetColor(Red, Black);
					cout << bool(bit.ch[z] & (1 << i));
				}
				else {
					SetColor(White, Black);
					cout << bool(bit.ch[z] & (1 << i));
				}
			}
		}
		SetColor(White, Black);
		cout << endl;
		cout << "cout = " << count << " new number = " << bit.number;
		
	}
	else if (typeOfData == 10) {
	
		if (numberInMass[0] != 0) {
			cout << 1;
		}
		else {
			cout << 0;
		}
	}

	cout << endl;
	system("pause");
	
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

void input(int numberSystem, int typeOfData, int colorForChangesBites) {
	system("cls");
	cout << "ENTER NUMBER" << endl;
	string availableCharacters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	cout << "Available Characters: ";
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
			cout <<endl <<  "ERROR";
			system("pause");
			typeOwerflow = true;
			break;
		}


		keyNumber = _getch();
	}
	if (!typeOwerflow) {
		translateOnTypeOfData(numberInMass, typeOfData, numberSystem, counterNumber, negativeFlag, factionalMass, counterFactionalNumber, colorForChangesBites);
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
	cout << "bool" << endl;
	cout << "color" << endl;
	cout << "exit";


	int positionOnArrow = 1;



	while (true) {
		

		gotoxy(10, positionOnArrow);

		cout << "<----";

		int keyNumber = _getch();

		gotoxy(10, positionOnArrow);

		cout << "     ";

		if (keyNumber == 224) {
			int temp = _getch();
			if (temp == 72) {
			
				if (positionOnArrow == 1) {
					positionOnArrow = 12;
				}
				else {
					positionOnArrow--;
				}
			}
			else if(temp == 80) {
				if (positionOnArrow == 12) {
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

int choiceColorForChangesBites() {
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


		gotoxy(20, positionOnArrow);

		cout << "<----";

		int keyNumber = _getch();

		gotoxy(20, positionOnArrow);

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
	while(true){
		system("cls");
		int choice = choiceParamMenu();
		if (choice == 12) {
			exit(0);
		}
		if (choice == 11) {
			
			colorForChangesBites = choiceColorForChangesBites();
		}
		else {
			input(choiceSystemNumber(), choice, colorForChangesBites);
		}
	}



	return 0;
}
