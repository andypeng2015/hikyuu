/*
 * Log.cpp
 *
 *  Created on: 2013-2-1
 *      Author: fasiondog
 */

#include <iostream>
#include "Log.h"
#include <spdlog/sinks/stdout_color_sinks.h>
//#include "spdlog/sinks/ostream_sink.h"
//#include "spdlog/sinks/rotating_file_sink.h"

namespace hku {

static LOG_LEVEL g_log_level = TRACE;

LOG_LEVEL get_log_level() {
    return g_log_level;
}

void set_log_level(LOG_LEVEL level) {
    g_log_level = level;
    spdlog::get("hikyuu")->set_level((spdlog::level::level_enum)level);
}

/**********************************************
 * Use SPDLOG for logging
 *********************************************/
void init_logger(const std::string& configure_name) {
    //auto stdout_sink = std::make_shared<spdlog::sinks::ostream_sink_mt>(std::cout, true);
    auto stdout_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    stdout_sink->set_level(spdlog::level::trace);

    auto logger = std::shared_ptr<spdlog::logger>(
            //new spdlog::logger("hikyuu", {stdout_sink, file_sink}));
            new spdlog::logger("hikyuu", stdout_sink));
    logger->set_level(spdlog::level::trace);
    logger->flush_on(spdlog::level::trace);
    //logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] %v [%!]");
    logger->set_pattern("%Y-%m-%d %H:%M:%S.%e [%^HKU-%L%$] - %v [%!]");
    spdlog::details::registry::instance().register_logger(logger);
}

} /* namespace hku */
