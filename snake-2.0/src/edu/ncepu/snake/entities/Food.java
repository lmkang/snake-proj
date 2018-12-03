package edu.ncepu.snake.entities;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Point;

import edu.ncepu.snake.util.GlobleVar;
/**
 * ʳ��
 * @version 1.2
 * @author ������
 */
public class Food extends Point {
	
	/**
	 * �ж����Ƿ�Ե�ʳ��
	 * @param snake
	 * @return �ǣ�����true�����򷵻�false
	 */
	public boolean isSnakeEatFood(Snake snake) {

		return (this.equals(snake.getHead()));
	}
	/**
	 * ��ʳ��
	 * @param g
	 */
	public void drawMe(Graphics g) {

		g.setColor(Color.green);
		g.fill3DRect(x * GlobleVar.CELL_SIZE + GlobleVar.NUM, y
				* GlobleVar.CELL_SIZE + GlobleVar.NUM, GlobleVar.CELL_SIZE,
				GlobleVar.CELL_SIZE, true);
	}
	/**
	 * ����һ��ʳ��
	 * @param p
	 */
	public void getFood(Point p) {
		this.setLocation(p);
	}
}
