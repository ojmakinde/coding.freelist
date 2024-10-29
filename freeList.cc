#include "freeList.h"

freeList::freeList( long int*inRAM, int size ) {
  head = inRAM;
  head[0] = size - 2;
  head[1] = 0;
}

long int*
freeList::reserve_space( int size ) {
  int total_size = size + 2;    // to account for the header info
  long int* iter = head;
  long int* prev = NULL;
  long int* new_chunk = NULL;

  while(iter != NULL && iter[0] < total_size){
    prev = iter;
    iter = (long int*)iter[1];
  }

  if (iter == NULL){
    return NULL;
  }

  if (iter[0] > total_size){
    new_chunk = iter + total_size;
    new_chunk[0] = iter[0] - total_size;
    new_chunk[1] = iter[1];
    if (prev == NULL){
      head = new_chunk;
    } else {
      prev[1] = (long int)new_chunk;
    }
  } else {
    if (prev == NULL){
      head = (long int*)iter[1];
    } else {
      prev[1] = iter[1];
    }
  }

  iter[0] = size;
  iter[1] = 0;
  
  return iter + 2;
}

void
freeList::free_space( long int* location ) {
  long int* size_ptr = location - 2;
  size_ptr[1] = (long int)head;
  head = size_ptr;
}

void
freeList::coalesce_forward() {
  long int* iter = head;
  long int* next_chunk = NULL;
  long int* next_ptr = NULL;

  while (iter!= NULL && iter[1] != 0){
    next_ptr = (long int*)iter[1];
    next_chunk = iter + iter[0] + 2;     // checks the next immediate block if it is recently freed
    if (next_ptr == next_chunk){
      iter[0] += next_chunk[0] + 2;
      iter[1] = next_chunk[1];
    }
    iter = (long int*)iter[1];
  }
}

// print() is given to you. It traverses the free list and prints out what is there.
void freeList::print() {
  long int * printHead = head;
  
  while( printHead != NULL ) {
    cout << "at " << printHead << "("<< dec <<printHead[0] << " : 0x" << hex << printHead[1] <<  ")\n";
    printHead = (long int *)printHead[1];
  }
}
