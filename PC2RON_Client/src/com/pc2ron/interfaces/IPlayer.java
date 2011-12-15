package com.pc2ron.interfaces;

import com.pc2ron.frame.data.*;
import com.pc2ron.game.EDirection;
import com.pc2ron.game.ESpeed;
import java.awt.Point;

/**
 * Interface representant un joueur
 * @author Mehdi Drici
 */
public interface IPlayer {
	
	public String getName();
        public int getId();
        
        // Couleur de la moto au format RGB
        // {Red, Green, Blue}
        public int[] getRGB();
        
        public Point getPosition();
        public EDirection getDir();
        public ESpeed getSpeed();
        
        public void setRGB(int[] color);
	public void setName(String name);
	public void setId(int id);
	public void setPosition(Point pt);
	public void setDir(EDirection dir);
	public void setSpeed(ESpeed speed);
}