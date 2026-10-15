#pragma once
#include <string>
#include "Database.h"

class CommandProcessor {
private:
	Database& db;
public:
	CommandProcessor(Database& database);
	std::string execute(const std::string& input);
};