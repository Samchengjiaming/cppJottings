>文件更新日志
>***-version:0.1***
>***-date:2024/04/22***

参考：
[https://www.cnblogs.com/burner/p/gcc-bian-yiccde-si-ge-guo-cheng.html](https://www.cnblogs.com/burner/p/gcc-bian-yiccde-si-ge-guo-cheng.html)


cpp从源码到可执行程序，经历四个过程：预处理、编译、汇编和链接，前三步由使用编译器来完成、链接由连接器来完成。
- 编译器将编译工作主要分为预处理,编译和汇编三步
- 连接器的工作是把各个独立的模块链接为可执行程序
- 静态链接在编译期完成,动态链接在运行期完成

## 预处理阶段
预处理完成的工作：
- 处理所有的注释，以空格代替
- 将所有的```#define```删除， 并且展开所有的宏定义
- 处理条件编译指令```#if, #ifdef, #elif, #else, #endif```处理条件编译指令
- 处理```#include```，展开被包含的文件
- 保留编译器需要使用的```#pragma```指令

C语言代码在交给编译器之前，会先由预处理器进行一些文本替换方面的操作，例如宏展开、文件包含、删除部分代码等。在正常的情况下，GCC 不会保留预处理阶段的输出文件，也即 .i 文件。然而，可以利用 -E 选项保留预处理器的输出文件，以用于诊断代码。-E选项指示 GCC 在预处理完毕之后即可停止。

```c++
//complie.cpp
#include <iostream>
#include <cmath>
using namespace std;
int main()
{
    // 定义一个注释
    #define DAA 100 
    std::cout<<DAA<<std::endl;
    int num=101;
    system("pause");
    return 0;
}
```
对上面的cpp代码使用下面的命令进行预处理：
```
c++ -E complie.cpp > complie.i  # 预处理complie.cpp并且输出到complie.i文件种
```
得到的complie.i文件有28000+行，编译器会把包含的iostream和cmath两个库展开。
```c++
//complie.i
...

# 3 "complie.cpp" 2
# 4 "complie.cpp"
using namespace std;
int main()
{


    std::cout<<100<<std::endl;
    int num=101;
    system("pause");
    return 0;
}
```
发现注释被替换为空格，宏定义被替换为变量。

如果使用-C选项阻止预处理器删除源文件和头文件中的注释。
```
c++ -E -C complie.cpp > complie.i  # 预处理complie.cpp并且输出到complie.i文件种 大写C表示不取消注释
```

## 编译阶段
编译阶段进行的工作：
- 对预处理文件进行一系列词法分析,语法分析和语义分析
- 词法分析主要分析关健字,标示符,立即数等是否合法
- 语法分析主要分析表达式是否遵循语法规则
- 语义分析在语法分析的基础上进一步分析表达式是否合法
- 分析结束后进行代码优化生成相应的汇编代码文件

编译器的核心任务是把C程序翻译成机器的汇编语言（assembly language）。
汇编语言是人类可以阅读的编程语言，也是相当接近实际机器码的语言。每种 CPU 架构都有不同的汇编语言。实际上，GCC 是一个适合多种 CPU 架构的编译器，不会把C程序语句直接翻译成目标机器的汇编语言，而是在输入语言和输出汇编语言之间，利用一个中间语言，称为 RegisterTransfer Language（简称 RTL，寄存器传输语言）。借助于这个抽象层，在任何背景下，编译器可以选择最经济的方式对给定的操作编码。通常情况下，GCC 把汇编语言输出存储到临时文件中，并且在汇编器执行完后立刻删除它们。但是可以使用-S选项，让编译程序在生成汇编语言输出之后立刻停止,而不删除临时文件。

针对上面的代码进行编译：
```
c++ -S complie.cpp > complie.s #直接从源文件生成汇编代码文件
c++ -S complie.i > complie.s # 从预处理的文件生成汇编代码文件
```
生产的汇编代码如下：
```
	.file	"complie.cpp"
	.text
	.section .rdata,"dr"
_ZStL19piecewise_construct:
	.space 1
.lcomm _ZStL8__ioinit,1,1
	.def	__main;	.scl	2;	.type	32;	.endef
.LC0:
	.ascii "pause\0"
	.text
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$48, %rsp
	.seh_stackalloc	48
	.seh_endprologue
	call	__main
	movl	$100, %edx
	movq	.refptr._ZSt4cout(%rip), %rcx
	call	_ZNSolsEi
	movq	.refptr._ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_(%rip), %rdx
	movq	%rax, %rcx
	call	_ZNSolsEPFRSoS_E
	movl	$101, -4(%rbp)
	leaq	.LC0(%rip), %rcx
	call	system
	movl	$0, %eax
	addq	$48, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.def	__tcf_0;	.scl	3;	.type	32;	.endef
	.seh_proc	__tcf_0
__tcf_0:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	leaq	_ZStL8__ioinit(%rip), %rcx
	call	_ZNSt8ios_base4InitD1Ev
	nop
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.def	_Z41__static_initialization_and_destruction_0ii;	.scl	3;	.type	32;	.endef
	.seh_proc	_Z41__static_initialization_and_destruction_0ii
_Z41__static_initialization_and_destruction_0ii:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	movl	%ecx, 16(%rbp)
	movl	%edx, 24(%rbp)
	cmpl	$1, 16(%rbp)
	jne	.L6
	cmpl	$65535, 24(%rbp)
	jne	.L6
	leaq	_ZStL8__ioinit(%rip), %rcx
	call	_ZNSt8ios_base4InitC1Ev
	leaq	__tcf_0(%rip), %rcx
	call	atexit
.L6:
	nop
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.def	_GLOBAL__sub_I_main;	.scl	3;	.type	32;	.endef
	.seh_proc	_GLOBAL__sub_I_main
_GLOBAL__sub_I_main:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	movl	$65535, %edx
	movl	$1, %ecx
	call	_Z41__static_initialization_and_destruction_0ii
	nop
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.section	.ctors,"w"
	.align 8
	.quad	_GLOBAL__sub_I_main
	.ident	"GCC: (x86_64-posix-sjlj-rev0, Built by MinGW-W64 project) 8.1.0"
	.def	_ZNSolsEi;	.scl	2;	.type	32;	.endef
	.def	_ZNSolsEPFRSoS_E;	.scl	2;	.type	32;	.endef
	.def	system;	.scl	2;	.type	32;	.endef
	.def	_ZNSt8ios_base4InitD1Ev;	.scl	2;	.type	32;	.endef
	.def	_ZNSt8ios_base4InitC1Ev;	.scl	2;	.type	32;	.endef
	.def	atexit;	.scl	2;	.type	32;	.endef
	.section	.rdata$.refptr._ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, "dr"
	.globl	.refptr._ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_
	.linkonce	discard
.refptr._ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_:
	.quad	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_
	.section	.rdata$.refptr._ZSt4cout, "dr"
	.globl	.refptr._ZSt4cout
	.linkonce	discard
.refptr._ZSt4cout:
	.quad	_ZSt4cout
```

## 汇编阶段
汇编阶段工作：
- 汇编器将汇编代码转变为机器可以执行的指令
- 每个汇编语句几乎都对应一条机器指令

汇编阶段生成的目标文件是一种中间文件或者临时文件，如果不设置该选项，gcc一般不会保留目标文件，可执行文件生成完成后就自动删除了。
注意，使用-c选项表示只编译源文件，而不进行链接，因此，对于链接中的错误是无法发现的。
使用下面的命令生成二进制指令文件：
```
c++ -c complie.s > complie.o
```

## 链接阶段
连接器的主要作用是把各个模块之间相互引用的部分处理好,使得各个模块之间能够正确的衔接
- 静态链接
    静态链接使用静态库进行链接，生成的程序包含程序运行所需要的全部库，可以直接运行，不过静态链接生成的程序比较大。
- 动态链接
    动态链接使用动态链接库进行链接，生成的程序在执行的时候需要加载所需的动态库才能运行。动态链接生成的程序体积较小，但是必须依赖所需的动态库，否则无法执行。
通过下面的命令实现链接步骤得到exe可执行文件：
```
c++ complie.o -o complie.exe
```