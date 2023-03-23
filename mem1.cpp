#include <iostream>
#include "mem.hpp"

// Create constant to replace magic number in Segment constructor
const int MEMORY_SEGMENT_EMPTY = -1;

// Return the allocated segment. If no place found, return nullptr
Segment* allocate(Segment** head, unsigned int pid, unsigned int size) {
    Segment* curr = *head;
    Segment* new_seg = nullptr; // initialize new_seg 

    while(curr != nullptr) { // loop through all memory segments
        if(curr->pid == MEMORY_SEGMENT_EMPTY && curr->size >= size) { // if a hole is found
            // if the hole is exactly the size we want
            if(curr->size == size) {
                curr->pid = static_cast<int>(pid);
                return curr;
            }
            // if hole is larger than the required size, \
            split the segment
            new_seg = new Segment{static_cast<int>(pid), \
                                  curr->start, size,  curr};
            
            curr->prev = new_seg;
            curr->size -= size;
            curr->start = new_seg->start + new_seg->size;
            
            if(new_seg->prev) { // attach new segment to list
                new_seg->prev->next = new_seg;              
            } else {
                *head = new_seg;                
            }
            return new_seg;            
        }
        curr = curr->next;
    }   
    delete new_seg; // free memory if it exits after the loop
    return nullptr;
}

// Free all segments allocated to process
void deallocate(Segment* head, unsigned int pid) {
    Segment* curr = head;
    Segment* next = nullptr; // initialize pointer
    
    while(curr != nullptr) { // loop through all memory segments
        if(curr->pid == static_cast<int>(pid)) { // if segment belongs to process, free it
            curr->pid = MEMORY_SEGMENT_EMPTY;
            // merge with previous hole if adjacent and both are holes
            if(curr->prev && curr->prev->pid == MEMORY_SEGMENT_EMPTY) {
                curr->prev->size += curr->size;
                curr->prev->next = curr->next;
                if(curr->next) {
                    curr->next->prev = curr->prev;
                }
                next = curr->prev;
                delete curr;
                curr = next;
            }
            // merge with next hole if adjacent and both are holes
            else if(curr->next && curr->next->pid == MEMORY_SEGMENT_EMPTY) {
                curr->next->size += curr->size;
                curr->next->start -= curr->size;
                curr->next->prev = curr->prev;
                if(curr->prev) {
                    curr->prev->next = curr->next;
                } else {
                    head = curr->next;
                }
                next = curr->next;
                delete curr;
                curr = next;
            }
        } else {
            curr = curr->next;
        }
    }
}

// For debugging/testing
// You can use this to print a list as follow: \
dump(std::cout, list_head)
//
// DO NOT EDIT
void dump(std::ostream& o, Segment* head) {
    while (head != nullptr) {
        o << "(" << (( head->pid == MEMORY_SEGMENT_EMPTY ) ? "H" : "P") << ", " <<
        head->start << ", " << head->size << ") " << "--> ";
        head = head->next;
    }
    o << "NULL";
}

#ifndef GRADING // Don't delete

int main() {
    std::cout << "Initial memory state: ";
    Segment* memory = new Segment{MEMORY_SEGMENT_EMPTY, 0, 50, nullptr, nullptr}; // initialize memory with one segment representing empty space
    dump(std::cout, memory);
    std::cout << std::endl;

    std::cout << "Allocate 5 bytes for process 0: ";
    Segment* new_seg = allocate(&memory, 0, 5); // allocate memory for process 0
    if(new_seg) {
        dump(std::cout, memory);
        std::cout << std::endl;
    } else {
        std::cout << "Failed to allocate memory" << std::endl;
    }

    std::cout << "Allocate 3 bytes for process 0: ";
    new_seg = allocate(&memory, 0, 3); // allocate memory for process 0
    if(new_seg) {
        dump(std::cout, memory);
        std::cout << std::endl;
    } else {
        std::cout << "Failed to allocate memory" << std::endl;
    }

    std::cout << "Allocate 5 bytes for process 1: ";
    new_seg = allocate(&memory, 1, 5); // allocate memory for process 1
    if(new_seg) {
        dump(std::cout, memory);
        std::cout << std::endl;
    } else {
        std::cout << "Failed to allocate memory" << std::endl;
    }

    std::cout << "Allocate 10 bytes for process 0: ";
    new_seg = allocate(&memory, 0, 10); // allocate memory for process 0
    if(new_seg) {
        dump(std::cout, memory);
        std::cout << std::endl;
    } else {
        std::cout << "Failed to allocate memory" << std::endl;
    }

    std::cout << "Allocate 10 bytes for process 2: ";
    new_seg = allocate(&memory, 2, 10); // allocate memory for process 2
    if(new_seg) {
        dump(std::cout, memory);
        std::cout << std::endl;
    } else {
        std::cout << "Failed to allocate memory" << std::endl;
    }

    std::cout << "Deallocate memory for process 0: ";
    deallocate(memory, 0); // free memory belonging to process 0
    dump(std::cout, memory);
    std::cout << std::endl;

    std::cout << "Deallocate memory for process 1: ";
    deallocate(memory, 1); // free memory belonging to process 1
    dump(std::cout, memory);
    std::cout << std::endl;

    std::cout << "Deallocate memory for process 2: ";
    deallocate(memory, 2); // free memory belonging to process 2
    dump(std::cout, memory);
    std::cout << std::endl;
    delete memory; // free memory segment linked list

return 0;
}
#endif