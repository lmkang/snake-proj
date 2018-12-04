// food.c
// (C) 2018/12/03 梁明康 lmkang25@163.com

#include <time.h>
#include <stdlib.h>
#include "food.h"
#include "snake.h"

// 初始化食物
void food_init(struct food *food, int *index) {
	srand((unsigned int) time(NULL)); // 时间种子
	food->index = index;
	food->flag = 1; // 默认食物被吃, 因此才能继续产生食物
}

// 随机产生食物
// 位置不能与list重叠
void food_rand(struct list *list, struct food *food, 
	struct rectangle *rect) {
	
	int cellCountX = (rect->x2 - rect->x1) / CELL_SIZE;
	int cellCountY = (rect->y2 - rect->y1) / CELL_SIZE;
	if(food->flag) {
		food->x = rect->x1 + (rand() % cellCountX) * CELL_SIZE;
		food->y = rect->y1 + (rand() % cellCountY) * CELL_SIZE;
		int cover = 0; // 标识食物和list是否重叠, 1: 重叠, 0: 不重叠
		struct list *p = list->next;
		while(1) {
			p = list->next;
			while(p != NULL && p != list) {
				if(p->x == food->x && p->y == food->y) {
					food->x = rect->x1 + (rand() % cellCountX) * CELL_SIZE;
					food->y = rect->y1 + (rand() % cellCountY) * CELL_SIZE;
					cover = 1;
					break;
				}
				p = p->next;
			}
			if(!cover) {
				break;
			}
			cover = 0;
		}
		food->flag = 0;
		*food->index = *food->index + 1;
	}
}
