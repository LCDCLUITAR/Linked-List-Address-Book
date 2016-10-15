//*******************************
// Address_Book by Luis Chaparro
//*******************************
#ifndef LIST_H
#define LIST_H
#include <string>
#include <vector>
using namespace std;

class List{
	private:
		typedef struct node{
			int ID;
			string name;
			string ADDRESS;
 			string CITY;
 			string STATE;
 			int    ZIP;
 			string BIRTHDATE;
 			string DEATHDATE;
 			string WEDDING_DATE;
			node* next;
			node* prev;
			
			node* spousePtr;
			vector<node*>childPtr;
			
		}* nodePtr;
		
		nodePtr head;
		nodePtr tail;
		nodePtr n;
		nodePtr temp;
		
	public:
		// TOOLS
		List();
		string limiter(string field, string value);
		string convertUpper(string str);
		string dupData(string uniqName);
		string dateFix(string date);
		
		// ADDING
		int addNames(string);
		void addFields(string, string, int, int);
		void addSpouse(int, int);
		void addChild(int, int);
		
		// OTHER OPTIONS
		void searchByID(nodePtr &, int);
		void searchNode(string searchName);
		void deleteNode(string delName);
		void printList();
		void printListID(int ID);
		void printTree(int);
};

#endif // LIST_H