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
        this.donnees = new ArrayList<IDonnee>();
	}
	
	public Trame(short id) {
		this();
		setTypeFanion(ETypeFanion.TrameNormale.getType());
		setId(id);
	}
	
	public void ajouterDonnee(IDonnee donnee) {
		this.donnees.add(donnee);
	}

	public void ajouterDonnees(List<IDonnee> donnees) {
		this.donnees.addAll(donnees);
	}
	
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
	
    @Override
	public String toString() {
		String s = ">>> { ";
		s += "0x" + Integer.toHexString(getId()).toUpperCase();
		
		for (int i = 0; i < getNbDonnees(); i++) {
			s += ", ";
			s += getDonnees().get(i).toString();
		}
		
		s += " }\n";
		
		return s;
	}
}
