package edu.ncepu.snake.view;

import java.awt.Color;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.UIManager;
import javax.swing.border.EtchedBorder;

import edu.ncepu.snake.controller.Controller;
/**
 * 游戏选项面板
 * @version 1.2
 * @author 梁明康
 */
public class GameOptionPanel extends JPanel {

	private final JButton btnStart;
	private final JButton btnContinue;
	private final JCheckBox chckbxShownet;

	private final JCheckBox chckbxConstspeed;
	private final JLabel lblScore;
	private final JLabel lblSpeed;

	public JButton getBtnStart() {
		return this.btnStart;
	}

	public JButton getBtnContinue() {
		return this.btnContinue;
	}

	public JCheckBox getChckbxShownet() {
		return this.chckbxShownet;
	}

	public JLabel getLblScore() {
		return this.lblScore;
	}
	
	public JLabel getLblSpeed() {
		return this.lblSpeed;
	}

	public GameOptionPanel(JFrame contentPane, final Controller controller) {

		JPanel panel_1 = new JPanel();
		panel_1.setBorder(new EtchedBorder(EtchedBorder.LOWERED, new Color(204,
				255, 255), null));
		panel_1.setBounds(10, 419, 504, 142);
		contentPane.add(panel_1);
		panel_1.setLayout(null);

		btnStart = new JButton("开始游戏");
		btnStart.setFont(new Font("楷体", Font.BOLD, 16));
		btnStart.setFocusable(false);
		btnStart.setEnabled(true);
		btnStart.setBounds(344, 28, 112, 27);
		btnStart.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				controller.newGame();
				btnStart.setEnabled(false);
				btnContinue.setEnabled(true);
			}
		});
		panel_1.add(btnStart);

		btnContinue = new JButton("继续/暂停");
		btnContinue.setFont(new Font("楷体", Font.BOLD, 16));
		btnContinue.setFocusable(false);
		btnContinue.setEnabled(false);
		btnContinue.setBounds(344, 78, 112, 27);
		btnContinue.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				controller.continueGame();
			}
		});
		panel_1.add(btnContinue);

		JLabel lblImg = new JLabel("img");
		lblImg.setBackground(UIManager.getColor("Button.background"));
		lblImg.setIcon(new ImageIcon(GameOptionPanel.class.getResource("/ncepu.jpg")));
		lblImg.setBounds(35, 9, 92, 112);
		panel_1.add(lblImg);

		chckbxShownet = new JCheckBox("显示网格");
		chckbxShownet.setFont(new Font("华文行楷", Font.PLAIN, 16));
		chckbxShownet.setFocusable(false);
		chckbxShownet.setBounds(185, 27, 103, 23);
		chckbxShownet.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				controller.getGamePanel().changeShowNet();
			}
		});
		panel_1.add(chckbxShownet);

		chckbxConstspeed = new JCheckBox("变速");
		chckbxConstspeed.setFont(new Font("华文行楷", Font.PLAIN, 16));
		chckbxConstspeed.setFocusable(false);
		chckbxConstspeed.setBounds(185, 69, 103, 23);
		chckbxConstspeed.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				controller.getSnake().changeConstSpeed();
			}
		});
		panel_1.add(chckbxConstspeed);

		JPanel panel_2 = new JPanel();
		panel_2.setBorder(new EtchedBorder(EtchedBorder.LOWERED, new Color(255,
				255, 153), null));
		panel_2.setBounds(524, 419, 246, 142);
		contentPane.add(panel_2);
		panel_2.setLayout(null);

		JLabel lblHelp = new JLabel("Tip:Enter:暂停 P:加速 L:减速");
		lblHelp.setBounds(10, 10, 230, 34);
		lblHelp.setFont(new Font("楷体", Font.PLAIN, 16));
		panel_2.add(lblHelp);

		lblSpeed = new JLabel("CurrentSpeed: ");
		lblSpeed.setBounds(10, 50, 230, 34);
		lblSpeed.setFont(new Font("Microsoft JhengHei UI", Font.BOLD, 15));
		panel_2.add(lblSpeed);

		lblScore = new JLabel("Score: ");
		lblScore.setFont(new Font("Microsoft JhengHei UI", Font.BOLD, 15));
		lblScore.setBounds(10, 97, 230, 34);
		panel_2.add(lblScore);

	}

}
