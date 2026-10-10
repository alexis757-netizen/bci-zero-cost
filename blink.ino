void setup() {
  pinMode(2, OUTPUT);
}

// 自定义函数：参数 onTime 控制亮的时间，offTime 控制灭的时间
void blinkAndPrint(int onTime, int offTime) {
  digitalWrite(2, HIGH);
  delay(onTime);
  digitalWrite(2, LOW);
  delay(offTime);
}

void loop() {
  blinkAndPrint(1000, 5000); // 调用函数
}