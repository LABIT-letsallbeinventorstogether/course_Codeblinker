/* LABIT - Codeblinker course 
 * This code is for the base station, which will be able to measure codes send with light 
 * when the code 1001101 is measured this program will show "known code" in the serial monitor
 */

// P I N S
int gc_photocel = A5;                 //pin of photocel

// V A R I A B L E S
unsigned long gv_timeOld = 0;         //time of last trigger
int gv_light = 1;                     //is signal high indicator
String gv_codeString = "";            //string with found code, string values have to be between "this is as string"
                                      //!!! the code in the blinky key should always start and end with light (a 1)



//-----------------------------------------------------------------------
void setup() {
  pinMode(A6, INPUT);                 //pin setup
  Serial.begin(9600);                 //start serial monitor
}





//-----------------------------------------------------------------------
void loop() {

  // L O C A L   V A R I A B L E S
  int lv_measured = analogRead(gc_photocel);                                                //signal read from analog pin
  int lv_timeDifference   = 0;                                                              //difference in time between trigger now and last trigger
  int lv_signalLength = 25;                                                                 //time of one send signal
  int lv_slopeTrigger = 100;                                                                //when to detect a slope



  // --- D E T E C T   S L O B E   R I S E / F A L L
  // measures time between slopes
  if (gv_light == 1 && lv_measured < lv_slopeTrigger) {                                       // see && means  and, 2 conditions here
    gv_light = 0;                                                                             //signal is low
    lv_timeDifference   = (millis() - gv_timeOld);                                            //time between triggers, millis() gives the time passed since the arduino started up in milliseconds
    gv_timeOld = millis();                                                                    //store old time
  }
  if (gv_light == 0 && lv_measured > lv_slopeTrigger) {
    gv_light = 1; //signal is high
    lv_timeDifference   = (millis() - gv_timeOld);
    gv_timeOld = millis();
  }



  // --- A D D   M E A S U R E M E N T   T O   A R R A Y
  // count amount of signals in time measured between slopes
  if (lv_timeDifference   != 0) {                                                                //when triggered
    if (lv_timeDifference   < 250) {                                                             //ignore times > 250ms
      for (int i = 0; i < ((lv_timeDifference   + lv_signalLength / 2) / lv_signalLength); i++) {//how many consequent same values measured, (+lv_signalLength/2) because these are integers
        gv_codeString = gv_codeString + String(gv_light);                                        //add signal to string
      }
    }
  }



  // --- D I S P L A Y   A R R A Y   I N   S E R I A L   M O N I T O R
  if (gv_codeString != "" and (millis() - gv_timeOld) > 250) {                                   // instead of && you can also use and
    Serial.println(gv_codeString);                                                               // show if something is detected
    if (gv_codeString == "1001101") {                                                            //!!! the code should always start and end with an 1
      Serial.println("known code");                                                              // show if this code is detected
    }
    gv_codeString = "";
  }

}
//-----------------------------------------------------------------------
