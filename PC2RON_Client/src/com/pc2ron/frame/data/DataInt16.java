package com.pc2ron.frame.data;

import java.io.DataInput;
import java.io.IOException;
import java.util.ArrayList;

import com.pc2ron.interfaces.IDataInt16;
import com.pc2ron.interfaces.IVisitor;

/**
 * Representation d'un entier sur 16 bits conformement 
 * a la couche de transport definie par PC2RON
 * @author Mehdi Drici
 */
public class DataInt16 implements IDataInt16 {
    private short entier;

    public DataInt16() {
        entier = 0;
    }

    public DataInt16(short entier) {
        this.entier = entier;
    }

    @Override
    public short getValue() {
        return entier;
    }

    public String toString() {
        return EDataType.INT16.getTypeString() + " " + getValue();
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
