#include "lidardriver.h"

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
     * @throws logic_error If the buffer is empty
     * @author Diego Chiesurin
     */
    std::vector<double> LidarDriver::get_scan() {
        if(this->empty()) throw std::logic_error("LidarDriver's buffer is empty");
        std::vector<double> res = this->buffer[this->start];
        this->start = (this->start + 1) % BUFFER_DIM;
        return res;
    }
    /**
     * Adds a new scan into the buffer, if full overwrites the oldest scan
     * @param scan The new scan to add to the buffer
     * @author Pietro Ballarin
     */
    void LidarDriver::new_scan(std::vector<double>& scan) {
        // Padding/Cropping the buffer according to the excpected number of readings
        scan.resize(180/resolution + 1, 0.0);
        // Overwriting the last element if queue is full
        if ((this->stop+1)%BUFFER_DIM == this->start) this->start = (this->start + 1) % BUFFER_DIM;
        this->buffer[this->stop] = scan;
        this->stop = (this->stop + 1) % BUFFER_DIM;
    }
    /**
     * Retrieves the distance of an object at a given angle
     * of the latest read.
     * @throws logic_error If the buffer is empty
     * @param angle The angle of the reading
     * @author Pietro Ballarin
     */ 
    double LidarDriver::get_distance(const double angle) const {
        if(this->empty()) throw std::logic_error("LidarDriver's buffer is empty"); 
        return this->buffer[this->start].at((int)(angle/this->resolution));
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
     * @throws logic_error If the buffer is empty
     * @author Elisa Chiarel
     * @returns The latest scan
     */
    std::vector<double> LidarDriver::get_latest() const {
        if(this->empty()) throw std::logic_error("LidarDriver's buffer is empty");
        return this->buffer[(this->stop-1)%BUFFER_DIM];
    }

    /**
     * Checks whether the container is empty or not
     * @author Diego Chiesurin
     * @return true if the container's empty
     */
    bool LidarDriver::empty() const {
        return this->start == this->stop;
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
            if (i != latest.size()-1) {
                os << " ";
            }
        }
        return os;
    }
}