package fr.pc2ron.interfaces;

import java.util.*;

public interface ITrame {	
	/* Decodage pour chaque type de donnees */
	//public ITrame decoder(Byte[] tabOctets);
	
    //@todo a enlever
	public static final short FANION = (short) 0xFF;
	public static final short FIN_TRANSMISSION = (short) 0x00;
	
	public void setId(short id);
	public void setTypeFanion(short typeFanion);
	
	public void ajouterDonnee(IDonnee donnee);
	public void ajouterDonnees(List<IDonnee> donnees);
	
	public short getTypeFanion();
	public short getId();
	public short getNbDonnees();
	public List<IDonnee> getDonnees();
	
	public String toString();
}
