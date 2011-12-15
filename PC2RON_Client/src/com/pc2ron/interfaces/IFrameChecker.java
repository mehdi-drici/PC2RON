/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.pc2ron.interfaces;

import com.pc2ron.protocol.FormatException;

/**
 * Interface representant le verificateur de trame au niveau 
 * de la couche application (protocole)
 * Ce checker s'assure de la validite du format des trames
 * @author Mehdi Drici
 */
public interface IFrameChecker {
    public void check(IFrame frame) throws FormatException;
    public void checkAck(IFrame frame) throws FormatException;
    public void checkRegistered(IFrame frame) throws FormatException;
    public void checkStart(IFrame frame) throws FormatException;
    public void checkPause(IFrame frame) throws FormatException;
    public void checkDeath(IFrame frame) throws FormatException;
    public void checkWin(IFrame frame) throws FormatException;
    public void checkTurn(IFrame frame) throws FormatException;
    public void checkUser(IFrame frame) throws FormatException;
    public void checkEnd(IFrame frame) throws FormatException;
}
