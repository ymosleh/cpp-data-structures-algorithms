#include <iostream>
#include <memory>

using namespace std;

// Template node for linked list elements
template <typename T>
class DataNode {
	public:
		T value{};
		unique_ptr<DataNode<T>> next{ nullptr };
		DataNode(const T& v) : value(v), next(nullptr) {}
};

// Singly linked list with tail pointer for O(1) append
template <typename T>
class DSLinkedList {
	private:
		unique_ptr<DataNode<T>> head{ nullptr };
		DataNode<T>* tail{ nullptr }; // raw pointer, since tail is not responsible for the object lifetime.
		int len{};

	public:
		DSLinkedList() : head(nullptr), tail(nullptr), len(0) {}

		DSLinkedList(const T& v) {
			head = make_unique<DataNode<T>>(v);
			tail = head.get();
			len = 1;
		}

		void append(const T& v) {
			auto newNode = make_unique<DataNode<T>>(v);
			
			if (!head) {
				head = move(newNode);
				tail = head.get();
			}
			else {
				tail->next = move(newNode);
				tail = tail->next.get();
			}
			++len;
		}

		void deleteLast() {
			if (!head) {
				cout << "List empty, nothing to delete" << endl;
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
				cout << "Empty list, nothing to print" << endl;
				return;
			}
			
			auto iter = head.get();
			while (iter) {
				cout << "Value: " << iter->value << endl;
				iter = iter->next.get();
			}

		}

		int size() const { return len; }
};


int main() {

	// Example with integers
	DSLinkedList<int> intList(4);
	intList.append(65);
	intList.append(5);
	intList.append(67);
	intList.printList();
	cout << "List size: " << intList.size() << endl;
	intList.deleteLast();
	intList.deleteLast();
	intList.printList();
	cout << "List size: " << intList.size() << endl;

	cout << "\n--- String Example ---\n";

	// Example with strings
	DSLinkedList<string> stringList("Hello");
	stringList.append("World");
	stringList.append("Template");
	stringList.append("Example");
	stringList.printList();
	cout << "String list size: " << stringList.size() << endl;

	cout << "\n--- Double Example ---\n";

	// Example with doubles
	DSLinkedList<double> doubleList(3.14);
	doubleList.append(2.71);
	doubleList.append(1.41);
	doubleList.printList();
	cout << "Double list size: " << doubleList.size() << endl;

	return 0;
}