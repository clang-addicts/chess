#include <stdio.h>
#include <stdarg.h>

#include "log.h"

static const char* get_string_priority(int priority)
{
    switch(priority) {
        case LOG_EMERG:     return "emergency";
        case LOG_ALERT:     return "alert";
        case LOG_CRIT:      return "critical";
        case LOG_ERR:       return "error";
        case LOG_WARNING:   return "warning";
        case LOG_NOTICE:    return "notice";
        case LOG_INFO:      return "info";
        case LOG_DEBUG:     return "debug";
        default:            return "unknown";
    }
}

void log_general(int priority, char *fmt, ...)
{
    va_list vlist;
    const char *pri_str = get_string_priority(priority);
    char str[512]       = {0,};
    int pos             = 0;
    
    pos = snprintf(str, sizeof(str), "[%s] ", get_string_priority(priority));

    va_start(vlist, fmt);
    pos += vsnprintf(str+pos, sizeof(str)-pos, fmt, vlist);
    va_end(vlist);

    printf("%s\n", str);
}

void log_debug(int priority, const char *function, int line, char *fmt, ...)
{
    va_list vlist;
    const char *pri_str = get_string_priority(priority);
    char str[512]       = {0,};
    int pos             = 0;

    if(!function) {
        function = "unknown";
    }
    // TODO: need a function length checker (max:20?)
    
    pos = snprintf(str, sizeof(str), "[%s][%s():%d] ", function, line, get_string_priority(priority));

    va_start(vlist, fmt);
    pos += vsnprintf(str+pos, sizeof(str)-pos, fmt, vlist);
    va_end(vlist);

    printf("%s\n", str);
}