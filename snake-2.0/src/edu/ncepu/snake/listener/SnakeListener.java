package edu.ncepu.snake.listener;

import edu.ncepu.snake.entities.Snake;

/**
 * �ߵļ�����
 * @version 1.2
 * @author ������
 */
public interface SnakeListener {
	/**
	 * ���ƶ��¼�
	 */
	void snakeMoved(Snake snake);

	/**
	 * �߳Ե�ʳ���¼�
	 */
	void snakeEatFood(Snake snake);
}
