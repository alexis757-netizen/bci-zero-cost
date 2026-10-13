# bci-zero-cost

我的脑机接口嵌入式学习之旅。

## Day 1: ESP32 Blink 入门

- Wokwi 模拟器项目链接: ([day1_led_blink Copy - Wokwi ESP32, STM32, Arduino Simulator](https://wokwi.com/projects/477381962549865473))
- 学会了：GPIO 控制、数字输出、定时器延迟。

## Day 2: 函数封装与参数控制

- 理解了 `delay()` 中的数字直接决定亮灭的时长。
- 学会了将重复的 LED 闪烁代码封装成 `blinkAndPrint(int onTime, int offTime)` 函数。
- 通过修改函数参数（如 100, 1000），改变硬件行为，验证了函数封装的有效性。

## Day 3: ADC 与模拟信号采集基础

**学习目标：**
- 搞懂模拟信号（连续电压）与数字信号（0和1）的区别。
- 理解 ADC（模拟-数字转换器）的工作原理。
- 学会使用 `analogRead()` 读取 0V~3.3V 的电压，并在串口监视器中实时查看。

**Wokwi 电路搭建：**
- 核心元件：ESP32 开发板 + 电位器（Potentiometer，模拟传感器输出）。
- 接线逻辑：
  - 电位器 VCC -> ESP32 3V3
  - 电位器 GND -> ESP32 GND
  - 电位器 SIG (中间引脚) -> ESP32 GPIO 34 (仅输入引脚)

**代码核心逻辑：**
- `int sensorValue = analogRead(34);` // 读取 0~4095 的整数（ESP32 是 12位 ADC）
- `float voltage = sensorValue * (3.3 / 4095.0);` // 将数字读数换算为实际电压（0V~3.3V）
- `Serial.print(...)` // 将读数与电压值输出到串口监视器

**实际运行与排错记录：**
- 现象：点击运行时，Wokwi 提示 `Build Servers Busy` 或 `Failed to fetch`。
- 定位：这是 Wokwi 免费编译服务器排队/网络连接失败，并不是本地代码或电路错误。
- 结果：等待并重试后，成功运行。拖动电位器旋钮，串口成功滚动输出 `ADC Read` 与 `Voltage` 数据。
- 经验总结：第一次接触到 Windows 与 Linux 的换行符差异警告（LF will be replaced by CRLF），虽然看似报错，但不影响代码运行。

**Wokwi 项目链接：**
[点击查看 Day 3 的 ADC 模拟项目](https://wokwi.com/projects/477655855407270913)

## Day 4: 非阻塞轮询 (millis) 与多任务并行

- 理解了 `delay()` 阻塞 CPU 的致命缺陷（导致系统无法响应外界指令）。
- 掌握了 `millis()` 时间戳管理，实现了非阻塞的定时控制。
- 实现了“并行”处理三个任务：LED 闪烁、ADC 连续采样、串口实时接收指令改变闪烁频率。
- **Wokwi 项目链接**：[点击查看 Day 4 非阻塞多任务项目](https://wokwi.com/projects/477750457575512065)