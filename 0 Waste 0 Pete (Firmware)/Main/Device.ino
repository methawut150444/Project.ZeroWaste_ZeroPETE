
//------------------------------------< ULTRASONIC >---------------------------------//

int Ultra_checkDistance(int trig, int echo){
  long duration, distance; //ประกาศตัวแปรเก็บค่าระยะ

  digitalWrite(trig, LOW); 
  delayMicroseconds(5); 
  digitalWrite(trig, HIGH); 
  delayMicroseconds(5); 
  digitalWrite(trig, LOW); 

  duration = pulseIn(echo, HIGH); //อ่านค่าของ echo
  distance = (duration/2) / 29.1; //คำนวณเป็น centimeters
  // Serial.print(distance); 
  // Serial.print(" cm\n");
  return distance;
}

//------------------------------------< LIGHT SENSOR >---------------------------------//

int Light_checkLux(int signal_pin){
  int val = analogRead(signal_pin);
  return val;
}

//------------------------------------< CHECK BOTTON >---------------------------------//

int CheckBottle(){  // return 1: open gate, 0: close gate
  int ultra_l_distance = Ultra_checkDistance(ultra_l_trig, ultra_l_echo);
  int ultra_r_distance = Ultra_checkDistance(ultra_r_trig, ultra_r_echo);
  int ultra_t_distance = Ultra_checkDistance(ultra_t_trig, ultra_t_echo);
  // Serial.println(String(ultra_l_distance) + " " + String(ultra_t_distance) + " " + String(ultra_r_distance));

  if(ultra_l_distance <= 9 && ultra_l_distance <= 9){
    return 1;
  }
  else{
    return 0;
  }
  // if(bottle_status == 0){
  //   if(ultra_l_distance <= 0 && ultra_r_distance <= 0 && ultra_t_distance <= 0){  // RW bottle size
  //     amountBottle += 1;
  //     bottle_status = 1;
  //     return 1;
  //   }
  //   else if(ultra_l_distance <= 0 && ultra_r_distance <= 0 && ultra_t_distance <= 0){ // crystal bottle size
  //     amountBottle += 1;
  //     bottle_status = 1;
  //     return 1;
  //   }
  //   else if(ultra_l_distance <= 0 && ultra_r_distance <= 0 && ultra_t_distance <= 0){ // nestle bottle size
  //     amountBottle += 1;
  //     bottle_status = 1;
  //     return 1;
  //   }
  //   else if(ultra_l_distance <= 0 && ultra_r_distance <= 0 && ultra_t_distance <= 0){ // minere bottle size
  //     amountBottle += 1;
  //     bottle_status = 1;
  //     return 1;
  //   }
  //   else if(ultra_l_distance <= 0 && ultra_r_distance <= 0 && ultra_t_distance <= 0){ // pura bottle size
  //     amountBottle += 1;
  //     bottle_status = 1;
  //     return 1;
  //   }
  //   else{ // out of scope botton
  //     amountBottle += 0;
  //     return 0;
  //   }
  // }
  // else if(bottle_status != 0){
  //   if(ultra_l_distance <= 0 && ultra_r_distance <= 0 && ultra_t_distance <= 0){  // take bottle off
  //     bottle_status = 0;
  //     return 0;
  //   }
  //   else{
  //     return 1;
  //   }
  // }

}

//------------------------------------< CHECK BOTTON LABEL >---------------------------------//
int CheckLabelBottle(){
  // int lux = Light_checkLux(lightSensor_bottle);
  // Serial.println(lux);
  // if(lux >= 100 && lux <= 200){
  //   return 1; // found label
  // }
  // else{
  //   return 0; // not found label
  // }
}

//------------------------------------< CHECK CAP >---------------------------------//

int CheckCap(){ // return 1: open gate, 0: close gate
  int lux = Light_checkLux(lightSensor_cap);
  if(cap_status == 0){
    if(lux >= 100 && lux <= 200){
      amountCap += 1;
      cap_status = 1;
      return 1;
    }
    else{
      return 0;
    }
  }
  else if(cap_status != 0){
    if(lux >= 100 && lux <= 200){ // cap dropped.
      cap_status = 0;
      return 0;
    }
    else{
      return 1;
    }
  }
}

//------------------------------------< CUTTING BOTTON >---------------------------------//

void CuttingBottle(int status){
  if(status == 0){    // stop
    digitalWrite(motor_cutBottle_pin1, 0);
    digitalWrite(motor_cutBottle_pin2, 0);
  }
  else if(status == 1){   // cut
    digitalWrite(motor_cutBottle_pin1, 1);
    digitalWrite(motor_cutBottle_pin2, 0);
  }
  else if(status == -1){  // disposal
    digitalWrite(motor_cutBottle_pin1, 0);
    digitalWrite(motor_cutBottle_pin2, 1);
  }
}

//------------------------------------< CHECKHACK_BOTTLE >---------------------------------//

int CheckHack_bottle(){
  if(digitalRead(IR_bottle) == 0){
    // Serial.println("found hand (cap)");
    return 0;
  }
  else{
    // Serial.println("not found hand (cap)");
    return 1;
  }
}

//------------------------------------< CHECKHACK_BOTTLE >---------------------------------//

int CheckHack_cap(){
  if(digitalRead(IR_cap) == 0){
    // Serial.println("found hand (cap)");
    return 0;
  }
  else{
    // Serial.println("not found hand (cap)");
    return 1;
  }
}




