#pragma once
using namespace std;
//
class CPhBookEntry
{
public:
	CPhBookEntry();
	~CPhBookEntry();
private:
	string _firstName;
	string _lastName;
	string _phoneNo;
public:
	CPhBookEntry(string aName, string aSurname, string aPhoneNo);
	bool operator>(CPhBookEntry entry);
	bool operator==(string entry);
	bool operator==(CPhBookEntry entry);
	bool operator<(CPhBookEntry entry);
	friend ostream& operator<<(ostream& os, CPhBookEntry&);
	string GetFirstName();
	string GetLastName();
	string GetPhoneNo();
};

