#include "enesfunctions.h"

void setup() {
    Serial.begin(9600);
    for (int i = 0; i < (sizeof(INPUT_PINS) / sizeof(int)); i++) {
        pinMode(INPUT_PINS[i],INPUT);
    }
    for (int i = 0; i < (sizeof(OUTPUT_PINS) / sizeof(int)); i++) {
        pinMode(OUTPUT_PINS[i],OUTPUT);
    }

    drive_left(100);

}


void loop() {
  struct RGB rgb = read_rgb();
  Serial.println(rgb.r);
  Serial.println(rgb.g);
  Serial.println(rgb.b);
  Serial.println("- - - - - ");
  delay(1000);

}
