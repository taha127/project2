#include <iostream>
#include <string>

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
    ContactNode* title;
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
    title = 0;
    size = 0;
}
ContactsList::ContactsList(const ContactsList& other){
    head = 0;
    title = 0;
    size = 0;
    ContactNode * temp = other.head;
    while(temp){
        push_back(temp -> getName(), temp -> getEmail(), temp -> getPhone());
        temp = temp -> getNext();
    } 
}
// Destructor for Contactslist
ContactsList::~ContactsList(){
    ContactNode* temp = head;
    while(head){
        head = head -> getNext();
        delete temp;
        temp = head;
    }
}
void ContactsList::push_front(const std::string& name, const std::string& email,
        const std::string& phone){
            ContactNode * temp = new ContactNode;
            temp -> setName(name);
            temp -> setEmail(email);
            temp -> setPhone(phone);
            temp -> setNext(head);
            head = temp;
            size++;
            if(title == 0) title = head;
        }
void ContactsList::push_back(const std::string& name, const std::string& email,
        const std::string& phone){
            if(head == 0){
                push_front(name, email, phone);
                return;
            }
            ContactNode* temp = new ContactNode;
            temp -> setName(name);
            temp -> setEmail(email);
            temp -> setPhone(phone);
            temp -> setNext(0);
            title -> setNext(temp);
            title = temp;
            size++;
        }
//operators
ContactsList& ContactsList::operator=(const ContactsList& other){
    this -> ~ContactsList();
    ContactNode * temp = other.head;
    while(temp){
        this -> push_back(temp -> getName(), temp -> getEmail(), temp -> getPhone());
        temp = temp -> getNext();
    }
    return *this;
}
ContactNode& ContactsList::operator[](int index){
    ContactNode * temp = head; 
    while(index){
        temp = temp -> getNext();
        index --;
    }
    return *temp;
}
bool ContactsList::operator==(const ContactsList& other){
    ContactNode * temp = other.head;
    ContactNode * self = this -> head;
    if(this->size != other.size) return false;
    bool answer = false;
    while(temp){
        while(self){
            if(temp->getName() == self->getName() && temp->getEmail() == self->getEmail() && temp->getPhone() == self->getPhone())
            {
                answer = true;
                break;
            }
            answer = false;
            self = self->getNext();
        }
        temp = temp->getNext();
    }
    return answer;
}
//methods
// Insertion method
void ContactsList::addContact(const std::string& name, const std::string& email,
        const std::string& phone){            
            for(int i = 0; i < size; i++){
                if(name.compare(this->operator[](i).getName()) < 1){
                    if(i > 0){
                        ContactNode *temp = new ContactNode;
                        temp->setName(name);
                        temp->setEmail(email);
                        temp->setPhone(phone);
                        temp->setNext(&this->operator[](i));
                        this->operator[](i - 1).setNext(temp);
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
void ContactsList::removeByName(const std::string& name){// Removes the contact with matching name
    for(int i = 0; i < size; i++){
        if(this->operator[](i).getName() == name){
            ContactNode * temp = &this->operator[](i);
            size --;
            if(i > 0){                 
                this->operator[](i - 1).setNext(temp->getNext());
                if(i == size - 1) title = &this->operator[](i - 1);
                delete temp;                
                return;
            }
            head = head->getNext();
            delete temp;
        }
    }
} 
// Search methods
ContactNode* ContactsList::searchByName(const std::string& name){// Returns the node with matching name
    for(int i = 0; i < size; i++){
        if(name == this->operator[](i).getName())
            return &this->operator[](i);
    }
    return 0;
}    
ContactNode* ContactsList::searchByEmail(const std::string& email){// Returns the node with matching email
    for(int i = 0; i < size; i++){
        if(email == this->operator[](i).getEmail())
            return &this->operator[](i);
    }
    return 0;   
}
ContactNode* ContactsList::searchByPhone(const std::string& phone){// Returns the node with matching phone
    for(int i = 0; i < size; i++){
        if(phone == this->operator[](i).getPhone())
            return &this->operator[](i);
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
        std::cout << "||name  ||  " << this->operator[](i).getName();
        for(int j = 0; j < 33 - this->operator[](i).getName().size(); j++) std::cout << " ";
        std::cout <<"||\n";
        std::cout << "||~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~||\n";
        std::cout << "||email ||  " << this->operator[](i).getEmail();
        for(int j = 0; j < 33 - this->operator[](i).getEmail().size(); j++) std::cout << " ";
        std::cout <<"||\n";
        std::cout << "||~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~||\n";
        std::cout << "||Phone ||  " << this->operator[](i).getPhone();
        for(int j = 0; j < 33 - this->operator[](i).getPhone().size(); j++) std::cout << " ";
        std::cout <<"||\n";
        std::cout << "||###########################################||\n";
    }
}


/*void ContactsList::print(){
    ContactNode * temp = head;
    std::cout << size << std::endl << std::endl;
    while(temp){
        std::cout << temp -> getName() << std::endl;
        std::cout << temp -> getEmail() << std::endl;
        std::cout << temp -> getPhone() << std::endl;
        std::cout<< "--------------------------------------------------\n";
        temp = temp -> getNext();
    }
}*/
// main function to use all the methods
int main(){
    ContactsList x, z;
    x.addContact("mohammad taha dehgani", "tahadehghani127@gmail.com", "35292764");
    x.addContact("ali", "email", "74573");
    x.addContact("hamed", "yaho", "35465");
    x.addContact("javad", "apple", "3155");
    x.addContact("ahmad", "ita", "4995");
    x.removeByName("taha");
    x.editContact("ali", "srosh", "0000");
    x.editContact("ahmad", "aiphone", "232323");
    x.editContact("taha", "iui", "38974");
    x.print();
}
