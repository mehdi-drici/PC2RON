package fr.pc2ron.trame.donnee;

import java.io.DataInput;
import java.io.IOException;
import java.util.ArrayList;

import fr.pc2ron.interfaces.IEntierSigne2;
import fr.pc2ron.interfaces.IVisiteur;

public class EntierSigne2 implements IEntierSigne2 {
	private short entier;
	
	public EntierSigne2() {
		entier = 0;
	}
	
	public EntierSigne2(short entier) {
		this.entier = entier;
	}
	
	@Override
	public short getEntier() {
		return entier;
	}
	
	public String toString() {
		return ETypeDonnee.ENTIER_SIGNE2.getStringType() + " " + getEntier();
	}
	
	@Override
	public <Data, Result> Result accept(IVisiteur<Data, Result> visiteur, Data donnees) {
		return visiteur.visit(this, donnees);
	}
}
