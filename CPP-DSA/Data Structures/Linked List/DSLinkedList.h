#pragma once

#include <iostream>
#include <memory>

//using namespace std;


// Template node for linked list elements
template <typename T>
class DataNode {
public:
	T value{};
	std::unique_ptr<DataNode<T>> next{ nullptr };
	DataNode(const T& v) : value(v), next(nullptr) {}
};

// Singly linked list with tail pointer for O(1) append
template <typename T>
class DSLinkedList {
private:
	std::unique_ptr<DataNode<T>> head{nullptr};
	DataNode<T>* tail{ nullptr }; // raw pointer, since tail is not responsible for the object lifetime.
	int len{};

public:
	DSLinkedList() : head(nullptr), tail(nullptr), len(0) {}

	DSLinkedList(const T& v) {
		head = std::make_unique<DataNode<T>>(v);
		tail = head.get();
		len = 1;
	}

	void append(const T& v) {
		auto newNode = std::make_unique<DataNode<T>>(v);

		if (!head) {
			head = std::move(newNode);
			tail = head.get();
		}
		else {
			tail->next = std::move(newNode);
			tail = tail->next.get();
		}
		++len;
	}

	void deleteLast() {
		if (!head) {
			std::cout << "List empty, nothing to delete" << std::endl;
			return;
		}

		// Single element
		if (head->next == nullptr) {
			head.reset(); // Deletes node and set head to nullptr.
			tail = nullptr;
			len = 0;
			return;
		}

		// Find the second to last to last node.
		auto prev = head.get();
		while (prev->next.get() != tail) {
			prev = prev->next.get();
		}
		prev->next.reset();
		tail = prev;
		--len;
	}

	void printList() const {
		if (!head) {
			std::cout << "Empty list, nothing to print" << std::endl;
			return;
		}

		auto iter = head.get();
		while (iter) {
			std::cout << "Value: " << iter->value << std::endl;
			iter = iter->next.get();
		}

	}

	int size() const { return len; }
};