#ifndef LOG_BACKEND_ITERABLE_API_H
#define LOG_BACKEND_ITERABLE_API_H

#include "log_backend_types.h"
#include "log_storage_types.h"

typedef struct log_iterable_api_t{

    log_iterator_t * (*begin)(
        log_backend_cxt_t * backend_ctxt
    );

    log_result_t (*next)(
        log_backend_cxt_t * backend_ctxt,
        log_iterator_t * iter,
        log_entry_t * entry
    );

    void (*end)(
        log_backend_cxt_t * backend_ctxt,
        log_iterator_t * iter
    );

}log_iterable_api_t;

#endif
