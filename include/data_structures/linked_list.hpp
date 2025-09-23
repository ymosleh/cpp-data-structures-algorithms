#pragma once
#include <iostream>
#include <memory>


// Linked list template using smart pointers.

/// <summary>
/// Node of a singly linked list.
/// Owns the next node via unique_ptr to enforce single ownership.
/// </summary>
/// <typeparam name="T"> Type stored in the list. </typeparam>
template <typename T>
class DataNode {
public:
	T value{};
	std::unique_ptr<DataNode<T>> next{ nullptr };
	DataNode(const T& v) : value(v), next(nullptr) {}
};

/// <summary>
/// Singly linked list implementation using smart pointers.
/// Maintains O(1) append with a non-owning raw tail pointer.
/// </summary>
template <typename T>
class DSLinkedList {
private:
	std::unique_ptr<DataNode<T>> head{ nullptr };
	DataNode<T>* tail{ nullptr }; // Raw pointer, since tail is not responsible for the object lifetime.
	int length{};

	void relinkTail() {
		tail = head.get();
		while (tail && tail->next) {
			tail = tail->next.get();
		}
	}

public:
	DSLinkedList() : head(nullptr), tail(nullptr), length(0) {}

	DSLinkedList(const T& value) {
		head = std::make_unique<DataNode<T>>(value);
		tail = head.get();
		length = 1;
	}

	~DSLinkedList() = default;

	// Copy constructor
	DSLinkedList(const DSLinkedList& other) : head(nullptr), tail(nullptr), length(0) {
		auto* current = other.head.get();
		while (current) {
			append(current->value);
			current = current->next.get();
		}
	}

	// Copy assignment operator
	DSLinkedList& operator=(const DSLinkedList& other) {
		if (this != &other) {
			// Clear current list
			head.reset();
			tail = nullptr;
			length = 0;

			// Copy from other
			auto* current = other.head.get();
			while (current) {
				append(current->value);
				current = current->next.get();
			}
		}
		return *this;
	}

	// Move constructor
	DSLinkedList(DSLinkedList&& other) noexcept
		: head(std::move(other.head)), tail(other.tail), length(other.length) {
		other.tail = nullptr;
		other.length = 0;
	}

	// Move assignment operator
	DSLinkedList& operator=(DSLinkedList&& other) noexcept {
		if (this != &other) {
			head = std::move(other.head);
			tail = other.tail;
			length = other.length;

			other.tail = nullptr;
			other.length = 0;
		}
		return *this;
	}

	/// <summary>
	/// Appends an element to the end of the list in O(1).
	/// Uses the tail pointer for efficiency.
	/// </summary>
	/// <param name="value"> The value to store in the newly created tail node. </param>
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

	/// <summary>
	/// Prepends an element to the start of the list in O(1).
	/// </summary>
	/// <param name="value"> The value to store in the new head node. </param>
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

	/// <summary>
	/// Deletes the last node.
	/// Traverses the list to find the node before the tail. O(n).
	/// </summary>
	void deleteLast() {
		if (!head) return;

		if (!head->next) {
			head.reset();  // Deletes node and sets head to nullptr.
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

	/// <summary>
	/// Deletes the first node in O(1).
	/// </summary>
	void deleteFirst() {
		if (!head) return;

		if (length == 1) {
			head.reset();
			tail = nullptr;
		}
		else {
			head = std::move(head->next);
		}
		--length;
	}

	/// <summary>
	/// Returns the node at the given index, or nullptr if out of range.
	/// Time: O(n).
	/// </summary>
	/// <param name="index"> Zero-based index of the node to retrieve. </param>
	/// <returns> Pointer to the node if valid, otherwise nullptr. </returns>
	DataNode<T>* get(int index) {
		if (index < 0 || index >= length) return nullptr;

		auto current = head.get();
		for (int i = 0; i < index; ++i) {
			current = current->next.get();
		}
		return current;
	}

	/// <summary>
	/// Sets the value of the node at the given index.
	/// </summary>
	/// <param name="index"> Zero-based index of the node whose value will be updated. </param>
	/// <param name="value"> The new value to assign to the node. </param>
	/// <returns> True if the node value was updated; false if the index was invalid. </returns>
	bool set(int index, const T& value) {
		auto current = get(index);
		if (current) {
			current->value = value;
			return true;
		}
		return false;
	}

	/// <summary>
	/// Inserts a new node at the specified index. Supports insert at head, tail, or middle.
	/// </summary>
	/// <param name="index"> Zero-based position where the new node will be inserted. </param>
	/// <param name="value"> The value to store in the newly inserted node. </param>
	/// <returns> True if the node was inserted; false if the index was invalid. </returns>
	bool insert(int index, const T& value) {
		if (index < 0 || index > length) return false;

		if (index == 0) {
			prepend(value);
			return true;
		}
		if (index == length) {
			append(value);
			return true;
		}

		auto newNode = std::make_unique<DataNode<T>>(value);
		auto current = get(index - 1);
		newNode->next = std::move(current->next);
		current->next = std::move(newNode);

		++length;
		return true;
	}

	/// <summary>
	/// Removes the node at the given index.
	/// Relinks nodes by transferring unique_ptr ownership, which deletes the removed node.
	/// Time: O(n).
	/// </summary>
	/// <param name="index"> Zero-based index of the node to remove. </param>
	void removeAt(int index) {
		if (index < 0 || index >= length) return;

		if (index == 0) {
			deleteFirst();
			return;
		}
		if (index == length - 1) {
			deleteLast();
			return;
		}

		auto prev = get(index - 1);
		prev->next = std::move(prev->next->next);  // Old node deleted automatically.
		--length;
	}

	/// <summary>
	/// Prints the list contents to stdout in "a -> b -> c" format.
	/// </summary>
	void printList() const {
		auto iter = head.get();
		while (iter) {
			std::cout << iter->value;
			if (iter->next) std::cout << " -> ";
			iter = iter->next.get();
		}
		std::cout << std::endl;
	}

	/// <summary>
	/// Returns the number of elements in the list.
	/// </summary>
	/// <returns> The current list size. </returns>
	int size() const { return length; }


	/*** Linked list algorithms ***/

	/// <summary>
	/// LeetCode 206. Reverse Linked List.
	/// Reverses the list in place.
	/// Time: O(n) | Space: O(1).
	/// </summary>
	void reverse() {
		if (!head || !head->next) return;

		std::unique_ptr<DataNode<T>> prev = nullptr;
		auto current = std::move(head);
		tail = current.get();  // Old head becomes new tail.

		while (current) {
			auto nextNode = std::move(current->next);
			current->next = std::move(prev);
			prev = std::move(current);
			current = std::move(nextNode);
		}
		head = std::move(prev);
	}

	/// <summary>
	/// LeetCode 876. Middle of the Linked List.
	/// Returns the middle node using the slow/fast pointer technique.
	/// For even-length lists, returns the second middle node.
	/// Time: O(n) | Space: O(1).
	/// </summary>
	/// <returns> Pointer to the middle node if the list is non-empty; otherwise nullptr. </returns>
	DataNode<T>* findMiddle() {
		if (!head) return nullptr;

		auto* slow = head.get();
		auto* fast = head.get();
		while (fast && fast->next) {
			fast = fast->next->next.get();
			slow = slow->next.get();
		}
		return slow;
	}

	/// <summary>
	/// Finds the k-th node from the end (tail).
	/// Constraints: Cannot use the length variable.
	/// Time: O(n) | Space: O(1).
	/// </summary>
	/// <param name="k"> One-based index from the end (k=1 returns the last node). </param>
	/// <returns> Pointer to the node if valid; otherwise nullptr. </returns>
	DataNode<T>* findKthNodeFromEnd(int k) {
		if (k <= 0 || !head) return nullptr;

		auto* fast = head.get();
		auto* slow = head.get();

		// Move fast k steps ahead
		for (int i = 0; i < k; ++i) {
			if (!fast) return nullptr;
			fast = fast->next.get();
		}

		while (fast) {
			slow = slow->next.get();
			fast = fast->next.get();
		}
		return slow;
	}

	/// <summary>
	/// LeetCode 83. Remove Duplicates from Sorted List.
	/// Removes duplicates so each element appears once.
	/// Time: O(n) | Space: O(1).
	/// </summary>
	void removeDuplicatesFromSortedList() {
		auto* current = head.get();
		while (current && current->next) {
			if (current->value == current->next->value) {
				auto temp = std::move(current->next);  // Take ownership of duplicate node.
				current->next = std::move(temp->next);
				--length;
				if (!current->next) tail = current;
			}
			else {
				current = current->next.get();
			}
		}
	}

	/// <summary>
	/// LeetCode 1290. Convert Binary Number in a Linked List to Integer.
	/// Converts binary sequence to a decimal value.
	/// Constraint: Each node's value must be 0 or 1.
	/// Time: O(n) | Space: O(1).
	/// </summary>
	/// <returns> The decimal representation of the binary sequence. </returns>
	int binaryToDecimal() {
		int result = 0;
		auto* current = head.get();
		while (current) {
			result = (result << 1) | current->value;
			current = current->next.get();
		}
		return result;
	}

	/// <summary>
	/// LeetCode 86. Partition List.
	/// Partitions the list so all nodes less than x come before nodes greater than or equal to x.
	/// Preserves relative order in both partitions.
	/// Time: O(n) | Space: O(1).
	/// </summary>
	/// <param name="x"> The partition value. </param>
	/// <returns> Pointer to the new head of the partitioned list. </returns>
	DataNode<T>* partitionList(const T& x) {
		if (!head) return nullptr;

		auto beforeList = std::make_unique<DataNode<T>>(T{});
		auto afterList = std::make_unique<DataNode<T>>(T{});
		auto* before = beforeList.get();
		auto* after = afterList.get();

		auto current = std::move(head);
		while (current) {
			auto nextNode = std::move(current->next);
			if (current->value < x) {
				before->next = std::move(current);
				before = before->next.get();
			}
			else {
				after->next = std::move(current);
				after = after->next.get();
			}
			current = std::move(nextNode);
		}

		after->next = nullptr;
		before->next = std::move(afterList->next);
		head = std::move(beforeList->next);

		relinkTail();
		return head.get();
	}

	/// <summary>
	/// LeetCode 92. Reverse Linked List II.
	/// Reverses the nodes from indices m to n (0-based).
	/// Time: O(n) | Space: O(1).
	/// </summary>
	/// <param name="m"> Start index of the reversal. </param>
	/// <param name="n"> End index of the reversal. </param>
	void reverseSubset(int m, int n) {
		if (!head || m == n || m < 0 || n < m || n >= length) return;

		DataNode<T> dummyNode(T{});
		dummyNode.next = std::move(head);
		auto* prev = &dummyNode;

		for (int i = 0; i < m; ++i) {
			prev = prev->next.get();
		}

		auto* current = prev->next.get();
		for (int i = 0; i < (n - m); ++i) {
			auto temp = std::move(current->next);
			current->next = std::move(temp->next);
			temp->next = std::move(prev->next);
			prev->next = std::move(temp);
		}
		head = std::move(dummyNode.next);
		relinkTail();
	}

	/// <summary>
	/// LeetCode 24. Swap Nodes in Pairs.
	/// Swaps every two adjacent nodes without modifying values.
	/// Time: O(n) | Space: O(1).
	/// </summary>
	void swapPairs() {
		DataNode<T> dummyNode(T{});
		dummyNode.next = std::move(head);

		auto* prev = &dummyNode;
		auto* first = prev->next.get();

		while (first && first->next) {
			auto second = std::move(first->next);

			// Perform swap
			first->next = std::move(second->next);
			second->next = std::move(prev->next);
			prev->next = std::move(second);

			// Move pointers
			prev = first;
			first = first->next.get();
		}

		head = std::move(dummyNode.next);
		relinkTail();
	}
};
