package fr.pc2ron;

import fr.pc2ron.interfaces.IChaine;
import java.io.DataInputStream;
import java.io.IOException;
import java.net.Socket;
import java.net.UnknownHostException;

import fr.pc2ron.interfaces.IReceptionTrame;
import fr.pc2ron.interfaces.ITrame;
import fr.pc2ron.trame.ReceptionTrame;

public class TestReception {
	public static void main(String[] argv) {        
        Socket socket;
		try {
			socket = new Socket("127.0.0.1", 5555);
		
			DataInputStream in = new DataInputStream(socket.getInputStream());        
			IReceptionTrame reception = new ReceptionTrame();
			//ITrame t = reception.recevoirTrame(in);
			IChaine t = reception.recevoirChaine(in);
			System.out.println("Trame recue : " + t.toString());
			//System.out.println("Byte recu = " + in.readByte());
			
		} catch (UnknownHostException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		} catch (IOException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
	}
}
