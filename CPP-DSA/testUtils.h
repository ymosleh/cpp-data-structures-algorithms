#pragma once
#include <iostream>

/*
  Since our linked list uses smart pointers (unique_ptr), it enforces an acyclic structure.
  This makes it tricky to introduce cycles for testing.
  Therefore, this separate implementation uses raw pointers to create and test linked lists with cycles.
*/


/// <summary>
/// Simple node structure for a raw-pointer linked list, 
/// used to test cycle detection.
/// </summary>
struct TestNode {
    int value;
    TestNode* next;
    TestNode(int v) : value(v), next(nullptr) {}
};

/// <summary>
/// Detects whether the linked list contains a cycle using the slow/fast pointer technique.
/// Time: O(N) | Space O(1)
/// </summary>
/// <param name="head"> Pointer to the head of the list. </param>
/// <returns> True if a cycle is detected; otherwise false. </returns>
inline bool hasCycle(TestNode* head) {
    if (!head || !head->next) return false;

    TestNode* slow = head;
    TestNode* fast = head;

    while (fast && fast->next) {
        fast = fast->next->next;
        slow = slow->next;
        if (fast == slow) return true;
    }
    return false;
}

/// <summary>
/// Small test harness for demonstrating cycle detection.
/// Creates a list, tests without a cycle, then introduces one.
/// </summary>
inline void testCycleDetection() {
    // Create test nodes with raw pointers
    TestNode* node1 = new TestNode(1);
    TestNode* node2 = new TestNode(2);
    TestNode* node3 = new TestNode(3);
    TestNode* node4 = new TestNode(4);

    // Link them
    node1->next = node2;
    node2->next = node3;
    node3->next = node4;

    std::cout << "--- Cycle detection ---\n";
    std::cout << "No cycle: " << hasCycle(node1) << std::endl;

    // Create cycle
    node4->next = node2; // Cycle back to node2

    std::cout << "With cycle: " << hasCycle(node1) << std::endl;

    // Clean up: break cycle before deleting nodes.
    node4->next = nullptr;
    delete node1; delete node2; delete node3; delete node4;
}