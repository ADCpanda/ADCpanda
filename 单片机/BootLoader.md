## BootLoader

### 工具

#### 生成bin

fromelf  --bin  --output=bootloader.bin  Objects\led_c.axf

#### 生成 dis

fromelf  --text  -a -c  --output=led.dis  Objects\led_c.axf

## 地址跳转

1.void  (*app)(void); //定义函数指针

2.app = (*app)(void)addr；

3.app();

### 地址

由于 stm32 是 Thumb指令集，不是arm指令集

addr的bit0位为0为arm指令集，bit位为1，指令集为Thumb。

## 分析stm32启动文件

1.Set the initial SP  

// 设置初始 SP

2.Set the initial PC == Reset_Handler 

//设置初始 PC == Reset_Handler

3.Set the vector table entries with the exceptions ISR address

//设置中断向量表

4.Configure the clock system

//配置时钟系统

5.Branches to __main in the C library (which eventually calls main()).

//分支到 C 库中的 __main（最终调用 main()）

 After Reset the Cortex-M3 processor is in Thread mode,priority is Privileged, and the Stack is set to Main.

//复位后，Cortex-M3 处理器处于线程模式，;* 优先级为 Privileged，堆栈设置为 Main。

## 流程

### 1.重定位VTOR

修改VTOR寄存器，M3和M4架构的VTOR地址都为0xE000ED0C

  = addr

### 2.读addr =》sp

### 3.读（addr+4）=》pc

## 链接

