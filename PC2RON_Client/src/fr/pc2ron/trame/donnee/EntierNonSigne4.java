package fr.pc2ron.trame.donnee;

import java.io.DataInput;
import java.io.IOException;
import java.util.ArrayList;

import fr.pc2ron.interfaces.IEntierNonSigne4;
import fr.pc2ron.interfaces.IVisiteur;

public class EntierNonSigne4 implements IEntierNonSigne4 {
	public long entier;
	
	public EntierNonSigne4() {
		entier = 0;
	}
	
	public EntierNonSigne4(long entier) {
		this.entier = entier & 0xffffffffL;
	}
	
	@Override
	public long getEntier() {
		return entier;
	}
	
	public String toString() {
		return ETypeDonnee.ENTIER_NON_SIGNE4.getStringType() + " " + getEntier();
	}
	
	@Override
	public <Data, Result> Result accept(IVisiteur<Data, Result> visiteur, Data donnees) {
		return visiteur.visit(this, donnees);
	}
}
