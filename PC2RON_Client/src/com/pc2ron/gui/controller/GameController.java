/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.pc2ron.gui.controller;

import com.pc2ron.frame.EPennant;
import com.pc2ron.gui.model.GameModel;
import com.pc2ron.gui.model.DisplayModel;
import com.pc2ron.interfaces.IPlayer;
import com.pc2ron.interfaces.IProtocol;
import com.pc2ron.protocol.EFrameType;
import com.pc2ron.protocol.EOrder;
import com.pc2ron.protocol.Protocol;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.util.ArrayList;
import javax.swing.JOptionPane;

/**
 *
 * @author Mehdi Drici
 */
public class GameController implements KeyListener, ActionListener {
    private IProtocol protocol;
    private GameModel gameModel;
    private DisplayModel displayModel;
    
    public GameController() {
        protocol = Protocol.getInstance();
    }
    
    /**
     * Definir le modele du jeu
     * contenant l'ensemble des positions et directions des joueurs
     * @param gameModel 
     */
    public void setModel(GameModel gameModel) {
        this.gameModel = gameModel;
    }
    
    /**
     * Definir le modele contenant les trames recues du serveur
     */
    public void setModel(DisplayModel displayModel) {
        this.displayModel = displayModel;
    }
    
    
    @Override
    public void keyPressed(KeyEvent arg0) {
        System.out.println(arg0.toString());
        
        try {
            switch(arg0.getKeyCode()) {
               case KeyEvent.VK_LEFT:
                   protocol.sendOrder(EOrder.LEFT);
                   break;

               case KeyEvent.VK_RIGHT:
                   protocol.sendOrder(EOrder.RIGHT);
                   break;
            } 
        } catch (Exception ex) {
            JOptionPane.showMessageDialog(null, ex.toString(), 
                         "Server Error", JOptionPane.ERROR_MESSAGE);
        }
    }
    
    @Override
    public void actionPerformed(ActionEvent arg0) {
        try {
            short[] rgb = {10, 10, 10};

            protocol.connect("127.0.0.1", 5555);
            protocol.register(rgb, "Mehdi");
            
            ReceptionThread thread = new ReceptionThread();
            
            thread.start();
           
        } catch (Exception ex) {
            JOptionPane.showMessageDialog(null, ex.toString(), 
                         "Server Error", JOptionPane.ERROR_MESSAGE);
        }
    }
    
    // Thread de reception
    class ReceptionThread extends Thread {
        @Override
        public void run() {
            try {
                ArrayList result;
                EFrameType frameType;
                
                while(true) {
                    result = protocol.readFrame();
                    
                    // Fin de transmission demandee par le serveur
                    // Trame speciale { 00 }
                    // Fin de reception
                    if(result.get(0) instanceof EPennant) {
                        break;
                    }
                    
                    frameType = (EFrameType) result.get(0);
                    
                    switch(frameType) {
                        /* @todo reprendre le jeu */
                        case Start:
                            displayModel.setText(result.get(1).toString());
                            break;
                        
                        /* @todo mettre le jeu en pause */
                        case Pause:
                            displayModel.setText(result.get(1).toString());
                            break;
                        
                        /* @todo fin de partie et affichage du score */
                        case Win:
                            //model.update((ArrayList<IPlayer>) result.get(1));
                            displayModel.setText((String) result.get(1));
                            break;
                            
                        /* @todo preciser au modele le mort en question
                         * afin qu'il ne l'affiche plus
                         */ 
                        case Death:
                            displayModel.setText((String) result.get(1));
                            break;
                        
                        /* Initialisation des positions */
                        case User:
                            displayModel.setText(result.get(1).toString());
                            gameModel.initPlayers((ArrayList<IPlayer>) result.get(1));
                            break;
                        
                        /* Mise a jour des positions */
                        case Turn:
                            ArrayList content = (ArrayList) result.get(1);
                            ArrayList<IPlayer> players = (ArrayList<IPlayer>) content.get(1);
                            
                            displayModel.setText(players.toString());
                            gameModel.update(players);
                            break;
                    }
                }
            
            /* @todo Affichage de l'erreur */
            } catch (Exception ex) {
               JOptionPane.showMessageDialog(null, ex.toString(), 
                         "Server Error", JOptionPane.ERROR_MESSAGE);
            }
        }
    }
    
    @Override
    public void keyTyped(KeyEvent arg0) {
    }
    
    @Override
    public void keyReleased(KeyEvent arg0) {
    }
}
