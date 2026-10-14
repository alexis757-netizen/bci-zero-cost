// ================= 全局变量区 =================
const int analogPin = 34;    
const int ledPin = 2;        

unsigned long lastBlinkTime = 0; 
unsigned long lastAdcTime = 0;   
bool ledState = false;       
int blinkInterval = 500;     

// ================= 今天的新增变量（滤波用） =================
const int numReadings = 50;      // 滤波窗口大小（每次算50个数据的平均值）
int readings[numReadings];       // 存储最近50次读数的数组
int readIndex = 0;               // 当前数组存储位置索引
int total = 0;                   // 当前所有读数的总和
int average = 0;                 // 最终的平滑平均值

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  
  // 初始化数组，全部清零
  for (int i = 0; i < numReadings; i++) {
    readings[i] = 0;
  }
  Serial.println("Day 5: 移动平均滤波已启动...");
}

void loop() {
  // ---------- 任务 1：串口指令（保留Day 4的功能） ----------
  if (Serial.available() > 0) {
    char cmd = Serial.read();
    if (cmd == '1') blinkInterval = 100; 
    if (cmd == '2') blinkInterval = 1000; 
  }

  // ---------- 任务 2：滤波与ADC采样（每50ms执行一次） ----------
  if (millis() - lastAdcTime >= 50) { // 我们加快频率到50ms
    lastAdcTime = millis(); 

    // 1. 减去最老的读数（将它移出总和）
    total = total - readings[readIndex];
    
    // 2. 读取新的ADC值，存入数组
    // 人为加入 ±20 的随机噪声，模拟现实世界
int noise = random(-20, 20); 
readings[readIndex] = analogRead(analogPin) + noise;
    
    // 3. 将新读数加到总和中
    total = total + readings[readIndex];
    
    // 4. 数组索引前进1位，如果到了末尾就回到开头（循环数组）
    readIndex = readIndex + 1;
    if (readIndex >= numReadings) {
      readIndex = 0;
    }
    
    // 5. 计算平均值
    average = total / numReadings;
    
    // 6. 打印对比：左边是原始值（跳动大），右边是平均值（平滑）
    Serial.print("Raw: ");
    Serial.print(analogRead(analogPin) + random(-20, 20)); // 打印一次原始值做对比
    Serial.print(" | Filtered: ");
    Serial.print(average);
    
    // 顺便把平均值换算成电压打印出来
    float voltage = average * (3.3 / 4095.0);
    Serial.print(" | Voltage: ");
    Serial.print(voltage);
    Serial.println(" V");
  }

  // ---------- 任务 3：LED闪烁（保持并行） ----------
  if (millis() - lastBlinkTime >= blinkInterval) {
    lastBlinkTime = millis(); 
    ledState = !ledState;     
    digitalWrite(ledPin, ledState);
  }
}