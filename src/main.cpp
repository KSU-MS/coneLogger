#include "main.hpp"

void setup() {
  Serial.begin(9600);
  Serial.println("init");

  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(SW3, INPUT_PULLUP);
  pinMode(SW4, INPUT_PULLUP);

  nd.init(Logger);

  // Wait for SD stuffs
  delay(500);
  if (!SD.begin(BUILTIN_SDCARD)) { // Begin Arduino SD API
    Serial.println("SD card failed or not present");
  }
  delay(500);

  // TODO: Make this not look braindead
  char filename[] = "GPS_0000.CSV";
  for (uint16_t i = 0; i < 10000; i++) {
    filename[4] = i / 1000 + '0';
    filename[5] = i / 100 % 10 + '0';
    filename[6] = i / 10 % 10 + '0';
    filename[7] = i % 10 + '0';
    if (!SD.exists(filename)) { // Create and open file
      track = SD.open(filename, (uint8_t)O_WRITE | (uint8_t)O_CREAT);
      break;
    }
    if (i == 9999) { // Print if it cant
      Serial.println("Ran out of names, clear SD");
    }
  }

  char filename2[] = "PPS_0000.CSV";
  for (uint16_t i = 0; i < 10000; i++) {
    filename2[4] = i / 1000 + '0';
    filename2[5] = i / 100 % 10 + '0';
    filename2[6] = i / 10 % 10 + '0';
    filename2[7] = i % 10 + '0';
    if (!SD.exists(filename2)) { // Create and open file
      points = SD.open(filename2, (uint8_t)O_WRITE | (uint8_t)O_CREAT);
      break;
    }
    if (i == 9999) { // Print if it cant
      Serial.println("Ran out of names, clear SD");
    }
  }

  // Print guide at top of CSV
  track.println("latitude, longitude");
  track.flush();

  // Print another guide
  points.println("latitude, longitude");
  points.flush();
}

void loop() {
  digitalToggle(LED_BUILTIN);

  a_button.update(millis());

  // Get data
  if (Serial2.available() > 4) {
    if (nd.check_sync_byte()) {
      nd.read_data();

      track.print(String(nd.position.latitude) + ",");
      track.println(String(nd.position.longitude));
    }
  }

  if (a_button.state == true && a_button.held == false) {
    Serial.println("logging point");

    points.print(String(nd.position.latitude) + ",");
    points.println(String(nd.position.longitude));
  }

  if (flush_timer.check()) {
    track.flush();
    points.flush();
  }
}
