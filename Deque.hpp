struct MyClass {
    int id;
    char name[10];
};

struct Deque_MyClass
{
	size_t front_idx;
	size_t left;
	size_t right;
	size_t capacity;
	size_t deq_size;
	MyClass* arr; 
	char* type_name;

	void (*resize)(Deque_MyClass *deq);
	bool (*isFull)(Deque_MyClass *deq);
	void (*dtor)(Deque_MyClass *deq);
	void (*clear)(Deque_MyClass *deq);
	size_t (*size)(Deque_MyClass *deq);
	bool (*empty)(Deque_MyClass *deq);
	void (*push_back)(Deque_MyClass *deq, MyClass val);
	void (*push_front)(Deque_MyClass *deq, MyClass val);
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

void Deque_MyClass_resize(Deque_MyClass *deq){
	size_t temp = 2*deq->capacity;
	MyClass* newList = (MyClass*)malloc(sizeof(MyClass)*temp);
	for(size_t i = 0; i < deq->capacity + 1; i++){
		size_t index = (deq->left + i) % deq->capacity;
		newList[i] = deq->arr[index];
	}
	free(deq->arr);
	deq->arr = newList;
	deq->capacity = temp;
}
bool Deque_MyClass_isFull(Deque_MyClass *deq){
	if(deq->deq_size == deq->capacity) return true;
	return false;
}
size_t Deque_MyClass_size(Deque_MyClass *deq){
	return deq->deq_size;
}
bool Deque_MyClass_empty(Deque_MyClass *deq){
	if(deq->deq_size == 0) return true;
	return false;
}

void Deque_MyClass_push_back(Deque_MyClass *deq, MyClass val){
	if(deq->deq_size == deq->capacity){
		deq->resize(deq);
		deq->arr[deq->right] = val;
		deq->right = deq->right + 1;
	}
	else{
		deq->arr[deq->right] = val;
		deq->right = deq->right + 1;
	}
	deq->deq_size++;
}

void Deque_MyClass_push_front(Deque_MyClass *deq, MyClass val){
	if(deq->isFull(deq)){
		deq->resize(deq);
		deq->arr[deq->capacity - 1] = val;
	}
	else if(deq->left == 0){
		deq->left = deq->capacity - 1;
		deq->arr[deq->left] = val;
	}
	else{
		deq->left--;
		deq->arr[deq->left] = val;
	}
	deq->deq_size++;
}

MyClass& Deque_MyClass_front(Deque_MyClass *deq){	
	return deq->arr[deq->left];
}

MyClass& Deque_MyClass_back(Deque_MyClass *deq){
	if(deq->right == 0){
		return deq->arr[(deq->capacity)-1];
	}
	return deq->arr[(deq->right)-1];
}

MyClass& Deque_MyClass_at(Deque_MyClass *deq, int index){
	return deq->arr[index];
}

void Deque_MyClass_pop_back(Deque_MyClass *deq){
	deq->right--;
	deq->deq_size--;
}

void Deque_MyClass_pop_front(Deque_MyClass *deq){
	deq->left++;
	deq->deq_size--;
}
void Deque_MyClass_clear(Deque_MyClass *deq){
	deq->left = 0;
	deq->right = 0;
	deq->capacity = 16;
	free((size_t*)deq->arr);
	deq->arr = (MyClass*)malloc(sizeof(MyClass)*deq->capacity);
}
void Deque_MyClass_dtor(Deque_MyClass *deq){
	deq->clear(deq);
	deq->left = 0;
	deq->right = 0;
	deq->capacity = 0;
	deq->front_idx = 0;
	deq->deq_size = 0;
	deq->type_name = NULL;
	free((size_t*)deq->arr);
	
	deq->resize = NULL;
	deq->clear = NULL;
	deq->size = NULL;
	deq->empty = NULL;
	deq->push_back = NULL;
	deq->push_front = NULL;
	deq->front = NULL;
	deq->back = NULL;
	deq->at = NULL;
	deq->pop_back = NULL;
	deq->pop_front = NULL;
}
void Deque_MyClass_ctor (Deque_MyClass *deq, bool(*compare)(const MyClass &T, const MyClass &U)){
	deq->front_idx = 0;
	deq->left = 0;
	deq->right = 0;
	deq->capacity = 16;
	deq->deq_size = 0;
	deq->type_name = NULL;
	deq->arr = (MyClass*)malloc(sizeof(MyClass)*deq->capacity);

	deq->resize = Deque_MyClass_resize;
	deq->dtor = Deque_MyClass_dtor;
	deq->clear = Deque_MyClass_clear;
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










