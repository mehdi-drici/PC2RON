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

//	@Override
//	public void setValeur(DataInput in) {
//		try {
//			entier = in.readLong();
//		} catch (IOException e) {
//			e.printStackTrace();
//		}
//	}

	/*@Override
	public byte[] toBytes() {
		byte[] tab = new byte[taille()];
		
		// Entete
		tab[0] = ETypeDonnee.ENTIER_NON_SIGNE4.getType();
		
		// conversion de l'entier signé en entier non signé
		long entierNonSigne = entier & 0xffffffffL;
		
		// conversion en octets
		

		tab[1] = (byte)(entierNonSigne >>> 56);
		tab[2] = (byte)(entierNonSigne >>> 48);
		tab[3] = (byte)(entierNonSigne >>> 40);
		tab[4] = (byte)(entierNonSigne >>> 32);
		tab[5] = (byte)(entierNonSigne >>> 24);
		tab[6] = (byte)(entierNonSigne >>> 16);
		tab[7] = (byte)(entierNonSigne >>>  8);
		tab[8] = (byte)(entierNonSigne >>>  0);
		
		return tab;
	}*/
	/*
	@Override
	public ArrayList<Byte> toBytes() {
		long entierNonSigne = (entier & 0xffffffffL);
		
		ArrayList<Byte> tab=new ArrayList<Byte>();
		
		// Entete		
		tab.add(ETypeDonnee.ENTIER_NON_SIGNE4.getType());
						
		// Valeur		
		tab.add((byte)((entierNonSigne >>> 24)));
		tab.add((byte)((entierNonSigne >>> 16)));
		tab.add((byte)((entierNonSigne >>>  8)));
		tab.add((byte)(entierNonSigne));

		return tab;
	}
	*/
//	public int taille() {
//		return ETypeDonnee.ENTIER_NON_SIGNE4.getTaille() + 1;
//	}
	
	public String toString() {
		return ETypeDonnee.ENTIER_NON_SIGNE4.getStringType() + " " + getEntier();
	}
	
	@Override
	public <Data, Result> Result accept(IVisiteur<Data, Result> visiteur, Data donnees) {
		return visiteur.visit(this, donnees);
	}
}
