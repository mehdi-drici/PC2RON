package com.pc2ron;

import java.util.ArrayList;

import com.pc2ron.interfaces.IData;
import com.pc2ron.interfaces.IDataFactory;
import com.pc2ron.interfaces.IFrame;
import com.pc2ron.interfaces.IFrameFactory;
import com.pc2ron.frame.FrameFactory;
import com.pc2ron.frame.data.DonneeFactory;

public class Test {
	public static void main(String[] args) {
		IDataFactory donneeFactory = DonneeFactory.getInstance();
		IFrameFactory trameFactory = FrameFactory.getInstance();
		
		// Création des données
		IData chaine = donneeFactory.getChaine("OK");
		byte b = 7;
		
		IData entier1 = donneeFactory.getEntierSigne1(b);
		IData entier2 = donneeFactory.getEntierSigne2((short) 7);
		IData entier4 = donneeFactory.getEntierSigne4(7);
		
		IData entierNonSigne1 = donneeFactory.getEntierNonSigne1((short) -59);
		IData entierNonSigne2 = donneeFactory.getEntierNonSigne2((char) 127);
		IData entierNonSigne4 = donneeFactory.getEntierNonSigne4((long) -77);
		
		IData flottant = donneeFactory.getFlottant((double)2.78);
		
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
		IFrame trame = trameFactory.getTrame((byte)50, donnees);
		
		IFrame trame2 = trameFactory.getTrame((byte)50);
		trame2.ajouterDonnee(chaine);
		trame2.ajouterDonnee(entier1);
		
		/*trame2.ajouterDonnee(entier2);
		trame2.ajouterDonnee(entier4);
		trame2.ajouterDonnee(entierNonSigne1);
		trame2.ajouterDonnee(entierNonSigne2);
		trame2.ajouterDonnee(entierNonSigne4);
		trame2.ajouterDonnee(flottant);*/
		
		System.out.println("Nombre de données (getDonnees().size())= " + trame.getDonnees().get(0).toString());
		
		System.out.println("Nombre de données (getNbDonnees) = " + trame.getNbDonnees());
		System.out.println("Nombre de données (getDonnees().size())= " + trame.getDonnees().size());
		System.out.println("Trame : " + trame.toString() + "\n\n");
		
		System.out.println("Nombre de données (getNbDonnees) = " + trame2.getNbDonnees());
		System.out.println("Nombre de données (getDonnees().size())= " + trame2.getDonnees().size());
		System.out.println("Trame2 : " + trame2.toString());
	}
}
