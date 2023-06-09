// 可配置项（默认未定义）
// asio_net_LOG_NDEBUG               关闭asio_net_LOGD的输出
// asio_net_LOG_SHOW_VERBOSE         显示asio_net_LOGV的输出
// asio_net_LOG_DISABLE_COLOR        禁用颜色显示
// asio_net_LOG_LINE_END_CRLF        默认是\n结尾 添加此宏将以\r\n结尾
// asio_net_LOG_FOR_MCU              更适用于MCU环境
// asio_net_LOG_NOT_EXIT_ON_FATAL    FATAL默认退出程序 添加此宏将不退出
//
// c++11环境默认打开以下内容
// asio_net_LOG_ENABLE_THREAD_SAFE   线程安全
// asio_net_LOG_ENABLE_THREAD_ID     显示线程ID
// asio_net_LOG_ENABLE_DATE_TIME     显示日期
// 分别可通过下列禁用
// asio_net_LOG_DISABLE_THREAD_SAFE
// asio_net_LOG_DISABLE_THREAD_ID
// asio_net_LOG_DISABLE_DATE_TIME
//
// 其他配置项
// asio_net_LOG_PRINTF_IMPL          定义输出实现（默认使用printf）
// 并添加形如int asio_net_LOG_PRINTF_IMPL(const char *fmt, ...)的实现
//
// 在库中使用时
// 1. 修改此文件中的`asio_net_LOG`以包含库名前缀（全部替换即可）
// 2. 取消这行注释: #define asio_net_LOG_IN_LIB
// 库中可配置项
// asio_net_LOG_SHOW_DEBUG           开启asio_net_LOGD的输出
//
// 非库中使用时
// asio_net_LOGD的输出在debug时打开 release时关闭（依据NDEBUG宏）

#pragma once

// clang-format off

// 自定义配置
//#include "log_config.h"

// 在库中使用时需取消注释
#define asio_net_LOG_IN_LIB

#ifdef __cplusplus
#include <cstring>
#include <cstdlib>
#if __cplusplus >= 201103L

#if !defined(asio_net_LOG_DISABLE_THREAD_SAFE) && !defined(asio_net_LOG_ENABLE_THREAD_SAFE)
#define asio_net_LOG_ENABLE_THREAD_SAFE
#endif

#if !defined(asio_net_LOG_DISABLE_THREAD_ID) && !defined(asio_net_LOG_ENABLE_THREAD_ID)
#define asio_net_LOG_ENABLE_THREAD_ID
#endif

#if !defined(asio_net_LOG_DISABLE_DATE_TIME) && !defined(asio_net_LOG_ENABLE_DATE_TIME)
#define asio_net_LOG_ENABLE_DATE_TIME
#endif

#endif
#else
#include <string.h>
#include <stdlib.h>
#endif

#ifdef  asio_net_LOG_LINE_END_CRLF
#define asio_net_LOG_LINE_END            "\r\n"
#else
#define asio_net_LOG_LINE_END            "\n"
#endif

#ifdef asio_net_LOG_NOT_EXIT_ON_FATAL
#define asio_net_LOG_EXIT_PROGRAM()
#else
#ifdef asio_net_LOG_FOR_MCU
#define asio_net_LOG_EXIT_PROGRAM()      do{ for(;;); } while(0)
#else
#define asio_net_LOG_EXIT_PROGRAM()      exit(EXIT_FAILURE)
#endif
#endif

#define asio_net_LOG_BASE_FILENAME       (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

#define asio_net_LOG_WITH_COLOR

#if defined(_WIN32) || defined(__ANDROID__) || defined(asio_net_LOG_FOR_MCU)
#undef asio_net_LOG_WITH_COLOR
#endif

#ifdef asio_net_LOG_DISABLE_COLOR
#undef asio_net_LOG_WITH_COLOR
#endif

#ifdef asio_net_LOG_WITH_COLOR
#define asio_net_LOG_COLOR_RED           "\033[31m"
#define asio_net_LOG_COLOR_GREEN         "\033[32m"
#define asio_net_LOG_COLOR_YELLOW        "\033[33m"
#define asio_net_LOG_COLOR_BLUE          "\033[34m"
#define asio_net_LOG_COLOR_CARMINE       "\033[35m"
#define asio_net_LOG_COLOR_CYAN          "\033[36m"
#define asio_net_LOG_COLOR_DEFAULT
#define asio_net_LOG_COLOR_END           "\033[m"
#else
#define asio_net_LOG_COLOR_RED
#define asio_net_LOG_COLOR_GREEN
#define asio_net_LOG_COLOR_YELLOW
#define asio_net_LOG_COLOR_BLUE
#define asio_net_LOG_COLOR_CARMINE
#define asio_net_LOG_COLOR_CYAN
#define asio_net_LOG_COLOR_DEFAULT
#define asio_net_LOG_COLOR_END
#endif

#define asio_net_LOG_END                 asio_net_LOG_COLOR_END asio_net_LOG_LINE_END

#if __ANDROID__
#include <android/log.h>
#define asio_net_LOG_PRINTF(...)         __android_log_print(ANDROID_L##OG_DEBUG, "asio_net_LOG", __VA_ARGS__)
#else
#define asio_net_LOG_PRINTF(...)         printf(__VA_ARGS__)
#endif

#ifndef asio_net_LOG_PRINTF_IMPL
#ifdef __cplusplus
#include <cstdio>
#else
#include <stdio.h>
#endif

#ifdef asio_net_LOG_ENABLE_THREAD_SAFE
#include <mutex>
struct asio_net_LOG_Mutex {
static std::mutex& mutex() {
static std::mutex mutex;
return mutex;
}
};
#define asio_net_LOG_PRINTF_IMPL(...)    \
std::lock_guard<std::mutex> lock(asio_net_LOG_Mutex::mutex()); \
asio_net_LOG_PRINTF(__VA_ARGS__)
#else
#define asio_net_LOG_PRINTF_IMPL(...)    asio_net_LOG_PRINTF(__VA_ARGS__)
#endif

#else
extern int asio_net_LOG_PRINTF_IMPL(const char *fmt, ...);
#endif

#ifdef asio_net_LOG_ENABLE_THREAD_ID
#include <thread>
#include <sstream>
#include <string>
namespace asio_net_LOG {
inline std::string get_thread_id() {
std::stringstream ss;
ss << std::this_thread::get_id();
return ss.str();
}
}
#define asio_net_LOG_THREAD_LABEL "%s "
#define asio_net_LOG_THREAD_VALUE ,asio_net_LOG::get_thread_id().c_str()
#else
#define asio_net_LOG_THREAD_LABEL
#define asio_net_LOG_THREAD_VALUE
#endif

#ifdef asio_net_LOG_ENABLE_DATE_TIME
#include <sstream>
#include <iomanip>
namespace asio_net_LOG {
inline std::string get_time() {
auto now = std::chrono::system_clock::now();
std::time_t time = std::chrono::system_clock::to_time_t(now);
auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
std::stringstream ss;
ss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S") << '.' << std::setw(3) << std::setfill('0') << ms.count();
return ss.str();
}
}
#define asio_net_LOG_TIME_LABEL "%s "
#define asio_net_LOG_TIME_VALUE ,asio_net_LOG::get_time().c_str()
#else
#define asio_net_LOG_TIME_LABEL
#define asio_net_LOG_TIME_VALUE
#endif

#define asio_net_LOG(fmt, ...)           do{ asio_net_LOG_PRINTF_IMPL(asio_net_LOG_COLOR_GREEN   asio_net_LOG_TIME_LABEL asio_net_LOG_THREAD_LABEL "[*]: %s:%d "       fmt asio_net_LOG_END asio_net_LOG_TIME_VALUE asio_net_LOG_THREAD_VALUE, asio_net_LOG_BASE_FILENAME, __LINE__, ##__VA_ARGS__); } while(0)
#define asio_net_LOGT(tag, fmt, ...)     do{ asio_net_LOG_PRINTF_IMPL(asio_net_LOG_COLOR_BLUE    asio_net_LOG_TIME_LABEL asio_net_LOG_THREAD_LABEL "[" tag "]: %s:%d " fmt asio_net_LOG_END asio_net_LOG_TIME_VALUE asio_net_LOG_THREAD_VALUE, asio_net_LOG_BASE_FILENAME, __LINE__, ##__VA_ARGS__); } while(0)
#define asio_net_LOGI(fmt, ...)          do{ asio_net_LOG_PRINTF_IMPL(asio_net_LOG_COLOR_YELLOW  asio_net_LOG_TIME_LABEL asio_net_LOG_THREAD_LABEL "[I]: %s:%d "       fmt asio_net_LOG_END asio_net_LOG_TIME_VALUE asio_net_LOG_THREAD_VALUE, asio_net_LOG_BASE_FILENAME, __LINE__, ##__VA_ARGS__); } while(0)
#define asio_net_LOGW(fmt, ...)          do{ asio_net_LOG_PRINTF_IMPL(asio_net_LOG_COLOR_CARMINE asio_net_LOG_TIME_LABEL asio_net_LOG_THREAD_LABEL "[W]: %s:%d [%s] "  fmt asio_net_LOG_END asio_net_LOG_TIME_VALUE asio_net_LOG_THREAD_VALUE, asio_net_LOG_BASE_FILENAME, __LINE__, __func__, ##__VA_ARGS__); } while(0)                     // NOLINT(bugprone-lambda-function-name)
#define asio_net_LOGE(fmt, ...)          do{ asio_net_LOG_PRINTF_IMPL(asio_net_LOG_COLOR_RED     asio_net_LOG_TIME_LABEL asio_net_LOG_THREAD_LABEL "[E]: %s:%d [%s] "  fmt asio_net_LOG_END asio_net_LOG_TIME_VALUE asio_net_LOG_THREAD_VALUE, asio_net_LOG_BASE_FILENAME, __LINE__, __func__, ##__VA_ARGS__); } while(0)                     // NOLINT(bugprone-lambda-function-name)
#define asio_net_LOGF(fmt, ...)          do{ asio_net_LOG_PRINTF_IMPL(asio_net_LOG_COLOR_CYAN    asio_net_LOG_TIME_LABEL asio_net_LOG_THREAD_LABEL "[!]: %s:%d [%s] "  fmt asio_net_LOG_END asio_net_LOG_TIME_VALUE asio_net_LOG_THREAD_VALUE, asio_net_LOG_BASE_FILENAME, __LINE__, __func__, ##__VA_ARGS__); asio_net_LOG_EXIT_PROGRAM(); } while(0) // NOLINT(bugprone-lambda-function-name)

#if defined(asio_net_LOG_IN_LIB) && !defined(asio_net_LOG_SHOW_DEBUG) && !defined(asio_net_LOG_NDEBUG)
#define asio_net_LOG_NDEBUG
#endif

#if defined(NDEBUG) || defined(asio_net_LOG_NDEBUG)
#define asio_net_LOGD(fmt, ...)          ((void)0)
#else
#define asio_net_LOGD(fmt, ...)          do{ asio_net_LOG_PRINTF_IMPL(asio_net_LOG_COLOR_DEFAULT asio_net_LOG_TIME_LABEL asio_net_LOG_THREAD_LABEL "[D]: %s:%d "       fmt asio_net_LOG_END asio_net_LOG_TIME_VALUE asio_net_LOG_THREAD_VALUE, asio_net_LOG_BASE_FILENAME, __LINE__, ##__VA_ARGS__); } while(0)
#endif

#if defined(asio_net_LOG_SHOW_VERBOSE)
#define asio_net_LOGV(fmt, ...)          do{ asio_net_LOG_PRINTF_IMPL(asio_net_LOG_COLOR_DEFAULT "[V]: %s: "         fmt asio_net_LOG_END, asio_net_LOG_BASE_FILENAME, ##__VA_ARGS__); } while(0)
#else
#define asio_net_LOGV(fmt, ...)          ((void)0)
#endif
