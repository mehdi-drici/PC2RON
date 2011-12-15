package com.pc2ron.interfaces;

/**
 * Interface de la fabrique de trames et de donnees
 * @author Mehdi Drici
 */
public interface IDataFactory {
        // Donnee generique
	public IData createData(byte type);
	
        // Entiers signes
	public IDataInt8 createInt8(byte int8);
	public IDataInt16 createInt16(short int16);
	public IDataInt32 createInt32(int int32);
	
        // Entiers non signes
	public IDataUint8 createUint8(short uint8);
	public IDataUint16 createUint16(int uint16);
	public IDataUInt32 createUint32(long uint32);
	
        // Flottant
	public IDataDouble createDouble(double myDouble);
	
	// Chaine de caracteres en UTF-8
	public IDataString createString(String myString);
}
