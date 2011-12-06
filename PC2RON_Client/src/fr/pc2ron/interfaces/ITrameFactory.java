package fr.pc2ron.interfaces;

import java.util.ArrayList;

public interface ITrameFactory {
	public ITrame getTrame();
	public ITrame getTrame(short id);
	public ITrame getTrame(short id, IDonnee donnee);
	public ITrame getTrame(short id, ArrayList<IDonnee> donnees);
	public ITrame getTrameEnd();
}
