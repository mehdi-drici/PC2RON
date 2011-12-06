package fr.pc2ron.trame.donnee;

import java.io.DataInput;
import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.util.ArrayList;

import fr.pc2ron.interfaces.IFlottant;
import fr.pc2ron.interfaces.IVisiteur;

public class Flottant implements IFlottant {
	private double flottant;
	
	public Flottant() {
		flottant = 0.0;
	}
	
	public Flottant(double flottant) {
		this.flottant = flottant;
	}
	
	@Override
	public double getFlottant() {
		return flottant;
	}

//	@Override
//	public void setValeur(DataInput in) {
//		try {
//			flottant = in.readDouble();
//		} catch (IOException e) {
//			e.printStackTrace();
//		}
//	}

	/*@Override
	public byte[] toBytes() {
		byte[] tab = new byte[taille()];
		long l = Double.doubleToRawLongBits(flottant);
		
	    tab[0] = ETypeDonnee.FLOTTANT.getType();
	    	
	    tab[1] = (byte)((l >> 56) & 0xff);
	    tab[2] = (byte)((l >> 48) & 0xff);
	    tab[3] = (byte)((l >> 40) & 0xff);
	    tab[4] = (byte)((l >> 32) & 0xff);
	    tab[5] = (byte)((l >> 24) & 0xff);
	    tab[6] = (byte)((l >> 16) & 0xff);
	    tab[7] = (byte)((l >> 8) & 0xff);
	    tab[8] = (byte)((l >> 0) & 0xff);
	    
	    
		return tab;
	}*/
	/*
	@Override
	public ArrayList<Byte> toBytes() {
		ArrayList<Byte> tab=new ArrayList<Byte>();
		long l = Double.doubleToRawLongBits(flottant);
		// Entete
		tab.add(ETypeDonnee.FLOTTANT.getType());
		// Valeur
		tab.add((byte)((l >> 56) & 0xff));
		tab.add((byte)((l >> 48) & 0xff));
		tab.add((byte)((l >> 40) & 0xff));
		tab.add((byte)((l >> 32) & 0xff));
		tab.add((byte)((l >> 24) & 0xff));
		tab.add((byte)((l >> 16) & 0xff));
		tab.add((byte)((l >> 8) & 0xff));
		tab.add((byte)((l >> 0) & 0xff));
				
		return tab;
	}
	*/
	
//	public int taille() {
//		return ETypeDonnee.FLOTTANT.getTaille() + 1;
//	}
	
	public String toString() {
		return ETypeDonnee.FLOTTANT.getStringType() + " " + getFlottant();
	}
	
	@Override
	public <Data, Result> Result accept(IVisiteur<Data, Result> visiteur, Data donnees) {
		return visiteur.visit(this, donnees);
	}
}
