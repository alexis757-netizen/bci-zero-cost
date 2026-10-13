// ================= 全局变量区（存 RAM） =================
const int analogPin = 34;    // 电位器引脚
const int ledPin = 2;        // LED引脚

unsigned long lastBlinkTime = 0; // 上一次翻转灯的时间
unsigned long lastAdcTime = 0;   // 上一次读取ADC的时间

bool ledState = false;       // LED当前状态（false是灭，true是亮）
int blinkInterval = 500;     // 闪烁间隔，默认500毫秒

// ================= 初始化（只执行一次） =================
void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  Serial.println("系统启动，等待指令...");
}

// ================= 主循环（飞速跑圈） =================
void loop() {
  
  // ---------- 任务 1：检查串口指令 ----------
  if (Serial.available() > 0) {
    char cmd = Serial.read();
    if (cmd == '1') {
      blinkInterval = 100; // 指令1：快速闪烁
      Serial.println("已切换为：快速闪烁 (100ms)");
    } 
    else if (cmd == '2') {
      blinkInterval = 1000; // 指令2：慢速闪烁
      Serial.println("已切换为：慢速闪烁 (1000ms)");
    }
  }

  // ---------- 任务 2：每 100 毫秒读取一次 ADC ----------
  if (millis() - lastAdcTime >= 100) {
    lastAdcTime = millis(); // 必须更新时间戳
    int sensorValue = analogRead(analogPin);
    float voltage = sensorValue * (3.3 / 4095.0);
    Serial.print("ADC Read: ");
    Serial.print(sensorValue);
    Serial.print(" | Voltage: ");
    Serial.print(voltage);
    Serial.println(" V");
  }

  // ---------- 任务 3：按设定间隔翻转 LED ----------
  if (millis() - lastBlinkTime >= blinkInterval) {
    lastBlinkTime = millis(); // 必须更新时间戳
    ledState = !ledState;     // 反转状态
    digitalWrite(ledPin, ledState);
  }
}