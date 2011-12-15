package com.pc2ron.frame;

import java.io.DataOutputStream;
import java.io.IOException;
import java.util.ArrayList;

import com.pc2ron.interfaces.IString;
import com.pc2ron.interfaces.IUint8;
import com.pc2ron.interfaces.IUint16;
import com.pc2ron.interfaces.IUInt32;
import com.pc2ron.interfaces.IInt8;
import com.pc2ron.interfaces.IInt16;
import com.pc2ron.interfaces.IInt32;
import com.pc2ron.interfaces.IDouble;
import com.pc2ron.interfaces.IFrame;
import com.pc2ron.interfaces.IVisitable;
import com.pc2ron.interfaces.IVisitor;
import com.pc2ron.frame.data.ETypeDonnee;

public class FrameSenderVisitor implements IVisitor<DataOutputStream, IVisitable>{
   
    @Override
    public IVisitable visit(IFrame trame, DataOutputStream out) {
            try {
                out.writeByte(trame.getTypeFanion());

                EPennant typeFanion = EPennant.getTypeFanion(
                                                     trame.getTypeFanion());
                switch(typeFanion) {
                    case TrameNormale:
                        out.writeByte(trame.getId());
                        out.writeByte(trame.getNbDonnees());

                        for (int i=0; i < trame.getNbDonnees(); i++) {
                            trame.getDonnees().get(i).accept(this, out);
                        }
                        break;

                    case TrameSpeciale:
                        break;

                    default:
                        //@todo envoyer une exception
                        System.out.println("Fanion de la trame envoyee incorrect");
                }
            } catch (IOException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
            }

            // TODO Auto-generated method stub
            return null;
    }

    @Override
    public IVisitable visit(IInt8 donnee, DataOutputStream out) {
            try {
                    out.writeByte(ETypeDonnee.ENTIER_SIGNE1.getType());
                    out.writeByte(donnee.getEntier());

            } catch (IOException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
            }
            return null;
    }

    @Override
    public IVisitable visit(IInt16 donnee, DataOutputStream out) {
            try {
                    out.writeByte(ETypeDonnee.ENTIER_SIGNE2.getType());
                    out.writeShort(donnee.getEntier());
            } catch (IOException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
            }
            return null;
    }

    @Override
    public IVisitable visit(IInt32 donnee, DataOutputStream out) {
            try {
                    out.writeByte(ETypeDonnee.ENTIER_SIGNE4.getType());
                    out.writeInt(donnee.getEntier());
            } catch (IOException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
            }
            return null;
    }

    @Override
    public IVisitable visit(IUint8 donnee, DataOutputStream out) {
            try {
                    out.write(ETypeDonnee.ENTIER_NON_SIGNE1.getType());
                    //out.writeShort(donnee.getEntier());

                    // Conversion en entier non signe
                    short entierNonSigne = donnee.getEntier();

                    out.writeByte((byte)entierNonSigne);
            } catch (IOException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
            }
            return null;
    }

    @Override
    public IVisitable visit(IUint16 donnee, DataOutputStream out) {
            try {
                    out.write(ETypeDonnee.ENTIER_NON_SIGNE2.getType());
                    //out.writeInt(donnee.getEntier());

                    int entierNonSigne = donnee.getEntier();

                    //@todo tester
                    //out.writeShort((short) entierNonSigne);

                    ArrayList<Byte> listeOctets = new ArrayList<Byte>();

                    // Valeur
                    listeOctets.add((byte) (entierNonSigne >>> 8));
                    listeOctets.add((byte) (entierNonSigne));

                    for(int i=0; i < listeOctets.size(); i++){	
                            out.writeByte(listeOctets.get(i));
            }

            } catch (IOException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
            }
            return null;
    }

    @Override
    public IVisitable visit(IUInt32 donnee, DataOutputStream out) {
            try {
                    out.write(ETypeDonnee.ENTIER_NON_SIGNE4.getType());
                    //out.writeLong(donnee.getEntier());

                    long entierNonSigne = donnee.getEntier();
                    ArrayList<Byte> listeOctets = new ArrayList<Byte>();

                    //@todo tester
                    //out.writeInt((int) entierNonSigne);

                    // Valeur		
                    listeOctets.add((byte)(entierNonSigne >>> 24));
                    listeOctets.add((byte)(entierNonSigne >>> 16));
                    listeOctets.add((byte)(entierNonSigne >>>  8));
                    listeOctets.add((byte)(entierNonSigne));

                    for(int i=0; i < listeOctets.size(); i++){	
                            out.writeByte(listeOctets.get(i));
            }

            } catch (IOException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
            }
            return null;
    }

    @Override
    public IVisitable visit(IString donnee, DataOutputStream out) {
            try {
                    short taille = (short) donnee.getChaine().getBytes("UTF-8").length;

                    out.write(ETypeDonnee.CHAINE.getType());
                    //out.writeShort(donnee.getChaine().getBytes("UTF-8").length);
                    out.writeShort(taille);
                    out.write(donnee.getChaine().getBytes());
                    //out.writeUTF(donnee.getChaine());
            } catch (IOException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
            }
            return null;
    }

    @Override
    public IVisitable visit(IDouble donnee, DataOutputStream out) {
            try {
                    out.write(ETypeDonnee.FLOTTANT.getType());
                    out.writeDouble(donnee.getFlottant());
            } catch (IOException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
            }
            return null;
    }
}
