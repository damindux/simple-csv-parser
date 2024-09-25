#include "main.h"

auto split(const std::string& line) -> std::vector<std::string> {
    auto delimiter = ',';
    std::vector<std::string> result;
    std::stringstream ss(line);
    std::string item;

    while (getline(ss, item, delimiter)) {
        result.push_back(item);
    }

    return result;
}

auto parse_csv(const std::string& file_path) -> std::vector<std::vector<std::string>> {
    std::ifstream input_file(file_path);
    std::vector<std::vector<std::string>> csv_data;

    if (!input_file.is_open()) {
        std::cerr << "Error opening the file!\n";
        return csv_data;
    }

    std::string line;
    while(getline(input_file, line)) {
        csv_data.push_back(split(line));
    }

    input_file.close();
    return csv_data;
}

auto calculate_column_widths(const std::vector<std::vector<std::string>>& csv_data) -> std::vector<size_t> {
    if (csv_data.empty()) return {};

    std::vector<size_t> column_widths(csv_data[0].size(), 0);

    for (const auto& row : csv_data) {
        for (size_t col = 0; col < row.size(); ++col) {
            column_widths[col] = std::max(column_widths[col], row[col].size());
        }
    }

    return column_widths;
}

auto format_csv(const std::vector<std::vector<std::string>>& csv_data) -> std::string {
    if (csv_data.empty()) return "";

    auto column_widths = calculate_column_widths(csv_data);
    std::string result;

    auto add_row = [&](const std::vector<std::string>& row) {
        result += "| ";
        for (size_t col = 0; col < row.size(); ++col) {
            result += row[col] + std::string(column_widths[col] - row[col].size(), ' ') + " | ";
        }
        result += "\n";
    };

    // Header
    add_row(csv_data[0]);

    // Seperate Header and data
    result += "|";
    for (size_t col = 0; col < column_widths.size(); ++col) {
        result += " " + std::string(column_widths[col], '-') + " |";
    }
    result += "\n";

    // Data
    for (size_t row = 1; row < csv_data.size(); ++row) {
        add_row(csv_data[row]);
    }

    return result;
}

auto markdown_export(const std::string& content, const std::string& file_name) -> void {
    std::ofstream output_file(file_name);
    if (output_file.is_open()) {
        output_file << content;
        output_file.close();
        std::cout << "Markdown exported successfully to " << file_name << "\n";
    } else {
        std::cerr << "Error: Could not open file for writing.\n";
    }
}

auto main() -> int {
    std::string file_path;
    int choice;

    std::cout << "Enter CSV file path: ";
    std::cin >> file_path;

    auto file_content = parse_csv(file_path);
    auto result = format_csv(file_content);

    std::cout << result << "\n";

    std::cout << "Press 1 to export to Markdown or another key to exit: ";
    std::cin >> choice;
    if(choice == 1) {
        std::filesystem::path path_obj(file_path);
        std::string file_name = path_obj.stem().string() + ".md";
        markdown_export(result, file_name);
    }

    return 0;
}