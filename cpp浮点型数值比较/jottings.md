>文件更新日志
>***-version:0.1***
>***-date:2024/04/21***

参考：
[https://blog.csdn.net/slience_646898/article/details/80954464](https://blog.csdn.net/slience_646898/article/details/80954464)


<font color='red'>C/C++中除了可以表示为2的幂次以及整数数乘的浮点数可以准确表示外，其余的数的值都是近似值。</font>
例如，1.5可以精确表示，因为$1.5 = 3*2^{(-1)}$；然而3.6却不能精确表示，因为它并不满足这一规则。
所以在比较的时候需要用一个很小的数值来进行比较。（二分法的思想）当二者之差小于这个很小的数时，就认为二者是相等的了，而不能直接用== 或！=比较。这个很小的数，称为精度。
精度由计算过程中需求而定。比如一个常用的精度为1e-6.也就是0.000001所以对于两个浮点数a,b，如果要比较大小，那么常常会设置一个精度如果```fabs(a-b)<=1e-6```，那么就是相等了。 fabs是求浮点数绝对值的函数。类似的判断大于的时候，就是```if(a>b && fabs(a-b)>1e-6)```；判断小于的时候，就是```if(a<b&&fabs(a-b)>1e-6)```。

