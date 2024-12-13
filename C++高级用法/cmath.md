# cmath库内容：

<cmath>头文件中声明了一系列函数来计算常见的数学运算和变换：

- abs: **计算绝对值，包括整数类型**；
- fabs: **计算绝对值，不包括整数类型**；
- fma(x,y,z):x*y+z;
- sin: 正弦；
- asin: 反正弦；
- sinh: 双曲正弦；
- asinh: 双曲反正弦；
- cos: 余弦；
- acos: 反正弦；
- cosh: 双曲余弦；
- acosh: 双曲反余弦；
- tan：正切；
- atan：反正切；
- atan2: 反正切；
- tanh: 双曲正切；
- atanh: 双曲反正切；
- sqrt: 计算平方根；
- cbrt: **计算立方根**；
- hypot: **计算两个数平方的和的平方根**；
- pow：幂运算；
- ceil: 不小于给定值的最近整数；
- floor: 不大于给定值的最近整数；
- fmod: 两数除法操作的余数(rounded towards zero)；
- trunc: 不大于给定值的最近整数；
- round: **舍入取整**；
- lround: **舍入取整, 返回long int**；
- llround: **舍入取整, 返回long long int**；
- nearbyint: 使用当前的舍入模式取整(fegetround())；
- remainder: 两数除法操作的余数(rounded to nearest)；
- remquo: 两数除法操作的余数；
- rint: 使用当前的舍入模式取整(fegetround())；
- lrint: 使用当前的舍入模式取整(fegetround()),返回long int；
- llrint: 使用当前的舍入模式取整(fegetround())，返回long longint；
- exp: ex;
- frexp: 将一个浮点数分解为有效数(significand)及以2为底的幂(x = significand* 2exp);
- ldexp: x *2exp;
- exp2: $2^x$;
- expm1: $e^{x-1}$;
- scalbn: x *FLT_RADIXn;
- scalbln: x* FLT_RADIXn;
- log: ln(x);
- log10: log10(x);
- modf: 将一个浮点数分解为整数及小数部分；
- ilogb: 返回以FLT_RADIX为底，|x|的对数值，返回值为整数；
- log1p: ln(1+x);
- log2: log2(x);
- logb: 返回以FLT_RADIX为底，|x|的对数值，返回值为浮点数；
- erf: 误差函数；
- erfc: 互补(complementary)误差函数；
- tgamma: 伽玛函数；
- lgamma: log-伽玛函数；
- copysign(x,y):返回x的值及y的正负符号组成的浮点数；
- nan: Generatequiet NaN;
- nextafter(x,y): 返回x之后y方向上的下一个可表示值；
- nexttoward(x,y): 返回x之后y方向上的下一个可表示值；
- fdim(x,y): Thefunction returns x-y if x>y, and zero otherwise;
- fmax: **返回较大的值**;
- fmin: **返回较小的值**;
- fpclassify:为浮点值归类，返回一个类型为int的值；
- isfinite: 检测是否是有限值；
- isinf: 检测是否是无穷大值；
- isnan: 检测是否是非数型；
- isnormal: 检测是否是normal值，neitherinfinity, NaN, zero or subnormal；
- signbit: 检测是否是负数；
- isgreater: 检测第一个数是否大于第二个数；
- isgreaterequal:检测第一个数是否大于或等于第二个数；
- isless: 检测第一个数是否小于第二个数；
- islessequal:检测第一个数是否小于或等于第二个数；
- islessgreater:检测第一个数是否不等于第二个数；
- isunordered:检测两个浮点数是否是无序的.

# 不常用函数：

`fmax` 、`fmin` 、`cbrt` 、`hypot`

# cmath库易错内容演示：
