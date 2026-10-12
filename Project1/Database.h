#pragma once
#include <string>
#include <optional>
#include <unordered_map>
#include <vector>
#include <cstddef>

class Database {
private:
	std::unordered_map<std::string, std::string> data;

public:
	Database() = default;
	void set(const std::string& key, const std::string& value);
	std::optional<std::string> get(const std::string& key) const;
	bool exists(const std::string& key) const;
	bool remove(const std::string& key);
	
	std::size_t size() const;
	std::vector<std::string> keys() const;
};