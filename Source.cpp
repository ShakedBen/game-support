#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
#include <ostream>
#include <string>
#include <fstream>
#include <time.h>
#include <Windows.h>
#include <wchar.h>
using namespace std;
void FAQ();
void ChooseSortOption();
void prevCasesOptions();
void printNewCases();
void changeStatusMenu();
void printTicket(int);
void printTicket(int,bool);
void ViewAllTicketHistory(string);
bool CheckLegalCode(int*,int,int);
typedef struct
{
	int code;
	string username;
	string date;
	string describedIssue;
	string Reason;
	string description;
	string department;
	string status;
	int severity;
	string responseDate;
	string response;
}Ticket;
typedef struct
{
	string username;
	string password;
	string firstname;
	string lastname;
	string email;
	string gender;
	string isAdmin;
}Account;
void AccountProblems(Ticket*);
void printPrevCases(Account*);

string Encrypt(string str) {
	string encrypted = "";
	int tmp;
	for (unsigned int i = 0; i < str.length(); i++) {
		tmp = str[i];
		encrypted += to_string(tmp) + " ";
	}
	return encrypted;
}
string Undo(string str) {
	string undo = "";
	while (str.length() > 0)
	{
		int start = 0;
		int last = str.find(" ");
		undo += char(stoi(str.substr(start, last)));
		str.erase(start, last + 1);
	}
	return undo;
}
Account* LoadData(int* size) {
	Account*  DB = NULL;
	fstream myfile;
	myfile.open("Accounts.txt");
	*size = 0;
	string tmp;
	while (myfile)
	{
		getline(myfile, tmp);
		*size = *size + 1;
	}
	myfile.close();
	*size = *size / 7;
	if (*size == 0)
		return NULL;

	//DB = (Account*)malloc(*size * sizeof(Account));
	DB = new Account[*size];
	if (DB == NULL)
		return NULL;
	myfile.open("Accounts.txt");
	for (int i = 0; i < *size; i++) {
		getline(myfile, tmp);
		DB[i].username = tmp;
		getline(myfile, tmp);
		DB[i].password = Undo(tmp);
		getline(myfile, tmp);
		DB[i].firstname = tmp;
		getline(myfile, tmp);
		DB[i].lastname = tmp;
		getline(myfile, tmp);
		DB[i].email = tmp;
		getline(myfile, tmp);
		DB[i].gender = tmp;
		getline(myfile, tmp);
		DB[i].isAdmin = tmp;
	}
	myfile.close();
	return DB;
}
Ticket* TicketDB = NULL;
int TicketDBsize;
Ticket* LoadTickets(int *size) {
	Ticket* T_DB = NULL;
	fstream file;
	file.open("Tickets.txt");
	*size = -1;
	string temp2;
	while (file) {
		getline(file, temp2);
		*size = *size + 1;
	}
	file.close();
	*size = *size / 11;
	if (!(*size))
		return NULL;
	TicketDBsize = *size;
	T_DB = new Ticket[*size];
	if (!(T_DB))
		return NULL;
	file.open("Tickets.txt");
	for (int i = 0; i < *size; i++) {
		getline(file, temp2);
		T_DB[i].code = stoi(temp2);
		getline(file, temp2);
		T_DB[i].username = temp2;
		getline(file, temp2);
		T_DB[i].date = temp2;
		getline(file, temp2);
		T_DB[i].describedIssue = temp2;
		getline(file, temp2);
		T_DB[i].Reason = temp2;
		getline(file, temp2);
		T_DB[i].description = temp2;
		getline(file, temp2);
		T_DB[i].department = temp2;
		getline(file, temp2);
		T_DB[i].status = temp2;
		getline(file, temp2);
		T_DB[i].severity = stoi(temp2);
		getline(file, temp2);
		T_DB[i].responseDate = temp2;
		getline(file, temp2);
		T_DB[i].response = temp2;
	}
	file.close();
	return T_DB;
}
int AccountDBsize;
Account* AccountDB = NULL;
bool isAlpha(char ch) {

	if (!(ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z'))
		return false;
	return true;
}
bool isNumerical(char ch) {
	if (!(ch >= '0'&&ch <= '9'))
		return false;
	return true;
}
bool isNameValid(string str) {
	int i;
	for (i = 0; i <= (int)str.size() - 1; i++) {
		if (!isalpha(str[i]))
			return false;
	}
	return true;
}
bool isUsernameTaken(string str) {
	/*ifstream myfile;
	string tmp;
	myfile.open("Accounts.txt");
	while (myfile)
	{
	getline(myfile, tmp);
	tmp = tmp.substr(9);
	if (tmp == str)
	{
	myfile.close();
	return false;
	}
	for(int b=0;b<7;b++)
	getline(myfile, tmp);
	}
	myfile.close();
	return true;
	*/
	for (int i = 0; i < AccountDBsize; i++)
	{
		if (AccountDB[i].username == str)
			return false;
	}
	return true;
}
bool isEmailValid(string adress)
{
	int index;
	string temp;

	if (adress.length() > 100)
		return false;
	index = adress.find('@');
	if (index != adress.find_last_of('@'))
		return false;
	if (index < 1)
		return false;
	temp = adress.substr(adress.length() - 4, 4);
	if ((temp == ".com") || (temp == ".net") || (temp == ".org") || (temp == ".edu"))
		return true;
	return false;
}
bool isUsernameValid(string str) {
	int i;
	for (i = 0; i <= (int)str.size() - 1; i++) {
		if (isAlpha(str[i]) == true || isNumerical(str[i]) == true)
			continue;
		else
			return false;
	}
	return true;
}
bool isPasswordValid(string str) {
	return isUsernameValid(str);
}
void PrintMainMenu() {
	cout << "*****************************************************************" << endl;
	cout << "*\t\t Welcome to Summoners War \t\t\t*" << endl;
	cout << "*****************************************************************" << endl;
	cout << "1.Play\n2.Settings\n3.Support\n4.Exit\n";
}
void PlayMenu()
{
	system("cls");
	cout << "*****************************************************************" << endl;
	cout << "*\t\t\tSummoners War \t\t\t\t*" << endl;
	cout << "*****************************************************************" << endl;
	cout << "This is where the player starts to play.\nWe assume the game already exists and do not code it on our own.\n\n";
	cout << "Press any key to continue...";
	getchar();
	system("cls");

}
void SettingsMenu()
{
	system("cls");
	cout << "*****************************************************************" << endl;
	cout << "*\t\t\tSummoners War \t\t\t\t*" << endl;
	cout << "*****************************************************************" << endl;
	cout << "This is where the player adjusts the game's settings.\n\n";
	cout << "Press any key to continue...";
	getchar();
	system("cls");
}
void PrintSupportMenu() {
	system("cls");
	cout << "*****************************************************************" << endl;
	cout << "*\t\tSummoners War Support System \t\t\t*" << endl;
	cout << "*****************************************************************" << endl;
	cout << "1.Sign-Up.\n2.Login.\n3.FAQ.\n4.Go back.\n";
}
Account* isValidLogin(string username, string password) {
	/*ifstream myfile;
	string tmpusername, tmppassword;
	myfile.open("Accounts.txt");
	while (myfile) {
	getline(myfile, tmpusername);
	tmpusername = tmpusername.substr(9);
	getline(myfile, tmppassword);
	tmppassword = tmppassword.substr(9);
	if (tmpusername == username && tmppassword == password)
	{
	for (int b = 0;b < 5;b++)
	getline(myfile, tmpusername);
	if (tmpusername == "Admin:Y")
	*admin = 1;
	else
	*admin = 0;
	myfile.close();
	return true;
	}

	for (int b = 0;b < 6;b++)
	{

	getline(myfile, tmpusername);
	/*
	if (b == 4)
	{
	if (tmpusername == "Admin:Y")
	*admin = 1;
	else *admin = 0;
	}

	}
	}
	myfile.close();
	return false;
	*/
	for (int i = 0; i < AccountDBsize; i++)
	{
		if (AccountDB[i].username == username && AccountDB[i].password == password)
		{
			return &AccountDB[i];
		}
	}
	return NULL;
}
void PrintUserMenu(string username) {
	system("cls");
	cout << "*****************************************************************" << endl;
	cout << "*\t\t\t Welcome " << username << "\t\t\t\t*" << endl;
	cout << "*****************************************************************" << endl;
	cout << "1.Report a problem.\n2.View ticket history.\n3.Logout.\n";
}
void ReportProblemMenu(string username) {
	system("cls");
	int choice;
	string issue, des, reason, status, department;
	SYSTEMTIME DateOfNow;
	GetLocalTime(&DateOfNow);
	string temp, date_str = to_string(DateOfNow.wYear) + "/" + to_string(DateOfNow.wMonth) + "/" + to_string(DateOfNow.wDay);
	Ticket* ticket = new Ticket;
	ticket->date = date_str;
	ticket->username = username;
	ticket->code = TicketDBsize + 1;
	ticket->severity = 0;
	ticket->responseDate = "none";
	ticket->response = "none";
	cout << "*****************************************************************" << endl;
	cout << "*\t\t " << username << "please describe your issue:\t\t*" << endl;
	cout << "*****************************************************************" << endl;
	cout << "1.Account problems\n2.In-Game or Graphic issues\n3.Security breach\n4.Purchase issues\n";
	while (true) {
		cin >> choice;
		switch (choice)
		{
		case 1:
			ticket->describedIssue = "Account Problems";
			system("cls");
			cout << "*****************************************************************" << endl;
			cout << "*\t\t\tReason of problem: \t\t\t*" << endl;
			cout << "*****************************************************************" << endl;
			cout << "1.Can't log in\n2.I was banned for no reason\n3.My account is already connected\n";
			choice = 0;
			while (choice != 1 && choice != 2 && choice != 3)
			{
				cin >> choice;
				if (choice == 1) {
					ticket->Reason = "Can't log in";
					break;
				}
				else if (choice == 2) {
					ticket->Reason = "I was banned for no reason";
					break;
				}
				else if (choice == 3) {
					ticket->Reason = "My account is already connected";
					break;
				}
				else {
					cout << "Wrong choice,please choose again\n";
					cin >> choice;
				}
			}
			break;
		case 2:
			ticket->describedIssue = "In-Game or Graphic issues";
			system("cls");
			cout << "*****************************************************************" << endl;
			cout << "*\t\t\tReason of problem: \t\t\t*" << endl;
			cout << "*****************************************************************" << endl;
			cout << "1.I have a graphic bug\n2.My screen is frozen\n3.Can't see the main menu\n4.The loading takes forever\n";
			choice = 0;
			while (choice != 4)
			{
				cin >> choice;
				if (choice != 1 && choice != 2 && choice != 3) {
					ticket->Reason = "I have a graphic bug";
					break;
				}
				else if (choice == 2) {
					ticket->Reason = "My screen is frozen";
					break;
				}
				else if (choice == 3) {
					ticket->Reason = "Can't see the main menu";
					break;
				}
				else if (choice == 4) {
					cout << "The loading takes forever";
					break;
				}
				else {
					cout << "Wrong choice,please choose again\n";
					cin >> choice;
				}
			}
			break;
		case 3:
			ticket->describedIssue = "Security breach";
			system("cls");
			cout << "*****************************************************************" << endl;
			cout << "*\t\t\tReason of problem: \t\t\t*" << endl;
			cout << "*****************************************************************" << endl;
			cout << "1.Someone tries to login into my account.\n2.I saw a hacker ingame.\n3.Someone changed my password\n";
			choice = 0;
			while (choice != 1 && choice != 2 && choice != 3)
			{
				cin >> choice;
				if (choice == 1) {
					ticket->Reason = "Someone tries to login into my account";
					break;
				}
				else if (choice == 2) {
					ticket->Reason = "I saw a hacker ingame";
					break;
				}
				else if (choice == 3) {
					ticket->Reason = "Someone changed my password";
					break;
				}
				else {
					cout << "Wrong choice,please choose again\n";
					cin >> choice;
				}
			}
			break;
		case 4:
			ticket->describedIssue = "Purchase issues";
			system("cls");
			cout << "*****************************************************************" << endl;
			cout << "*\t\t\tReason of problem: \t\t\t*" << endl;
			cout << "*****************************************************************" << endl;
			cout << "1.Did not receive my In-Game gold after I purchased\n2.I want a refund\n3.I did not get gold from watching the advertising videos\n4.Can't make a purchase\n";
			choice = 0;
			while (choice != 1 && choice != 2 && choice != 3 && choice != 4)
			{
				cin >> choice;
				if (choice == 1) {
					ticket->Reason = "Did not receive my In-Game gold after I purchased";
					break;
				}
				else if (choice == 2) {
					ticket->Reason = "I want a refund";
					break;
				}
				else if (choice == 3) {
					ticket->Reason = "I did not get gold from watching the advertising videos";
					break;
				}
				else if (choice == 4) {
					ticket->Reason = "Can't make a purchase";
				}
				else {
					cout << "Wrong choice,please choose again\n";
					cin >> choice;
				}
			}
			break;
		default:
		{
			cout << "Wrong option,please enter 1~4 only\n";
			continue;
		}
		}
	}
	ticket->department = "none";
	ticket->status = "Received";
	cout << "Description: ";
	getline(cin>>ws, des);
	ticket->description = des;
	Ticket* newArr = new Ticket[TicketDBsize + 1];
	for (int i = 0; i < TicketDBsize; i++)
	{
		newArr[i].code = TicketDB[i].code;
		newArr[i].username = TicketDB[i].username;
		newArr[i].date = TicketDB[i].date;
		newArr[i].describedIssue = TicketDB[i].describedIssue;
		newArr[i].Reason = TicketDB[i].Reason;
		newArr[i].description = TicketDB[i].description;
		newArr[i].department = TicketDB[i].department;
		newArr[i].status = TicketDB[i].status;
		newArr[i].severity = TicketDB[i].severity;
		newArr[i].responseDate = TicketDB[i].responseDate;
		newArr[i].response = TicketDB[i].response;
	}
	TicketDBsize = TicketDBsize + 1;
	newArr[TicketDBsize - 1].code = ticket->code;
	newArr[TicketDBsize - 1].username = ticket->username;
	newArr[TicketDBsize - 1].date = ticket->date;
	newArr[TicketDBsize - 1].describedIssue = ticket->describedIssue;
	newArr[TicketDBsize - 1].Reason = ticket->Reason;
	newArr[TicketDBsize - 1].description = ticket->description;
	newArr[TicketDBsize - 1].department = ticket->department;
	newArr[TicketDBsize - 1].status = ticket->status;
	newArr[TicketDBsize - 1].severity = ticket->severity;
	newArr[TicketDBsize - 1].responseDate = ticket->responseDate;
	newArr[TicketDBsize - 1].response = ticket->response;
	TicketDB = new Ticket[TicketDBsize];
	for (int i = 0; i < TicketDBsize; i++)
	{
		TicketDB[i].code = newArr[i].code;
		TicketDB[i].username = newArr[i].username;
		TicketDB[i].date = newArr[i].date;
		TicketDB[i].describedIssue = newArr[i].describedIssue;
		TicketDB[i].Reason = newArr[i].Reason;
		TicketDB[i].description = newArr[i].description;
		TicketDB[i].department = newArr[i].department;
		TicketDB[i].status = newArr[i].status;
		TicketDB[i].severity = newArr[i].severity;
		TicketDB[i].responseDate = newArr[i].responseDate;
		TicketDB[i].response = newArr[i].response;
	}
	delete[] newArr;
	cout << "\n\nSubmitted request! Press any key to continue.\n";
	system("pause");
}
void ViewHistoryMenu() {
	system("cls");
	cout << "*****************************************************************" << endl;
	cout << "*\t\t\t View History\t\t\t\t*" << endl;
	cout << "*****************************************************************" << endl;
	cout << "1) View all ticket history " << endl << "2) Search spesific ticket by code" << endl << "3) Go back" << endl;
}
void ViewSpesificTicketByCode(string username) {
	int i = 0,choice;
	int AvailableCodesSize = 0;
	int* AvailableCodes = NULL;
	AvailableCodes = (int*)malloc((1 + AvailableCodesSize) * sizeof(int));
	for (i; i < TicketDBsize; i++) {
		if (TicketDB[i].username == username) {
			AvailableCodes[AvailableCodesSize++] = TicketDB[i].code;
			AvailableCodes = (int*)realloc(AvailableCodes, (AvailableCodesSize + 1) * sizeof(int));
		}
	}
	if (AvailableCodesSize == 0) {
		cout << "No new cases!\n";
		system("pause");
		return;
	}
	cout << "Please enter the code for the ticket you want to work on: " << endl;
	cin >> choice;
	while (CheckLegalCode(AvailableCodes, AvailableCodesSize, choice) == false) {
		cout << "Wrong choice,you can only choose ";
		for (int b = 0; b < AvailableCodesSize; b++) {
			if (b != AvailableCodesSize - 1)
				cout << AvailableCodes[b] << ",";
			else cout << AvailableCodes[b] << endl;
		}
		cout << "Please choose again:";
		cin >> choice;
	}
	system("cls");
	printTicket(choice - 1);
	system("pause");
	delete[] AvailableCodes;
}
void ViewHistory(string username) {
	int choice = 0;
	while (true) {
		ViewHistoryMenu();
		cin >> choice;
		switch (choice) {
		case 1: {
			ViewAllTicketHistory(username);
			continue;
		}
		case 2: {
			ViewSpesificTicketByCode(username);
			continue;
		}
		case 3: {
			cout << "Going back\n";
			system("pause");
		}
		}
		break;
	}
}
void ViewAllTicketHistory(string username) {
	system("cls");
	bool ifFoundOne = false;
	for (int i = 0; i < TicketDBsize; i++)
	{
		if (TicketDB[i].username == username)
		{
			printTicket(i);
			ifFoundOne = true;
		}
	
	}
	if (ifFoundOne == false)
		cout << "No tickets found" << endl;
	system("pause");

}
void UserMenu(Account* account)
{
	int choice = 0;
	while (choice != 3) {
		PrintUserMenu(account->username);
		cout << "What would you like to do? (1~3)\n";
		cin >> choice;
		switch (choice) {
		case 1:
		{
			ReportProblemMenu(account->username);
			continue;
		}
		case 2:
		{
			ViewHistory(account->username);
			continue;
		}
		case 3:
		{
			break;
		}
		default: {
			cout << "Please choose 1~3 only\n";
			system("pause");
		}
		break;
		}
	}
}
bool CheckLegalCode(int* codes, int size, int choice) {
	for (int i = 0; i < size; i++) {
		if (codes[i] == choice)
			return true;
	}
	return false;
}
int SortSeverity(const void *p, const void *q)
{
	int l = (( Ticket *)p)->severity;
	int r = ((Ticket *)q)->severity;
	return (r-l);
}
int SortCode(const void *p, const void *q)
{
	int l = ((Ticket *)p)->code;
	int r = ((Ticket *)q)->code;
	return (l - r);
}
int SortDepartment(const void *p, const void *q)
{
	string left = ((Ticket*)p)->department;
	char* cleft = new char[left.length() + 1];
	strcpy(cleft, left.c_str());
	string right = ((Ticket*)q)->department;
	char* cright = new char[right.length() + 1];
	strcpy(cright, right.c_str());
	int res= strcmp(cright, cleft);
	delete[] cleft;
	delete[] cright;
	return res;
}
void sort() {
	qsort(TicketDB, TicketDBsize, sizeof(Ticket), SortSeverity);
}
void sort(bool check) {
	qsort(TicketDB, TicketDBsize, sizeof(Ticket), SortCode);
}
void sort(bool check, bool check2) {
	qsort(TicketDB, TicketDBsize, sizeof(Ticket), SortDepartment);
}
void ClosedCases(Account* account) {
	system("cls");
	int i = 0, count = 0;
	ChooseSortOption();
	string check;
	for (i; i < TicketDBsize; i++) {
		check = TicketDB[i].response.substr(0, (TicketDB[i].response.find(" ")));
		if (TicketDB[i].status == "Closed"&&check == account->username) {
			printTicket(i, true);
			count++;
		}
	}
	if (count == 0)
		cout << "No closed tickets.\n";
	system("pause");
}
void PrintAnalysisMenu() {
	system("cls");
	cout << "*****************************************************************" << endl;
	cout << "*\t\t What would you like to check?\t\t\t*" << endl;
	cout << "*****************************************************************" << endl;
	cout << "1) My statistics " << endl << "2) General Statistics" << endl<<"3) Go back"<<endl;
}
void MyStatistics(Account* account) {
	int countOngoingThisMonth = 0, countClosedThisMonth = 0, countClosedAllTime = 0;
	SYSTEMTIME DateOfNow;
	GetLocalTime(&DateOfNow);
	string check, thisMonth = to_string(DateOfNow.wYear) + "/" + to_string(DateOfNow.wMonth);
	for (int i = 0; i < TicketDBsize; i++) {
		check = TicketDB[i].response.substr(0, (TicketDB[i].response.find(" ")));
		if (check == account->username&&TicketDB[i].responseDate.substr(0, TicketDB[i].responseDate.find_last_of("/")) == thisMonth)
		{
			if (TicketDB[i].status == "Closed")
				countClosedThisMonth++;
			else
				if (TicketDB[i].status == "In Process")
					countOngoingThisMonth++;
		}
		else
			if (check == account->username&&TicketDB[i].responseDate.substr(0, TicketDB[i].responseDate.find_last_of("/")) != thisMonth)
				if (TicketDB[i].status == "Closed")
					countClosedAllTime++;
	}
	cout << "Amount of tickets you're working on this month:" << countOngoingThisMonth << endl;
	cout << "Amount of tickets you closed this month: " << countClosedThisMonth<<endl;
	cout << "Amount of tickets you closed all time besides this month: " << countClosedAllTime<<endl;
	system("pause");
}
void GeneralStatistics() {
	int countF = 0, countM = 0, countAccounts = 0, countSecurity = 0, countPurchase = 0, countGrahpics = 0;
	for (int i = 0; i < AccountDBsize; i++) {
		if (AccountDB[i].gender == "F"&&AccountDB[i].isAdmin == "N")
			countF++;
		else if (AccountDB[i].gender == "M"&&AccountDB[i].isAdmin == "N")
			countM++;
	}
	for (int i = 0; i < TicketDBsize; i++) {
		if (TicketDB[i].describedIssue == "Account Problems")
			countAccounts++;
		else
		if (TicketDB[i].describedIssue == "In-Game or Graphic issues")
			countGrahpics++;
		else
		if (TicketDB[i].describedIssue == "Security breach")
			countSecurity++;
		else countPurchase++;
	}
	cout << "Number of male users: " << countM << ", which is " << ((double)countM / (double)(countM+countF))*100 << "% out of all the users base\n";
	cout << "Number of female users: " << countF << ", which is " << ((double)countF / (double)(countM+countF))*100 << "% out of all the users base\n";
	cout << "Number of account issues:" << countAccounts << ", which is " << ((double)countAccounts / (double)TicketDBsize) * 100 << "% of all the tickets\n";
	cout << "Number of graphic issues:" << countGrahpics << ", which is " << ((double)countGrahpics / (double)TicketDBsize) * 100 << "% of all the tickets\n";
	cout << "Number of security issues:" << countSecurity << ", which is " << ((double)countSecurity / (double)TicketDBsize) * 100 << "% of all the tickets\n";
	cout << "Number of purchase issues:" << countPurchase << ", which is " << ((double)countPurchase / (double)TicketDBsize) * 100 << "% of all the tickets\n";
	system("pause");
}
void AnalysisMenu(Account* account) {
	int choice = 0;
	while (true) {
		PrintAnalysisMenu();
		cin >> choice;
		switch (choice) {
		case 1: {
			MyStatistics(account);
			continue;
		}
		case 2: {
			GeneralStatistics();
			continue;
		}
		case 3: {
			break;
		}
		default:
		{
			cout << "Wrong option,please choose 1~3 only\n";
			system("pause");
			continue;
		}
		}
		break;
	}
}
void NewCases(Account* account) {
	int i = 0,choice;
	int* AvailableCodes = NULL;
	int AvailableCodesSize =0;
	AvailableCodes = (int*)malloc((1+AvailableCodesSize)*sizeof(int));
	string resp,department;
	int severity=-1;
	SYSTEMTIME DateOfNow;
	GetLocalTime(&DateOfNow);
	system("cls");
	for (i; i < TicketDBsize; i++)
	{
		if (TicketDB[i].status == "Received")
		{
			printTicket(i, true);
			AvailableCodes[AvailableCodesSize++] = TicketDB[i].code;
			AvailableCodes = (int*)realloc(AvailableCodes, (AvailableCodesSize+1)*sizeof(int));
		}
	}
	if (AvailableCodesSize == 0) {
		cout << "No new cases!\n";
		system("pause");
		return;
	}
	cout << "Please enter the code for the ticket you want to work on: " << endl;
	cin >> choice;
	while(CheckLegalCode(AvailableCodes,AvailableCodesSize,choice)==false){
		cout << "Wrong choice,you can only choose ";
		for (int b = 0; b < AvailableCodesSize; b++) {
			if(b!=AvailableCodesSize-1)
			cout << AvailableCodes[b] <<",";
			else cout << AvailableCodes[b] << endl;
		}
		cout << "\n";
		cin >> choice;
	}
	system("cls");
	TicketDB[choice-1].status = "In Process";
	TicketDB[choice-1].response = account->username+" : ";
	TicketDB[choice-1].responseDate = to_string(DateOfNow.wYear) + "/" + to_string(DateOfNow.wMonth) + "/" + to_string(DateOfNow.wDay);
	TicketDB[choice-1].responseDate = to_string(DateOfNow.wYear) + "/" + to_string(DateOfNow.wMonth) + "/" + to_string(DateOfNow.wDay);
	printTicket(choice-1, true);
	cout << "Leave your reply here: ";
	getline(cin >> ws, resp);
	cout << "Please choose a proper department: ";
	cin >> department;
	TicketDB[choice-1].department = department;
	TicketDB[choice-1].response = TicketDB[choice-1].response + resp;
	cout << "Please choose severity for this request: (0~10)";
	cin >> severity;
	while (severity < 0 || severity>10)
	{
		cout << "Wrong choice,please only choose 0~10\n";
		cin >> severity;
	}
	TicketDB[choice - 1].severity = severity;
	cout << "Case finished\n";
	delete[] AvailableCodes;
	sort(true);
	system("pause");
}
void PrintAdminMenu() {
	system("cls");
	cout << "*****************************************************************" << endl;
	cout << "*\t\t\t Admin Menu\t\t\t\t*" << endl;
	cout << "*****************************************************************" << endl;
	cout << "1) Ongoing cases " << endl << "2) New cases" << endl << "3) Closed cases" <<"\n4) Analysis"<< endl << "5) Logout" << endl;
}
void AdminMenu(Account* account) {
	int choice=0;
	while (choice != 5) {
		PrintAdminMenu();
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			printPrevCases(account);
			break;
		}
		case 2: 
		{
			NewCases(account);
			continue;
		}
		case 3: 
		{
			ClosedCases(account);
			continue;
		}
		case 4: 
		{
			AnalysisMenu(account);
			continue;
		}
		case 5:
		{
			break;
		}
		default:
		{
			cout << "Wrong option,please only choose 1~4\n";
			cin >> choice;
		}
		}
		break;
	}
}
void printTicket(int index) {
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 14);
	cout << "Code : " << TicketDB[index].code << endl;
	cout << "Date : " << TicketDB[index].date << endl;
	cout << "Described Issue : " << TicketDB[index].describedIssue << endl;
	cout << "Reason : " << TicketDB[index].Reason << endl;
	cout << "Description : " << TicketDB[index].description << endl;
	cout << "Status : " << TicketDB[index].status << endl;
	cout << "Department : " << TicketDB[index].department << endl;
	cout << "Response Date: " << TicketDB[index].responseDate << endl;
	cout << "Response : " << TicketDB[index].response << endl;

	SetConsoleTextAttribute(hConsole, 7);

	cout << "\n";
}
void printSortMenu() {
	system("cls");
	cout << "*****************************************************************" << endl;
	cout << "*\t\t How would you like to sort?\t\t\t*" << endl;
	cout << "*****************************************************************" << endl;
	cout << "1) By Code " << endl << "2) By Severity" << endl << "3) By Department\n" << endl;
}
void ChooseSortOption() {
	int choice = 0;
	while (true) {
		printSortMenu();
		cin >> choice;
		switch (choice) {
		case 1: {
			break;
		}
		case 2: {
			sort();
			break;
		}
		case 3: {
			sort(true, true);
			break;
		}
		default: {
			cout << "Wrong option,please choose 1~3 only\n";
			system("pause");
			continue;
		}
		}
		break;
	}
}
void printTicket(int index, bool check) {
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 14);
	cout << "Code : " << TicketDB[index].code << endl;
	cout << "Date : " << TicketDB[index].date << endl;
	cout << "Username : " << TicketDB[index].username << endl;
	cout << "Described Issue : " << TicketDB[index].describedIssue << endl;
	cout << "Reason : " << TicketDB[index].Reason << endl;
	cout << "Description : " << TicketDB[index].description << endl;
	cout << "Status : " << TicketDB[index].status << endl;
	cout << "Department : " << TicketDB[index].department << endl;
	cout << "Severity : " << TicketDB[index].severity << endl;
	cout << "Response Date: " << TicketDB[index].responseDate << endl;
	cout << "Response : " << TicketDB[index].response << endl;

	SetConsoleTextAttribute(hConsole, 7);

	cout << "\n";
}
void PrintEditTicketMenu(int i) {
	system("cls");
	printTicket(i-1, true);
	cout << "\n\n\n";
	cout << "*****************************************************************" << endl;
	cout << "*\t\tWhat would you like to edit? \t\t\t*" << endl;
	cout << "*****************************************************************" << endl;
	cout << "1) Department" << endl << "2) Status\n" << "3) Response" << endl<<"4) Go back"<<endl;

}
void EditTicketMenu(int i) {
	int choice = 0;
	string tmp;
	SYSTEMTIME DateOfNow;
	GetLocalTime(&DateOfNow);
	string date_str = to_string(DateOfNow.wYear) + "/" + to_string(DateOfNow.wMonth) + "/" + to_string(DateOfNow.wDay);
	while (true) {
		PrintEditTicketMenu(i);
		cin >> choice;
		switch (choice) {
		case 1: {
			cout<<"Please choose new department:\n";
			cin >> tmp;
			TicketDB[i - 1].department = tmp;
			cout << "Done!\n";
			system("pause");
			continue;
		}
		case 2: {
			cout<<"Please choose a new status:\n";
			cin >> tmp;
			TicketDB[i - 1].status = tmp;
			cout << "Done!\n";
			system("pause");
			continue;
		}
		case 3: {
			cout<<"Please enter your new response:\n";
			getline(cin >> ws, tmp);
			TicketDB[i - 1].response = tmp;
			TicketDB[i - 1].responseDate = date_str;
			cout << "Done!\n";
			system("pause");
			continue;
		}
		case 4: {
			cout << "Going back\n";
			break;
		}
		default: {
			cout << "Wrong option,please only choose 1~3\n";
			continue;
		}
		}
		break;
	}
	system("pause");
}
void printPrevCases(Account* account)
/*
param1:reference to the working file
return:none
raise:none
*/
{
	ChooseSortOption();
	system("cls");
	cout << "*****************************************************************" << endl;
	cout << "*\t\t\t Ongoing cases \t\t\t\t*" << endl;
	cout << "*****************************************************************" << endl;
	int count = 0,choice;
	int* AvailableCodes = NULL;
	int AvailableCodesSize = 0;
	AvailableCodes = (int*)malloc((1 + AvailableCodesSize) * sizeof(int));
	string check;
	for (int i = 0; i < TicketDBsize; i++) {
		check = TicketDB[i].response.substr(0, (TicketDB[i].response.find(" ")));
		if (TicketDB[i].status == "In Process"&&check == account->username) {
			printTicket(i, true);
			AvailableCodes[AvailableCodesSize++] = TicketDB[i].code;
			AvailableCodes = (int*)realloc(AvailableCodes, (AvailableCodesSize + 1) * sizeof(int));
		}
	}
	if (AvailableCodesSize == 0) {
		cout << "No ongoing cases!\n";
		system("pause");
		return;
	}
	cout << "Please enter the code for the ticket you want to work on: " << endl;
	cin >> choice;
	while (CheckLegalCode(AvailableCodes, AvailableCodesSize, choice) == false) {
		cout << "Wrong choice,you can only choose ";
		for (int b = 0; b < AvailableCodesSize; b++) {
			if (b != AvailableCodesSize - 1)
				cout << AvailableCodes[b] << ",";
			else cout << AvailableCodes[b] << endl;
		}
		cout << "\n";
		cin >> choice;
	}
	EditTicketMenu(choice);

	delete[] AvailableCodes;
	sort(true);
}
void printNewCases()
/*
param1:reference to the working file
return:none
raise:none
*/
{
	system("cls");
	cout << "*****************************************************************" << endl;
	cout << "*\t\t New cases \t\t\t" << endl;
	cout << "*****************************************************************" << endl;
	int count = 0;
	for (int i = 0; i < TicketDBsize; i++)
	{
		if (TicketDB[i].status == "Received")
			printTicket(i,true);
	}
}
void searchAndPrintByCode()
/*
param1:reference to the working file
return:none
raise:none
*/
{
	int code;
	cout << "*****************************************************************" << endl;
	cout << "\t\t Enter the wanted ticket by code: " << endl;
	cout << "*****************************************************************" << endl;
	cin >> code;
	for (int i = 0; i < TicketDBsize; i++)
	{
		if (TicketDB[i].code == code)
		{
			printTicket(i);
			break;
		}
		if (i == (TicketDBsize - 1))	/*	if next hitteration the loop will break	*/
		{
			HANDLE hConsole;
			hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, 4);
			cout << "There no ticket with entered Code" << endl;
			SetConsoleTextAttribute(hConsole, 7);
			return;
		}
	}
}
void searchAndPrintByUserName()
/*
param1:reference to the working file
return:none
raise:none
*/
{
	string userName, line;
	bool ifFoundOne = false;
	int count = 0;
	cout << "*****************************************************************" << endl;
	cout << "\t Enter the Desirable ticket by Username: " << endl;
	cout << "*****************************************************************" << endl;
	cin >> userName;
	for (int i = 0; i < TicketDBsize; i++)
	{
		if (TicketDB[i].username == userName && TicketDB[i].status == "In Attention")
		{
			printTicket(i);
			ifFoundOne = true;
		}
		if (i == (TicketDBsize - 1) && ifFoundOne == false)	/*	if next iteration the loop will break	*/
		{
			HANDLE hConsole;
			hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, 4);
			cout << "There no ticket with entered Username" << endl;
			SetConsoleTextAttribute(hConsole, 7);
			return;
		}
	}
}
void prevCasesOptions()
/*
param1:reference to the working file
return:none
raise:none
*/
{
	bool flag = true;
	int choice;
	while (flag)
	{
		cout << "*****************************************************************" << endl;
		cout << "1) Search by 'code' " << endl << "2) Search by Username" << endl << "3) back" << endl;
		cout << "*****************************************************************" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:// Search by 'code'
		{
			searchAndPrintByCode();
			break;
		}
		case 2: // Search by Username"
		{
			searchAndPrintByUserName();
			break;
		}
		case 3: // back
		{
			flag = false;
			break;
		}
		default:
		{
			HANDLE hConsole;
			hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, 4);
			cout << "You have entered an unavailable choice, please try again." << endl;
			SetConsoleTextAttribute(hConsole, 7);
		}
		}
	}
}
void changeStatusMenu()
/*
param1:reference to the working file
return:none
raise:none
*/
{
	int code;
	cout << "*****************************************************************" << endl;
	cout << "Enter the 'Code' of the report-status you want to change:" << endl;
	cout << "*****************************************************************" << endl;
	cin >> code;
	for (int i = 0; i < TicketDBsize; i++)
	{
		if (TicketDB[i].code == code && TicketDB[i].status == "Received")
		{
			TicketDB[i].status = "In Attention";
			break;
		}
		if (i == (TicketDBsize - 1))	/*	if next hitteration the loop will break	*/
		{
			HANDLE hConsole;
			hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, 4);
			cout << "error : there no ticket with entered Code" << endl;
			SetConsoleTextAttribute(hConsole, 7);
			break;
		}
	}
}
void PrintLoginMenu() {
	system("cls");
	cout << "*****************************************************************" << endl;
	cout << "*\t\tSummoners War Ticketing System - Login \t\t*" << endl;
	cout << "*****************************************************************" << endl;
	cout << "1.Login.\n2.Back.\n";
}
void LoginMenu()
{
	string username, password;
	int choice = 0;
	while (choice != 2) {
		PrintLoginMenu();
		cout << "What would you like to do? (1~2)\n";
		cin >> choice;
		switch (choice) {
		case 1:
		{
			cout << "Username:";
			cin >> username;
			cout << "Password:";
			cin >> password;

			if (isValidLogin(username, password) == NULL)
			{
				cout << "Username or password are incorrect.Try again.\n";
				system("pause");
			}
			else
			{
				if (isValidLogin(username, password)->isAdmin == "N")
				{
					UserMenu(isValidLogin(username, password));
				}
				else
				{
					AdminMenu(isValidLogin(username, password));
				}

				break;

			}
		}
		case 2:
		{
			break;
		}
		}
		/*
		cout << "Username:";
		cin >> username;
		cout << "Password:";
		cin >> password;

		while (isValidLogin(username, password) == false) {
		cout << "Username or password are incorrect.Please re-enter your info\n";
		cout << "Username:";
		cin >> username;
		cout << "Password:";
		cin >> password;
		}
		*/

	}
}
bool SignUp()
{
	system("cls");
	string firstname, lastname, username, password, email;
	char gender;

	cout << "*****************************************************************" << endl;
	cout << "*\t\tSummoners War Support-System Sign-Up \t\t*" << endl;
	cout << "*****************************************************************" << endl;
	cout << "Username:";
	cin >> username;
	while (isUsernameValid(username) == false || isUsernameTaken(username) == false) {
		cout << "Something went wrong,please choose a different username!\n";
		cin >> username;
	}
	cout << "Password:";
	cin >> password;
	while (isPasswordValid(password) == false)
	{
		cout << "Please make the password contain only a~z,A~Z and 0~9\n";
		cin >> password;
	}
	cout << "First name:";
	cin >> firstname;

	while (isNameValid(firstname) == false) {
		cout << "Please use only a~z and A~Z\n";
		cin >> firstname;
	}
	cout << "Last name:";
	cin >> lastname;
	while (isNameValid(lastname) == false) {
		cout << "Please use only a~z and A~Z\n";
		cin >> lastname;
	}
	cout << "Gender:";
	cin >> gender;
	while (gender!='F'&&gender!='M')
	{
	cout << "Please choose F/M only\n";
	cin >> gender;
	}
	cout << "Email:";
	cin >> email;
	while (isEmailValid(email) == false) {
		cout << "Invalid Email,please try again.\n";
		cin >> email;
	}
	/*ofstream myfile;
	myfile.open("Accounts.txt",ios::app);
	myfile << endl << "'''" << endl;
	myfile << "Username:" << username << endl;
	myfile << "Password:" << password << endl;
	myfile << "Firstname:" << firstname << endl;
	myfile << "Lastname:" << lastname << endl;
	myfile << "Email:" << email << endl;
	myfile << "Gender:" << gender << endl;
	myfile << "Admin:" << "N";
	myfile.close();
	return true;
	*/
	Account* acc = new Account;
	acc->username = username;
	acc->password = password;
	acc->firstname = firstname;
	acc->lastname = lastname;
	acc->email = email;
	acc->gender = gender;
	acc->isAdmin = "N";
	Account* newArr = new Account[AccountDBsize + 1];
	for (int i = 0; i < AccountDBsize; i++)
	{
		newArr[i].username = AccountDB[i].username;
		newArr[i].password = AccountDB[i].password;
		newArr[i].firstname = AccountDB[i].firstname;
		newArr[i].lastname = AccountDB[i].lastname;
		newArr[i].email = AccountDB[i].email;
		newArr[i].gender = AccountDB[i].gender;
		newArr[i].isAdmin = AccountDB[i].isAdmin;
	}
	AccountDBsize = AccountDBsize + 1;
	newArr[AccountDBsize - 1].username = (*acc).username;
	newArr[AccountDBsize - 1].password = (*acc).password;
	newArr[AccountDBsize - 1].firstname = (*acc).firstname;
	newArr[AccountDBsize - 1].lastname = (*acc).lastname;
	newArr[AccountDBsize - 1].email = (*acc).email;
	newArr[AccountDBsize - 1].gender = (*acc).gender;
	newArr[AccountDBsize - 1].isAdmin = (*acc).isAdmin;
	//delete[] AccountDB;
	AccountDB = new Account[AccountDBsize];
	for (int i = 0; i < AccountDBsize; i++)
	{
		AccountDB[i].username = newArr[i].username;
		AccountDB[i].password = newArr[i].password;
		AccountDB[i].firstname = newArr[i].firstname;
		AccountDB[i].lastname = newArr[i].lastname;
		AccountDB[i].email = newArr[i].email;
		AccountDB[i].gender = newArr[i].gender;
		AccountDB[i].isAdmin = newArr[i].isAdmin;
	}
	delete[] newArr;
	return true;
}
void FAQ()
{
	system("cls");
	cout << "*****************************************************************" << endl;
	cout << "*\t\t\tSummoners War- FAQ \t\t\t*" << endl;
	cout << "*****************************************************************" << endl;
	cout << "Question : Why is the game frozen?\n";
	cout << "Answer : Check for updates in the playstore store.\n\n";

	cout << "Question  Why can't I make a purchase in the ingame store?\n";
	cout << "Answer : Make sure your ingame currency is balanced.\n\n";

	cout << "Question : Why am I getting error e-0x512d?\n";
	cout << "Answer : It means your device does not support our game.\n\n";

	cout << "Question : Why didn't I receive my coins from the advertising videos?\n";
	cout << "Answer : Restart the game,once you do the coins would be added.\n\n";

	cout << "Question : Why am I getting error e-666tx?\n";
	cout << "Answer : It means your data files are corrupted, re-downloaded the game from the playstore.\n\n";

	cout << "Press any key to continue...";
	getchar();
}
void SupportMenu()
{
	cout << "Please enter an option (1~4)\n";
	int choice = 0;
	while (choice != 4)
	{
		PrintSupportMenu();
		cout << "Please enter an option (1~4)\n";
		cin >> choice;
		getchar();
		switch (choice) {
		case 1: {
			if (SignUp() == true)
			{
				cout << "Registration complete! Press any key to continue.\n";
				system("pause");
			}
			continue;
		}
		case 2: {
			LoginMenu();
			break;
		}
		case 3: {
			FAQ();
			break;
		}
		case 4: {
			system("cls");
			break;
		}
		default: printf("Invalid.");
			continue;
		}
	}
}
void MainMenu() {
	int choice = 0;
	while (choice != 4)
	{
		PrintMainMenu();
		cout << "Please enter an option (1~4)\n";
		cin >> choice;
		getchar();
		switch (choice) {
		case 1: {
			PlayMenu();
			continue;
		}
		case 2: {
			SettingsMenu();
			break;
		}
		case 3: {
			SupportMenu();
			break;
		}
		case 4: {
			printf("Goodbye.\n");
			cout << "Press any key to continue...";
			getchar();
			break;
		}
		default: cout << "Invalid. ";
			cout << "Please re-enter.";
			getchar();
			system("cls");
			continue;
		}
	}
}
void SaveData() {
	ofstream myfile;
	myfile.open("Accounts.txt");
	for (int i = 0; i < AccountDBsize; i++) {

		myfile << AccountDB[i].username << endl;
		myfile << Encrypt(AccountDB[i].password) << endl;
		myfile << AccountDB[i].firstname << endl;
		myfile << AccountDB[i].lastname << endl;
		myfile << AccountDB[i].email << endl;
		myfile << AccountDB[i].gender << endl;
		myfile << AccountDB[i].isAdmin << endl;
	}
	myfile.close();
}
void SaveTicket() {
	fstream file;
	file.open("Tickets.txt");
	for (int i = 0; i < TicketDBsize; i++) {
		file << TicketDB[i].code << endl;
		file << TicketDB[i].username << endl;
		file << TicketDB[i].date << endl;
		file << TicketDB[i].describedIssue << endl;
		file << TicketDB[i].Reason << endl;
		file << TicketDB[i].description << endl;
		file << TicketDB[i].department << endl;
		file << TicketDB[i].status << endl;
		file << TicketDB[i].severity << endl;
		file << TicketDB[i].responseDate << endl;
		file << TicketDB[i].response << endl;
	}
	file.close();
}
int main() {
	AccountDB = LoadData(&AccountDBsize);
	TicketDB = LoadTickets(&TicketDBsize);
	/*for (int i = 0; i < TicketDBsize; i++) {
		cout << TicketDB[i].code << endl;
		cout << TicketDB[i].username << endl;
		cout << TicketDB[i].date << endl;
		cout << TicketDB[i].describedIssue << endl;
		cout << TicketDB[i].Reason << endl;
		cout << TicketDB[i].description << endl;
		cout << TicketDB[i].department << endl;
		cout << TicketDB[i].status << endl;
		cout << "=====================================================================" << endl;
		printTicket(i);
	}
	*/
	// save db into array of structs
	MainMenu();
	// store structs back to db
	SaveData();
	SaveTicket();
}