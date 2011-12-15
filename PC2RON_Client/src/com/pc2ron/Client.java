/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.pc2ron;

import com.pc2ron.interfaces.*;
import com.pc2ron.protocol.EOrder;
import com.pc2ron.protocol.EFrameType;
import com.pc2ron.protocol.Protocol;
import com.pc2ron.protocol.FrameBuilder;
import com.pc2ron.frame.FrameReceiver;
import com.pc2ron.frame.FrameFactory;
import com.pc2ron.frame.FrameSenderVisitor;
import com.pc2ron.frame.data.Chaine;
import com.pc2ron.frame.data.DonneeFactory;
import com.pc2ron.frame.data.EntierNonSigne1;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;

/**
 *
 * @author mehdi
 */
public class Client {
    public static void main(String[] argv) {       
        //@fail
        // Creation de la trame
        IDataFactory donneeFactory = DonneeFactory.getInstance();
        IFrameFactory trameFactory = FrameFactory.getInstance();
        IProtocol protocole = Protocol.getInstance();
        
        //@fail
        FrameSenderVisitor envoi = new FrameSenderVisitor();
        IFrameReceiver recept = new FrameReceiver();
        IFrameBuilder tBuilder = FrameBuilder.getInstance();
        
        try {
            Socket sock = new Socket("127.0.0.1", 5555);
            DataOutputStream out = new DataOutputStream(sock.getOutputStream());
            DataInputStream in = new DataInputStream(sock.getInputStream());
            
            IFrame t1 = trameFactory.getTrame(EFrameType.TrameInit.getType());
            IFrame t2 = trameFactory.getTrame(EFrameType.TrameConnect.getType());
            IFrame t3 = trameFactory.getTrame(EFrameType.TrameOrder.getType());
            IFrame t4 = trameFactory.getTrame(EFrameType.TrameStart.getType());
            IFrame t5 = trameFactory.getTrameEnd();
            
            IData d1 = new Chaine("PC2RON?");
            IData d2 = new Chaine("PC2RON2011"); 
            IData nom = new Chaine("Toto"); 
            IData ordre = new Chaine("idle"); 
            
            IData d3 = donneeFactory.getEntierNonSigne1((short)10);
            IData d4 = donneeFactory.getEntierNonSigne2((int)10);
            IData d5 = donneeFactory.getEntierNonSigne4((long)10);
            
            IData d6 = donneeFactory.getEntierSigne1((byte)10);
            IData d7 = donneeFactory.getEntierSigne2((short)10);
            IData d8 = donneeFactory.getEntierSigne4(10);
            
            // Connexion
            t1.ajouterDonnee(d1);
            t1.ajouterDonnee(d2);
            
            // inscription
            t2.ajouterDonnee(d3);
            t2.ajouterDonnee(d3);
            t2.ajouterDonnee(d3);
            t2.ajouterDonnee(nom);
            
            // ordre
            t3.ajouterDonnee(ordre);
            envoi.visit(t3, out);
            //System.out.println("Trame recue: " + recept.recevoirTrame(in));
            
            // start (refusé)
            t4.ajouterDonnee(nom);
            
            // Envoi
            envoi.visit(t1, out);
            System.out.println("Trame recue: " + recept.recevoirTrame(in));
            
            
            envoi.visit(t2, out);
            System.out.println("Trame recue: " + recept.recevoirTrame(in));
            
            envoi.visit(t2, out);
            System.out.println("Trame recue: " + recept.recevoirTrame(in));
            
            envoi.visit(t3, out);
            
            envoi.visit(t4, out);
            //System.out.println("Trame recue: " + recept.recevoirTrame(in));
            
            //envoi.visit(t5, out);
            
            System.out.println("Trame recue: " + recept.recevoirTrame(in));
            System.out.println("Trame recue: " + recept.recevoirTrame(in));
            System.out.println("Trame recue: " + recept.recevoirTrame(in));
            System.out.println("Trame recue: " + recept.recevoirTrame(in));
            System.out.println("Trame recue: " + recept.recevoirTrame(in));
            
            System.out.println("Trame recue: " + recept.recevoirTrame(in));
            System.out.println("Trame recue: " + recept.recevoirTrame(in));
            System.out.println("Trame recue: " + recept.recevoirTrame(in));
            System.out.println("Trame recue: " + recept.recevoirTrame(in));
            System.out.println("Trame recue: " + recept.recevoirTrame(in));
            Thread.sleep(500000);
            //protocole.connexion("127.0.0.1", 5555);
            //protocole.inscription((short)56, (short)67, (short)350, "Mehdi");
            //protocole.inscription((short)56, (short)67, (short)350, "Mehdi");
            
            //protocole.deconnexion();
          
            // Trame User
            //protocole.getContenuTrame();
            
            // Decompte
            //protocole.getContenuTrame();
            //protocole.getContenuTrame();
            //protocole.getContenuTrame();
            //protocole.getContenuTrame();
            
            //protocole.envoyerOrdre(EOrdre.DROIT);*/
        } catch (Exception ex) {
            System.out.println("Connexion impossible");
            ex.printStackTrace();
        }
    }
}
