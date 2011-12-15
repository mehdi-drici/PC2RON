package com.pc2ron.frame.data;

import com.pc2ron.interfaces.IDataUint16;
import com.pc2ron.interfaces.IVisitor;

/**
 * Representation d'un entier non signe sur 16 bits conformement 
 * a la couche de transport definie par PC2RON
 * @author Mehdi Drici
 */
public class DataUint16 implements IDataUint16 {
    private int entier;

    public DataUint16() {
        entier = 0;
    }

    public DataUint16(int entier) {
        this.entier = entier & 0xffff;	
    }

    @Override
    public int getValue() {
        return entier;
    }
    
    @Override
    public String toString() {
        return EDataType.ENTIER_NON_SIGNE2.getStringType() + " " + getValue();
    }
    
    /**
     * Traitement effectue par un visiteur et relatif a la donnee courante
     * @param <Data>
     * @param <Result>
     * @param visitor Visiteur s'occupant du traitement
     * @param data Donnee a traiter
     * @return 
     */
    @Override
    public <Data, Result> Result accept(IVisitor<Data, Result> visiteur, Data donnees) {
        return visiteur.visit(this, donnees);
    }
}
