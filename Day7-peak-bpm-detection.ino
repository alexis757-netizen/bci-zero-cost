// ================= 全局变量区 =================
const int ledPin = 2;            

unsigned long lastSampleTime = 0; 
const int sampleInterval = 20;   

float simulatedSignal = 0.0;     
float filteredSignal = 0.0;      

// ---------- 今天的新增变量 ----------
bool isPeakDetected = false;     // 状态标志：当前是否正在经历信号峰值
unsigned long lastPeakTime = 0;  // 记录上一次检测到峰值的时间
int bpm = 0;                     // 计算出的频率（每分钟多少次）

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); 
  Serial.println("Day 7: 峰值检测与BPM估算已启动...");
}

void loop() {
  if (millis() - lastSampleTime >= sampleInterval) {
    lastSampleTime = millis();

    // ---- 1. 模拟脑电/心电信号 ----
    float noise = random(-30, 30); 
    // 每1.2秒（1200毫秒）出现一次信号爆发，模拟心跳（1.2秒 = 50 BPM）
    if (millis() % 1200 < 300) { 
      simulatedSignal = 800 + noise; 
    } else {
      simulatedSignal = 50 + noise;  
    }

    // ---- 2. 移动平均滤波 ----
    filteredSignal = (simulatedSignal * 0.2) + (filteredSignal * 0.8);

    // ---- 3. 峰值检测与频率计算（核心） ----
    int threshold = 400; 
    
    if (filteredSignal > threshold) {
      // 状态从“平静”变成“爆发”的那一刻
      if (!isPeakDetected) { 
        isPeakDetected = true;
        digitalWrite(ledPin, HIGH); 
        
        unsigned long currentTime = millis(); // 获取当前时间
        
        // 如果 lastPeakTime 不是 0（说明之前已经检测过一次峰值了）
        if (lastPeakTime != 0) {
          // 计算两次峰值的时间差（毫秒）
          unsigned long timeDiff = currentTime - lastPeakTime;
          
          // 计算BPM：1分钟(60000毫秒) / 两次跳动的时间差
          if (timeDiff > 0) { // 防止除以 0 崩溃
            bpm = 60000 / timeDiff;
            Serial.print(">>> 检测到峰值！当前频率: ");
            Serial.print(bpm);
            Serial.println(" BPM <<<");
          }
        }
        
        // 更新最后一次峰值的时间
        lastPeakTime = currentTime;
      }
    } 
    else {
      // 信号掉回阈值以下
      if (isPeakDetected) {
        isPeakDetected = false;
        digitalWrite(ledPin, LOW); 
      }
    }
  }
}