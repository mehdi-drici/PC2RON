package fr.pc2ron;

import java.net.*;
import java.io.*;
import fr.pc2ron.interfaces.IProtocole;
import fr.pc2ron.protocole.EOrdre;
import fr.pc2ron.protocole.Protocole;
import java.util.ArrayList;

public class TestEnvoi {
    public static void main(String[] argv) {        
        try {
            short r=10;
            short v=10;
            short b=10;
            String nom="ken";
            IProtocole pro = Protocole.getInstance();
            ArrayList contenu;
            
            // Init
            pro.connexion("127.0.0.1", 5555);
            int id = pro.inscription(r, v, b, nom);
            System.out.println("ID : " + id);
            
            pro.envoyerOrdre(EOrdre.DROIT);
            
            //start
            contenu = pro.getContenuTrame();
            System.out.println("{Contenu} : " + contenu.toString());
            
            //pause
            contenu = pro.getContenuTrame();
            System.out.println("{Contenu} : " + contenu.toString());
            
            //users
            contenu = pro.getContenuTrame();
            System.out.println("{Contenu} : " + contenu.toString());
            
            //Thread.sleep(1000);
            pro.deconnexion();
        } catch (UnknownHostException e) {
            System.out.println("Unkonw exception " + e.getMessage());

        } catch (IOException e) {
            System.out.println("IOException caught " + e.getMessage());
        } catch (Exception e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        } 
    }
}