#include <iostream>
#include <cassert>
#include <string>
#include "Database.h"
#include "CommandProcessor.h"

void run_unit_tests() {
	std::cout << "RUNNING m4 AUTOMATED TESTS \n";
	Database db;
	db.set("name", "JLA");
	assert(db.get("name").value_or("") == "JLA");

	try {
		db.set("", "value");
		assert(false);
	} catch (const std::invalid_argument&) {}

	try {
		db.set("a=b", "value");
		assert(false);
	} catch (const std::invalid_argument&) {}

	CommandProcessor cmd(db);
	assert(cmd.execute("SET hero batman") == "OK");
	assert(cmd.execute("GET hero") == "batman");

	std::cout << "[PASS] ALL UNIT TESTS PASSED!\n\n";
}

int main() {
	run_unit_tests();
	
	Database db;
	CommandProcessor cmd(db);
	std::string line;

	std::cout << "MiniDB Interactive CLI \n";
	std::cout << "give command:\n ";

	while (true) {
		std::cout << "minidb> ";
		if (!std::getline(std::cin, line)) break;

		std::string response = cmd.execute(line);
		if (response == "EXIT") {
			std::cout << "BYE!\n";
			break;
		}

		if (!response.empty()) {
			std::cout << response << "\n";
		}
	}
	return 0;
}