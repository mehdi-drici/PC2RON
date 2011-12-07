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

public class DonneeFactory implements IDonneeFactory {
	private static IDonneeFactory instance;
	
	private DonneeFactory() {	
	}
	
	@Override
	public IDonnee getDonnee(byte type) {
		IDonnee donnee = null;
		ETypeDonnee eType = ETypeDonnee.getTypeDonnee(type);
                
                switch(eType) {
                    case ENTIER_SIGNE1:
                        donnee = new EntierSigne1();
                        break;
                    
                    case ENTIER_SIGNE2:
                        donnee = new EntierSigne2();
                        break;
                        
                    case ENTIER_SIGNE4:
                        donnee = new EntierSigne4();
                        break;
                    
                    case ENTIER_NON_SIGNE1:
                        donnee = new EntierNonSigne1();
                        break;
                        
                    case ENTIER_NON_SIGNE2:
                        donnee = new EntierNonSigne2();
                        break;
                        
                    case ENTIER_NON_SIGNE4:
                        donnee = new EntierNonSigne4();
                        break;
                        
                    case CHAINE:
                        donnee = new Chaine();
                        break;
                        
                    case FLOTTANT:
                        donnee = new Flottant();
                        break;
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
