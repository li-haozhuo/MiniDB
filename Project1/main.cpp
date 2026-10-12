#include <iostream>
#include <string>
#include "Database.h"
#include "CommandProcessor.h"
using namespace std;

int main() {
	Database db;
	string line;

	while (true) {
		cout << "> ";
		if (!getline(cin, line)) break;

		Response r = processCommand(db, line);
		if (!r.text.empty()) {
			cout << r.text << endl;
		}
		if (r.quit) {
			break;
		}
	}
	return 0;
}