package com.pc2ron.frame;

import java.io.DataInputStream;
import java.io.IOException;

import com.pc2ron.interfaces.*;
import com.pc2ron.frame.data.DataFactory;
import com.pc2ron.frame.data.EDataType;

/**
 * Reception d'une trame et de ses donnees (niveau transport)
 * L'instance de ce recepteur de trame etant unique
 * on utilise le pattern Singleton 
 * @author Mehdi Drici
 */
public class FrameReceiver implements IFrameReceiver {
    // Unique instance du recepteur
    private static IFrameReceiver instance;
	
    private FrameReceiver() {
    }

    /**
    * Recuperer l'instance du singleton
    * @return L'unique instance du constructeur 
    */
    public static IFrameReceiver getInstance() {
        if (null == instance) { // Premier appel
            instance = new FrameReceiver();
        }

        return instance;
    }
    
    /**
     * Reception d'une trame
     * @param in Flux de reception des donnees provenant du serveur
     * @return La trame recue
     * @throws IncorrectFrameException Exception envoyee lorsque la trame 
     *         recue est incorrecte
     */
    @Override
    public IFrame readFrame(DataInputStream in) throws IncorrectFrameException {
        IFrameFactory trameFactory = FrameFactory.getInstance();
        IFrame trameRecue = trameFactory.createFrame();

        try {
            // Reception du fanion
            byte typeFanion = in.readByte();
            trameRecue.setPennant(typeFanion);
            EPennant eTypeFanion = EPennant.getPennant(typeFanion);
            
            // Traitement adapte au fanion recu
            switch(eTypeFanion) {
                case NormalFrame:
                    // Reception de l'identifiant de la trame
                    byte id = in.readByte();
                    trameRecue.setId(id);
                    
                    // Reception du nombre de donnees
                    byte nbDonnees = in.readByte();

                    // Reception des donnees
                    IData donneeRecue;
                    for(int i=0; i < nbDonnees; i++) {  
                        donneeRecue = readData(in);             
                        trameRecue.addData(donneeRecue);   
                    }
                    break;

                case SpecialFrame:
                    return trameRecue;
                
                // Fanion inconnu
                default:
                    throw new IncorrectFrameException("Unknown pennant");
            }

        } catch (IOException e) {
                e.printStackTrace();
        }

        return trameRecue;
    }
    
    /***
     * Reception d'une donnee quelconque
     * @param in Flux de reception des donnees provenant du serveur
     * @return La donnee recue
     */
    @Override
    public IData readData(DataInputStream in) throws IncorrectFrameException {
        byte type;
        IData donnee = null;

        try {
            // Reception du type de donnee
            type = in.readByte();
            EDataType t = EDataType.getDataType(type);

            // Reception adaptee au type de donnee recu
            switch (t) {
                case INT8:
                    donnee = readInt8(in);
                    break;

                case INT16:
                    donnee = readInt16(in);
                    break;

                case INT32:
                    donnee = readInt32(in);
                    break;

                case UINT8:
                    donnee = readUInt8(in);
                    break;

                case UINT16:
                    donnee = readUInt16(in);
                    break;

                case UINT32:
                    donnee = readUInt32(in);
                    break;

                case STRING:
                    donnee = readString(in);
                    break;

                case DOUBLE:
                    donnee = readDouble(in);
                    break;

                // Type de donnee inconnu
                default:
                    throw new IncorrectFrameException("Data type unknown");
            }

        } catch (IOException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
        }

        return donnee;
    }
    
    /***
     * Reception d'une donnee contenant une chaine de caracteres
     * @param in Flux de reception des donnees provenant du serveur
     * @return La donnee de la chaine de caracteres recue
     */
    @Override
    public IDataString readString(DataInputStream in) {
            IDataFactory donneeFactory = DataFactory.getInstance();

            IDataString chaine = null;
            IDataUint16 nbOctets;
            byte[] buffer ;

            try {
                // Reception de la taille de la chaine de caracteres
                int temp = in.readUnsignedShort();
                nbOctets = donneeFactory.createUint16(temp);

                // Reception de la chaine
                buffer = new byte[nbOctets.getValue()];
                in.read(buffer, 0, nbOctets.getValue());
                chaine = donneeFactory.createString(new String(buffer, IDataString.CHARSET));

            } catch (IOException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }

            return chaine;
    }

    
    /***
     * Reception d'une donnee contenant un entier non signe sur 8 octets
     * @param in Flux de reception des donnees provenant du serveur
     * @return La donnee recue
     */
    @Override
    public IDataUint8 readUInt8(DataInputStream in) {
        IDataFactory donneeFactory = DataFactory.getInstance();
        IDataUint8 entier = null;
        try {
                entier = donneeFactory.createUint8((short) in.readUnsignedByte());
        } catch (IOException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
        }
        return entier;
    }
    
    
    /***
     * Reception d'une donnee contenant un entier non signe sur 16 octets
     * @param in Flux de reception des donnees provenant du serveur
     * @return La donnee recue
     */
    @Override
    public IDataUint16 readUInt16(DataInputStream in) {
        IDataFactory donneeFactory = DataFactory.getInstance();
        IDataUint16 entier = null;
        try {
                entier = donneeFactory.createUint16(in.readUnsignedShort());
        } catch (IOException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
        }
        return entier;
    }
    
    /***
     * Reception d'une donnee contenant un entier non signe sur 32 octets
     * @param in Flux de reception des donnees provenant du serveur
     * @return La donnee recue
     */
    @Override
    public IDataUInt32 readUInt32(DataInputStream in) {
        IDataFactory donneeFactory = DataFactory.getInstance();
        IDataUInt32 entier = null;
        try {
                long entierSigne = in.readInt();

                // Conversion de l'entier recu en entier non signe
                long entierNonSigne = entierSigne & 0xffffffffL;
                entier = donneeFactory.createUint32(entierNonSigne);
        } catch (IOException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
        }
        return entier;
    }
    
    /***
     * Reception d'une donnee contenant un entier signe sur 8 octets
     * @param in Flux de reception des donnees provenant du serveur
     * @return La donnee recue
     */
    @Override
    public IDataInt8 readInt8(DataInputStream in) {
        IDataFactory donneeFactory = DataFactory.getInstance();
        IDataInt8 entier = null;
        try {
                entier = donneeFactory.createInt8(in.readByte());
        } catch (IOException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
        }
        return entier;
    }
    
    /***
     * Reception d'une donnee contenant un entier signe sur 16 octets
     * @param in Flux de reception des donnees provenant du serveur
     * @return La donnee recue
     */
    @Override
    public IDataInt16 readInt16(DataInputStream in) {
        IDataFactory donneeFactory = DataFactory.getInstance();
        IDataInt16 entier = null;
        try {
                entier = donneeFactory.createInt16(in.readShort());
        } catch (IOException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
        }
        return entier;
    }
    
    /***
     * Reception d'une donnee contenant un entier signe sur 32 octets
     * @param in Flux de reception des donnees provenant du serveur
     * @return La donnee recue
     */
    @Override
    public IDataInt32 readInt32(DataInputStream in) {
        IDataFactory donneeFactory = DataFactory.getInstance();
        IDataInt32 entier = null;
        try {
                entier = donneeFactory.createInt32(in.readInt());
        } catch (IOException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
        }
        return entier;
    }
    
    /***
     * Reception d'une donnee contenant un flottant en double precision
     * @param in Flux de reception des donnees provenant du serveur
     * @return La donnee recue
     */
    @Override
    public IDataDouble readDouble(DataInputStream in) {
        IDataFactory donneeFactory = DataFactory.getInstance();
        IDataDouble flottant = null;
        try {
                flottant = donneeFactory.createDouble(in.readDouble());
        } catch (IOException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
        }
        return flottant;
    }
}
