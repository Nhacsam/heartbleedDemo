/**
 * This is a minimal code to explain to heartbleed bug
 * we will try to use some struct from the openssl code
 * and the RFC 6520
 *
 * Main file !
 * Interresting code is in heartbleed.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heartbleed.h"
#include "utils.h"



/**
 * Main
 * Sorry I didn't make any user interface
 */
int main(int argc, char *argv[]) {
	
	
	// Payload to send
	char *payload = "Do or do not. There is no try !" ;
	
	// Paylaod length to send (not necesserely the right )
	unsigned short int  false_payload_length = 0xffff;
	
	// Padding length
	unsigned int padding_len = 16;
	
	
	
	
	
	
	// Get the rigth payload length
	unsigned short int payload_length = strlen( payload ) ;
	
	// Allocate memory for the request
	size_t dataLength = 1 + 2 + payload_length + padding_len ;
	unsigned char *data = malloc( dataLength );
	unsigned char *ptr = data ;
	
	SSL3_RECORD record ;
	
	// Copy the message 
	*ptr++ = RFC6520_HEARTBEAT_REQUEST ;
	
	memcpy(ptr, &false_payload_length, HB_PAYLOADLENGTH_LEN ) ;
	ptr +=  HB_PAYLOADLENGTH_LEN ;
	
	memcpy( ptr, payload, payload_length ) ;
	
	// Create the structure
	record.length = dataLength ;
	record.data = data ;
	
	// do stuff ^^
	dostuff( 0 ) ;
	
	
	printf("\n\n\n\nHearbeat Request : \n" );
	dump( record.data, record.length );
	
	
	SSL3_RECORD *r = vulnerableHearbeat( &record );
	
	
	
	printf( "\n\n\n\nVulnerable Hearbeat Response : \n" );
	if( r ) {
		dump( r->data, r->length );
		free( r->data ) ;
		free( r );
	} else {
		printf( "wrong request\n" );
	}
	
	
	printf( "\n\n\n\nCorrected Hearbeat Response : \n" );
	r = correctedHearbeat( &record );
	
	if( r != NULL ) {
		dump( r->data, r->length );
		free( r->data ) ;
		free( r );
	} else {
		printf( "wrong request\n" );
	}
	
	
	return 1 ;
}
