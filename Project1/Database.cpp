#include <algorithm>
#include <fstream>
#include <string>
#include "Database.h"

void Database::set(const std::string& key, const std::string& value) {
	data[key] = value;
}

std::optional<std::string> Database::get(const std::string& key) const {
	auto it = data.find(key);
	if (it != data.end()) {
		return it->second;
	}
	return std::nullopt;
}

bool Database::remove(const std::string& key) {
	return data.erase(key) > 0;
}
bool Database::exists(const std::string& key) const {
	return data.find(key) != data.end();
}
size_t Database::size() const {
	return data.size();
}

std::vector<std::string> Database::keys() const {
	std::vector<std::string> result;
	result.reserve(data.size());

	for (const auto& pair : data) {
		result.push_back(pair.first);
	}
	std::sort(result.begin(), result.end());
	return result;
}

bool Database::save(const std::string& filename) const {
	std::ofstream out(filename);
	if (!out) return false;

	for (const auto& pair : data) {
		out << pair.first << "=" << pair.second << "\n";
	}
	return true;
}

std::string Database::load(const std::string& filename) {
	std::ifstream in(filename);
	if (!in) {
		return "ERR cannot open file '" + filename + "'";
	}
	std::unordered_map<std::string, std::string> temp_data;
	std::string line;
	int lineNum = 1;

	while (std::getline(in, line)) {
		if (line.empty()) {
			lineNum++;
			continue;
		}
		size_t pos = line.find('=');

		if (pos == std::string::npos || pos == 0) {
			return "ERR malformed line " + std::to_string(lineNum);
		}

		std::string key = line.substr(0, pos);
		std::string value = line.substr(pos + 1);

		temp_data[key] = value;
		lineNum++;
	}

	data.swap(temp_data);
	return "OK";
}