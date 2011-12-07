package fr.pc2ron.trame.donnee;

import fr.pc2ron.interfaces.IEntierNonSigne1;
import fr.pc2ron.interfaces.IVisiteur;

public class EntierNonSigne1 implements IEntierNonSigne1 {
	private short entier;
	
	public EntierNonSigne1() {
		entier = 0;
	}
	
	public EntierNonSigne1(short entier) {
		this.entier = (short) (entier & 0xff);
	}
	
	@Override
	public short getEntier() {
		return entier;
	}
	
        @Override
	public String toString() {
		return ETypeDonnee.ENTIER_NON_SIGNE1.getStringType() + " " + getEntier();
	}
	
	@Override
	public <Data, Result> Result accept(IVisiteur<Data, Result> visiteur, Data donnees) {
		return visiteur.visit(this, donnees);
	}
}
