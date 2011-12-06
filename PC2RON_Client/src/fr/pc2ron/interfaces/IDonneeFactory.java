package fr.pc2ron.interfaces;

public interface IDonneeFactory {
	public IDonnee getDonnee(byte type);
	
	public IEntierSigne1 getEntierSigne1(byte valeur);
	public IEntierSigne2 getEntierSigne2(short valeur);
	public IEntierSigne4 getEntierSigne4(int valeur);
	
	public IEntierNonSigne1 getEntierNonSigne1(short valeur);
	public IEntierNonSigne2 getEntierNonSigne2(int valeur);
	public IEntierNonSigne4 getEntierNonSigne4(long valeur);
	
	public IFlottant getFlottant(double flottant);
	
	// En UTF-8
	public IChaine getChaine(String chaine);
}
