#include <ostream>
#include "mem.hpp"


// Return the allocated segment. If no place found, return nullptr
Segment* allocate(Segment** head, unsigned int pid, unsigned int size) {
	return nullptr;
}

// Free all segments allocated to process
void deallocate(Segment* head, unsigned int pid) {
}

// For debugging/testing
// You can use this to print a list as follow: dump(std::cout, list_head)
//
// DO NOT EDIT
void dump(std::ostream& o, Segment* head) {
	while (head != nullptr) {
		o << "(" << (( head->pid == -1 )? "H":"P") << ", " << head->start << ", " << head->size << ") " << "--> ";
		head = head->next;
	}
	o << "NULL";
}

#ifndef GRADING // Don't delete

int main() {
	// You don't need to write anything here, but you can use it to try out your program

	return 0;
}

#endif // Don't delete
