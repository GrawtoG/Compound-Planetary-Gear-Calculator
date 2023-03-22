#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>
#include <time.h>
using namespace std;

const double PI = 3.14159265359;
void delay(int number_of_miliseconds)
{



    // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + number_of_miliseconds)
        ;
}
struct Vector2f{
public:
    float x;
    float y;

    Vector2f(float _x, float _y){
        this->x=_x;
        this->y=_y;

    }


};
struct przekladnia{
public:
    int S1;
    int P1;
    int R1;
    int P2;
    int R2;
    double przelozenie;
    double znorPrzelozenie;
    double obliczPrzelozenie(){
        this->przelozenie = (double)((double)S1/(double)(R1+S1))*(1-((double)((double)R1*P2)/((double)P1*R2)));
        this->znorPrzelozenie=(double)1/przelozenie;
    }

    przekladnia(int _S1,int _P1,int _R1,int _P2,int _R2){
        this->S1=_S1;
        this->P1=_P1;
        this->R1=_R1;
        this->P2=_P2;
        this->R2=_R2;

    };
};
bool porownanie(przekladnia przek1, przekladnia przek2){
if(przek1.przelozenie>przek2.przelozenie){
    return true;
}
return false;

}
bool porownanieOdleglosci(pair<przekladnia, float> p1,pair<przekladnia, float> p2){
    if(p1.second<p2.second)
        return true;
    return false;
}
void WypiszPrzekladnie(przekladnia przek){
    cout<<"Przelozenie: 1:"<<przek.znorPrzelozenie<<endl;
    cout<<"Sun1: "<<przek.S1<<endl;
    cout<<"Planet1: "<<przek.P1<<endl;
    cout<<"Ring1: "<<przek.R1<<endl;
    cout<<"Sun2: "<<przek.R2-2*przek.P2<<endl;
    cout<<"Planet2: "<<przek.P2<<endl;
    cout<<"Ring2: "<<przek.R2<<endl;
}
void WypiszPrzekladnie2(przekladnia przek){
   printf("%f\n",przek.znorPrzelozenie);
   printf("%i\n",przek.S1);
   printf("%i\n",przek.P1);
   printf("%i\n",przek.R1);
   printf("%i\n",przek.R2-2*przek.P2);
   printf("%i\n",przek.P2);
   printf("%i\n",przek.R2);
}
float sqrDistance(int x1, int y1, int x2, int y2)
{
    // Calculating distance
    return pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0;
}
float degToRad(float deg){
    return (deg * (PI / 180));

}
int main()
{
    /*
    const int S1 = 10;
    const int P1 = 14;
    const int R1 = 38;
    const int P2 = 12;
    const int R2 = 32;
    if(S1<=0||P1<=0||R1<=0||P2<=0||R2<=0){
        cout<<"Liczba zebow nie moze byc mniejsza od 1!"<<endl;
        return 0;
    }
    przekladnia przek(S1,P1,R1,P2,R2);
    przek.obliczPrzelozenie();
   // przelozenie = (double)((double)S1/(double)(R1+S1))*(1-((double)((double)R1*P2)/((double)P1*R2)));
    cout<<setprecision(14)<<"jeden obrot S1 to: "<<przek.przelozenie<<" obrotu R2"<<endl;
    cout<<setprecision(14)<<"znormalizowane przelozenie: 1:"<<(double)1/przek.przelozenie<<endl;
    */
    const int minS1=5;
    const int maxS1=50;
    const int minP1=5;
    const int maxP1=50;
    const int minR1=5;
    const int maxR1=150;
    const int minP2=5;
    const int maxP2=50;
    const int minR2=5;
    const int maxR2=150;
    const int minS2 =5;
    const int maxS2 =50;

    const int maxRoznicaR2R1 = 1;
    const int maxRoznicaP2P1 = 1;


    const int liczbaPlanet = 4;

    float minDistMiedzyZebamiPlanet = 1;
    float m;
    int S2;
    int liczbaKombinacji = (maxS1-minS1+1)*(maxP1-minP1+1)*(maxR1-minR1+1)*(maxP2-minP2+1)*(maxR2-minR2+1);
    cout<<"Liczba kombinacji: "<<liczbaKombinacji<<endl;
    vector<przekladnia> wszyztskieMozliwePrzekladnie;
    float alfa = (float)360/liczbaPlanet;
    cout<<"afla: "<<alfa<<endl;
    for(int S1=minS1;S1<=maxS1;S1++){
        for(int P1=minP1;P1<=maxP1;P1++){
            for(int R1=minR1;R1<=maxR1;R1++){
                for(int P2=minP2;P2<=maxP2;P2++){
                    for(int R2=minR2;R2<=maxR2;R2++){

                        S2=R2-2*P2;
                        if(S2<minS2||S2>maxS2){
                            continue;
                        }
                        if(R1!=2*P1+S1)
                            continue;
                        if(R2!=2*P2+S2)
                            continue;

                        if(abs(R2-R1)>maxRoznicaR2R1){
                            continue;
                        }
                        if(abs(P2-P1)>maxRoznicaP2P1){
                            continue;
                        }

                        Vector2f p1GV(0, S1/(float)2+P1/(float)2);
                        Vector2f p1PV((S1/(float)2+P1/(float)2)*cos(degToRad(90-alfa)), (S1/(float)2+P1/(float)2)*sin(degToRad(90-alfa)));
                        //float sqrDist1 = (p1GV.x-p1PV.x)*(p1GV.x-p1PV.x)+(p1GV.y-p1PV.y)*(p1GV.y-p1PV.y);
                        float sqrDist1 = sqrDistance(p1GV.x, p1GV.y, p1PV.x, p1PV.y);
                        float sqrMinDist1 = P1*P1 + minDistMiedzyZebamiPlanet;
                       // cout<<"actDist: "<<sqrDist1<<endl;
                        //cout<<"minDist: "<<sqrMinDist1<<endl;
                        //cout<<sqrDist1<<endl;
                        if(sqrDist1<sqrMinDist1){
                            continue;
                        }
                        Vector2f p2GV(0, S2/(float)2+P2/(float)2);
                        Vector2f p2PV((S2/(float)2+P2/(float)2)*cos(degToRad(90-alfa)), (S2/(float)2+P2/(float)2)*sin(degToRad(90-alfa)));
                        //float sqrDist2 = (p2GV.x-p2PV.x)*(p2GV.x-p2PV.x)+(p2GV.y-p2PV.y)*(p2GV.y-p2PV.y);
                        float sqrDist2 = sqrDistance(p2GV.x, p2GV.y, p2PV.x, p2PV.y);
                        float sqrMinDist2 = P2*P2+minDistMiedzyZebamiPlanet;
                        if(sqrDist2<sqrMinDist2){
                            continue;
                        }

                        //m=((R1+S1))/(float)liczbaPlanet;
                        //if(floor(m)!=m)
                            //continue;
                        //m =((R2+S2)/(float)liczbaPlanet);
                        //if(floor(m)!=m)
                          //  continue;
                        wszyztskieMozliwePrzekladnie.push_back(przekladnia(S1,P1,R1,P2,R2));
                        wszyztskieMozliwePrzekladnie[wszyztskieMozliwePrzekladnie.size()-1].obliczPrzelozenie();
                        if(wszyztskieMozliwePrzekladnie[wszyztskieMozliwePrzekladnie.size()-1].przelozenie>=0){
                            wszyztskieMozliwePrzekladnie.erase(wszyztskieMozliwePrzekladnie.end());
                        }
                    }
                }
            }
        }
    }
    cout<<"Liczba poprawnych kombinacji: "<<wszyztskieMozliwePrzekladnie.size()<<endl;
    sort(wszyztskieMozliwePrzekladnie.begin(),wszyztskieMozliwePrzekladnie.end(),porownanie);
   /*
   for(int i=0;i<wszyztskieMozliwePrzekladnie.size();i++){
        delay(10);
        WypiszPrzekladnie(wszyztskieMozliwePrzekladnie[i]);
        cout.flush();
    }
*/

    float poszPrzel;
    cout<<"Poszukiwane przelozenie: 1:";
    cin>>poszPrzel;
    if(poszPrzel>0){
        poszPrzel*=-1;
    }
    float odleglosc=0;
    vector<pair<przekladnia, float>> odleglosci;
    for(int i=0;i<wszyztskieMozliwePrzekladnie.size();i++){
        odleglosci.push_back(pair<przekladnia, float>{wszyztskieMozliwePrzekladnie[i],0});
        odleglosc = abs(poszPrzel-odleglosci[i].first.znorPrzelozenie);
        odleglosci[i].second=odleglosc;
    }

    int ileChceszZobaczyc =3;
    cout<<"Ile chcesz zobaczyc wynikow? "<<endl;
    cin>>ileChceszZobaczyc;
    sort(odleglosci.begin(), odleglosci.end(), porownanieOdleglosci);
    for(int i=0;i<ileChceszZobaczyc;i++){
        delay(10);
        WypiszPrzekladnie(odleglosci[i].first);
        cout.flush();
        cout<<endl;
    }


    return 0;
}
