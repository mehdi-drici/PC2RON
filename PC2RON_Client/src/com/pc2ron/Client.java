/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.pc2ron;

import com.pc2ron.interfaces.*;
import com.pc2ron.protocol.Protocol;
import com.pc2ron.frame.data.DataString;
import com.pc2ron.protocol.EOrder;
import java.util.ArrayList;


/**
 *
 * @author Mehdi Drici
 */
public class Client {
    public static void main(String[] argv) {       
        IProtocol protocol = Protocol.getInstance();
        short[] color = {50, 50, 50};
        ArrayList result = null;
        
        try {
            // Connexion du joueur
            protocol.connect("127.0.0.1", 5555);
            
            // Inscription du joueur
            protocol.register(color, "Mehdi");
            
            // Mise en ecoute du client
            result = protocol.readFrame();
            System.out.println(result.toString());
            
            // Envoi d'un ordre
            protocol.sendOrder(EOrder.LEFT);
            
            // Deconnexion
            protocol.disconnect();
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }
}
