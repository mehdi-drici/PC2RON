package fr.pc2ron.interfaces;

import java.io.DataInputStream;

public interface IReceptionTrame {
	public ITrame recevoirTrame(DataInputStream in);
	public IDonnee recevoirDonnee(DataInputStream in);
	public IEntierSigne1 recevoirEntierSigne1(DataInputStream in);
	public IEntierSigne2 recevoirEntierSigne2(DataInputStream in);
	public IEntierSigne4 recevoirEntierSigne4(DataInputStream in);
	public IEntierNonSigne1 recevoirEntierNonSigne1(DataInputStream in);
	public IEntierNonSigne2 recevoirEntierNonSigne2(DataInputStream in);
	public IEntierNonSigne4 recevoirEntierNonSigne4(DataInputStream in);
	public IChaine recevoirChaine(DataInputStream in);
	public IFlottant recevoirFlottant(DataInputStream in);
}
