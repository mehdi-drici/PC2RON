package com.pc2ron.interfaces;

/**
 * Interface representant une chaine de caracteres
 * @author Mehdi Drici
 */
public interface IDataString extends IData {
    // Encodage de la chaine
    public static String CHARSET = "UTF-8";

    public String getContent();
}
