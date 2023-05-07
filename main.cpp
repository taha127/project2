#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
class ContactNode {
private:
    std::string name;
    std::string email;
    std::string phone;
    ContactNode* next;

public:
    ContactNode(const std::string& name, const std::string& email,
             const std::string& phone);
// getters and setters
    void setName(const std::string& newName){
        name = newName;
    }
    void setEmail(const std::string& newEmail){
        email = newEmail;
    }
    void setPhone(const std::string& newPhone){
        phone = newPhone;
    }
    void setNext(ContactNode* newNext){
        next = newNext;
    }
    std::string getName(){
        return name;
    }
    std::string getEmail(){
        return email;
    }
    std::string getPhone(){
        return phone;
    }
    ContactNode* getNext(){
        return next;
    }
};
//constructor function for ContactNode
ContactNode::ContactNode(const std::string& name = "", const std::string& email = "",
        const std::string& phone = ""){
            this -> name = name;
            this -> email = email;
            this -> phone = phone;
        }

class ContactsList {
private:
    ContactNode* head;
    ContactNode* tail;
    int size;
public:
    
    ContactsList();
    void push_back(const std::string& name, const std::string& email,
            const std::string& phone);
    void push_front(const std::string& name, const std::string& email,
            const std::string& phone);
    ContactsList(const ContactsList& other);
    ~ContactsList();

    // Operators
    ContactsList& operator=(const ContactsList& other); // Replace operator
    ContactsList operator+(const ContactsList& other);  // Concatenation operator
    ContactsList operator-(const ContactsList other);    // Subtraction operator
    ContactNode& operator[](int index);                 // Subscript operator
    bool operator==(const ContactsList& other);         // Equality operator

    // Insertion method
    void addContact(const std::string& name, const std::string& email,
            const std::string& phone);

    // Deletion methods
    void removeByName(const std::string& name); // Removes the contact with matching name

    // Search methods
    ContactNode* searchByName(const std::string& name);    // Returns the node with matching name 
    ContactNode* searchByEmail(const std::string& email);  // Returns the node with matching email
    ContactNode* searchByPhone(const std::string& phone);  // Returns the node with matching phone

    // Print methods
    void print();

    // Edit method
    void editContact(const std::string& name, const std::string& newEmail,
            const std::string& newPhone); // Edits the contact with matching name
};
// Constructors for Contactslist
ContactsList::ContactsList(){
    head = 0;
    tail = 0;
    size = 0;
}
ContactsList::ContactsList(const ContactsList& other){
    head = 0;
    tail = 0;
    size = 0;
    ContactNode * temp = other.head;
    while(temp){
        push_back(temp->getName(), temp->getEmail(), temp->getPhone());
        temp = temp->getNext();
    } 
}
// Destructor for Contactslist
ContactsList::~ContactsList(){
    ContactNode* temp = head;
    while(head){
        head = head->getNext();
        delete temp;
        temp = head;
    }
}
void ContactsList::push_front(const std::string& name, const std::string& email,
        const std::string& phone){
            ContactNode * temp = new ContactNode;
            temp->setName(name);
            temp->setEmail(email);
            temp->setPhone(phone);
            temp->setNext(head);
            head = temp;
            size++;
            if(tail == 0) tail = head;
        }
void ContactsList::push_back(const std::string& name, const std::string& email,
        const std::string& phone){
            if(head == 0){
                push_front(name, email, phone);
                return;
            }
            ContactNode* temp = new ContactNode;
            temp->setName(name);
            temp->setEmail(email);
            temp->setPhone(phone);
            temp->setNext(0);
            tail->setNext(temp);
            tail = temp;
            size++;
        }
//operators
ContactsList& ContactsList::operator=(const ContactsList& other){
    this->~ContactsList();
    ContactNode * temp = other.head;
    while(temp){
        push_back(temp->getName(), temp->getEmail(), temp->getPhone());
        temp = temp->getNext();
    }
    return *this;
}
ContactNode& ContactsList::operator[](int index){
    ContactNode * temp = head; 
    while(index){
        temp = temp->getNext();
        index --;
    }
    return *temp;
}
bool ContactsList::operator==(const ContactsList& other){
    ContactsList temp = other;
    ContactsList self = *this;
    if(size != other.size) return false;
    if((temp - self).size == 0) return true;
    return false;
}
ContactsList ContactsList::operator+(const ContactsList& other){
    ContactsList answer = other;
    for(int i = 0; i < size; i++){
        int j;
        for(j = 0; j < answer.size; j++){
            if((*this)[i].getName() == answer[j].getName() && (*this)[i].getEmail() == answer[j].getEmail() && 
                    (*this)[i].getPhone() == answer[j].getPhone()) break;
        }
        if(j == answer.size) 
            answer.addContact((*this)[i].getName(), (*this)[i].getEmail(), (*this)[i].getPhone());
    }
    return answer;
}
ContactsList ContactsList::operator-(const ContactsList other){
    ContactsList answer;
    ContactsList temp = other;
    for(int i = 0; i < size; i++){
        ContactNode *exist_name = temp.searchByName((*this)[i].getName()), 
        *exist_email = temp.searchByEmail((*this)[i].getEmail()),
        *exist_phone = temp.searchByPhone((*this)[i].getPhone());
        if(exist_name == 0 || exist_email == 0 || exist_phone == 0 || 
            (exist_name != exist_email && exist_email != exist_phone)){
                answer.addContact((*this)[i].getName(), (*this)[i].getEmail(), (*this)[i].getPhone());
            }
    }
    return answer;
}


//methods

// Insertion method
void ContactsList::addContact(const std::string& name, const std::string& email,
        const std::string& phone){            
            for(int i = 0; i < size; i++){
                if(name.compare((*this)[i].getName()) < 1){
                    if(i > 0){
                        ContactNode *temp = new ContactNode;
                        temp->setName(name);
                        temp->setEmail(email);
                        temp->setPhone(phone);
                        temp->setNext(&(*this)[i]);
                        (*this)[i - 1].setNext(temp);
                        size++;
                        return;
                    }
                    push_front(name, email, phone);
                    return;
                }              
            }
            push_back(name, email, phone);
        }
// Deletion methods
// Removes the contact with matching name
void ContactsList::removeByName(const std::string& name){
    std::vector<int>index;
    int target;
    for(int i = 0; i < size; i++)
        if((*this)[i].getName() == name)
            index.push_back(i);
    if(index.size() == 0){
        system("cls");
        std::cout << "No such name found!\n";
        return ;
    }
    if(index.size() == 1)
        target = 1;
        
    else{
        system("cls");
        for(int i = 0; i < index.size(); i++){
            std::cout << i + 1 << " >\n";
            std::cout << "||###########################################||\n";
            std::cout << "||name  ||  " << (*this)[index[i]].getName();
            for(int j = 0; j < 33 - (*this)[index[i]].getName().size(); j++) std::cout << " ";
            std::cout <<"||\n";
            std::cout << "||~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~||\n";
            std::cout << "||email ||  " << (*this)[index[i]].getEmail();
            for(int j = 0; j < 33 - (*this)[index[i]].getEmail().size(); j++) std::cout << " ";
            std::cout <<"||\n";
            std::cout << "||~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~||\n";
            std::cout << "||Phone ||  " << (*this)[index[i]].getPhone();
            for(int j = 0; j < 33 - (*this)[index[i]].getPhone().size(); j++) std::cout << " ";
            std::cout <<"||\n";
            std::cout << "||###########################################||\n";
        }
        while(true){
            std::cout << "which Contact do you want to delete?\n Enter its index : ";
            std::cin >> target;
            if(target < index.size() + 1 && target > 0) break;
            std::cout << "incorrect value!\n";
        }
    }
    ContactNode * temp = &(*this)[index[target - 1]];
    size --;
    if(index[target - 1] > 0){                 
        (*this)[index[target - 1] - 1].setNext(temp->getNext());
        if(index[target - 1] == size - 1) tail = &(*this)[index[target - 1] - 1];
        delete temp;                
        return;
    }
    head = head->getNext();
    delete temp;
} 
// Search methods
ContactNode* ContactsList::searchByName(const std::string& name){// Returns the node with matching name
    for(int i = 0; i < size; i++){
        if(name == (*this)[i].getName())
            return &(*this)[i];
    }
    return 0;
}    
ContactNode* ContactsList::searchByEmail(const std::string& email){// Returns the node with matching email
    for(int i = 0; i < size; i++){
        if(email == (*this)[i].getEmail())
            return &(*this)[i];
    }
    return 0;   
}
ContactNode* ContactsList::searchByPhone(const std::string& phone){// Returns the node with matching phone
    for(int i = 0; i < size; i++){
        if(phone == (*this)[i].getPhone())
            return &(*this)[i];
    }
    return 0;   
}
void ContactsList::editContact(const std::string& name, const std::string& newEmail,
            const std::string& newPhone){// Edits the contact with matching name
                if(searchByName(name)){
                    searchByName(name)->setEmail(newEmail);
                    searchByName(name)->setPhone(newPhone);
                }
            } 
void ContactsList::print(){
    std::cout << "||###########################################||\n";
    for(int i = 0; i < size; i++){
        std::cout << "||name  ||  " << (*this)[i].getName();
        for(int j = 0; j < 33 - (*this)[i].getName().size(); j++) std::cout << " ";
        std::cout <<"||\n";
        std::cout << "||~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~||\n";
        std::cout << "||email ||  " << (*this)[i].getEmail();
        for(int j = 0; j < 33 - (*this)[i].getEmail().size(); j++) std::cout << " ";
        std::cout <<"||\n";
        std::cout << "||~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~||\n";
        std::cout << "||Phone ||  " << (*this)[i].getPhone();
        for(int j = 0; j < 33 - (*this)[i].getPhone().size(); j++) std::cout << " ";
        std::cout <<"||\n";
        std::cout << "||###########################################||\n";
    }
}

int main(){
    ContactsList x, z, y;
    x.addContact("taha", "tahadehghani127@gmail.com", "35292764");
    x.addContact("ali", "email", "74573");
    x.addContact("ali", "gmail", "7498495");
    x.addContact("hamed", "yaho", "35465");
    x.addContact("hamed", "apple", "3155");
    x.addContact("ali", "you tube", "3784");

    z.addContact("ali", "email", "74573");
    z.addContact("javad", "apple", "3155");
    bool t = x == x;
    std::cout << t << std::endl;
    t = x == z;
    std::cout << t << std::endl;
    
}
