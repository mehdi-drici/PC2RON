package fr.pc2ron.trame;

import java.util.ArrayList;

import fr.pc2ron.interfaces.IDonnee;
import fr.pc2ron.interfaces.ITrame;
import fr.pc2ron.interfaces.ITrameFactory;
import fr.pc2ron.protocole.ETypeTrame;

public class TrameFactory implements ITrameFactory {
	private static ITrameFactory instance;
	
	private TrameFactory() {	
	}
	
	@Override
	public ITrame getTrame() {
		// TODO Auto-generated method stub
		return new Trame();
	}

	@Override
	public ITrame getTrame(short id) {
		// TODO Auto-generated method stub
		return new Trame(id);
	}

	@Override
	public ITrame getTrame(short id, IDonnee donnee) {
		// TODO Auto-generated method stub
		ITrame trame = new Trame(id);
		trame.ajouterDonnee(donnee);
		
		return trame;
	}

	@Override
	public ITrame getTrame(short id, ArrayList<IDonnee> donnees) {
		ITrame trame = new Trame(id);
		trame.ajouterDonnees(donnees);
		
		return trame;
	}
	
	public static ITrameFactory getInstance() {
		if (null == instance) { // Premier appel
			instance = new TrameFactory();
	    }
	    return instance;
	}

	@Override
	public ITrame getTrameEnd() {
		return getTrame(ETypeTrame.TrameFin.getType());
	}
}
