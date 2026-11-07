// Implements CSV loading, including quoted-cell parsing, optional column selection,
// and conversion of invalid numeric cells to NaN for the preprocessing stage.
#include "k_means/DataLoader.hpp"

#include <cmath>
#include <cctype>
#include <fstream>
#include <limits>
#include <stdexcept>
#include <string>
#include <utility>

namespace {
// Split a one-line CSV record while retaining commas in quoted fields and
// decoding escaped quote pairs ("").
std::vector<std::string> parseCsvRow(const std::string& line) {
    std::vector<std::string> cells;
    std::string cell;
    bool quoted = false;
    for (std::size_t i = 0; i < line.size(); ++i) {
        const char ch = line[i];
        if (ch == '"') {
            if (quoted && i + 1 < line.size() && line[i + 1] == '"') {
                cell += '"';
                ++i;
            } else {
                quoted = !quoted;
            }
        } else if (ch == ',' && !quoted) {
            cells.push_back(cell);
            cell.clear();
        } else {
            cell += ch;
        }
    }
    if (quoted) throw std::invalid_argument("CSV row has an unterminated quote.");
    cells.push_back(cell);
    return cells;
}

double parseNumber(const std::string& text) {
    // Invalid, partially parsed, and non-finite cells become NaN so callers
    // can handle them deliberately during preprocessing.
    try {
        std::size_t consumed = 0;
        const double value = std::stod(text, &consumed);
        while (consumed < text.size() && std::isspace(static_cast<unsigned char>(text[consumed]))) ++consumed;
        if (consumed != text.size() || !std::isfinite(value)) return std::numeric_limits<double>::quiet_NaN();
        return value;
    } catch (const std::exception&) {
        return std::numeric_limits<double>::quiet_NaN();
    }
}
}

std::vector<std::vector<double>> DataLoader::loadCSV(
    const std::string& filename,
    const std::vector<std::size_t>& selectedColumns) {
    std::ifstream input(filename);
    if (!input) throw std::runtime_error("Could not open file: " + filename);

    std::string line;
    if (!std::getline(input, line)) throw std::invalid_argument("CSV file is empty.");
    const auto header = parseCsvRow(line);
    if (header.empty()) throw std::invalid_argument("CSV header is empty.");

    std::vector<std::size_t> columns = selectedColumns;
    if (columns.empty()) {
        // An empty selection means retain all fields in their original order.
        columns.resize(header.size());
        for (std::size_t i = 0; i < columns.size(); ++i) columns[i] = i;
    }
    for (const auto column : columns) {
        if (column >= header.size()) throw std::out_of_range("Selected CSV column is outside the header.");
    }

    std::vector<std::vector<double>> dataset;
    std::size_t lineNumber = 1;
    while (std::getline(input, line)) {
        ++lineNumber;
        if (line.empty()) continue;
        const auto cells = parseCsvRow(line);
        if (cells.size() != header.size()) {
            throw std::invalid_argument("CSV row " + std::to_string(lineNumber) + " has a different number of fields than the header.");
        }
        std::vector<double> row;
        row.reserve(columns.size());
        for (const auto column : columns) row.push_back(parseNumber(cells[column]));
        dataset.push_back(std::move(row));
    }
    return dataset;
}
