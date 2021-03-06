# CSAPP阅读

## 参考资料

[读薄csapp博客](https://wdxtub.com/csapp/thin-csapp-0/2016/04/16/)
[csapp gitbook电子书](https://hansimov.gitbook.io/csapp/)


[csapp 英文原版pdf](https://github.com/wangmu89/Book-CSAPP/blob/master/_Attachments/Computer_Systems_A_Programmers_Perspective(3rd).pdf)
[编程书籍汇总](https://github.com/imarvinle/awesome-cs-books#%E8%AE%A1%E7%AE%97%E6%9C%BA%E7%B3%BB%E7%BB%9F)

## 学习检查点
> 本环节可以理解成大学学习中的作业， 目的是为了让学习真正产生效果。 作业会从讨论和博客，实验两个角度入手， 考察理解和实践的能力。 每个项目的checkList由大家补充投票定义， 靠自觉完成。


书本阅读讨论和博客，大概每周/双周一篇
TODO

实验
TODO


## 个人笔记
> 说明:本文就是阅读[《读薄csapp》](https://wdxtub.com/csapp/thin-csapp-1/2016/04/16/)系列博客的再抽象、理解记录。适合

### 第一章
#### 学习目标

1. 理解计算机系统的复杂与和理论抽象描述的不同
1. 理解内存中数据的保存形式，以及这种方式的好处以及限制
1. 注意避开一些常见的关于计算机的迷思
1. 区别整型和浮点数的表达机制，并理解为什么会有这种差异
1. 简单理解溢出出现的条件

**计算机不只是执行程序的机器**
> 现代计算机的冯诺依曼的结构

**很多东西不像看起来那么简单**
> 1. 时空复杂度， 在多线程甚至分布式并行计算的条件下， 需要特别考虑，比如是否能拆分并行运算， 是否会线程安全。
> 2. 计算机的数学运算存在溢出和精度问题
> 3. 很多算法，思想的设计， 往往都很难最优， 而是在限制下比较好的一种**权衡**，比如时间换空间，锁机制。


**内存里多的是我们不知道的事**
> 1. 内存问题在实践中特别容易发生，排查起来也非常困难（典型的是内存泄漏、野指针、悬垂指针，多线程问题）

#### 比特心生

计算机的任何指令、数据都是二进制表示的。而现实生活中的数字往往是10进制表示的。而为了让2进制读起来更快、写起来更少、记起来也不会太多， 2进制4位为一组，生成了16进制。
也就是说我们需要背一下16进制。但实际上，16进制基本上和10进制类似， 所以2进制到16进制的转换一般经过10进制。
比如1-9 -> 1-9, 10-15 -> A-F

而二进制的4位， 为了更好算有一点， 我们拆成2组，前2位一组，后2位1组。
比如$1011=10<<2+11=10*2+1=4*2+3=8+3=11$

这样拆分的好处就是，我们只需要背下2位二进制的映射就行了。也就是


|2机制b|10进制d|16进制h|
|-|-|-|
|1001|2*4+1|9
|1010|2*4+2|A
|1011|2*4+3|B
|1100|3*4+0|C
|1101|3*4+1|D
|1110|3*4+2|E
|1111|15|F
而对于10进制与16进制的转换，我们只要管A-F 与 10-15的转换。好在我们从小写选择题以及让我们建立了A-E -> 1-5 -> 1+9-4+9 -> 10-14的映射。 最后剩下个F，就是1111就是15啊，多好记。（/wink)

#### 整数
**整型表示的特点**

我们知道对于计算机里的二进制，有符号数和无符号数改变的只是该部分内存的类型，而不改变吗值本身。

所以为了让相同位数w的无符号（$0\to2^w-1)$和有符号数能够比较容易地对应上，
我们直接让一半数$0 \to 2^{w-1}-1$的解释不变，
剩下的一半数$2^{w-1}\to2^w-1$， 让他直接往回调一圈(即$-2^w$)，变成$-2^{w-1}\to-1$

这样做的好处有
1. 小的数在有符号和无符号的数在$0 \to 2^{w-1}-1$上完全一致
2. 无符号数越小，对应的有符号数的负数也越小。
3. 有符号数的负数$x\%2^{w} == x+2^{w}$

![](https://wdxtub.com/images/csapp/14609257940557.jpg)

**C语言中signed和unsigned的比较**

2个原则
1. C语言中常量默认是有符号数, 除非显式加上`U`后缀
2. 有符号和无符号数做运算时，会都当做无符号数做比较比如$-1<0, -1>0U$


**截取和拓展**

位多的数往位低的数转换时，需要截取保留低位， 相反需要拓展高位。
截取和拓展其实从十进制看来是很直觉的，即向下兼容。
- 对于拓展，其实就是10进制保持不变（也即正数给补0， 负数给补1)
- 对于截取，不区分正负数直接截取l(比如下面代码的结果)
```c++
#include <cstdio>
int main() {
    int a = 0x7fffffff;
    short b = (short)a;
    int c = 0xffffffff;
    short d = (short)c;
    int e = 0xffff7fff;
    short f = (short)e;
    printf("%d->%d, %d->%d, %d->%d", a,b,c,d,e,f);
    return 0;
}
//2147483647->-1, -1->-1, -32769->32767
```

#### 浮点数
浮点数这个名字起得很不错，其实就是在整数的<u>**位中间加了个点**</u>。
点左边的叫整数部分，右边的叫小数部分。
也可以看成是一个整数，除上了$2^{t} (t是小数的位数)$

**IEEE 浮点数标准**
$value=(-1)^{s}M2^{E}$
![](https://wdxtub.com/images/csapp/14609515849125.jpg)
$E_{10}=exp_{2}, M=1+frac_2(frac表示的小数是0.x...., x\not ={0})$
其中exp是一个有符号数E的移码。

**浮点数的无穷和0**
- 浮点数的范围
浮点数其实就是二进制的科学计数法。 浮点数的标识范围取决于指数的位数， 可以通过改变指数的大小， 来调整数值部分浮点的位置。那当一个运算，指数部分超过了指数的表示范围。则为无穷（全1）或0（全0）。也就是绝对值太大和绝对值太小的数，无法表示了。 这是浮点数的范围

- 浮点数的精度
浮点数的精度取决于数值部分的位数。假设有f位， 那么比$2^{-f}$还小的数将无法表示。 并且由于指数和浮点的位置可以相互影响。我们往往会尽量地把整数部分左移（同时减少指数）来保证更高的精度（这也是IEEE的标准）

**舍入**
左移溢出， 右移舍入。


**浮点数加法**

**浮点数乘法**

#### 数据在内存中的形式

关于大端和小端如何记忆
1. 关于为什么要有小端，如果熟悉两个二进制按照位 进行加减乘除的同学（cpu的整数加法实现或者c实现大数运算）知道，计算机都是从一个数的低位开始运算，并不断传递进位的。那么小端其实就是这样设计的。这也就是为什么， 常见的x86和arm处理器都采用小端规则。
   > 我们假设一个8个字节的整数， 32位的计算机， 每次只能取4个字节的数据，为了完成两个8字节整数的运算，我们需要先取两个数第4个字节进行运算。结果存入结果内存的低四个字节，进位参与高4个字节的运算，结果存入高四个字节。这是一个比较直觉的设计。
   > **另外小端也只是字节之间是从低到高**。 字节内部其实还是从高位往低位的。 因此每个字节内部也是方便书写和阅读的。
```c++
int main(){
    int x = 0x00007fab;
    unsigned char *point = (unsigned char *)&x;
    size_t len = sizeof(int)/sizeof(char);
    for (size_t i=0;i<len;i++) {
        printf("%p\t0x%.2x\n", point+i, *(point+i));
    }
    return 0;
}
// 0x7ffeea51c370  0xab
// 0x7ffeea51c371  0x7f
// 0x7ffeea51c372  0x00
// 0x7ffeea51c373  0x00
```

2. 大端其实就是便于书写和阅读。


### 第二章：机器指令和程序

#### 学习目标
1. 了解基本的 CPU 架构，以及 CPU 如何进行指令计算
2. 掌握基本的汇编语法，常见的寻址方式和运算方式
3. 理解如何通过条件代码进行流程控制
4. 理解过程调用和递归的底层实现机制
5. 理解数据在内存中的存储方式
6. 了解程序在内存中的组织形式以及缓冲区溢出漏洞攻击
7. 利用代码执行的机制来优化已有代码

addtion: 动态调试和逆向实践

#### 基础知识
**从C到机器代码**
1. 汇编代码是机器指令的翻译，是可读形式。因此从汇编入手我们可以更好地指导机器时如何运作的。
2. C语言代码经过编译，汇编，静态链接变成真正的可执行程序
3. 汇编代码一般由操作符+1~3个逗号隔开的操作数组成。
4. 处理器能够执行的操作十分有限，简单来说只有三种：存取数据、计算和传输控制
   1. 事实上处理器由运算器（LRU）、控制器、以及缓存组成。自然对应着上述的三个功能。当然对于处理器来说，存取数据是指向内存存取数据。但是对于汇编代码会涉及到向某个寄存器存储数据
   2. 
x86-64的几个通用寄存器的名字解释,其中r是64位的寄存器，e是32位的寄存器。 r->egister,p->point
- %rax(%eax) 用于做累加 a->acc， 
- %rcx(%ecx) 用于计数 c->count
- %rdx(%edx) 用于保存数据 d指的是？？
- %rbx(%ebx) 用于做内存查找的基础地址 b->base指的是内存查找的基地址
- %rsi(%esi) 用于保存源索引值 si -> source index
- %rdi(%edi) 用于保存目标索引值 di -> destination index
- %rsp(%esp) 栈指针 sp -> stack point
- %rbp(%ebp) 基指针（与rbx不同的是rbp一般用于指令寻址？？）bp -> base point

操作数分为3种基本类型
1. Imm $0x5
2. Reg %rax
3. Mem (%rdx)  ()表示访存，即M[%rdx]， 内存中%rdx指向地址的内容。
> 这里有一点需要注意， 计算机看到%rax这样的寄存器的时候，事实上就是%rax里面的地址（也就是寄存器存的值），而非寄存器的地址。
> 而在内存中，0x00001abc这样的内存地址则是地址本身。
> 举个例子， 比如%rdx存放着0x00001abc，0x00001abc存放着0x1ABC的数据
> 那%rdx == 0x00001abc, (%rdx) == (0x00001abc) == (0x1ABC)


寻址的通用表达式（可以缺省）`D(Rb, Ri, S) -> Mem[Reg[Rb]+S*Reg[Ri]+D]`， 最基本的的就是(Rb)只有寄存器的地址值。

了解了寻址之后，我们来看看运算指令，这里以 leaq 指令为例子。具体格式为 leaq Src, Dst，其中 Src 是地址的表达式，然后把计算的值存入 Dst 指定的寄存器，也就是说，无须内存引用就可以计算，类似于 p = &x[i];。我们来看一个具体的例子，假设一个 C 函数是：

long m12(long x)
{
    return x * 12;
}
对应的汇编代码为：

leaq (%rdi, %rdi, 2), %rax # t <- x+x*2
salq $2, %rax              # return t << 2
可以看到是直接对 %rdi 寄存器中存的数据（地址）进行运算，然后赋值给 %rax。最后给出一些常见的算术运算指令，注意参数的顺序，而且对于有符号和无符号数都是一样的，

> 这里其实做了一个化简操作 x*12 -> (x+x*2)*4 -> 是把x放到了%rdi中， 然后 (%rdi, %rdi, 2) 就被翻译成 x+2*x

下面的汇编指令可以参照着(汇编语言指令英文全称对照表)[https://www.bilibili.com/read/cv6166473]进行阅读

