/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package fr.pc2ron;

import fr.pc2ron.interfaces.*;
import fr.pc2ron.protocole.Protocole;
import fr.pc2ron.trame.TrameFactory;
import fr.pc2ron.trame.donnee.DonneeFactory;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author mehdi
 */
public class Client {
    public static void main(String[] argv) {                
        IProtocole protocole = Protocole.getInstance();
        
        try {
            protocole.connexion("127.0.0.1", 5555);
            protocole.inscription((short)50, (short)50, (short)50, "Superman");
            System.out.println("Connexion etablie !");
        } catch (Exception ex) {
            System.out.println("Connexion impossible");
            ex.printStackTrace();
        }
    }
}
