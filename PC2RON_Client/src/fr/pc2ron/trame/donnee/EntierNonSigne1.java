package fr.pc2ron.trame.donnee;

import java.io.DataInput;
import java.io.IOException;
import java.util.ArrayList;

import fr.pc2ron.interfaces.IEntierNonSigne1;
import fr.pc2ron.interfaces.IVisiteur;

public class EntierNonSigne1 implements IEntierNonSigne1 {
	private short entier;
	
	public EntierNonSigne1() {
		entier = 0;
	}
	
	public EntierNonSigne1(short entier) {
		this.entier = (short) (entier & 0xff);
	}
	
	@Override
	public short getEntier() {
		return entier;
	}

//	@Override
//	public void setValeur(DataInput in) {
//		try {
//			//entier = in.readShort();
//			entier = (short) in.readUnsignedByte();
//		} catch (IOException e) {
//			e.printStackTrace();
//		}
//	}
	/*
	@Override
	public ArrayList<Byte> toBytes() {
		short entierNonSigne = (short) (entier & 0xff);
		ArrayList<Byte> tab=new ArrayList<Byte>();
		
		// Entete				
		tab.add(ETypeDonnee.ENTIER_NON_SIGNE1.getType());
		
		// Valeur
		tab.add((byte)(entierNonSigne));
		//tab.add((byte)((entierNonSigne >> 8) & 0xff));
				
		return tab;
	}
	*/
//	public int taille() {
//		return ETypeDonnee.ENTIER_NON_SIGNE1.getTaille() + 1;
//	}
	
	public String toString() {
		return ETypeDonnee.ENTIER_NON_SIGNE1.getStringType() + " " + getEntier();
	}
	
	@Override
	public <Data, Result> Result accept(IVisiteur<Data, Result> visiteur, Data donnees) {
		return visiteur.visit(this, donnees);
	}
}
