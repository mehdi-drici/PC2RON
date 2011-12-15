/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.pc2ron.protocol;

/**
 * Exception representant une erreur de format d'une trame
 * @author Mehdi Drici
 */
public class FormatException extends Exception {
    String frameType;
    String errorMsg;
    
    FormatException(){
        this.frameType = "";
        this.errorMsg = "";
    }
    
    FormatException(String frameType, String errorMsg){
        this.frameType = frameType;
        this.errorMsg = errorMsg;
    }

    public String toString(){
       return new String(super.toString() + " : " + frameType + " >> " + errorMsg);   
    }
}
