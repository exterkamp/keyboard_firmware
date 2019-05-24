/*
 * Written by Shane Exterkamp in 2019.
 * 
 * This is firmware for the 2x2 Code keyboard.  It assigns the keys
 * to 1-4 and activates the onboard teensy 2 LED on key down.
 * 
 * Inspired by Stefan Jakobsson, 2019.
 * https://forum.pjrc.com/threads/55395-Keyboard-simple-firmware
 */

#include <Bounce.h>

#define ROW_COUNT 2
#define COL_COUNT 2
#define DEBOUNCE 10
#define SCAN_DELAY 5

int colPins[] = {0,1};
int rowPins[] = {2,3};

unsigned int keys[] = {KEY_1, KEY_2, KEY_3, KEY_4};

int currentRow = 0;
int keyStatus[ROW_COUNT * COL_COUNT];

// Create Bounce objects for each button.  The Bounce object
// automatically deals with contact chatter or "bounce", and
// it makes detecting changes very simple.
Bounce button0 = Bounce(0, DEBOUNCE);
Bounce button1 = Bounce(1, DEBOUNCE);  // 10 = 10 ms debounce time
Bounce button2 = Bounce(2, DEBOUNCE);  // which is appropriate for
Bounce button3 = Bounce(3, DEBOUNCE);  // most mechanical pushbuttons

const int led = LED_BUILTIN;
const bool led_on = false;

void setup() {
  // Column Pins
  pinMode(0, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP);

  // Row Pins
  pinMode(2, INPUT);
  pinMode(3, INPUT);

  // LED
  pinMode(led, OUTPUT);
}

void loop() {
  scanKeys();
  delay(SCAN_DELAY);
}

/*
 * Scan keyboard matrix, results stored in keyStatus array
 * 
 * Key status values:
 * DEBOUNCE*2                   = key press event
 * DEBOUNCE+1 to DEBOUNCE*2-1   = key down
 * DEBOUNCE                     = key release event
 * 0 to DEBOUNCE-1              = key up
*/
void scanKeys(){
  int i;
  bool led_on = false;
  for (i=0;i<ROW_COUNT*COL_COUNT;i++){
    int pin = getKeyPin(i);
    
    if (keyStatus[i]==0 && digitalRead(pin)==LOW){
      //Key press event
      keyStatus[i] = DEBOUNCE*2;
      // digitalWrite(led, HIGH);
      Keyboard.press(keys[i]);
    }
    else if (keyStatus[i]>DEBOUNCE+1){
      keyStatus[i]--;
    }
    else if (keyStatus[i]==DEBOUNCE+1 && digitalRead(pin)==HIGH){
      //Key release event
      keyStatus[i]--;
      Keyboard.release(keys[i]);
      //digitalWrite(led, LOW);
    }
    else if (keyStatus[i]>0 && keyStatus[i]<=DEBOUNCE){
      keyStatus[i]--;
    }
    
    if (keyStatus[i] > DEBOUNCE) {
      led_on = true;
      digitalWrite(led, HIGH);
    }
    if (!led_on) {
      digitalWrite(led, LOW);
    }
  }

}

/*
 * Returns input pin to be read by keyScan method
 * 
 * Param key is the keyboard matrix scan code (row * COL_COUNT + col)
 */
int getKeyPin(int key){
  int p = key/COL_COUNT;
  if (p != currentRow){
    pinMode(rowPins[currentRow], INPUT);
    pinMode(rowPins[p], OUTPUT);
    digitalWrite(rowPins[p], LOW);
    currentRow=p;
  }
  return colPins[key % COL_COUNT];
}

/*
 * Returns 0 if the specified key is pressed, otherwise a value not equal to 0
 * 
 * Param keyCode is the keyboard matrix scan code (row * COL_COUNT * col)
 */
 int isKeyDown(int keyCode){
 if (keyStatus[keyCode]>DEBOUNCE) return 1; else return 0; 
}