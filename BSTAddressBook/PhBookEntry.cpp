#include "stdafx.h"
#include "PhBookEntry.h"
 

CPhBookEntry::CPhBookEntry()
{
}


CPhBookEntry::~CPhBookEntry()
{
}


CPhBookEntry::CPhBookEntry(string aName,string aSurname, string aPhoneNo)
{
	_firstName = aName;
	_lastName = aSurname;
	_phoneNo = aPhoneNo;
}
bool CPhBookEntry::operator>(CPhBookEntry entry)
{
	if (_lastName.compare(entry._lastName) == 0)
		if (_firstName.compare(entry._firstName)>0)
			return true;
	if (_lastName.compare(entry._lastName) > 0)
		return true;
	return false;
}
bool CPhBookEntry::operator==(string entry)
{
	int length = entry.length();
	string name = _lastName;
	transform(name.begin(), name.end(), name.begin(), ::tolower);
	if (name.substr(0,length).compare(entry) == 0)
		return true;
	return false;
}
bool CPhBookEntry::operator==(CPhBookEntry entry)
{
	return (_firstName == entry._firstName && _lastName == entry._lastName && _phoneNo == entry._phoneNo);
}
bool CPhBookEntry::operator<(CPhBookEntry entry)
{
	if (_lastName.compare(entry._lastName) == 0)
		if (_firstName.compare(entry._firstName)<0)
			return true;
	if(_lastName.compare(entry._lastName) < 0)
		return true;
	return false;
	
}
ostream& operator << (ostream& os, CPhBookEntry& ent)
{

	os << setw(20) <<ent.GetLastName() << setw(20) << ent.GetFirstName() << setw(20) << ent.GetPhoneNo() << endl;
		
	
	return os;
}
string CPhBookEntry::GetFirstName()
{
	return _firstName;
}
string CPhBookEntry::GetLastName()
{
	return _lastName;
}
string CPhBookEntry::GetPhoneNo()
{
	return _phoneNo;
}