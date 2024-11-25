#include "lidardriver.hpp"

namespace lidar {

    /*********************************************************
     * LidarDriver class member functions
     *********************************************************/

    /**
     * Constructs the LidarDriver declaring the reading resolution
     * @param resolution The angle interval of the readings
     * @author Pietro Ballarin
     */
    LidarDriver::LidarDriver(double resolution) {
        this->stop = 0;
        this->start = 0;
        this->resolution = resolution;
        this->buffer = std::vector<std::vector<double>>();
        this->buffer.reserve(BUFFER_DIM);
        this->buffer.resize(BUFFER_DIM);
    }
    /**
     * Retrieves the oldest scan and removes it from the buffer
     * @author Diego Chiesurin
     */
    std::vector<double> LidarDriver::get_scan() {
        std::vector<double> res = this->buffer[start];
        this->start = (this->start + 1) % BUFFER_DIM;
        return res;
    }
    /**
     * Adds a new scan into the buffer, if full overwrites the oldest scan
     * @param scan The new scan to add to the buffer
     */
    void LidarDriver::new_scan(std::vector<double> scan) {

    }
    /**
     * Retrieves the distance of an object at a given angle
     * of the latest read.
     * @param angle The angle of the reading
     */
    double LidarDriver::get_distance(double angle) const {

    }

    /**
     * Removes all the readings from the buffer.
     */
    void LidarDriver::clear_buffer() {

    }

    /******************************************************************
     * LidarDriver class helper functions
     ******************************************************************/

    /**
     * Streams the content of the buffer
     */
    std::ostream& operator<<(std::ostream& os, LidarDriver& ld) {

    }
}

