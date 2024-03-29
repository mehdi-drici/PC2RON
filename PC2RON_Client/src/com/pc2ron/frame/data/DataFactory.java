package com.pc2ron.frame.data;

import com.pc2ron.interfaces.IDataString;
import com.pc2ron.interfaces.IData;
import com.pc2ron.interfaces.IDataFactory;
import com.pc2ron.interfaces.IDataUint8;
import com.pc2ron.interfaces.IDataUint16;
import com.pc2ron.interfaces.IDataUInt32;
import com.pc2ron.interfaces.IDataInt8;
import com.pc2ron.interfaces.IDataInt16;
import com.pc2ron.interfaces.IDataInt32;
import com.pc2ron.interfaces.IDataDouble;

public class DataFactory implements IDataFactory {
	private static IDataFactory instance;
	
	private DataFactory() {	
	}
	
	@Override
	public IData createData(byte type) {
		IData donnee = null;
		EDataType eType = EDataType.getDataType(type);
                
                switch(eType) {
                    case INT8:
                        donnee = new DataInt8();
                        break;
                    
                    case INT16:
                        donnee = new DataInt16();
                        break;
                        
                    case INT32:
                        donnee = new DataInt32();
                        break;
                    
                    case UINT8:
                        donnee = new DataUint8();
                        break;
                        
                    case UINT16:
                        donnee = new DataUint16();
                        break;
                        
                    case UINT32:
                        donnee = new DataUint32();
                        break;
                        
                    case STRING:
                        donnee = new DataString();
                        break;
                        
                    case DOUBLE:
                        donnee = new DataDouble();
                        break;
                }
		
		return donnee;
	}

	@Override
	public IDataUint8 createUint8(short entier) {
		return new DataUint8(entier);
	}

	@Override
	public IDataUint16 createUint16(int entier) {
		return new DataUint16(entier);
	}

	@Override
	public IDataUInt32 createUint32(long entier) {
		return new DataUint32(entier);
	}

	@Override
	public IDataInt8 createInt8(byte entier) {
		return new DataInt8(entier);
	}

	@Override
	public IDataInt16 createInt16(short entier) {
		return new DataInt16(entier);
	}

	@Override
	public IDataInt32 createInt32(int entier) {
		return new DataInt32(entier);
	}

	@Override
	public IDataDouble createDouble(double flottant) {
		return new DataDouble(flottant);
	}
	
	@Override
	public IDataString createString(String chaine) {
		return new DataString(chaine);
	}
	
	public static IDataFactory getInstance() {
		if (null == instance) { // Premier appel
			instance = new DataFactory();
	    }
	    return instance;
	}
}
