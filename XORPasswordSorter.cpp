// Name: Caleb Tseng-Tham

// Personal Password Program
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <string>

using namespace std; 
// Current Key is ABC
// Second Test is CAT
const char key1 = 'A';
const char key2 = 'B';
const char key3 = 'C';

class Password {
private:
	string type;
	string username;
	string password; 
public:
	setPassword ()
	{
	 type = "EMPTY_TYPE";
	 username = "EMPTY_USERNAME";
	 password = "EMPTY_PASSWORD";
	}
	setPassword (string type, string username, string password)
	{
		(*this).type = type; 
		(*this).username = username;
		(*this).password = password; 
	}
	string getType () const
	{
		return (*this).type;
	}
	string getUsername () const
	{
		return (*this).username; 
	}
	string getPassword () const
	{
		return (*this).password; 
	}
};

int checkSize (ifstream & fin);
void readFile (ifstream & fin, int size, Password passwordList []);
void output (ostream & out,Password passwordList [], int size, string searchType, bool coutFout, const char key1, const char key2, const char key3); 
void clearEntry (int choice, Password passwordList[]); 
void waitForChoice (int & choice);
void outputNewPassword (ostream & out, string newType, string newUsername, string newPassword, const char key1, const char key2, const char key3);

int main()
{
	int size = 0;
	int choice = 0; 
	string searchType = ""; 
	ifstream fin("Passwords.txt");
	
	if(!fin)
	{
		cout << "The Passwords.txt file did not open. " << endl;
		return EXIT_FAILURE;
	}
	
	size = checkSize (fin);
	const int SIZE_LIST = size; 
	Password passwordList [SIZE_LIST];
	
	cout << "There are " << size << " passwords." << endl; 
	cout << endl; 
	fin.close();
	ifstream fin2("Passwords.txt");
	readFile (fin2, size, passwordList);
	cout << "What type of password are you looking for? Type 'ALL' to reveal entire list." << endl;
	cout << "Otherwise, just type in (case-sensitive) the name of the password type. e.g. facebook" << endl; 
	cout << "Be careful with typing in capital K, it breaks the program." << endl; 
	cout << " (Just try not to type in Capital letter in general. SPACES NOT ALLOWED" << endl; 
	cin >> searchType; 
	cout << endl; 
	output (cout,passwordList,size,searchType,false,key1,key2,key3);
	cout << endl;
	
	
	
	cout << "Would you like to clear an entry? (Yes = 1/No = 0)" << endl; 
	waitForChoice (choice);
	if (choice == 1)
	{
		int clearChoice = 0; 
		cout << "Which entry # would you like to clear?" << endl;
		cin >> clearChoice; 
		clearEntry (clearChoice,passwordList);
		cout << endl; 
		cout << "The entry has been removed" << endl; 
	}
	
	cout << "Would you like to add a new entry? (Yes = 1/No = 0)" << endl; 
	waitForChoice (choice);
	string newType = "", newUsername = "", newPassword = ""; 
	if (choice == 1)
	{
		cout << "Enter new type:";
		cin >> newType; 
		cout << "Enter new username:";
		cin >> newUsername; 
		cout << "Enter new password:";
		cin >> newPassword; 
	}
	cout << "Outputting list to a new file." << endl; 
	ofstream fout("Passwords.txt");
	output (fout,passwordList,size,"ALL",true,key1,key2,key3);
	if (choice == 1)
	{
		outputNewPassword (fout,newType,newUsername,newPassword,key1,key2,key3);
	}
	fin.close();
	fout.close();
	return 0; 
}

void waitForChoice (int & choice)
{
	do 
	{
	cin >> choice; 
	} while (choice != 1 && choice != 0);
}

void clearEntry (int clearChoice, Password passwordList[])
{
	passwordList [clearChoice-1].setPassword(); 
}

int checkSize (ifstream & fin)
{
	string holder = ""; 
	int counter = 0;
	while (getline (fin,holder) && getline (fin,holder) && getline (fin,holder))
	{
		counter ++;
	}
	return counter; 
}


void readFile (ifstream & fin, int size, Password passwordList [])
{
	string type = "", username = "", password = ""; 
	for (int index = 0; index < size; index ++)
	{
		getline (fin,type) ;
		getline (fin,username);
		getline (fin,password);
		passwordList[index].setPassword(type,username,password); 
	}
}

string encryptDecrypt (string & toProcess, char key)
{
	string output = toProcess; 
	for (int encDec = 0; encDec < toProcess.size (); encDec ++)
	{
		output [encDec] = toProcess[encDec] ^ key;
	}
	return output; 
}

void output (ostream & out,Password passwordList [], int size, string searchType, bool coutFout, const char key1, const char key2, const char key3)
{
	string typeOut = "", usernameOut = "", passwordOut = ""; 
		for (int index = 0; index < size; index ++)
	{
		typeOut = passwordList[index].getType();
		usernameOut = passwordList[index].getUsername();
		passwordOut = passwordList[index].getPassword();
		if (coutFout == false) 
		{	
			typeOut = encryptDecrypt(typeOut,key1);
			usernameOut = encryptDecrypt(usernameOut,key2); 
			passwordOut = encryptDecrypt(passwordOut,key3);
		}
		if (searchType == typeOut || searchType == "ALL" && typeOut != "EMPTY_TYPE")
		{
			out << typeOut << endl; 
			out << usernameOut << endl;
			out << passwordOut << endl;
			if (coutFout == false)
			{
			out << endl; 	
			} 
		}
	}
}

void outputNewPassword (ostream & out, string newType, string newUsername, string newPassword, const char key1, const char key2, const char key3)
{
	string typeOut = "", usernameOut = "", passwordOut = ""; 
	typeOut = encryptDecrypt(newType,key1);
	usernameOut = encryptDecrypt(newUsername,key2);
	passwordOut = encryptDecrypt(newPassword,key3);
	out << typeOut << endl;
	out << usernameOut << endl; 
	out << passwordOut << endl;
}

