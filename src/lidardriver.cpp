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
    LidarDriver::LidarDriver(const double resolution) : resolution{resolution} {
        this->buffer.reserve(BUFFER_DIM);
        this->buffer.resize(BUFFER_DIM);
    }

    /**
     * Constructs a LidarDriver by copy
     * @param ld The LidarDriver instance to copy
     * @author Diego Chiesurin
     */
    LidarDriver::LidarDriver(const LidarDriver& ld)
        : stop{ld.stop}, start{ld.stop}, resolution{ld.resolution}, buffer{ld.buffer} {}

    /**
     * Retrieves the oldest scan and removes it from the buffer
     * Throws "empty_lidar_driver" if the buffer is empty
     * @author Diego Chiesurin
     */
    std::vector<double> LidarDriver::get_scan() {
        if(this->stop == this->start) throw std::logic_error("LidarDriver's buffer is empty");
        std::vector<double> res = this->buffer[start];
        this->start = (this->start + 1) % BUFFER_DIM;
        return res;
    }
    /**
     * Adds a new scan into the buffer, if full overwrites the oldest scan
     * @param scan The new scan to add to the buffer
     * @author Pietro Ballarin
     */
    void LidarDriver::new_scan(std::vector<double>& scan) {
        scan.resize(180/resolution + 1, 0.0);
        if (this->stop == this->start) this->start = (this->start + 1) % BUFFER_DIM;
        this->buffer[this->stop] = scan;
        this->stop = (this->stop + 1) % BUFFER_DIM;
    }
    /**
     * Retrieves the distance of an object at a given angle
     * of the latest read.
     * Throws "empty_lidar_driver" if the buffer is empty
     * @param angle The angle of the reading
     * @author Pietro Ballarin
     */ 
    double LidarDriver::get_distance(const double angle) const {
        if(this->stop == this->start) throw std::logic_error("LidarDriver's buffer is empty");
        return this->buffer[this->start].at(angle * this->resolution);
    }

    /**
     * Removes all the readings from the buffer.
     * @author Elisa Chiarel
     */
    void LidarDriver::clear_buffer() {
        this->start = 0;
        this->stop = 0;
    }

    /**
     * Returns the last scan captured by the driver
     * Throws "empty_lidar_driver" if the buffer is empty
     * @returns The latest scan
     */
    std::vector<double> LidarDriver::get_latest(){
        if(this->stop == this->start) throw std::logic_error("LidarDriver's buffer is empty");
        return this->buffer[this->stop];
    }
    
    /******************************************************************
     * LidarDriver class helper functions
     ******************************************************************/

    /**
     * Streams the content of the buffer
     * @param os The output stream
     * @param ld The LidarDriver instance
     * @author Elisa Chiarel
     */
    std::ostream& operator<<(std::ostream& os, LidarDriver& ld) {
        std::vector<double> latest = ld.get_latest();
        for(int i=0; i<latest.size(); i++) {
            os << latest[i];
            if (i == latest.size()-1) {
                os << std::endl;
            } else {
                os << " ";
            }
        }
        return os;
    }
}