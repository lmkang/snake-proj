package edu.ncepu.snake.entities;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Point;

import edu.ncepu.snake.util.GlobleVar;
/**
 * 食物
 * @version 1.2
 * @author 梁明康
 */
public class Food extends Point {
	
	/**
	 * 判断蛇是否吃到食物
	 * @param snake
	 * @return 是，返回true；否则返回false
	 */
	public boolean isSnakeEatFood(Snake snake) {

		return (this.equals(snake.getHead()));
	}
	/**
	 * 画食物
	 * @param g
	 */
	public void drawMe(Graphics g) {

		g.setColor(Color.green);
		g.fill3DRect(x * GlobleVar.CELL_SIZE + GlobleVar.NUM, y
				* GlobleVar.CELL_SIZE + GlobleVar.NUM, GlobleVar.CELL_SIZE,
				GlobleVar.CELL_SIZE, true);
	}
	/**
	 * 产生一个食物
	 * @param p
	 */
	public void getFood(Point p) {
		this.setLocation(p);
	}
}
