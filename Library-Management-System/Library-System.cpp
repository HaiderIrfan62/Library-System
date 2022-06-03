#include <iostream>
#include <fstream>
#include <sstream>
#include<vector>

using namespace std;

void register_student()
{
	string word, line;

	vector<vector<string>> all_data;
	vector <string> row_data;

	fstream file("data.csv", ios::in);

	while (getline(file, line))
	{
		row_data.clear();

		stringstream str(line);

		while (getline(str, word, ',')) {
			row_data.push_back(word);
		}
		all_data.push_back(row_data);
	}

	int t_rows = all_data.size();

	string addno;

	cout << "\nEnter admission number: ";
	cin >> addno;

	bool k = true;


	if (t_rows >= 11)
	{
		k = false;
	}

	for (int i = 0; i < t_rows; i++)
	{
		if (all_data[i][0] == addno)
		{
			k = false;
		}
	}



	if (k)
	{
		string bookname;
		string name;
		string lbook = "0";

		cin.ignore();
		cout << "\n\nEnter The Name of The Student ";
		getline(cin, name);

		fstream fout1;
		fout1.open("data.csv", ios::out | ios::app);
		fout1 << addno << "," << name << "," << lbook << "\n";

		cout << "\n\nStudent Record Created..";
	}
	else
	{
		cout << "More than 10 users can't be registered or User already exists. ";
	}
}
string convert(string lbook)
{
	if (lbook == "0")
		return "1";
	else if (lbook == "1")
		return "2";
	else if (lbook == "2")
		return "3";
	else if (lbook == "3")
		return "4";
}

string convert_back(string lbook)
{
	if (lbook == "1")
		return "0";
	else if (lbook == "2")
		return "1";
	else if (lbook == "3")
		return "2";
	else if (lbook == "0")
		return "Invalid";
}

int book_av(string book)
{
	string word, line;

	vector<vector<string>> all_data;
	vector <string> row_data;

	fstream file("book.csv", ios::in);

	while (getline(file, line))
	{
		row_data.clear();

		stringstream str(line);

		while (getline(str, word, ',')) {
			row_data.push_back(word);
		}
		all_data.push_back(row_data);
	}

	bool k = true;

	for (int i = 0; i < 50; i++)
	{
		if (all_data[i][0] == book)
		{
			k = false;
			if (all_data[i][1] == "1")
			{
				return 0;
			}
			else if (all_data[i][1] == "2")
			{
				return 1;
			}
		}
	}

	if (k)
	{
		cout << "Book doesn't exist.";
		return 0;
	}
}

void books_issue(string book) {
	string word, line;

	vector<vector<string>> all_data;
	vector <string> row_data;

	fstream file("book.csv", ios::in);

	while (getline(file, line))
	{
		row_data.clear();

		stringstream str(line);

		while (getline(str, word, ',')) {
			row_data.push_back(word);
		}
		all_data.push_back(row_data);
	}

	for (int i = 0; i < 50; i++)
	{
		if (all_data[i][0] == book)
		{
			if (all_data[i][1] == "1")
			{
				//cout << "Book not avaliable.";
				//k = false;
			}
			else if (all_data[i][1] == "2")
			{
				all_data[i][1] = "1";
			}
		}
	}

	fstream fout;

	fout.open("newbook.csv", ios::out);

	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			fout << all_data[i][j] << ",";
		}
		fout << "\n";
	}

	file.close();
	fout.close();

	remove("book.csv");
	rename("newbook.csv", "book.csv");

}


void issue()
{
	string reg, book;

	cout << "Enter reg number: ";
	cin >> reg;
	cout << "Enter book name: ";
	cin >> book;

	string word, line;

	vector<vector<string>> all_data;
	vector <string> row_data;

	fstream file("data.csv", ios::in);

	while (getline(file, line))
	{
		row_data.clear();

		stringstream str(line);

		while (getline(str, word, ',')) {
			row_data.push_back(word);
		}
		all_data.push_back(row_data);
	}

	int t_rows = all_data.size();
	bool k = true;
	bool y = false;

	for (int i = 0; i < t_rows; i++) {
		if (all_data[i][0] == reg) {
			all_data[i][2] = convert(all_data[i][2]);
			y = true;
			if (all_data[i][2] == "4") {
				k = false;
			}
		}
	}

	if (y) {
		if (book_av(book)) {
			if (k) {
				fstream fout;

				fout.open("newdata.csv", ios::out);

				for (int i = 0; i < t_rows; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						fout << all_data[i][j] << ",";
					}
					fout << "\n";
				}

				file.close();
				fout.close();

				remove("data.csv");
				rename("newdata.csv", "data.csv");

				books_issue(book);
			}
			else {
				cout << "You cannot issue more than 3 books.";
			}
		}
	}
	else {
		cout << "User not found.";
	}
}


void search()
{
	string word, line, reg;

	cout << "Enter registration number: ";
	cin >> reg;
	cout << endl;

	vector<vector<string>> all_data;
	vector <string> row_data;

	fstream file("data.csv", ios::in);

	while (getline(file, line))
	{
		row_data.clear();

		stringstream str(line);

		while (getline(str, word, ',')) {
			row_data.push_back(word);
		}
		all_data.push_back(row_data);
	}

	int t_rows = all_data.size();
	bool k = true;

	for (int row = 0; row < t_rows; row++) {
		if (reg == all_data[row][0]) {
			cout << "Registration number: " << all_data[row][0] << endl;
			cout << "Student Name: " << all_data[row][1] << endl;
			cout << "Loan Books: " << all_data[row][2] << endl;
			k = false;
		}
	}

}

void add_book(string book)
{
	string word, line;

	vector<vector<string>> all_data;
	vector <string> row_data;

	fstream file("book.csv", ios::in);

	while (getline(file, line))
	{
		row_data.clear();

		stringstream str(line);

		while (getline(str, word, ',')) {
			row_data.push_back(word);
		}
		all_data.push_back(row_data);
	}

	int t_rows = all_data.size();

	for (int i = 0; i < t_rows; i++)
	{
		if (all_data[i][0] == book)
		{
			all_data[i][1] = "2";
		}
	}

	fstream fout;

	fout.open("newbook.csv", ios::out);

	for (int i = 0; i < t_rows; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			fout << all_data[i][j] << ",";
		}
		fout << "\n";
	}

	file.close();
	fout.close();

	remove("book.csv");
	rename("newbook.csv", "book.csv");

}

void return_book()
{
	string reg, book;

	cout << "Enter reg number: ";
	cin >> reg;
	cout << "Enter name of the book: ";
	cin >> book;

	string word, line;

	vector<vector<string>> all_data;
	vector <string> row_data;

	fstream file("data.csv", ios::in);

	while (getline(file, line))
	{
		row_data.clear();

		stringstream str(line);

		while (getline(str, word, ',')) {
			row_data.push_back(word);
		}
		all_data.push_back(row_data);
	}

	int t_rows = all_data.size();

	for (int i = 0; i < t_rows; i++)
	{
		if (all_data[i][0] == reg)
		{
			if (all_data[i][2] != "0")
				all_data[i][2] = convert_back(all_data[i][2]);
		}
	}

	fstream fout;

	fout.open("newdata.csv", ios::out);

	for (int i = 0; i < t_rows; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			fout << all_data[i][j] << ",";
		}
		fout << "\n";
	}

	file.close();
	fout.close();

	remove("data.csv");
	rename("newdata.csv", "data.csv");

	add_book(book);
}

void users()
{
	string word, line;

	vector<vector<string>> all_data;
	vector <string> row_data;

	fstream file("data.csv", ios::in);

	while (getline(file, line))
	{
		row_data.clear();

		stringstream str(line);

		while (getline(str, word, ',')) {
			row_data.push_back(word);
		}
		all_data.push_back(row_data);
	}

	int t_rows = all_data.size();


	for (int i = 1; i < t_rows; i++)
	{
		for (int j = 1; j < 3; j++)
		{
			for (int k = i + 1; k < t_rows; k++)
			{
				if (all_data[i][0] > all_data[k][0])
				{
					string temp = all_data[i][0];
					all_data[i][0] = all_data[k][0];
					all_data[k][0] = temp;

					string temp1 = all_data[i][1];
					all_data[i][1] = all_data[k][1];
					all_data[k][1] = temp1;

					string temp2 = all_data[i][2];
					all_data[i][2] = all_data[k][2];
					all_data[k][2] = temp2;
				}
			}
		}
	}

	for (int i = 0; i < t_rows; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << all_data[i][j] << ' ';
		}
		cout << endl;
	}

}

void display_books()
{
	string word, line;

	vector<vector<string>> all_data;
	vector <string> row_data;

	fstream file("book.csv", ios::in);

	while (getline(file, line))
	{
		row_data.clear();

		stringstream str(line);

		while (getline(str, word, ',')) {
			row_data.push_back(word);
		}
		all_data.push_back(row_data);
	}

	int t_rows = all_data.size();

	for (int i = 0; i < t_rows; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			if (all_data[i][j] == "1")
				cout << "Borrowed" << ' ';
			else if (all_data[i][j] == "2")
				cout << "Avaliable" << ' ';
			else {
				cout << all_data[i][j] << ' ';

				if (i < 9)
					cout << ' ';

			}
		}
		cout << endl;
	}
}

void delete_record()
{
	string reg;
	cout << "Enter reg number: ";
	cin >> reg;

	string word, line;

	vector<vector<string>> all_data;
	vector <string> row_data;

	fstream file("data.csv", ios::in);

	while (getline(file, line))
	{
		row_data.clear();

		stringstream str(line);

		while (getline(str, word, ',')) {
			row_data.push_back(word);
		}
		all_data.push_back(row_data);
	}

	int t_rows = all_data.size();

	bool k = true;

	if (t_rows > 1)
	{
		for (int i = 0; i < t_rows; i++)
		{
			if (all_data[i][0] == reg)
			{
				for (int j = 0; j < 3; j++)
				{
					all_data[i][j] = "delete";
				}
				k = false;
			}
		}

		for (int i = 1; i < t_rows; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				for (int k = i + 1; k < t_rows; k++)
				{
					if (all_data[i][0] > all_data[k][0])
					{
						string temp = all_data[i][0];
						all_data[i][0] = all_data[k][0];
						all_data[k][0] = temp;

						string temp1 = all_data[i][1];
						all_data[i][1] = all_data[k][1];
						all_data[k][1] = temp1;

						string temp2 = all_data[i][2];
						all_data[i][2] = all_data[k][2];
						all_data[k][2] = temp2;
					}
				}
			}
		}

		if (k)
		{
			cout << "Entry not found." << endl;
		}
		else
		{
			fstream fout;

			fout.open("newdata.csv", ios::out | ios::app);

			t_rows = all_data.size() - 1;

			for (int i = 0; i < t_rows; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					fout << all_data[i][j] << ",";
				}
				fout << "\n";
			}

			file.close();
			fout.close();

			remove("data.csv");
			rename("newdata.csv", "data.csv");

		}
	}
	else
	{
		cout << "The data base is empty.";
	}
}

int main()
{
	int choice;

	cout << "Welcome! What will you like to do?" << endl;
	cout << "1.Register a user." << endl;
	cout << "2.Delete an existing user from the system." << endl;
	cout << "3.Search a user and display the number of outstanding books against him/her." << endl;
	cout << "4.Loan a book to a user." << endl;
	cout << "5.Return a book from a user." << endl;
	cout << "6.Display a list of existing users." << endl;
	cout << "7.Display a list of existing books and their status." << endl;
	cout << "Enter your choice: ";
	cin >> choice;

	if (choice == 1)
		register_student();
	else if (choice == 2)
		delete_record();
	else if (choice == 3)
		search();
	else if (choice == 4)
		issue();
	else if (choice == 5)
		return_book();
	else if (choice == 6)
		users();
	else if (choice == 7)
		display_books();

	return 0;
}