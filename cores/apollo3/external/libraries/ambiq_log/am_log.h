#ifndef AM_LOG_H__
#define AM_LOG_H__

#ifdef __cplusplus
extern "C"
{
#endif

#define RTT_LOG_ENABLED 1
#ifdef RTT_LOG_ENABLED

#include "SEGGER_RTT.h"

#define LOG_FLOAT_MARKER "%s%d.%03d"

/**
 * @brief Macro for dissecting a float number into two numbers (integer and residuum).
 */
#define LOG_FLOAT(val)                                                                                                 \
    (uint32_t)(((val) < 0 && (val) > -1.0) ? "-" : ""), (int32_t)(val),                                                \
        (int32_t)((((val) > 0) ? (val) - ((int32_t)(val)) : ((int32_t)(val)) - (val)) * 1000)

    // Function Declarations
    void rtt_log_general_print(int terminal, const char* color, const char* file, int line, const char* sFormat, ...);

    // LOG INIT
    void am_log_init(void);

#define HALO_SERIAL_LOGGER_ENABLED
#ifdef HALO_SERIAL_LOGGER_ENABLED

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

    // See log.cpp for implementation of these functions, they are used to forward logs to the serial logger if enabled
    void serialLoggerPrintfError(const char* format, ...);
    void serialLoggerPrintfWarning(const char* format, ...);
    void serialLoggerPrintfInfo(const char* format, ...);

#define am_log_err(...)                                                                                                \
    do                                                                                                                 \
    {                                                                                                                  \
        serialLoggerPrintfError("[ERROR] %s:%d: ", __FILENAME__, __LINE__);                                            \
        serialLoggerPrintfError(__VA_ARGS__);                                                                          \
        serialLoggerPrintfError("\r\n");                                                                               \
        rtt_log_general_print(0, RTT_CTRL_TEXT_BRIGHT_RED, __FILE__, __LINE__, __VA_ARGS__);                           \
    } while (0)
#define am_log_wrn(...)                                                                                                \
    do                                                                                                                 \
    {                                                                                                                  \
        serialLoggerPrintfWarning("[WARN] %s:%d: ", __FILENAME__, __LINE__);                                           \
        serialLoggerPrintfWarning(__VA_ARGS__);                                                                        \
        serialLoggerPrintfWarning("\r\n");                                                                             \
        rtt_log_general_print(0, RTT_CTRL_TEXT_BRIGHT_YELLOW, __FILE__, __LINE__, __VA_ARGS__);                        \
    } while (0)
#define am_log_inf(...)                                                                                                \
    do                                                                                                                 \
    {                                                                                                                  \
        serialLoggerPrintfInfo("[INFO] %s:%d: ", __FILENAME__, __LINE__);                                              \
        serialLoggerPrintfInfo(__VA_ARGS__);                                                                           \
        serialLoggerPrintfInfo("\r\n");                                                                                \
        rtt_log_general_print(0, RTT_CTRL_TEXT_BRIGHT_WHITE, __FILE__, __LINE__, __VA_ARGS__);                         \
    } while (0)

#else
// Log ERROR - Warning - Info
#define am_log_err(...) rtt_log_general_print(0, RTT_CTRL_TEXT_BRIGHT_RED, __FILE__, __LINE__, __VA_ARGS__)
#define am_log_wrn(...) rtt_log_general_print(0, RTT_CTRL_TEXT_BRIGHT_YELLOW, __FILE__, __LINE__, __VA_ARGS__)
#define am_log_inf(...) rtt_log_general_print(0, RTT_CTRL_TEXT_BRIGHT_WHITE, __FILE__, __LINE__, __VA_ARGS__)
#endif // HALO_SERIAL_LOGGER_ENABLED

#else

#define am_log_err(...)
#define am_log_wrn(...)
#define am_log_inf(...)
#define am_log_init()

#endif // RTT_LOG_ENABLED

#ifdef __cplusplus
}
#endif

#endif // AM_LOG_H__
