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
  //...
  
  //...
};
ContactNode::ContactNode(const std::string& name, const std::string& email,
          const std::string& phone){
              this -> name = name;
              this -> email = email;
              this -> phone = phone;
          }
class ContactsList {
private:
    ContactNode* head;

public:
    // Constructors
    ContactsList();
    ContactsList(const ContactsList& other);

    // Destructor
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

// main function to use all the methods
int main();
