//+++++++++++++++++++++++++++++++++++++
// Author: Luis D. Chaparro
// Program: Linked List Implementation
// Date: 08/05/2015
// DESCRIPTION:  Adds the capability to enter data for all of the fields
//				 listed for each entry (name) in the Address Book. 
//    			 Entry of the data requires a significant number of 
//				 individual commands, each with possible connections to 
//      		 multiple fields.
//+++++++++++++++++++++++++++++++++++++
#include <sstream>
#include <vector>
#include <fstream>
#include <iostream> 
#include <iomanip>
#include <string>
#include <cstdlib>
#include "Linked_List.h"
using namespace std;

//Function Prototypes
void mainMenu(string &menuSel);
void commands(List &contact, vector<string> &value);
void commandMenu();

// MAIN FUNCTION
int main(){
	bool status = true;
	string menuSel = "0";
	vector<string>value;
	vector<string>command;
	List person1;
	
	//cout << "File Location: " << argv[1] << endl;	
	
	while(status){
		// MENU
		mainMenu(menuSel);
		
		// Puts command line input into vector
		string line, line2;
		stringstream ss(menuSel);
		while(getline(ss, line)) 
		{
			size_t prev = 0, pos;
			while ((pos = line.find_first_of(" <>", prev)) != string::npos)
			{
				if (pos > prev)
					value.push_back(line.substr(prev, pos-prev));
				prev = pos+1;
			}
			if (prev < line.length())
				value.push_back(line.substr(prev, string::npos));
		}
		
		if(value[0] == "file"){
			value.clear();
			
			string fileAddress;
			cout << "Enter full file address.\ncmd>";
			
			getline(cin, fileAddress);				
			ifstream addressBook(fileAddress.c_str(), ios::in); // /home/pwb0013/csce2100/program3/data/Progam3_Data.csv
			
			if (addressBook.fail())			{
				cout << "ERROR: cannot open the file.\n";
				exit(EXIT_FAILURE);
			}else{
				//cout << "Success" << endl;
			}
			
			
			
			while(!addressBook.eof()){				
				getline(addressBook, line2, '\n');
				command.push_back(line2);
			}
			
			for(int i = 0; i < command.size(); i++){				
				stringstream ss(command[i]);
				while(getline(ss, line2)){
					size_t prev = 0, pos;
					while ((pos = line2.find_first_of(" ,\r", prev)) != string::npos)// "\r" converts from Windows to Unix text file
					{
						if (pos > prev)
							value.push_back(line2.substr(prev, pos-prev));
						prev = pos+1;
					}
					if (prev < line2.length())
						value.push_back(line2.substr(prev, string::npos));
					
					
					commands(person1, value);					
				}
			}
		}
		
		commands(person1, value);			
		
	}
	return 0;	
}
// MAIN MENU FUNCTION
void mainMenu(string &menuSel){	
	static int count = 0;
	if(count == 0){
		system("clear");
	}else{
		cout << "Press enter to continue...\n";
		cin.ignore();
		system("clear");
	}
	count++;
	// Welcome Screen
	cout << "\n\n++++++++++++++++++++++++++++++++++\n";
	cout << 	"***   Group E's Address Book   ***\n";
	cout << 	"++++++++++++++++++++++++++++++++++\n\n";
	
	// Main Menu
	cout << " Commands: \n";
	cout << "~~~~~~~~~~~~~~\n";
	cout << "a. ADD\n";
	cout << "b. SEARCH\n";
	cout << "c. REMOVE\n";
	cout << "d. PRINT\n";
	cout << "e. FILE\n";
	cout << "f. FTREE\n";
	cout << "g. COMMANDS (detailed)\n";
	cout << "h. QUIT\n\n";
	cout << "cmd> ";
	getline(cin, menuSel);
}
void commandMenu(){
	// Welcome Screen
	cout << "\n\n++++++++++++++++++++++++++++++++++\n";
	cout << 	"***   Group E's Address Book   ***\n";
	cout << 	"++++++++++++++++++++++++++++++++++\n\n";
	
	// Main Menu
	cout << " Detailed Command List: \n";
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~\n";
	cout << "add name <name>  ==>  Add a new name (First Last) to the Address Book\n";
	cout << "add spouse <uid> <name>  ==> Add spouse of <uid> (First Last) to the Address Book\n";
	cout << "add child  <uid> <name>  ==>  Add a child of <uid> (First Last) to the Address Book\n";
	cout << "add address1 <uid> <address>  ==> Add/change the address for <uid>\n";
	cout << "add city <uid> <city>    ==> Add/change the city for <uid>\n";
	cout << "add state <uid> <state>  ==> Add/change the state for <uid>\n";
	cout << "add zip <uid> <zipcode>  ==> Add/change the zipcode for <uid>\n";
	cout << "add date_birth <uid> <ddmmyyyy>  ==> Add/change the birthday for <uid>\n";
	cout << "add date_wedding <uid> <ddmmyyyy>   ==> Add/change the wedding day for <uid>\n";
	cout << "add date_death <uid> <ddmmyyyy>   ==> Add/change the date of death for <uid>\n";
	cout << "search <name>  ==> searches for name (First Last) and returns the <uid>, if found\n";
	cout << "print all ==>  Prints a list of ALL of the names in the Address Book with their <uid>\n";
	cout << "print <uid>  ==>  Prints all of the fields for <uid>\n";
	cout << "file  ==>  user is prompted for a filename that contains correctly formatted commands\n";
	cout << "		--- the file must be in CSV format with one full command per line\n";
	cout << "quit  ==>  processing complete\n";
}
void commands(List &contact, vector<string> &value){
	// COMMANDS
	if(value[0] == "commands"){
		commandMenu();
		value.clear();
	}
	// ADD
	else if(value[0] == "add"){
		if(value[1] == "name"){
			contact.addNames(value[2] + " " + value[3]);
			value.clear();
		}
		else if(value[1] == "spouse"){				
			int spouseID = contact.addNames(value[3] + " " + value[4]);
			if(spouseID == -1){
				cout << "ALREADY IN LIST: " << contact.convertUpper(value[3] + " " + value[4]) << endl;
				goto finished;
			}
			
			size_t pos = value[2].find("ID");
			string str = value[2].substr(pos+2);
			int ID;
			istringstream(str) >> ID;
			contact.addSpouse(ID, spouseID);
			value.clear();				
		}
		// FIX ADDCHILD FUNCTION "-1"
		else if(value[1] == "child"){
			int childID = contact.addNames(value[3] + " " + value[4]);
			if(childID == -1){
				cout << "ALREADY IN LIST: " << contact.convertUpper(value[3] + " " + value[4]) << endl;
				goto finished;
			}
			
			size_t pos = value[2].find("ID");
			string str = value[2].substr(pos+2);
			int ID;
			istringstream(str) >> ID;				
			contact.addChild(ID, childID);
			value.clear();				
		}
		// ADDRESS
		else if(value[1] == "address1" || value[1] == "city" || value[1] == "state"){
			string fieldValue;
			
			size_t pos = value[2].find("ID");
			string str = value[2].substr(pos+2);
			int ID;
			istringstream(str) >> ID;
			
			fieldValue = value[3];
			if(value.size() > 3){
				for(int t=4; t<value.size();t++)
					fieldValue.append(" " + value[t]);
			}
			contact.addFields(value[1], fieldValue, 0, ID);
			cout << "ADDED " << contact.convertUpper(value[1]) << ": " << contact.convertUpper(fieldValue) << " UID: " << setfill('0') << setw(3) << ID << endl << endl;
			value.clear();				
		}			
		// ZIP
		else if(value[1] == "zip"){
			size_t pos = value[2].find("ID");
			string str = value[2].substr(pos+2);
			int ID;
			istringstream(str) >> ID;
			
			int zip;
			istringstream(value[3]) >> zip;
			contact.addFields(value[1], "0", zip, ID);
			cout << "ADDED " << value[1] << ": " << value[3] << " UID: " << setfill('0') << setw(3) << ID << endl << endl;
			value.clear();	
		}
		else if(value[1] == "date_birth"){
			size_t pos = value[2].find("ID");
			string str = value[2].substr(pos+2);
			int ID;
			istringstream(str) >> ID;
			
			contact.addFields("Bdate", value[3], 0, ID);
			cout << "ADDED " << "BIRTHDAY: " << contact.dateFix(value[3]) << " UID: " << setfill('0') << setw(3) << ID << endl << endl;
			value.clear();	
		}
		else if(value[1] == "date_death"){
			size_t pos = value[2].find("ID");
			string str = value[2].substr(pos+2);
			int ID;
			istringstream(str) >> ID;
			
			contact.addFields("Ddate", value[3], 0, ID);
			cout << "ADDED " << "DATE of DEATH: " << contact.dateFix(value[3]) << " UID: " << setfill('0') << setw(3) << ID << endl << endl;
			value.clear();	
		}
		else if(value[1] == "date_wedding"){
			size_t pos = value[2].find("ID");
			string str = value[2].substr(pos+2);
			int ID;
			istringstream(str) >> ID;
			
			contact.addFields("Wdate", value[3], 0, ID);
			cout << "ADDED " << "WEDDING-DAY: " << contact.dateFix(value[3]) << " UID: " << setfill('0') << setw(3) << ID << endl << endl;
			value.clear();	
		}
	}
	// DELETE
	else if(value[0] == "remove"){
		contact.deleteNode(value[1] + " " + value[2]);
		value.clear();
	}
	// SEARCH
	else if(value[0] == "search"){			
		contact.searchNode(value[1] + " " + value[2]);
		value.clear();
	}		
	// PRINT
	else if(value[0] == "print"){
		// PRINT ALL
		if(value[1] == "all"){
			contact.printList();
			value.clear();
		}
		// PRINT ID
		else{
			size_t pos = value[1].find("ID");
			string str = value[1].substr(pos+2);
			int ID;
			istringstream(str) >> ID;
			contact.printListID(ID);
			value.clear();				
		}
	}
	// FTREE
	else if(value[0] == "ftree"){
			size_t pos = value[1].find("ID");
			string str = value[1].substr(pos+2);
			int ID;
			istringstream(str) >> ID;
			contact.printTree(ID);
			value.clear();				
	}
	// QUIT
	else if(value[0] == "quit"){
		cout << "Processing complete..." << endl;
		exit(EXIT_SUCCESS);
	}
	else{
		finished:
		value.clear();
	}
}