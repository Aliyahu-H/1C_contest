#pragma once
#include <unordered_map>
#include <vector>
#include <string>
#include <memory>

struct Node
{
public:
	Node(char _name);
	Node* FindChild(char name);
	Node* AddChild(char name);

	std::unordered_map<char, std::unique_ptr<Node>> children;
	Node* parrent;
	Node* suffix_ptr;
	Node* short_suffix_ptr;
	char name;
	bool is_terminated;
	Node* bridge;
};

class Trie
{
public:
	Trie();
	Trie(char root_name);
	Trie(const std::vector<std::string>& s);
	void BuildTrie(const std::vector<std::string>& patterns);
	
	Node* AddString(const std::string& s, Node* bridge_);

	Node* Find(const std::string& s) const;
	std::string ReturnKey(Node* leaf) const;
private:
	Node* add_char(const std::string& s, int i, Node* current, Node* bridge_);

	std::unique_ptr<Node> root;
};
