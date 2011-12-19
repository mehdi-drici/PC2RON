/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.pc2ron.gui.model;

import com.pc2ron.interfaces.IPlayer;
import java.awt.Graphics;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Observable;

/**
 *
 * @author Mehdi Drici
 */
public class GraphicalGameModel extends GameModel {
    public GraphicalGameModel() {
        super();
    }
    
    public void paint(Graphics g){
        IPlayer currentPlayer;
        
        for(Integer currentId : getPlayers().keySet()) {
            currentPlayer = getPlayers().get(currentId);
            
            // On colore la moto du joueur
            g.setColor(currentPlayer.getRGB());
            
            g.fillOval(currentPlayer.getLastPosition().x, 
                       currentPlayer.getLastPosition().y, 10, 10);
        }
    }
}


