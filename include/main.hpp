#include <Arduino.h>
#include <Metro.h>

#include <Adafruit_NeoPixel.h>
#include <logger.hpp>

#include "button.hpp"
#include "defs.hpp"
#include "vectornav.hpp"

// Vectornav setup
vNav nd(Serial2);

// User input setup
bool button1() { return bool(digitalRead(SW3)); }
bool button2() { return bool(digitalRead(SW4)); }

polButton a_button(300, &button1, true);
polButton b_button(300, &button2, true);

// User output setup
// Adafruit_NeoPixel pixels(NEOPIXEL_COUNT, NEOPIXEL_DIN, NEO_GRB + NEO_KHZ800);

// File saving
// class Logger track(teensy_microsd_numbered_log);
// class Logger points(teensy_microsd_numbered_log);
Metro flush_timer(500, true);
File track;
File points;
