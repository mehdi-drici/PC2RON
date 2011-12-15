package com.pc2ron.frame;

import java.util.ArrayList;
import java.util.List;

import com.pc2ron.interfaces.IData;
import com.pc2ron.interfaces.IFrame;

/**
 * Representation d'une trame conformement a la specification 
 * de la couche transport de PC2RON
 * @author Mehdi Drici
 */
public class Frame implements IFrame {
	private ArrayList<IData> donnees = null;
        
	private short typeFanion;
	private short id;
	
	public Frame() {
            this.donnees = new ArrayList<IData>();
	}
	
	public Frame(short id) {
		this();
                typeFanion = EPennant.NormalFrame.getType();
		this.setId(id);
	}
	
        /**
         * Ajouter une donnee
         * @param data Donnee
         */
        @Override
	public void addData(IData data) {
            this.donnees.add(data);
	}
        
        /**
         * Ajouter une liste de donnees
         * @param dataArray Liste de donnees
         */
        @Override
	public void addData(List<IData> dataArray) {
            this.donnees.addAll(dataArray);
	}
	
        @Override
	public List<IData> getData() {
            return this.donnees;
	}

        @Override
	public short getId() {
		return id;
	}
	
        @Override
	public short getPennant() {
		return typeFanion;
	}
	
        /**
         * Recuperer le nombre de donnees de la trame
         * @return Nombre de donnees
         */
	@Override
	public short getDataSize() {
		return (short) this.donnees.size();
	}
    
        /**
         * Modifier l'id d'une trame
         * La conversion en entier non signe est effectue 
         * lors de cette modification
         * @param id Nouvel id de la trame courante
         */
	public void setId(short id) {
            this.id = (short) (id & 0xff);
	}
        
        /**
         * Modifier le fanion d'une trame
         * La conversion en entier non signe est effectue 
         * lors de cette modification
         * @param pennantType Nouveau fanion de la trame courante
         */
        @Override
	public void setPennant(short pennantType) {
            this.typeFanion = (short) (pennantType & 0xff);
	}
	
        @Override
	public String toString() {
            String s = " { ";
            EPennant eTypeFanion = EPennant.getPennant(this.getPennant());
            
            switch(eTypeFanion) {
                case SpecialFrame:
                    s += eTypeFanion.toString();
                    break;
                    
                case NormalFrame:
                    s += "0x" + Integer.toHexString(getId()).toUpperCase();

                    for (int i = 0; i < getDataSize(); i++) {
                            s += ", ";
                            s += getData().get(i).toString();
                    }
                    break;
            }
            
            s += " }\n";
            
            return s;
	}
}