package com.pc2ron.interfaces;

import java.util.ArrayList;

public interface IFrameFactory {
	public IFrame getTrame();
	public IFrame getTrame(short id);
	public IFrame getTrame(short id, IData donnee);
	public IFrame getTrame(short id, ArrayList<IData> donnees);
	public IFrame getTrameEnd();
}
