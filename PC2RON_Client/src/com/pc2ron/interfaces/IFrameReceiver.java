package com.pc2ron.interfaces;

import com.pc2ron.frame.IncorrectFrameException;
import java.io.DataInputStream;

/**
 * Interface representant le recepteur de trame
 * et disposant par consequant de methodes pour recevoir des donnees
 * @author mehdi
 */
public interface IFrameReceiver {
	// Point d'entree du recepteur
        public IFrame readFrame(DataInputStream in) throws IncorrectFrameException;
        
	public IData readData(DataInputStream in) throws IncorrectFrameException;
        
	public IDataInt8 readInt8(DataInputStream in);
	public IDataInt16 readInt16(DataInputStream in);
	public IDataInt32 readInt32(DataInputStream in);
	public IDataUint8 readUInt8(DataInputStream in);
	public IDataUint16 readUInt16(DataInputStream in);
	public IDataUInt32 readUInt32(DataInputStream in);
	public IDataString readString(DataInputStream in);
	public IDataDouble readDouble(DataInputStream in);
}
