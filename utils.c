/**
 * Some utils functions for the demo
 * @author Nhacsam
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Dump the memory at a given address
 * @param pointer Address of the memory to dump
 * @param length Number of bytes to dump
 */

void dump(void *pointer, const unsigned int length) {
	unsigned char *buffer = (unsigned char *) pointer ;
	unsigned char byte;
	unsigned int i, j ;
	
	for( i =0; i<length; i++ ) {
		
		byte = buffer[i] ;
		printf( "%02x ", buffer[i] );
		
		if( ((i%16)==15) || (i == length-1 ) ) {
			
			for( j=0; j < 15 - (i%16); j++)
				printf("   ");
			printf("|  ");
			
			for( j=(i-(i%16)); j <= i; j++ ) {
				
				byte = buffer[j];
				if( (byte > 31) && (byte < 127) )
					printf( "%c", byte );
				else
					printf( "." );
			}
			printf( "\n" );
		}
	}
}



/**
 * allocate some memory space, to have something to see in the dump
 * @param i Number of recusive call 
 */
void dostuff( int i ) {
	
	if( i > 500 )
		return ;
	
	char *pass = "password=mypass" ;
	char *p ;
	int j ;
	
	for (j = 0; j < 40; j ++ ) {
		
		p = malloc( strlen(pass) + 1) ;
		memcpy( p, pass, strlen(pass) ) ;
		p[ strlen(pass) ] = (char) ((j+i) % 80) + 31 ;
		
		// memory leak to have something to show
		//free(p);
		
	}
	dostuff( i + 1 );
}



void RAND_pseudo_bytes(unsigned char *p, unsigned int l) {
	
	unsigned int i ;
	for ( i = 0; i < l; i++ ) {
		p[i] = 'A' ;
	}
	
}

