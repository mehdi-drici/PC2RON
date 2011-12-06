package fr.pc2ron.interfaces;

import java.io.DataOutputStream;
import java.util.ArrayList;
import java.util.HashMap;

import fr.pc2ron.protocole.EOrdre;
import fr.pc2ron.trame.donnee.DonneeFactory;

public interface IProtocole {
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
	public void envoyerOrdre(EOrdre ordre);
	
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
	
	public String getMessageStart(ITrame trameStart) throws Exception;
	public String getMessagePause(ITrame tramePause) throws Exception;
	public int[] getPerdants(ITrame trameDeath) throws Exception;
	public int getGagnant(ITrame trameWin) throws Exception;
	public HashMap<String, Object> getPositions(ITrame trameTurn) throws Exception;
	public HashMap<String, Object> getDonneesUser(ITrame trameUser) throws Exception;
	
	/*
	public void envoyerTrameAck(ITrame init, DataOutputStream out);
	public void envoyerTrameRegistered(ITrame connec,DataOutputStream out,char id);
	public void envoyerTrameUse(DataOutputStream out,char id,String nom,short r,short v,short b,char x,char y,short dir,short speed );
	public void envoyerTrameEnd(DataOutputStream out);
	public void envoyerTramePause(DataOutputStream out);
	public void envoyerTrameStart(DataOutputStream out);
	*/
}
