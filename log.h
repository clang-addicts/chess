#ifndef __CHESS_LOG__
#define __CHESS_LOG__

#define PATH_LOG_DIR "C:\\\\log"

#ifndef LOG_EMERG
#define LOG_EMERG 0
#endif
#ifndef LOG_ALERT
#define LOG_ALERT 1
#endif
#ifndef LOG_CRIT
#define LOG_CRIT 2
#endif
#ifndef LOG_ERR
#define LOG_ERR 3
#endif
#ifndef LOG_WARNING
#define LOG_WARNING 4
#endif
#ifndef LOG_NOTICE
#define LOG_NOTICE 5
#endif
#ifndef LOG_INFO
#define LOG_INFO 6
#endif
#ifndef LOG_DEBUG
#define LOG_DEBUG 7
#endif

void log_general(int priority, char *str, ...);
#define log(pri, str, ...) log_general(pri, str, #__VA_ARGS__)

void log_debug(int priority, const char *function, int line, char *str, ...);
#define logd(pri, str, ...) log_debug(pri, __func__, __LINE__, str, #__VA_ARGS__)

void init_log();

#endif // __CHESS_LOG__