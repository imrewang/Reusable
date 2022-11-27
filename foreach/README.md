## 一、作用

```C++
listTemp.append("aaa");
listTemp.append("bbb");
listTemp.append("ccc");

foreach(strTemp1,listTemp)
{
    strTemp2= strTemp1;
}
```

listTemp会把自己的每个项，依次赋值给strTemp1。本例中，listTemp共有三项，foreach会循环三次，strTemp1在这三次循环中，依次被赋值“aaa”，“bbb”，“ccc”。

## 二、使用样例

```
foreach(string size, compositeState) {
	complexFlyWeight->Add(size, this->Factory(size));
}
```

## 三、说明
C++ 完成
