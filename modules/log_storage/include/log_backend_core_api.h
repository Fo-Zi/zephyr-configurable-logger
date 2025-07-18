#ifndef LOG_BACKEND_H_
#define LOG_BACKEND_H_

#include <stddef.h>

#include "log_storage_types.h"
#include "log_backend_types.h"

typedef struct log_core_api_t{
    log_status_t (*init) (
        log_backend_cxt_t * backend_ctxt
    );

    log_status_t (*peek_entry)(
        log_backend_cxt_t * backend_ctxt,
        log_entry_t * entry
    );

    log_status_t (*pop_entry)(
        log_backend_cxt_t * backend_ctxt,
        log_entry_t * entry
    );

    log_status_t (*push_entry)(
        log_backend_cxt_t * backend_ctxt,
        log_entry_t * entry
    );

    log_status_t (*close)(
        log_backend_cxt_t * backend_ctxt
    );
}log_core_api_t;

#endif
