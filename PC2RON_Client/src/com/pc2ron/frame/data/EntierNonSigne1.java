package com.pc2ron.frame.data;

import com.pc2ron.interfaces.IUint8;
import com.pc2ron.interfaces.IVisitor;

public class EntierNonSigne1 implements IUint8 {
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
	
        @Override
	public String toString() {
		return ETypeDonnee.ENTIER_NON_SIGNE1.getStringType() + " " + getEntier();
	}
	
	@Override
	public <Data, Result> Result accept(IVisitor<Data, Result> visiteur, Data donnees) {
		return visiteur.visit(this, donnees);
	}
}
