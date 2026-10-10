# bci-zero-cost

我的脑机接口嵌入式零成本学习之旅。

## Day 1: ESP32 Blink 入门
- Wokwi 模拟器项目链接: (把你昨天那个Wokwi链接粘贴在这里)
- 学会了：GPIO 控制、数字输出、定时器延迟。

## Day 2: 函数封装与参数控制
- 理解了 `delay()` 中的数字直接决定亮灭的时长。
- 学会了将重复的 LED 闪烁代码封装成 `blinkAndPrint(int onTime, int offTime)` 函数。
- 通过修改函数参数（如 100, 1000），改变硬件行为，验证了函数封装的有效性。