#include "jogo.h"
#include "ui_jogo.h"
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>

jogo::jogo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::jogo)
{
    ui->setupUi(this);
}

jogo::~jogo()
{
    delete ui;
}
// Rascunho do Baralho

#include <iostream>
#include <string>
#include <vector>
using namespace std;

/**
 * representa o local onde uma carta pode estar
 */
struct LocalCarta {
    string nome;

    LocalCarta(string n) : nome(n) {
    };
};

enum Naipe {
    Paus, Espadas, Copas, Ouros
};

enum CartaValor {
    A, _2, _3, _4, _5, _6, _7, _8, _9, _10, J, Q, K
};



struct Carta : public QGraphicsItem {
    int local;
    Naipe naipe;
    CartaValor valor;

    QRectF boundingRect(){
        return QRectF();
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
        painter
->    }

    Carta(Naipe n, CartaValor v) : naipe(n), valor(v), local(-1) {
    }

    friend ostream & operator<<(ostream & out, Carta & carta) {
        string naipeStr = "empty";
        string valorStr = "empty";
        switch (carta.naipe) {
            case Paus:
                naipeStr = "Paus";
                break;
            case Espadas:
                naipeStr = "Espadas";
                break;
            case Copas:
                naipeStr = "Copas";
                break;
            case Ouros:
                naipeStr = "Ouros";
                break;
        }
        out << naipeStr << ":" << carta.valor << "[" << carta.local << "]";
        return out;
    }

    static void testMe() {
        cout << "Carta::testMe()" << endl;
        Carta carta(Copas, A);
        cout << carta << endl;
    }
};

struct Baralho {
    vector<Carta> m_cartas;

public:

    void preencherDeFormaPadrao() {
        m_cartas.push_back(Carta(Paus, A));
        m_cartas.push_back(Carta(Paus, _2));
        m_cartas.push_back(Carta(Paus, _3));
        m_cartas.push_back(Carta(Paus, _4));
        m_cartas.push_back(Carta(Paus, _5));
        m_cartas.push_back(Carta(Paus, _6));
        m_cartas.push_back(Carta(Paus, _7));
        m_cartas.push_back(Carta(Paus, _8));
        m_cartas.push_back(Carta(Paus, _9));
        m_cartas.push_back(Carta(Paus, _10));
        m_cartas.push_back(Carta(Paus, J));
        m_cartas.push_back(Carta(Paus, Q));
        m_cartas.push_back(Carta(Paus, K));
        m_cartas.push_back(Carta(Espadas, A));
        m_cartas.push_back(Carta(Espadas, _2));
        m_cartas.push_back(Carta(Espadas, _3));
        m_cartas.push_back(Carta(Espadas, _4));
        m_cartas.push_back(Carta(Espadas, _5));
        m_cartas.push_back(Carta(Espadas, _6));
        m_cartas.push_back(Carta(Espadas, _7));
        m_cartas.push_back(Carta(Espadas, _8));
        m_cartas.push_back(Carta(Espadas, _9));
        m_cartas.push_back(Carta(Espadas, _10));
        m_cartas.push_back(Carta(Espadas, J));
        m_cartas.push_back(Carta(Espadas, Q));
        m_cartas.push_back(Carta(Espadas, K));
        m_cartas.push_back(Carta(Copas, A));
        m_cartas.push_back(Carta(Copas, _2));
        m_cartas.push_back(Carta(Copas, _3));
        m_cartas.push_back(Carta(Copas, _4));
        m_cartas.push_back(Carta(Copas, _5));
        m_cartas.push_back(Carta(Copas, _6));
        m_cartas.push_back(Carta(Copas, _7));
        m_cartas.push_back(Carta(Copas, _8));
        m_cartas.push_back(Carta(Copas, _9));
        m_cartas.push_back(Carta(Copas, _10));
        m_cartas.push_back(Carta(Copas, J));
        m_cartas.push_back(Carta(Copas, Q));
        m_cartas.push_back(Carta(Copas, K));
        m_cartas.push_back(Carta(Ouros, A));
        m_cartas.push_back(Carta(Ouros, _2));
        m_cartas.push_back(Carta(Ouros, _3));
        m_cartas.push_back(Carta(Ouros, _4));
        m_cartas.push_back(Carta(Ouros, _5));
        m_cartas.push_back(Carta(Ouros, _6));
        m_cartas.push_back(Carta(Ouros, _7));
        m_cartas.push_back(Carta(Ouros, _8));
        m_cartas.push_back(Carta(Ouros, _9));
        m_cartas.push_back(Carta(Ouros, _10));
        m_cartas.push_back(Carta(Ouros, J));
        m_cartas.push_back(Carta(Ouros, Q));
        m_cartas.push_back(Carta(Ouros, K));
    }

    void embaralhar() {
        std::random_shuffle ( m_cartas.begin(), m_cartas.end() );//Codigo para embaralhar *Experimental*
    }

    void dumpCartas() {
        vector<Carta>::iterator it;
        // a loop to scan the STL container
        for (it = m_cartas.begin();
                it != m_cartas.end();
                it++) {
            cout << *it << endl;
        }
    }

    static void testMe() {
        cout << "Baralho::testMe()" << endl;

        Baralho baralho;

        baralho.preencherDeFormaPadrao();

        baralho.embaralhar();
        baralho.dumpCartas();

    }
};

struct Jogo {
    Baralho m_baralho;
    vector<LocalCarta> m_locais;

    Jogo() {
        m_baralho.preencherDeFormaPadrao();
        m_baralho.embaralhar(); //Embaralhando o baralho preenchido *Experimental*
    }

    void algunsJogadores() {
        m_locais.push_back(LocalCarta("Jogador")); // 0
        m_locais.push_back(LocalCarta("Mesa")); // 1
    }

    /**
     * @param local onde a carta pode estar
     * @return id do local
     */
    int getId(string local) {
        int i = 0;
        vector<LocalCarta>::iterator it;
        for (it = m_locais.begin();
                it != m_locais.end();
                it++) {
//            cout << "DEBUG:" << it->nome << ":" << i << endl;
            if (it->nome == local)
                return i;
            i++;
        }
    }

//    /**
//     * faz todas as cartas irem para a mesa *Versão SBVB*
//     */
//    void cartasNaMesa() {
//        vector<Carta>::iterator it;
//        for (it = m_baralho.m_cartas.begin();
//                it != m_baralho.m_cartas.end();
//                it++) {
//            int i = getId("Mesa");
////            cout << "DEBUG: i=" << i << endl;
//            it->local = i;
//        }
//    }


    /**
     * faz todas as cartas irem para a mesa *Versão Nando Fire*
     */
    void cartasNaMesa() {
        vector<Carta> coluna1;
        vector<Carta> coluna2;
        vector<Carta> coluna3;
        vector<Carta> coluna4;
        vector<Carta> coluna5;
        vector<Carta> coluna6;
        vector<Carta> coluna7;
        vector<Carta> coluna8;
        vector<Carta>::iterator it;
        for (it = m_baralho.m_cartas.begin();
                it != m_baralho.m_cartas.end();
                it++) {
            int i = getId("Mesa");
//            cout << "DEBUG: i=" << i << endl;
            it->local = i;
        }
    }





    static void testMe() {
        cout << "Jogo::testMe()" << endl;
        Jogo jogo;
        jogo.algunsJogadores();
//        cout << jogo.getId("Mesa") << endl;
        jogo.m_baralho.dumpCartas();
        jogo.cartasNaMesa();
        jogo.m_baralho.dumpCartas();


    }


};

//int main() {
//    cout << "hello" << endl;
//    Jogo::testMe();
//    Carta::testMe();
//    Baralho::testMe();


//    return 0;
//}
