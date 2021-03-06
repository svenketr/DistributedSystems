/**
 * Holder file for miscellaneous functions
 */
#include <errno.h>

#include "header.h"
#include "lspmessage.pb-c.h"


/** Utility Functions */
void Error(const char *str, ...)
{
	va_list ap;
	int e;

	e = errno;
	va_start(ap, str);
	vfprintf(stderr, str, ap);
	va_end(ap);
	fprintf( stderr, "\n" );
	if (e)
	{
		errno = e;
		perror("system error");
		fprintf( stderr, "errno %d\n", errno);
	}
	exit(1);
}

void pprint(LSPMessage& msg)
{
	printf("LSPMessage\n{connid: %d, seqnum: %d, payload.len: %u\n",
			msg.connid, msg.seqnum, msg.payload.len);

	printBytes(msg.payload.data, msg.payload.len);
	printf("}\n");
}

void printBytes(uint8_t* data, size_t len)
{
	printf("Data [%u bytes]: ", len);
	for(int i = 0; i < len; i++) printf("%2X ", data[i]);
	printf("\n");
}


