#ifndef LIDAR_LIDARDRIVER_HPP_
#define LIDAR_LIDARDRIVER_HPP_

#include <vector>
#include <ostream>

namespace lidar {
    // The maximum buffer dimension of the lidar driver
    constexpr int BUFFER_DIM = 10;

    /**
     * LidarDriver class used to manage the data of a lidar.
     * It uses an internal buffer managed by sliding window method.
     */
    class LidarDriver {
        private:
            int start;
            int stop;
            double resolution;
            std::vector<std::vector<double>> buffer;

        public:
            /**
             * Constructs the LidarDriver declaring the reading resolution
             * @param resolution The angle interval of the readings
             */
            LidarDriver(double resolution);
            /**
             * Retrieves the oldest scan and removes it from the buffer
             */
            std::vector<double> get_scan();
            /**
             * Adds a new scan into the buffer, if full overwrites the oldest scan
             * @param scan The new scan to add to the buffer
             */
            void new_scan(std::vector<double> scan);
            /**
             * Retrieves the distance of an object at a given angle 
             * of the latest read.
             * @param angle The angle of the reading
             */
            double get_distance(double angle) const;
            /**
             * Removes all the readings from the buffer.
             */
            void clear_buffer();
    };

    /**
     * Streams the content of the buffer
     */
    std::ostream &operator<<(std::ostream &os, LidarDriver &ld);
}

#endif