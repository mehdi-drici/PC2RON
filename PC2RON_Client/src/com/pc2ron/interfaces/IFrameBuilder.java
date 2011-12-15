package com.pc2ron.interfaces;

import com.pc2ron.protocol.EOrder;

public interface IFrameBuilder {
	public IFrame creerTrameInit();
	public IFrame creerTrameConnect(short r, short v, short b, String nom);
	public IFrame creerTrameOrder(EOrder ordre);
}
