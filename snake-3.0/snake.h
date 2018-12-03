// snake.h
// (C) 2018/12/03 梁明康 lmkang25@163.com

#ifndef SNAKE_H
#define SNAKE_H

#include "common.h"

struct food; // 前置声明

// 带头节点的双向循环链表
struct list {
	int index; // 图标索引
	int x; // x坐标
	int y; // y坐标
	struct list *prev;
	struct list *next;
};

// 初始化链表
struct list *list_init(void);

// 在链表尾部插入
void list_append(struct list *list, struct list *ele);

// 蛇初始化
struct list *snake_init(int *index, int x, int y);

// 蛇移动
void snake_move(struct list *list, enum direction direction);

// 蛇死亡
int snake_die(struct list *list, struct rectangle *rect);

// 蛇吃掉食物
void snake_eat_food(struct list *list, struct food *food);

#endif
