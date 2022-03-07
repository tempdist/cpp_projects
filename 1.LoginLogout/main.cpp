#include <iostream>
#include <fstream>
#include <string>
#include <termios.h>
#include <cstring>
#include <unistd.h>

#define MAXPW 32

using namespace std;

ssize_t getpasswd (char **pw, size_t sz, int mask, FILE *fp){
	if(pw == nullptr || !sz || fp == nullptr) return -1;
#ifndef MAXPW
if(sz > MAXPW) sz = MAXPW;
#endif

	if(*pw == NULL){
		void *tmp = realloc(*pw, sz * sizeof **pw);
		if(!tmp)
		return -1;
		memset (tmp, 0, sz);
		*pw = (char*) tmp;
	}
	size_t idx = 0;
	int c = 0;
	struct termios old_kbd_mode;
	struct termios new_kbd_mode;
	if(tcgetattr(0, &old_kbd_mode)){
		fprintf(stderr, "%s() error: tcgetattr failed.\n", __func__);
		return -1;
	}
	memcpy (&new_kbd_mode, &old_kbd_mode, sizeof(struct termios));

	new_kbd_mode.c_lflag &= ~(ICANON | ECHO);  /* new kbd flags */
	new_kbd_mode.c_cc[VTIME] = 0;
	new_kbd_mode.c_cc[VMIN] = 1;
	if (tcsetattr (0, TCSANOW, &new_kbd_mode)) {
		fprintf (stderr, "%s() error: tcsetattr failed.\n", __func__);
		return -1;
	}

	/* read chars from fp, mask if valid char specified */
	while (((c = fgetc (fp)) != '\n' && c != EOF && idx < sz - 1) ||
		(idx == sz - 1 && c == 127))
    {
        if (c != 127) {
            if (31 < mask && mask < 127)    /* valid ascii char */
                fputc (mask, stdout);
            (*pw)[idx++] = c;
        }
        else if (idx > 0) {         /* handle backspace (del)   */
            if (31 < mask && mask < 127) {
                fputc (0x8, stdout);
                fputc (' ', stdout);
                fputc (0x8, stdout);
            }
            (*pw)[--idx] = 0;
        }
    }
    (*pw)[idx] = 0; /* null-terminate   */

    /* reset original keyboard  */
    if (tcsetattr (0, TCSANOW, &old_kbd_mode)) {
        fprintf (stderr, "%s() error: tcsetattr failed.\n", __func__);
        return -1;
    }

    if (idx == sz - 1 && c != '\n') /* warn if pw truncated */
        fprintf (stderr, " (%s() warning: truncated at %zu chars.)\n",
                __func__, sz - 1);

    return idx; /* number of chars in passwd    */

}

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