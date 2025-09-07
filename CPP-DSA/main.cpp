#include ""

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