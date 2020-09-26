#include "hexpad.h"

bool is_keyboard_left(void) {
     // Test pin SPLIT_HAND_PIN for High/Low, if high it's right hand
     // (this is the opposite of regular SPLIT_HAND_PIN)
     setPinInput(SPLIT_HAND_PIN);
     return !readPin(SPLIT_HAND_PIN);
}
