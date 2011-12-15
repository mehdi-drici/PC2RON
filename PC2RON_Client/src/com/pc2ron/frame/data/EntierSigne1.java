package com.pc2ron.frame.data;

import java.io.DataInput;
import java.io.IOException;

import com.pc2ron.interfaces.IInt8;
import com.pc2ron.interfaces.IVisitor;

public class EntierSigne1 implements IInt8 {
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
	
	public String toString() {
		return ETypeDonnee.ENTIER_SIGNE1.getStringType() + " " + getEntier();
	}

	@Override
	public <Data, Result> Result accept(IVisitor<Data, Result> visiteur, Data donnees) {
		return visiteur.visit(this, donnees);
	}
}
