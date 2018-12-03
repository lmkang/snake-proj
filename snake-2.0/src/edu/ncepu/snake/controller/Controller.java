package edu.ncepu.snake.controller;

import java.awt.Point;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.util.Random;

import javax.swing.JButton;
import javax.swing.JLabel;

import edu.ncepu.snake.entities.Food;
import edu.ncepu.snake.entities.Ground;
import edu.ncepu.snake.entities.Snake;
import edu.ncepu.snake.listener.SnakeListener;
import edu.ncepu.snake.util.GlobleVar;
import edu.ncepu.snake.view.GamePanel;

/**
 * 控制器
 * 
 * @author 梁明康
 * @version 1.2
 */
public class Controller extends KeyAdapter implements SnakeListener {

	private Snake snake;
	private Food food;
	private Ground ground;
	private GamePanel gamePanel;
	private Random r = new Random();
	private JLabel lblScore;
	private int score = 0;
	private JButton btnContinue;
	private JButton btnStart;
	private JLabel lblSpeed;

	public JLabel getLblSpeed() {
		return this.lblSpeed;
	}

	public void setLblSpeed(JLabel lblSpeed) {
		this.lblSpeed = lblSpeed;
	}

	public JButton getBtnStart() {
		return this.btnStart;
	}

	public void setBtnStart(JButton btnStart) {
		this.btnStart = btnStart;
	}

	public JButton getBtnContinue() {
		return this.btnContinue;
	}

	public void setBtnContinue(JButton btnContinue) {
		this.btnContinue = btnContinue;
	}

	public Snake getSnake() {
		return this.snake;
	}

	public GamePanel getGamePanel() {
		return this.gamePanel;
	}

	@Override
	public void keyPressed(KeyEvent e) {
		switch (e.getKeyCode()) {
		case KeyEvent.VK_W:
		case KeyEvent.VK_UP:
			if (!(snake.isEatBody() || ground.isSnakeEatGround(snake))) {
				snake.changeDirection(Snake.UP);
			}
			break;
		case KeyEvent.VK_S:
		case KeyEvent.VK_DOWN:
			if (!(snake.isEatBody() || ground.isSnakeEatGround(snake))) {
				snake.changeDirection(Snake.DOWN);
			}
			break;
		case KeyEvent.VK_A:
		case KeyEvent.VK_LEFT:
			if (!(snake.isEatBody() || ground.isSnakeEatGround(snake))) {
				snake.changeDirection(Snake.LEFT);
			}
			break;
		case KeyEvent.VK_D:
		case KeyEvent.VK_RIGHT:
			if (!(snake.isEatBody() || ground.isSnakeEatGround(snake))) {
				snake.changeDirection(Snake.RIGHT);
			}
			break;
		case KeyEvent.VK_ENTER:
			snake.changePause();
			break;
		case KeyEvent.VK_P:
			snake.setlastConstSpeed((snake.getSpeed() - 10));
			break;
		case KeyEvent.VK_L:
			snake.setlastConstSpeed((snake.getSpeed() + 10));
			break;
		}
	}

	public JLabel getLblScore() {
		return this.lblScore;
	}

	public void setLblScore(JLabel lblScore) {
		this.lblScore = lblScore;
	}

	/**
	 * 
	 * @param snake
	 * @param food
	 * @param ground
	 * @param gamePanel
	 */
	public Controller(Snake snake, Food food, Ground ground, GamePanel gamePanel) {
		this.snake = snake;
		this.food = food;
		this.ground = ground;
		this.gamePanel = gamePanel;
	}

	@Override
	public void snakeMoved(Snake snake) {
		if (ground.isSnakeEatGround(snake) || snake.isEatBody()) {
			snake.changeLive();
			btnStart.setEnabled(true);
			btnContinue.setEnabled(false);
			lblSpeed.setText("Current Speed: 0  毫秒/格");
			return;
		}
		if (!snake.isConstSpeed()) {// 不是恒定速度
			snake.setSpeed(r.nextInt(snake.getSpeed()) + 50);
		} else {
			snake.setSpeed(snake.getlastConstSpeed());
		}
		if (snake.isPause()) {// 暂停
			lblSpeed.setText("Current Speed: 0  毫秒/格");
		} else {
			lblSpeed.setText("Current Speed: " + snake.getSpeed() + " 毫秒/格");
		}
		gamePanel.display(snake, food, ground);
	}

	@Override
	public void snakeEatFood(Snake snake) {
		if (food.isSnakeEatFood(snake)) {
			snake.eatFood();
			food.getFood(getPoint());
			lblScore.setText("Score: " + (++score) * 100);
		}
	}
	/**
	 * 开始新游戏
	 */
	public void newGame() {
		snake.init();
		score = 0;
		lblScore.setText("Score: 0");
		snake.start();
		food.getFood(getPoint());
	}
	/**
	 * 继续游戏
	 */
	public void continueGame() {

		snake.changePause();
	}

	/**
	 * 判断食物产生时是否与蛇身体冲突
	 * 
	 * @return Point
	 */
	public Point getPoint() {

		boolean flag = false;
		int x = r.nextInt(GlobleVar.WIDTH - 2) + 1;
		int y = r.nextInt(GlobleVar.HEIGHT - 2) + 1;
		Point p = new Point(x, y);
		for (;;) {
			for (int i = 0; i < snake.getBody().size(); i++) {
				if (p.equals(snake.getBody().get(i))) {
					x = r.nextInt(GlobleVar.WIDTH - 2) + 1;
					y = r.nextInt(GlobleVar.HEIGHT - 2) + 1;
					p = new Point(x, y);
					flag = !flag;
					break;
				}
			}
			if (!flag) {
				break;
			}
			flag = !flag;
		}
		return p;
	}

}
