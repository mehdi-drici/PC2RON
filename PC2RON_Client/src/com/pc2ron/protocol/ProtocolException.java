/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.pc2ron.protocol;

/**
 * Exception representant une erreur suite a un acquittement negatif 
 * au niveau d'echange avec le serveur
 * @author Mehdi Drici
 */
public class ProtocolException extends Exception {
    String errorMsg;
    
    ProtocolException() {
        this.errorMsg = "Protocol Error";
    }
    
    ProtocolException(String errorMsg) {
        this.errorMsg = errorMsg;
    }

    public String toString(){
       return new String(super.toString() + " : " + errorMsg);   
    }
}
