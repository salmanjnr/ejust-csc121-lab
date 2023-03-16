#include <iostream>
#include "mem.hpp"

Segment* allocate(Segment** head, unsigned int pid, unsigned int size) {
    int remainingSize, start, totalMem = 50;

    Segment* currentHead = *head;
    while (currentHead->next != nullptr)
        currentHead = currentHead->next;

    if (currentHead->prev == nullptr) {
        currentHead->start = 0;
        if((int) size > totalMem)
            return nullptr;
    }
    else {
        if (size > currentHead -> size)
            return nullptr;
    }

    currentHead->pid = pid;
    currentHead->size = size;

    Segment* newSegment = new Segment;
    currentHead->next = newSegment;
    newSegment->next = nullptr;
    newSegment->prev = currentHead;

    start = currentHead->start + size;
    remainingSize = totalMem - start;

    newSegment->pid = -1;
    newSegment -> start = start;
    newSegment->size = remainingSize;

    return *head;
}

void deallocate(Segment* head, unsigned int pid) {
    Segment* current = head;
    while(current->next != nullptr) {
        if (current->pid == (int) pid) 
            current->pid = -1;
        current = current->next;
    }

    while (head->next != nullptr){
        while (head->pid == head->next->pid){
            head->size += head->next->size;
            head->next = head->next->next;
        }
        head = head->next;
    }   
}

void dump(std::ostream& o, Segment* head) {
    while (head != nullptr) {
        o << "(" << ((head->pid == -1) ? "H" : std::to_string(head->pid)) << ", " << head->start << ", " << head->size << ") " << "--> ";
        head = head->next;
    }
    o << "NULL";
}

#ifndef GRADING IHJO
int main() {
    return 0;
}
#endif
