package com.pc2ron.protocol;

import java.util.ArrayList;

import com.pc2ron.interfaces.IData;
import com.pc2ron.interfaces.IDataFactory;
import com.pc2ron.interfaces.IFrame;
import com.pc2ron.interfaces.IFrameBuilder;
import com.pc2ron.interfaces.IFrameFactory;
import com.pc2ron.frame.FrameFactory;
import com.pc2ron.frame.data.DonneeFactory;

public class FrameBuilder implements IFrameBuilder {
	private static IFrameBuilder instance;
	
	private FrameBuilder() {
	}
	
	@Override
	public IFrame creerTrameConnect(short r, short v, short b, String nom) {
		IDataFactory donneeFactory = DonneeFactory.getInstance();
		IFrameFactory trameFactory = FrameFactory.getInstance();
		
		ArrayList<IData> listeDonnees = new ArrayList<IData>();
		IData rouge = donneeFactory.getEntierNonSigne1(r);
		IData vert = donneeFactory.getEntierNonSigne1(v);
		IData bleu = donneeFactory.getEntierNonSigne1(b);
		IData nomM = donneeFactory.getChaine(nom);
		
		listeDonnees.add(rouge);
		listeDonnees.add(vert);
		listeDonnees.add(bleu);
		listeDonnees.add(nomM);
		
		IFrame trame = trameFactory.getTrame(EFrameType.TrameConnect.getType(), listeDonnees);
		
		return trame;
	}

	@Override
	public IFrame creerTrameInit() {
		IDataFactory donneeFactory = DonneeFactory.getInstance();
		IFrameFactory trameFactory = FrameFactory.getInstance();
		
		IData chaine1 = donneeFactory.getChaine("PC2RON?");
		IData chaine2 = donneeFactory.getChaine("PC2RON2011");
		
		ArrayList<IData> listeDonnees = new ArrayList<IData>();
		listeDonnees.add(chaine1);
		listeDonnees.add(chaine2);
		IFrame trame = trameFactory.getTrame(EFrameType.TrameInit.getType(), listeDonnees);
		
		return trame;
	}

	@Override
	public IFrame creerTrameOrder(EOrder ordre) {
		IDataFactory donneeFactory = DonneeFactory.getInstance();
		IFrameFactory trameFactory = FrameFactory.getInstance();
		
		IData chaine = donneeFactory.getChaine(ordre.getStringOrdre());
		
		IFrame trame = trameFactory.getTrame(EFrameType.TrameOrder.getType(), chaine);
		
		return trame;
	}

	public static IFrameBuilder getInstance() {
		if (null == instance) { // Premier appel
			instance = new FrameBuilder();
	    }
	    return instance;
	}
}
