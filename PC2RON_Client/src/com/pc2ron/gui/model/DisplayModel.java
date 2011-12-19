/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.pc2ron.gui.model;

import java.util.Observable;

/**
 *
 * @author Mehdi Drici
 */
public class DisplayModel extends Observable {
    private String text;
    private boolean initialized;
    
    public DisplayModel() {
        super();
        initialized = false;
    }
    
    public void setText(String text) {
        this.text = text;
        setChanged();
        notifyObservers();
    }
    
    public boolean isInitialized() {
        return initialized;
    }
    
    public String getText() {
        return text;
    }
}
