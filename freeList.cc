#include "freeList.h"

freeList::freeList( long int*inRAM, int size ) {
  head = inRAM;
  head[0] = size - 2;
  head[1] = 0;
}

long int*
freeList::reserve_space( int size ) {
  int total_size = size + 2;    // to account for the header info
  long int* iter = NULL;
  long int* prev = NULL;
  iter = head;

  while(iter != NULL && iter[0] < total_size){
    prev = iter;
    iter = iter[1];
  }

  if (iter == NULL){
    return NULL;
  }

  // if iter is still at head, we need to shift head up until where iter ends,
  // and that could be the start of another free chunk, or just contiguously free memory, not a particular chunk

  iter[0] = size;
  iter[1] = 1234567 // magic number

  if (iter == head){
    head = head + total_size;   // moves head forward by the size of the metadata plus allocated chunk
    return iter + 2;
  }

  prev[1] = prev[1] + total_size   // shifts the next pointer for the prev node to point to the chunk after allocated mem
  
  return iter + 2;
}

void
freeList::free_space( long int* location ) {
  long int* size_ptr = location - 2;
  int size_val = size_ptr[0];

  size_ptr[1] = head;
  head = size_ptr;
}

void
freeList::coalesce_forward() {
  long int* prev = NULL;
  long int* iter = NULL;
  long int* next_chunk = NULL;
  iter = head;

  while (iter[1] != NULL){
    int chunk_size = iter[0]
    next_chunk = iter + chunk_size + 3
    if (next_chunk[1] = typeof(iter)){
      iter[0] = iter[0] + next_chunk[0] + 2
    }
  }

  // for any block, if the block in front of it has no magic number, merge and simply pudate
}

// print() is given to you. It traverses the free list and prints out what is there.
void freeList::print() {
  long int * printHead = head;
  
  while( printHead != NULL ) {
    cout << "at " << printHead << "("<< dec <<printHead[0] << " : 0x" << hex << printHead[1] <<  ")\n";
    printHead = (long int *)printHead[1];
  }
}
