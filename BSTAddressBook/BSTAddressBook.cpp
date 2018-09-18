// BSTAddressBook.cpp : Defines the entry point for the console application.
//





#include "stdafx.h"
#include "PhBookEntry.h"
#include "BinarySearchTree.h"
using namespace std;

void DisplayMenu(TreeType<CPhBookEntry>& phBook);
int Menu();
void KeyboardKeyListener();
void DisplayLastName();
void ClearPhoneBook(TreeType<CPhBookEntry>& phBook);
void AddNewContact(TreeType<CPhBookEntry>& phBook);
void SearchByLetter(TreeType<CPhBookEntry>& phBook);
void SearchBySurname();
void DisplayAll(TreeType<CPhBookEntry>& phBook);
void DeleteContact();
void gotoxy(int x, int y);
TreeType<CPhBookEntry> phBook;
vector<CPhBookEntry> list;
bool quitFlag = false;
bool lastnameChanged = false;
string lastname;
bool firstTime = true;

int _tmain(int argc, _TCHAR* argv[])
{
	ofstream outfile("PhoneBook.txt");
	string name, surname, phoneNo;

	ifstream infile("data1.txt");
	if (!infile)
	{
		cout << "File not found (data1.txt)";
		cin.get();
	}
	else
	{
		while (!infile.eof())
		{
			infile >> name >> surname >> phoneNo;

			CPhBookEntry newEntry(name, surname, phoneNo);
			phBook.InsertItem(newEntry);
		}
	}
	DisplayMenu(phBook);
	phBook.PrintTree(outfile);

	TreeType<int> tree;
	tree.InsertItem(5);
	cout << tree.NumberOfNodes();

	return 0;
}

void ClearPhoneBook(TreeType<CPhBookEntry>& phBook)
{
	if (!phBook.IsEmpty())
	{
		cout << "\n\tPhone book is cleared.";
		phBook.MakeEmpty();
	}
	else
		cout << "\n\tPhone book is emtpy, nothing to clear.";
	cin.get(); cin.get();
	
}


void AddNewContact(TreeType<CPhBookEntry>& phBook)
{
	system("cls");
	string name, surname, phNo;
	cout << "\n\tEnter Name, Surname, and Phone Number: ";
	cin >> name >> surname >> phNo;
	CPhBookEntry newContact(name, surname, phNo);
	
	phBook.InsertItem(newContact);

}

void SearchByLetter(TreeType<CPhBookEntry>& phBook)
{
	if (phBook.IsEmpty())
	{
		cout << "\n\tPhone book is empty.";
		cin.get(); cin.get();
	}
	
	else
	{
		KeyboardKeyListener();
	}
}

void DeleteContact()
{
	if (phBook.IsEmpty())
		cout << "\n\tPhone book is empty.";
	else
	{
		system("cls");
		string name, surname;
		cout << "\tPress 0 to exit";
		cout << "\n\tEnter name and surname of the contact you want to delete: ";


		cin >> name;
		if (name != "0")
		{
			cin >> surname;
			CPhBookEntry newContact(name, surname, "");
			bool found;
			phBook.RetrieveItem(newContact, found);
			if (found)
			{
				phBook.DeleteItem(newContact);
				cout << "\n\tContact deleted.";
			}

			else
				cout << "\n\tThere is no contact with that surname!";
		}
	}
	
	
	cout << "\n\tPress any key to return...";
	cin.get(); cin.get();
}

void SearchBySurname()
{
	if (phBook.IsEmpty())
		cout << "\n\tPhone book is empty.";
	else
	{
		system("cls");
		string surname;
		cout << "\n\tEnter Surname of the contact you want to search: ";
		cin >> surname;
		cout << endl << setw(20) << "Last name" << setw(20) << "First name" << setw(20) << "Phone No.";
		cout << "\n------------------------------------------------------------------------\n\n";

		surname[0] = tolower(surname[0]);

		vector<CPhBookEntry> list2;
		phBook.HasA(surname, list2);

		for each (CPhBookEntry entry in list2)
		{
			cout << entry;
		}
		
	}
	cin.get(); cin.get();
}
void DisplayMenu(TreeType<CPhBookEntry>& phBook)
{
	do
	{
		system("cls");
		switch (Menu())
		{
		case 1:
			ClearPhoneBook(phBook);
			break;
		case 2:
			AddNewContact(phBook);
			break;
		case 3:
			DeleteContact();
			break;
		case 4:
			SearchByLetter(phBook);
			break;
		case 5:
			SearchBySurname();
			break;
		case 6:
			DisplayAll(phBook);
			break;
		case 7:
			quitFlag = true;
			break;
		default:
			cout << "\n\tInvalid option!";
			cin.ignore(); cin.ignore();
		}

	} while (!quitFlag);

}
int Menu()
{
	int option;
	do{
		system("cls");
		cout << "\n\n\t1. Clear address book\n"
			<< "\t2. Add new contact\n"
			<< "\t3. Remove a contact\n"
			<< "\t4. Search by letter\n"
			<< "\t5. Search by surname\n"
			<< "\t6. Display all\n"
			<< "\n\t7. Quit\n"
			<< "\n\tYour option: ";

		cin >> option;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore();
		}
	} while (cin.fail());

	return option;
}


void DisplayLastName()
{	
	if (lastnameChanged || firstTime)
	{
		
		system("cls");
		if (lastname.length() > 0)
			phBook.HasA(lastname, list);
		if (lastname.length() == 0)
			list.clear();
		cout << "\n\tFilter contacts as you type (Press ESC to return to main menu)";
		cout << "\n--------------------------------------------------------------------------\n\n\nLast name: " << lastname << endl << "------------------------\n";

		for each (CPhBookEntry ent in list)
		{

			cout << ent.GetLastName() << endl;
		}
		lastnameChanged = false;
	}

	firstTime = false;
	
}

void KeyboardKeyListener()
{
	bool firstTimeEnter = true;
	//						GetAsyncKeyState
	// The function queries current state of keyboard keys (at the time of the call). 
	//   The function returns 0 if key is NOT pressed and value < 0 ( less than zero) when key is currently pressed. 

	DisplayLastName();
	bool changed = false;
	

	int j = 0;
	while (true)
	{
	
		for (int i = 8; i <= 90; i++)
		{
			//if key(i) is pressed
			if (GetAsyncKeyState(i) < 0)
			{
				
				j = i;
				//this key is still pressed, so I dont want to keep printing it
				if (changed)
					continue;
				else
				{
					//if backspace pressed
					if (i == 8)
					{
						int length = lastname.length();
						lastname = lastname.substr(0, length - 1);
						system("cls");
						changed = true;
						lastnameChanged = true;

					}
					else if (i == 13 && firstTimeEnter == false)
					{
						vector<CPhBookEntry> list2;
						phBook.HasA(lastname, list2);
						cout << endl << setw(20) << "Last name" << setw(20) << "First name" << setw(20) << "Phone No.";
						cout << "\n------------------------------------------------------------------------\n\n";
						for each (CPhBookEntry entry in list2)
						{
							cout << entry;
						}
						changed = true;
					}
					//if letter pressed
					else
					{
						if (i >= 65 && i <= 90)
						{
							lastname += tolower(i);
							changed = true;
							lastnameChanged = true;
							firstTimeEnter = false;
						
						}
					}
				}
			
			}
			//if key is not pressed 
			//when key was pressed have to assign that keys int value to j
			//so when key j is not pressed toggle changed status (this is done to limit key print once per key press)
			if (GetAsyncKeyState(j) == 0)
			{
				if (!changed)
					continue;
				else
					changed = false;
			}
			
		}
		DisplayLastName();
		Sleep(50);
		//exit if escpace pressed 
		if (GetAsyncKeyState(VK_ESCAPE))
			break;
	}
	firstTime = true;
	lastname = "";
}

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void DisplayAll(TreeType<CPhBookEntry>& phBook)
{
	if (phBook.IsEmpty())
		cout << "\n\tPhone book is empty.";
	else
	{
		system("cls");
		cout << endl << endl << setw(20) << "Surname" << setw(20) << "Name" << setw(20) << "Phone No" << "\n-------------------------------------------------------------------\n";
		phBook.Display();
	}
	cin.get(); cin.get();
}