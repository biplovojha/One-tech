
// Programmar: Biplov Ojha
// Assignment # 2: This program emphasis on using string class. 

#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include <sstream> 
#include <algorithm>

using namespace std;

// struct for storing area code and state
struct location {
	string areaCode;
	string state;
};

// struct for storing name and telephone
struct personal {
	string name;
	string telephone;
};

// declaring functions used in the program
void readFileState(vector<location>&, ifstream&);
void readFileNames(vector<personal>&, ifstream&);
void displayVectors(vector<location>, vector<personal>);
void reFormatNamesTelNums(vector<personal>&);
void sortNamesTelNums(vector<personal>&);
void sortEverything(vector<location>&, vector<personal>&);
void searchAreaCode(vector<location>, vector<personal>);


/*
	this is the main function... execution starts from here
*/
int main() {
	
	// two file pointers
	ifstream fileNames;
	ifstream fileState;
	
	// two vectors for storing struct object of each file
	vector<location> vec_state; 
	vector<personal> vec_names;
	
/*
	first we will read each file and store their content in 
	each of vectors
*/
	readFileState(vec_state, fileState);	// reading file 1
	readFileNames(vec_names, fileNames);	// reading file 2
	
	// now displaying content of files which are read
	displayVectors(vec_state, vec_names);
	
/*
	this is implementation of first task in which we have reformatted
	names and telephone numbers
*/	
	reFormatNamesTelNums(vec_names);
	
/*
	this is second implementation in which we have sorted the names and 
	the area code
*/	
	sortEverything(vec_state,vec_names);
	
	// searching area code in telphones array
	searchAreaCode(vec_state,vec_names);
}

/*
	in this function we will read areacodesStates.txt file and store its contents
	in their structure named as location and then store its structure in
	their respective vector
*/
void readFileState(vector<location>& vec_location, ifstream& infile){
   
   string str, temp; // temporary string variables
   
   location strLoc;	// temporary struct object
   
   // opening file
   infile.open("areacodesStates.txt"); 
   
   // file exist or not
   if (infile.fail()) {	
    	cout<<"file not found !!\n";
    	exit(EXIT_FAILURE);	// exit if file not found
   }
 
  while (getline(infile, str))	// read file line by line
  {
		if(str != " ")
		{
			/*
				using stream we have made token of string
				and then stored in structure
			*/
			stringstream os(str);	
			os >> temp;
			strLoc.state = temp;
			
			// second token
			os >> temp;
			strLoc.areaCode = temp;			
			
			// now storing structure of line in vector
			vec_location.push_back(strLoc);
		}
  }
	
   infile.close();	// closing file
}


/*
	in this function we will read NamesTelNums.txt file and store its contents
	in their structure named as personal and then store its structure in
	their respective vector
*/
void readFileNames(vector<personal>& vec_personal, ifstream& infile){
   
   string str, temp;  // temporary string variables
   
   personal strPrs;  // temporary struct object
   // opening file
   infile.open("NamesTelNums.txt"); 
   
   // file exist or not
   if (infile.fail()) {
	cout<<"file not found !!\n";
    exit(EXIT_FAILURE);  // exit if file not found
   }
    
  while (getline(infile, str))	// read file line by line
  {
		if(str != "")
		{
			/*
				using stream we have made token of string
				and then stored in structure
			*/
			stringstream os(str);
			os >> temp;
			strPrs.telephone = temp;
			
			os >> temp;
			strPrs.name = temp;
			os >> temp;
			strPrs.name = strPrs.name + " " + temp;
			
			// now storing structure of line in vector
			vec_personal.push_back(strPrs);
		}
  }
   infile.close();	// closing file
}

/*
	in this function we are taking data from vectors which are read from file
	and displaying it on the console
*/
void displayVectors(vector<location> vec_state, vector<personal> vec_names){
	
	// displaying data of first vector
	cout<<" Data read from codes and states file : \n\n";
	for(int i = 0; i < vec_state.size(); i++){
    	cout << "\t"<<vec_state[i].state <<"\t"<< vec_state[i].areaCode << endl;
   	}
	
	// displaying data of second vector
	cout<<"\n Data read from names and telephone file : \n\n";
	for(int i = 0; i < vec_names.size(); i++){
    	cout << "\t"<<vec_names[i].telephone <<"\t"<< vec_names[i].name << endl;
   	}
}

/*
	function takes names and telephone vector as input argument
	and reformat it using string functions. also display the updated 
	vectors
*/
void reFormatNamesTelNums(vector<personal>& vec_names){
	
	string tel, first, last, temp;
	cout<<"\n Reformatting telephone and names : \n\n";
	
	// iterate through all the elements of vector
	for(int i = 0; i < vec_names.size(); i++){
		
		temp = vec_names[i].name;	// fetching name
		tel = vec_names[i].telephone;	// fetching telephone
		
		// formating it according to instructions
		vec_names[i].telephone = "(" + tel.substr(0,3) + ") " + tel.substr(4,5) + "-" + tel.substr(6,9);
		
		// breaking name into its first name and last name
		stringstream os(temp);
		os >> temp;
		first = temp;
		os >> temp;
		last = temp;
		
		// now reformatting the name according to instructions
		vec_names[i].name = last + ", " + first;
		
		// displaying the generated result vectors
    	cout << "\t"<<vec_names[i].telephone <<" \t"<< vec_names[i].name << endl;
   	}
}

// sort functions for name and state 
bool sortByName(const personal &lhs, const personal &rhs) { return lhs.name < rhs.name; }
bool sortByState(const location &lhs, const location &rhs) { return lhs.areaCode < rhs.areaCode; }

/*
	this function take both vectors as input and sort them using sort function
	on the basis of names and areaCode
*/
void sortEverything(vector<location>& vec_state, vector<personal>& vec_names){
	
    cout<<"\n Sorting Names : \n\n";
    sort(vec_names.begin(), vec_names.end(), sortByName);
    
    // displaying sorted names and their associated telephone numbers
	for(int i = 0; i < vec_names.size(); i++)
		cout << "\t"<<vec_names[i].telephone <<"\t"<< vec_names[i].name << endl;
		
    cout<<"\n Sorting Area Code : \n\n";
    sort(vec_state.begin(), vec_state.end(), sortByState);
    
    // displaying area codes and associated states
	for(int i = 0; i < vec_names.size(); i++)
		cout << "\t"<<vec_state[i].state <<"\t"<< vec_state[i].areaCode << endl;		
}


/*
	this function is responsible for searching each of telephone area code from
	names and telephone array and its match in area code and state file. 
	if matches then it simply displays the name of the guy, its state and area code
*/
void searchAreaCode(vector<location> vec_state, vector<personal> vec_names) {
	
	cout<<"\n Searching telephone numbers containing area code\n\n";
	
	for(int i = 0; i < vec_names.size(); i++) {	// iterating through all names
		
		for(int j = 0; j < vec_state.size(); j++){	// iterating through all states and area codes

			if(vec_names[i].telephone.substr(1,3) == vec_state[j].areaCode)
				cout << "\t"<<vec_names[i].name <<"\n\t"<< vec_names[i].telephone.substr(1,3)<<" Lives in : "<< vec_state[j].state << "\n\n";		
		}
	}	
}






