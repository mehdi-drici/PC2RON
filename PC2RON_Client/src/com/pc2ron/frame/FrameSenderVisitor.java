package com.pc2ron.frame;

import java.io.DataOutputStream;
import java.io.IOException;
import java.util.ArrayList;

import com.pc2ron.interfaces.*;
import com.pc2ron.frame.data.EDataType;

/**
 * Envoi d'une trame et de ses donnees (niveau transport)
 * L'instance de ce sender de trame etant unique
 * on utilise le pattern Singleton 
 * @author mehdi
 */
public class FrameSenderVisitor implements IVisitor<DataOutputStream, IVisitable>{
    // Unique instance de l'emetteur
    private static IVisitor instance;
	
    private FrameSenderVisitor() {
    }

    /**
    * Recuperer l'instance du singleton
    * @return L'unique instance du constructeur 
    */
    public static IVisitor getInstance() {
        if (null == instance) { // Premier appel
            instance = new FrameSenderVisitor();
        }

        return instance;
    }
    
    /**
     * Envoi d'une trame
     * Il s'agit du point d'entree de cette classe
     * @param frame Trame a envoyer
     * @param out Flux d'envoi des donnees au serveur
     * @return null
     * @throws IncorrectFrameException 
     */
    @Override
    public IVisitable visit(IFrame frame, DataOutputStream out) 
                                                throws IncorrectFrameException {
        try {
            out.writeByte(frame.getPennant());

            EPennant typeFanion = EPennant.getPennant(
                                                 frame.getPennant());
            switch(typeFanion) {
                case NormalFrame:
                    // Envoi de l'identifiant
                    out.writeByte(frame.getId());
                    
                    // Envoi du nombre de donnees
                    out.writeByte(frame.getDataSize());
                    
                    // Envoi des donnees
                    for (int i=0; i < frame.getDataSize(); i++) {
                        frame.getData().get(i).accept(this, out);
                    }
                    break;

                case SpecialFrame:
                    break;

                default:
                    throw new IncorrectFrameException("Unknown pennant");
            }
        } catch (IOException e) {
                e.printStackTrace();
        }

        return null;
    }
    
    /**
     * Envoi d'une donnee d'une entier signe sur 8 octets
     * @param data Donnee a envoyer
     * @param out Flux d'envoi des donnees au serveur
     * @return
     */
    @Override
    public IVisitable visit(IDataInt8 data, DataOutputStream out) {
        try {
            // Envoi du type de donnee
            out.writeByte(EDataType.INT8.getType());
            
            // Envoi de la donnee
            out.writeByte(data.getValue());

        } catch (IOException e) {
                e.printStackTrace();
        }
        return null;
    }
    
    /**
     * Envoi d'une donnee d'une entier signe sur 16 octets
     * @param data Donnee a envoyer
     * @param out Flux d'envoi des donnees au serveur
     * @return
     */
    @Override
    public IVisitable visit(IDataInt16 data, DataOutputStream out) {
        try {
            // Envoi du type de donnee
            out.writeByte(EDataType.INT16.getType());
            
            // Envoi de la donnee
            out.writeShort(data.getValue());
        } catch (IOException e) {
                e.printStackTrace();
        }
        return null;
    }
    
    /**
     * Envoi d'une donnee d'une entier signe sur 32 octets
     * @param data Donnee a envoyer
     * @param out Flux d'envoi des donnees au serveur
     * @return
     */
    @Override
    public IVisitable visit(IDataInt32 data, DataOutputStream out) {
        try {
            // Envoi du type de donnee
            out.writeByte(EDataType.INT32.getType());
            
            // Envoi de la donnee
            out.writeInt(data.getValue());
        } catch (IOException e) {
                e.printStackTrace();
        }
        return null;
    }
    
    /**
     * Envoi d'une donnee d'une entier non signe sur 8 octets
     * @param data Donnee a envoyer
     * @param out Flux d'envoi des donnees au serveur
     * @return
     */
    @Override
    public IVisitable visit(IDataUint8 data, DataOutputStream out) {
        try {
            // Envoi du type de donnee
            out.write(EDataType.UINT8.getType());

            // Conversion de l'entier en entier non signe
            short entierNonSigne = data.getValue();

            out.writeByte((byte)entierNonSigne);
        } catch (IOException e) {
                e.printStackTrace();
        }
        return null;
    }
    
    /**
     * Envoi d'une donnee d'une entier non signe sur 16 octets
     * @param data Donnee a envoyer
     * @param out Flux d'envoi des donnees au serveur
     * @return
     */
    @Override
    public IVisitable visit(IDataUint16 data, DataOutputStream out) {
        try {
            // Envoi du type de donnee
            out.write(EDataType.UINT16.getType());
            
            // Codage du nombre en octets
            int entierNonSigne = data.getValue();
            ArrayList<Byte> listeOctets = new ArrayList<Byte>();
            
            listeOctets.add((byte) (entierNonSigne >>> 8));
            listeOctets.add((byte) (entierNonSigne));

            // Envoi de la donnee
            for(int i=0; i < listeOctets.size(); i++){	
                out.writeByte(listeOctets.get(i));
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
        return null;
    }
    
    /**
     * Envoi d'une donnee d'une entier non signe sur 32 octets
     * @param data Donnee a envoyer
     * @param out Flux d'envoi des donnees au serveur
     * @return
     */
    @Override
    public IVisitable visit(IDataUInt32 data, DataOutputStream out) {
        try {
            // Envoi du type de donnee
            out.write(EDataType.UINT32.getType());

            // Codage du nombre en octets
            long entierNonSigne = data.getValue();
            ArrayList<Byte> listeOctets = new ArrayList<Byte>();
            
            listeOctets.add((byte)(entierNonSigne >>> 24));
            listeOctets.add((byte)(entierNonSigne >>> 16));
            listeOctets.add((byte)(entierNonSigne >>>  8));
            listeOctets.add((byte)(entierNonSigne));
            
            // Envoi de la donnee
            for(int i=0; i < listeOctets.size(); i++){	
                out.writeByte(listeOctets.get(i));
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return null;
    }
    
    /**
     * Envoi d'une donnee d'une chaine de caracteres
     * @param data Donnee a envoyer
     * @param out Flux d'envoi des donnees au serveur
     * @return
     */
    @Override
    public IVisitable visit(IDataString data, DataOutputStream out) {
        try {
            //short taille = (short) donnee.getContent().getBytes("UTF-8").length;
            
            // Envoi du type de donnee
            out.write(EDataType.STRING.getType());
            
            // Envoi de la taille de la chaine
            out.writeShort(data.getContent().getBytes("UTF-8").length);
            
            // Envoi de la chaine
            out.write(data.getContent().getBytes());
        } catch (IOException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
        }
        return null;
    }
    
    /**
     * Envoi d'une donnee d'un flottant en double precision
     * @param data Donnee a envoyer
     * @param out Flux d'envoi des donnees au serveur
     * @return
     */
    @Override
    public IVisitable visit(IDataDouble data, DataOutputStream out) {
        try {
            // Envoi du type de donnee
            out.write(EDataType.DOUBLE.getType());
            
            // Envoi de la donnee
            out.writeDouble(data.getDouble());
        } catch (IOException e) {
            e.printStackTrace();
        }
        return null;
    }
}
