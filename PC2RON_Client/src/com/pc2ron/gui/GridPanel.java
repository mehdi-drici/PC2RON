/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.pc2ron.gui;

/**
 *
 * @author mehdi
 */
import com.pc2ron.game.EDirection;
import com.pc2ron.game.Player;
import com.pc2ron.interfaces.IPlayer;
import com.pc2ron.interfaces.IProtocol;
import com.pc2ron.protocol.Protocol;
import java.awt.*;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.util.ArrayList;
import java.util.HashMap;
import javax.swing.*;
import javax.swing.border.BevelBorder;
 
public class GridPanel extends JPanel implements KeyListener {
    private HashMap<Integer, IPlayer> playersHash;
    private IProtocol protocol = Protocol.getInstance();
    
    /* Degres de mise a jour d'un joueur */

    // Modification de la direction uniquement
    public static final int UPDATE_DIRECTION = 1;
    
    // Modification de la position uniquement
    public static final int UPDATE_POSITION = 2;
    
    // Modification de la direction et de la position
    public static final int UPDATE_BOTH = 3;
    
    // Tests
    private int id = new Integer(1);
    
    public GridPanel() {
        this.playersHash = new HashMap<Integer, IPlayer>(1);
        super.setBorder(BorderFactory.createBevelBorder(BevelBorder.RAISED));
        
        //this.setBackground(Color.LIGHT_GRAY);
        this.setBorder(BorderFactory.createMatteBorder(2, 2, 2, 2, Color.DARK_GRAY));
        this.setBorder(BorderFactory.createBevelBorder(BevelBorder.LOWERED));
        this.setFocusable(true);
        
        //test
        IPlayer testPlayer = new Player(1);
        testPlayer.getPositions().add(new Point(50, 50));
        testPlayer.setRGB(Color.RED);
        
        playersHash.put(id, testPlayer);
    }
    
    @Override
    public void paintComponent(Graphics g){
        super.paintComponent(g);
        //On décide d'une couleur de fond pour notre rectangle
        //g.setColor(Color.red);
        
        //On dessine celui-ci afin qu'il prenne tout la surface
        //g.fillRect(0, 0, this.getWidth(), this.getHeight());
        
        IPlayer currentPlayer;
        
        for(Integer currentId : playersHash.keySet()) {
            currentPlayer = playersHash.get(currentId);
            
            //System.out.println(currentPlayer.toString());
            
            // On colore la moto du joueur
            g.setColor(currentPlayer.getRGB());
        
            g.fillOval(currentPlayer.getLastPosition().x, 
                       currentPlayer.getLastPosition().y, 15, 15);
        }
    }
    
    /**
     * Initialisation des informations des joueurs:
     * - position et direction initiales
     * - nom
     * - couleur
     * @param players Liste des joueurs de la partie
     */
    public void initPlayers(ArrayList<IPlayer> players) {
        IPlayer currentPlayer;
        
        for(int i = 0; i < players.size(); i++) {
            currentPlayer = players.get(i);
            playersHash.put(new Integer(currentPlayer.getId()), currentPlayer);
        }
    }
    
    /**
     * Mise a jour des positions des joueurs en fonction de leur direction
     * Version synchrone locale et asynchrone
     */
    public void updatePositions() {
        IPlayer currentPlayer;
        
        for(Integer currentId : playersHash.keySet()) {
            currentPlayer = playersHash.get(currentId);
            
            //System.out.println(currentPlayer.toString());
            
            switch(currentPlayer.getDir()) {
                case BOTTOM:
                    if(currentPlayer.getLastPosition().y < this.getHeight() - 15) {
                        currentPlayer.goDown(); 
                    }
                    break;
                
                case TOP:
                    if(currentPlayer.getLastPosition().y > 0) {
                        currentPlayer.goUp(); 
                    }
                    break;
                    
                case LEFT:
                    if(currentPlayer.getLastPosition().x > 0) {
                        currentPlayer.goLeft(); 
                    }
                    break;
                    
                case RIGHT:
                    if(currentPlayer.getLastPosition().x < this.getWidth() - 15) {
                        currentPlayer.goRight(); 
                    }
                    break;
            }
        }
    }
    
    /**
     * Mise a jour des positions des joueurs a partir des nouvelles positions
     * transmises en parametre.
     * Il s'agit en fait d'une copie des nouvelles positions transmises.
     * @param players Liste des joueurs dont les informations ont ete modifiees  
     */
    public void updatePlayers(ArrayList<IPlayer> players, int updateType) {
        for(int i = 0; i < players.size(); i++) {
            IPlayer currentPlayer = players.get(i);
            IPlayer playerToUpdate = this.playersHash.get(i);
            
            switch(updateType) {
                case UPDATE_DIRECTION:
                    playerToUpdate.setDir(currentPlayer.getDir());
                    break;
                
                case UPDATE_POSITION:
                    playerToUpdate.getPositions().add(currentPlayer.getLastPosition());
                    break;
                    
                case UPDATE_BOTH:
                    playerToUpdate.setDir(currentPlayer.getDir());
                    playerToUpdate.getPositions().add(currentPlayer.getLastPosition());
                    break;
            }
        }
    }
    
    @Override
    public void keyTyped(KeyEvent arg0) {
        System.out.println("Touche typed : " + Character.toString(
                                                            arg0.getKeyChar()));
    }

    @Override
    public void keyPressed(KeyEvent arg0) {
        System.out.println("Touche pressee : " + Character.toString(
                                                            arg0.getKeyChar()));
        switch(arg0.getKeyCode()) {
           case KeyEvent.VK_LEFT: 
               this.playersHash.get(id).setDir(EDirection.LEFT);
               break;

           case KeyEvent.VK_RIGHT:
               this.playersHash.get(id).setDir(EDirection.RIGHT);
               break;

           case KeyEvent.VK_UP: 
               this.playersHash.get(id).setDir(EDirection.TOP);
               break;

           case KeyEvent.VK_DOWN: 
               this.playersHash.get(id).setDir(EDirection.BOTTOM);
               break;
        }
    }

    @Override
    public void keyReleased(KeyEvent arg0) {
        System.out.println("Touche released : " + Character.toString(
                                                            arg0.getKeyChar()));
    }
}