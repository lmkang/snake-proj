package edu.ncepu.snake.listener;

import edu.ncepu.snake.entities.Snake;

/**
 * 蛇的监听器
 * @version 1.2
 * @author 梁明康
 */
public interface SnakeListener {
	/**
	 * 蛇移动事件
	 */
	void snakeMoved(Snake snake);

	/**
	 * 蛇吃到食物事件
	 */
	void snakeEatFood(Snake snake);
}
