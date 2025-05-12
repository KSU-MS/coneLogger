#pragma once

#include <stdint.h>

class polButton {
private:
  unsigned long time_pressed; // time sense first pressed
  float threshhold;           // time that needs to pass to count as pressed
  bool (*method)();           // The function to read the pin's state
  bool pull_down;             // If it goes from 1 to 0 or from 0 to 1

public:
  bool state;
  bool held;

  polButton(float time_req, bool (*read_method)(), bool is_pull_down) {
    threshhold = time_req;
    method = read_method;
    pull_down = is_pull_down;
  }

  void update(uint32_t millis) {
    if ((method() == 1 && !pull_down) || (method() == 0 && pull_down)) {
      if (time_pressed == 0) {
        time_pressed = millis;
      } else if (state) {
        held = true;
      } else {
        if (millis - time_pressed >= threshhold) {
          state = true;
          held = false;
        }
      }
    } else {
      state = false;
      held = false;
      time_pressed = 0;
    }
  }
};
