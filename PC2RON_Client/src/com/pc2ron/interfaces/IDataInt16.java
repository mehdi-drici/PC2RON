package com.pc2ron.interfaces;

/**
 * Interface representant un entier signe sur 16 octets
 * @author Mehdi Drici
 */
public interface IDataInt16 extends IData {
	public static byte NB_OCTETS = 2;
	public short getValue();
}
