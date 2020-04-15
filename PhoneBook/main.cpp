#include <iostream>
#include "PhoneBook.h"


int main(int argc, char **argv) {
	PhoneBook phone_book;
	int n = 0;

	std::cin >> n;

	std::string name;
	std::string phone;

	for (int i = 0; i < n; ++i) {
		std::cin >> name;
		std::cin >> phone;
		phone_book.AddNote(name, phone);
	}

	std::cin >> n;

	for (int i = 0; i < n; ++i) {
		std::cin >> name;
		std::cout << phone_book.FindByName(name) << std::endl;

		std::cin >> phone;
		std::cout << phone_book.FindByPhone(phone) << std::endl;
	}
	
	return 0;
}