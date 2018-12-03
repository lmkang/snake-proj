package edu.ncepu.snake.entities;

import java.awt.Color;
import java.awt.Graphics;

import edu.ncepu.snake.util.GlobleVar;
/**
 * 石头
 * @version 1.2
 * @author 梁明康
 */
public class Ground {

	private int[][] rocks = new int[GlobleVar.WIDTH][GlobleVar.HEIGHT];
	/**
	 * 初始化石头
	 */
	public Ground() {

		for (int x = 0; x < GlobleVar.WIDTH; x++) {
			rocks[x][0] = 1;
			rocks[x][GlobleVar.HEIGHT - 1] = 1;
		}
		for (int y = 0; y < GlobleVar.HEIGHT; y++) {
			rocks[0][y] = 1;
			rocks[GlobleVar.WIDTH - 1][y] = 1;
		}
	}
	/**
	 * 判断蛇是否吃到石头
	 * @param snake
	 * @return 是，返回true；否则返回false
	 */
	public boolean isSnakeEatGround(Snake snake) {

		for (int i = 0; i < GlobleVar.WIDTH; i++) {
			for (int j = 0; j < GlobleVar.HEIGHT; j++) {
				if (rocks[i][j] == 1 && snake.getHead().x == i
						&& snake.getHead().y == j) {
					return true;
				}
			}
		}
		return false;
	}
	/**
	 * 画石头
	 * @param g
	 */
	public void drawMe(Graphics g) {

		g.setColor(Color.DARK_GRAY);
		for (int i = 0; i < GlobleVar.WIDTH; i++) {
			for (int j = 0; j < GlobleVar.HEIGHT; j++) {
				if (rocks[i][j] == 1) {
					g.fill3DRect(i * GlobleVar.CELL_SIZE + GlobleVar.NUM, j
							* GlobleVar.CELL_SIZE + GlobleVar.NUM,
							GlobleVar.CELL_SIZE, GlobleVar.CELL_SIZE, true);
				}
			}
		}
	}
}
