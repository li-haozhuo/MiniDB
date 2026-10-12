#include <algorithm>
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