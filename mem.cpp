#include <iostream>
#include "mem.hpp"

Segment* allocate(Segment** segHead, unsigned int pid, unsigned int size) {
    int remainingSize, start, totalMem = 50;
    
    Segment* current = *segHead;
while (current -> next != nullptr)
current = current->next;
 if (current->prev == nullptr) {
    current->start = 0;
    if((int) size > totalMem)
    return nullptr;
 }
else {
    if (size > current->size)
         return nullptr;
}
current->pid = pid;
current->size= size;

Segment* newSeg = new Segment;
current -> next = newSeg;
newSeg->next=nullptr;
newSeg->prev=current;

start = current->start + size;
remainingSize = totalMem - start;

newSeg->pid = -1;
newSeg -> start = start;
newSeg->size=remainingSize;
return *segHead;
}

void deallocate(Segment* segHead, unsigned int pid) {
    Segment* current = segHead;
    while(segHead->next != nullptr) {
        if (segHead->pid == (int) pid )
         segHead->pid = -1;
        segHead = segHead ->next;
    }
    while (current->next != nullptr){
        while (current->pid == current->next->pid){
            current->size+= current->next->size;
            current->next = current->next->next;
        }
        current = current->next;
    }
}

void dump(std::ostream& o, Segment* segHead) {
    while (segHead != nullptr) {
        o << "(" << ((segHead->pid == -1) ? "H" : std::to_string(segHead->pid)) << ", " << segHead->start << ", " << segHead->size << ") " << "--> ";
        segHead = segHead->next;
    }
    o << "NULL";
}

#ifndef GRADING IHJO
int main() {
    return 0;
}
#endif
