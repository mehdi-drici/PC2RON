package fr.pc2ron.trame.donnee;

import java.io.DataInput;
import java.io.IOException;

import fr.pc2ron.interfaces.IEntierSigne1;
import fr.pc2ron.interfaces.IVisiteur;

public class EntierSigne1 implements IEntierSigne1 {
	private byte entier;
	
	public EntierSigne1() {
		entier = 0;
	}
	
	public EntierSigne1(byte entier) {
		this.entier = entier;
	}
	
	public byte getEntier() {
		return entier;
	}
	
	public String toString() {
		return ETypeDonnee.ENTIER_SIGNE1.getStringType() + " " + getEntier();
	}

	@Override
	public <Data, Result> Result accept(IVisiteur<Data, Result> visiteur, Data donnees) {
		return visiteur.visit(this, donnees);
	}
}
