#include <WiFi.h>
#include <WiFiUdp.h>

const int ledPin = 2;
unsigned long lastSendTime = 0;
int counter = 0;

// Wokwi 内置的虚拟 Wi-Fi
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// 创建一个 UDP 对象，用于发送数据
WiFiUDP udp;
// 目标 IP 和端口（Wokwi 模拟的接收端，也可以改成你自己的电脑 IP）
const char* targetIP = "192.168.1.100"; 
const int targetPort = 1234;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); 

  Serial.println("1. 启动...");
  
  // ---- 连接 Wi-Fi ----
  Serial.print("2. 正在连接 Wi-Fi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  // 循环等待 Wi-Fi 连接（这是 Wi-Fi 初始化的标准写法）
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("3. Wi-Fi 连接成功！");
  Serial.print("本机 IP 地址: ");
  Serial.println(WiFi.localIP());
  
  // 启动 UDP
  udp.begin(8888); // 本机监听端口，随便写一个
  Serial.println("4. UDP 已就绪，准备发送数据...");
}

void loop() {
  // 每 1000 毫秒（1秒）发送一次数据
  if (millis() - lastSendTime >= 1000) {
    lastSendTime = millis();
    
    // 翻转 LED 作为视觉反馈
    digitalWrite(ledPin, !digitalRead(ledPin));

    // 准备数据
    counter++;
    char txString[32];
    sprintf(txString, "BPM: %d", counter); 

    // ---- UDP 无线发送 ----
    udp.beginPacket(targetIP, targetPort); // 开始打包
    udp.print(txString);                   // 写入数据
    udp.endPacket();                       // 发送！
    
    // 同时在本地串口打印，确认发送成功
    Serial.print("已通过 Wi-Fi 发送: ");
    Serial.println(txString);
  }
  
  delay(1); // 留出时间给 Wi-Fi 后台，防止看门狗崩溃
}