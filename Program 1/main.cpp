#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <math.h>

using namespace std;

void openFiles(ifstream&, ofstream&);
void Populatetable1(unsigned short int**, int, int, ifstream&);
void CreateBitwisetable1(unsigned short int**, int, int);
void Printtable1(unsigned short int** , int, ofstream&);
void Initilazetable2(int**, int, int);
void Printtable2( int**, int, ofstream&);
void moreBitwiseops(int**, int, ifstream&);
int getbit(int, int);
int	setbit(int, int, int);
int countOnes(int);
bool isEven(int);
bool isPower2(int);
int main() {

	ifstream infile;
	ofstream outfile;
	int t1_rows = 4;
	int t1_columns = 6;
	int t1_inputrows;
	int t2_rows;
	int t2_columns =10;



	openFiles(infile, outfile);
	infile >> t1_inputrows;
	t1_rows = (t1_rows + t1_inputrows);

	unsigned short int** Table1 = new unsigned short int* [t1_rows];
	for (int i = 0; i < t1_rows; i++) {

		Table1[i] = new unsigned short int[t1_columns];
	}
	Populatetable1(Table1, t1_rows, t1_columns, infile);
	CreateBitwisetable1(Table1, t1_rows, t1_columns);
	Printtable1(Table1, t1_rows, outfile);

	infile >> t2_rows;
	 int** Table2 = new  int* [t2_rows];
	for ( int i = 0; i < t2_rows; i++) {

		Table2[i] = new  int[t2_columns];
	}
	Initilazetable2(Table2, t2_rows, t2_columns);
	moreBitwiseops(Table2, t2_rows, infile);
	Printtable2(Table2, t2_rows, outfile);

	
	

	infile.close();
	outfile.close();
}
void openFiles(ifstream& infile, ofstream& outfile)
{
	char inFileName[40];
	char outFileName[40];

	cout << "Enter the input file name: ";
	cin >> inFileName;
	infile.open(inFileName); //open input file

	cout << "Enter the output file name: ";
	cin >> outFileName;
	outfile.open(outFileName);//open out putfile
}

void Populatetable1(unsigned short int** a, int row, int column, ifstream& infile) {
	int num = 0;

	a[0][0] = 1;
	a[1][0] = 1;
	a[2][0] = 0;
	a[3][0] = 0;

	a[0][1] = 1;
	a[1][1] = 0;
	a[2][1] = 1;
	a[3][1] = 0;

	for (int r = 4; r < row; r++) {
		for (int c = 0; c < 2; c++) {
			infile >> num;
			a[r][c] = num;
			num = 0;
		}
	}

}
void CreateBitwisetable1(unsigned short int** a, int row, int column) {

	unsigned short int result = 0;
	for (int r = 0; r < 4; r++) {
		for (int c = 2; c < column; c++) {


			switch (c) {
			case 2:
				a[r][c] = (a[r][0] & a[r][1]);
				break;
			case 3:
				a[r][c] = (a[r][0] | a[r][1]);
				break;
			case 4:
				a[r][c] = (a[r][0] ^ a[r][1]);
				break;
			case 5:
				if ((~a[r][0]) == -2) {
					a[r][c] = 0;
				}
				else if ((~a[r][0]) == -1) {
					a[r][c] = 1;
				}
				else {
					a[r][c] = (~a[r][0]);
					break;
				}
			}
		}
	}
	for (int r = 4; r < row; r++) {
		for (int c = 2; c < column; c++) {


			switch (c) {
			case 2:
				a[r][c] = a[r][0] & a[r][1];
				break;
			case 3:
				a[r][c] = a[r][0] | a[r][1];
				break;
			case 4:
				a[r][c] = a[r][0] ^ a[r][1];
				break;
			case 5:
				a[r][c] = (~a[r][0]);
				break;

			}
		}
	}

}
void Printtable1(unsigned short int** a, int row, ofstream& outfile) {
	outfile << endl;
	outfile << "|" << setw(7) << "X" << "|"
		<< setw(7) << "Y" << "|"
		<< setw(7) << "&" << "|"
		<< setw(7) << "|" << "|"
		<< setw(7) << "^" << "|"
		<< setw(7) << "~" << "|" << endl;
	outfile << "|-------|-------|-------|-------|-------|-------|" << endl;


	for (int r = 0; r < row; r++) {
		outfile << "|" << setw(7) << a[r][0] << "|"
			<< setw(7) << a[r][1] << "|"
			<< setw(7) << a[r][2] << "|"
			<< setw(7) << a[r][3] << "|"
			<< setw(7) << a[r][4] << "|"
			<< setw(7) << a[r][5] << "|" << endl;
		outfile << "|-------|-------|-------|-------|-------|-------|" << endl;
	}
}
void Initilazetable2( int** a, int rows, int columns) {
	
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < columns; c++) {
			a[r][c] = -1;
		}
	}
}
void Printtable2( int** a, int rows, ofstream& outfile) {
	outfile << endl;
	outfile << "|" << setw(7) << "X" << "|"
		<< setw(7) << "P" << "|"
		<< setw(7) << "V" << "|"
		<< setw(7) << ">>" << "|"
		<< setw(7) << "<<" << "|"
		<< setw(7) << "S" << "|"
		<< setw(7) << "G" << "|"
		<< setw(7) << "E" << "|"
		<< setw(7) << "C" << "|"
		<< setw(7) << "2" << "|" << endl;
	outfile << "|-------|-------|-------|-------|-------|-------"
		<< "|-------|-------|-------|-------|" << endl;


	for (int r = 0; r < rows; r++) {
		outfile << "|"; 
		if (a[r][0] == -1) { 
			outfile << setw(7) << " "<< "|"; 
		} 
		else { 
			outfile << setw(7) << a[r][0] << "|";
		}
		if (a[r][1] == -1) {
			outfile << setw(7) << " " << "|"; 
		} else {
			outfile << setw(7) << a[r][1] << "|";
		}
		if (a[r][2] == -1) {
			outfile << setw(7) << " " << "|";
		}
		else {
			outfile << setw(7) << a[r][2] << "|";
		}
		if (a[r][3] == -1) {
			outfile << setw(7) << " " << "|";
		}
		else {
			outfile << setw(7) << a[r][3] << "|";
		}
		if (a[r][4] == -1) {
			outfile << setw(7) << " " << "|";
		}
		else {
			outfile << setw(7) << a[r][4] << "|";
		}
		if (a[r][5] == -1) {
			outfile << setw(7) << " " << "|";
		}
		else {
			outfile << setw(7) << a[r][5] << "|";
		}
		if (a[r][6] == -1) {
			outfile << setw(7) << " " << "|";
		}
		else {
			outfile << setw(7) << a[r][6] << "|";
		}
		if (a[r][7] == -1) {
			outfile << setw(7) << " " << "|";
		}
		else {
			outfile << setw(7) << a[r][7] << "|";
		}
		if (a[r][8] == -1) {
			outfile << setw(7) << " " << "|";
		}
		else {
			outfile << setw(7) << a[r][8] << "|";
		}
		if (a[r][9] == -1) {
			outfile << setw(7) << " " << "|";
		}
		else {
			outfile << setw(7) << a[r][9] << "|";
		}
		outfile << endl;
		outfile << "|-------|-------|-------|-------|-------|-------"
			<< "|-------|-------|-------|-------|" << endl;
	}
}
void moreBitwiseops(int** a, int rows, ifstream& infile) {
	char symbol;
	for (int r = 0; r < rows; r++) {
		infile >> symbol;
		infile >> a[r][0];

		switch (symbol) {

		case '>':
			a[r][3] = (a[r][0] >> 1);
			break;
		case '<':
			a[r][4] = (a[r][0] << 1);
			break;
		case 'S':
			infile >> a[r][1];
			infile >> a[r][2];
			a[r][5] = setbit(a[r][0], a[r][1], a[r][2]);
			break;
		case 'G':
			infile >> a[r][1];
			a[r][6] = getbit(a[r][0], a[r][1]);
			break;
		case 'E':
			a[r][7] = isEven(a[r][0]);
			break;
		case 'C':
			a[r][8] = countOnes(a[r][0]);
			break;
		case '2':
			a[r][9] = isPower2(a[r][0]);
			break;
		}

	}
}
int getbit(int num, int n) {
	int power = pow(2, n);
	int result;
	if ((num & power) != 0) {
		result = 1;
	}
	else {
		result = 0;
	}
	return result;
}
int setbit(int num, int n, int v) {
	int result;
	int power = pow(2, n);
	if (getbit(num, n) == v) {
		result = num;
	}
	else {
		result = (num ^ power);
	}
	return result;
}
int countOnes(int num) {
	int count = 0;
	int power;
	for (int i = 0; i < 32; i++) {
		power = pow(2, i);
		if (( num & power) != 0) {
			count++;
		}
	}
	return count;
}
bool isEven(int num) {
	int power = pow(2, 0);
	if ((num & power) == 0) {
		return true;
	}
	else
	{
		return false;
	}

}
bool isPower2(int num) {
	 int num2 = num - 1;
	if (num == 0) {
		return false;
	}
	else {
		if ((num & num2) == 0) {
			return true;
		}
		else {
			return false;
		}
	}
}