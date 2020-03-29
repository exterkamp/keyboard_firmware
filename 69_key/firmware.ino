/*
 * Written by Shane Exterkamp in 2020.
 * 
 * Inspired by Stefan Jakobsson, 2019.
 */

#include <Bounce.h>

#define ROW_COUNT 5
#define COL_COUNT 15
#define DEBOUNCE 10
#define SCAN_DELAY 10

#define KEY_UNDEFINED -1    // For keyboard matrix positions not in use

int colPins[] = {5,6,7,8,9,10,11,12,13/* Only useable if you "disable" the onboard LED */,14,15,16,17,18,19};
int rowPins[] = {0,1,2,3,4};

int keys[5][15] = {
 //0                    1              2                3              4          5              6          7              8          9           10             11              12               13                       14
  {KEY_ESC,           KEY_1,           KEY_2,           KEY_3,         KEY_4,     KEY_5,         KEY_6,     KEY_7,         KEY_8,     KEY_9,      KEY_0,         KEY_MINUS,      KEY_EQUAL,       KEY_BACKSPACE,           KEY_INSERT}, 
  {KEY_TAB,           KEY_Q,           KEY_W,           KEY_E,         KEY_R,     KEY_T,         KEY_Y,     KEY_U,         KEY_I,     KEY_O,      KEY_P,         KEY_LEFT_BRACE, KEY_RIGHT_BRACE, KEY_BACKSLASH,           KEY_DELETE},
  {KEY_CAPS_LOCK,     KEY_A,           KEY_S,           KEY_D,         KEY_F,     KEY_G,         KEY_H,     KEY_J,         KEY_K,     KEY_L,      KEY_SEMICOLON, KEY_QUOTE,      KEY_UNDEFINED,   KEY_ENTER,               KEY_HOME},
  {MODIFIERKEY_SHIFT, KEY_Z,           KEY_X,           KEY_C,         KEY_V,     KEY_B,         KEY_N,     KEY_M,         KEY_COMMA, KEY_PERIOD, KEY_SLASH,     KEY_UNDEFINED,  KEY_UNDEFINED,   MODIFIERKEY_RIGHT_SHIFT, KEY_END},
  {MODIFIERKEY_CTRL,  MODIFIERKEY_GUI, MODIFIERKEY_ALT, KEY_BACKSPACE, KEY_ENTER, KEY_UNDEFINED, KEY_SPACE, KEY_UNDEFINED, KEY_TILDE, KEY_LEFT,   KEY_UP,        KEY_DOWN,       KEY_UNDEFINED,   KEY_RIGHT,               KEY_F1}};

int currentRow = 0;
int keyStatus[ROW_COUNT][COL_COUNT];

// Create Bounce objects for each button.  The Bounce object
// automatically deals with contact chatter or "bounce", and
// it makes detecting changes very simple.

Bounce button2 = Bounce(5, DEBOUNCE);  
Bounce button3 = Bounce(6, DEBOUNCE);
Bounce button4 = Bounce(7, DEBOUNCE);
Bounce button5 = Bounce(8, DEBOUNCE);
Bounce button6 = Bounce(9, DEBOUNCE);
Bounce button7 = Bounce(10, DEBOUNCE);
Bounce button8 = Bounce(11, DEBOUNCE);
Bounce button9 = Bounce(12, DEBOUNCE);
Bounce button10 = Bounce(13, DEBOUNCE);
Bounce button11 = Bounce(14, DEBOUNCE);
Bounce button12 = Bounce(15, DEBOUNCE);
Bounce button13 = Bounce(16, DEBOUNCE);
Bounce button14 = Bounce(17, DEBOUNCE);
Bounce button15 = Bounce(18, DEBOUNCE);
Bounce button16 = Bounce(19, DEBOUNCE);

void setup() {
  // Column Pins
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  pinMode(13, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);
  pinMode(15, INPUT_PULLUP);
  pinMode(16, INPUT_PULLUP);
  pinMode(17, INPUT_PULLUP);
  pinMode(18, INPUT_PULLUP);
  pinMode(19, INPUT_PULLUP);


  // Row Pins
  pinMode(0, INPUT);
  pinMode(1, INPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);


  // Init status
  int i;
  int j;
  for (i=0;i<ROW_COUNT;i++){
    for (j=0;j<COL_COUNT;j++){
      keyStatus[i][j] = 0;
    }
  }
}

void loop() {
  scanKeys();
  delay(SCAN_DELAY);
}

/*
 * Scan keyboard matrix, results stored in keyStatus array
*/
void scanKeys(){
  int i;
  int j;
  for (i=0;i<ROW_COUNT;i++){
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(rowPins[i], LOW);
    for (j=0;j<COL_COUNT;j++){
      if (keyStatus[i][j]==0 && digitalRead(colPins[j])==LOW){
        //Key press event
        keyStatus[i][j] = 1;
        Keyboard.press(keys[i][j]);
      }
      else if (keyStatus[i][j]==1 && digitalRead(colPins[j])==HIGH){
        //Key release 
        keyStatus[i][j] = 0;
        Keyboard.release(keys[i][j]);
      }
    }
    pinMode(rowPins[i], INPUT);
    digitalWrite(rowPins[i], HIGH);
    delay(1);
  }
}
