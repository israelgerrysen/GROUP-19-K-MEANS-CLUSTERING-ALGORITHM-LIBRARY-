#include "Distance_Calculation.hpp"
#include <cmath>
#include <stdexcept>

double calculateEuclideanDistance(const std::vector<double>& p1, const std::vector<double>& p2){
    if (p1.size() != p2.size()){
        throw std::invalid_argument("points must have the same number of dimensions");}
        double sumSq=0.0;
        for(size_t i=0; i<p1.size(); ++i){
            double diff = p1[i]-p2[i];
            sumSq += diff * diff;}
            return std::sqrt(sumSq);
    }
