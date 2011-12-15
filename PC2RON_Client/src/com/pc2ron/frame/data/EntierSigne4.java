package com.pc2ron.frame.data;

import java.io.DataInput;
import java.io.IOException;
import java.util.ArrayList;

import com.pc2ron.interfaces.IUInt32;
import com.pc2ron.interfaces.IInt32;
import com.pc2ron.interfaces.IVisitor;

public class EntierSigne4 implements IInt32 {
	private int entier;
	
	public EntierSigne4() {
		entier = 0;
	}
	
	public EntierSigne4(int entier) {
		this.entier = entier;
	}
	
	@Override
	public int getEntier() {
		return entier;
	}
	
	public String toString() {
		return ETypeDonnee.ENTIER_SIGNE4.getStringType() + " " + getEntier();
	}
	
	@Override
	public <Data, Result> Result accept(IVisitor<Data, Result> visiteur, Data donnees) {
		return visiteur.visit(this, donnees);
	}
}
