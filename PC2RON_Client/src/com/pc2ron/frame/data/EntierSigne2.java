package com.pc2ron.frame.data;

import java.io.DataInput;
import java.io.IOException;
import java.util.ArrayList;

import com.pc2ron.interfaces.IInt16;
import com.pc2ron.interfaces.IVisitor;

public class EntierSigne2 implements IInt16 {
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
	
	public String toString() {
		return ETypeDonnee.ENTIER_SIGNE2.getStringType() + " " + getEntier();
	}
	
	@Override
	public <Data, Result> Result accept(IVisitor<Data, Result> visiteur, Data donnees) {
		return visiteur.visit(this, donnees);
	}
}
