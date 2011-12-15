package com.pc2ron.frame.data;

import java.io.DataInput;
import java.io.IOException;
import java.util.ArrayList;

import com.pc2ron.interfaces.IUint16;
import com.pc2ron.interfaces.IVisitor;

public class EntierNonSigne2 implements IUint16 {
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
	
	public String toString() {
		return ETypeDonnee.ENTIER_NON_SIGNE2.getStringType() + " " + getEntier();
	}
	
	@Override
	public <Data, Result> Result accept(IVisitor<Data, Result> visiteur, Data donnees) {
		return visiteur.visit(this, donnees);
	}
}
