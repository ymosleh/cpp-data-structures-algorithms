#include "data_structures/linked_list.hpp"
#include "algorithms/test_utils.hpp"
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
    doubleList.printList();

    std::cout << "--- Middle node ---\n";
    DSLinkedList<int> nums(1);
    nums.append(2);
    nums.append(3);
    nums.append(4);
    nums.printList();


    std::cout << "Middle Node: " << nums.findMiddle()->value << std::endl;

    testCycleDetection();

    std::cout << "--- Find the Kth Node from end ---\n";
    std::cout << "Kth node: " << nums.findKthNodeFromEnd(2)->value << std::endl;

    std::cout << "--- Find and remove duplicates ---\n";
    DSLinkedList<int> dupes(1);
    dupes.append(2);
    dupes.append(3);
    dupes.append(4);
    dupes.append(5);

    std::cout << "List with duplicates: " << std::endl;
    dupes.printList();
    std::cout << "size: " << dupes.size() << std::endl;

    dupes.removeDuplicatesFromSortedList();

    std::cout << "List after removing duplicates: " << std::endl;
    dupes.printList();
    std::cout << "size: " << dupes.size() << std::endl;

    DSLinkedList<int> binarySeq(1);
    binarySeq.append(0);
    binarySeq.append(1);
    std::cout << "--- binary to decimal ---\n";
    binarySeq.printList();
    std::cout << "Decimal value: " << binarySeq.binaryToDecimal() << std::endl;

    std::cout << "--- Partition List ---\n";
    DSLinkedList<int> ListToPart(1);
    ListToPart.append(4);
    ListToPart.append(3);
    ListToPart.append(2);
    ListToPart.append(5);
    ListToPart.append(2);

    int x = 3;
    ListToPart.partitionList(x);
    std::cout << "Partitioned List based on X: " << x << std::endl;
    ListToPart.printList();


    std::cout << "--- Reverse subset of list ---\n";
    DSLinkedList<int> reverseSubList(1);
    reverseSubList.append(2);
    reverseSubList.append(3);
    reverseSubList.append(4);
    reverseSubList.append(5);
    reverseSubList.printList();
    reverseSubList.reverseSubset(1, 3);
    reverseSubList.printList();

    return 0;
}

