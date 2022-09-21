/*
	Jarette Greene

	Course CS 2433-101, Fall 22, Stringfellow

	Purpose: This program prompts to enter the name of the input
	file. Then prompts for the name of the output file. The program
	then runs and produces two tables. The first table begins uses the 
	&(and), | (or), ^(xor) and ~(not) operations. Starting with a basic
	table then performs the operations on data from the input file. The
	second  table performs bit manipulations on data from the same input.
	These manipulations are getbit,setbit,countones, isEven and isPower2.
	Where set bits changes the bit in a specfied space to one or zero based
	.Getbit returns the bit at a specified location. Countones returns how
	many ones are in the binary of a given integer. isEven returns true if
	an integer is even and false if it is odd. isPower2 returns true if an 
	integer is a power of 2 and false if not.
*/
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <math.h>

using namespace std;
// Function Prototypes
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
	// declaring variables
	ifstream infile;
	ofstream outfile;
	int t1_rows = 4;
	int t1_columns = 6;
	int t1_inputrows;
	int t2_rows;
	int t2_columns =10;


	// calling function to open files 
	openFiles(infile, outfile); 	// gets the amount of data that shall
                                    // be read in from input file for the first table
	
	infile >> t1_inputrows;       // creates the amount of rows that will be in the first table
	
	t1_rows = (t1_rows + t1_inputrows);

	// creating dynamically allocated 2D array  
	// where i foound the code to dynamically allocate a 2D array and deallocate it:
	// https://www.geeksforgeeks.org/how-to-declare-a-2d-array-dynamically-in-c-using-new-operator/
	unsigned short int** Table1 = new unsigned short int* [t1_rows];
	for (int i = 0; i < t1_rows; i++) {

		Table1[i] = new unsigned short int[t1_columns];
	}

	// calling functions to initialize the table then perform operations
	// and filled the remainder of the table then display the table respectively 
	Populatetable1(Table1, t1_rows, t1_columns, infile);
	CreateBitwisetable1(Table1, t1_rows, t1_columns);
	Printtable1(Table1, t1_rows, outfile);

	
	delete[] Table1;	// deallocates table 

	infile >> t2_rows; // gets the amount of rows in for the new table 

	// dynamically allocates new 2D array of ints 
	 int** Table2 = new  int* [t2_rows];
	for ( int i = 0; i < t2_rows; i++) {

		Table2[i] = new  int[t2_columns];
	}
	// functions to initialize, perform operations and place into the table
	// then display the table.
	Initilazetable2(Table2, t2_rows, t2_columns);
	moreBitwiseops(Table2, t2_rows, infile);
	Printtable2(Table2, t2_rows, outfile);

	delete[] Table2;  // dealocates the table

	// closes input an output file
	infile.close();
	outfile.close();
}
/**
 * Purpose: Opens a input file and opens a output file
 * 
 * Recieves: infile, ifstream variable passed by reference and 
 * 			outfile, ofstream variable passed by reference
 * 
 * Returns: N/A (void function)
 *
 */
void openFiles(ifstream& infile, ofstream& outfile)
{
	//declaring varibales
	char inFileName[40]; 	//stores name of the input file
	char outFileName[40];	// stores the nname of the output file

	cout << "Enter the input file name: "; //prompts for name of input file
	cin >> inFileName;				// recieves name of file
	infile.open(inFileName); //open input file

	cout << "Enter the output file name: ";  //prompts for name of output file
	cin >> outFileName;			//recieves name of output file
	outfile.open(outFileName);//open out putfile
}
/**
 * Purpose: initializes values for 2D array 
 * 
 * Recieves: a, a 2D array of unsigned short integers, row,
 * 			the amount of rows in the 2D array, column, the 
 * 			amount of columns in the 2D array and infile,
 * 			an infile variable passed by reference.
 * 
 * Returns: N/A (void function)
 *
 */
void Populatetable1(unsigned short int** a, int row, int column, ifstream& infile) {
	// declaring variables
	int num = 0;

	// hard coding the first two rows and first two colums of the table with 1s and 0s
	a[0][0] = 1;
	a[1][0] = 1;
	a[2][0] = 0;
	a[3][0] = 0;

	a[0][1] = 1;
	a[1][1] = 0;
	a[2][1] = 1;
	a[3][1] = 0;
	// for loop that goes through the remaining rows and columns
	for (int r = 4; r < row; r++) {
		for (int c = 0; c < 2; c++) {
			// assigning data from input file into the table
			infile >> num; 
			a[r][c] = num;
			num = 0;
		}
	}

}
/**
 * Purpose: Performs bitwise operations on unisigned short ints and
 * 			stores in 2D array
 * 
 * Recieves: a, a 2D array of unsigned short integers, row,
 * 			the amount of rows in the 2D array, column, the 
 * 			amount of columns in the 2D array.
 * 
 * Returns: N/A (void function)
 *
 */
void CreateBitwisetable1(unsigned short int** a, int row, int column) {

	// for loop that goes through the first 4 rows and all columns other than
	// the first 2 columsn
	for (int r = 0; r < 4; r++) {
		for (int c = 2; c < column; c++) {

			// switch case that checks the columns of the 2D array to know which 
			//operations are to be performed and places result in correct space
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
	// second for loop to traverse the rest of the rows
	for (int r = 4; r < row; r++) {
		for (int c = 2; c < column; c++) {

			//switch case that checks for the columns and based on column
			//performs approipriate operation and places result in correct
			//spot
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
/**
 * Purpose: Displays the elements of a 2D array in the form of a table
 * 
 * Recieves: a, a 2D array of unsigned short integers, row,
 * 			the amount of rows in the 2D array and outfile, ofstream 
 * 			variable passed by reference
 * 
 * Returns: N/A (void function)
 *
 */
void Printtable1(unsigned short int** a, int row, ofstream& outfile) {
	// header of the table
	outfile << "Jarette Greene" << endl;
	outfile << "Program 1: Bitwise Operations" << endl;
	outfile << endl;
	// the column headers of the rows
	outfile << "|" << setw(7) << "X" << "|"
		<< setw(7) << "Y" << "|"
		<< setw(7) << "&" << "|"
		<< setw(7) << "|" << "|"
		<< setw(7) << "^" << "|"
		<< setw(7) << "~" << "|" << endl;
	outfile << "|-------|-------|-------|-------|-------|-------|" << endl;

	//for loop that traverses the rows of the 2D array 
	for (int r = 0; r < row; r++) {
		// displays all the elements in the 2D array
		outfile << "|" << setw(7) << a[r][0] << "|"
			<< setw(7) << a[r][1] << "|"
			<< setw(7) << a[r][2] << "|"
			<< setw(7) << a[r][3] << "|"
			<< setw(7) << a[r][4] << "|"
			<< setw(7) << a[r][5] << "|" << endl;
		outfile << "|-------|-------|-------|-------|-------|-------|" << endl;
	}
}
/**
 * Purpose: Initializing 2D array of ints with -1
 * 
 * Recieves: a, a 2D array  integers, row, the amount of rows in 
 * 			 the 2D array,column, the amount of columns in the 2D array.
 * 
 * Returns: N/A (void function)
 *
 */
void Initilazetable2( int** a, int rows, int columns) {
	//for loop that traverses the entire 2D array 
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < columns; c++) {
			// fills each element of 2D array with -1
			a[r][c] = -1;
		}
	}
}
/**
 * Purpose: Displays the elements of a 2D array in the form of a table
 * 
 * Recieves: a, a 2D array of integers, row, the amount of rows in the 2D array 
 * 			 and outfile, ofstream variable passed by reference
 * 
 * Returns: N/A (void function)
 *
 */
void Printtable2( int** a, int rows, ofstream& outfile) {
	outfile << endl;
	// row headers of the table
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

	// for loop that traverse the rows of the 2D array 
	for (int r = 0; r < rows; r++) {
		outfile << "|"; 
		// if statments that checks if the array space holds -1 and
		// if it does prints a blank space if not displays the data 
		// stored
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
/**
 * Purpose: Performs bit manipulations on data stored in a 2D array of 
 * 			ints
 * 
 * Recieves: a, a 2D array of integers, row, the amount of rows
 * 			 in the 2D array, column, the amount of columns in the 2D array.
 * 
 * Returns: N/A (void function)
 *
 */
void moreBitwiseops(int** a, int rows, ifstream& infile) {
	char symbol;
	// for loop that traverses the row of the 2D array
	for (int r = 0; r < rows; r++) {
		// recieves a symbol and integer from the input file
		infile >> symbol;
		infile >> a[r][0];
		// switch case that checks for the symbol and performs 
		// appriopriate function
		switch (symbol) {

		case '>':
			a[r][3] = (a[r][0] >> 1);
			break;
		case '<':
			a[r][4] = (a[r][0] << 1);
			break;
		case 'S':
		// recieving the position and what the bit is to be changed to 
			infile >> a[r][1];
			infile >> a[r][2];
			a[r][5] = setbit(a[r][0], a[r][1], a[r][2]);
			break;
		case 'G':
		// recieving the position
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
/**
 * Purpose: tells you the bit (1 or 0) at a specific position in
 * 			a integer 
 * 
 * Recieves: num, the integer that the bits are being searched and n, 
 * 			an integer that indicates the position that will be checked
 * 
 * Returns: the integer 1 and 0 based on what is found at the pit position
 *
 */
int getbit(int num, int n) {
	//integer to stor the positin to be checked
	int power = pow(2, n);
	int result;
	// if statement that ands the num with the position and if the result is 
	// not 0 then the bit position is a 1 if result is 0 the position is 
	//a 0
	if ((num & power) != 0) {
		result = 1;
	}
	else {
		result = 0;
	}
	return result;
}
/**
 * Purpose: changes the bit located at a specific position in to a value (1 or 0)
 * 			specified by user 
 * 		
 * Recieves: num, the integer that the bits are being searched and n, 
 * 			an integer that indicates the position that will be checked, v 
 * 			the value that the bit will be changed to
 * 
 * Returns: returns the new integer after changing the bit
 *
 */
int setbit(int num, int n, int v) {
	int result;
	int power = pow(2, n);
	// if statement that checks for the bit to be changed 
	// if the bit is same as the the value that you would want
	// to change the result would be the original num but if it 
	// is not the then perform xor operation
	if (getbit(num, n) == v) {
		result = num;
	}
	else {
		result = (num ^ power);
	}
	return result;
}
/**
 * Purpose: Counts the amounts of 1s that are in the binary of an integer
 * 		
 * Recieves: num, the integer that the bits are being counted
 * 
 * Returns: the amount of num 1s are in the binary of the integer
 *
 */
int countOnes(int num) {
	int count = 0;
	int power;
	// for loop that will allows you to access every bit position of a num 
	for (int i = 0; i < 32; i++) {
		power = pow(2, i);
		//checks to see if the position is a 1 the increments count
		if (( num & power) != 0) {
			count++;
		}
	}
	return count;
}
/**
 * Purpose: Checks if an integer is an even number 
 * 		
 * Recieves: num, the integer that will be checked if it is even
 * 
 * Returns: returns true if it is even if not then return false
 *
 */
bool isEven(int num) {
	int power = pow(2, 0);
	// if statement that checks if the first position in a num is 1 or 0
	// if it is a 0 then it returns true if it is a 1 it returns false
	if ((num & power) == 0) {
		return true;
	}
	else
	{
		return false;
	}

}
/**
 * Purpose: Checks if a integer num is a power of 2
 * 		
 * Recieves: num, the integer thar will be checked if it is a power
 * 			 of 2
 * 
 * Returns: returns a true if the integer is a power of 2 and if not it
 * 			will return false
 *
 */
bool isPower2(int num) {
	//declares and initializes new variable that will be checked agaisnt 
	// the passed in variable
	 int num2 = num - 1;
	 // error checking for the number 0;
	if (num == 0) {
		return false;
	}
	// checks if the result of new variable & passing in integer is 0
	// if it is 0 return true if not return false 
	else {
		if ((num & num2) == 0) {
			return true;
		}
		else {
			return false;
		}
	}
}