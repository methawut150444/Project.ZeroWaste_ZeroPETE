// ESP32 38pin pinout: https://www.upesy.com/cdn/shop/files/doc-esp32-pinout-reference-wroom-devkit.png
// Ultrasonic sensor: https://www.analogread.com/article/58/%E0%B8%AA%E0%B8%AD%E0%B8%99%E0%B9%83%E0%B8%8A%E0%B9%89%E0%B8%87%E0%B8%B2%E0%B8%99%E0%B8%9A%E0%B8%AD%E0%B8%A3%E0%B9%8C%E0%B8%94-arduino-%E0%B8%81%E0%B8%B1%E0%B8%9A-ultrasonic-module-hc-sr04-%E0%B8%9E%E0%B8%A3%E0%B9%89%E0%B8%AD%E0%B8%A1%E0%B9%82%E0%B8%84%E0%B9%89%E0%B8%94%E0%B8%95%E0%B8%B1%E0%B8%A7%E0%B8%AD%E0%B8%A2%E0%B9%88%E0%B8%B2%E0%B8%87%E0%B8%9B%E0%B8%A3%E0%B8%B0%E0%B8%A2%E0%B8%B8%E0%B8%81%E0%B8%95%E0%B9%8C%E0%B9%83%E0%B8%8A%E0%B9%89%E0%B8%87%E0%B8%B2%E0%B8%99

void Pin_setup(){
  servo_bottle.attach(2);
  servo_cap.attach(15);

  pinMode(ultra_l_trig, OUTPUT);
  pinMode(ultra_l_echo, INPUT);
  pinMode(ultra_r_trig, OUTPUT);
  pinMode(ultra_r_echo, INPUT);
  pinMode(ultra_t_trig, OUTPUT);
  pinMode(ultra_t_echo, INPUT);

  pinMode(lightSensor_bottle1, INPUT);
  pinMode(lightSensor_bottle2, INPUT);
  pinMode(lightSensor_cap, INPUT);

  pinMode(motor_cutBottle_pin1, OUTPUT);
  pinMode(motor_cutBottle_pin2, OUTPUT);

  pinMode(IR_bottle, INPUT);
  pinMode(IR_cap, INPUT);
}

void InitialDevice(){
  servo_bottle.write(90);
  servo_cap.write(85);

  CuttingBottle(0);
}