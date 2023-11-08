/* Fatemah Elsewaky - U29797564
*  Noreen Abdelmaksoud - U14450950
* February 10, 2023

* This program is a representation of a virtual library of books that implements a singly linked list.
* Our program targets two types of users: employees of the virtual library and customers of the virtual library.
* The library provides distinct options for employees and customers. Employees have the option of viewing our collection of books, 
* adding to it, removing from it, and searching for a specific title in our current collection.
* Customers, on the other hand, have the option of browsing our current collection for a book to purchase and 
* searching for a specific book in our collection without viewing it. 
* To create our library’s collection of books, we created a text file that has the titles of one hundred books.

*/
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


template<typename L>                                 // Template for our classes "L"                
class LinkedList;                                   //class decleration

using namespace std;


template<typename L>                                // Template for our classes "L"
class Node {                                        // Node class declaration
  private:
    L book;
    Node<L> * next;                                 // next used for travling through the singly linked list
  public:
    Node(){};                                       // Constructor(s) for the Node
    Node(L b, Node *n) {
      book = b;
      next = n;
    }

  friend class LinkedList<L>;                       //creating friend class LinkedList to make sure it can access everything from the Node class
};

template<typename L>                                //Template for LinkedList class
class LinkedList {                                  // LinkedList class decleration
  private:
    Node<L> *head;
  public:
    LinkedList(){
      head = NULL;
  }
  //Function to search for the book in list 
  void searchList(L sbook)
  {
    Node<L>* curr = head;
    while(curr->next !=NULL)
    {
    if(curr->book == sbook){
      cout <<"The book: " <<curr->book <<" is currently available" <<endl;
      return;                                       // exit when it finds the book
    }
    curr = curr-> next;                            //to iterate through the list
    }

    cout << "book not found" << endl;             //print this if book is not found
    
  }
  //adds a book to the front of the list
  void addNode(L newbook) {
    Node<L> *newNode = new Node<L>(newbook, head);
      head = newNode;
      return;
  }
  //print the whole list
  void printList() {
    Node<L> *current = head;
    int lineNumber = 1;
    while (current != NULL) {
      cout << lineNumber << ". " << current->book << endl;
      current = current->next;
      lineNumber++;
    }

  }
  //remove a book from the list
  void remove(L rbook){
    Node<L> * curr = head;
    Node<L>* prev= NULL;
    
    for(; (curr != NULL) &&(curr->book.compare(rbook)!=0) ; prev= curr, curr = curr-> next)
    ;
    //if the book is not in the list
    if(curr == NULL){
      cout<<"Book is not found"<< endl;
      return;
    }
    //prints in case the book was found
    cout <<"The book: " <<curr->book <<" is being processed"<< endl;
    //In case the book was in the beginning
    if (prev== NULL)
      head= head->next;
    else{
        prev->next = curr -> next;
        curr->next=NULL;
    }
    
    delete curr;
    return;

  }
  //This function access the list of names of the books in the text file and adds each name as a node in the list
  void readFromFile(L filename) {
    stringstream ss;                      //used to convert the string returned by ss.str() to a const char*, 
    ss << filename;                       //That is required by the std::ifstream constructor.
    ifstream file(ss.str().c_str());

    //ifstream file(filename);
    if (!file.is_open()) {
      cerr << "Error opening file\n";
      return;
    }
    L line;
    while (getline(file, line)) {
      addNode(line); // add the line with the name of the book to the list
    }
    file.close();
  }
};

int main() {
  
  LinkedList<string> linkedList;
  linkedList.readFromFile("listofbooks.txt"); //calling readFromFile function to add the name of the books to the list

  

  string  book, ans, ans2;
  string again= "y";
  
  int user,option; 

  cout<<"Welcome to the our virtual Library :)"<< endl << endl;

  cout << "Are you one of our customers or employees?" << endl << endl;

  cout << "If you are an employee, enter 1. If you are a customer, enter 2: ";
  cin >> user;
  //Input validation
  while((user>2 || user< 1)){
    cout << "This is not a valid option :( Please try again" << endl;
    cout << "If you are an employee, enter 1. If you are a customer, enter 2: ";
    cin >> user;
  }
  //Employee case 
  if(user== 1){
    cout << "What would you like to do today?" << endl;
    cout<< "1.View our current collection\n2.Add a book\n3.Remove a book\n4.search for a book in our collection"<< endl;
    cout << "Please enter the number of your desired option: ";
    cin >> option;

    //Input validation
    while((option>4 || option< 1)){
      cout << "This is not a valid option :( Please try again" << endl;
      cout<< "1.View our current collection\n2.Add a book\n3.Remove a book\n4.search for a book in our collection"<< endl;
      cout << "Please enter the number of your desired option: ";
      cin >> option;
    }
    
    while (again=="y"){
      switch (option){
        case 1:
          linkedList.printList();
          break;

        case 2:
          cout << "Which book would you like to add?" << endl;
          cin >> book;
          linkedList.addNode(book);
          
          cout << "Would you like to see the updated list?(y/n)" << endl;
          cin >> ans;
          if(ans=="y")
            linkedList.printList();
          break;

        case 3:
          cout << "Which book would you like to remove?" << endl;
          cin >> book;
          linkedList.remove(book);
          
          cout << "Would you like to see the list?(y/n)" << endl;
          cin >> ans;
          if(ans=="y")
            linkedList.printList();
          break;

        case 4:
          cout << "Which book would you like to search for?" << endl;
          cin >> book;
          linkedList.searchList(book);
          break;
      
        default:
          cout<<"There was an error sorry about that!!"<< endl;
          break;
      }
      cout<<"Would you like to do anything else today? (y/n)"<< endl;
      cin>>again;
      if(again=="y"){
        cout << "What would you like to do?" << endl;
        cout<< "1.View our current collection\n2.Add a book\n3.Remove a book\n4.search for a book in our collection"<< endl;
        cout << "Please enter the number of your desired option: ";
        cin >> option;
      }
    }
    cout<<"Okay Goodbye!!";
  }
  //Customer case
  else{
    cout << "What would you like to do today?" << endl;
    cout<< "1.Browse our current collection\n2.Look for a specific book to purchase from our collection"<< endl;
    cout << "Please enter the number of your desired option: ";
    cin >> option;
    
    //Input validation
    while((option>2 || option< 1)){
      cout << "This is not a valid option :( Please try again" << endl;
      cout<< "1.Browse our current collection\n2.Look for a specific book to purchase from our collection"<< endl;
      cout << "Please enter the number of your desired option: ";
      cin >> option;
    }
    while (again=="y"){
      switch (option){
        case 1:
          linkedList.printList();
          cout<< "Did you find what you were looking for?(y/n)"<< endl;
          cin>> ans;
          if(ans=="y"){
            cout<<"Would you like to purchase it today?(y/n)"<< endl;
            cin>> ans2;
            if(ans2=="y"){
              cout<<"Enter the name of the book you want:"<< endl;
              cin>> book;
              linkedList.remove(book);
            }

          }
          else{
            cout<<"Sorry about that :( We will be having a new collection coming up soon\n"<< endl;
          }
          break;

        case 2:
          cout<<"Enter the name of the book you want:"<< endl;
          cin>> book;
          linkedList.remove(book);
          break;
      
        default:
          cout<<"There was an error sorry about that!!"<< endl;
          break;
      }
      cout<<"Would you like to do anything else today? (y/n)"<< endl;
      cin>>again;
      if(again=="y"){
        cout << "What would you like to do?" << endl;
        cout<< "1.Browse our current collection\n2.Look for a specific book to purchase from our collection"<< endl;
        cout << "Please enter the number of your desired option: ";
        cin >> option;
      }
    }
    cout<<"Thank you, See you again soon!!\n\nGood bye :)"<< endl;
  }

  return 0;
}