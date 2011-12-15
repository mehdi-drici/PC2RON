package com.pc2ron.interfaces;

public interface IVisitor<Data, Result> {
    Result visit (IFrame trame, Data data);
    Result visit (IInt8 donnee, Data data);
    Result visit (IInt16 donnee, Data data);
    Result visit (IInt32 donnee, Data data);
    Result visit (IUint8 donnee, Data data);
    Result visit (IUint16 donnee, Data data);
    Result visit (IUInt32 donnee, Data data);
    Result visit (IString donnee, Data data);
    Result visit (IDouble donnee, Data data);
}
