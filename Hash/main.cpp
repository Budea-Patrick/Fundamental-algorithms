/*
 * Hash tables are used for searching through a big amount of entries in a small amount of operations.
 * Hash tables have an average complexity of O(1) for searching but it depends a lot on the
 * hashes of new entries. If a lot of collisions happen because the hash function in not adequate then the
 * complexity rises to O(n) in the worst case.
 *
 * In order to make the hash search faster it is recommended that the filling factor is not 1. Having a few empty slots
 * in the table makes the seach operation faster.
 *
 * Still using hash functions is a good idea for those applications which need fast searching.
 *
 * */
#include <bits/stdc++.h>
#include <windows.h>
#define NR_OF_TESTS 1
#define N 11
#define m 6
#define c1 2
#define c2 5
#define c3 7
using namespace std;

typedef struct {
    int id;
    string name;
}Entry;

long long opsPerSearch;
long long totalOpsFound, totalOpsNotFound;
long long maxEffortFound, maxEffortNotFound;

long long totalOpsFoundGlobal, totalOpsNotFoundGlobal;
long long maxEffortFoundGlobal, maxEffortNotFoundGlobal;

Entry hashTable[N];
string entries[m];

char alpha[]={"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"};
double fillingFactor[]={0.8, 0.85, 0.9, 0.99};

char getRandomChar()
{
    return alpha[rand()%52];
}

string generateRandomString()
{
    int length=30; // the string become are generated more randomly if length remains exactly 30
    srand(rand()^ time(NULL));
    string s="";
    for(int i=0;i<length;i++){
        s=s+getRandomChar();
    }
    return s;
}

int hashFunction(string s, int j)
{
    int sum=0;
    for(int i=0;i<s.length();i++){
        sum=sum+s[i];
    }
    return (c3*sum+c1*j+c2*j*j)%N;
}

int generateElements(double alfa)
{
    int n=N*alfa;
    for(int i=0;i<n;i++){
        Sleep(25);
        string aux=generateRandomString();
        cout<<aux<<" "<<hashFunction(aux,0)<<'\n';
        int j=0;
        int hash;
        do{
            hash= hashFunction(aux,j);
            if(hashTable[hash].id==-1){
                hashTable[hash].id=hash;
                hashTable[hash].name=aux;
                break;
            }
            else{
                j++;
            }
        }while(j<N);
    }
    printf("\n");
    return n;
}

string rememberRandomEntry()
{
    int aux=rand()%N;
    while(hashTable[aux].id==-1){
        aux=rand()%N;
    }
    return hashTable[aux].name;
}

void elementsToBeSearched()
{

    for(int i=0;i<m/2;i++){
        entries[i]=rememberRandomEntry();
    }
    for(int i=m/2;i<m;i++){
        Sleep(25);
        entries[i]=generateRandomString();
    }
    for(int i=0;i<m;i++){
        cout<<entries[i]<<'\n';
    }
    printf("\n");
}

int search(string s)
{
    cout<<s<<" with the hash of: "<<hashFunction(s,0)<<"\n";
    int j=-1; // i
    int hash; // j
    opsPerSearch=0;
    do{
        j++;
        hash=hashFunction(s,j);
        opsPerSearch++;
        if(hashTable[hash].id!=-1 and hashTable[hash].name==s){
            cout<<"Found after: "<<opsPerSearch<<" on pos "<<hashTable[hash].id<<'\n';
            totalOpsFound=totalOpsFound+opsPerSearch;
            if(maxEffortFound<opsPerSearch){
                maxEffortFound=opsPerSearch;
            }
            return hashTable[hash].id;
        }
    }while(hashTable[hash].id!=-1 and c1*j+c2*j*j<N);
    cout<<"Not found after "<<opsPerSearch<<"\n";
    totalOpsNotFound=totalOpsNotFound+opsPerSearch;
    if(maxEffortNotFound<opsPerSearch){
        maxEffortNotFound=opsPerSearch;
    }
    return -2;
}

void print()
{
    for(int i=0;i<N;i++){
        cout<<hashTable[i].id<<" "<<hashTable[i].name<<'\n';
    }
}

void reset()
{
    totalOpsFound=0;
    totalOpsNotFound=0;
    maxEffortFound=0;
    maxEffortNotFound=0;
    for(int i=0;i<N;i++){
        hashTable[i].id=-1;
        hashTable[i].name="";
    }
    for(int i=0;i<m;i++){
        entries[i]="";
    }
}

void resetGlobal()
{
    totalOpsFoundGlobal=0;
    totalOpsNotFoundGlobal=0;
    maxEffortFoundGlobal=0;
    maxEffortNotFoundGlobal=0;
}

void makeSound()
{
    for(int i=0;i<5;i++){
        Beep(523,500);
    }
}

int main()
{
    FILE *out=fopen("table.txt", "w");
    fprintf(out,"Filling factor      Avg. effort found       Max. effort found       Avg. effort not-found       Max. effort not-found\n");
    for(int i=0;i<1;i++){
        ///cout<<fillingFactor[i]<<"                          ";
        fprintf(out,"%.2f                          ",fillingFactor[i]);
        for(int test=0;test<NR_OF_TESTS;test++){
            reset();
            generateElements(fillingFactor[i]);
            elementsToBeSearched();
            for(int j=0;j<m;j++){
                search(entries[j]);
            }
            printf("\n");
            print();
            totalOpsFoundGlobal=totalOpsFoundGlobal+totalOpsFound/(m/2);
            totalOpsNotFoundGlobal=totalOpsNotFoundGlobal+totalOpsNotFound/(m/2);
            if(maxEffortFoundGlobal<maxEffortFound){
                maxEffortFoundGlobal=maxEffortFound;
            }
            if(maxEffortNotFoundGlobal<maxEffortNotFound){
                maxEffortNotFoundGlobal=maxEffortNotFound;
            }
        }

        fprintf(out,"%.2f              %.2f                      %.2f                       %.2f\n",(double)totalOpsFoundGlobal/NR_OF_TESTS,(double)maxEffortFoundGlobal,
                (double)totalOpsNotFoundGlobal/NR_OF_TESTS,(double)maxEffortNotFoundGlobal);
        resetGlobal();
    }
    makeSound();
    return 0;
}