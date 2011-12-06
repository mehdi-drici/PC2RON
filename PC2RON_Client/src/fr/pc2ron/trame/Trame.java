package fr.pc2ron.trame;

import java.util.ArrayList;
import java.util.List;

import fr.pc2ron.interfaces.IDonnee;
import fr.pc2ron.interfaces.ITrame;

public class Trame implements ITrame {
	private ArrayList<IDonnee> donnees = null;
	private short typeFanion;
	private short id;
	
	public Trame() {
	}
	
	public Trame(short id) {
		this.donnees = new ArrayList<IDonnee>();
		setTypeFanion(ETypeFanion.TrameNormale.getType());
		setId(id);
	}
	
	public void ajouterDonnee(IDonnee donnee) {
		this.donnees.add(donnee);
	}

	public void ajouterDonnees(List<IDonnee> donnees) {
		this.donnees.addAll(donnees);
	}
	
	/*
	@Override
	public ArrayList<Byte> toBytes() {
		
		ArrayList<Byte> tab = new ArrayList<Byte>();
		
		// Cast du nombre de donnees en byte
		Byte nbDonnees = new Byte((byte) getDonnees().size());
		
		tab.add(type);
		tab.add(id);
		tab.add(nbDonnees);
		
		for (int i = 0; i < nbDonnees; i++) {
				tab.addAll(getDonnees().get(i).toBytes());
				//tab[(i+1) * j] = getDonnees().get(i).toBytes()[j]; 
		}
		
		return tab;
	}
	*/
	
    @Override
	public List<IDonnee> getDonnees() {
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
	
	/*
	@Override
	public int taille() {
		int taille = 0;
		
		// Taille de l'entête de la trame
		// Elle dépend du type de la trame (trame spéciale ou non)
		taille += this.typeFanion == ETypeFanion.TrameNormale.getType() ? 3 : 1;
		
		// Taille des données
		for (int i=0; i < getNbDonnees(); i++) {
			taille += getDonnees().get(i).taille();
		}
		
		return taille;
	}
	*/
	
    @Override
	public String toString() {
		String s = "{ ";
		s += "0x" + Integer.toHexString(getId()).toUpperCase();
		
		for (int i = 0; i < getNbDonnees(); i++) {
			s += ", ";
			s += getDonnees().get(i).toString();
		}
		
		s += " }";
		
		return s;
	}
}
