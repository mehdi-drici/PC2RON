package com.pc2ron.protocol;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import com.pc2ron.interfaces.IString;
import com.pc2ron.interfaces.IData;
import com.pc2ron.interfaces.IUint16;
import com.pc2ron.interfaces.IPlayer;
import com.pc2ron.interfaces.IProtocol;
import com.pc2ron.interfaces.IFrame;
import com.pc2ron.interfaces.IFrameBuilder;
import com.pc2ron.interfaces.IFrameFactory;
import com.pc2ron.frame.FrameReceiver;
import com.pc2ron.frame.Frame;
import com.pc2ron.frame.FrameFactory;
import com.pc2ron.frame.FrameSenderVisitor;
import com.pc2ron.frame.data.Chaine;
import com.pc2ron.frame.data.DonneeFactory;
import com.pc2ron.frame.data.EntierNonSigne2;

import com.pc2ron.protocol.EFrameType;
import com.pc2ron.frame.data.*;
import java.util.logging.Level;
import java.util.logging.Logger;

public class Protocol implements IProtocol {
	private Socket sock;
	private DataOutputStream out;
	private DataInputStream in;
	
	private static IProtocol instance;
	
	private Protocol() {
        }
	
	public static IProtocol getInstance() {
		if (null == instance) { // Premier appel
			instance = new Protocol();
	    }
	    return instance;
	}

	@Override
	public void commencerPartie() {
		// TODO Auto-generated method stub
		
	}

	@Override
	// { 0x49, string "PC2RON?", string "PC2RON2011" } 
	public void connexion(String host, int port) throws Exception {
		// Initialisation de la socket
		sock = new Socket(host, port);
		in = new DataInputStream(sock.getInputStream());
		out = new DataOutputStream(sock.getOutputStream());
		
		// Envoi de la trame Init
		IFrameBuilder trameBuilder = FrameBuilder.getInstance();
		IFrame trameInit = trameBuilder.creerTrameInit();
		
		FrameSenderVisitor envoi = new FrameSenderVisitor();
		envoi.visit(trameInit, out);
		
		// Reception de l'acquittement
		FrameReceiver reception = new FrameReceiver();
		IFrame ack = reception.recevoirTrame(in);
                
                EFrameType eTypeTrame = EFrameType.getTypeTrame(ack.getId());
		IData message = ack.getDonnees().get(0);
		
		// ? { 0x41, string "OK", string "PC2R2011" }
		if(eTypeTrame == EFrameType.TrameAck &&
		   message instanceof Chaine) {
			IString chaine = (IString) message;
				
			if(! chaine.getChaine().equals("OK")) {
                            throw new Exception("La version du protocole n'est pas supportee par le serveur !");
			}
		} else {
                    throw new Exception("Impossible de lire la reponse du serveur !");
		}
	}

	@Override
	public void deconnexion() {
        try {
            //try {
                IFrameFactory trameFactory = FrameFactory.getInstance();
                IFrame trameFin = trameFactory.getTrameEnd();
                FrameSenderVisitor envoi = new FrameSenderVisitor();
                
                envoi.visit(trameFin, out);
                
                out.flush();
                out.close();
                sock.close();
            } catch (IOException ex) {
                Logger.getLogger(Protocol.class.getName()).log(Level.SEVERE, null, ex);
            } 
        }
        
	@Override
	public void envoyerOrdre(EOrder ordre) {
            // Envoi de la trame Order
            IFrameBuilder trameBuilder = FrameBuilder.getInstance();
            IFrame trameOrder = trameBuilder.creerTrameOrder(ordre);
            
            //debug
            System.out.println(trameOrder.toString());
            //debug
            
            FrameSenderVisitor envoi = new FrameSenderVisitor();
            envoi.visit(trameOrder, out);
	}

	@Override
        //@todo implementer
	public IPlayer getDonneesUser(IFrame trameUser) throws Exception {
            System.out.print(trameUser);
            
            Joueur j = new Joueur();
            
            if(trameUser.getNbDonnees() == 9) {
                List donnees = trameUser.getDonnees();
                
                
                if (donnees.get(0) instanceof EntierNonSigne2 &&
                    donnees.get(1) instanceof Chaine &&
                    donnees.get(2) instanceof EntierNonSigne1 &&
                    donnees.get(3) instanceof EntierNonSigne1 &&
                    donnees.get(4) instanceof EntierNonSigne1 &&
                    donnees.get(5) instanceof EntierNonSigne2 &&
                    donnees.get(6) instanceof EntierNonSigne2 &&
                    donnees.get(7) instanceof EntierNonSigne1 &&
                    donnees.get(8) instanceof EntierNonSigne1) {
                    
                    j.setId((EntierNonSigne2) donnees.get(0));
                    j.setNom((Chaine) donnees.get(1));
                    j.setRouge((EntierNonSigne1) donnees.get(2));
                    j.setVert((EntierNonSigne1) donnees.get(3));
                    j.setBleu((EntierNonSigne1) donnees.get(4));
                    j.setX((EntierNonSigne2) donnees.get(5));
                    j.setY((EntierNonSigne2) donnees.get(6));
                    j.setDir((EntierNonSigne1) donnees.get(7));
                    j.setSpeed((EntierNonSigne1) donnees.get(8));
                    
                } else {
                    throw new Exception("La trame user recue n'est pas correcte !");
                }
            } else {
                throw new Exception("La trame user recue n'est pas correcte !");
            }
		
            return j;
	}
		
	@Override
	public int getGagnant(IFrame trameWin) throws Exception {
            //IDonnee donnee = trameWin.getDonnees().get(0);
            int idGagnant = -1;
            
            if(trameWin.getNbDonnees() != 1) {
                throw new Exception("La trame Start recue n'est pas correcte !");
            } else {
                IData donnee = trameWin.getDonnees().get(0);

                if(donnee instanceof EntierNonSigne2) {
                    IUint16 entierNonSigne2 = (IUint16) donnee;
                    idGagnant = entierNonSigne2.getEntier();
                } else {
                    throw new Exception("La trame Start recue n'est pas correcte !");
                }
            }
            
            return idGagnant;
	}


	@Override
	public ArrayList getContenuTrame() throws Exception {
            FrameReceiver reception = new FrameReceiver();
            IFrame trameRecue = reception.recevoirTrame(in);
            
            //debug
            System.out.println(trameRecue.toString());
            //debug
                        
            EFrameType typeTrame = EFrameType.getTypeTrame(trameRecue.getId());
            
            ArrayList contenuTrame = new ArrayList();
            contenuTrame.add(typeTrame);
            
            switch(typeTrame) {
                // @todo implementer
                case TrameUser:
                    do {
                        contenuTrame.add(getDonneesUser(trameRecue));
                        trameRecue = reception.recevoirTrame(in);
                        typeTrame = EFrameType.getTypeTrame(trameRecue.getId());
                    } while (typeTrame != EFrameType.TrameEnd);
                    
                    break;

                case TrameStart:
                    contenuTrame.add(getMessageStart(trameRecue));
                    break;

                case TramePause:
                    contenuTrame.add(getMessagePause(trameRecue));
                    break;

                case TrameTurn:
                    contenuTrame.add(getPositions(trameRecue));
                    break;

                case TrameDeath:
                    contenuTrame.add(getPerdants(trameRecue));
                    break;

                case TrameWin:
                    contenuTrame.add(getGagnant(trameRecue));
                    break;

                default:
                    throw new Exception("Type de trame inconnu !");
            }
            
            return contenuTrame;
	}

	@Override
	public int inscription(short r, short v, short b, String nom)
			throws Exception {
                System.out.println("Inscription...");
                
		// Envoi de la trame Connect
		IFrameBuilder trameBuilder = FrameBuilder.getInstance();
		IFrame trameConnect = trameBuilder.creerTrameConnect(r, v, b, nom);
		
		FrameSenderVisitor envoi = new FrameSenderVisitor();
		envoi.visit(trameConnect, out);
		
		// Reception de l'acquittement
		FrameReceiver reception = new FrameReceiver();
		IFrame ack = reception.recevoirTrame(in);
		
		EFrameType typeTrame = EFrameType.getTypeTrame(ack.getId());
		
		IData message = ack.getDonnees().get(0);
		IData donnee = ack.getDonnees().get(1);
		int id = -1;
		
                //DEBUG
                System.out.println(ack.toString());
                //DEBUG
                
		// ? { 0x52, string "OK", uint16 id }
		if(typeTrame == EFrameType.TrameRegistered &&
		   message instanceof Chaine) {
			IString chaine = (IString) message;
			
			if(! chaine.getChaine().equals("OK")) {
				IString messageErreur = (IString) donnee;
				throw new Exception("Inscription impossible ! : " + messageErreur.getChaine());
			} else {
				IUint16 entierNonSigne2 = (IUint16) donnee;
				id = entierNonSigne2.getEntier();
			}
		} else {
			throw new Exception("Impossible de lire la reponse du serveur !");
		}
		
		return id;
	}

	@Override
	public String getMessageStart(IFrame trameStart) throws Exception {
		IData donnee = trameStart.getDonnees().get(0);
		String message = "";
		
		if(donnee != null && donnee instanceof Chaine) {
			IString chaine = (IString) donnee;
			message = chaine.getChaine();
		} else {
			throw new Exception("La trame Start recue n'est pas correcte !");
		}
		
		return message;
	}

	@Override
	public String getMessagePause(IFrame tramePause) throws Exception {
		IData donnee = tramePause.getDonnees().get(0);
		String message = "";
		
		if(donnee != null && donnee instanceof Chaine) {
			IString chaine = (IString) donnee;
			message = chaine.getChaine();
		} else {
			throw new Exception("La trame Pause recue n'est pas correcte !");
		}
		
		return message;
	}

	@Override
	public int[] getPerdants(IFrame trameDeath) throws Exception {
            int[] perdants = null;
            int nbDonnees = trameDeath.getNbDonnees();
            
            if(nbDonnees == 1 || nbDonnees == 2) {
                perdants = new int[nbDonnees];
                IData donnee;
                
                for(int i = 0; i < nbDonnees; i++) {
                    donnee = trameDeath.getDonnees().get(i);
                    
                    if(donnee instanceof EntierNonSigne2) {
                        IUint16 entier = (IUint16) donnee; 
                        perdants[i] = entier.getEntier();
                    }  else {
                        throw new Exception("La trame Death recue n'est pas correcte !");
                    }
                }
                
            } 
            
            return perdants;
	}


    @Override
    public IPlayer[] getPositions(IFrame trameTurn) throws Exception {
        Joueur[] joueurs=new Joueur[4];
		int nbDonnees=trameTurn.getNbDonnees();
		if(nbDonnees == 17) {
			IData donnee;
			int j=0;
			int i=1;
	        while(i < nbDonnees) {//commence a 1 je sais pas koi faire du t qui represente les centieme de seconde ecoulees
	        	   if(i==5){
	        		   j++;
	        	   }
	        	   if(i==9){
	        		   j++;
	        	   }
	        	   if(i==13){
	        		   j++;
	        	   }
	        	   donnee=trameTurn.getDonnees().get(i);
	        	   if(donnee instanceof EntierNonSigne2) {
	                    EntierNonSigne2 id = (EntierNonSigne2) donnee; 
	                    joueurs[j].setId(id);
	                    i++;
	                }  else {
	                    throw new Exception("La trame turn recue n'est pas correcte !");
	                }
	        	   donnee=trameTurn.getDonnees().get(i);
	        	   if(donnee instanceof EntierNonSigne2) {
	        		   EntierNonSigne2 x = (EntierNonSigne2) donnee; 
	                    joueurs[j].setX(x);
	                    i++;
	                }  else {
	                    throw new Exception("La trame turn recue n'est pas correcte !");
	                } 
	        	   donnee=trameTurn.getDonnees().get(i);
	        	   if(donnee instanceof EntierNonSigne2) {
	        		   EntierNonSigne2 y = (EntierNonSigne2) donnee; 
	                    joueurs[j].setId(y);
	                    i++;
	                }  else {
	                    throw new Exception("La trame turn recue n'est pas correcte !");
	                } 
	        	   donnee=trameTurn.getDonnees().get(i);
	        	   if(donnee instanceof EntierNonSigne2) {
	        		   EntierNonSigne2 dir = (EntierNonSigne2) donnee; 
	                    joueurs[j].setId(dir);
	                    i++;
	                }  else {
	                    throw new Exception("La trame turn recue n'est pas correcte !");
	                } 
	               
	      }
            
        } 
		return joueurs;
    }
}
