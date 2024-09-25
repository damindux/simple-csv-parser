#pragma once

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>

auto split(const std::string& line) -> std::vector<std::string>;
auto parse_csv(const std::string& file_path) -> std::vector<std::vector<std::string>>;
auto calculate_column_widths(const std::vector<std::vector<std::string>>& csv_data) -> std::vector<size_t>;
auto format_csv(const std::vector<std::vector<std::string>>& csv_data) -> std::string;
auto markdown_export(const std::string& content, const std::string& file_name) -> void;