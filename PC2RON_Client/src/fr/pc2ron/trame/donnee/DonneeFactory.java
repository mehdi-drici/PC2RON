package fr.pc2ron.trame.donnee;

import fr.pc2ron.interfaces.IChaine;
import fr.pc2ron.interfaces.IDonnee;
import fr.pc2ron.interfaces.IDonneeFactory;
import fr.pc2ron.interfaces.IEntierNonSigne1;
import fr.pc2ron.interfaces.IEntierNonSigne2;
import fr.pc2ron.interfaces.IEntierNonSigne4;
import fr.pc2ron.interfaces.IEntierSigne1;
import fr.pc2ron.interfaces.IEntierSigne2;
import fr.pc2ron.interfaces.IEntierSigne4;
import fr.pc2ron.interfaces.IFlottant;
import fr.pc2ron.interfaces.ITrameFactory;
import fr.pc2ron.trame.TrameFactory;

public class DonneeFactory implements IDonneeFactory {
	private static IDonneeFactory instance;
	
	private DonneeFactory() {	
	}
	
	@Override
	public IDonnee getDonnee(byte type) {
		IDonnee donnee = null;
		
		if(type == ETypeDonnee.ENTIER_SIGNE1.getType()) {
			donnee = new EntierSigne1();
		} else if (type == ETypeDonnee.ENTIER_SIGNE2.getType()) {
			donnee = new EntierSigne2();
			
		} else if (type == ETypeDonnee.ENTIER_SIGNE4.getType()) {
			donnee = new EntierSigne4();
			
		} else if (type == ETypeDonnee.ENTIER_NON_SIGNE1.getType()) {
			donnee = new EntierNonSigne1();
			
		} else if (type == ETypeDonnee.ENTIER_NON_SIGNE2.getType()) {
			donnee = new EntierNonSigne2();
			
		} else if (type == ETypeDonnee.ENTIER_NON_SIGNE4.getType()) {
			donnee = new EntierNonSigne4();
			
		} else if (type == ETypeDonnee.CHAINE.getType()) {
			donnee = new Chaine();
			
		} else if (type == ETypeDonnee.FLOTTANT.getType()) {
			donnee = new Flottant();
		}
		
		return donnee;
	}

	@Override
	public IEntierNonSigne1 getEntierNonSigne1(short entier) {
		return new EntierNonSigne1(entier);
	}

	@Override
	public IEntierNonSigne2 getEntierNonSigne2(int entier) {
		return new EntierNonSigne2(entier);
	}

	@Override
	public IEntierNonSigne4 getEntierNonSigne4(long entier) {
		return new EntierNonSigne4(entier);
	}

	@Override
	public IEntierSigne1 getEntierSigne1(byte entier) {
		return new EntierSigne1(entier);
	}

	@Override
	public IEntierSigne2 getEntierSigne2(short entier) {
		return new EntierSigne2(entier);
	}

	@Override
	public IEntierSigne4 getEntierSigne4(int entier) {
		return new EntierSigne4(entier);
	}

	@Override
	public IFlottant getFlottant(double flottant) {
		return new Flottant(flottant);
	}
	
	@Override
	public IChaine getChaine(String chaine) {
		return new Chaine(chaine);
	}
	
	public static IDonneeFactory getInstance() {
		if (null == instance) { // Premier appel
			instance = new DonneeFactory();
	    }
	    return instance;
	}
}
