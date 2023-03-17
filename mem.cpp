#include <ostream>
#include <iostream>
#include "mem.hpp"
using namespace std;


// Return the allocated segment. If no place found, return nullptr
Segment* allocate(Segment** head, unsigned int pid, unsigned int size) {
    int remain_size, start, whole_mem = 50;

    Segment* First_head = *head;
    while (First_head ->next != nullptr)
        First_head = First_head ->next;

    if (First_head ->prev == nullptr) {
        First_head ->start = 0;
        if ((int)size > whole_mem)
            return nullptr;
    }
    else {
        if (size > First_head ->size)
            return nullptr;
    }
    First_head ->pid = pid;
    First_head ->size = size;

    Segment* newtemp = new Segment;
    First_head ->next = newtemp;
    newtemp->next = nullptr;
    newtemp->prev = First_head;

    start = First_head ->start + size;
    remain_size = whole_mem - start;

    newtemp->pid = -1;
    newtemp->start = start;
    newtemp->size = remain_size;

    return newtemp;
}

// Free all segments allocated to process
void deallocate(Segment* head, unsigned int pid) {
    Segment* Deallo = head;
    while (Deallo->next != nullptr) {
        if (Deallo ->pid == (int)pid)
            Deallo ->pid = -1;
        Deallo = Deallo ->next;

    }
    Deallo = head;
    while (Deallo ->next != nullptr) {
        while (Deallo ->pid == Deallo ->next->pid) {
            Deallo ->size += Deallo ->next->size;
            Deallo ->next = Deallo ->next->next;
        }
        Deallo = Deallo ->next;

    }
}

// For debugging/testing
// You can use this to print a list as follow: dump(std::cout, list_head)
//
// DO NOT EDIT
void dump(std::ostream& o, Segment* head) {
    while (head != nullptr) {
        o << "(" << ((head->pid == -1) ? "H" : "P") << ", " << head->start << ", " << head->size << ") " << "--> ";
        head = head->next;
    }
    o << "NULL";
}

#ifndef GRADING // Don't delete

int main() {

    return 0;
}

#endif // Don't delete