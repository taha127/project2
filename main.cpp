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
    ContactNode *title;

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
    bool operator==(const ContactsList& other);         // Equality operator
    ContactNode& operator[](int index);                 // Subscript operator

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
}
ContactsList::ContactsList(const ContactsList& other){
  head = 0;
  title = 0;
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
          }
/*void ContactsList::print(){
  ContactNode * temp = head;
  while(temp){
    std::cout << temp -> getName() << std::endl;
    std::cout << temp -> getEmail() << std::endl;
    std::cout << temp -> getPhone() << std::endl;
    std::cout<< "--------------------------------------------------\n";
    temp = temp -> getNext();
  }
  }*/
// main function to use all the methods
int main();
