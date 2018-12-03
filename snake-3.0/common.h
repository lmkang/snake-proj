// common.h
// (C) 2018/12/03 梁明康 lmkang25@163.com

#ifndef COMMON_H
#define COMMON_H

// 格子大小
#define CELL_SIZE 75

// 热键ID
#define HOTKEY_W_ID 1
#define HOTKEY_A_ID 2
#define HOTKEY_S_ID 3
#define HOTKEY_D_ID 4
#define HOTKEY_ALT_Q_ID 5

// 方向常量
enum direction {
	DIRECTION_UP,
	DIRECTION_LEFT,
	DIRECTION_DOWN,
	DIRECTION_RIGHT
};

// 矩形
struct rectangle {
	int x1;
	int y1;
	int x2;
	int y2;
};

#endif
