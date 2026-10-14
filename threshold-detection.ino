// ================= 全局变量区 =================
const int ledPin = 2;            

unsigned long lastSampleTime = 0; // 采样时间戳
const int sampleInterval = 20;   // 每20毫秒采样一次（模拟50Hz采样率）

float simulatedSignal = 0.0;     // 模拟的脑电信号原始值
float filteredSignal = 0.0;      // 滤波后的平滑信号
bool isBursting = false;         // 状态标志：当前是否处于信号爆发期

// ================= 初始化区 =================
void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); // 初始灯灭
  Serial.println("Day 6: 阈值检测已启动...");
}

// ================= 主循环区 =================
void loop() {
  // 每隔 20 毫秒执行一次信号处理逻辑
  if (millis() - lastSampleTime >= sampleInterval) {
    lastSampleTime = millis();

    // ---- 1. 模拟脑电波生成（不用电位器了） ----
    // 基础信号是50Hz的环境噪声（比如工频干扰）
    float noise = random(-30, 30); 
    
    // 模拟每1.5秒出现一次的“眨眼”尖峰
    if (millis() % 1500 < 300) { 
      simulatedSignal = 800 + noise; // 尖峰出现，幅度很大
    } else {
      simulatedSignal = 50 + noise;  // 平静状态，幅度很小
    }

    // ---- 2. 移动平均滤波（沿用Day 5的知识） ----
    // 系数0.2代表新数据占20%，旧数据占80%，这就是低通滤波
    filteredSignal = (simulatedSignal * 0.2) + (filteredSignal * 0.8);

    // ---- 3. 阈值检测（核心算法） ----
    int threshold = 400; // 阈值：400以上视为“动作检测”
    
    // 如果滤波后的信号超过了阈值
    if (filteredSignal > threshold) {
      if (!isBursting) { // 只有在“从平静变成爆发”的那一刻，才打印一次
        isBursting = true;
        digitalWrite(ledPin, HIGH); // 点亮LED
        Serial.println(">>> 检测到动作爆发！(LED亮) <<<");
      }
    } 
    // 如果信号掉回了阈值以下
    else {
      if (isBursting) { // 只有在“从爆发变成平静”的那一刻，才打印一次
        isBursting = false;
        digitalWrite(ledPin, LOW); // 熄灭LED
        Serial.println("    信号恢复平静。(LED灭)");
      }
    }

    // ---- 4. 串口打印数据 ----
    Serial.print("Raw: ");
    Serial.print(simulatedSignal);
    Serial.print(" | Filtered: ");
    Serial.print(filteredSignal);
    Serial.print(" | State: ");
    Serial.println(isBursting ? "爆发中" : "平静");
  }
}