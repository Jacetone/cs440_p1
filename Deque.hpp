struct Deque_MyClass
{
    int size;
    int read;
    int length;
    int* arr; 
    char* type_name;

    void (*constructor)(Deque_MyClass &deq, void (*comparison)());
    size_t (*find_size)(Deque_MyClass &deq);
    bool (*empty)(Deque_MyClass &deq);
    void (*push_back)(Deque_MyClass &deq, int val);
    void (*push_front)(Deque_MyClass &deq, int val);
    int (*front_ele)(Deque_MyClass &deq);
    int (*back_ele)(Deque_MyClass &deq);
    int (*at)(Deque_MyClass &deq, int index);
    void (*pop_back)(Deque_MyClass &deq);
    void (*pop_front)(Deque_MyClass &deq);
    /*Still need to add sort, and begin and end iterator functions(new struct)*/

    /* Functions:
     * * Size
     * * Empty
     * * push_back
     * * push_front
     * * front
     * * back
     * * at
     * * pop_back
     * * pop_front
     * * sort
     * * begin
     * * end
     */
};
