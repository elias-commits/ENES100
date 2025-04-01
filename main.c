#include "enesfunctions.h"

void setup() {
    Serial.begin(9600);
    for (int i = 0; i < (sizeof(INPUT_PINS) / sizeof(int)); i++) {
        pinMode(INPUT_PINS[i],INPUT);
    }
    for (int i = 0; i < (sizeof(OUTPUT_PINS) / sizeof(int)); i++) {
        pinMode(OUTPUT_PINS[i],OUTPUT);
    }

}


void loop() {
    Serial.println("Forwards");
    drive_forwards(100);
    delay(1000);
    Serial.println("Backwards");
    drive_backwards(100);
    delay(1000);
}
