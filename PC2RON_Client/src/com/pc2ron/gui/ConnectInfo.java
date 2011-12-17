/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.pc2ron.gui;

/**
 *
 * @author mehdi
 */
public class ConnectInfo {
    private String host;
    private int port;

    public ConnectInfo() {
    }

    public ConnectInfo(String host, int port){
        this.host = host;
        this.port = port;
    }

    // Getters
    public String getHost() {
        return host;
    }

    public int getPort() {
        return port;
    }

    // Setters
    public void setHost(String host) {
        this.host = host;
    }

    public void setPort(int port) {
        this.port = port;
    }


    @Override
    public String toString(){
        String connectInfo = "";

        connectInfo += "Host : " + this.host;
        connectInfo += "Port : " + this.port;

        return connectInfo;
    }
}
