#include <QCoreApplication>
#include <iostream>
#include <QMap>
#include <QString>
#include <QVector>
#include <QRegularExpression>
#include <regex>
using namespace std;


//choose next action
int chooseAction(){
    cout << endl;
    cout << "1. Add New Person" << endl;
    cout << "2. Add Phone to Person" << endl;
    cout << "3. Delete Person" << endl;
    cout << "4. Delete Phone from person" << endl;
    cout << "5. Find by name" << endl;
    cout << "6. Find by phone" << endl;
    cout << "7. Print all" << endl;
    cout << "Not number or 0. Exit" << endl;
    cout << "Input number: ";

    int i;
    cin>>i;
    while (i<0 || i>7){
        cout << "Incorrect number"<<endl;
        cout << "Input number: ";
        cin>>i;
    }
    return i;
}

//print only all names
void printNames(QMap<string, QVector<string>>& book){
    int c = 1;
    foreach (string key, book.keys())
    {
      QVector<string> value =book.value(key);
      cout <<c<<". "<< key<<endl;
      ++c;
    }
}

//print names and phones
void printAll(QMap<string, QVector<string>>& book){
    int c = 1;
    foreach (string key, book.keys())
    {
      QVector<string> value =book.value(key);

      cout <<c<<". "<< key<<endl;
      ++c;
      int i = 1;
      foreach (string v, value){
          cout << " "<<i<<". "<<v<<endl;
          ++i;
      }
    }


}

//add person
void addPerson(QMap<string, QVector<string>>& book){
    cout << "Add person"<<endl;
    cout << "Input name: ";
    string name;
    cin >> name;
    //check if name is new
    if (book.contains(name)){
        cout << "Name already exists"<<endl;
        return;
    }
    cout << "Input phone (+xxxxxxxxxxxx): ";
    string phone;
    cin >> phone;

    //check if phone format is correct
    QRegularExpression re("\\+\\d{12}");
    if (!re.match(phone.c_str()).hasMatch()){
        cout << "Incorrent phone"<<endl;
        return;
    }

    QVector<string> phones;
    phones.push_back(phone);

    book.insert(name, phones);
}

//add phone to person
void addPhoneToPerson(QMap<string, QVector<string>>& book){
    cout << "Add phone to person"<<endl;
    printAll(book);
    cout << "Input name: ";
    string i;
    cin>>i;
    //check if name exists
    if (!book.contains(i)){
        cout << "Name doesn`t exist"<<endl;
        return;
    }

    cout << "Input phone: ";
    string phone;
    cin >>phone;
    //check phone format
    QRegularExpression re("\\+\\d{12}");
    if (!re.match(phone.c_str()).hasMatch()){
        cout << "Incorrent phone"<<endl;
        return;
    }

    //check if phone already exists
    if(book[i].contains(phone)){
         cout << "Phone already exists"<<endl;
         return;
    }

    book[i].push_back(phone);
}

//delete person with all phones
void deletePerson(QMap<string, QVector<string>>& book){
    cout << "Delete person"<<endl;
    printNames(book);
    cout << "Input name: ";
    string i;
    cin >> i;
    //check if person exists
    if (!book.contains(i)){
        cout << "Name doesn`t exist"<<endl;
        return;
    }
    book.remove(i);
}

//delete phone from person
void deletePhoneFromPerson(QMap<string, QVector<string>>& book){
    cout << "Delete phone from person"<<endl;
    printAll(book);
    cout << "Input name: ";
    string i;
    cin>>i;
    //check if name exists
    if (!book.contains(i)){
        cout << "Name doesn`t exist"<<endl;
        return;
    }
    cout << "Input number of phone in list (1-"<<book[i].size()<<"): ";
    int phone;
    cin >>phone;

    //check if number correct
    if (phone < 1 || phone > book[i].size()){
        cout << "Incorrect number"<<endl;
        return;
    }

    book[i].remove(phone-1);
    //if it was last number, delete person
    if (book[i].isEmpty()) book.remove(i);
}

//find person by name or by it part
void findByName(QMap<string, QVector<string>>& book){
    cout << "Find by name"<<endl;
    cout << "Input name or part of it: ";
    string name;
    cin >>name;

    //check for full match
    cout << "Full match: "<<endl;
    if (book.contains(name)){
        cout << name<< endl;
        int i = 1;
        foreach (string v, book[name]){
            cout << " "<<i<<". "<<v<<endl;
            ++i;
        }
    }
    //check for partitial match
    cout << "Part match: "<<endl;
    foreach (string key, book.keys()){
        regex p(name);
        int i = 1;
        if (regex_search(key, p) && key!=name){
            cout << key<< endl;
            foreach (string v, book[key]){
                cout << " "<<i<<". "<<v<<endl;
                ++i;
            }
        }
    }
}

//find person by phone or by it part
void findByPhone(QMap<string, QVector<string>>& book){
    cout << "Find by phone"<<endl;
    cout << "Input phone or part of it: ";
    string phone;
    cin >>phone;

    QMap<string, QVector<string>> fullMatch;
    QMap<string, QVector<string>> partMatch;
    foreach (string key, book.keys()){
        //check this person for full match
        if (book[key].contains(phone)) fullMatch.insert(key, book[key]);
        else{
            //check this person for partitial match
            if (phone[0]=='+') phone = "\\+" + phone.substr(1);
            regex p(phone);
            foreach (string v, book[key]){
                if (regex_search(v, p)) {
                    partMatch.insert(key, book[key]);
                    break;
                }
            }
        }
    }
    cout << "Full match: "<<endl;
    printAll(fullMatch);
    cout << "Part match: "<<endl;
    printAll(partMatch);

}

int main(int argc, char *argv[])
{
    QMap<string, QVector<string>> book;
    QCoreApplication a(argc, argv);
    int ch = chooseAction();
    system("CLS");
    while (ch!=0){
        switch (ch) {
        case 1:
        addPerson(book);
        break;
        case 2:
        addPhoneToPerson(book);
        break;
        case 3:
        deletePerson(book);
        break;
        case 4:
        deletePhoneFromPerson(book);
        break;
        case 5:
        findByName(book);
        break;
        case 6:
        findByPhone(book);
        break;
        case 7:
        printAll(book);
        break;
        }
        ch = chooseAction();
        system("CLS");
    }
    return a.exec();
}
