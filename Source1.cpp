#include "Header.h"
LMS lms;
void MainMenu() {
	while (true) {
		cout << "BAHRIA UNIVERSITY LMS (DEVELOPED BY ABDULLAH & DUR-E-SHAHWAR)\n";
		cout << "LOGIN AS\n";
		cout << "1. Admin\n";
		cout << "2. Teacher\n";
		cout << "3. Student\n";
		cout << "4. Exit\n";
		cout << "Select Option\n";
		int ch;
		cin >> ch;
		string id, pass;
		cout << "Enter ID : ";
		cin >> id;
		cout << "Enter password : ";
		cin >> pass;
		User* login = nullptr;
		switch (ch) {
		case 1: {
			login = lms.loginadmin(id, pass);
			break;
		}
		case 2: {
			login = lms.loginteacher(id, pass);
			break;
		}
		case 3: {
			login = lms.loginstudent(id, pass);
			break;
		}
		case 4: {
			cout << "BYE...SEE YOU SOON \n";
			return;
		}
		default:
			cout << "Invalid Option\n";
			continue;
		}
		if (login == nullptr)
		{
			cout << "Wrong Credential. Try Again...\n";
			continue;
		}
		login->Dispmenu();//polumorphism derive class object is also an object of base class
	}
}
int main() {
	MainMenu();
	return 0;
}