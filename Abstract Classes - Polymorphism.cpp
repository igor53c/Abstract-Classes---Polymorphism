// Abstract Classes - Polymorphism.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>
using namespace std;

struct Node {
	Node* next;
	Node* prev;
	int value;
	int key;
	Node(Node* p, Node* n, int k, int val) :prev(p), next(n), key(k), value(val) {};
	Node(int k, int val) :prev(nullptr), next(nullptr), key(k), value(val) {};
};

class Cache {

protected:
	map<int, Node*> mp; //map the key to the node in the linked list
	int cp;  //capacity
	Node* tail; // double linked list tail pointer
	Node* head; // double linked list head pointer
	virtual void set(int, int) = 0; //set function
	virtual int get(int) = 0; //get function

};

class LRUCache : Cache {
public:
	LRUCache(int capacity) {
		cp = capacity;
	}
	void set(int key, int value) override {
		if (head == nullptr)
		{
			mp[key] = new Node(key, value);
			head = mp[key];
			tail = mp[key];
		}
		else
		{
			if (mp.find(key) != mp.end())
			{
				if (mp[key]->prev == nullptr)
				{
					mp[key]->value = value;
				}
				else
				{
					mp[key]->prev->next = mp[key]->next;
					mp[key]->prev = nullptr;
					mp[key]->next = head;
					mp[key]->value = value;
					head = mp[key];
				}
			}
			else
			{
				mp[key] = new Node(nullptr, head, key, value);
				head->prev = mp[key];
				head = mp[key];
				if (mp.size() > cp)
				{
					Node* temp = tail;
					tail = temp->prev;
					mp.erase(temp->key);
					tail->next = nullptr;
					tail->prev = nullptr;
					delete temp;
				}
			}
		}
	}
	int get(int key) override  {

		if (mp.find(key) != mp.end())
			return mp[key]->value;

		return -1;
	}
};

int main() {
	int n, capacity, i;
	cin >> n >> capacity;
	LRUCache l(capacity);
	for (i = 0; i < n; i++) {
		string command;
		cin >> command;
		if (command == "get") {
			int key;
			cin >> key;
			cout << l.get(key) << endl;
		}
		else if (command == "set") {
			int key, value;
			cin >> key >> value;
			l.set(key, value);
		}
	}
	return 0;
}
