package fr.pc2ron;

import java.util.ArrayList;

import fr.pc2ron.interfaces.IDonnee;
import fr.pc2ron.interfaces.IDonneeFactory;
import fr.pc2ron.interfaces.ITrame;
import fr.pc2ron.interfaces.ITrameFactory;
import fr.pc2ron.trame.TrameFactory;
import fr.pc2ron.trame.donnee.DonneeFactory;

public class TestTrame {
	public static void main(String[] args) {
		IDonneeFactory donneeFactory = DonneeFactory.getInstance();
		ITrameFactory trameFactory = TrameFactory.getInstance();
		
		// Création des données
		IDonnee chaine = donneeFactory.getChaine("OK");
		byte b = 7;
		
		IDonnee entier1 = donneeFactory.getEntierSigne1(b);
		IDonnee entier2 = donneeFactory.getEntierSigne2((short) 7);
		IDonnee entier4 = donneeFactory.getEntierSigne4(7);
		
		IDonnee entierNonSigne1 = donneeFactory.getEntierNonSigne1((short) -59);
		IDonnee entierNonSigne2 = donneeFactory.getEntierNonSigne2((char) 127);
		IDonnee entierNonSigne4 = donneeFactory.getEntierNonSigne4((long) -77);
		
		IDonnee flottant = donneeFactory.getFlottant((double)2.78);
		
		/* Ajout des données*/
		ArrayList<IDonnee> donnees = new ArrayList<IDonnee>();
		donnees.add(chaine);
		donnees.add(entier1);
		donnees.add(entier2);
		donnees.add(entier4);
		
		donnees.add(entierNonSigne1);
		donnees.add(entierNonSigne2);
		donnees.add(entierNonSigne4);
		
		donnees.add(flottant);
		
		// Création de la trame
		ITrame trame = trameFactory.getTrame((byte)50, donnees);
		
		ITrame trame2 = trameFactory.getTrame((byte)50);
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
