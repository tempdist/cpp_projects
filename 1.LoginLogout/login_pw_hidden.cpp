#include <iostream>
#include <fstream>
#include <string>
#include <termios.h>
#include <cstring>
#include <unistd.h>

#define MAXPW 32

using namespace std;

// ssize_t getpasswd (char **pw, size_t sz, int mask, FILE *fp){
// 	if(pw == nullptr || !sz || fp == nullptr) return -1;
// #ifndef MAXPW
// if(sz > MAXPW) sz = MAXPW;
// #endif
// 
// 	if(*pw == NULL){
		// void *tmp = realloc(*pw, sz * sizeof **pw);
// 		if(!tmp)
// 		return -1;
// 		memset (tmp, 0, sz);
// 		*pw = (char*) tmp;
// 	}
// }

bool IsLoggedIn()
{
	string username, un, pw;
	char * password;

	cout << "Enter username: "; cin >> username;
	password = getpass("Select a password: ");
//		printf("%s\n", password);
//	cout << "Enter password: "; cin >> password;

	ifstream read("/home/abhineet/Documents/Personal/Purple Cat/Projects/1.LoginLogout" + username + ".txt");
	getline(read, un);
	getline(read, pw);

	if(un == username && pw == password)
	{
		return true;
	}
	else {
		return false;
	}
}

int main() 
{
	int choice;

	cout << "1: Register\n2: Login\nYour choice: "; cin >> choice;
	if(choice == 1)
	{
		string username, password;
		char * pwd;
		cout << "Select a username: "; cin >> username;
		pwd = getpass("Select a password: ");
//		printf("%s\n", pwd);
//		cout << "Select a password: "; cin >> pwd;


		ofstream file;
		file.open("/home/abhineet/Documents/Personal/Purple Cat/Projects/1.LoginLogout" + username + ".txt");
		file << username << endl << password;
		file.close();
	}
	else if(choice == 2) {
		bool status = IsLoggedIn();
		if (!status) {
			cout << "False login!" << endl;
			return 0;
		}
		else {
			cout << "Login successful!" << endl;
			return 1;
		}
	}
}