#include "DSLinkedList.h"
#include "testUtils.h"
#include <string>


int main(int argc, char * argv[]) {
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

    std::cout << "--- String List Example ---\n";
    DSLinkedList<std::string> stringList("Hello");
    stringList.append("World");
    stringList.append("Template");
    stringList.append("Example");
    stringList.printList();
    std::cout << "List size: " << stringList.size() << "\n\n";

    std::cout << "--- Double List Example ---\n";
    DSLinkedList<double> doubleList(3.14);
    doubleList.append(2.71);
    doubleList.append(1.41);
    doubleList.printList();
    std::cout << "List size: " << doubleList.size() << "\n\n";


    std::cout << "--- Reverse List ---\n";
    doubleList.reverse();
    
    DSLinkedList<int> nums(1);
    nums.append(2);
    nums.append(3);
    nums.append(4);
    nums.append(5);
    nums.printList();

    std::cout << "--- Middle node ---\n";
    std::cout << nums.findMiddle()->value << std::endl;

    testCycleDetection();

    std::cout << "--- Find the Kth Node from end ---\n";
    std::cout << nums.findKthNodeFromEnd(2)->value << std::endl;

    return 0;
}

