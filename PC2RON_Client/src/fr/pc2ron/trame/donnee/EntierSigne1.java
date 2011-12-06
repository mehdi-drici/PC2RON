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

//	@Override
//	public void setValeur(DataInput in) {
//		try {
//			this.entier = in.readByte();
//		} catch (IOException e) {
//			e.printStackTrace();
//		}
//	}

	/*
	@Override
	
	public ArrayList<Byte> toBytes() {
		ArrayList<Byte> tab=new ArrayList<Byte>();
		
		// Entete
		tab.add(ETypeDonnee.ENTIER_SIGNE1.getType());
		
		// Valeur
		tab.add(getEntier());
				
		return tab;
	}
	*/
//	@Override
//	public int taille() {
//		return ETypeDonnee.ENTIER_SIGNE1.getTaille() + 1;
//	}
	
	public String toString() {
		return ETypeDonnee.ENTIER_SIGNE1.getStringType() + " " + getEntier();
	}

	@Override
	public <Data, Result> Result accept(IVisiteur<Data, Result> visiteur, Data donnees) {
		return visiteur.visit(this, donnees);
	}
}
