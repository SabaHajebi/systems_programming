#include "bitset.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

// create a new, empty bit vector set with a universe of 'size' items
struct bitset *bitset_new(int size)
{
    struct bitset *result = malloc(sizeof(struct bitset));
    float word_size = sizeof(uint64_t) * 8;
    int words = ceil(size / word_size);
    result->size_in_words = words;
    result->universe_size = size;
    result->bits = malloc(sizeof(uint64_t) * words);
    for (int i = 0; i < words; i++)
        result->bits[i] = 0;
    return result;
}

// get the size of the universe of items that could be stored in the set
int bitset_size(struct bitset *this)
{
    return this->universe_size;
}

// get the number of items that are stored in the set
int bitset_cardinality(struct bitset *this)
{
    int count = 0;
    for (int i = 0; i < bitset_size(this); i++)
    {
        if (this->bits[i] == 1)
        {
            count++;
        }
    }
}

// check to see if an item is in the set
int bitset_lookup(struct bitset *this, int item)
{
    int word_size = sizeof(uint64_t) * 8;
    int byte_number = item / word_size;
    uint64_t num = this->bits[byte_number];
    uint64_t mask = 1ul << item % word_size;;
    if ((num & mask) == 0)
        return 0;
    else
        return 1;
}

// add an item, with number 'item' to the set
// has no effect if the item is already in the set
void bitset_add(struct bitset *this, int item)
{
    int word_size = sizeof(uint64_t) * 8;
    int byte_number = item / word_size;
    uint64_t num = this->bits[byte_number];
    uint64_t mask = 1ul << item % word_size;;
    if ((num & mask) == 0)
        return;
    
    else 
        this -> bits[byte_number] = num | mask;
}

// remove an item with number 'item' from the set
void bitset_remove(struct bitset *this, int item)
{
    
    int word_size = sizeof(uint64_t) * 8;
    int byte_number = item / word_size;
    uint64_t num = this->bits[byte_number];
    uint64_t mask = 1ul << item % word_size;;
    if ((num & mask) == 0)
        return;
    
    else 
        this -> bits[byte_number] = num & (~mask);
}

// place the union of src1 and src2 into dest;
// all of src1, src2, and dest must have the same size universe
void bitset_union(struct bitset *dest, struct bitset *src1,
                  struct bitset *src2)
{
    for (int i = 0; i < dest->size_in_words; i++)
        dest->bits[i] = src1->bits[i] | src2->bits[i];
}

// place the intersection of src1 and src2 into dest
// all of src1, src2, and dest must have the same size universe
void bitset_intersect(struct bitset *dest, struct bitset *src1,
                      struct bitset *src2)
{
    for (int i = 0; i < dest->size_in_words; i++)
        dest->bits[i] = src1->bits[i] & src2->bits[i];
}
