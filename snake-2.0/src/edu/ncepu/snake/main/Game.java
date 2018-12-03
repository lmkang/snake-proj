package edu.ncepu.snake.main;

import java.awt.event.WindowEvent;
import java.awt.event.WindowFocusListener;

import javax.swing.JFrame;

import edu.ncepu.snake.controller.Controller;
import edu.ncepu.snake.entities.Food;
import edu.ncepu.snake.entities.Ground;
import edu.ncepu.snake.entities.Snake;
import edu.ncepu.snake.util.GlobleVar;
import edu.ncepu.snake.view.GameOptionPanel;
import edu.ncepu.snake.view.GamePanel;
/**
 * 主函数类
 * @version 1.2
 * @author 梁明康
 */
public class Game extends JFrame {

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {

		Snake snake = new Snake();
		Food food = new Food();
		Ground ground = new Ground();
		GamePanel gamePanel = new GamePanel();
		final Controller controller = new Controller(snake, food, ground,
				gamePanel);

		JFrame contentPane = new JFrame();
		contentPane.setTitle("贪 吃 蛇");
		GameOptionPanel gameOption = new GameOptionPanel(contentPane,
				controller);

		controller.setLblScore(gameOption.getLblScore());
		controller.setBtnStart(gameOption.getBtnStart());
		controller.setBtnContinue(gameOption.getBtnContinue());
		controller.setLblSpeed(gameOption.getLblSpeed());

		contentPane.setBounds(250, 80, GlobleVar.CLIENT_WIDTH,
				GlobleVar.CLIENT_HEIGHT);
		contentPane.setDefaultCloseOperation(EXIT_ON_CLOSE);
		gamePanel.setBounds(GlobleVar.NUM, GlobleVar.NUM, GlobleVar.WIDTH
				* GlobleVar.CELL_SIZE, GlobleVar.HEIGHT * GlobleVar.CELL_SIZE);
		contentPane.add(gamePanel);
		contentPane.setResizable(false);

		gamePanel.addKeyListener(controller);
		snake.addSnakeListener(controller);
		contentPane.addKeyListener(controller);
		contentPane.addWindowFocusListener(new WindowFocusListener() {
			@Override
			public void windowLostFocus(WindowEvent e) {
				if (!controller.getSnake().isPause()) {
					controller.continueGame();
				}
			}

			@Override
			public void windowGainedFocus(WindowEvent e) {

			}
		});

		// 聚焦到gamePanel上
		gamePanel.setFocusable(true);
		contentPane.setVisible(true);

	}

}
