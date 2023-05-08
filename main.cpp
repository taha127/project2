#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <map>
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
    size = 0;
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
        this->push_back(temp->getName(), temp->getEmail(), temp->getPhone());
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
    system("cls");
    //std::cin.ignore();
    std::cout << "Such a name is not in the contact list!\n";
    return 0;
}    
ContactNode* ContactsList::searchByEmail(const std::string& email){// Returns the node with matching email
    for(int i = 0; i < size; i++){
        if(email == (*this)[i].getEmail())
            return &(*this)[i];
    }
    system("cls");
    //std::cin.ignore();
    std::cout << "Such a email is not in the contact list!\n";
    return 0;   
}
ContactNode* ContactsList::searchByPhone(const std::string& phone){// Returns the node with matching phone
    for(int i = 0; i < size; i++){
        if(phone == (*this)[i].getPhone())
            return &(*this)[i];
    }
    system("cls");
    //std::cin.ignore();
    std::cout << "Such a phone is not in the contact list!\n";
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
    std::cout << "Press enter to continue.\n";
    getchar();
    system("cls");
}

void getCommandForList(ContactsList&, bool&, std::map<std::string, ContactsList>&);
void exist(bool&);

int main(){
    std::vector<ContactsList> booklet(1);
    std::map<std::string, ContactsList> nameList;
    bool continuation = true;
    while(continuation){
        system("cls");
        std::string order1;
        std::cout << "Main menu guide :\n"; 
        std::cout <<"Creat a new list of contacts : cl  #  Select contact list : sc  #  exist : ex\n";
        std::cin >> order1;
        if(order1 == "cl"){
            ContactsList new_list;
            std::string name, order2;
            std::cin.ignore();
            std::cout << "Enter the name of the created contact list : ";
            std::getline(std::cin, name);
            system("cls");
            getCommandForList(new_list, continuation, nameList);
            nameList[name] = new_list;
        }
        else if(order1 == "sc"){
            std::string name_desired;
            std::cout << "Enter the name of the desired contact list : ";
            std::cin.ignore();
            std::getline(std::cin, name_desired);
            auto it = nameList.find(name_desired);
            if(it != nameList.end()){
                getCommandForList(it->second, continuation, nameList);
            }
            else{
                std::cout << "Name not found\n";
            }
        }
        else if(order1 == "ex")
            exist(continuation);
        else std::cout << "The desired command was not found\n";
    }
        
        
}
std::string get_str(const char type){
    std::string str;
    if(type == 'n')
        str = "name : ";
    else if(type == 'e')
        str = "email : ";
    else str = "phone : ";
    std::cout << "enter " << str;
    std::cin >> str;
    return str;
}
void exist(bool& continuation){
    system("cls");
     std::cout << "Are you sure you want to exit?\n YES : y\n NO : n\n";
    switch (getchar())
    {
        case 'y':
        continuation = false;
            system("cls");
            return;
        case 'n':
            return;
        default:
            system("cls");
            std::cout << "The desired command was not found\n";
            exist(continuation);
            break;
    }    
}

bool split_detection(ContactsList& list2, std::string& order, std::map<std::string, ContactsList>& booklet, 
    const std::string type){
    auto index = order.find(type);
    order.erase(index, 1);
    while(true){
        if(order[0] == ' '){
            index = order.find(" ");
            order.erase(index, type.size());
        }
        else  break;
    }
    auto itr = booklet.find(order);
    if(itr != booklet.end()){
        list2 = itr->second;
        return true;
    }
    std::cout << "No contact list was found with this name \n";
    return false;
}

void preformOperation(ContactsList& list1, std::string& order, std::map<std::string, ContactsList>& booklet, 
    const std::string type){
    ContactsList list2;
    if(split_detection(list2, order, booklet, type)){
        ContactsList temp;
        if(type == "+") temp = list1 + list2;
        else temp = list1 - list2;
        std::cout << "Do you want to create a new contact list with this operator or just want to print it?"
        <<"\n create : c\n print : p\n";
        std::string name;
        switch (getchar())
        {
            case 'c':
                std::cout << "enter name of new contact list : ";
                std::cin.ignore();
                std::getline(std::cin, name);
                booklet[name] = temp;
                break;
            case 'p':
                (temp).print();
                break;
            default:
                std::cout << "The desired command was not found\n";
                break;
        }
    }
}

void getCommandForList(ContactsList& list, bool& continuation, std::map<std::string, ContactsList>& booklet)
{
    std::string order2;
    std::cout << "Guide :\n";
    std::cout << "Add a contact : ac  #  Delete a contact : dc  #  Edit a contact : ec  #  "
    << "Search for a contact by name : sn\nSearch for a contact by email : se  #  "
    <<"Search for a contact by phone : sp  #  Print contact list : pc\nBack to the main menu : bm"
    <<"  #  Exist : ex  #  operator (+) : + \"list2\"  #   operator (-) : - \"list2\"\n"
    <<"operator (=) : = \"list2\"  #  operator(==) : = \"list2\"  #  operator ([]) : [unsigned int]\n";
    std::getline(std::cin, order2);
    system("cls");
    if(order2 == "ac"){
        std::string name = get_str('n'), email = get_str('e'), phone = get_str('p'); 
        list.addContact(name, email, phone);
        getCommandForList(list, continuation, booklet);
    }
    else if(order2 == "dc"){
        list.removeByName(get_str('n'));
        getCommandForList(list, continuation, booklet);
    }  
    else if(order2 == "ec"){
        std::string name = get_str('n'), email = get_str('e'), phone = get_str('p'); 
        list.editContact(name, email, phone);
        getCommandForList(list, continuation, booklet);
    }
    else if(order2 == "sn"){
        ContactNode *temp;
        ContactsList aim;
        temp = list.searchByName(get_str('n'));
        if(temp){
            aim.addContact(temp->getName(), temp->getEmail(), temp->getPhone());
            aim.print();
        }
        getCommandForList(list, continuation, booklet);
    }
    else if(order2 == "se"){
        ContactNode *temp;
        ContactsList aim;
        temp = list.searchByEmail(get_str('e'));
        if(temp){
            aim.addContact(temp->getName(), temp->getEmail(), temp->getPhone());
            aim.print();
        }
        getCommandForList(list, continuation, booklet);
    }
    else if(order2 == "sp"){
        ContactNode *temp;
        ContactsList aim;
        temp = list.searchByPhone(get_str('p'));
        if(temp){
            aim.addContact(temp->getName(), temp->getEmail(), temp->getPhone());
            aim.print();
        }
        getCommandForList(list, continuation, booklet);
    }
    else if(order2[0] == '+'){
        preformOperation(list, order2, booklet, "+");
        getCommandForList(list, continuation, booklet);
    }  
    else if(order2[0] == '-'){
        preformOperation(list, order2, booklet, "-");
        getCommandForList(list, continuation, booklet);
    }
    else if(order2[0] == '=' && order2[1] == '='){
        ContactsList list2;
        bool answer;
        system("cls");
        if(split_detection(list2, order2, booklet, "==")){
            answer = list == list2;
            if(answer) std::cout << "Yes, they are equal\n";
            else std::cout << "No, they are not equal\n";
        }
        else std::cout << "No contact list was found with this name \n";
        getCommandForList(list, continuation, booklet);
    }
    else if(order2[0] == '='){
        ContactsList list2;
        if(split_detection(list2, order2, booklet, "=")){
            list = list2;
        }
        else std::cout << "No contact list was found with this name \n";
        getCommandForList(list, continuation, booklet);
    }
    else if(order2[0] == '['){
        ContactsList temp;
        int index = (int)order2[1] - 49;
        temp.addContact(list[index].getName(), list[index].getEmail(), list[index].getPhone());
        temp.print();
        getCommandForList(list, continuation, booklet);
    }
    else if(order2 == "pc"){
        list.print();
        getCommandForList(list, continuation, booklet);
    }
    else if(order2 == "bm")
        return;
    else if(order2 == "ex"){
        exist(continuation);
        return ;
    }
    else{
        std::cout << "The desired command was not found\n";
        getCommandForList(list, continuation, booklet);
    }
}
