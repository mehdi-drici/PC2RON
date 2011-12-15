package com.pc2ron.interfaces;

import java.util.*;

public interface IFrame {	
	/* Decodage pour chaque type de donnees */
	//public ITrame decoder(Byte[] tabOctets);
	
    //@todo a enlever
	public static final short FANION = (short) 0xFF;
	public static final short FIN_TRANSMISSION = (short) 0x00;
	
	public void setId(short id);
	public void setTypeFanion(short typeFanion);
	
	public void ajouterDonnee(IData donnee);
	public void ajouterDonnees(List<IData> donnees);
	
	public short getTypeFanion();
	public short getId();
	public short getNbDonnees();
	public List<IData> getDonnees();
	
	public String toString();
}
