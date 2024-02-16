#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class user;
class book
{
public:
	int id, quantity, borrowed;
	string name;
	vector<user> book_users;

	book()
	{

	}

	book(int id, string name, int quantity)
	{
		this->id = id;
		this->name = name;
		this->quantity = quantity;
		borrowed = 0;
	}

	static bool cmp_by_id(book& a, book& b)
	{
		return a.id < b.id;
	}

	static bool cmp_by_name(book& a, book& b)
	{
		return a.name < b.name;
	}

	void print()
	{
		cout << "id = " << id << " name = " << name << " quantity = " << quantity << " borrowed " << book_users.size() << "\n";
	}
};

class user
{
public:
	int id;
	string name;
	vector<book> user_books;
	user()
	{

	}

	user(string name, int id)
	{
		this->name = name;
		this->id = id;
	}

	void print()
	{
		cout << "user " << name << " id " << id << " borrowed books ids: ";
		for (book b : user_books)
			cout << b.id << ' ';
		cout << "\n";
	}
};

class library
{
	vector<user> users;
	vector<book> books;
public:

	int choice()
	{
		int choice = -1;
		while (choice == -1)
		{
			cout << "===================================================\n";
			cout << "Library menu:\n";
			cout << "1) Add_book\n";
			cout << "2) search_books_by_prefix\n";
			cout << "3) who_borrowed_by_name\n";
			cout << "4) print_all_by_id\n";
			cout << "5) print_all_by_name\n";
			cout << "6) add_user\n";
			cout << "7) user_borrow\n";
			cout << "8) user_return\n";
			cout << "9) print_users\n";
			cout << "10) exit\n";

			cin >> choice;

			if (!(choice <= 10 && choice >= 1))
			{
				cout << "invalid choice. try again \n";
				choice = -1;
			}
		}

		return choice;
	}

	void run()
	{

		while (true)
		{
			int ch = choice();


			if (ch == 1)
			{
				add_book();
			}
			else if (ch == 2)
			{
				search_by_prefix();
			}
			else if (ch == 3)
			{
				who_borrowed_book();
			}
			else if (ch == 4)
			{
				print_by_id();
			}
			else if (ch == 5)
			{
				print_by_name();
			}
			else if (ch == 6)
			{
				add_user();
			}
			else if (ch == 7)
			{
				borrow_book();
			}
			else if (ch == 8)
			{
				return_book();
			}
			else if (ch == 9)
			{
				print_all();
			}
			else
				return;
		}
	}

	void add_book()
	{
		cout << "Enter book info: id & name & quantity: \n";
		int id, quantity;
		string name;

		cin >> id >> name >> quantity;

		book b(id, name, quantity);
		books.push_back(b);
	}

	void add_user()
	{
		cout << "Enter user info: name & national id: \n";
		int id;
		string name;

		cin >> name >> id;
		user u(name, id);
		users.push_back(u);
	}

	void search_by_prefix()
	{
		cout << "Enter book name by prefix: \n";
		string prefix;
		cin >> prefix;

		bool found = false;

		for (int i = 0; i < books.size(); i++)
		{
			if (books[i].name.find(prefix) != string::npos)
			{
				cout << books[i].name << '\n';
				found = true;
			}
		}

		if (!found)
		{
			cout << "No books with such prefix\n";
		}
	}

	int find_user(string s)
	{
		for (int i = 0; i < users.size(); i++)
		{
			if (users[i].name == s)
			{
				return i;
			}
		}

		return -1;
	}

	int find_book(string b)
	{
		for (int i = 0; i < books.size(); i++)
		{
			if (books[i].name == b)
			{
				return i;
			}
		}

		return -1;
	}

	void borrow_book()
	{
		cout << "Enter user name and book name: \n";
		string name, book;
		cin >> name >> book;

		int user_index = find_user(name);
		int book_index = find_book(book);

		if (user_index != -1)
		{
			if (book_index != -1)
			{
				if (books[book_index].quantity == 0)
				{
					cout << "Book out of stock\n";
					return;
				}
				books[book_index].quantity--;
				books[book_index].borrowed++;
				books[book_index].book_users.push_back(users[user_index]);
				users[user_index].user_books.push_back(books[book_index]);
			}
			else
			{
				cout << "No book such a name\n";
				return;
			}
		}
		else
		{
			cout << "No user such a name\n";
			return;
		}
	}

	void return_book()
	{
		cout << "Enter user name and book name: \n";
		string name, book;
		cin >> name >> book;

		int user_index = find_user(name);
		int book_index = find_book(book);

		if (user_index != -1)
		{
			if (book_index != -1)
			{
				if (books[book_index].borrowed == 0)
				{
					cout << "Books are full\n";
					return;
				}
				books[book_index].quantity++;
				books[book_index].borrowed--;
				books[book_index].book_users.erase(books[book_index].book_users.begin() + user_index);
				users[user_index].user_books.erase(users[user_index].user_books.begin() + book_index);
			}
			else
			{
				cout << "No book such a name\n";
				return;
			}
		}
		else
		{
			cout << "No user such a name\n";
			return;
		}
	}

	void print_by_id()
	{
		sort(books.begin(), books.end(), book::cmp_by_id);

		for (book& b : books)
			b.print();
	}

	void print_by_name()
	{
		sort(books.begin(), books.end(), book::cmp_by_name);

		for (book& b : books)
			b.print();
	}

	void print_all()
	{
		for (user& u : users)
			u.print();
	}

	void who_borrowed_book()
	{
		cout << "Enter book name: \n";
		string book;
		cin >> book;

		int idx = find_book(book);

		if (idx == -1)
			return;

		for (int i = 0; i < books[idx].book_users.size(); i++)
		{
			cout << books[idx].book_users[i].name << ' ';
		}

		cout << '\n';
	}

};

int main()
{
	library l;
	l.run();
}
