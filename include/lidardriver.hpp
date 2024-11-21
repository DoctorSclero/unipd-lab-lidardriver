#ifndef LIDAR_LIDARDRIVER_HPP_
#define LIDAR_LIDARDRIVER_HPP_

#include <vector>
#include <ostream>

namespace lidar {
    constexpr int BUFFER_DIM = 10;

    class LidarDriver {
        private:
            int start;
            int stop;
            double resolution;
            std::vector<std::vector<double>> buffer;

        public:
            LidarDriver(double resolution);
            std::vector<double> get_scan() const;
            void new_scan (std::vector<double> scan);
            double get_distance(double angle) const;
            void clear_buffer();
    };

    std::ostream &operator<<(std::ostream &os, LidarDriver &ld);
}

#endif