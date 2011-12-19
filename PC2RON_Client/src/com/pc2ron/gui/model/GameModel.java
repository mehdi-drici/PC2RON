/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.pc2ron.gui.model;

import com.pc2ron.interfaces.IPlayer;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Observable;

/**
 *
 * @author Mehdi Drici
 */
public class GameModel extends Observable {
    public static final int GRID_HEIGHT = 500;
    public static final int GRID_WIDTH = 500;
    private HashMap<Integer, IPlayer> playersHash;
    private boolean paused;
    private boolean initialized;
    
    public GameModel() {
        playersHash = new HashMap<Integer, IPlayer>();
        paused = false;
        initialized = false;
    }
    
    public boolean isPaused() {
        return paused;
    }
    
    public boolean isInitialized() {
        return initialized;
    }
    
    public void update(ArrayList<IPlayer> players) {
        for(int i = 0; i < players.size(); i++) {
            IPlayer currentPlayer = players.get(i);
            IPlayer playerToUpdate = this.playersHash.get(currentPlayer.getId());
            
            System.out.print("playerToUpdate = " + playerToUpdate);
            
            playerToUpdate.setDir(currentPlayer.getDir());
            playerToUpdate.getPositions().add(currentPlayer.getLastPosition());
        }
        
        setChanged();
        notifyObservers();
    }
    
    public HashMap<Integer, IPlayer> getPlayers() {
        return this.playersHash;
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
        initialized = true;
        setChanged();
        notifyObservers();
    }
        
    /**
     * Mise a jour des positions des joueurs en fonction de leur direction
     * Version synchrone locale et asynchrone
     */
    public void update() {
        IPlayer currentPlayer;
        
        for(Integer currentId : playersHash.keySet()) {
            currentPlayer = playersHash.get(currentId);
            
            System.out.println(currentPlayer.toString());
            
            switch(currentPlayer.getDir()) {
                case BOTTOM:
                    if(currentPlayer.getLastPosition().y < GRID_HEIGHT - 12) {
                        currentPlayer.goDown(); 
                    } else {
                    /* Kill the player in the Asynchronous version */ 
                    }
                    break;
                
                case TOP:
                    if(currentPlayer.getLastPosition().y > 0) {
                        currentPlayer.goUp(); 
                    } else {
                        /* Kill the player in the Asynchronous version */
                    }
                    break;
                    
                case LEFT:
                    if(currentPlayer.getLastPosition().x > 0) {
                        currentPlayer.goLeft(); 
                    } else {
                        /* Kill the player in the Asynchronous version */
                    }
                    break;
                    
                case RIGHT:
                    if(currentPlayer.getLastPosition().x < GRID_WIDTH - 12) {
                        currentPlayer.goRight(); 
                    } else {
                        /* Kill the player in the Asynchronous version */
                    }
                    break;
            }
        }
        
        setChanged();
        notifyObservers();
    }
}

