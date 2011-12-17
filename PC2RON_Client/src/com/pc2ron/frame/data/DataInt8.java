package com.pc2ron.frame.data;

import com.pc2ron.interfaces.IDataInt8;
import com.pc2ron.interfaces.IVisitor;

/**
 * Representation d'un entier signe sur 8 bits conformement 
 * a la couche de transport definie par PC2RON
 * @author Mehdi Drici
 */
public class DataInt8 implements IDataInt8 {
    private byte entier;

    public DataInt8() {
        entier = 0;
    }

    public DataInt8(byte entier) {
        this.entier = entier;
    }

    @Override
    public byte getValue() {
        return entier;
    }
    
    @Override
    public String toString() {
        return EDataType.INT8.getTypeString() + " " + getValue();
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
