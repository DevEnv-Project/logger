/*
    DevEnv-Project/Logger
      A simple single-file C++ logger

    Author(s): MrBisquit, DevEnv-Project
    File name: logger_basic.hpp
    Original:  https://github.com/DevEnv-Project/logger/blob/master/src/logger_basic.hpp
*/

/// @brief Logger
namespace Logger {
    #include <stdio.h>
    #include <stdarg.h>
    #include <malloc.h>
    #include <string.h>
    #include <ctime>

    /// @brief The log level
    typedef enum Level {
        LOG_INFO    = 1 << 0,
        LOG_ERROR   = 1 << 1,
        LOG_WARN    = 1 << 2,
        LOG_FATAL   = 1 << 3
    } Level;

    /// @brief The level text
    const char* levels_text[4] = {
        "INFO",
        "ERROR",
        "WARN",
        "FATAL"
    };

    /// @brief Adds spaces onto the end of a string
    /// @param dest The destination pointer
    /// @param spaces The number of spaces to add to the end
    /// @note Originally from https://stackoverflow.com/a/21855898
    void __add_spaces(char* dest, int spaces) {
        int len = strlen(dest);
        memset(dest + len, ' ', spaces);
        dest[len + spaces] = '\0';
    }

    /// @brief Pads the right of a string by a number of spaces
    /// @param text The original text
    /// @param length The full length of the string
    /// @param ptr The string pointer
    void __pad_right_ptr(const char* text, int length, char* ptr) {
        int len = length - strlen(text);
        strcpy(ptr, text);
        __add_spaces(ptr, len);
    }

    /// @brief Gets the log level text from the log level
    /// @param level The log level
    /// @return The log level text
    const char* __get_levels_text(Level level) {
        switch(level) {
            case Level::LOG_INFO:
                return levels_text[0];
                break;
            case Level::LOG_ERROR:
                return levels_text[1];
                break;
            case Level::LOG_WARN:
                return levels_text[2];
                break;
            case Level::LOG_FATAL:
                return levels_text[3];
                break;
        }
    }

    /// @brief Log
    /// @param level The log level
    /// @param format The formatted log string
    void Log(Level level, const char* format, ...) {
        va_list args;
        va_start(args, format);
        int size = _vscprintf(format, args) + 1;
        va_end(args);

        char* buffer = (char*)malloc(size);

        va_start(args, format);
        vsnprintf(buffer, size, format, args);
        va_end(args);

        time_t timestamp;
        time(&timestamp);

        struct tm* time_info = localtime(&timestamp);

        char time[100];
        strftime(time, sizeof(time), "%Y-%m-%d %H:%M:%S", time_info);

        const char* _level = __get_levels_text(level);
        char padded_level[5];
        strcpy(padded_level, _level);
        __pad_right_ptr(_level, 5, padded_level);

        fprintf(stdout, "%s: %s", padded_level, buffer);

        free(buffer);
    }
}