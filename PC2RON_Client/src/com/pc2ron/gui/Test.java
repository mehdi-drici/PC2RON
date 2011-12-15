package com.pc2ron.gui;

import java.awt.*;
import java.awt.event.*;

import javax.swing.*;

public class Test extends  JPanel implements KeyListener {
	 private JLabel lab;
	 
	 public static void main(String[] arg) {
		  JPanel panel=new Test();
		  JFrame frame=new JFrame();
		  frame.getContentPane().add(panel,BorderLayout.CENTER);
		  frame.setSize(400,300);
		  frame.setVisible(true);
	 }
	 
	 public Test() {
		 this.setBackground(Color.white);
	     this.setPreferredSize(new Dimension(300, 200));
	     this.addKeyListener(this);  // This class has its own key listeners.
	     this.setFocusable(true);    // Allow panel to get focus
	        
		 this.lab = new JLabel("passe dessus et tu verras");
		 this.lab.addKeyListener(this);
		 this.add(this.lab,BorderLayout.NORTH);
	 }
	

	@Override
	public void keyPressed(KeyEvent e) {
		char i = e.getKeyChar();
		 String str = Character.toString(i);
		 System.out.println("Touche pressee : " + str);
  
		 switch(e.getKeyCode()) {
		 	case KeyEvent.VK_LEFT: 
		 		lab.setText("Gauche");
		 		break;
		 		
		 	case KeyEvent.VK_RIGHT: 
		 		lab.setText("Droite");
		 		break;
		 		
		 	case KeyEvent.VK_UP: 
		 		lab.setText("Haut");
		 		break;
		 		
		 	case KeyEvent.VK_DOWN: 
		 		lab.setText("Bas");
		 		break;
		 }
		 
		 //this.repaint();
	}

	@Override
	public void keyReleased(KeyEvent e) {
		char i = e.getKeyChar();
		 String str = Character.toString(i);
		 System.out.println("Touche pressee : " + str);
	}

	@Override
	public void keyTyped(KeyEvent e) {
		char i = e.getKeyChar();
		 String str = Character.toString(i);
		 System.out.println("Touche pressee : " + str);

	}
}