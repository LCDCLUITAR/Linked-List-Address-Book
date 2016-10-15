//+++++++++++++++++++++++++++++++++++++
// Author: Luis D. Chaparro
// Program: Linked List Implementation
// Date: 08/05/2015
//+++++++++++++++++++++++++++++++++++++
#include <sstream>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <string>
#include "Linked_List.h"
using namespace std;
/*===========================================
++++++++++++++++ CONSTRUCTOR ++++++++++++++++
---
---    Sets all data to NULL
============================================*/
List::List(){
	head = NULL;
	temp = NULL;
	n 	 = NULL;
}
/*===========================================
++++++++++++++++ NAMELIMITER ++++++++++++++++
---
---    Limits the number of characters for name
============================================*/
string List::limiter(string field, string value){
	// NAME
	while(value.size() > 30 && field == "name"){
		cout << "Name cannot contain more than 30 characters, please enter name again\n>> ";
		getline(cin, value);
	}
	// ADDRESS
	while(value.size() > 100 && field == "address"){
		cout << "Address cannot contain more than 100 characters, please enter address again\n>> ";
		getline(cin, value);
	}
	// CITY
	while(value.size() > 20 && field == "city"){
		cout << "City cannot contain more than 20 characters, please enter city again\n>> ";
		getline(cin, value);
	}
	// STATE          
	while(value.size() > 2 && field == "state"){
		cout << "State cannot contain more than 2 characters, please enter a state again\n>> ";
		getline(cin, value);
	}
	// BIRTHDATE     
	while(value.size() != 1 && value.size() != 8 && field == "date"){
		cout << "Date cannot contain more than 8 characters, please enter date again\n>> ";
		cin >> value;
	}
	
	return value;	
}
/*===========================================
+++++++++++ ADDNAMES FUNCTION ++++++++++++
---
---    	 Adds a New Name to List
============================================*/
int List::addNames(string name){
	// New Node
	n = new node;
	static int count = 0;
	name = limiter("name", name);
	name = dupData(name);
	if(name == "-1")
		return -1;
	
	count++;
	
	// Set pointer if there is a head pointer
	if(head != NULL){
		n->spousePtr = NULL;
		
		n->ID = count;
		n->name = name;
		n->ADDRESS = "0";
		n->CITY = "0";
		n->STATE = "0";
		n->ZIP = 0;
		n->BIRTHDATE = "0";
		n->DEATHDATE = "0";
		
		n->prev = tail;
		tail->next = n;
		tail = n;
		tail->next = NULL;
		
		cout << "ADDED: " << name << "\tUID: " << setfill('0') << setw(3) << n->ID << endl << endl;		
		
	}else{ 						// if there is no head pointer
		// Name Fields
		n->spousePtr = NULL;
		
		n->ID = count;
		n->name = name;
		n->ADDRESS = "0";
		n->CITY = "0";
		n->STATE = "0";
		n->ZIP = 0;
		n->BIRTHDATE = "0";
		n->DEATHDATE = "0";
		
		n->prev = NULL;
		head = n;
		tail = n;
		tail->next = NULL;
		cout << "ADDED: " << convertUpper(name) << "\tUID: " << setfill('0') << setw(3) << n->ID << endl << endl;
	}
	
	return count;
}
/*===========================================
+++++++++++++ ADDFIELDS FUNCTION ++++++++++++
---
---    		  Adds Fields to Value
============================================*/
void List::addFields(string field, string value, int zip, int ID){
	
	n = new node;
	value = convertUpper(value);
	value = limiter(field, value);
	// ADDRESS
	if(field == "address1"){
		searchByID(n, ID);
		n->ADDRESS = value;
		if(n->spousePtr != NULL){
			n->spousePtr->ADDRESS = value;
		}
	}
	// CITY
	else if(field == "city"){
		searchByID(n, ID);
		n->CITY = value;
		if(n->spousePtr != NULL){
			n->spousePtr->CITY = value;
		}
	}
	// STATE          
	else if(field == "state"){
		searchByID(n, ID);
		n->STATE = value;
		if(n->spousePtr != NULL){
			n->spousePtr->STATE = value;
		}
	}
	// ZIP
	else if (field == "zip"){
		searchByID(n, ID);
		n->ZIP = zip;
		if(n->spousePtr != NULL){
			n->spousePtr->ZIP = zip;
		}
	}
	// BIRTHDATE     
	else if(field == "Bdate"){
		searchByID(n, ID);
		n->BIRTHDATE = value;
	}
	// DEATHDATE     
	else if(field == "Ddate"){
		searchByID(n, ID);
		n->DEATHDATE = value;
	}
	// WEDDING DATE     
	else if(field == "Wdate"){
		searchByID(n, ID);
		n->WEDDING_DATE = value;
		if(n->spousePtr != NULL){
			n->spousePtr->WEDDING_DATE = value;
		}
	}
}
/*===========================================
+++++++++++++ SEARCHBYID FUNCTION ++++++++++++
---
---    			Searches by ID
============================================*/
void List::searchByID(nodePtr &t, int ID){
	temp = head;
		
	while(temp != NULL && temp->ID != ID){
		temp = temp->next;
	}
	if(temp != NULL){
		t = temp;
	}else{
		cout << "Not Found: ERROR" << endl;
		t = NULL;
	}
}
/*===========================================
+++++++++++++ ADDCHILD FUNCTION ++++++++++++
---
---    			Adds Child
============================================*/
void List::addChild(int ID, int childID){
	nodePtr child = new node;
	
	// Child Fields
	string address, city, state, deathdate, birthdate;
	int zip = 0, spouseID = 0;
	address = city = state = deathdate = deathdate = "0";
	
	// Add Parent fields to variables	
	//searchByID(temp, ID);
	//address = temp->ADDRESS;
	//city    = temp->CITY;	
	//state   = temp->STATE;
	//zip     = temp->ZIP;	
		
	addFields("address1", address, 0, childID);
	addFields("city", city, 0, childID);
	addFields("state", state, 0, childID);
	addFields("zip", "0", zip, childID);
	
	searchByID(temp, childID);
	
	child = temp;
	// Add childPtr to both parents
	searchByID(temp, ID);
	temp->childPtr.push_back(child);	
	spouseID = temp->spousePtr->ID;
	searchByID(temp, spouseID);
	temp->childPtr.push_back(child);
	
}
/*===========================================
+++++++++++++ ADDSPOUSE FUNCTION ++++++++++++
---
---    			Adds Spouse
============================================*/
void List::addSpouse(int spouse1, int spouse2){	
	nodePtr wife = new node;
	
	// Spouse Fields
	string address, city, state, deathdate, birthdate, wedding_date;
	int zip = 0;
	address = city = state = deathdate = deathdate = wedding_date = "0";
	
	// Add spouse1 fields to variables	
	searchByID(temp, spouse1);
	address = temp->ADDRESS;
	city    = temp->CITY;	
	state   = temp->STATE;
	zip     = temp->ZIP;	
		
	addFields("address1", address, 0, spouse2);
	addFields("city", city, 0, spouse2);
	addFields("state", state, 0, spouse2);
	addFields("zip", "0", zip, spouse2);
	
	searchByID(temp, spouse2);
	addFields("Wdate", "0", 0, spouse1);
	addFields("Wdate", "0", 0, spouse2);
	
	wife = temp;
	// Add spousePtr to both pointers
	searchByID(temp, spouse1);
	
	wife->spousePtr = temp;
	temp->spousePtr = wife;
}
/*===========================================
+++++++++++++ DUPDATA FUNCTION ++++++++++++++
---
---    Adds unique ID to Duplicate Data
============================================*/
string List::dupData(string dupName){
	temp = head;
	
	while(temp != NULL){		
		if(temp->name == convertUpper(dupName)){
						
			cout << "Duplicate: " << convertUpper(dupName) << " UID: " << setfill('0') << setw(3) << temp->ID << endl << endl;
			dupName = "-1";
			return dupName;
		}else{
			temp = temp->next;
		}
	}
	
	return convertUpper(dupName);
}
/*===========================================
+++++++++++ SEARCHNODE FUNCTION ++++++++++++
---
---    Searches for data within the list
============================================*/
void List::searchNode(string searchName){
	temp = head;
	
	while(temp != NULL && convertUpper(temp->name) != convertUpper(searchName)){
		temp = temp->next;
	}
	if(temp == NULL){
		cout << "NOT FOUND: " << convertUpper(searchName) << endl;
	}else{
		cout << "FOUND: " << convertUpper(searchName) << " UID: " << setfill('0') << setw(3) << temp->ID << endl;
	}
}
/*===========================================
+++++++++++ DELETENODE FUNCTION ++++++++++++
---
---    Removes data from within the list
============================================*/
void List::deleteNode(string delName){
	nodePtr delPtr = NULL;
	temp = head;
	nodePtr curr = head;
	
	while(curr != NULL && convertUpper(curr->name) != convertUpper(delName)){
		temp = curr;
		curr = curr->next;
	}
	if(curr == NULL){
		cout << "ERROR: Not found for Removal: " << convertUpper(delName) << endl;
		delete delPtr;
	}else{
		delPtr = curr;	
		if(delPtr == head){
			head = head->next;
			temp = NULL;
		}
		else if(delPtr == tail){
			tail = tail->prev;
			tail->next = NULL;
		}
		else{
			curr = curr->next;
			temp->next = curr;
			curr->prev = temp;
			delete delPtr;
		}
		cout << "Removal successful: " << convertUpper(delName) << endl;
		nodePtr  t = head;
	}
}
/*===========================================
+++++++++++ PRINTLIST FUNCTION ++++++++++++
---
---    		Prints List of data
============================================*/
void List::printList(){
	temp = head;
	
	/*========================================================
	---    Sorts Names in alphabetical order by Last Name
	=========================================================*/
	nodePtr search = new node;
	search = head;
	vector<string>nameTemp;
	
	while(search != NULL){
		string lastName, firstName;
		stringstream ss(search->name);// Sorts by Last Name
		ss >> firstName >> lastName;
		
		nameTemp.push_back(lastName+" "+firstName);
		search = search->next;
	}
	int lastElem = nameTemp.size();
    sort(nameTemp.begin(), nameTemp.end());
	for(int t=0; t < lastElem; t++){		
		string lastName, firstName;
		stringstream ss(nameTemp[t]);// Sorts back to First Name
		ss >> lastName >> firstName;
		
		nameTemp[t] = firstName+" "+lastName;
	}
	//==========================================================
	
	int j = 0, i = 0;
	while(i < nameTemp.size()){
		if(temp->name == nameTemp[j]){
			cout << "ID: " << setfill('0') << setw(3) << temp->ID << "  " << convertUpper(temp->name) << endl;
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;			
			temp = head;
			++i;
			j++;
		}else{
			temp = temp->next;			
		}
	}
}
/*===========================================
++++++++++ PRINTLISTID FUNCTION +++++++++++
---
---    	  Prints List of data by ID
============================================*/
void List::printListID(int ID){
	temp = NULL;
	searchByID(temp, ID);
	
	if(temp != NULL){
		cout << "\nID: " << setfill('0') << setw(3) << temp->ID << "  " << convertUpper(temp->name) << endl;
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << "\t Address:            " << convertUpper(temp->ADDRESS) << endl; 
		cout << "\t City:               " << convertUpper(temp->CITY) << endl;
		cout << "\t State:              " << convertUpper(temp->STATE) << endl; 
		cout << "\t Zip Code:           " << temp->ZIP << endl;
		cout << "\t Birth Date:         " << setfill('0') << dateFix(temp->BIRTHDATE) << endl; 
		cout << "\t DeathDate:          " << dateFix(temp->DEATHDATE) << endl;
		if(temp->spousePtr != NULL){
			cout << "\t Spouse:             " << convertUpper(temp->spousePtr->name) << endl;
			cout << "\t Wedding Date:       " << dateFix(temp->WEDDING_DATE) << endl;
			for(int c = 0; c < temp->childPtr.size(); c++){
				cout << "\t Child " << setfill('0') << setw(2) << c+1 << ":           " << convertUpper(temp->childPtr[c]->name) << endl;
			}
		}
		else{
			cout << "\t Spouse:             " << "N/A" << endl;
		}
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	}
}
/*===========================================
+++++++++++ DATEFIX FUNCTION ++++++++++++
---
---     Converts date to Month, dd yyyy
============================================*/
string List::dateFix(string date){
	string MONTHS[12] = {"January, ", "February, ", "March, ", "April, ", "May, ", "June, ", "July, ", "August, ", "September, ", "October, ", "November, ", "December, "};
	string 	day,
			month,
			year;
	

	if(date != "0"){
		day = date.substr(2, 2);
		month = date.substr(0,2);
		year = date.substr(4,4);
		if(month == "01")
			month = MONTHS[0];
		else if(month == "02")
			month = MONTHS[1];
		else if(month == "03")
			month = MONTHS[2];
		else if(month == "04")
			month = MONTHS[3];
		else if(month == "05")
			month = MONTHS[4];
		else if(month == "06")
			month = MONTHS[5];
		else if(month == "07")
			month = MONTHS[6];
		else if(month == "08")
			month = MONTHS[7];
		else if(month == "09")
			month = MONTHS[8];
		else if(month == "10")
			month = MONTHS[9];
		else if(month == "11")
			month = MONTHS[10];
		else if(month == "12")
			month = MONTHS[11];
		else
			//cout << "Month is incorrect" << endl;
		date = " ";
		date = month + day + " " + year;
	}
	
			
	return date;
}
/*===========================================
+++++++++++ CONVERTUPPER FUNCTION ++++++++++++
---
---     Converts Characters to upper case
============================================*/
string List::convertUpper(string str){
	string converted;

	for(short i = 0; i < str.size(); ++i)
		converted += toupper(str[i]);
	
	return converted;
}
/*===========================================
++++++++++++ PRINTTREE FUNCTION +++++++++++++
---
---          Prints a Family Tree
============================================*/
void List::printTree(int ID){
	temp = NULL;
	searchByID(temp, ID);
	int childNmbr = 0;
	
	if(temp->spousePtr != NULL){
		childNmbr = temp->childPtr.size();
		vector<string>grandChild;
		
		// Initializes vector to " "
		for(int i = 0; i <= 9; i++){
			grandChild.push_back(" ");
		}
		
		// IF 1 CHILDREN
		if(childNmbr == 1){
			int grandChildNmbr = 0;
			string 	parent1 = temp->name, 
					parent2 = temp->spousePtr->name, 
					child1  = temp->childPtr[0]->name;
			// Fills grandChild vector
			grandChildNmbr = temp->childPtr[0]->childPtr.size();
			for(int i = 0; i < grandChildNmbr; i++){
				grandChild[i] = temp->childPtr[0]->childPtr[i]->name;
			}		
			cout << setfill(' ');
			cout << "=========================|=========================|=========================" << endl;
			cout << "++++++++ Parents ++++++++ +++++++ Children ++++++++ +++++ GrandChildren +++++" << endl;
			cout << "                                                                             " << endl;
			cout << setw(67) << right << grandChild[0] << endl;
			cout << parent1 << setw(41-parent1.length()) << right << child1 << setw(26) << right << grandChild[1] << endl;
			cout << parent2 << setw(67-parent2.length()) << right << grandChild[2] << endl;
			cout << "===========================================================================" << endl;			
		}
		// IF 2 CHILDREN
		else if(childNmbr == 2){
			int grandChildNmbr = 0,
				grandChildNmbr2 = 0;
			string 	parent1 = temp->name, 
					parent2 = temp->spousePtr->name, 
					child1  = temp->childPtr[0]->name,
					child2  = temp->childPtr[1]->name;
			// Fills grandChild vector
			grandChildNmbr = temp->childPtr[0]->childPtr.size();
			for(int i = 0; i < grandChildNmbr; i++){
				grandChild[i] = temp->childPtr[0]->childPtr[i]->name;
			}	
			grandChildNmbr2 = temp->childPtr[1]->childPtr.size();
			for(int i = 3, j = 0; i < 3+grandChildNmbr2; i++){
				grandChild[i] = temp->childPtr[1]->childPtr[j]->name;
				j++;
			}	
			cout << setfill(' ');	
			cout << "=========================|=========================|=========================" << endl;
			cout << "++++++++ Parents ++++++++ +++++++ Children ++++++++ +++++ GrandChildren +++++" << endl;
			cout << "                                                                             " << endl;
			cout << setw(67) << right << grandChild[0] << endl;
			cout << parent1 << setw(41-parent1.length()) << right << child1 << setw(26) << right << grandChild[1] << endl;
			cout << setw(67) << right << grandChild[2] << endl;
			cout << "                                                      " << endl;
			cout << setw(67) << right << grandChild[3] << endl;
			cout << parent2 << setw(41-parent2.length()) << right << child2 << setw(26) << grandChild[4] << endl;
			cout << setw(67) << right << grandChild[5] << endl;
			cout << "===========================================================================" << endl;			
		}
		// IF 3 CHILDREN
		else if(childNmbr == 3){
			int grandChildNmbr = 0,
				grandChildNmbr2 = 0,
				grandChildNmbr3 = 0;
			string 	parent1 = temp->name, 
					parent2 = temp->spousePtr->name, 
					child1  = temp->childPtr[0]->name,
					child2  = temp->childPtr[1]->name,
					child3  = temp->childPtr[2]->name;
			// Fills grandChild vector
			grandChildNmbr = temp->childPtr[0]->childPtr.size();
			for(int i = 0; i < grandChildNmbr; i++){
				grandChild[i] = temp->childPtr[0]->childPtr[i]->name;
			}	
			grandChildNmbr2 = temp->childPtr[1]->childPtr.size();
			for(int i = 3, j = 0; i < 3+grandChildNmbr2; i++){
				grandChild[i] = temp->childPtr[1]->childPtr[j]->name;
				j++;
			}	
			grandChildNmbr3 = temp->childPtr[2]->childPtr.size();
			for(int i = 6, j = 0; i < 6+grandChildNmbr3; i++){
				grandChild[i] = temp->childPtr[2]->childPtr[j]->name;
				j++;
			}		
			cout << setfill(' ');	
			cout << "=========================|=========================|=========================" << endl;
			cout << "++++++++ Parents ++++++++ +++++++ Children ++++++++ +++++ GrandChildren +++++" << endl;
			cout << "                                                                             " << endl;
			cout << setw(66) << right << grandChild[0] << endl;
			cout << setw(41) << right << child1 << setw(26) << right << grandChild[1] << endl;
			cout << setw(66) << right << grandChild[2] << endl;
			cout << parent1 << endl;
			cout << setw(67) << right << grandChild[3] << endl;
			cout << setw(41) << right << child2 << setw(26) << right << grandChild[4] << endl;
			cout << setw(67) << right << grandChild[5] << endl;
			cout << parent2 << endl;
			cout << setw(67) << right << grandChild[6] << endl;
			cout << setw(41) << right << child3 << setw(26) << right << grandChild[7] << endl;
			cout << setw(67) << right << grandChild[8] << endl;
			cout << "===========================================================================" << endl;			
		}
	}
}






	