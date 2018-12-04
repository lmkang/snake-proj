// main.c
// (C) 2018/12/03 梁明康 lmkang25@163.com

#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <commctrl.h>
#include "snake.h"
#include "food.h"

// 初始化游戏
static struct list *game_init(int *index, int snake_x, int snake_y, 
	struct food *food, struct rectangle *rect);

// 刷新, 重画
static void repaint(HWND hwnd, struct list *list, struct food *food);

// 释放资源
static void release(HWND hDesktop, int iconCount, POINT *srcPoints, 
	HANDLE hProcess, POINT *ppt, struct list *list);

// 主函数
int main(__attribute__((unused)) int argc, __attribute__((unused)) char **argv) {
	// 隐藏控制台窗口
	HWND hConsole = FindWindow("ConsoleWindowClass", NULL);
	ShowWindow(hConsole, SW_HIDE);
	
	// 模拟[WIN + D], 最小化桌面
	INPUT inputs[4];
	memset(inputs, 0, sizeof(inputs));
	inputs[0].type = INPUT_KEYBOARD;
	inputs[0].ki.wVk = 0x5b;
	inputs[1].type = INPUT_KEYBOARD;
	inputs[1].ki.wVk = 0x5b;
	inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;
	inputs[2].type = INPUT_KEYBOARD;
	inputs[2].ki.wVk = 0x44;
	inputs[3].type = INPUT_KEYBOARD;
	inputs[3].ki.wVk = 0x44;
	inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, inputs, sizeof(INPUT));
	SendInput(1, inputs + 2, sizeof(INPUT));
	SendInput(1, inputs + 1, sizeof(INPUT));
	SendInput(1, inputs + 3, sizeof(INPUT));
	
	// 获取桌面句柄
	HWND hDesktop = FindWindowEx(0, 0, "Progman", "Program Manager");
	hDesktop = FindWindowEx(hDesktop, 0, "SHELLDLL_DefView", "");
	hDesktop = FindWindowEx(hDesktop, 0, "SysListView32", "FolderView");
	int iconCount = SendMessage(hDesktop, LVM_GETITEMCOUNT, 0, 0);
	printf("iconCount : %d\n", iconCount);
	if(iconCount < 3) {
		MessageBox(NULL, "The number of desktop's icon is 3 at least!", "INFO", MB_OK);
		return 0;
	}
	
	// 取消自动排列
	int oldStyle = GetWindowLong(hDesktop, GWL_STYLE);
	SetWindowLong(hDesktop, GWL_STYLE, oldStyle & ~LVS_AUTOARRANGE);
	// 取消网格对齐
	SendMessage(hDesktop, 0x1000 + 54, 0x80000, 0);
	
	// 获取桌面大小
	RECT rect;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0);
	int clientX = rect.right - rect.left;
	int clientY = rect.bottom - rect.top;
	printf("clientX : %d, clientY : %d\n", clientX, clientY);
	
	// 计算起始X坐标和Y坐标, 结束X坐标和Y坐标
	int cellCountX = clientX / CELL_SIZE;
	int cellCountY = clientY / CELL_SIZE;
	int startX = (clientX - cellCountX * CELL_SIZE) / 2;
	int startY = (clientY - cellCountY * CELL_SIZE) / 2;
	int endX = startX + cellCountX * CELL_SIZE;
	int endY = startY + cellCountY * CELL_SIZE;
	printf("startX : %d, startY : %d\n", startX, startY);
	printf("endX : %d, endY : %d\n", endX, endY);
	
	// 打开桌面进程
	DWORD dwPid;
	GetWindowThreadProcessId(hDesktop, &dwPid);
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, dwPid);
	if(hProcess == INVALID_HANDLE_VALUE) {
		printf("打开进程失败!");
		return -1;
	}
	
	// 获取桌面图标原始位置
	POINT *ppt = (POINT *) VirtualAllocEx(hProcess, NULL, 
		sizeof(POINT), MEM_COMMIT, PAGE_READWRITE);
	POINT *srcPoints = (POINT *) malloc(iconCount * sizeof(POINT));
	int iconIndex = 0; // 图标索引, 从0开始
	POINT pt;
	for(int i = 0; i < iconCount; i++) {
		// 获取图标位置
		SendMessage(hDesktop, LVM_GETITEMPOSITION, i, (LPARAM) ppt);
		ReadProcessMemory(hProcess, ppt, &pt, sizeof(POINT), NULL);
		printf("%d:%d\n", pt.x, pt.y);
		
		// 记录桌面图标位置的原始位置
		srcPoints[i].x = pt.x;
		srcPoints[i].y = pt.y;
		
		// 隐藏桌面图标
		SendMessage(hDesktop, LVM_SETITEMPOSITION, i, MAKELPARAM(5000, 250 * i));
	}
	
	// 注册热键
	if(RegisterHotKey(NULL, HOTKEY_W_ID, 0x4000, 0x57)) { // 'W'
		printf("Hotkey 'W' registered, using MOD_NOREPEAT flag\n");
	}
	if(RegisterHotKey(NULL, HOTKEY_A_ID, 0x4000, 0x41)) { // 'A'
		printf("Hotkey 'A' registered, using MOD_NOREPEAT flag\n");
	}
	if(RegisterHotKey(NULL, HOTKEY_S_ID, 0x4000, 0x53)) { // 'S'
		printf("Hotkey 'S' registered, using MOD_NOREPEAT flag\n");
	}
	if(RegisterHotKey(NULL, HOTKEY_D_ID, 0x4000, 0x44)) { // 'D'
		printf("Hotkey 'D' registered, using MOD_NOREPEAT flag\n");
	}
	if(RegisterHotKey(NULL, HOTKEY_ALT_Q_ID, MOD_ALT, 0x51)) { // ALT + 'Q'
		printf("Hotkey 'ALT + Q' registered, using MOD_ALT flag\n");
	}
	
	// 游戏提示信息
	MessageBox(NULL, "Using [W A S D] to move, and using [ALT + Q] to quit. Have a fun!", "INFO", 
		MB_OK | MB_SYSTEMMODAL);
	
	// main函数全局变量
	enum direction direction = DIRECTION_LEFT; // 当前运动方向
	struct food food; // 食物
	struct rectangle rect_game; // 游戏地图边界
	rect_game.x1 = startX;
	rect_game.y1 = startY;
	rect_game.x2 = endX;
	rect_game.y2 = endY;
	
	// 初始化list
	struct list *list = game_init(&iconIndex, 
		startX + (cellCountX / 2) * CELL_SIZE, startY + cellCountY / 2 * CELL_SIZE, 
		&food, &rect_game);
	// 刷新, 重画
	repaint(hDesktop, list, &food);
	
	// 消息循环
	MSG msg = {0};
	while(1) {
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if(msg.message == WM_HOTKEY) { // 热键
				if(HIWORD(msg.lParam) == 0x57) { // W
					if(direction != DIRECTION_DOWN) {
						direction = DIRECTION_UP;
					}
				} else if(HIWORD(msg.lParam) == 0x41) { // A
					if(direction != DIRECTION_RIGHT) {
						direction = DIRECTION_LEFT;
					}
				} else if(HIWORD(msg.lParam) == 0x53) { // S
					if(direction != DIRECTION_UP) {
						direction = DIRECTION_DOWN;
					}
				} else if(HIWORD(msg.lParam) == 0x44) { // D
					if(direction != DIRECTION_LEFT) {
						direction = DIRECTION_RIGHT;
					}
				} else if(LOWORD(msg.lParam) == MOD_ALT && HIWORD(msg.lParam) == 0x51) { // ALT + Q
					release(hDesktop, iconCount, srcPoints, hProcess, ppt, list);
					return 0;
				}
			}
		}
		// 蛇移动
		snake_move(list, direction);
		// 判断是否遇到食物
		if(list->next->x == food.x && list->next->y == food.y) {
			snake_eat_food(list, &food);
			if(iconIndex == iconCount - 1) {
				MessageBox(NULL, "You win the game!", "INFO", MB_OK);
				release(hDesktop, iconCount, srcPoints, hProcess, ppt, list);
				return 0;
			}
			food_rand(list, &food, &rect_game);
		}
		// 判断游戏是否结束
		if(snake_die(list, &rect_game)) {
			MessageBox(NULL, "GAME OVER!", "INFO", MB_OK);
			release(hDesktop, iconCount, srcPoints, hProcess, ppt, list);
			return 0;
		}
		// 刷新, 重画
		repaint(hDesktop, list, &food);
		Sleep(200);
	}
	return 0;
}

// 游戏初始化
// index: 图标索引, main函数全局变量
// 初始化两个图标, 坐标从(snake_x, snake_y)开始
// rect: 游戏地图边界
// 返回: list链表
static struct list *game_init(int *index, int snake_x, int snake_y, 
	struct food *food, struct rectangle *rect) {
	
	// 初始化蛇
	struct list *list = snake_init(index, snake_x, snake_y);
	// 初始化食物
	food_init(food, index);
	// 随机产生食物
	food_rand(list, food, rect);
	return list;
}

// 刷新, 重画
static void repaint(HWND hwnd, struct list *list, struct food *food) {
	// 画蛇
	struct list *p = list->next;
	while(p != list) {
		SendMessage(hwnd, LVM_SETITEMPOSITION, p->index, MAKELPARAM(p->x, p->y));
		p = p->next;
	}
	// 画食物
	SendMessage(hwnd, LVM_SETITEMPOSITION, *food->index, MAKELPARAM(food->x, food->y));
}

// 释放资源
static void release(HWND hDesktop, int iconCount, POINT *srcPoints, 
	HANDLE hProcess, POINT *ppt, struct list *list) {
	
	// 注销热键
	UnregisterHotKey(NULL, HOTKEY_W_ID);
	UnregisterHotKey(NULL, HOTKEY_A_ID);
	UnregisterHotKey(NULL, HOTKEY_S_ID);
	UnregisterHotKey(NULL, HOTKEY_D_ID);
	UnregisterHotKey(NULL, HOTKEY_ALT_Q_ID);
	
	// 恢复桌面图标位置
	for(int i = 0; i < iconCount; i++) {
		SendMessage(hDesktop, LVM_SETITEMPOSITION, i, MAKELPARAM(srcPoints[i].x, srcPoints[i].y));
	}
	
	// 释放内存资源
	VirtualFreeEx(hProcess, ppt, 0, MEM_RELEASE);
	CloseHandle(hProcess);
	free(srcPoints);
	
	// 释放list
	struct list *p = list;
	struct list *tmp;
	while(p != NULL && p != list) {
		tmp = p;
		p = p->next;
		free(tmp);
	}
}
