#ifndef LOG_BACKEND_API_H
#define LOG_BACKEND_API_H

#include "log_backend_core_api.h"
#include "log_backend_iterable_api.h"

typedef struct log_backend_api_t{
    log_core_api_t * core;
    log_iterable_api_t * iterable;
}log_backend_api_t;

#endif
