package com.pc2ron.interfaces;

import com.pc2ron.frame.IncorrectFrameException;

/**
 * Visiteur du point de vue du Design Pattern Visitor
 * s'occupant des traitements relaifs a une trame et a ses donnees
 * Le visiteur est generique pour permettre l'ajout de futurs traitements
 * @author Mehdi Drici
 * @param <Data> Type de donnee additionnel
 * @param <Result> Type du resultat du traitement
 */
public interface IVisitor<Data, Result> {
    Result visit (IFrame frame, Data data) throws IncorrectFrameException;
    Result visit (IDataInt8 dataToSend, Data data);
    Result visit (IDataInt16 dataToSend, Data data);
    Result visit (IDataInt32 dataToSend, Data data);
    Result visit (IDataUint8 dataToSend, Data data);
    Result visit (IDataUint16 dataToSend, Data data);
    Result visit (IDataUInt32 dataToSend, Data data);
    Result visit (IDataString dataToSend, Data data);
    Result visit (IDataDouble dataToSend, Data data);
}
