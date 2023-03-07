#include <ostream>
#include "mem.hpp"


// Return the allocated segment. If no place found, return nullptr
Segment* allocate(Segment** root, unsigned int pid, unsigned int size) {
	return nullptr;
}

// Free all segments allocated to process
void deallocate(Segment* root, unsigned int pid) {
}

// For debugging/testing
// You can use this to print a list as follow: dump(std::cout, list_head)
//
// DO NOT EDIT
void dump(std::ostream& o, Segment* root) {
	while (root != nullptr) {
		o << "(" << (( root->pid == -1 )? "H":"P") << ", " << root->start << ", " << root->size << ") " << "--> ";
		root = root->next;
	}
	o << "NULL";
}

#ifndef GRADING // Don't delete

int main() {
	// You don't need to write anything here, but you can use it to try out your program

	return 0;
}

#endif // Don't delete
