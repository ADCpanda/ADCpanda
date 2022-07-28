# linux操作

## 更新源

### 无法更新源 更新DNS

#### 1.编辑resolv.conf

sudo gedit /etc/resolv.conf

#### 2.resolv.conf中增加

1. nameserver 8.8.8.8
2. nameserver 8.8.4.4

#### 3.重启网络服务

sudo /etc/init.d/networking restart

#### 4.更新源

sudo apt-get update

#### 5.更新软件

sudo apt-get upgrade

## bad interpreter:No such file or directory的原因

### 错误分析

 因为操作系统是windows，我在windows下编辑的脚本，所以有可能有不可见字符。从你的脚本及报告的错误看来, 很有可能是你的**脚本文件是DOS格式的, 即每一行的行尾以\r\n来标识**, 其ASCII码分别是0x0D, 0x0A.



#### （1）vi filename
然后用命令:set ff?
可以看到dos或unix的字样. 如果的确是dos格式的, 那么你可以用:set ff=unix把它强制为unix格式的, 然后存盘退出. 再运行一遍看.

####  （2）用joe filename

如果是DOS格式的, 那么行尾会有很多绿色的^M字样出现. 你也可以用上述办法把它转为UNIX格式的.
####  （3） 用od -t x1 filename

如果你看到有0d 0a 这样的字符, 那么它是dos格式的, 如果只有0a而没有0d, 那么它是UNIX格式的, 同样可以用上述方法把它转为UNIX格式的.

#### 解决方法

用命令**:set ff?**查看是doc还是unix格式，如果是dos格式，用命令**:set ff=unix**转化为unix格式。