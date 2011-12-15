package com.pc2ron.frame;

import java.util.ArrayList;
import java.util.List;

import com.pc2ron.interfaces.IData;
import com.pc2ron.interfaces.IFrame;

public class Frame implements IFrame {
	private ArrayList<IData> donnees = null;
        
        // Entiers non signes 1
	private short typeFanion;
	private short id;
	
	public Frame() {
            this.donnees = new ArrayList<IData>();
	}
	
	public Frame(short id) {
		this();
                typeFanion = EPennant.TrameNormale.getType();
		this.setId(id);
	}
	
        @Override
	public void ajouterDonnee(IData donnee) {
		this.donnees.add(donnee);
	}

        @Override
	public void ajouterDonnees(List<IData> donnees) {
		this.donnees.addAll(donnees);
	}
	
        @Override
	public List<IData> getDonnees() {
		return this.donnees;
	}

        @Override
	public short getId() {
		return id;
	}
	
        @Override
	public short getTypeFanion() {
		return typeFanion;
	}
	
	@Override
	public short getNbDonnees() {
		return (short) this.donnees.size();
	}
    
        //@todo conversion en entier non signe
        @Override
	public void setId(short id) {
		this.id = (short) (id & 0xff);
	}

        @Override
	public void setTypeFanion(short typeFanion) {
		this.typeFanion = (short) (typeFanion & 0xff);
	}
	
        @Override
	public String toString() {
            String s = " { ";
            EPennant eTypeFanion = EPennant.getTypeFanion(this.getTypeFanion());
            
            switch(eTypeFanion) {
                case TrameSpeciale:
                    s += eTypeFanion.toString();
                    break;
                    
                case TrameNormale:
                    s += "0x" + Integer.toHexString(getId()).toUpperCase();

                    for (int i = 0; i < getNbDonnees(); i++) {
                            s += ", ";
                            s += getDonnees().get(i).toString();
                    }
                    break;
            }
            
            s += " }\n";
            
            return s;
	}
}