#include "PhoneBook.h"

PhoneBook::PhoneBook() {
}

void PhoneBook::AddNote(const std::string& name, const std::string& phone) {
	Node* bridge_to_name = names.AddString(name, nullptr);
	Node* bridge_to_phone = phones.AddString(phone, bridge_to_name);
	names.AddString(name, bridge_to_phone);
}

std::string PhoneBook::FindByName(const std::string& name) {
	return phones.ReturnKey(names.Find(name, nullptr, 0)[0]);
}

std::string PhoneBook::FindByPhone(const std::string& phone) {
	return names.ReturnKey(phones.Find(phone, nullptr, 0)[0]);
}

std::vector<std::string> PhoneBook::FindByPhonePattern(const std::string& phone_pattern) const {
	std::vector<std::string> answer;
	std::vector<Node*> name_links = phones.Find(phone_pattern, nullptr, 0);
	for (auto u : name_links) {
		answer.push_back(names.ReturnKey(u));
	}
	return answer;
}