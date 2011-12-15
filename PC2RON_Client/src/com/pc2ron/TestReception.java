package com.pc2ron;

import com.pc2ron.interfaces.IString;
import com.pc2ron.interfaces.IData;
import com.pc2ron.interfaces.IProtocol;
import java.io.DataInputStream;
import java.io.IOException;
import java.net.Socket;
import java.net.UnknownHostException;

import com.pc2ron.interfaces.IFrameReceiver;
import com.pc2ron.interfaces.IFrame;
import com.pc2ron.protocol.Protocol;
import com.pc2ron.frame.FrameReceiver;

public class TestReception {
    public static void main(String[] argv) {        
        try {
            IProtocol proto = Protocol.getInstance();
            proto.connexion("127.0.0.1", 5555);
            
            // start
            proto.getContenuTrame();

            // pause
            proto.getContenuTrame();
            
            // joueurs
            proto.getContenuTrame();
        } catch (Exception e1) {
            // TODO Auto-generated catch block
            e1.printStackTrace();
        }
    }
}
