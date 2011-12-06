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

//	@Override
//	public void setValeur(DataInput in) {
//		try {
//			entier = in.readInt();
//		} catch (IOException e) {
//			e.printStackTrace();
//		}
//
//	}

	/*@Override
	public byte[] toBytes() {
		byte[] tab = new byte[taille()];
		
		// Entete
		tab[0] = ETypeDonnee.ENTIER_SIGNE2.getType();
		
		// Valeur
		tab[1] =(byte)( getEntier() >> 24 );
		tab[2] =(byte)( (getEntier() << 8) >> 24 );
		tab[3] =(byte)( (getEntier() << 16) >> 24 );
		tab[4] =(byte)( (getEntier() << 24) >> 24 );
		
		return tab;
	}*/
	/*
	@Override
	public ArrayList<Byte> toBytes() {
		ArrayList<Byte> tab=new ArrayList<Byte>();
		
		// Entete
		tab.add(ETypeDonnee.ENTIER_SIGNE4.getType());
		
		// Valeur
		tab.add((byte)( getEntier() >> 24 ));
		tab.add((byte)( (getEntier() << 8) >> 24 ));
		tab.add((byte)( (getEntier() << 16) >> 24 ));
		tab.add((byte)( (getEntier() << 24) >> 24 ));
				
		return tab;
	}
	*/
//	public int taille() {
//		return ETypeDonnee.ENTIER_SIGNE4.getTaille();
//	}
	
	public String toString() {
		return ETypeDonnee.ENTIER_SIGNE4.getStringType() + " " + getEntier();
	}
	
	@Override
	public <Data, Result> Result accept(IVisiteur<Data, Result> visiteur, Data donnees) {
		return visiteur.visit(this, donnees);
	}
}
