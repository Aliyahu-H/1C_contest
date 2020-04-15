#include "Trie.h"


Node::Node(char _name) : short_suffix_ptr(nullptr), suffix_ptr(nullptr), name(_name), is_terminated(false), bridge(nullptr), parrent(nullptr)
{
	children.reserve(1);
}


Node* Node::AddChild(char name) {
	children.insert(std::pair<char, std::unique_ptr<Node>>(name, std::make_unique<Node>(name)));
	Node* child = children[name].get();
	child->parrent = this;
	return child;
}

Node* Node::FindChild(char name) {
	auto position = children.find(name);
	if (position == children.end())
		return nullptr;
	else
		return position->second.get();
}

Trie::Trie() : root(std::make_unique<Node>(-1)) {
}

Trie::Trie(char root_name) : root(std::make_unique<Node>(root_name)) {
}

Trie::Trie(const std::vector<std::string>& patterns) : root(std::make_unique<Node>(-1)){
	BuildTrie(patterns);
}

Node* Trie::add_char(const std::string& s, int i, Node* start, Node* bridge_) {
	if (start->FindChild(s[i]) == nullptr) {
		Node* current = start->suffix_ptr;
		start = start->AddChild(s[i]);
		while (current != nullptr) {
			if (current->FindChild(s[i]) != nullptr) {
				start->suffix_ptr = current->FindChild(s[i]);
				break;
			}
			current = current->suffix_ptr;
		}
		if (current == nullptr) {
			start->suffix_ptr = root.get();
		}
		current = start->suffix_ptr;
		while (current != nullptr) {
			if (current->is_terminated) {
				start->short_suffix_ptr = current;
				break;
			}
			current = current->short_suffix_ptr;
		}
		if (current == nullptr) {
			start->short_suffix_ptr = root.get();
		}
		if (i == s.size() - 1) {
			start->is_terminated = true;
			start->bridge = bridge_;
		}
	}
	else {
		start = start->FindChild(s[i]);
		if (i == s.size() - 1) {
			start->is_terminated = true;
			start->bridge = bridge_;
		}
	}
	return start;
}

void Trie::BuildTrie(const std::vector<std::string>& patterns) {
	int i = 0;
	int skip = 0;
	std::vector<Node*> parents(patterns.size(), root.get());
	while (true) {
		for (int j = 0; j < patterns.size(); ++j) {
			if (i >= patterns[j].size()) {
				++skip;
				continue;
			}
			add_char(patterns[j], i, parents[j], nullptr);
		}
		if (skip == patterns.size())
			break;
		skip = 0;
		++i;
	}
}

Node* Trie::AddString(const std::string& s, Node* bridge_ = nullptr) {
	Node* leaf = root.get();
	for (int i = 0; i < s.size(); ++i) {
		leaf = add_char(s, i, leaf, bridge_);
	}
	return leaf;
}

Node* Trie::Find(const std::string& s) const {
	Node* current = root.get();

	for(int i = 0; i < s.size(); ++i) {
		current = current->FindChild(s[i]);
	}

	return current->bridge;
}

std::string Trie::ReturnKey(Node* leaf) const {
	std::string key = "";
	key += leaf->name;
	Node* current = leaf->parrent;

	while (current != root.get()) {
		key = current->name + key;
		current = current->parrent;
	} ;

	return key;
}
