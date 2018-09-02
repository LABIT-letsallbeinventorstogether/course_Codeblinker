/* LABIT - Code for blinkey in the codeblinker course
   This code is for the blinkey on breaboard, 
   with the button attached to the powerline
   when activated it will send 1001101 as code
*/


// P I N S
const int gc_pinLed = 3;

// C O N S T A N T S
const int gc_code[]     = {1, 0, 0, 1, 1, 0, 1};
int gv_codeLength = sizeof(gc_code) / sizeof(int);
int lv_delayTime  = 25;




//-----------------------------------------------------------------------
void setup() {
  pinMode(gc_pinLed, OUTPUT);

}





//-----------------------------------------------------------------------
void loop() {
  // --- S E N D   L E D   C O D E
  for (int i = 0; i < gv_codeLength; i++) {
    if (gc_code[i] == 1) {
      digitalWrite(gc_pinLed, HIGH);
      delay(lv_delayTime);
      digitalWrite(gc_pinLed, LOW);
    }
    else {
      delay(lv_delayTime);
    }
  }
  delay(2000);
}
//-----------------------------------------------------------------------
