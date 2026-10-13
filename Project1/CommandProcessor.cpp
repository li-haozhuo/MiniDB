#include <sstream>
#include <vector>
#include <cctype>
#include "CommandProcessor.h"
using namespace std;

namespace {
	string toUpper(string s) {
		for (char& c : s) {
			c = toupper(static_cast<unsigned char>(c));
		}
		return s;
	}
	string wrongArgs(const string& cmd) {
		return "ERR wrong number of arguments for '" + cmd + "'";
	}
}

Response processCommand(Database& db, const string& line) {
	if (line.empty()) return { "" };

	istringstream iss(line);
	string cmd;
	iss >> cmd;

	if (cmd.empty()) return { "" };
	cmd = toUpper(cmd);

	if (cmd == "KEYS") {
		string extra;
		if (iss >> extra) return { wrongArgs(cmd) };

		vector<string> keys = db.keys();
		if (keys.empty()) return { "(empty)" };

		string result = keys[0];
		for (size_t i = 1; i < keys.size(); ++i) {
			result += "\n" + keys[i];
		}
		return { result };
	}
	else if (cmd == "GET") {
		string key, extra;
		iss >> key;
		if (key.empty() || (iss >> extra)) return { wrongArgs(cmd) };
		return { db.get(key).value_or("(nil)") };
	}
	else if (cmd == "SET") {
		string key, value;
		iss >> key;
		getline(iss >> ws, value);

		if (key.empty() || value.empty()) return { wrongArgs(cmd) };
		db.set(key, value);
		return { "OK" };
	}
	else if (cmd == "DEL") {
		string key, extra;
		iss >> key;
		if (key.empty() || (iss >> extra)) return { wrongArgs(cmd) };
		bool deleted = db.remove(key);
		return { deleted ? "(integer) 1" : "(integer) 0" };
	}
	else if (cmd == "EXISTS") {
		string key, extra;
		iss >> key;
		if (key.empty() || (iss >> extra)) return { wrongArgs(cmd) };
		bool exists = db.exists(key);
		return { exists ? "(integer) 1" : "(integer) 0" };
	}
	else if (cmd == "SAVE") {
		string filename, extra;
		iss >> filename;
		if (filename.empty() || (iss >> extra)) return { wrongArgs(cmd) };
		bool success = db.save(filename);
		if (!success) return { "ERR cannot open file '" + filename + "'" };
		return { "OK" };
	}
	else if (cmd == "LOAD") {
		string filename, extra;
		iss >> filename;
		if (filename.empty() || (iss >> extra)) return { wrongArgs(cmd) };
		string result = db.load(filename);
		return { result };
	}
	else if (cmd == "EXIT") {
		string extra;
		if (iss >> extra) return { wrongArgs(cmd) };
		return { "", true };
	}
	else {
		return { "ERR unknown command '" + cmd + "'" };
	}
	
	return { "" };
}