// snake.c
// (C) 2018/12/03 梁明康 lmkang25@163.com

#include <stdlib.h>
#include "snake.h"
#include "food.h"

// 初始化链表
struct list *list_init(void) {
	struct list *list = (struct list *) malloc(sizeof(struct list));
	list->index = -1;
	list->x = -1;
	list->y = -1;
	list->next = NULL;
	return list;
}

// 在链表尾部插入
void list_append(struct list *list, struct list *ele) {
	if(list != NULL) {
		struct list *prev = list;
		struct list *p = list->next;
		while(p != NULL && p != list) {
			prev = p;
			p = p->next;
		}
		prev->next = ele;
		ele->prev = prev;
		ele->next = list;
		list->prev = ele;
	}
}

// 蛇初始化
struct list *snake_init(int *index, int x, int y) {
	// 初始化链表
	struct list *list = list_init();
	// 添加两个节点到list
	struct list *first = (struct list *) malloc(sizeof(struct list));
	first->index = *index;
	first->x = x;
	first->y = y;
	*index = *index + 1;
	struct list *second = (struct list *) malloc(sizeof(struct list));
	second->index = *index;
	second->x = x + CELL_SIZE;
	second->y = y;
	list_append(list, first);
	list_append(list, second);
	return list;
}

// 蛇移动
// list: 链表
// direction: 当前方向
void snake_move(struct list *list, enum direction direction) {
	struct list *first = list->next;
	struct list *p = list->prev;
	while(p && p->prev != list) {
		p->x = p->prev->x;
		p->y = p->prev->y;
		p = p->prev;
	}
	switch(direction) {
		case DIRECTION_UP: // UP
			first->y -= CELL_SIZE;
			break;
		case DIRECTION_LEFT: // LEFT
			first->x -= CELL_SIZE;
			break;
		case DIRECTION_DOWN: // DOWN
			first->y += CELL_SIZE;
			break;
		case DIRECTION_RIGHT: // RIGHT
			first->x += CELL_SIZE;
			break;
	}
}

// 蛇是否死亡
// 边界: rect
// 返回值: 1: true, 0: false
int snake_die(struct list *list, struct rectangle *rect) {
	struct list *first = list->next;
	// 判断是否越界
	if(first->x < rect->x1 || first->y < rect->y1
		|| first->x + CELL_SIZE > rect->x2 || first->y + CELL_SIZE > rect->y2) {
		return 1;
	}
	// 判断是否吃到自己
	struct list *p = first->next;
	while(p && p != list) {
		if(first->x == p->x && first->y == p->y) {
			return 1;
		}
		p = p->next;
	}
	return 0;
}

// 蛇吃掉食物
void snake_eat_food(struct list *list, struct food *food) {
	// 在尾部添加食物
	struct list *p = list->prev;
	struct list *tmp = (struct list *) malloc(sizeof(struct list));
	tmp->index = *food->index;
	tmp->x = p->x;
	tmp->y = p->y;
	p->next = tmp;
	tmp->prev = p;
	tmp->next = list;
	list->prev = tmp;
	food->flag = 1;
}
