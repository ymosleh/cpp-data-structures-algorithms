#include "DSLinkedList.h"


int main() {

	// Example with integers
	DSLinkedList<int> intList(4);
	intList.append(65);
	intList.append(5);
	intList.append(67);
	intList.printList();
	std::cout << "List size: " << intList.size() << std::endl;
	intList.deleteLast();
	intList.deleteLast();
	intList.printList();
	std::cout << "List size: " << intList.size() << std::endl;

	std::cout << "\n--- String Example ---\n";

	// Example with strings
	DSLinkedList<std::string> stringList("Hello");
	stringList.append("World");
	stringList.append("Template");
	stringList.append("Example");
	stringList.printList();
	std::cout << "String list size: " << stringList.size() << std::endl;

	std::cout << "\n--- Double Example ---\n";

	// Example with doubles
	DSLinkedList<double> doubleList(3.14);
	doubleList.append(2.71);
	doubleList.append(1.41);
	doubleList.printList();
	std::cout << "Double list size: " << doubleList.size() << std::endl;

	return 0;
}