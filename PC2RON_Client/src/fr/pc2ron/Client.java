/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package fr.pc2ron;

import fr.pc2ron.interfaces.*;
import fr.pc2ron.protocole.EOrdre;
import fr.pc2ron.protocole.ETypeTrame;
import fr.pc2ron.protocole.Protocole;
import fr.pc2ron.protocole.TrameBuilder;
import fr.pc2ron.trame.ReceptionTrame;
import fr.pc2ron.trame.TrameFactory;
import fr.pc2ron.trame.VisiteurEnvoiTrame;
import fr.pc2ron.trame.donnee.Chaine;
import fr.pc2ron.trame.donnee.DonneeFactory;
import fr.pc2ron.trame.donnee.EntierNonSigne1;
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
        IDonneeFactory donneeFactory = DonneeFactory.getInstance();
        ITrameFactory trameFactory = TrameFactory.getInstance();
        IProtocole protocole = Protocole.getInstance();
        
        //@fail
        VisiteurEnvoiTrame envoi = new VisiteurEnvoiTrame();
        IReceptionTrame recept = new ReceptionTrame();
        ITrameBuilder tBuilder = TrameBuilder.getInstance();
        
        try {
            Socket sock = new Socket("127.0.0.1", 5555);
            DataOutputStream out = new DataOutputStream(sock.getOutputStream());
            DataInputStream in = new DataInputStream(sock.getInputStream());
            
            ITrame t1 = trameFactory.getTrame(ETypeTrame.TrameInit.getType());
            ITrame t2 = trameFactory.getTrame(ETypeTrame.TrameConnect.getType());
            ITrame t3 = trameFactory.getTrame(ETypeTrame.TrameOrder.getType());
            ITrame t4 = trameFactory.getTrame(ETypeTrame.TrameStart.getType());
            ITrame t5 = trameFactory.getTrameEnd();
            
            IDonnee d1 = new Chaine("PC2RON?");
            IDonnee d2 = new Chaine("PC2RON2011"); 
            IDonnee nom = new Chaine("Toto"); 
            IDonnee ordre = new Chaine("idle"); 
            
            IDonnee d3 = donneeFactory.getEntierNonSigne1((short)10);
            IDonnee d4 = donneeFactory.getEntierNonSigne2((int)10);
            IDonnee d5 = donneeFactory.getEntierNonSigne4((long)10);
            
            IDonnee d6 = donneeFactory.getEntierSigne1((byte)10);
            IDonnee d7 = donneeFactory.getEntierSigne2((short)10);
            IDonnee d8 = donneeFactory.getEntierSigne4(10);
            
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
            /*
            envoi.visit(t2, out);
            System.out.println("Trame recue: " + recept.recevoirTrame(in));
            
            envoi.visit(t3, out);
            
            envoi.visit(t4, out);
            //System.out.println("Trame recue: " + recept.recevoirTrame(in));
            
            envoi.visit(t5, out);
            System.out.println("Trame recue: " + recept.recevoirTrame(in));
            System.out.println("Trame recue: " + recept.recevoirTrame(in));
            System.out.println("Trame recue: " + recept.recevoirTrame(in));
            System.out.println("Trame recue: " + recept.recevoirTrame(in));*/
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
