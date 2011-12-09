package fr.pc2ron;

import fr.pc2ron.interfaces.IChaine;
import fr.pc2ron.interfaces.IDonnee;
import fr.pc2ron.interfaces.IProtocole;
import java.io.DataInputStream;
import java.io.IOException;
import java.net.Socket;
import java.net.UnknownHostException;

import fr.pc2ron.interfaces.IReceptionTrame;
import fr.pc2ron.interfaces.ITrame;
import fr.pc2ron.protocole.Protocole;
import fr.pc2ron.trame.ReceptionTrame;

public class TestReception {
    public static void main(String[] argv) {        
        try {
            IProtocole proto = Protocole.getInstance();
            proto.connexion("127.0.0.1", 5555);
            
            // start
            proto.getContenuTrame();

            // pause
            proto.getContenuTrame();
            
            // joueurs
            proto.getContenuTrame();
        } catch (Exception e1) {
            // TODO Auto-generated catch block
            e1.printStackTrace();
        }
    }
}
