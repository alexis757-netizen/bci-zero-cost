#include <WiFi.h>
#include <WiFiUdp.h>

const int ledPin = 2;
unsigned long lastSampleTime = 0;
const int sampleInterval = 10; // 每10毫秒采一次，即 100Hz 采样率

// 模拟的三个脑电通道数据
int ch1 = 0;
int ch2 = 0;
int ch3 = 0;

// Wokwi 内置虚拟 Wi-Fi
const char* ssid = "Wokwi-GUEST";
const char* password = "";
WiFiUDP udp;
const char* targetIP = "192.168.1.100"; 
const int targetPort = 1234;

// 全局变量：存放打包后的字符串
char txBuffer[64]; 

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); 

  Serial.println("1. 启动...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n2. Wi-Fi 连接成功！");
  udp.begin(8888); 
  Serial.println("3. UDP 就绪，开始发送多通道数据...");
}

void loop() {
  // 每 10ms（100Hz）执行一次采样和发送
  if (millis() - lastSampleTime >= sampleInterval) {
    lastSampleTime = millis();

    // ---- 1. 生成 3 个通道的模拟数据 ----
    ch1 = random(100, 200);
    ch2 = random(200, 300);
    ch3 = random(300, 400);

    // ---- 2. 数据打包（Packing） ----
    // 将三个整数拼成 "ch1,ch2,ch3" 的格式
    sprintf(txBuffer, "%d,%d,%d", ch1, ch2, ch3);

    // ---- 3. 通过 Wi-Fi 发送 ----
    udp.beginPacket(targetIP, targetPort);
    udp.print(txBuffer);
    udp.endPacket();

    // ---- 4. 模拟接收端：解析数据（Parsing） ----
    int r1 = 0, r2 = 0, r3 = 0;
    // sscanf 会按照 "%d,%d,%d" 的格式，从 txBuffer 中提取数字
    sscanf(txBuffer, "%d,%d,%d", &r1, &r2, &r3);

    // ---- 5. 打印验证 ----
    // 每 100 次打印一次，防止串口刷屏太快卡死
    static int printCount = 0;
    if (printCount++ % 100 == 0) {
      Serial.print("打包发送: ");
      Serial.print(txBuffer);
      Serial.print("  |  解析后 -> 通道1: ");
      Serial.print(r1);
      Serial.print(", 通道2: ");
      Serial.print(r2);
      Serial.print(", 通道3: ");
      Serial.println(r3);
      
      // LED 闪烁作为数据流的指示
      digitalWrite(ledPin, !digitalRead(ledPin));
    }
  }
  delay(1); 
}