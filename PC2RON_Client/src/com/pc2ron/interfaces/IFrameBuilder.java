package com.pc2ron.interfaces;

import com.pc2ron.protocol.EOrder;

/**
 * Interface representant le constructeur de trames specifiques 
 * au protocole PC2RON 
 * @author Mehdi Drici
 */
public interface IFrameBuilder {
    public IFrame createInit();
    public IFrame createConnect(short[] rgbColor, String name);
    public IFrame createOrder(EOrder order);
}
