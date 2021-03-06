# ![](RackMultipart20220206-4-ab1xyt_html_c45aa9e8630acd37.png)一、任务

## 武汉大学电子设计竞赛培训题目  ![](RackMultipart20220206-4-ab1xyt_html_22d870c55dd81641.png)数字钟

以 MSP430F6638LaunchPad实验板和单片机拓展板为实验平台，利用单片机内部功能和拓展的外设，设计程序实现数字钟系统，并撰写实验报告。

# 二、要求


## 1.基本要求

  1. 利用定时器中断实现 1s 的定时功能，并驱动 LED灯使其闪烁；
  2. 完成基本的时钟功能，通过 OLED屏显示当前时间，正确走时和进位；
  3. 完成万年历功能，通过 OLED 屏显示是当前日期；
  4. 可通过矩阵按键设置当前时间和日期；
  5. 系统掉电，重新上电后的时间和日期与掉电前一样。

## 2.发挥要求

  1. 使用按键切换 12/24 时制，在 12 小时制时显示 AM/PM；
  2. 增加闹钟功能，可独立设置 3个闹钟，可查看闹钟时间并修改，可设置闹钟开关，各个闹钟可独立工作；
  3. 增加计时器功能，计时器显示单位为 s，能通过按键开启、暂停、关闭和清零计时器；
  4. 温度计功能，使用片上温度传感器测量实时温度。
  5. 其他功能，例如使用esp8266芯片联网获取时间、通过拓展板接口连接蓝牙模块与其他模块进行通信校时、连接陀螺仪模块显示数字钟姿态信息。

# 三、说明

1. 显示日期时，需要显示年月日和星期；
2. 万年历功能中，星期几可通过年月日计算出来，具体公式自行查找；

(3)24时制中，23:59:59下一时刻为 00:00:00；12时制中，11:59:59(AM)下一时刻为 12:00:00(PM)，12:59:59(PM)下一时刻为 01:00:00(PM)，11:59:59(PM)下一时刻为 00:00:00(AM)；

(4)开发平台每人一套，独立完成，同学之间可以相互交流，严禁抄袭代码。

**四、评分标准**



**设计报告**

| | **项目** | **分数** |
| --- | --- | --- |
| 系统方案 | 设计与论证、方案描述 | 3 |
| 理论分析与计算 | 定时器参数设计、矩阵按键分析、重要函数描述 | 6 |
| 电路与程序设计 | 矩阵按键设计、程序设计 | 4 |
| 测试结果 | 测试方法、测试数据、测试结果分析 | 5 |
| 设计报告结构及规范性 | 摘要、设计报告结构及正文、图表规范性 | 2 |
| 小计 | 20 |
|


**基本要求**

| 完成第(1)项 | 5 |
| --- | --- |
| 完成第(2)项 | 15 |
| 完成第(3)项 | 10 |
| 完成第(4)项 | 15 |
| 完成第(5)项 | 5 |
| 小计 | 50 |
|

**发挥要求**

| 完成第(1)项 | 10 |
| --- | --- |
| 完成第(2)项 | 20 |
| 完成第(3)项 | 10 |
| 完成第(4)项 | 10 |
| 小计 | 50 |
| **总分** | 120 |
