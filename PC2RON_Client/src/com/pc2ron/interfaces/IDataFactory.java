package com.pc2ron.interfaces;

public interface IDataFactory {
	public IData getDonnee(byte type);
	
	public IInt8 getEntierSigne1(byte valeur);
	public IInt16 getEntierSigne2(short valeur);
	public IInt32 getEntierSigne4(int valeur);
	
	public IUint8 getEntierNonSigne1(short valeur);
	public IUint16 getEntierNonSigne2(int valeur);
	public IUInt32 getEntierNonSigne4(long valeur);
	
	public IDouble getFlottant(double flottant);
	
	// En UTF-8
	public IString getChaine(String chaine);
}
