package com.pc2ron.frame;

import java.util.ArrayList;

import com.pc2ron.interfaces.IData;
import com.pc2ron.interfaces.IFrame;
import com.pc2ron.interfaces.IFrameFactory;

/**
 * Fabrique de trames basiques (niveau couche de transport)
 * L'instance de cette fabrique etant unique
 * on utilise le pattern Singleton 
 * @author Mehdi Drici
 */
public class FrameFactory implements IFrameFactory {
    // Unique instance de la fabrique
    private static IFrameFactory instance;
    
    private FrameFactory() {	
    }
    
    /**
     * Recuperer l'instance du singleton
     * @return L'unique instance de la fabrique 
     */
    public static IFrameFactory getInstance() {
        if (null == instance) { // Premier appel
            instance = new FrameFactory();
        }
        return instance;
    }
    
    /**
     * Creer une trame minimale
     * @return Trame creee (sans identifiant, ni donnees)
     */
    @Override
    public IFrame createFrame() {
        return new Frame();
    }

    /**
     * Creer une trame avec son identifiant
     * @param id Identifiant de la trame a creer
     * @return Trame creee
     */
    @Override
    public IFrame createFrame(short id) {
        return new Frame(id);
    }
    
    /**
     * Creer une trame avec son identifiant et une donnee
     * @param id Identifiant de la trame a creer
     * @param data Donnee a ajouter
     * @return Trame creee
     */
    @Override
    public IFrame createFrame(short id, IData data) {
        IFrame trame = new Frame(id);
        trame.addData(data);

        return trame;
    }
    
    /**
     * Creer une trame avec son identifiant et une liste de donnees
     * @param id Identifiant de la trame a creer
     * @param data Liste de donnees a ajouter
     * @return Trame creee
     */
    @Override
    public IFrame createFrame(short id, ArrayList<IData> dataArray) {
        IFrame trame = new Frame(id);
        trame.addData(dataArray);

        return trame;
    }
    
    
    /**
     * Creer une trame de fin de transmission
     * @return Trame de fin de transmission
     */
    @Override
    public IFrame createEndFrame() {
        IFrame trameEnd = createFrame();
        trameEnd.setPennant(EPennant.SpecialFrame.getType());

        return trameEnd;
    }
}
