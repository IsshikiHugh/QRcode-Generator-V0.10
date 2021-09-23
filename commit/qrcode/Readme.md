QRcode Generator V0.10 
===========================
用于生成 Alphanumeric Mode 的 version 1~2 的二维码

## 初始化与使用

运行 `compile.bat` 后将在源目录下生成可执行文件 `run.exe`

## 目录结构描述

```
├── Readme.md                   // readme
├── compile.bat                 // 编译脚本
├── src                         // 源文件
│   ├── main.cpp                // main
│   ├── table.cpp               // 打表.cpp
│   ├── table.h                 // 打表.h
│   ├── encode.cpp              // 字符内容转01数据流.cpp
│   ├── table.h                 // 字符内容转01数据流.h
│   ├── calculate_ECcode.cpp    // 计算纠错码.cpp
│   ├── calculate_ECcode.h      // 计算纠错码.h
│   ├── fill_matrix.cpp         // 矩阵填充.cpp
│   ├── fill_matrix.h           // 矩阵填充.h
│   └──                         // EoF
└── doc.md                      // 文档
```