package com.pc2ron;

import java.util.ArrayList;

import com.pc2ron.interfaces.IData;
import com.pc2ron.interfaces.IDataFactory;
import com.pc2ron.interfaces.IFrame;
import com.pc2ron.interfaces.IFrameFactory;
import com.pc2ron.frame.FrameFactory;
import com.pc2ron.frame.data.DataFactory;

public class Test {
	public static void main(String[] args) {
		IDataFactory donneeFactory = DataFactory.getInstance();
		IFrameFactory trameFactory = FrameFactory.getInstance();
		
		// Création des données
		IData chaine = donneeFactory.createString("OK");
		byte b = 7;
		
		IData entier1 = donneeFactory.createInt8(b);
		IData entier2 = donneeFactory.createInt16((short) 7);
		IData entier4 = donneeFactory.createInt32(7);
		
		IData entierNonSigne1 = donneeFactory.createUint8((short) -59);
		IData entierNonSigne2 = donneeFactory.createUint16((char) 127);
		IData entierNonSigne4 = donneeFactory.createUint32((long) -77);
		
		IData flottant = donneeFactory.createDouble((double)2.78);
		
		/* Ajout des données*/
		ArrayList<IData> donnees = new ArrayList<IData>();
		donnees.add(chaine);
		donnees.add(entier1);
		donnees.add(entier2);
		donnees.add(entier4);
		
		donnees.add(entierNonSigne1);
		donnees.add(entierNonSigne2);
		donnees.add(entierNonSigne4);
		
		donnees.add(flottant);
		
		// Création de la trame
		IFrame trame = trameFactory.createFrame((byte)50, donnees);
		
		IFrame trame2 = trameFactory.createFrame((byte)50);
		trame2.addData(chaine);
		trame2.addData(entier1);
		
		/*trame2.ajouterDonnee(entier2);
		trame2.ajouterDonnee(entier4);
		trame2.ajouterDonnee(entierNonSigne1);
		trame2.ajouterDonnee(entierNonSigne2);
		trame2.ajouterDonnee(entierNonSigne4);
		trame2.ajouterDonnee(flottant);*/
		
		System.out.println("Nombre de données (getDonnees().size())= " + trame.getData().get(0).toString());
		
		System.out.println("Nombre de données (getNbDonnees) = " + trame.getDataSize());
		System.out.println("Nombre de données (getDonnees().size())= " + trame.getData().size());
		System.out.println("Trame : " + trame.toString() + "\n\n");
		
		System.out.println("Nombre de données (getNbDonnees) = " + trame2.getDataSize());
		System.out.println("Nombre de données (getDonnees().size())= " + trame2.getData().size());
		System.out.println("Trame2 : " + trame2.toString());
	}
}
