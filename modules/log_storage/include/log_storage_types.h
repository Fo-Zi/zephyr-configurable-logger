#ifndef LOG_STORAGE_TYPES_H
#define LOG_STORAGE_TYPES_H

#include <stddef.h>
#include <stdint.h>

typedef enum log_status_t{
    LOG_STATUS_OK = 0,
    LOG_STATUS_TIMEOUT_ERR,
    

}log_status_t;

typedef enum log_section_t{
    LOG_SECTION_DATA,
    LOG_SECTION_EVENTS,
    LOG_SECTION_ERROR,
    LOG_SECTION_NUM_SECTIONS,
} log_section_t;

typedef struct log_entry_t{
    log_section_t section;
    uint32_t timestamp;
    uint8_t * data;
    size_t data_len_bytes;
}log_entry_t;

#endif
