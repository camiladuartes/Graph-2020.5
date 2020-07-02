#include <iostream>

using namespace std;

class Aresta{
    
    private:
        int vertice1;
        int vertice2;
        int wheight;

    public:
        Aresta(int vertice1, int vertice2, int wheight){
            this->vertice1 = vertice1;
            this->vertice2 = vertice2;
            this->wheight = wheight;
        }

        int getVertice1() { return this->vertice1;}
        int getVertice2() { return this->vertice2;}
        int getWheight() { return this->wheight;}
        
        void setVertice1(int vertice1){ this->vertice1 = vertice1;}
        void setVertice2(int vertice2){ this->vertice2 = vertice2;}
        void setWheight(int wheight){ this->wheight = wheight;}

        bool operator< (const Aresta& aresta2) const{
		    return (wheight < aresta2.wheight);
        }   

        friend ostream &operator<<(ostream &os, const Aresta &aresta){
            os << aresta.vertice1 << " - " << aresta.vertice2 << "----->" << endl;

            return os;
        }


};