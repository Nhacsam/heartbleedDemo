/**
 * Some utils functions for the demo
 * @author Nhacsam
 */

#ifndef UTILS_H
#define UTILS_H

/**
 * Dump the memory at a given address
 * @param pointer Address of the memory to dump
 * @param length Number of bytes to dump
 */
void dump(void* pointer, const unsigned int length );

/**
 * allocate some memory space, to have something to see in the dump
 * @param i Number of recusive call 
 */
void dostuff( int i );


void RAND_pseudo_bytes(unsigned char *, unsigned int);


#endif 
