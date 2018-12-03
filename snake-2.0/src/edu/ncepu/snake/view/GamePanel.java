package edu.ncepu.snake.view;

import javax.swing.JPanel;

import java.awt.Color;
import java.awt.Graphics;

import edu.ncepu.snake.entities.Food;
import edu.ncepu.snake.entities.Ground;
import edu.ncepu.snake.entities.Snake;
import edu.ncepu.snake.util.GlobleVar;
/**
 * 进行游戏的panel
 * @version 1.2
 * @author 梁明康
 */
public class GamePanel extends JPanel {

	private Snake snake;
	private Food food;
	private Ground ground;
	/**
	 * 是否显示网格
	 */
	private boolean showNet = false;

	public boolean isShowNet() {
		return this.showNet;
	}

	public void changeShowNet() {
		this.showNet = !showNet;
	}

	public void display(Snake snake, Food food, Ground ground) {

		this.snake = snake;
		this.food = food;
		this.ground = ground;
		//不要全部重绘，否则会把其他控件覆盖了
		this.repaint(GlobleVar.NUM, GlobleVar.NUM, GlobleVar.WIDTH
				* GlobleVar.CELL_SIZE, GlobleVar.HEIGHT * GlobleVar.CELL_SIZE);
	}

	@Override
	protected void paintComponent(Graphics g) {
		super.paintComponent(g);

		g.setColor(getBackground());
		g.fill3DRect(GlobleVar.NUM, GlobleVar.NUM, GlobleVar.WIDTH
				* GlobleVar.CELL_SIZE, GlobleVar.HEIGHT * GlobleVar.CELL_SIZE,
				true);

		if (snake != null && food != null && ground != null) {
			snake.drawMe(g);
			food.drawMe(g);
			ground.drawMe(g);
		}
		
		if (isShowNet()) {
			g.setColor(Color.LIGHT_GRAY);
			drawNet(g);
		}
	}

	private void drawNet(Graphics g) {

		for (int x = GlobleVar.NUM + GlobleVar.CELL_SIZE; x < GlobleVar.WIDTH
				* GlobleVar.CELL_SIZE; x += GlobleVar.CELL_SIZE) {
			g.drawLine(x, GlobleVar.NUM + GlobleVar.CELL_SIZE, x, GlobleVar.NUM
					+ (GlobleVar.HEIGHT - 1) * GlobleVar.CELL_SIZE);
		}
		for (int y = GlobleVar.NUM + GlobleVar.CELL_SIZE; y < GlobleVar.HEIGHT
				* GlobleVar.CELL_SIZE; y += GlobleVar.CELL_SIZE) {
			g.drawLine(GlobleVar.NUM + GlobleVar.CELL_SIZE, y, GlobleVar.NUM
					+ (GlobleVar.WIDTH - 1) * GlobleVar.CELL_SIZE, y);
		}
	}

}
