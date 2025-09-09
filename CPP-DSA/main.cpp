#include "DSLinkedList.h"
#include <string>
#include <iostream>

int main() {
    std::cout << "--- Integer List Example ---\n";
    DSLinkedList<int> intList(1);
    intList.append(2);
    intList.append(3);
    intList.append(4);
    intList.append(5);
    intList.printList();

    std::cout << "Remove at index 2 (value 3):\n";
    intList.removeAt(2);
    intList.printList();

    std::cout << "Remove first element:\n";
    intList.removeAt(0);
    intList.printList();

    std::cout << "Remove last element:\n";
    intList.removeAt(intList.size() - 1);
    intList.printList();

    std::cout << "Set index 1 to 500:\n";
    intList.set(1, 500);
    intList.printList();

    std::cout << "Insert 99 at index 1:\n";
    intList.insert(1, 99);
    intList.printList();

    std::cout << "List size: " << intList.size() << "\n\n";

    // --------------------------------------------------------
    std::cout << "--- String List Example ---\n";
    DSLinkedList<std::string> stringList("Hello");
    stringList.append("World");
    stringList.append("Template");
    stringList.append("Example");
    stringList.printList();
    std::cout << "List size: " << stringList.size() << "\n\n";

    // --------------------------------------------------------
    std::cout << "--- Double List Example ---\n";
    DSLinkedList<double> doubleList(3.14);
    doubleList.append(2.71);
    doubleList.append(1.41);
    doubleList.printList();
    std::cout << "List size: " << doubleList.size() << "\n\n";


    std::cout << "--- Algorithms Reverse List---\n";
    doubleList.printList();
    doubleList.reverse();
    std::cout << "Reverse: ";
    doubleList.printList();


    return 0;
}
