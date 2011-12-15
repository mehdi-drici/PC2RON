package com.pc2ron.frame.data;

import com.pc2ron.interfaces.IString;
import com.pc2ron.interfaces.IData;
import com.pc2ron.interfaces.IDataFactory;
import com.pc2ron.interfaces.IUint8;
import com.pc2ron.interfaces.IUint16;
import com.pc2ron.interfaces.IUInt32;
import com.pc2ron.interfaces.IInt8;
import com.pc2ron.interfaces.IInt16;
import com.pc2ron.interfaces.IInt32;
import com.pc2ron.interfaces.IDouble;

public class DonneeFactory implements IDataFactory {
	private static IDataFactory instance;
	
	private DonneeFactory() {	
	}
	
	@Override
	public IData getDonnee(byte type) {
		IData donnee = null;
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
	public IUint8 getEntierNonSigne1(short entier) {
		return new EntierNonSigne1(entier);
	}

	@Override
	public IUint16 getEntierNonSigne2(int entier) {
		return new EntierNonSigne2(entier);
	}

	@Override
	public IUInt32 getEntierNonSigne4(long entier) {
		return new EntierNonSigne4(entier);
	}

	@Override
	public IInt8 getEntierSigne1(byte entier) {
		return new EntierSigne1(entier);
	}

	@Override
	public IInt16 getEntierSigne2(short entier) {
		return new EntierSigne2(entier);
	}

	@Override
	public IInt32 getEntierSigne4(int entier) {
		return new EntierSigne4(entier);
	}

	@Override
	public IDouble getFlottant(double flottant) {
		return new Flottant(flottant);
	}
	
	@Override
	public IString getChaine(String chaine) {
		return new Chaine(chaine);
	}
	
	public static IDataFactory getInstance() {
		if (null == instance) { // Premier appel
			instance = new DonneeFactory();
	    }
	    return instance;
	}
}
