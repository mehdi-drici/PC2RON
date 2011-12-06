package fr.pc2ron.interfaces;

public interface IVisiteur<Data, Result> {
    Result visit (ITrame trame, Data data);
    Result visit (IEntierSigne1 donnee, Data data);
    Result visit (IEntierSigne2 donnee, Data data);
    Result visit (IEntierSigne4 donnee, Data data);
    Result visit (IEntierNonSigne1 donnee, Data data);
    Result visit (IEntierNonSigne2 donnee, Data data);
    Result visit (IEntierNonSigne4 donnee, Data data);
    Result visit (IChaine donnee, Data data);
    Result visit (IFlottant donnee, Data data);
}
