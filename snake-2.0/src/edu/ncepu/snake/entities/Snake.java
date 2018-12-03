package edu.ncepu.snake.entities;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Point;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.Set;

import edu.ncepu.snake.listener.SnakeListener;
import edu.ncepu.snake.util.GlobleVar;
/**
 * ��
 * @version 1.2
 * @author ������
 */
public class Snake {

	/**
	 * ����ڵ�
	 */
	private LinkedList<Point> body = new LinkedList<Point>();
	private Set<SnakeListener> listeners = new HashSet<SnakeListener>();
	private int oldDirection, newDirection;
	private int speed;
	/**
	 * �Ƿ��Ǻ㶨�ٶ�
	 */
	private boolean constSpeed = true;
	/**
	 * ��һ�κ㶨���ٶȴ�С
	 */
	private int lastConstSpeed;
	private Point tail;
	private boolean live;
	private boolean pause;

	/**
	 * �ߵķ�������
	 */
	public static final int UP = 1;
	/**
	 * �ߵķ�������
	 */
	public static final int DOWN = -1;
	/**
	 * �ߵķ�������
	 */
	public static final int LEFT = 2;
	/**
	 * �ߵķ�������
	 */
	public static final int RIGHT = -2;

	public int getlastConstSpeed() {
		return this.lastConstSpeed;
	}

	public void setlastConstSpeed(int lastConstSpeed) {
		this.lastConstSpeed = lastConstSpeed;
	}

	public boolean isConstSpeed() {
		return this.constSpeed;
	}
	
	/**
	 * �л����������
	 */
	public void changeConstSpeed(){
		this.constSpeed = !constSpeed;
		if(!constSpeed){
			this.speed = 150;
		}
	}

	public int getSpeed() {
		return this.speed;
	}

	public void setSpeed(int speed) {
		
		this.speed = speed;
	}

	public boolean isLive() {
		return this.live;
	}
	
	public void changeLive() {
		live = !live;
	}
	
	public boolean isPause() {
		return this.pause;
	}
	
	public void changePause() {
		pause = !pause;
	}
	/**
	 * ��ʼ����
	 */
	public void init() {
		body.clear();
		int x = GlobleVar.WIDTH / 2;
		int y = GlobleVar.HEIGHT / 2;
		for (int i = 0; i < 3; i++) {
			body.addLast(new Point(x--, y));
		}
		oldDirection = newDirection = RIGHT;
		this.constSpeed = isConstSpeed();
		this.live = true;
		this.pause = false;
		this.speed = 200;
		this.lastConstSpeed = 200;
	}
	/**
	 * �õ���ͷ����
	 * @return
	 */
	public Point getHead() {
		return body.getFirst();
	}
	/**
	 * �ߵ��ƶ�
	 */
	public void move() {

		if (!(oldDirection + newDirection == 0)) {
			oldDirection = newDirection;
		}

		tail = body.removeLast();
		int x = body.getFirst().x;
		int y = body.getFirst().y;
		switch (oldDirection) {
		case UP:
			y--;
			if (y < 0) {
				y = GlobleVar.HEIGHT;
			}
			break;
		case DOWN:
			y++;
			if (y >= GlobleVar.HEIGHT) {
				y = 0;
			}
			break;
		case LEFT:
			x--;
			if (x < 0) {
				x = GlobleVar.WIDTH;
			}
			break;
		case RIGHT:
			x++;
			if (x >= GlobleVar.WIDTH) {
				x = 0;
			}
			break;

		}
		Point newHead = new Point(x, y);
		body.addFirst(newHead);
	}

	public void changeDirection(int direction) {

		newDirection = direction;
	}
	/**
	 * �߳�ʳ��
	 */
	public void eatFood() {

		body.addLast(tail);
	}
	/**
	 * ���Ƿ�Ե��Լ�����
	 * @return �ǣ�����true�����򷵻�false
	 */
	public boolean isEatBody() {
		Point head = getHead();
		// �ӵ����ڿ�ʼ�ж�
		for (int i = 2; i < body.size(); i++) {
			if (body.get(i).equals(head)) {
				return true;
			}
		}
		return false;
	}
	/**
	 * ����
	 * @param g
	 */
	public void drawMe(Graphics g) {

		g.setColor(Color.RED);
		g.fill3DRect(getHead().x * GlobleVar.CELL_SIZE + GlobleVar.NUM, getHead().y
				* GlobleVar.CELL_SIZE + GlobleVar.NUM, GlobleVar.CELL_SIZE,
				GlobleVar.CELL_SIZE, true);
		
		g.setColor(Color.PINK);
		for (int i = 1; i<body.size(); i++) {
			g.fill3DRect(body.get(i).x * GlobleVar.CELL_SIZE + GlobleVar.NUM, body.get(i).y
					* GlobleVar.CELL_SIZE + GlobleVar.NUM, GlobleVar.CELL_SIZE,
					GlobleVar.CELL_SIZE, true);
		}
	}

	private class SnakeDriver implements Runnable {

		@Override
		public void run() {
			while (live) {
				for (SnakeListener sl : listeners) {
					sl.snakeMoved(Snake.this);
					sl.snakeEatFood(Snake.this);
				}
				if(!pause){
					move();
				}
				try {
					Thread.sleep(getSpeed());
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
		}

	}
	/**
	 * �����ߵ��߳�
	 */
	public void start() {
		new Thread(new SnakeDriver()).start();
	}
	/**
	 * ����߼�����
	 * @param sl
	 */
	public synchronized void addSnakeListener(SnakeListener sl) {
		if (sl != null) {
			this.listeners.add(sl);
		}
	}
	/**
	 * �õ��ߵ�����ڵ㼯��
	 * @return
	 */
	public LinkedList<Point> getBody() {
		return body;
	}
}