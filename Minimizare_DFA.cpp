#include <fstream>
#include <vector>

using namespace std;
ifstream in ("input.in");
ofstream out ("output.out");
vector < pair < int,char > > p[100];
vector <int> fin;
int mat[100][100];
int mat_stari[100][100];
int f[100];
int nr_stari,nr_tranz,nr_fin;
struct graf
{
    char tranz[100];

};
void citire()
{
    int i,from,to,f;
    char tr;
    in>>nr_stari>>nr_fin>>nr_tranz;
    for (i=0; i<nr_fin; i++)
    {
        in>>f;
        fin.push_back(f);
    }

    while(in>>from>>tr>>to)
    {
        p[from].push_back(make_pair(to,tr));

    }
}
int inFinale(int x)
{
    int i;
    for (i=0; i<fin.size(); i++)
        if (x==fin[i])
            return 1;

    return 0;
}
void marcaj_initial()
{
    int i,j;
    for (i=0; i<nr_stari; i++)
    {
        for (j=0; j<nr_stari; j++)
        {
            if (i>j)
            {
                if (inFinale(i) ^ inFinale(j))
                {
                    mat[i][j]=1;
                }
            }
        }
    }
}
void marcaj_ramas()
{
    int i,j,l,st1,st2,ok=0;
    for (i=1; i<nr_stari; i++)
    {
        for (j=0; j<nr_stari; j++)
        {
            if (!mat[i][j] && i>j)
            {
                for (l=0; l<p[i].size(); l++)
                {
                    st1=p[i][l].first;
                    st2=p[j][l].first;
                    if (mat[st1][st2] || mat[st2][st1])
                    {
                        mat[i][j]=1;
                        ok=1;
                        break;
                    }
                }
            }
        }
    }
    if (ok==1)
        marcaj_ramas();

}

void afis_mat()
{
    int i,j;

    for (i=0; i<nr_stari; i++)
    {
        for(j=0; j<nr_stari; j++)
        {
            if (i>j)
                out<<mat[i][j]<<" ";
        }
        out<<'\n';
    }
}
void afis_test()
{
    int i,j;
    for (i=0; i<nr_stari; i++)
    {
        for (j=0; j<p[i].size(); j++)
            out<<i<<" "<<p[i][j].second<<" "<<p[i][j].first<<'\n';
    }
}

void formare_mat_stari()
{
    int i,j,ki,kj,ok,p1,p2;


    for(i = 0; i < nr_stari; i++)
        for(j = 0; j < nr_stari; j++)
            mat_stari[i][j] = -1;

    for (i=1; i<nr_stari; i++)
    {
        for (j=0; j<i; j++)
        {
            ok=false;
            if (mat[i][j]==0)
            {
                ki = 0;
                kj = 0;
                p1 = -1;
                p2 = -1;
                for(ki = 0; ki < nr_stari && mat_stari[ki][0]!= -1; ki ++)
                {
                    for(kj = 0; kj < nr_stari && mat_stari[ki][kj]!= -1 ; kj ++)
                    {
                        if(mat_stari[ki][kj] == i)
                        {
                            p1 = j;
                            ok = true;
                        }
                        if(mat_stari[ki][kj] == j)
                        {
                            p2 = i;
                            ok = true;
                        }
                    }
                    if (p1!=-1 && p2!=-1)
                        continue;
                    else if (p1!=-1)
                    {
                        mat_stari[ki][kj]=p1;
                        f[p1]++;
                    }
                    else
                    {
                        mat_stari[ki][kj]=p2;
                        f[p2]++;

                    }

                }
                if(ok == false)
                {
                    mat_stari[ki][0] = i;
                    mat_stari[ki][1] = j;
                    f[i] ++;
                    f[j] ++;
                }
            }
        }
    }

    for(ki = 0; mat_stari[ki][0]!= -1; ki++);

    for(int i = 0; i < nr_stari; i++)
        if(f[i] == 0)
        {
            mat_stari[ki][0] = i;
            ki ++;
        }

    int st_fin[100] = {0};


    for(i = 0; i < nr_stari && mat_stari[i][0]!= -1; i++)
        for(j = 0; j < nr_stari && mat_stari[i][j]!= -1; j++)
            if (inFinale(mat_stari[i][j])==1)
                st_fin[i]=1;


    out << "Starile finale sunt: ";
    ok=0;
    for(int i = 0; i < nr_stari && mat_stari[i][0]!= -1; i ++)
    {
        if(st_fin[i] == 1)
        {
            out << i;
            ok = 1;
        }

        if(ok==1)
            out << " ";
    }
}

void minimizare()
{
    int i,j,ki,kj,ok=0,k;
    out<<'\n'<<"Automatul minimal este: \n";

    for(i = 0; i < nr_stari; i ++)
        for (j=0; j<p[k].size(); j++)
            for(k = 0; k < nr_stari; k ++)
            {
                if (mat_stari[i][0]==k)
                {
                    out<<i;
                    out << " " << p[i][j].second << " ";
                    ok = 0;
                    for(ki = 0; ki < nr_stari && mat_stari[ki][0] != -1 && ok == 0; ki++)
                        for(kj = 0; kj < nr_stari && mat_stari[ki][kj] != -1; kj++)
                            if(mat_stari[ki][kj] == p[k][j].first)
                            {
                                ok = 1;
                                break;
                            }
                    out<<ki-1;
                    out << endl;
                    break;
                }
            }
}
int main()
{
    citire();
    marcaj_initial();
    marcaj_ramas();
    afis_mat();

    formare_mat_stari();
    minimizare();
    //afis_test();
}
