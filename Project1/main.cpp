#include <iostream>
#include "Database.h"
using namespace std;

int main() {
	Database db;
	
	db.set("name", "alice");
	db.set("city", "new york");
	db.set("name", "bob");

	cout << "size: " << db.size() << endl;
	cout << "exists name: " << db.exists("name") << endl;
	cout << "exists age: " << db.exists("age") << endl;

	cout << "get name: " << db.get("name").value_or("none") << endl;
	cout << "get age: " << db.get("age").value_or("none") << endl;

	cout << "remove city: " << db.remove("city") << endl;
	cout << "remove city again: " << db.remove("city") << endl;
	cout << "size: " << db.size() << endl;

	const Database& view = db;
	cout << "size via const ref: " << view.size() << endl;
	cout << "exists via const ref: " << view.exists("name") << endl;

	return 0;
}
