#ifndef __RG_QUEUE_H
#define __RG_QUEUE_H
#include <list.h>
#include <stdint.h>
#include <sys/time.h>
#include <unistd.h>


/** 
 * Resource Group thread request queue entry.
 */
typedef struct __request {
	list_head();				/** Next/prev pointers */
	uint32_t	rr_request;		/** Request */
	char		rr_group[64];		/** Resource Group */
	uint32_t	rr_errorcode;		/** Error condition */
	uint32_t	rr_orig_request;	/** Original request */
	uint32_t	rr_resp_fd;		/** FD to send response */
	time_t		rr_when;		/** time to execute */
	uint64_t	rr_target;		/** Target node */
	uint32_t	rr_arg0;		/** Integer argument */
	uint32_t	rr_arg1;		/** Integer argument */
	char 		*rr_file;		/** Who made req */
	char		rr_line;		/** Line no */
} request_t;


int __rq_queue_request(request_t **queue, char *name, uint32_t request,
    		     uint32_t err, uint32_t oldreq, uint32_t fd, time_t when,
    		     uint64_t target, uint32_t arg0, uint32_t arg1, char *file,
		     int line);

#define rq_queue_request(queue, name, request, err, oldreq,\
			 fd, when, target, arg0, arg1) \
	__rq_queue_request(queue, name, request, err, oldreq, fd, when, \
			 target, arg0, arg1, __FILE__, __LINE__)

request_t *rq_next_request(request_t **q);
int rq_queue_empty(request_t **q);
void rq_free(request_t *foo);

void forward_request(request_t *req);

#endif
