#pragma once
#include "Trie.h"

class PhoneBook
{
public:
	PhoneBook();

	void AddNote(const std::string& name, const std::string& phone);

	std::string FindByName(const std::string& name);
	std::string FindByPhone(const std::string& phone);
	std::vector<std::string> FindByPhonePattern(const std::string& phone_pattern) const;
private:
	Trie names;
	Trie phones;
};

