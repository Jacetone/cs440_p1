struct MyClass {
    int id;
    char name[10];
};

struct Deque_MyClass_Iterator
{
	size_t pos;
	size_t deq_capacity;
	MyClass* deq_ptr;	

	void (*inc)(Deque_MyClass_Iterator *it);
	void (*dec)(Deque_MyClass_Iterator *it);
	MyClass& (*deref)(Deque_MyClass_Iterator *it);
};
struct Deque_MyClass
{
	size_t front_idx;
	size_t left;
	size_t right;
	size_t capacity;
	MyClass* arr;
	char* type_name;


	Deque_MyClass_Iterator (*begin)(Deque_MyClass *deq);
	Deque_MyClass_Iterator (*end)(Deque_MyClass *deq);

	bool(*compare)(const MyClass &T, const MyClass &U);
	bool (*isFull)(Deque_MyClass *deq);
	bool (*empty)(Deque_MyClass *deq);
	void (*resize)(Deque_MyClass *deq);
	void (*dtor)(Deque_MyClass *deq);
	void (*clear)(Deque_MyClass *deq);
	void (*push_back)(Deque_MyClass *deq, MyClass val);
	void (*push_front)(Deque_MyClass *deq, MyClass val);
	void (*pop_back)(Deque_MyClass *deq);
	void (*pop_front)(Deque_MyClass *deq);
	size_t (*size)(Deque_MyClass *deq);
	MyClass& (*front)(Deque_MyClass *deq);
	MyClass& (*back)(Deque_MyClass *deq);	
	MyClass& (*at)(Deque_MyClass *deq, size_t index);

};

void Deque_MyClass_Iterator_inc(Deque_MyClass_Iterator *it){
	it->pos++;
}
void Deque_MyClass_Iterator_dec(Deque_MyClass_Iterator *it){
	it->pos--;
}
MyClass& Deque_MyClass_deref(Deque_MyClass_Iterator *it){
	return it->deq_ptr[it->pos % it->deq_capacity];
}
Deque_MyClass_Iterator Deque_MyClass_begin(Deque_MyClass *deq){
	Deque_MyClass_Iterator it = {deq->left, 
				deq->capacity,
				deq->arr, 
				Deque_MyClass_Iterator_inc,
				Deque_MyClass_Iterator_dec,
				Deque_MyClass_deref};
	return it;
}
Deque_MyClass_Iterator Deque_MyClass_end(Deque_MyClass *deq){
	Deque_MyClass_Iterator it = {deq->right,
				deq->capacity, 
				deq->arr, 
				Deque_MyClass_Iterator_inc,
				Deque_MyClass_Iterator_dec,
				Deque_MyClass_deref};
	return it;
}

bool Deque_MyClass_equal(Deque_MyClass &deq1, Deque_MyClass &deq2){
	size_t deq_size = deq1.size(&deq1);
	if(deq_size == deq2.size(&deq2)){
		for(size_t i = 0; i < deq_size; i++){
			if((!deq1.compare(deq1.at(&deq1, i), deq2.at(&deq2, i)) && !deq1.compare(deq2.at(&deq2, i), deq1.at(&deq1, i))))continue;
			else return false;
		}
		return true;
	} else return false;
}
bool Deque_MyClass_Iterator_equal(const Deque_MyClass_Iterator &it1, const Deque_MyClass_Iterator &it2){
	return (it1.deq_ptr == it2.deq_ptr && it1.pos == it2.pos);
}

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
	return (deq->size(deq) == deq->capacity);
}
size_t Deque_MyClass_size(Deque_MyClass *deq){
	return deq->right - deq->left;
}
bool Deque_MyClass_empty(Deque_MyClass *deq){
    return !deq->size(deq);
}

void Deque_MyClass_push_back(Deque_MyClass *deq, MyClass val){
	if(deq->isFull(deq)){
		deq->resize(deq);
		deq->arr[deq->right] = val;
		deq->right = deq->right + 1;
	}
	else{
		deq->arr[deq->right] = val;
		deq->right = deq->right + 1;
	}
}

void Deque_MyClass_push_front(Deque_MyClass *deq, MyClass val){
	if(deq->isFull(deq)){
		deq->resize(deq);
		deq->arr[deq->capacity - 1] = val;
	}
	else if(deq->left == 0){
		deq->left += deq->capacity - 1;
		deq->right += deq->capacity;
		deq->arr[deq->left] = val;
	}
	else{
		deq->left--;
		deq->arr[deq->left] = val;
	}
}

MyClass& Deque_MyClass_front(Deque_MyClass *deq){	
	return deq->arr[deq->left%deq->capacity];
}

MyClass& Deque_MyClass_back(Deque_MyClass *deq){
	return deq->arr[((deq->right)-1)%deq->capacity];
}

MyClass& Deque_MyClass_at(Deque_MyClass *deq, size_t index){
	return deq->arr[(deq->left + index)%deq->capacity];
}

void Deque_MyClass_pop_back(Deque_MyClass *deq){
	deq->right--;
}

void Deque_MyClass_pop_front(Deque_MyClass *deq){
	deq->left++;
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
	deq->type_name = NULL;
	free((size_t*)deq->arr);

	deq->compare = NULL;
	deq->begin = NULL;
	deq->end = NULL;
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
	deq->type_name = NULL;
	deq->arr = (MyClass*)malloc(sizeof(MyClass)*deq->capacity);

	deq->isFull = Deque_MyClass_isFull;
	deq->compare = compare;
	deq->begin = Deque_MyClass_begin;
	deq->end = Deque_MyClass_end;
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










