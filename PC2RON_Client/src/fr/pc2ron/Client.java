/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package fr.pc2ron;

import fr.pc2ron.interfaces.*;
import fr.pc2ron.protocole.EOrdre;
import fr.pc2ron.protocole.Protocole;
import fr.pc2ron.trame.TrameFactory;
import fr.pc2ron.trame.donnee.DonneeFactory;

/**
 *
 * @author mehdi
 */
public class Client {
    public static void main(String[] argv) {       
        //Socket socket = new Socket("192.168.1.8", 5555);
            
        // Creation de la trame
        IDonneeFactory donneeFactory = DonneeFactory.getInstance();
        ITrameFactory trameFactory = TrameFactory.getInstance();
        IProtocole protocole = Protocole.getInstance();
        
        try {
            protocole.connexion("127.0.0.1", 5555);
            protocole.inscription((short)56, (short)67, (short)350, "Mehdi");
            
            // Trame User
            //protocole.getContenuTrame();
            
            // Decompte
            protocole.getContenuTrame();
            protocole.getContenuTrame();
            protocole.getContenuTrame();
            protocole.getContenuTrame();
            
            protocole.envoyerOrdre(EOrdre.DROIT);
        } catch (Exception ex) {
            System.out.println("Connexion impossible");
            ex.printStackTrace();
        }
    }
}
