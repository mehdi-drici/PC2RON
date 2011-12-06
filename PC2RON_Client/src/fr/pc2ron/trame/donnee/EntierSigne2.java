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

//	@Override
//	public void setValeur(DataInput in) {
//		try {
//			entier = in.readShort();
//		} catch (IOException e) {
//			e.printStackTrace();
//		}
//	}
	/*
	@Override
	public ArrayList<Byte> toBytes() {
		ArrayList<Byte> tab=new ArrayList<Byte>();
		
		// Entete
		tab.add(ETypeDonnee.ENTIER_SIGNE2.getType());
		
		// Valeur
		//tab.add((byte) (getEntier() >>> 8));
		//tab.add((byte) (getEntier()));
		
		tab.add((byte)(getEntier() & 0xff));
		tab.add((byte)((getEntier() >> 8) & 0xff));
		
		return tab;
	}
	*/
	/*@Override
	public byte[] toBytes() {
		byte[] tab = new byte[taille()];
		
		// Entete
		tab[0] = ETypeDonnee.ENTIER_SIGNE2.getType();
		
		// Valeur
		tab[1] = (byte)(getEntier() & 0xff);
		tab[2] = (byte)((getEntier() >> 8) & 0xff);
		
		return tab;
	}*/
	
//	public int taille() {
//		return ETypeDonnee.ENTIER_SIGNE2.getTaille() + 1;
//	}
	
	public String toString() {
		return ETypeDonnee.ENTIER_SIGNE2.getStringType() + " " + getEntier();
	}
	
	@Override
	public <Data, Result> Result accept(IVisiteur<Data, Result> visiteur, Data donnees) {
		return visiteur.visit(this, donnees);
	}
}
