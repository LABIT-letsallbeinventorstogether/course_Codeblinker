/* LABIT - Code for blinkey in the codeblinker course
   This code is for the blinkey on breaboard, with the button on pin 2
   when activated it will send 1001101 as code
*/



// P I N S
const int gc_pinLed = 3;      // pin for led
const int gc_pinButton = 2;   // pin for button


// C O N S T A N T S
const int gc_code[]     = {1, 0, 0, 1, 1, 0, 1};   // code send
int gv_codeLength = sizeof(gc_code) / sizeof(int); // lengt of code, maybe you did it manually and used 7 in your own code, but this  will determine the length of the code automatically
int lv_delayTime  = 25;                            // time between pulses




//-----------------------------------------------------------------------
void setup() {
  pinMode(gc_pinLed, OUTPUT);   //make the ledpin an output pin
  pinMode(gc_pinButton, INPUT); //make the button pin an input pin

}





//-----------------------------------------------------------------------
void loop() {
  boolean var1 = 1;
  // --- S E N D   L E D   C O D E
  if (digitalRead(gc_pinButton)) {            // check if button is pressed
    for (int i = 0; i < gv_codeLength; i++) { // if so send code
      if (gc_code[i] != 1) {
        digitalWrite(gc_pinLed, HIGH);
        delay(lv_delayTime);
        digitalWrite(gc_pinLed, LOW);
      }
      else {
        delay(lv_delayTime);
      }
    }
    delay(1000);
  }
}
//-----------------------------------------------------------------------
