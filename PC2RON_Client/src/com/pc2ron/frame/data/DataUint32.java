package com.pc2ron.frame.data;

import java.io.DataInput;
import java.io.IOException;
import java.util.ArrayList;

import com.pc2ron.interfaces.IDataUInt32;
import com.pc2ron.interfaces.IVisitor;

/**
 * Representation d'un entier non signe sur 32 bits conformement 
 * a la couche de transport definie par PC2RON
 * @author Mehdi Drici
 */
public class DataUint32 implements IDataUInt32 {
    public long entier;

    public DataUint32() {
        entier = 0;
    }

    public DataUint32(long entier) {
        this.entier = entier & 0xffffffffL;
    }

    @Override
    public long getValue() {
        return entier;
    }
    
    @Override
    public String toString() {
        return EDataType.UINT32.getTypeString() + " " + getValue();
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
