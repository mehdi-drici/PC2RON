/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.pc2ron.frame;

/**
 *
 * @author mehdi
 */
public class IncorrectFrameException extends Exception {
    String errorMsg;

    IncorrectFrameException(String errorMsg){
        this.errorMsg = errorMsg;
    }
    
    @Override
    public String toString(){
       return new String(super.toString() + " : " + errorMsg);   
    }
}
