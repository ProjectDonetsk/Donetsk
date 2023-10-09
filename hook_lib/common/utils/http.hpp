#pragma once

#include <string>
#include <optional>
#include <future>

#pragma comment(lib, "Urlmon.lib")

namespace utils::http
{
	std::optional<std::string> get_data(const std::string& url);
	std::future<std::optional<std::string>> get_data_async(const std::string& url);
}
