struct MyClass {
    int id;
    char name[10];
};

struct Deque_MyClass
{
	size_t left;
	size_t right;
	size_t capacity;
	MyClass* arr; 
	char* type_name;

	void (*dtor)(Deque_MyClass *deq);
	void (*clear)(Deque_MyClass *deq);
	size_t (*size)(Deque_MyClass *deq);
	bool (*empty)(Deque_MyClass *deq);
	void (*push_back)(Deque_MyClass *deq, int val);
	void (*push_front)(Deque_MyClass *deq, int val);
	MyClass& (*front)(Deque_MyClass *deq);
	MyClass& (*back)(Deque_MyClass *deq);	
	MyClass& (*at)(Deque_MyClass *deq, int index);
	void (*pop_back)(Deque_MyClass *deq);
	void (*pop_front)(Deque_MyClass *deq);
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


void Deque_MyClass_dtor(Deque_MyClass *deq){
	free((size_t*)deq->arr);
	free((size_t*)deq->left);
	free((size_t*)deq->right);
}
void Deque_MyClass_clear(Deque_MyClass *deq){
	
}
size_t Deque_MyClass_size(Deque_MyClass *deq){
	return deq->capacity;
}
bool Deque_MyClass_empty(Deque_MyClass *deq){
	if((deq->right - deq->left) == 0) return true;
	return false;
}

void Deque_MyClass_push_back(Deque_MyClass *deq, int val){

}

void Deque_MyClass_push_front(Deque_MyClass *deq, int val){

}

MyClass& Deque_MyClass_front(Deque_MyClass *deq){	
	return deq->arr[0];
}

MyClass& Deque_MyClass_back(Deque_MyClass *deq){
	return deq->arr[0];
}

MyClass& Deque_MyClass_at(Deque_MyClass *deq, int index){
	return deq->arr[0];
}

void Deque_MyClass_pop_back(Deque_MyClass *deq){
	
}

void Deque_MyClass_pop_front(Deque_MyClass *deq){

}

void Deque_MyClass_ctor (Deque_MyClass *deq, bool(*compare)(const int &T, const int &U)){
	deq->left = 0;
	deq->right = 0;
	deq->capacity = 16;

	deq->size = Deque_MyClass_size;
	deq->empty = Deque_MyClass_empty;
	deq->push_back = Deque_MyClass_push_back;
	deq->push_front = Deque_MyClass_push_front;
	deq->front = Deque_MyClass_front;
	deq->back = Deque_MyClass_back;
	deq->at = Deque_MyClass_at;
	deq->pop_back = Deque_MyClass_pop_back;
	deq->pop_front = Deque_MyClass_pop_front;
}










