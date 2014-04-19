/**
 * This is bad way to make the includes
 * Just to have all the interresting code in a same file
 */

#ifndef HEARTBLEED_H
#define HEARTBLEED_H




/**
 * To be able to use the copy/paste form RFC 6520
 */
#define HB_TYPE_LEN 1
#define HB_PAYLOADLENGTH_LEN 2
#define HB_HEADER_LEN (HB_TYPE_LEN + HB_PAYLOADLENGTH_LEN)
#define HB_MINIMAL_PADDING_LEN 16
 
/**
 * Here the struct where is saved the information
 * received from the client
 * cp from openssl 
 */
typedef struct ssl3_record_st {
	int type; /* type of record */
	unsigned int length; /* How many bytes available */
	/* Some useless stuff for the example */
	unsigned char *data; /* pointer to the record data */
	/* other useless stuff */
} SSL3_RECORD;


/**
 * HeartbeatMessageType
 */
typedef enum {
	RFC6520_HEARTBEAT_REQUEST = 1,
	RFC6520_HEARTBEAT_RESPONSE = 2
} HeartbeatMessageType ;


SSL3_RECORD* vulnerableHearbeat( SSL3_RECORD *record ) ;
SSL3_RECORD* correctedHearbeat( SSL3_RECORD *record );


#endif
