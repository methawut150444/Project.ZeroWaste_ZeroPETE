
//-----------------------------< PIN DEFINE >---------------------------------//

#include <ESP32Servo.h>
Servo servo_bottle; 
Servo servo_cap; 

#define ultra_l_trig 32
#define ultra_l_echo 33
#define ultra_r_trig 25
#define ultra_r_echo 26
#define ultra_t_trig 27
#define ultra_t_echo 14

#define lightSensor_bottle1 35
#define lightSensor_bottle2 13
#define lightSensor_cap 34

#define IR_bottle 36
#define IR_cap 39

#define motor_cutBottle_pin1 22
#define motor_cutBottle_pin2 21

//-----------------------------< VARIABLE VALUE >---------------------------------//

// state
#define start_Page 1
#define countDisposal_Page 2
#define labelWarning_Page 3
#define inputID_Page 4
#define confirmRecrod 5

int state = start_Page;

unsigned long lst = 0;
int triggerTimecutting = 0;

int amountBottle = 0;
int amountCap = 0;

int bottle_status = 0;
int cap_status = 0;

int lux_bottle;
int lux_cap;

String studentID = "";

String totalPoint = "";
String totalBottle = "";
String totalCap = "";

//==================================< SETUP >===================================//

void setup() {
  Serial.begin(9600);
  Pin_setup();
  InitialDevice();
  
  Screen_setup();
  WiFi_setup();
}

//==================================< LOOP >====================================//

void loop() {
  switch(state){
    //--------------------------------------------------------> 1
    case start_Page: 
      Start_IMG();
      if(CheckTouch(0, 480, 0, 320) == 1){
        state = countDisposal_Page;
      }
    break;

    //--------------------------------------------------------> 2
    case countDisposal_Page: 
      CountDisposal_IMG();

      lux_cap = analogRead(lightSensor_cap);
      // lux_bottle = (analogRead(lightSensor_bottle1) + analogRead(lightSensor_bottle2)) / 2;
      // Serial.println(String(analogRead(lightSensor_bottle1)) + " " + String(analogRead(lightSensor_bottle2)));

      if(CheckHack_bottle() != 1){
        if(CheckBottle() == 1){
          delay(1000);
          servo_bottle.write(180);
          amountBottle += 1;
          delay(3000);
          servo_bottle.write(90);

          lst = millis();
          CuttingBottle(1);   //start cut
        }
        else{
          servo_bottle.write(90);
        }
      }
      else{
        servo_bottle.write(90);
      }

      if(millis() - lst >= 3000 && millis() - lst < 6000){
        CuttingBottle(-1);
      }
      else if(millis() - lst >= 6000){
        CuttingBottle(0);
      }

      if(CheckHack_cap() != 1){
        if(lux_cap >= 350){
          delay(1000);
          servo_cap.write(0);
          amountCap += 1;
          delay(1000);
          servo_cap.write(85);
          delay(1000);
        }
        else{
          servo_cap.write(85);
        }
      }
      else{
        servo_cap.write(85);
      }

      // Serial.println(String(lux_cap));

      if(CheckTouch(0, 110, 10, 50) == 1){  // "NEXT" button
        state = inputID_Page;
      }
    break;

    //--------------------------------------------------------> 3
    case labelWarning_Page: 
      LabelWarning_IMG();
      delay(600);
      state = countDisposal_Page;
    break;

    //--------------------------------------------------------> 4
    case inputID_Page: 
      inputID_IMG();
      if(CheckTouch(420, 460, 165, 210) == 1)       studentID += "1"; // 1 button
      else if(CheckTouch(370, 410, 165, 210) == 1)  studentID += "2"; // 2 button
      else if(CheckTouch(310, 350, 165, 210) == 1)  studentID += "3"; // 3 button
      else if(CheckTouch(260, 300, 165, 210) == 1)  studentID += "4"; // 4 button
      else if(CheckTouch(420, 460, 110, 155) == 1)  studentID += "5"; // 5 button
      else if(CheckTouch(370, 410, 110, 150) == 1)  studentID += "6"; // 6 button
      else if(CheckTouch(310, 350, 110, 150) == 1)  studentID += "7"; // 7 button
      else if(CheckTouch(260, 300, 110, 150) == 1)  studentID += "8"; // 8 button
      else if(CheckTouch(370, 410, 40, 100) == 1)   studentID += "9"; // 9 button 
      else if(CheckTouch(310, 350, 40, 100) == 1){  // C button for remove lasted character
        studentID.remove(studentID.length()-1, 1);
      }   
      else if(CheckTouch(25, 150, 0, 60) == 1) state = confirmRecrod;
    break;

    //--------------------------------------------------------> 5
    case confirmRecrod: 
      Recording_IMG();

      RecordData();

      RecordedInformation_IMG();
      
      delay(6000);

      CuttingBottle(0);
      studentID = "";
      amountBottle = 0;
      amountCap = 0;
      totalPoint = "";
      totalBottle = "";
      totalCap = "";

      state = start_Page;
    break;
  }
}











