package com.pc2ron.frame.data;

import java.io.DataInput;
import java.io.IOException;
import java.util.ArrayList;

import com.pc2ron.interfaces.IUInt32;
import com.pc2ron.interfaces.IVisitor;

public class EntierNonSigne4 implements IUInt32 {
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
	
	public String toString() {
		return ETypeDonnee.ENTIER_NON_SIGNE4.getStringType() + " " + getEntier();
	}
	
	@Override
	public <Data, Result> Result accept(IVisitor<Data, Result> visiteur, Data donnees) {
		return visiteur.visit(this, donnees);
	}
}
