#include "k_means/DataLoader.hpp"

#include <cassert>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

int main() {
    const std::string filename = "kmeans_test_dataloader.csv";
    {
        std::ofstream out(filename);
        out << "number,name,quoted,other\n";
        out << "1.5,alpha,\"text, with comma\",3.5\n";
        out << "2.5,beta,plain,\n";
        out << "3.5,gamma,plain,5.5\n";
    }
    try {
        const auto selected = DataLoader::loadCSV(filename, {0, 3});
        assert(selected.size() == 3);
        assert(selected[0] == std::vector<double>({1.5, 3.5}));
        assert(std::isnan(selected[1][1]));
        assert(selected[2] == std::vector<double>({3.5, 5.5}));

        const auto all = DataLoader::loadCSV(filename);
        assert(all.size() == 3 && all[0].size() == 4);
        assert(std::isnan(all[0][1]) && std::isnan(all[0][2]));
        assert(std::isnan(all[1][3]));

        bool badColumn = false;
        try { (void)DataLoader::loadCSV(filename, {4}); }
        catch (const std::out_of_range&) { badColumn = true; }
        assert(badColumn);

        {
            std::ofstream out(filename, std::ios::trunc);
            out << "a,b\n1\n";
        }
        bool ragged = false;
        try { (void)DataLoader::loadCSV(filename); }
        catch (const std::invalid_argument&) { ragged = true; }
        assert(ragged);
    } catch (...) {
        std::remove(filename.c_str());
        throw;
    }
    std::remove(filename.c_str());
}
