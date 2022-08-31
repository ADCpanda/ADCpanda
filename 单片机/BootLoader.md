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

### 2.读addr =>sp

### 3.读（addr+4）=>pc

## 链接

使用散列文件，定位到RAM中，实际程序在flash里，程序里只能使用相对偏移，保证不会出错，避免使用 *p = func（）这种，绝对偏移，会找不到函数。

### 为什么要拷贝？

拷贝到RAM中，即可使用绝对偏移，因为可以找到文件

```c
Reset_Handler   PROC
				EXPORT  Reset_Handler             [WEAK]
                IMPORT  mymain
				IMPORT  copy_myself
				IMPORT |Image$$ER_IROM1$$Length|
                adr r0, Reset_Handler  ; r0=0x0800C000
				bic r0, r0, #0xff
				
				ldr r1, =__Vectors ; r1=0x20000000  得到_Vectors的链接地址
				ldr r2, = |Image$$ER_IROM1$$Length|  ; LENGTH  
				;LDR SP, =(0x20000000+0x10000)
				BL copy_myself
				ldr pc, =mymain

                ENDP
```

```c
r0 ：from     adr 得到当前指令Reset_Handler的当前地址0x0800C008
              bic r0, r0, #0xff 把低8位清掉得到0x0800C000
r1 : to       r1=0x20000000  得到_Vectors的链接地址
r2 : len      |Image$$ER_IROM1$$Length|  得到长度


void copy_myself(int *from, int *to, int len)
{
	// 从哪里到哪里, 多长 ?
	int i;
	for (i = 0; i < len/4+1; i++)
	{
		to[i] = from[i];
	}
}

```

这个时候程序还在flash上运行，还没有跳到ram中

不要再使用相对跳转，不然会跳回flash，所以把BL mymain （相对），改成

ldr pc， = mymain 从这里就跳到内存里了

![第二个程序](C:\git_learn\learngit\单片机\pic\第二个程序.png)

## bootloader copy app

问题：1源

​           2.目的地址

​		   3.长度

在APP中加入头部，头部里有：

1.加载地址 ： copy to RAM

2.入口地址：我需要跳转到哪里去运行你app第一条指令

3.长度

4.CRC

bootloader要做的事

1.读0x0800C000得到header

2.解析头部

3.读app.bin 存到RAM

### 工具

mkimage.exe                                 

$./mkimage.exe -n "stm32f103_app" -a 0x20000000 -e 0x20000008 -d app.bin app_with_uboot_header.bin

使用这个结构体，这个头部结构体占64个字节

```c
typedef struct image_header {
__be32			    ih_magic;	/* Image Header Magic Number: 镜像魔数, 0x27051956为
                                    uimage的头部开始值 */
	__be32			ih_hcrc;	/* Image Header CRC Checksum: 整个64字节头的crc校验码 */
	__be32			ih_time;	/* Image Creation Timestamp: uImage的创建时间戳 */
	__be32			ih_size;	/* Image Data Size: zImage镜像的大小 */
	__be32			ih_load;	/* Data Load  Address: 内核加载地址 */
	__be32			ih_ep;		/* Entry Point Address: zImage的入口位置 = lode + 64，也是
                                   内核运行地址，“theKernel”指向该地址，说明这里藏着进入第一个
                                   函数-解压函数 */
	__be32			ih_dcrc;	/* Image Data CRC Checksum: 整个zImage的crc校验码 */
	uint8_t		    ih_os;		/* Operating System: 操作系统代码 */
	uint8_t		    ih_arch;	/* CPU architecture: 芯片类型,cpu架构 */
	uint8_t		    ih_type;	/* Image Type: 镜像类型 */
	uint8_t		    ih_comp;	/* Compression Type: 压缩类型 */
	uint8_t		    ih_name[IH_NMLEN];	/* Image Name: 32字节的名字 */
} image_header_t;
```

所以读到的程序位置在 new_pos = pos+sizeof(image_header_t);



## 对于不支持修改Vector地址

对于ST家的芯片支持修改硬件Vector地址，就修改

不能修改的，需要跳转

### 绝对跳转

因为bootloader 重定位里可能用到的变量存在ram中，不巧刚好被app.bin破坏

```c
static struct vectors *new_vector  _attribute_((at(0x00030000)));

```



# 注意

CPU只能在XIP（execute in place）设备执行，对于SPI的Flash不能执行

需要注意大小端的问题

制作出来的head是大端

所以需要转换成小端
