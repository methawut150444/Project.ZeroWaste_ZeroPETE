//TFT Manual: https://www.artronshop.co.th/article/95/%E0%B8%81%E0%B8%B2%E0%B8%A3%E0%B9%83%E0%B8%8A%E0%B9%89%E0%B8%87%E0%B8%B2%E0%B8%99%E0%B8%88%E0%B8%AD-lcd-tft-%E0%B8%A3%E0%B9%88%E0%B8%A7%E0%B8%A1%E0%B8%81%E0%B8%B1%E0%B8%9A-esp32-%E0%B8%94%E0%B9%89%E0%B8%A7%E0%B8%A2%E0%B9%84%E0%B8%A5%E0%B8%9A%E0%B8%A3%E0%B8%B2%E0%B8%A3%E0%B8%B5%E0%B9%88-tft_espi
// Size : x (width) = 480, y (height) = 320

/*  < pin connecting of ESP32 and 3.5 TFT 
  TFT         ESP
  
  vcc         3.3V
  gnd         GND
  cs          5
  reset       EN
  DC/RS       17
  SDI<MOSI>   23
  SCK         18
  LED         3.3V
  SDO<MISO>   -
  T_CLK       18     
  T_CS        16
  T_DIN       23
  T_DO        19
  T_IRQ       -
*/ 


#include <TFT_eSPI.h>
TFT_eSPI tft = TFT_eSPI();

#include "img/img_1/img_1.ino"
#include "img/img_2/img_2.ino"
#include "img/img_3/img_3.ino"

//------------------------------------< SCREEN BASE FUNCTION >---------------------------------//

void Screen_setup(){
  tft.init();
  tft.setRotation(3);
  uint16_t calData[5] = { 430, 3286, 512, 2989, 7 };  // Use this calibration code in setup():
  tft.setTouch(calData);
}

int CheckTouch(int xMin, int xMax, int yMin, int yMax){
  uint16_t a, b;
  if(tft.getTouch(&a, &b)){
    if ((a > xMin && a < xMax) && (b > yMin && b < yMax)) {
      return 1; // touched.
    }
    else{
      return 0; // not yet to touch.
    }
  }
}

void CheckTouchPosition(){
  uint16_t a, b;
  if(tft.getTouch(&a, &b)){
    Serial.println(String(a) + " " + String(b));
  }
}

//------------------------------------< SCREEN GRAPHIC >---------------------------------//


//--------------------------------------------------------> Setup
void ConnectingNetwork_IMG(){
  tft.setTextSize(3);
  tft.setTextColor(tft.color24to16(0x0E004B));
  tft.setTextDatum(MC_DATUM);
  tft.drawString("Connecting Wi-Fi.", 240, 130);

  String loadingDot = "";
  for(int i = 0; i < 5; i++){
    loadingDot += ".";
    tft.drawString(loadingDot, 240, 180);
    delay(500);
  }
}
//--------------------------------------------------------> 1
void Start_IMG(){
  tft.setSwapBytes(true);
  tft.pushImage(0, 0, 480, 320, img_1);
}

//--------------------------------------------------------> 2
void CountDisposal_IMG(){
  tft.setSwapBytes(true);
  tft.pushImage(0, 0, 480, 320, img_2);

  tft.setTextSize(3);
  tft.setTextColor(tft.color24to16(0x0E004B));//for test: 0xb22222
  tft.setTextDatum(TL_DATUM);
  tft.drawString(String(amountBottle), 69, 180);
  tft.drawString(String(amountCap), 172, 180);
}

//--------------------------------------------------------> 3
void LabelWarning_IMG(){
  // Shape layout
  tft.fillRect(45, 80, 390, 160, tft.color24to16(0x8B120F)); //for outline
  tft.fillRect(55, 90, 370, 140, tft.color24to16(0xF6F4C9));

  tft.setTextSize(3);
  tft.setTextColor(tft.color24to16(0x8B120F));
  tft.setTextDatum(MC_DATUM);
  tft.drawString("PLEASE TAKE OUT THE", 240, 130);
  tft.drawString("BOTTLE LABLE", 240, 180);
}

//--------------------------------------------------------> 4
void inputID_IMG(){
  tft.setSwapBytes(true);
  tft.pushImage(0, 0, 480, 320, img_3);

  // for studentID text
  tft.setTextSize(3);
  tft.setTextColor(tft.color24to16(0x0E004B));
  tft.setTextDatum(CL_DATUM);
  tft.drawString(": " + studentID, 65, 85);

  // for amountBottle
  tft.setTextSize(2);
  tft.setTextColor(tft.color24to16(0x0E004B));
  tft.setTextDatum(CL_DATUM);
  tft.drawString(String(amountBottle), 375, 112);

  // for amountCap
  tft.setTextSize(2);
  tft.setTextColor(tft.color24to16(0x0E004B));
  tft.setTextDatum(CL_DATUM);
  tft.drawString(String(amountCap), 375, 192);
}

//--------------------------------------------------------> 5
void Recording_IMG(){
  // Shape layout
  tft.fillRect(45, 80, 390, 160, tft.color24to16(0x0E004B)); //for outline
  tft.fillRect(55, 90, 370, 140, tft.color24to16(0xF6F4C9));

  tft.setTextSize(3);
  tft.setTextColor(tft.color24to16(0x8B120F));
  tft.setTextDatum(MC_DATUM);
  tft.drawString("Recording", 240, 130);

  String loadingDot = "";
  for(int i = 0; i < 3; i++){
    loadingDot += ".";
    tft.drawString(loadingDot, 240, 180);
    delay(1000);
  }
}

void RecordedInformation_IMG(){
  // Shape layout
  tft.fillRect(45, 80, 390, 160, tft.color24to16(0x0E004B)); //for outline
  tft.fillRect(55, 90, 370, 140, tft.color24to16(0xF6F4C9));

  tft.setTextSize(2);
  tft.setTextColor(tft.color24to16(0x0E004B));
  tft.setTextDatum(MC_DATUM);
  tft.drawString("Student ID: " + studentID, 240, 110);
  tft.drawString("totalBottle: " + totalBottle, 240, 190);
  tft.drawString("totalCap: " + totalCap, 240, 210);

  tft.setTextSize(3);
  tft.setTextColor(tft.color24to16(0x0E004B));
  tft.drawString("totalPoint: " + totalPoint, 240, 150);
}


