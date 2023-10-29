#include <iostream>
#include <fstream>
using namespace std;
struct contact {
    string name ;
    string surname ;
    int numberPhone ;
    contact *next ;
};
contact *head = NULL;
void ajouterContact(string na , string sur , int num)
{
    fstream fout("Contact.txt" , ios::app) ;
    contact *new_contact = new contact ;
    new_contact->name = na;
    new_contact->surname = sur ;
    new_contact->numberPhone = num ;
    fout << "## Name : " << new_contact->name << "\n## Surname : " << new_contact->surname << endl ;
    fout << "## Phone : " << new_contact->numberPhone << "\n\n" ;
    fout.close();
    
    if ( head == NULL)
    {
    head = new_contact ;
    new_contact->next = NULL ;
    }
    else{
        new_contact->next = head->next ;
        head =  new_contact ;
    }
    
}
void SearchContact (string na , string sur )
{
    contact *search ;
    search = head ;
    int input ;
    bool test = false ;
    while(search != NULL)
    {
        if (search->name == na)
        {
            if(search->surname == sur)
            {
                test = true ;
                cout << "## the contact you searching about is :\n" ;
                cout << "--->\t "<< search->name << "\t" << search->surname << " :\t" << search->numberPhone ;
                break ;
            }
            else
            {
                cout << "## did u mean this contact : " << search->surname << endl  ;
                cout << "## if yes type 1 /t ## else type 2 for no : " ;
                cin >> input ;
                if ( input == 1)
                {
                    test = true ;
                cout << "## the contact you searching about is :\n" ;
                cout << "--->\t "<< search->name << "\t" << search->surname << " :\t" << search->numberPhone ;
                    break ;
                    
                }
                else{
                    cout << "## try again and right the name correctly\n" ;
                }
                
            }
        }
        else if (search->surname == sur)
        {
            cout << "## did u mean this contact : " << search->name << endl ;
            cout << "## if yes type 1 /t ## else type 2 for no : " ;
            cin >> input ;
            if ( input == 1)
            {
                test = true ;
                cout << "## the contact you searching about is :\n" ;
                cout << "--->\t "<< search->name << "\t" << search->surname << " :\t" << search->numberPhone ;
                break ;
            }
        }
        search = search->next ;
    }
    if (!test )
    {
        cout << "## your contact desn't existe or you didn't right it correctly please try again :\n" ;
        cout << "## type 1 for try again /t type 2 for exite :\t" ;
        
    }
}
void deleteContact (string na , string sur)
{
    contact *search,*prev ;
    search = head ;
    prev = head ;
    while ( search != NULL)
    {
    if (search->name == na)
    {
        if ( search->surname == sur)
        {
            cout << "## this contact : " << na << "  " << sur << "  " << search->numberPhone ;
            cout << " he is deleted " ;
            prev->next = search->next ;
            
        }
    }
        prev = search ;
        search =search->next ;
    }
}


int main(){
    string na ;
    string sur ;
    int number ;
    cout << "## choose what u want : \n 1-Add a conatct \n 2-Search about a contact \n 3-Delete a contact \n" ;
    cout << "------> \t" ;
    cin >> number ;
    switch (number) {
        case 1:
            cout << "## enter the name of the contact : " ;
            cin >> na ;
            cout << "## enter the surname of the contact : " ;
            cin >> sur ;
            cout << "## enter the numberPhone of the contact : " ;
            cin >> number ;
            ajouterContact(na, sur, number) ;
            
            break;
        case 2:
            
            
        default:
            break;
    }
    
    return 0;
}

