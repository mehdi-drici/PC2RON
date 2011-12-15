package com.pc2ron.protocol;

/**
 * Les differents types de trame du point de vue du protocole
 * @author Mehdi Drici
 */
public enum EFrameType {
    Init(0x49),
    Connect(0x43),
    Ack(0x41),
    Registered(0x52),
    User(0x55),
    End(0x45),
    Pause(0x50),
    Start(0x53),
    Turn(0x54),
    Death(0x44),
    Win(0x57),
    Order(0x4F);

    private final short type;

    EFrameType(int type) {
        this.type = (short) type;
    }

    public short getType() {
        return this.type;
    }

    public static EFrameType getFrameType(short type) {
        short typeNonSigne = (short) (type & 0xff);

        EFrameType eTypes[] = EFrameType.values();
        EFrameType eType = null;

        for(EFrameType typeCourant : eTypes) {
            if(typeCourant.getType() == typeNonSigne) {
                eType = typeCourant;
            }
        }

        return eType;
    }
}