#include "lidardriver.h"
#include <ctime>
#include <iostream>

/**
 * Generates a random double bounded by min and max
 * @param min the lower bound
 * @param max the upper bound
 * @return a random double between min and max
 * @author Diego Chiesurin
 */
double rand_double(double min, double max);
/**
 * Generates a random integer bounded by min and max
 * @param min the lower bound
 * @param max the upper bound
 * @returns A random integer between min and max
 * @author Pietro Ballarin
 */
int rand_int(int min, int max);

/**
 * Tests the new_scan function of a LidarDriver
 * @param ld The LidarDriver to test
 * @param scan_count The number of mock scans to add into the driver
 * @param reading_count The number of mock distances to add into each scan
 * @author Pietro Ballarin
 */
void test_new_scan(lidar::LidarDriver& ld, int scan_count, int reading_count);
/**
 * Tests the get_scan function of a LidarDriver
 * @param ld The LidarDriver to test
 * @author Diego Chiesurin
 */
void test_get_scan(lidar::LidarDriver& ld);
/**
 * Tests the get_distance function of a LidarDriver
 * @param ld The LidarDriver to test
 * @param angle The angle to retrieve the distance from
 * @author Pietro Ballarin
 */
void test_get_distance(lidar::LidarDriver& ld, double angle);
/**
 * Tests the operator << of a LidarDriver
 * @param ld The LidarDriver to test
 * @author Elisa Chiarel
 */
void test_stream_operator(lidar::LidarDriver& ld);
/**
 * Tests the clear_buffer function of a LidarDriver
 * @param ld The LidarDriver to test
 * @author Elisa Chiarel
 */
void test_clear_buffer(lidar::LidarDriver& ld);

/**
 * @author Pietro Ballarin, Diego Chiesurin
 */
int main(void) {
    constexpr int TEST_COUNT = 100;

    // Initializing the random number generator
    srand(time(NULL));

    int error_count = 0;
    for (int i = 0; i < TEST_COUNT; i++) {
        try {
            double driver_resolution = rand_double(10.0, 30.0);
            int reading_count = rand_int(1, (180/driver_resolution)+1);
            int scan_count = rand_int(1, 20);
            double angle = rand_double(0.0, 5.0);
            std::cout << "Resolution: " << driver_resolution << std::endl;
            std::cout << "Expected reading count: " << (int)(180/driver_resolution) << std::endl;
            std::cout << "Actual reading count: " << reading_count <<std::endl;
            std::cout << "Scan count: " << scan_count << std::endl;
            lidar::LidarDriver ld = lidar::LidarDriver(driver_resolution);

            test_new_scan(ld, scan_count, reading_count);
            test_get_scan(ld);
            test_get_distance(ld, angle);
            test_stream_operator(ld);
            test_clear_buffer(ld);
            std::cout << std::endl << std::endl;
        } catch (...) {
            error_count++;
        }
    }
    std::cout << "Execution terminated with " << error_count << " errors" << std::endl;
    return 0;
}

double rand_double(double min, double max){
    double r = (double)rand() / RAND_MAX;
    return min + r * (max - min);
}

int rand_int(int min, int max) {
    return rand() % (max-min) + min;
}

void test_new_scan(lidar::LidarDriver& ld, int scan_count, int reading_count) {
    std::cout << "Generating " << scan_count << " scans and inserting them..." << std::endl;
    for(int i = 0; i < scan_count; i++){
        std::vector<double> scan;
        for(int j = 0; j < reading_count; j++){
            scan.push_back(rand_double(0, 1));
        }
        std::cout << "Inserted scan #" << i << " with " << reading_count << " readings" << std::endl;
        ld.new_scan(scan);
    }
    std::cout << "Scans generated and inserted!" << std::endl;
}
void test_get_scan(lidar::LidarDriver& ld) {
    std::cout << "Printing the first scan content..." << std::endl;
    std::vector<double> oldest = ld.get_scan();
    for (int i = 0; i < oldest.size(); i++) {
        std::cout << oldest[i];
        if (i == oldest.size() - 1) { 
            std::cout << std::endl; 
        } else {
            std::cout << " ";
        } 
    }
    ld.new_scan(oldest);
    std::cout << "Finished printing!" << std::endl;
    
}
void test_get_distance(lidar::LidarDriver& ld, double angle) {
    std::cout << "Printing the distance at a random angle..." << std::endl;
    std::cout << "Angle: " << angle << ", Distance: " << ld.get_distance(angle) << std::endl;
    std::cout << "Finished printing!" << std::endl;
    
}
void test_stream_operator(lidar::LidarDriver& ld) {
    std::cout << "Printing the latest scan..." << std::endl;
    std::cout << ld << std::endl;
    std::cout << "Finished printing!" << std::endl;
}
void test_clear_buffer(lidar::LidarDriver& ld) {
    std::cout << "Clearing the buffer..." << std::endl;
    ld.clear_buffer();
    std::cout << "Buffer cleared!" << std::endl;
}