#include "lidardriver.hpp"
#include <ctime>
#include <iostream>

int main(void) {
    // Initializing the random number generator
    srand(time(NULL));
    // Initializing a LidarDriver
    constexpr double RESOLUTION = 1.0; 
    lidar::LidarDriver ld = lidar::LidarDriver(RESOLUTION);

    // Scan length generator
    int numberOfReadings = std::rand() % 180/RESOLUTION + 10;
    // Scan count
    int numberOfScans = std::rand() % 20 + 1;
    
    // Filling in the LidarDriver with new scans
    for(int i = 0; i < numberOfScans; i++){
        std::vector<double> scan;
        for(int j = 0; j < numberOfReadings; j++){
            scan.push_back(randDouble(0, 1));
        }
        ld.new_scan(scan);
    }
    
    // Popping the first scan in queue and printing its measures
    std::vector<double> oldest = ld.get_scan();
    for (int i = 0; i < oldest.size(); i++) {
        std::cout << oldest[i];
        if (i == oldest.size() - 1) { 
            std::cout << std::endl; 
        } else {
            std::cout << " ";
        } 
    }
    // Printing the distance at a random angle
    std::cout << ld.get_distance(randDouble(0, 1)) << std::endl;

    // Printing the latest scan
    std::cout << ld << std::endl;

    // Clearing the LidarDriver
    ld.clear_buffer();
    std::cout << ld << std::endl;

    return 0;
}

/**
 * generates a random double bounded by min and max
 * @param min, the lower bound
 * @param max, the upper bound
 * @return a random double between min and max
 */
double randDouble(double min, double max){
    double r = (double)rand() / RAND_MAX;
    return min + r * (max - min);
}