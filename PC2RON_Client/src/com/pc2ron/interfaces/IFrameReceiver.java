package com.pc2ron.interfaces;

import java.io.DataInputStream;

public interface IFrameReceiver {
	public IFrame recevoirTrame(DataInputStream in);
	public IData recevoirDonnee(DataInputStream in);
	public IInt8 recevoirEntierSigne1(DataInputStream in);
	public IInt16 recevoirEntierSigne2(DataInputStream in);
	public IInt32 recevoirEntierSigne4(DataInputStream in);
	public IUint8 recevoirEntierNonSigne1(DataInputStream in);
	public IUint16 recevoirEntierNonSigne2(DataInputStream in);
	public IUInt32 recevoirEntierNonSigne4(DataInputStream in);
	public IString recevoirChaine(DataInputStream in);
	public IDouble recevoirFlottant(DataInputStream in);
}
