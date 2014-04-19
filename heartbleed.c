/**
 * This is a minimal code to explain to heartbleed bug
 * we will try to use some struct from the openssl code
 * and the RFC 6520
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heartbleed.h"
#include "utils.h"


#ifdef NEVER_DEFINED
 
/**
* Here the struct where is saved the information
* received from the client
*/
typedef struct ssl3_record_st {
	int type; /* type of record */
	unsigned int length; /* How many bytes available */
	/* Some useless stuff for the example */
	unsigned char *data; /* pointer to the record data */
	/* other useless stuff */
} SSL3_RECORD;

/**
 * Here the heartbeat struct from the RFC 6520
 * This is the request received from the client
 * we will not use this structure because we don't know the payload length
 * at the compilation.
 * copy/paste form RFC6520
 */
struct {
	HeartbeatMessageType type;							// the type of message, here : heartbeat_request 
	uint16 payload_length;								// the length of the payload 
	opaque payload[HeartbeatMessage.payload_length];	// The payload_length bytes of the payload 
	opaque padding[padding_length];						// Some random bytes : minimum : 16 bytes
} HeartbeatMessage;

// So we can define :
#define HB_TYPE_LEN 1
#define HB_PAYLOADLENGTH_LEN 2
#define HB_HEADER_LEN (HB_TYPE_LEN + HB_PAYLOADLENGTH_LEN)
#define HB_MINIMAL_PADDING_LEN 16


/**
 * Form RFC 6520 :
 * When a HeartbeatRequest message is received [...], 
 * the receiver MUST send a corresponding HeartbeatResponse
 * message carrying an exact copy of the payload of the received
 * HeartbeatRequest.
 */
#endif



/**
 * So let's try with the wrong method 
 */
SSL3_RECORD* vulnerableHearbeat( SSL3_RECORD *record ) {

	unsigned char *data = record->data ;	// received data
	unsigned char hbtype;					// heartbeat type 
	unsigned short int payloadLen;			// payload length
	unsigned int paddingLen = HB_MINIMAL_PADDING_LEN;
	
	// get the type and move data 1 byte forward
	hbtype = *data++;
	
	// get the payload length
	memcpy(&payloadLen, data, HB_PAYLOADLENGTH_LEN) ;
	// move data 2 byte forward
	data += HB_PAYLOADLENGTH_LEN ;
	
	// If we received a request
	if (hbtype == RFC6520_HEARTBEAT_REQUEST) {
	
		unsigned char *response, *responseBegin ;
		unsigned int hbGloabalLen = HB_HEADER_LEN + payloadLen + paddingLen ;
		
		// alocated the memory we need for the response message
		response = malloc( hbGloabalLen );
		responseBegin = response ;
		
		// Set the heartbeat type
		*response++ = RFC6520_HEARTBEAT_RESPONSE;
		
		// set the payload length
		memcpy(response, &payloadLen, HB_PAYLOADLENGTH_LEN) ;
		response += HB_PAYLOADLENGTH_LEN ;
		
		// copy the payload
		// The bug is here : We didn't check if payloadLen is
		// not > than record->length
		// in this case we copy more than just the payload given
		memcpy(response, data, payloadLen);
		response += payloadLen;
		
		// add the padding
		RAND_pseudo_bytes(response, paddingLen);
		
		// create de SSL3_RECORD response
		SSL3_RECORD* reccord = malloc( sizeof(SSL3_RECORD) ) ;
		reccord->data = responseBegin ;
		reccord->length = hbGloabalLen ;
		
		return reccord ;
		
	} else if (hbtype == RFC6520_HEARTBEAT_RESPONSE) {
		// DON'T CARE
	}
}




/**
 * Now without the bug !
 */
SSL3_RECORD* correctedHearbeat( SSL3_RECORD *record ) {

	unsigned char *data = record->data ;	// received data
	unsigned char hbtype;					// heartbeat type 
	unsigned short int payloadLen;			// payload length
	unsigned int paddingLen = HB_MINIMAL_PADDING_LEN;
	
	//////////////////////////////////////////////////////////////
	
	// Before doing any copy, we check that the receiced data is conform
	if ( (HB_HEADER_LEN + HB_MINIMAL_PADDING_LEN) > record->length )
		return NULL ;
	
	//////////////////////////////////////////////////////////////
	
	
	
	// get the type and move data 1 byte forward
	hbtype = *data++;
	
	// get the payload length
	memcpy(&payloadLen, data, HB_PAYLOADLENGTH_LEN) ;
	// move data 2 byte forward
	data += HB_PAYLOADLENGTH_LEN ;
	
	
	/////////////////////////////////////////////////////////////////
	
	// Check if the payloadLen is not greater than the received content
	// and if the given paddingLen > HB_MINIMAL_PADDING_LEN
	if ( (HB_HEADER_LEN + payloadLen + HB_MINIMAL_PADDING_LEN) > record->length )
		return NULL ;
	
	/////////////////////////////////////////////////////////////////
	
	
	// If we received a request
	if (hbtype == RFC6520_HEARTBEAT_REQUEST) {
	
		unsigned char *response, *responseBegin ;
		unsigned int hbGloabalLen = HB_HEADER_LEN + payloadLen + paddingLen ;
		
		// alocated the memory we need for the response message
		response = malloc( hbGloabalLen );
		responseBegin = response ;
		
		// Set the heartbeat type
		*response++ = RFC6520_HEARTBEAT_RESPONSE;
		
		// set the payload length
		memcpy(response, &payloadLen, HB_PAYLOADLENGTH_LEN) ;
		response += HB_PAYLOADLENGTH_LEN ;
		
		// copy the payload
		// The bug is here : We didn't check if payloadLen is
		// not > than record->length
		// in this case we copy more than just the payload given
		memcpy(response, data, payloadLen);
		response += payloadLen;
		
		// add the padding, we do not care here
		RAND_pseudo_bytes(response, paddingLen);
		
		SSL3_RECORD* reccord = malloc( sizeof(SSL3_RECORD) ) ;
		reccord->data = responseBegin ;
		reccord->length = hbGloabalLen ;
		
		return reccord ;
		
	} else if (hbtype == RFC6520_HEARTBEAT_RESPONSE) {
		// DON'T CARE
	}
}







