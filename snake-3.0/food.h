// food.h
// (C) 2018/12/03 梁明康 lmkang25@163.com

#ifndef FOOD_H
#define FOOD_H

#include "common.h"

struct list; // 前置声明

// 食物
struct food {
	int *index; // 图标索引的引用
	int x; // x坐标
	int y; // y坐标
	int flag; // 食物是否被吃, 1: true, 0: false
};

// 初始化食物
void food_init(struct food *food, int *index);

// 随机产生食物
// 食物的位置范围: rect
void rand_food(struct list *list, struct food *food, 
	struct rectangle *rect);

#endif
