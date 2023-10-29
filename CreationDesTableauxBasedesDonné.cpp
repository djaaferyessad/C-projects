// Djaafar yessad groupe : 08
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
using namespace std;
string no , fonc , emb , nomD , lieu , co;
int noS , sal  , noD , input , nu;
fstream fichier1("EMP.txt" , ios::app) ;
fstream fichier2("DEPT.txt" , ios::app) ;
struct employe {
    int numeEmp ;
    string nomEmp ;
    string fonction ;
    int noSup ;
    string embauche ;
    int salaire ;
    string comm ;
    int noDept ;
    employe *suivant ;
    
};
employe *head1 = NULL ;
struct dept {
    int noDept ;
    string nomDept ;
    string lieu ;
    dept *suivant ;
};
dept *head2 = NULL ;
void textemploye ()
{
    cout << "## enter le numéro d'employé : " ;
    cin >> nu ;
    cout << "## enter le nom de l'employé : " ;
    cin >> no ;
    cout << "## enter le fonction de l'employé : " ;
    cin >> fonc;
    cout << "## enter le numéro du supérieur : " ;
    cin >> noS ;
    cout << "## enter le date d'employé Ex : 12/12/2012 --> : " ;
    cin >> emb ;
    cout << "## enter le salaire de l'employé : " ;
    cin >> sal ;
    cout << "## enter le commission : " ;
    cin >> co ;
    cout << "## enter le numéro de département auquel appartient l'employé : " ;
    cin >> noD ;
}
void ajouterEmp(int nu , string no , string fonc , int noS , string emb , int sal , string co , int noD,bool R)
{
    
    employe *last ,*new_emp;
    new_emp = new employe ;
    new_emp->numeEmp = nu ;
    new_emp->nomEmp = no ;
    new_emp->fonction = fonc ;
    new_emp->noSup = noS ;
    new_emp->embauche = emb ;
    new_emp->salaire = sal ;
    new_emp->comm = co ;
    new_emp->noDept = noD ;
    if ( head1 == NULL)
    {
        head1 = new_emp ;
    }
    else
    {
        last = head1 ;
    while ( last->suivant != NULL)
    {
        last = last->suivant ;
    }
        last->suivant = new_emp ;
    }
    new_emp->suivant = NULL ;
    if ( R)
    {
    fichier1 << left << setw(6) << nu << setw(10) << no << setw(15) << fonc << setw(6) << noS << setw(12)<< emb << setw(7) << sal << setw(6) << co << setw(4) <<noD << endl ;
    }
    
}
void textDEPT ()
{
    cout << "## enter numéro de département : " ;
    cin >> noD ;
    cout << "## enter le nom du département : " ;
    cin >> nomD ;
    cout << "## enter emplacement du département : " ;
    cin >> lieu ;
}
void ajouterDEPT (int noD , string nomD , string li,bool R)
{
    dept *last ,*new_dept;
    new_dept = new dept ;
    new_dept->noDept = noD ;
    new_dept->lieu = li ;
    new_dept->nomDept = nomD ;
    if ( head2 == NULL)
    {
        head2 = new_dept ;
    }
    else
    {
        last = head2 ;
    while ( last->suivant != NULL)
    {
        last = last->suivant ;
    }
    last->suivant = new_dept ;
    }
    new_dept->suivant = NULL ;
    if (R)
    fichier2 << left << setw(4) << noD << setw(13) << nomD << setw(8) << li << endl ;
}
void deleteEmp (int nuEmp)
{
    employe *emp,*prev;
    bool test =  false ;
    emp = head1 ;
    prev = head1 ;
    while (emp != NULL)
    {
        if (emp->numeEmp == nuEmp)
        {
            prev->suivant = emp->suivant ;
            test = true ;
            break ;
        }
        prev = emp ;
        emp = emp->suivant;
    }
    if ( !test )
    {
        cout << "this employe doesn't existe \n" ;
    }
    
}
void fillTheList()
{
    // this for fill the data of emp and dept to the linked list
    ifstream fin ("EMP.txt") ;
    ifstream gin("DEPT.txt") ;
    string str  , str1;
    string saveStr[300] , saveStr1[300];
    bool right = false ;
    int saveInt[300],saveInt1[300];
    int i=0,s=0,j=0,r=0;
    // this for converting string to integer
    while(fin >> str )
    {
        saveStr[i] = str ;
        if (i == s || i == s+3 || i == s+5 || i == s+7 )
        {
            stringstream geek(saveStr[i]);
            geek >> saveInt[j];
            j++ ;
            if ( i == 7+r)
            {
                s = s+8 ;
                r = r+8 ;
            }
        }
        i++;
        
    }
    r=0 ;
    i=0;
    j=0;
    ifstream fcin ("EMP.txt") ;
    // this for adding the data in the linked list from emp.txt
    while ( fcin >> str )
    {
        
        if (i == 0+r)
        {
            right = false ;
            ajouterEmp(saveInt[j], saveStr[i+1], saveStr[i+2], saveInt[j+1], saveStr[i+4], saveInt[j+2], saveStr[i+6], saveInt[j+3],right) ;
        }
        if ( i == 7+r)
        {
            r = r+8 ;
            j = j+4 ;
        }
        i++;
    }
    
    // this for converting string to integer
    i=0 ;
    s=0 ;
    j=0 ;
    r=0 ;
    while(gin >> str1 )
    {
        saveStr1[i] = str1 ;
        if (i == s )
        {
            int x;
            stringstream move(saveStr1[i]);
            move >> x;
            saveInt1[j] = x ;
            j++ ;
            
            s = s+3 ;
        }
        i++;
        
    }
    
    // this for fill the linked list by what is inside of DEPT.txt
    i=0 ;
    j=0 ;
    ifstream gcin("DEPT.txt") ;
    while ( gcin >> str1 )
    {
        
        if (i == 0+r)
        {
            right = false ;
            ajouterDEPT(saveInt1[j], saveStr1[i+1], saveStr1[i+2],right) ;
        }
        if ( i == 2+r)
        {
            r = r+3 ;
            j = j+1 ;
        }
        i++;
    }
}
void CBD () {

    bool right ;
    cout << "## enter combien des employe : " ;
    cin >> input ;
    for (int i=0 ; i<input ; i++)
    {
        cout << "## employé numéro " << i+1 << "\n" ;
        textemploye() ;
        right = true ;
        ajouterEmp(nu ,no, fonc, noS, emb, sal, co, noD,right) ;
        
    }
    cout << "## combien d'épartement : " ;
    cin >> input ;
    for ( int i=0 ; i<input ; i++)
    {
        cout << "## Departement numéro " << i+1 << "\n" ;
        textDEPT() ;
        right = true ;
        ajouterDEPT(noD, nomD, lieu,right) ;
    }
    fichier2.close();
    fichier1.close();
    
    
}
void menu ()
{
    cout << "## enter voter choix : \n" ;
    cout << "1) Création de la base de données \n" ;
    cout << "2) Ajoute d'un département \n" ;
    cout << "3) Ajoute d'un employé \n" ;
    cout << "4) Suppression d'un employé \n" ;
    cout << "5) Recherche d'un département selon le numéro du département \n" ;
    cout << "6) Requéte(1)  : Donner tous les n-uplets de DEPT \n" ;
    cout << "7) Requéte(2)  : Donner tous les n-uplets de EMP \n" ;
    cout << "8) Requéte(3)  : Donner les noms et les salaires des employés \n" ;
    cout << "9) Requéte(4)  : Donner les professions des employés \n" ;
    cout << "10) Requéte(5) : Faire le produit cartésien enter EMP et DEPT \n" ;
    cout << "11) Requéte(6) : Donner les noms des employés et les noms de leur département \n" ;
    cout << "12) Requéte(7) : Donner les numéros des employés travaillant a Rennes \n";
    cout << "13) Requéte(8) : La list de tous les employés dont le salaire compris enter A et B \n" ;
    cout << "14) Requéte(9) : Affichier le nom des employés qui travaillent pour le département 'recherche' \n";
    cout << "15) Requéte(10): Afficher le nom des départements qui n'ont pas ingénieurs \n\n" ;
    cout << " ------------> :  " ;
}
void rechercheDEPT (int n)
{
    dept *search ;
    search = head2 ;
    while (search != NULL)
    {
        if ( search->noDept == n)
        {
            cout << n << "\t" << search->nomDept << "\t" << search->lieu  ;
        }
        search = search->suivant ;
    }
}
void requete1()
{
    dept *dpt ;
    dpt = head2 ;
    while (dpt != NULL)
    {
        cout << left << dpt->noDept << "  " << setw(11) << dpt->nomDept << dpt->lieu << endl ;
        dpt = dpt->suivant ;
    }
    
}
void requete2()
{
    employe *emp ;
    emp = head1 ;
    while ( emp != NULL)
    {
     cout << left << setw(5) << emp->numeEmp << " " << setw(9) << emp->nomEmp << " " << setw(13)<< emp->fonction << " " << setw(5) << emp->noSup << " " << emp->embauche << " " << setw(5)<< emp->salaire << " " << emp->comm << " " << emp->noDept << endl ;
        emp = emp->suivant ;
    }
}
void requete3(){
    employe *emp ;
    emp = head1 ;
    while (emp != NULL)
    {
        cout << emp->nomEmp << "\t" << emp->salaire << endl ;
        emp = emp->suivant ;
    }
}
void requete4(){
    employe *emp ;
    emp = head1 ;
    bool test = false;
    string save[50] ;
    int s=0 , j=1;
    while (emp != NULL)
    {
        test = false ;
        save[s] = emp->fonction ;
        if (s == 0 && save[s] != "DIRECTEUR")
            cout << save[0] << endl ;
        else if(s != 0){
            j = s ;
            while ( j != 0)
            {
            if ( save [s] == save[j-1] )
            {
                test = true ;
                break ;
            }
                j-- ;
            }
            if (!test && save[s] != "DIRECTEUR")
            {
                cout << save[s] << endl ;
            }
        }
        s++;
        emp = emp->suivant ;
    }
}
void requete5()
{
    employe *emp ;
    dept *dpt ;
    emp = head1 ; dpt = head2 ;
    int i=0 , k=0 ;
    while (emp != NULL )
    {
        emp = emp->suivant ;
        i++ ;
    }
    while (dpt != NULL)
    {
        dpt = dpt->suivant ;
        k++;
    }
    cout << "le produit cartésien enter EMP et DEPT = " << i << " X " << k << " = " << k*i << endl ;
    
}
void requete6()
{
    employe *emp ;
    emp = head1 ;
    dept *search ;
    while ( emp != NULL )
    {
        search = head2 ;
        cout << emp->nomEmp << "\t" ;
        while ( search != NULL)
        {
        if ( search->noDept == emp->noDept)
        {
            cout << search->nomDept << endl ;
        }
            search = search->suivant ;
            
        }
        emp = emp->suivant ;
        
    }
    
}
void requete7()
{
    employe *emp ;
    emp = head1 ;
    while ( emp != NULL)
    {
        
            if (emp->noDept == 10)
            {
                cout << emp->nomEmp << endl ;
            }
            emp = emp->suivant ;
        
        
    }
    
}
void requete8(int a , int b)
{
    int max=a,min=b ;
    if(b>a)
    {
        max = b;
        min = a;
    }
    employe *emp ;
    emp = head1 ;
    while (emp != NULL)
    {
        if ( emp->salaire >min && emp->salaire < max )
        {
            cout << emp->nomEmp << endl ;
        }
        emp = emp->suivant ;
    }
}
void requete9(){
    requete7() ;
}
void requete10(){
    employe *emp ;
    emp = head1 ;
    dept *dpt ;
    dpt = head2 ;
    bool test ;
    int save[100];
    int i=0 , j=0;
    while( emp != NULL)
    {
        if ( emp->fonction == "INGENIEUR")
        {
            save[i] = emp->noDept ;
            i++ ;
            j++ ;
        }
        emp = emp->suivant ;
    }
    while (dpt != NULL)
    {
        test = false ;
        i=0 ;
        while ( i < j)
        {
            if(dpt->noDept == save[i])
            {
                test = true ;
                break ;
            }
            i++ ;
        }
        if(!test)
            cout << dpt->nomDept << endl ;
        
        dpt = dpt->suivant ;
    }
    
    
}


int main()
{
    int input , number ;
    int a , b ;
    bool right = false ;
    do {
    fillTheList() ;
    menu() ;
    cin >> input ;
    
    switch (input) {
        case 1:
            CBD() ;
            break;
        case 2:
            textDEPT() ;
            right = true ;
            ajouterDEPT(noD, nomD, lieu,right) ;
            break ;
        case 3:
            textemploye() ;
            right = true ;
            ajouterEmp(nu ,no, fonc, noS, emb, sal, co, noD,right) ;
            break ;
        case 4:
            cout << "## enter le numéro de l'employe : " ;
            cin >> nu ;
            deleteEmp(nu) ;
            break ;
        case 5:
            cout << "## enter le numéro de d'épartement : " ;
            cin >> number ;
            rechercheDEPT(number) ;
            break ;
        case 6:
            requete1() ;
            break ;
        case 7:
            requete2() ;
            break ;
        case 8:
            requete3();
            break ;
        case 9:
            requete4() ;
            break ;
        case 10:
            requete5();
            break ;
        case 11:
            requete6() ;
            break ;
        case 12:
            requete7() ;
            break ;
        case 13:
            cout << "## enter le salaire enter a et b : \n 1-salaire a : " ;
            cin >> a ;
            cout << " 2- salaire b : ";
            cin >> b ;
            requete8(a, b) ;
        case 14:
            requete9();
            break ;
        case 15:
            requete10() ;
            break ;
        default:
            cout << "## wrong number \n" ;
            break;
    }
        cout << "## if u want to continue type 1 if u not type 2 : " ;
        cin >> input ;
    } while ( input == 1 ) ;

}
