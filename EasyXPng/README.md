# EasyXPng

### 一、功能

easyx输出背景透明图片

### 二、使用样例

```c++
Rocket rocket;  // 定义火箭对象
...
loadimage(&im_rocket, _T("rocket.png")); // 导入火箭图片
...
// 窗口左上角显示life个火箭图片，表示火箭生命数
for (int i = 0; i < life; i++){
	putimagePng(i * width * 0.9, 0, &im_rocket);
}
```

### 三、说明

EasyXPng1.h是putimagePng声明和定义在一起，可能会出现链接错误

建议使用EasyXPng.h和EasyXPng.cpp
