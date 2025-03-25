#include "enesmacros.h"
#include "enesfunctions.h"

void setup() {
    for (int i = 0; i < (sizeof(INPUT_PINS) / sizeof(int)); i++) {
        pinMode(INPUT_PINS[i],INPUT);
    }
    for (int i = 0; i < (sizeof(OUTPUT_PINS) / sizeof(int)); i++) {
        pinMode(OUTPUT_PINS[i],OUTPUT);
    }

}

void loop() {


}
