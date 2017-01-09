// Programmer: Biplov Ojha
// Assignment 1: This program will short mailing address y Names and Zipcodes and prints mailing labels. 


#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

struct person {
	string name;
	string zipCode;
};

void print_persons(person*, int);
void print_grouped(person*, int);
void sort_by_name(person*, int);
void sort_by_zipcode(person*, int);

void print_persons(person *p, int n) {
	cout << setw(7) << left << "ZIP" << "NAME" << endl << endl;
	for (int i = 0; i < n; i++) {
		//cout << "ZIP: " << p[i].zipCode << endl << "NAME:" << p[i].name << endl << endl;
		cout << p[i].zipCode << " " << p[i].name << endl;
	}
}

void print_grouped(person* p, int n) {
	// previous zipcode
	string prevZipcode = "";
	cout << "ZIP\t NAME\n\n";
	for (int i = 0; i < n; i++) {
		if (p[i].zipCode != prevZipcode) {
			// zipcode is different
			prevZipcode = p[i].zipCode;
			cout << p[i].zipCode << ":" << endl;
		}
		cout << "\t" << p[i].name << endl;
	}
}

void sort_by_name(person *p, int n) {
	for (int i = 0; i < n - 1; i++) {
		// true if there are elements needed
		// to be swapped
		bool swapped = false;
		for (int j = 0; j < n - i - 1; j++) {
			// swap elements, if they are
			// placed in incorrect order
			if (p[j].name > p[j+1].name) {
				person b = p[j]; 
				p[j] = p[j+1];
				p[j+1] = b;
				swapped = true;
			}
		}
		
		// break if there no elements
		// needed to be swapped 
		// (i.e. all elements are placed
		// in correct order)
		if(!swapped)
			break;
	}
}

void sort_by_zipcode(person *p, int n) {
	// algorithm is the same, but this time
	// objects are compared by zipcode
	for (int i = 0; i < n - 1; i++) {
		bool swapped = false;
		for (int j = 0; j < n - i - 1; j++) {
			if (p[j].zipCode > p[j+1].zipCode) {
				person b = p[j]; 
				p[j] = p[j+1];
				p[j+1] = b;
				swapped = true;
			}
		}

		if(!swapped)
			break;
	}
}

int main () {
	// create file input stream to read data
	ifstream dataFile ("NameZip.txt");

	// if file wan't opened correctly
	if (dataFile.fail()) {
		cout << "can’t open file" << endl;
		return 0;
	}
	
	// array to store person objects
	person p[20];
	// number of person objects in array
	int n = 0;
	
	// read file
	while (dataFile.peek() != EOF) {
		dataFile >> p[n].zipCode;
		getline(dataFile, p[n++].name);
	}
	
	// heading for initial list
	cout << "------------BEFORE SORT------------" << endl;
	print_persons(p, n);
	
	// heading for list, sorted by name
	cout << "------------AFTER SORT------------" << endl;	
	// sort by name
	sort_by_name(p, n);
	// print sorted list
	print_persons(p, n);
	
	// heading for list, sorted by zipcode
	cout << "--------GROUPED BY ZIPCODE--------" << endl;
	// sort by zipcode
	sort_by_zipcode(p, n);
	// print sorted list, grouping by zipcode
	print_grouped(p, n);
	
	return 0;
}
