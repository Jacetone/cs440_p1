#define Deque_DEFINE(t)                                                                                                                 \
struct Deque_##t##_Iterator                                                                                                             \
{                                                                                                                                       \
	size_t pos;                                                                                                                         \
	size_t deq_capacity;                                                                                                                \
	t* deq_ptr;	                                                                                                                \
	void (*inc)(Deque_##t##_Iterator *it);                                                                                              \
	void (*dec)(Deque_##t##_Iterator *it);                                                                                              \
	t& (*deref)(Deque_##t##_Iterator *it);                                                                                        \
};                                                                                                                                      \
struct Deque_##t                                                                                                                        \
{                                                                                                                                       \
	size_t front_idx;                                                                                                                   \
	size_t left;                                                                                                                        \
	size_t right;                                                                                                                       \
	size_t capacity;                                                                                                                    \
	t* arr;                                                                                                                       \
	char type_name[6 + sizeof(#t)];                                                                                                                    \
	Deque_##t##_Iterator (*begin)(Deque_##t *deq);                                                                                      \
	Deque_##t##_Iterator (*end)(Deque_##t *deq);                                                                                        \
	bool(*compare)(const t &T, const t &U);                                                                                 \
	bool (*isFull)(Deque_##t *deq);                                                                                                     \
	bool (*empty)(Deque_##t *deq);                                                                                                      \
	void (*resize)(Deque_##t *deq);                                                                                                     \
	void (*dtor)(Deque_##t *deq);                                                                                                       \
	void (*clear)(Deque_##t *deq);                                                                                                      \
	void (*push_back)(Deque_##t *deq, t val);                                                                                     \
	void (*push_front)(Deque_##t *deq, t val);                                                                                    \
	void (*pop_back)(Deque_##t *deq);                                                                                                   \
	void (*pop_front)(Deque_##t *deq);                                                                                                  \
	size_t (*size)(Deque_##t *deq);                                                                                                     \
	t& (*front)(Deque_##t *deq);                                                                                                  \
	t& (*back)(Deque_##t *deq);	                                                                                                \
	t& (*at)(Deque_##t *deq, size_t index);                                                                                       \
};                                                                                                                                      \
void Deque_##t##_Iterator_inc(Deque_##t##_Iterator *it){                                                                                \
	it->pos++;                                                                                                                          \
}                                                                                                                                       \
void Deque_##t##_Iterator_dec(Deque_##t##_Iterator *it){                                                                                \
	it->pos--;                                                                                                                          \
}                                                                                                                                       \
t& Deque_##t##_deref(Deque_##t##_Iterator *it){                                                                                   \
	return it->deq_ptr[it->pos % it->deq_capacity];                                                                                     \
}                                                                                                                                       \
Deque_##t##_Iterator Deque_##t##_begin(Deque_##t *deq){                                                                                 \
	Deque_##t##_Iterator it = {deq->left,                                                                                               \
				deq->capacity,                                                                                                          \
				deq->arr,                                                                                                               \
				Deque_##t##_Iterator_inc,                                                                                               \
				Deque_##t##_Iterator_dec,                                                                                               \
				Deque_##t##_deref};                                                                                                     \
	return it;                                                                                                                          \
}                                                                                                                                       \
Deque_##t##_Iterator Deque_##t##_end(Deque_##t *deq){                                                                                   \
	Deque_##t##_Iterator it = {deq->right,                                                                                              \
				deq->capacity,                                                                                                          \
				deq->arr,                                                                                                               \
				Deque_##t##_Iterator_inc,                                                                                               \
				Deque_##t##_Iterator_dec,                                                                                               \
				Deque_##t##_deref};                                                                                                     \
	return it;                                                                                                                          \
}                                                                                                                                       \
bool Deque_##t##_equal(Deque_##t &deq1, Deque_##t &deq2){                                                                               \
	size_t deq_size = deq1.size(&deq1);                                                                                                 \
	if(deq_size == deq2.size(&deq2)){                                                                                                   \
		for(size_t i = 0; i < deq_size; i++){                                                                                           \
			if((!deq1.compare(deq1.at(&deq1, i), deq2.at(&deq2, i)) && !deq1.compare(deq2.at(&deq2, i), deq1.at(&deq1, i))))continue;   \
			else return false;                                                                                                          \
		}                                                                                                                               \
		return true;                                                                                                                    \
	} else return false;                                                                                                                \
}                                                                                                                                       \
bool Deque_##t##_Iterator_equal(const Deque_##t##_Iterator &it1, const Deque_##t##_Iterator &it2){                                      \
	return (it1.deq_ptr == it2.deq_ptr && it1.pos == it2.pos);                                                                          \
}                                                                                                                                       \
                                                                                                                                        \
void Deque_##t##_resize(Deque_##t *deq){                                                                                                \
	size_t temp = 2*deq->capacity;                                                                                                      \
	t* newList = (t*)malloc(sizeof(t)*temp);                                                                          \
	for(size_t i = 0; i < deq->capacity + 1; i++){                                                                                      \
		size_t index = (deq->left + i) % deq->capacity;                                                                                 \
		newList[i] = deq->arr[index];                                                                                                   \
	}                                                                                                                                   \
	free(deq->arr);                                                                                                                     \
	deq->arr = newList;                                                                                                                 \
	deq->capacity = temp;                                                                                                               \
}                                                                                                                                       \
bool Deque_##t##_isFull(Deque_##t *deq){                                                                                                \
	return (deq->size(deq) == deq->capacity);                                                                                           \
}                                                                                                                                       \
size_t Deque_##t##_size(Deque_##t *deq){                                                                                                \
	return deq->right - deq->left;                                                                                                      \
}                                                                                                                                       \
bool Deque_##t##_empty(Deque_##t *deq){                                                                                                 \
    return !deq->size(deq);                                                                                                             \
}                                                                                                                                       \
                                                                                                                                        \
void Deque_##t##_push_back(Deque_##t *deq, t val){                                                                                \
	if(deq->isFull(deq)){                                                                                                               \
		deq->resize(deq);                                                                                                               \
		deq->arr[deq->right] = val;                                                                                                     \
		deq->right = deq->right + 1;                                                                                                    \
	}                                                                                                                                   \
	else{                                                                                                                               \
		deq->arr[deq->right] = val;                                                                                                     \
		deq->right = deq->right + 1;                                                                                                    \
	}                                                                                                                                   \
}                                                                                                                                       \
                                                                                                                                        \
void Deque_##t##_push_front(Deque_##t *deq, t val){                                                                               \
	if(deq->isFull(deq)){                                                                                                               \
		deq->resize(deq);                                                                                                               \
		deq->arr[deq->capacity - 1] = val;                                                                                              \
	}                                                                                                                                   \
	else if(deq->left == 0){                                                                                                            \
		deq->left += deq->capacity - 1;                                                                                                 \
		deq->right += deq->capacity;                                                                                                    \
		deq->arr[deq->left] = val;                                                                                                      \
	}                                                                                                                                   \
	else{                                                                                                                               \
		deq->left--;                                                                                                                    \
		deq->arr[deq->left] = val;                                                                                                      \
	}                                                                                                                                   \
}                                                                                                                                       \
                                                                                                                                        \
t& Deque_##t##_front(Deque_##t *deq){	                                                                                            \
	return deq->arr[deq->left%deq->capacity];                                                                                           \
}                                                                                                                                       \
                                                                                                                                        \
t& Deque_##t##_back(Deque_##t *deq){                                                                                              \
	return deq->arr[((deq->right)-1)%deq->capacity];                                                                                    \
}                                                                                                                                       \
                                                                                                                                        \
t& Deque_##t##_at(Deque_##t *deq, size_t index){                                                                                  \
	return deq->arr[(deq->left + index)%deq->capacity];                                                                                 \
}                                                                                                                                       \
                                                                                                                                        \
void Deque_##t##_pop_back(Deque_##t *deq){                                                                                              \
	deq->right--;                                                                                                                       \
}                                                                                                                                       \
                                                                                                                                        \
void Deque_##t##_pop_front(Deque_##t *deq){                                                                                             \
	deq->left++;                                                                                                                        \
}                                                                                                                                       \
void Deque_##t##_clear(Deque_##t *deq){                                                                                                 \
	deq->left = 0;                                                                                                                      \
	deq->right = 0;                                                                                                                     \
	deq->capacity = 16;                                                                                                                 \
	free((size_t*)deq->arr);                                                                                                            \
	deq->arr = (t*)malloc(sizeof(t)*deq->capacity);                                                                         \
}                                                                                                                                       \
void Deque_##t##_dtor(Deque_##t *deq){                                                                                                  \
	deq->clear(deq);                                                                                                                    \
	deq->left = 0;                                                                                                                      \
	deq->right = 0;                                                                                                                     \
	deq->capacity = 0;                                                                                                                  \
	deq->front_idx = 0;                                                                                                                 \
	deq->type_name[0] = '\0';                                                                                                              \
	free((size_t*)deq->arr);                                                                                                            \
	                                                                                                                                    \
	deq->compare = NULL;                                                                                                                \
	deq->begin = NULL;                                                                                                                  \
	deq->end = NULL;                                                                                                                    \
	deq->resize = NULL;                                                                                                                 \
	deq->clear = NULL;                                                                                                                  \
	deq->size = NULL;                                                                                                                   \
	deq->empty = NULL;                                                                                                                  \
	deq->push_back = NULL;                                                                                                              \
	deq->push_front = NULL;                                                                                                             \
	deq->front = NULL;                                                                                                                  \
	deq->back = NULL;                                                                                                                   \
	deq->at = NULL;                                                                                                                     \
	deq->pop_back = NULL;                                                                                                               \
	deq->pop_front = NULL;                                                                                                              \
}                                                                                                                                       \
void Deque_##t##_ctor (Deque_##t *deq, bool(*compare)(const t &T, const t &U)){                                             \
	deq->front_idx = 0;                                                                                                                 \
	deq->left = 0;                                                                                                                      \
	deq->right = 0;                                                                                                                     \
	deq->capacity = 16;                                                                                                                 \
	strcpy(deq->type_name, "Deque_"#t);                                                                                                     \
	deq->arr = (t*)malloc(sizeof(t)*deq->capacity);                                                                         \
	                                                                                                                                    \
	deq->isFull = Deque_##t##_isFull;                                                                                                   \
	deq->compare = compare;                                                                                                             \
	deq->begin = Deque_##t##_begin;                                                                                                     \
	deq->end = Deque_##t##_end;                                                                                                         \
	deq->resize = Deque_##t##_resize;                                                                                                   \
	deq->dtor = Deque_##t##_dtor;                                                                                                       \
	deq->clear = Deque_##t##_clear;                                                                                                     \
	deq->size = Deque_##t##_size;                                                                                                       \
	deq->empty = Deque_##t##_empty;                                                                                                     \
	deq->push_back = Deque_##t##_push_back;                                                                                             \
	deq->push_front = Deque_##t##_push_front;                                                                                           \
	deq->front = Deque_##t##_front;                                                                                                     \
	deq->back = Deque_##t##_back;                                                                                                       \
	deq->at = Deque_##t##_at;                                                                                                           \
	deq->pop_back = Deque_##t##_pop_back;                                                                                               \
	deq->pop_front = Deque_##t##_pop_front;                                                                                             \
}                                                                                                                                       \










