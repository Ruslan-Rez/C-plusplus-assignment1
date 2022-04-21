#include <iostream>
#include <utility>  // swap (may be useful)
#include <string>
template <typename T>
class DLL {
    struct Node {
        T     data;
        Node* next;
        Node* prev;
        
    };
    Node* sent;// sentinel
public:
DLL() : sent(new Node{T(),nullptr,nullptr}) {
    sent->next = sent->prev = sent;
}
bool empty() const{
    if(sent->prev == sent && sent->next==sent)
        return true;
    return false;        
}
void push_front(const T& t) const{
       Node* temp = new Node;
   temp -> data = t;
   if(empty()){
       sent->next = temp;
       sent->prev = temp;
       temp->next = sent;
       temp->prev = sent;
   }else{
       temp->next = sent->next;
       temp->next->prev = temp;
       temp->prev = sent;
       sent->next = temp;
   }
}
void push_back(const T& t) const{
   Node* tmp = new Node;
   tmp -> data = t;
   if(empty()){
       sent->next = tmp;
       sent->prev = tmp;
       tmp->next = sent;
       tmp->prev = sent;
   }else{
       tmp->prev = sent->prev;
       tmp->prev->next = tmp;
       tmp->next = sent;
       sent->prev = tmp;
   }
}

void print_fwd(std::ostream& str = std::cout) const{
    Node* q;
    q = sent->next;
    while(q!= sent){
        str<<q -> data <<" ";
        q = q-> next;
    }
    str<<std::endl;
}
void print_rev(std::ostream& str = std::cout) const{
    Node* r;
    r = sent->prev;
    while(r!= sent){
        str<<r -> data<<" ";
        r = r->prev;
    }
    str<<std::endl;
}
Node* find_first(const T& e) const{
        Node* first = NULL;
        Node* f = sent->next;
        int leng=0;
        while(f!=sent){
            leng++;
            f=f->next;
        }
        f=sent->next;
        for(int i=0; i<leng; i++){
            if(f->data==e){
                first=f;
                break;
            }
            else{
                f=f->next;
            }
        }
        return first;
    }
    Node* find_last(const T& e) const{
        Node* last = NULL;
        Node* l = sent->prev;
        int leng =0;
        while(l!=sent){
            leng++;
            l=l->prev;
        }
        l=sent->prev;
        for(int i=0; i<leng; i++){
            if(l->data==e){
                last=l;
                break;
            }
            else{
                l=l->prev;
            }
        }
        return last;
    }
    void insert_before(Node* b, const T& t) const{
        Node* x = new Node{t, b, b->prev};
        b->prev->next=x;
        b->prev=x;
    }
    void insert_after(Node* a, const T& t) const{
        Node* y = new Node{t, a->next, a};
        a->next->prev=y;
        a->next=y;
    }
void delete_node(const Node* d) const{
    d->prev->next=d->next;
    d->next->prev=d->prev;
    std::cout<<"del:"<<d->data<<"  ";
}
void reverse() const{
    Node* rev = new Node;
    while(sent!=NULL){
        rev = sent->next;
        sent->next = sent->prev;
        sent->prev = rev;
    }
    sent = rev;
}
void clear() const{
    int leng = 0;
    Node* y = sent-> next;
    while(y!=sent){
        leng++;
        y=y->next;
    }
    for(int i = 0; i<leng; i++){
        delete_node(y);
        y=y->next;
    }
}
~DLL(){
    clear();
    delete_node(sent);
}
};
int main () {
using std::cout; using std::endl; using std::string;
DLL<std::string>* listStr = new DLL<std::string>();
listStr->push_back("X");
listStr->push_back("E");
listStr->push_front("C");
listStr->push_front("X");
listStr->push_front("A");
cout << "List printed in both directions:" << endl;
listStr->print_fwd();
listStr->print_rev();
listStr->delete_node(listStr->find_first("X"));
listStr->delete_node(listStr->find_last("X"));
cout << "\nList after deleting X's:" << endl;
listStr->print_fwd();
listStr->insert_after(listStr->find_first("A"),"B");
listStr->insert_before(listStr->find_last("E"),"D");
cout << "List after inserting B and D:" << endl;
listStr->print_fwd();
//listStr->reverse();cout << "List after reversing:" << endl;listStr->print_fwd();
std::cout << "Is list empty? " << std::boolalpha
                          << listStr->empty() << std::endl;
std::cout << "Clearing the listt" << std::endl;
listStr->clear();
std::cout << "Adding one element (Z)" << std::endl;
listStr->push_front("Z");
std::cout << "Deleting the list" << std::endl;
delete listStr;
}