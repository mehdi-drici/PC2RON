package fr.pc2ron.trame.donnee;

import java.io.DataInput;
import java.io.IOException;
import java.util.ArrayList;

import fr.pc2ron.interfaces.IEntierNonSigne4;
import fr.pc2ron.interfaces.IEntierSigne4;
import fr.pc2ron.interfaces.IVisiteur;

public class EntierSigne4 implements IEntierSigne4 {
	private int entier;
	
	public EntierSigne4() {
		entier = 0;
	}
	
	public EntierSigne4(int entier) {
		this.entier = entier;
	}
	
	@Override
	public int getEntier() {
		return entier;
	}
	
	public String toString() {
		return ETypeDonnee.ENTIER_SIGNE4.getStringType() + " " + getEntier();
	}
	
	@Override
	public <Data, Result> Result accept(IVisiteur<Data, Result> visiteur, Data donnees) {
		return visiteur.visit(this, donnees);
	}
}
