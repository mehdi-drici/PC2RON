package fr.pc2ron.protocole;

import java.util.ArrayList;

import fr.pc2ron.interfaces.IDonnee;
import fr.pc2ron.interfaces.IDonneeFactory;
import fr.pc2ron.interfaces.IProtocole;
import fr.pc2ron.interfaces.ITrame;
import fr.pc2ron.interfaces.ITrameBuilder;
import fr.pc2ron.interfaces.ITrameFactory;
import fr.pc2ron.trame.TrameFactory;
import fr.pc2ron.trame.donnee.DonneeFactory;

public class TrameBuilder implements ITrameBuilder {
	private static ITrameBuilder instance;
	
	private TrameBuilder() {
	}
	
	@Override
	public ITrame creerTrameConnect(short r, short v, short b, String nom) {
		IDonneeFactory donneeFactory = DonneeFactory.getInstance();
		ITrameFactory trameFactory = TrameFactory.getInstance();
		
		ArrayList<IDonnee> listeDonnees = new ArrayList<IDonnee>();
		IDonnee rouge = donneeFactory.getEntierNonSigne1(r);
		IDonnee vert = donneeFactory.getEntierNonSigne1(v);
		IDonnee bleu = donneeFactory.getEntierNonSigne1(b);
		IDonnee nomM = donneeFactory.getChaine(nom);
		
		listeDonnees.add(rouge);
		listeDonnees.add(vert);
		listeDonnees.add(bleu);
		listeDonnees.add(nomM);
		
		ITrame trame = trameFactory.getTrame(ETypeTrame.TrameConnect.getType(), listeDonnees);
		
		return trame;
	}

	@Override
	public ITrame creerTrameInit() {
		IDonneeFactory donneeFactory = DonneeFactory.getInstance();
		ITrameFactory trameFactory = TrameFactory.getInstance();
		
		IDonnee chaine1 = donneeFactory.getChaine("PC2RON?");
		IDonnee chaine2 = donneeFactory.getChaine("PC2RON2011");
		
		ArrayList<IDonnee> listeDonnees = new ArrayList<IDonnee>();
		listeDonnees.add(chaine1);
		listeDonnees.add(chaine2);
		ITrame trame = trameFactory.getTrame(ETypeTrame.TrameInit.getType(), listeDonnees);
		
		return trame;
	}

	@Override
	public ITrame creerTrameOrder(EOrdre ordre) {
		IDonneeFactory donneeFactory = DonneeFactory.getInstance();
		ITrameFactory trameFactory = TrameFactory.getInstance();
		
		IDonnee chaine = donneeFactory.getChaine(ordre.getStringOrdre());
		
		ITrame trame = trameFactory.getTrame(ETypeTrame.TrameInit.getType(), chaine);
		
		return trame;
	}

	public static ITrameBuilder getInstance() {
		if (null == instance) { // Premier appel
			instance = new TrameBuilder();
	    }
	    return instance;
	}
}
