package com.pc2ron.frame;

import java.util.ArrayList;

import com.pc2ron.interfaces.IData;
import com.pc2ron.interfaces.IFrame;
import com.pc2ron.interfaces.IFrameFactory;
import com.pc2ron.protocol.EFrameType;

public class FrameFactory implements IFrameFactory {
	private static IFrameFactory instance;
	
	private FrameFactory() {	
	}
	
	@Override
	public IFrame getTrame() {
		// TODO Auto-generated method stub
		return new Frame();
	}

	@Override
	public IFrame getTrame(short id) {
		// TODO Auto-generated method stub
		return new Frame(id);
	}

	@Override
	public IFrame getTrame(short id, IData donnee) {
		// TODO Auto-generated method stub
		IFrame trame = new Frame(id);
		trame.ajouterDonnee(donnee);
		
		return trame;
	}

	@Override
	public IFrame getTrame(short id, ArrayList<IData> donnees) {
		IFrame trame = new Frame(id);
		trame.ajouterDonnees(donnees);
		
		return trame;
	}
	
	public static IFrameFactory getInstance() {
		if (null == instance) { // Premier appel
			instance = new FrameFactory();
	    }
	    return instance;
	}

	@Override
	public IFrame getTrameEnd() {
            IFrame trameEnd = getTrame();
            trameEnd.setTypeFanion(EPennant.TrameSpeciale.getType());
            
            return trameEnd;
	}
}
