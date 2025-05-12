#include "main.hpp"

void setup() {
  nd.init(Logger);
  pixels.begin();
}

void loop() {
  if (Serial8.available() > 4) {
    if (nd.check_sync_byte()) {
      // Get data
      nd.read_data();

      // Yeet data
      if (position_fix_send.check()) {
        write_to_SD(vectornav_time, 3);
        write_to_SD(vectornav_position, 3);
      }

      if (imu_data_send.check()) {
        write_to_SD(vectornav_attitude, 3);
        write_to_SD(vectornav_gyro, 3);
        write_to_SD(vectornav_velocity, 3);
        write_to_SD(vectornav_accel, 3);
      }
    }
  }
}
