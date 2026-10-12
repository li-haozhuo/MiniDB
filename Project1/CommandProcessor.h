#pragma once
#include <string>
#include "Database.h"

struct Response {
	std::string text;
	bool quit = false;
};

Response processCommand(Database& db, const std::string& line);