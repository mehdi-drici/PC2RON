package fr.pc2ron.trame.donnee;

import java.io.DataInput;
import java.io.IOException;
import java.util.ArrayList;

import fr.pc2ron.interfaces.IEntierNonSigne2;
import fr.pc2ron.interfaces.IVisiteur;

public class EntierNonSigne2 implements IEntierNonSigne2 {
	private int entier;
	
	public EntierNonSigne2() {
		entier = 0;
	}
	
	public EntierNonSigne2(int entier) {
		this.entier = entier & 0xffff;	
	}
	
	@Override
	public int getEntier() {
		// TODO Auto-generated method stub
		return entier;
	}
	
	public String toString() {
		return ETypeDonnee.ENTIER_NON_SIGNE2.getStringType() + " " + getEntier();
	}
	
	@Override
	public <Data, Result> Result accept(IVisiteur<Data, Result> visiteur, Data donnees) {
		return visiteur.visit(this, donnees);
	}
}
