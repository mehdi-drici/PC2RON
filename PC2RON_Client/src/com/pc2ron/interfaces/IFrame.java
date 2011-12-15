package com.pc2ron.interfaces;

import java.util.*;

/**
 * Interface representant une trame
 * @author mehdi
 */
public interface IFrame {	
	public void setId(short id);
	public void setPennant(short typeFanion);
	
	public void addData(IData donnee);
	public void addData(List<IData> donnees);
	
	public short getPennant();
	public short getId();
	public short getDataSize();
	public List<IData> getData();
	
}