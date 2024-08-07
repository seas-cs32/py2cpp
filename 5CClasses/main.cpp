#include <iostream>

////////////
// Class Elem (i.e., an element in a doubly linked list)
//
class Elem {
    public:
        int data;     // just some data held by this elem
        Elem *next;   // pointer to next elem in list
        Elem *prev;   // pointer to previous elem in list

        // constructors
        Elem() { data = 0; next = NULL; prev = NULL; }
        Elem(int d) {
            data = d; next = NULL; prev = NULL;
        }

        // no destructor since this elem has no dyn allocated data

        void print(bool with_newline = true);
};

// Member function (i.e., method) definitions for class Elem
void Elem::print(bool with_newline) {
    std::cout << "data = " << data;
    std::cout << " (" << prev << "," << next << ")";
    if (with_newline) {
        std::cout << std::endl;
    }
}

////////////
// Class DList (i.e., a doubly linked list of Elem objects)
//
class DList {
    public:
        Elem *head;   // head element in the list

        // constructors
        DList() { head = NULL; }
    
        // destructors
        ~DList();

        void insert_after(Elem *e, int data);

        void add(int index, int data);
        Elem* remove(int index);

        void print();
};

DList::~DList(void) {
    while (head) {
        // peel off head element
        Elem *e = head;
        head = head->next;

        // now delete previous head
        delete e;
    }
}

void DList::insert_after(Elem *e, int data) {
    // Check for bad usage
    if (e == NULL) {
        throw std::runtime_error("NULL element");
    }
    
    Elem *d = new Elem(data);

    // Slip d into list after e
    d->next = e->next;
    if (d->next) {
        d->next->prev = d;
    }
    d->prev = e;
    e->next = d;    
}

void DList::add(int index, int data) {
    // Check for bad usage
    if (index < 0) {
        throw std::range_error("DList negative index");
    }

    // If index >= length of list, add to end of list
    
    Elem *e = new Elem(data);

    if (head == NULL || index == 0) {
        // make e the new head
        e->next = head;
        if (head) {
            head->prev = e;
        }
        head = e;

    } else {
        // move p to insertion point while remembering prev p
        Elem *p = head->next;
        Elem *pp = head;
        int i = 1;
        while (p && i != index) {
            pp = p;
            p = p->next;
            i++;
        }
    
        // insert new elem before p (or at end if index > list length)
        e->next = p;
        e->prev = pp;
        if (p) {
            p->prev = e;
        } // else "inserting" at end of list
        if (pp) {
            pp->next = e;
        }
    }
}

Elem* DList::remove(int index) {
    // Check for bad usage
    if (index < 0) {
        throw std::range_error("DList negative index");
    } else if (head == NULL) {
        throw std::runtime_error("DList empty");
    }
    
    // move p to elem to remove
    Elem *p = head;
    int i = 0;
    while (p && i != index) {
        i++;
        p = p->next;
    }

    // remove elem at index i from list, if it exists
    if (p) {
        // remove p from list
        if (p->prev) p->prev->next = p->next;
        if (p->next) p->next->prev = p->prev;
    }

    // update head, if necessary
    if (p == head) {
        head = p->next;
    }

    return p;
}

void DList::print(void) {
    Elem *e = head;

    std::cout << "[" << std::endl;

    while (e) {
        std::cout << "  <";
        e->print(false);
        std::cout << ">, " << std::endl;
        e = e->next;
    }

    std::cout << "]" << std::endl;
}

////////////
// Class Stack
//
class Stack: public DList {
    public:
        // constructors
        Stack() { }

        void push(int data) {
            this->add(0, data);
        }

        int pop();

        bool is_empty() {
            return (head == NULL);
        }
};

int Stack::pop() {        
    Elem *e = this->remove(0);
    if (e) {
        int data = e->data;
        delete e;
        return data;
    } else {
        // We shouldn't get here, since an empty stack condition
        // is caught by DList::remove. The only way to get here
        // is if DList::remove tried to remove an elem at an
        // index greater than 0, but we hardcoded the 0 index!
        throw std::runtime_error("Unexpected NULL pop");
    }
}

////////////
// main
//
int main(void) {
    std::cout << "Welcome to writing C++ classes" << std::endl;

    // Create a (local) stack object
    Stack our_stack;
    std::cout << "Initial contents: ";
    our_stack.print();

    // Push a couple of numbers onto our stack
    our_stack.push(1);
    our_stack.push(2);
    our_stack.push(3);
    std::cout << "Pushed contents: ";
    our_stack.print();

    // Pop off the top element
    std::cout << "Popped value = " << our_stack.pop() << std::endl;
    std::cout << "Updated contents: ";
    our_stack.print();

    // Push a new number onto our stack
    our_stack.push(4);
    std::cout << "Push another: ";
    our_stack.print();

    // Other tests of DList methods add and remove (i.e.,
    // with non-zero indices)
    our_stack.add(1, 55);
    std::cout << "Add at index 1: ";
    our_stack.print();
    
    our_stack.add(3, 66);
    std::cout << "Add at index 3: ";
    our_stack.print();
    
    our_stack.add(5, 77);
    std::cout << "Add at index 5: ";
    our_stack.print();

    std::cout << "Removed value = " << our_stack.remove(1)->data << std::endl;
    std::cout << "Updated contents: ";
    our_stack.print();
    // leaked memory as can't delete removed elem

    std::cout << "Removed value = " << our_stack.remove(4)->data << std::endl;
    std::cout << "Updated contents: ";
    our_stack.print();
    // leaked memory as can't delete removed elem

    std::cout << "Removed value = " << our_stack.remove(4) << std::endl;
    std::cout << "Updated contents: ";
    our_stack.print();
    // Removed value should be NULL and contents unchanged, since
    // index was >= list length

    // Other tests of DList focused on insert_after
    our_stack.insert_after(our_stack.head, 888);
    std::cout << "Insert after index 0: ";
    our_stack.print();

    // Find last elem
    Elem *e = our_stack.head;
    while (e->next) e = e->next;
    our_stack.insert_after(e, 999);
    std::cout << "Insert after end: ";
    our_stack.print();

    // Pop entire list
    std::cout << "Popping everything ..." << std::endl;
    while (!our_stack.is_empty()) {
        std::cout << "Popped value = " << our_stack.pop() << std::endl;
        std::cout << "Updated contents: ";
        our_stack.print();
    }
    
    return 0;
}
