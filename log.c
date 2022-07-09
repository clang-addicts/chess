#include "log.h"

static FILE *fptr = NULL;

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

/*
static void write_to_file(char *str, size_t slen)
{
    FILE *fptr          = NULL;
    char file_name[32]  = {0};
    time_t mt           = time(NULL);
    struct tm mtms      = *localtime(&mt);

    snprintf(file_name, sizeof(file_name), PATH_LOG_DIR"\\%04d%02d%02d.log", 
    mtms.tm_year+1900, mtms.tm_mon+1, mtms.tm_mday);

    fptr = fopen(file_name, "a");
    if(!fptr) return;

    fputs(str, fptr);

    fclose(fptr);
}
*/

void log_general(int priority, char *fmt, ...)
{
    va_list vlist;
    const char *pri_str = get_string_priority(priority);
    char str[512]       = {0,};
    int pos             = 0;
    char file_name[32]  = {0};
    time_t mt           = time(NULL);
    struct tm mtms      = *localtime(&mt);

    if(!fptr) return;
    
    pos = snprintf(str, sizeof(str), "[%04d/%02d/%02d %02d:%02d:%02d][%s] ", 
        mtms.tm_year+1900, mtms.tm_mon+1, mtms.tm_mday,
        mtms.tm_hour, mtms.tm_min, mtms.tm_sec,
        get_string_priority(priority));

    va_start(vlist, fmt);
    pos += vsnprintf(str+pos, sizeof(str)-pos, fmt, vlist);
    va_end(vlist);

    str[pos]='\n';
    fputs(str, fptr);
    fflush(fptr);
    //write_to_file(str, sizeof(str));
}

void log_debug(int priority, const char *function, int line, char *fmt, ...)
{
    va_list vlist;
    const char *pri_str = get_string_priority(priority);
    char str[512]       = {0,};
    int pos             = 0;
    time_t mt           = time(NULL);
    struct tm mtms      = *localtime(&mt);

    if(!fptr) return;

    if(!function) {
        function = "unknown";
    }

    pos = snprintf(str, sizeof(str), "[%04d/%02d/%02d %02d:%02d:%02d][%s][%20s():%d] ",
        mtms.tm_year + 1900, mtms.tm_mon + 1, mtms.tm_mday,
        mtms.tm_hour, mtms.tm_min, mtms.tm_sec,
        get_string_priority(priority), function, line);

    va_start(vlist, fmt);
    pos += vsnprintf(str+pos, sizeof(str)-pos, fmt, vlist);
    va_end(vlist);

    str[pos]='\n';
    fputs(str, fptr);
    fflush(fptr);
    //write_to_file(str, sizeof(str));
}

void deinit_log()
{
    fclose(fptr);
}

void init_log()
{
    int error = 0;
    char file_name[32]  = {0};
    time_t mt           = time(NULL);
    struct tm mtms      = *localtime(&mt);

    if(!CreateDirectoryA(PATH_LOG_DIR, NULL)) {
        error = GetLastError();
        switch(error) {
            case ERROR_PATH_NOT_FOUND: {
                return;
            }
        }
    }
    
    snprintf(file_name, sizeof(file_name), PATH_LOG_DIR"\\%04d%02d%02d_%02d%02d%02d.log", 
        mtms.tm_year+1900,
        mtms.tm_mon+1,
        mtms.tm_mday,
        mtms.tm_hour,
        mtms.tm_min, 
        mtms.tm_sec);

    fptr = fopen(file_name, "a");
    if(!fptr) return;
}