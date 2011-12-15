package com.pc2ron;

import com.pc2ron.interfaces.IDataString;
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
            proto.connect("127.0.0.1", 5555);
            
            // start
            proto.readFrame();

            // pause
            proto.readFrame();
            
            // joueurs
            proto.readFrame();
        } catch (Exception e1) {
            // TODO Auto-generated catch block
            e1.printStackTrace();
        }
    }
}
