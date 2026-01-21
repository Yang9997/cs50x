int temp[pair_count] = {0};pair_count是个有值的全局变量，为什么会报错？是C版本不支持这种写法吗？

1. 并不是“常量表达式” (Global Context) 如果 int temp[pair_count] = {0}; 写在函数外部（全局作用域），C 语言规定全局数组的大小必须在编译时确定。pair_count 即使被初始化了，也只是一个变量，不能用来定义全局数组的大小。

解决方法：#define  PAIR_COUNT 100

2. 变长数组 (VLA) 不支持初始化 (Local Context) 如果这段代码写在函数内部：

C89/C90: 不支持变长数组，数组长度必须是具体的数字或宏。

C99/C11: 虽然支持变长数组（Variable Length Array, VLA），即可以用变量定义数组长度，但是标准规定 VLA 不能使用 {...} 进行初始化。

注意：在 C++ 中，如果 pair_count 被声明为 const int，这段代码通常是合法的。但在 C 语言中，const int 仅仅是“只读变量”，并不等同于编译时常量。此处代码出现的问题是2. 支持变成数组但是不能{}这样初始化。解决方法是，malloc或者for。
