#pragma once

#include <iostream>
#include <memory>


/* Template node for linked list elements.*/ 

template <typename T>
class DataNode {
public:
	T value{};
	std::unique_ptr<DataNode<T>> next{ nullptr };
	DataNode(const T& v) : value(v), next(nullptr) {}
};

// Singly linked list with tail pointer for O(1) append.
template <typename T>
class DSLinkedList {
private:
	std::unique_ptr<DataNode<T>> head{nullptr};
	DataNode<T>* tail{ nullptr }; // raw pointer, since tail is not responsible for the object lifetime.
	int length{};

public:
	DSLinkedList() : head(nullptr), tail(nullptr), length(0) {}

	DSLinkedList(const T& value) {
		head = std::make_unique<DataNode<T>>(value);
		tail = head.get();
		length = 1;
	}

	void append(const T& value) {
		auto newNode = std::make_unique<DataNode<T>>(value);
		if (!head) {
			head = std::move(newNode);
			tail = head.get();
		}
		else {
			tail->next = std::move(newNode);
			tail = tail->next.get();
		}
		++length;
	}

	void prepend(const T& value) {
		auto newNode = std::make_unique<DataNode<T>>(value);
		if (!head) {
			head = std::move(newNode);
			tail = head.get();
		}
		else {
			newNode->next = std::move(head);
			head = std::move(newNode);
		}
		++length;
	}

	void deleteLast() {
		if (!head) {
			return;
		}

		if (!head->next) {
			head.reset(); // Deletes node and set head to nullptr.
			tail = nullptr;
			length = 0;
			return;
		}

		auto prev = head.get();
		while (prev->next.get() != tail) {
			prev = prev->next.get();
		}
		prev->next.reset();
		tail = prev;
		--length;
	}

	void deleteFirst() {
		if (!head) {
			return;
		}

		if (length == 1) {
			head.reset();
			tail = nullptr;
		}
		else {
			head = std::move(head->next);
		}
		--length;
	}

	DataNode<T>* get(int index) {
		if (index < 0 || index >= length) {
			return nullptr;
		}

		auto current = head.get();
		for (int i = 0; i < index; ++i) {
			current = current->next.get();
		}
		return current;
	}

	bool set(int index, const T& value) {
		auto current = get(index);
		if (current) {
			current->value = value;
			return true;
		}
		return false;
	}

	bool insert(int index, const T& value) {
		if (index < 0 || index > length) {
			return false;
		}
		if (index == 0) {
			prepend(value);
			return true;

		}
		if (index == length) {
			append(value);
			return true;

		}

		auto newNode = std::make_unique<DataNode<T>> (value);
		auto current = get(index - 1);
		newNode->next = std::move(current->next);
		current->next = std::move(newNode);

		++length;
		return true;
	}

	void removeAt(int index) {
		if (index < 0 || index >= length) {
			return;
		}
		if (index == 0) {
			deleteFirst();
			return;
		}
		if (index == length - 1) {
			deleteLast();
			return;
		}

		auto prev = get(index - 1);
		prev->next = std::move(prev->next->next); // Reassigning prev->next destroys the old unique_ptr, automatically deleting the target node.
		--length;
	}

	void printList() const {
		if (!head) {
			return;
		}

		auto iter = head.get();
		while (iter) {
			std::cout << iter->value;
			if (iter->next) std::cout << " -> ";
			iter = iter->next.get();
		}
		std::cout << std::endl;
	}


	int size() const { return length; }
};