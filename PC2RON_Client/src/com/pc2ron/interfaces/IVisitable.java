package com.pc2ron.interfaces;

/**
 * Interface qui rend un objet visitable
 * Elle fait partie du Design Pattern Visitor
 * @author Mehdi Drici
 */
public interface IVisitable {
    <Data, Result> Result accept (IVisitor<Data, Result> visitor, Data data);
}
