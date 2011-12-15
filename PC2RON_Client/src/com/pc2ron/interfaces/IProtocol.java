package com.pc2ron.interfaces;

import java.io.DataOutputStream;
import java.util.ArrayList;
import java.util.HashMap;

import com.pc2ron.protocol.EOrder;
import com.pc2ron.frame.data.DonneeFactory;

public interface IProtocol {
	// Envoi de la trame Initiate
	// { 0x49, string "PC2RON?", string "PC2RON2011" }
	//private Socket sock; 
	
	//public void envoyerTrameInit(DataOutputStream out);
	//public void envoyerTrameConnexion(DataOutputStream out, ITrame ack,short r,short v,short b,String nom);
	
	/**
	 * Envoi
	 */
	// Initiate
	public void connexion(String host, int port) throws Exception;
	
	// Connect
	// return id
	public int inscription(short r, short v, short b, String nom) throws Exception;
	
	// Order
	public void envoyerOrdre(EOrder ordre);
	
	// Envoi du signal "pret"
	public void commencerPartie();
	
	public void deconnexion();
	
	/**
	 *  Reception
	 */
	// Format: <type, Data>
	// par ex: <0x50, "message de pause">
	public ArrayList getContenuTrame() throws Exception;
	
	
	//public ArrayList getDonneesUsers();
	
	public String getMessageStart(IFrame trameStart) throws Exception;
	public String getMessagePause(IFrame tramePause) throws Exception;
	public int[] getPerdants(IFrame trameDeath) throws Exception;
	public int getGagnant(IFrame trameWin) throws Exception;
	public IPlayer[] getPositions(IFrame trameTurn) throws Exception;
	public IPlayer getDonneesUser(IFrame trameUser) throws Exception;
}
