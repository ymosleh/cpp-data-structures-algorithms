#pragma once
#include <iostream>

// Since the smart-pointer-based linked list enforces an acyclic structure,
// it is difficult to create cycles for testing.
// This separate implementation uses raw pointers to construct lists with cycles
// and to test cycle detection algorithms.

/// <summary>
/// Simple node structure for a raw-pointer linked list,
/// used to test cycle detection.
/// </summary>
struct TestNode {
    int value;
    TestNode* next;
    explicit TestNode(int v) : value(v), next(nullptr) {}
};

/// <summary>
/// Detects whether the linked list contains a cycle using the slow/fast pointer technique.
/// Time: O(n) | Space: O(1).
/// </summary>
/// <param name="head"> Pointer to the head of the list. </param>
/// <returns> True if a cycle is detected; otherwise, false. </returns>
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
/// Demonstrates cycle detection by creating a list,
/// testing it without a cycle, then introducing one.
/// </summary>
inline void testCycleDetection() {
    // Create test nodes with raw pointers
    TestNode* node1 = new TestNode(1);
    TestNode* node2 = new TestNode(2);
    TestNode* node3 = new TestNode(3);
    TestNode* node4 = new TestNode(4);

    // Link them linearly
    node1->next = node2;
    node2->next = node3;
    node3->next = node4;

    std::cout << "--- Cycle detection demo ---\n";
    std::cout << "No cycle: " << std::boolalpha << hasCycle(node1) << std::endl;

    // Introduce a cycle (node4 points back to node2)
    node4->next = node2;

    std::cout << "With cycle: " << std::boolalpha << hasCycle(node1) << std::endl;

    // Break the cycle before cleanup
    node4->next = nullptr;
    delete node1;
    delete node2;
    delete node3;
    delete node4;
}
