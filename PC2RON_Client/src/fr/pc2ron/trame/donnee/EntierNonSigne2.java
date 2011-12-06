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

//	@Override
//	public void setValeur(DataInput in) {
//		try {
//			entier = in.readUnsignedShort();
//		} catch (IOException e) {
//			e.printStackTrace();
//		}
//	}
	/*
	@Override
	public ArrayList<Byte> toBytes() {
		int entierNonSigne = entier & 0xffff;
		
		System.out.println("entier non signe 2 = " + entierNonSigne);
		System.out.println("entier signe = " + entier);
		
		ArrayList<Byte> tab=new ArrayList<Byte>();
		
		// Entete		
		tab.add(ETypeDonnee.ENTIER_NON_SIGNE2.getType());
				
		// Valeur
		tab.add((byte)((entierNonSigne >>> 8)));
		tab.add((byte)(entierNonSigne));
						
		return tab;
	}
	*/
	
	/*public byte[] toBytes() {
		byte[] tab = new byte[taille()];
		
		// Entete
		tab[0] = ETypeDonnee.ENTIER_NON_SIGNE2.getType();
		
		// Valeur
		tab[1] = (byte)(getEntier() & 0xff);
		tab[2] = (byte)((getEntier() >> 8) & 0xff);
		
		return tab;
	}*/
	
//	public int taille() {
//		return ETypeDonnee.ENTIER_NON_SIGNE2.getTaille();
//	}
	
	public String toString() {
		return ETypeDonnee.ENTIER_NON_SIGNE2.getStringType() + " " + getEntier();
	}
	
	@Override
	public <Data, Result> Result accept(IVisiteur<Data, Result> visiteur, Data donnees) {
		return visiteur.visit(this, donnees);
	}
}
