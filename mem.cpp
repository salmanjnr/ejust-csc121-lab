#include <iostream>
#include "mem.hpp"

Segment* allocate(Segment** head, unsigned int pid, unsigned int size) {
    Segment* current = *head;
    while (current != nullptr) {
        if (current->pid == -1 && current->size >= size) {
            break;
        }
        current = current->next;
    }
    if (current == nullptr) {
        return nullptr;
    }
    if (current->size == size) {
        current->pid = pid;
        return current;
    }
    Segment* newSegment = new Segment;
    newSegment->pid = pid;
    newSegment->start = current->start;
    newSegment->size = size;
    newSegment->prev = current->prev;
    newSegment->next = current;
    current->start += size;
    current->size -= size;
    if (current->prev != nullptr) {
        current->prev->next = newSegment;
    }
    current->prev = newSegment;
    if (*head == current) {
        *head = newSegment;
    }
    return newSegment;
}

 void deallocate(Segment* head, unsigned int pid) {
    Segment* de_alloc = head;
    while(head->next != nullptr) {
        if (head->pid == (int) pid )
         head->pid = -1;
        head = head ->next;
    }
    while (de_alloc->next != nullptr){
        while (de_alloc->pid == de_alloc->next->pid){
            de_alloc-> size+= de_alloc->next->size;
            de_alloc-> next = de_alloc->next->next;
        }
        de_alloc = de_alloc->next;
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
