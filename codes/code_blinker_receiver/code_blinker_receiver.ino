/* LABIT - Codeblinker course 
 * This code is for the base station, which will be able to measure codes send with light 
 * when the code 1001101 is measured this program will show 0001 on a display
 */

// P I N S
int gc_photocel = A5;

// V A R I A B L E S
unsigned long gv_timeOld = 0;
unsigned long gv_timeLastMeasured = 0;
int gv_up = 1;
String gv_display = "";               //string that will be displayed on serial monitor

// D I S P L A Y
#include "TM1637.h"
#define CLK 8                         //pins definitions for TM1637 and can be changed to other ports
#define DIO 9
TM1637 tm1637(CLK, DIO);





//-----------------------------------------------------------------------
void setup() {
  pinMode(gc_photocel, INPUT);
  Serial.begin(9600);

  // D I S P L A Y
  tm1637.init();
  tm1637.set(BRIGHT_TYPICAL);//BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
}





//-----------------------------------------------------------------------
void loop() {
  int lv_measured = analogRead(gc_photocel);
  int lv_timediference = 0;
  int lv_delayTime = 25; //time of one signals send
  int lv_slopeTrigger = 180; //when to detect a slope


  // --- D E T E C T   S L O B E   R I S E / F A L L
  // measures time between slopes
  if (gv_up == 1 && lv_measured < lv_slopeTrigger) {
    gv_up = 0;
    lv_timediference = (millis() - gv_timeOld);
    gv_timeOld = millis();
  }
  if (gv_up == 0 && lv_measured > lv_slopeTrigger) {
    gv_up = 1;
    lv_timediference = (millis() - gv_timeOld);
    gv_timeOld = millis();
  }



  // --- A D D   M E A S U R E M E N T   T O   A R R A Y
  // count amount of signals in time measured between slopes
  if (lv_timediference != 0) {
    gv_timeLastMeasured = millis();
    if (lv_timediference < 500) {
      for (int i = 0; i < ((lv_timediference+lv_delayTime/2) / lv_delayTime); i++) {          //how many consequent same values measured
        gv_display = gv_display + String(gv_up);
      }
    }
  }



  // --- D I S P L A Y   A R R A Y   I N   S E R I A L   M O N I T O R
  if (gv_display != "" and (millis() - gv_timeLastMeasured) > 500) {
    Serial.println(gv_display);
    if (gv_display == "1001101") {
      tm1637.display(0, 0);
      tm1637.display(1, 0);
      tm1637.display(2, 0);
      tm1637.display(3, 1);
      delay(1500);
      tm1637.init();
    }
    gv_display = "";
  }

}
//-----------------------------------------------------------------------
