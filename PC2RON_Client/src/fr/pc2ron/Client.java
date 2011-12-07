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

public class Client {
    public static void main(String[] argv) {        
        try {
            //Socket socket = new Socket("192.168.1.8", 5555);
            
            // Creation de la trame
            IDonneeFactory donneeFactory = DonneeFactory.getInstance();
            ITrameFactory trameFactory = TrameFactory.getInstance();
            IProtocole protocole = Protocole.getInstance();
            
    		IChaine chaine = donneeFactory.getChaine("bonjour à toi l'élève");  // OK
            IDonnee int8 = donneeFactory.getEntierSigne1((byte) 127);		  // OK
            IDonnee int16 = donneeFactory.getEntierSigne2((short) 32767); // OK
            IDonnee int32 = donneeFactory.getEntierSigne4(-2147483648);	      // OK
            IDonnee uint8 = donneeFactory.getEntierNonSigne1((short) -1);	  // OK
            IDonnee uint16 = donneeFactory.getEntierNonSigne2(-2);		  // OK
            IDonnee uint32 = donneeFactory.getEntierNonSigne4(-1);// OK
            //IDonnee flottant = donneeFactory.getFlottant(35);
            
    		ArrayList<IDonnee> donnees = new ArrayList<IDonnee>();
    		donnees.add(chaine);
    		donnees.add(int8);
                donnees.add(int8);
    		donnees.add(int16);
                donnees.add(int16);
    		donnees.add(int32);
    		donnees.add(uint8);
    		donnees.add(uint16);
    		donnees.add(uint32);
    		//donnees.add(flottant);
    		
    		ArrayList<IDonnee> donnees2 = new ArrayList<IDonnee>();
    		//donnees2.add(chaine);
    		donnees2.add(uint32);
    		donnees2.add(uint16);
    		
            ITrame trame = trameFactory.getTrame((byte)50, donnees);
            ITrame trame2 = trameFactory.getTrame((byte)50, donnees2);
            
            // Envoi des trames
            Socket socket = new Socket("127.0.0.1", 5555);
            DataOutputStream out = new DataOutputStream(socket.getOutputStream());
            DataInputStream in = new DataInputStream(socket.getInputStream());
            
            VisiteurEnvoiTrame envoi = new VisiteurEnvoiTrame();
            
            System.out.println("Trame 1 = " + trame.toString());
            System.out.println("Trame 2 = " + trame2.toString());
            System.out.println("Taille T1 = "  + chaine.getChaine().getBytes().length);
            envoi.visit(trame, out);
            
            Thread.sleep(2000);
            
            //envoi.visit(trame2, out);
            
            //Thread.sleep(1000);
            
            out.close();
            out.flush();
            socket.close();

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