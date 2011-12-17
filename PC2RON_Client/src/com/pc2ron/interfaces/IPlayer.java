package com.pc2ron.interfaces;

import com.pc2ron.game.EDirection;
import com.pc2ron.game.ESpeed;
import java.awt.Color;
import java.awt.Point;
import java.util.ArrayList;

/**
 * Interface representant un joueur
 * @author Mehdi Drici
 */
public interface IPlayer {
	
	public String getName();
        public int getId();
        
        // Couleur de la moto au format RGB
        // {Red, Green, Blue}
        public Color getRGB();
        
        public ArrayList<Point> getPositions();
        public EDirection getDir();
        public ESpeed getSpeed();
        
        // Recuperer la derniere position du joueur
        public Point getLastPosition();
        
        public void setRGB(Color color);
	public void setName(String name);
	public void setId(int id);
	public void setDir(EDirection dir);
	public void setSpeed(ESpeed speed);
        
        /* Methodes de deplacement */
        public void goDown();
        public void goUp();
        public void goLeft();
        public void goRight();
        
        
}