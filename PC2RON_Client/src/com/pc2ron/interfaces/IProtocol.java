package com.pc2ron.interfaces;

import com.pc2ron.frame.IncorrectFrameException;
import com.pc2ron.protocol.*;
import java.util.ArrayList;

/**
 * Protocole PC2RON du point de vue du client
 * Celui-ci gere l'echange entre le client et le serveur
 * @author Mehdi Drici
 */
public interface IProtocol {
    
    // Nombre d'informations d'un joueur
    // conformement a la structure d'une trame Turn
    public static final int PLAYER_DATA_SIZE = 4;

    public void connect(String host, int port) throws Exception;
    public void disconnect();
    
    public int register(short[] rgb, String name) throws Exception;
    public void sendOrder(EOrder order) throws IncorrectFrameException;
    public void startGame() throws IncorrectFrameException;
    
    public ArrayList readFrame() throws Exception;
    public String readStart(IFrame trameStart);
    public String readPause(IFrame tramePause);
    public int[] readDeath(IFrame trameDeath);
    public int readWin(IFrame trameWin);
    public ArrayList readTurn(IFrame trameTurn);
    public IPlayer readUser(IFrame trameUser);
}
