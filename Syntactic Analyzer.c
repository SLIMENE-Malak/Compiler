#include <stdio.h>
#define program 1
#define id 2
#define pt 3
#define pv 4
#define var 5
#define dp 6
#define v 7
#define integer 8
#define chari 9
#define begin 10
#define end 11
#define iff 12
#define whille 13
#define write 14
#define writeln 15
#define read 16
#define readln 17
#define aff 18
#define po 19
#define pf 20
#define opadd 21
#define opmul 22
#define oprel 23
#define nb 24
#define elsee 25
#define then 26
#define doo 27

int symbole;
void P();void Dcl();void D();void Liste_id();void L();void Type();
void Inst_composee();void Inst();void Liste_inst();void L_I();
void I();void Exp();void S();void Terme();void T();void Facteur();
void ES();void Exp_simple();
int symbole_suiv()
{
    int s;
    printf("donner le symbole suivant\n");
    scanf("%d",&s);
    return s;
}

void error()
{
    printf("symbole non accepte !!\n");
}

void accepter(int s)
{
    if(symbole==s)
    {
        symbole=symbole_suiv();
    }
    else
    {
        error();
    }
}

void P()
{
    if(symbole==program) {
            accepter(program);accepter(id);accepter(pv);Dcl();
            Inst_composee();accepter(pt);
    }
    else error();
}

void Dcl()
{
    D();
}

void D()
{
    if(symbole==var)
    {
        accepter(var);Liste_id();accepter(dp);Type();accepter(pv);
        D();
    }
}

void Liste_id()
{
    if(symbole==id)
    {
        accepter(id);L();
    }
    else error();

}

void L()
{
    if(symbole==v)
    {
        accepter(v);accepter(id);L();
    }
}

void Type()
{
    if(symbole==integer) accepter(integer);
    else if (symbole==chari) accepter(chari);
    else error();
}

void Inst_composee()
{
    if(symbole==begin)
    {
        accepter(begin);Inst();accepter(end);
    }
    else error();
}

void Inst()
{
    Liste_inst();
}

void Liste_inst()
{
    I();L_I();
}

void L_I()
{
    if(symbole==pv)
    {
        accepter(pv);I();L_I();
    }
}

void I()
{
    if(symbole==id)
    {
        accepter(id);accepter(aff);Exp_simple();
    }
    else if (symbole==iff)
    {
        accepter(iff);Exp();accepter(then);I();accepter(elsee);I();
    }
    else if (symbole==whille)
    {
        accepter(whille);Exp();accepter(doo);I();
    }
    else if (symbole==read)
    {
        accepter(read);accepter(po);accepter(id);accepter(pf);
    }
    else if (symbole==readln)
    {
        accepter(readln);accepter(po);accepter(id);accepter(pf);
    }
    else if (symbole==write)
    {
        accepter(write);accepter(po);accepter(id);accepter(pf);
    }
    else if (symbole==writeln)
    {
        accepter(writeln);accepter(po);accepter(id);accepter(pf);
    }
}

void Exp()
{
    Exp_simple();S();
}

void S()
{
    if(symbole==oprel)
    {
        accepter(oprel);Exp_simple();
    }
}

void Exp_simple()
{
    Terme();ES();
}

void ES()
{
    if(symbole==opadd)
    {
        accepter(opadd);Terme();ES();
    }
}

void Terme()
{
    Facteur();T();
}

void T()
{
    if(symbole==opmul)
    {
        accepter(opmul);Facteur();T();
    }
}

void Facteur()
{
    if(symbole==id) accepter(id);
    else if(symbole==nb) accepter(nb);
    else if(symbole==po)
    {
        accepter(po);Exp_simple();accepter(pf);
    }
    else error();

}

int main()
{
    printf("donner un symbole\n");
    scanf("%d",&symbole);
    P();
    return 0;
}
