package fr.pc2ron;

import fr.pc2ron.interfaces.IChaine;
import java.net.*;
import java.util.ArrayList;
import java.io.*;

import fr.pc2ron.interfaces.IDonnee;
import fr.pc2ron.interfaces.IDonneeFactory;
import fr.pc2ron.interfaces.IProtocole;
import fr.pc2ron.interfaces.ITrame;
import fr.pc2ron.interfaces.ITrameFactory;
import fr.pc2ron.interfaces.IVisiteur;
import fr.pc2ron.protocole.Protocole;
import fr.pc2ron.trame.Trame;
import fr.pc2ron.trame.TrameFactory;
import fr.pc2ron.trame.VisiteurEnvoiTrame;
import fr.pc2ron.trame.donnee.DonneeFactory;

public class TestEnvoi {
    public static void main(String[] argv) {        
        try {
            short r=10;
            short v=10;
            short b=10;
            String nom="ken";
            IProtocole pro = Protocole.getInstance();
            
            pro.connexion("127.0.0.1", 5555);
            pro.inscription(r, v, b, nom);
            
            //Thread.sleep(1000);

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