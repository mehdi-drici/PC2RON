/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.pc2ron.gui.view;

/**
 *
 * @author mehdi
 */
import com.pc2ron.gui.controller.GameController;
import com.pc2ron.gui.model.GraphicalGameModel;
import java.awt.*;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.util.Observable;
import java.util.Observer;
import javax.swing.*;
import javax.swing.border.BevelBorder;
 
public class GridView extends JPanel implements Observer {
    private static final long serialVersionUID = 1125546565477564L;
    
    private GraphicalGameModel model;
    
    public GridView(GraphicalGameModel model) {
        this.model = model;
        model.addObserver(this);
        
        super.setBorder(BorderFactory.createBevelBorder(BevelBorder.RAISED));
        //this.setBackground(Color.LIGHT_GRAY);
        //this.setBorder(BorderFactory.createMatteBorder(2, 2, 2, 2, Color.DARK_GRAY));
        //this.setBorder(BorderFactory.createBevelBorder(BevelBorder.LOWERED));
        //addKeyListener(this);
        this.setBorder(BorderFactory.createBevelBorder(BevelBorder.LOWERED));
        this.setBackground(Color.darkGray);
        this.setFocusable(true);
        this.setVisible(true);
        
    }
    
    @Override
    public void paintComponent(Graphics g){
        super.paintComponent(g);
        model.paint(g);
    }

    @Override
    public void update(Observable arg0, Object arg1) {
        repaint();
    }
}