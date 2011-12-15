package com.pc2ron.protocol;

import java.util.ArrayList;

import com.pc2ron.interfaces.IData;
import com.pc2ron.interfaces.IDataFactory;
import com.pc2ron.interfaces.IFrame;
import com.pc2ron.interfaces.IFrameBuilder;
import com.pc2ron.interfaces.IFrameFactory;
import com.pc2ron.frame.FrameFactory;
import com.pc2ron.frame.data.DataFactory;

/**
 * Constructeur de trames specifique au protocole PC2RON
 * L'instance de ce constructeur etant unique
 * on utilise le pattern Singleton 
 * @author Mehdi Drici
 */
public class FrameBuilder implements IFrameBuilder {
    // Unique instance de la fabrique
    private static IFrameBuilder instance;
	
    private FrameBuilder() {
    }

    /**
    * Recuperer l'instance du singleton
    * @return L'unique instance du constructeur 
    */
    public static IFrameBuilder getInstance() {
        if (null == instance) { // Premier appel
            instance = new FrameBuilder();
        }

        return instance;
    }

    /**
     * Creation d'une trame Connect
     * @param rgbColor Couleur de la moto au format RGB
     * @param nom Nom du joueur
     * @return Trame Connect creee
     */
    @Override
    public IFrame createConnect(short[] rgbColor, String nom) {
        IDataFactory donneeFactory = DataFactory.getInstance();
        IFrameFactory trameFactory = FrameFactory.getInstance();

        ArrayList<IData> listeDonnees = new ArrayList<IData>();
        IData rouge = donneeFactory.createUint8(rgbColor[0]);
        IData vert = donneeFactory.createUint8(rgbColor[1]);
        IData bleu = donneeFactory.createUint8(rgbColor[2]);
        IData nomM = donneeFactory.createString(nom);

        listeDonnees.add(rouge);
        listeDonnees.add(vert);
        listeDonnees.add(bleu);
        listeDonnees.add(nomM);

        IFrame trame = trameFactory.createFrame(EFrameType.Connect.getType(), listeDonnees);

        return trame;
    }

    /**
     * Creation d'une trame Init
     * @return Trame Init creee
     */
    @Override
    public IFrame createInit() {
        IDataFactory donneeFactory = DataFactory.getInstance();
        IFrameFactory trameFactory = FrameFactory.getInstance();

        IData chaine1 = donneeFactory.createString("PC2RON?");
        IData chaine2 = donneeFactory.createString("PC2RON2011");

        ArrayList<IData> listeDonnees = new ArrayList<IData>();
        listeDonnees.add(chaine1);
        listeDonnees.add(chaine2);
        IFrame trame = trameFactory.createFrame(EFrameType.Init.getType(), listeDonnees);

        return trame;
    }

    /**
     * Creation d'une trame Order
     * @param order Ordre du joueur
     * @return Trame Order creee
     */
    @Override
    public IFrame createOrder(EOrder order) {
        IDataFactory donneeFactory = DataFactory.getInstance();
        IFrameFactory trameFactory = FrameFactory.getInstance();

        IData chaine = donneeFactory.createString(order.getStringOrder());

        IFrame trame = trameFactory.createFrame(EFrameType.Order.getType(), chaine);

        return trame;
    }
}
