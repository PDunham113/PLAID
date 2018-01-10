/* Weather Clock Firmware v0.1 (2014-03-07)
   Created 2014-03-07
   
   CHANGELOG:
     0.1 - Created.
   
   Uses the Time library to allow the Arduino to act as an RTC for the display.
   Prints the time to the serial monitor.
   
   Future Goals:
     -Get weather updates from the Internet (current temp, basic conditions)
     -Sync time with Internet
     -Output date, time, weather to 32x32 RGB LED panel
     
   Circuit:
     Requires:
       -Arduino (Developed on Arduino Pro Mini 5V w/ ATMega328P)
     * USB cable to computer
     
     That's all!   
*/

#include <Time.h>

String formattedTime = "";

void setup() {
  Serial.begin(9600);       // Opens serial connection
  
  setSyncProvider(getTime); // Sets function to call when sync is required
  
  getTime();
}

void loop() {
  
  if(timeStatus() != timeNotSet) {
    displayTime();
  }
}

String printDigits(int digit) {
  String digits = String(digits);
  
  if(digit < 10) {
    digits = '0' + digits;
  }
  
  return digits;
}
    

void formatTime() {
  formattedTime = String(year()) + "-" + printDigits(month()) + "-" + printDigits(day()) + " " + printDigits(hourFormat12()) + ":" + printDigits(minute()) + ":" + printDigits(second()) + " ";
 
 if(isAM()) {
  formattedTime += "AM";
 }
 else {
   formattedTime += "PM";
 }
}

void displayTime() {
  formatTime();
  
  Serial.println(formattedTime);
}

time_t getTime() {
  time_t time = 0;
  
  Serial.print("Enter the number of seconds since Jan 1, 1970");
  
  while(!Serial.available()) {
  }
  
  time = Serial.parseInt();
  
  return time;
}
