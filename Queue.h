#ifndef EX3_QUEUE_H
#define EX3_QUEUE_H 

//---------------------------------------Queue class-------------------------------------------
template<class T>
class Queue
{
public:
    /**
     * c'tor of Queue class
     * build the queue with one empty cell
     * 
     * @return
     *      new queue with one cell.
     */
    Queue();

    /**
     *here we are dedclare that we dont want to use the default c'tor of copy and - and 
     *and d'ctor and we will implicit them later
    */
    Queue(const Queue&);
    ~Queue();
    Queue& operator=(const Queue&);

    /**
     * this is aid function
     * return the mode of the queue
     *
     * @return bool - return true if the queue is empty else false
     *
     */
    bool isEmpty() const;

    /**
     * this is aid function
     * return the mode of the queue
     *
     * @return bool - return true if the queue is full else false
     *
     */
    bool isFull() const;

     /**
     * this is aid function
     * in case that the queue is full expend the queue with EXPEND_RATE cells
     */
    void expend();

    /**
     * get new parameter T and push it in the end of the queue
     *
     * @param T - object to place in the queue.
     *
     */
    void pushback(const T object);

    /**
     * return the fist object in the queue
     *
     * @return &T - object to place in the queue.
     *
     */
    T& front() const;

    /**
     * remove and free the memory of the first objecct in the queue
     *
     * @return T - the first object in the queue.
     */
    void popFront();

    /**
     * @return 
     *      the size of queue
     */
    int size() const;

    //kind of declaration for iterator class
    class Iterator; 
    Iterator begin() const; 
    Iterator end() const; 

    class EmptyQueue {};

private:

    T* info;
    int current_size;
    int max_size;

    static const int INTITIAL_SIZE=1;
    static const int EXPEND_RATE=5;
    static const int QUEUE_IS_EMPTY= 0;
};

//------------------------------------iterator class-------------------------------------------
template<class T>
class Queue<T>::Iterator
{ 
public: 

    const T& operator*() const;                               //pointer to object with iterator
    Iterator& operator++();                                   //prefix iterator 
    bool operator!=(const Iterator& iterator) const;          //
    Iterator(const Iterator&) = default;                      //copy c'tor
    Iterator& operator=(const Iterator&) = default;           // operator= c'tor
    class InvalidOperatio {};

private:

    const Queue<T>* queue; 
    int index; 
    Iterator(const Queue<T>* queue, int index);               //c'tor of iterator
    friend class Queue<T>; 
};

//------------------------------------iterator implementation-------------------------------------------

//c'tor of the iterator class
template<class T>
Queue<T>::Iterator::Iterator(const Queue<T>* queue, int index) :
    queue(queue),
    index(index)
{ }

template<class T> 
const T& Queue<T>::Iterator::operator*() const 
{ 
    assert(index >= 0 && index < queue->size()); 
    return queue->info[index]; 
} 

//prefix operator to iterator
template<class T> 
typename Queue<T>::Iterator& Queue<T>::Iterator::operator++()
{ 
    ++index;
    if(index)
    {
        throw InvalidOperatio();
    }
    return *this; 
}

template<class T> 
bool Queue<T>::Iterator::operator!=(const Iterator& it2) const
{ 
    return !(*this == it2); 
}

//--------------------------------begin and end iterator implementation-------------------------------------------

//this function give the begin iterator
template<class T>
typename Queue<T>::Iterator Queue<T>::begin() const 
{
    return Iterator(this, 0);
}

//this function give the end iterator
template<class T> 
typename Queue<T>::Iterator Queue<T>::end() const 
{ 
    return Iterator(this, size); 
}
//----------------------------------all the c'tor of queue-------------------------------------------

//main constructor
template<class T>
Queue<T>::Queue() :
    info(new T[INTITIAL_SIZE]),
    current_size(0),
    max_size(INTITIAL_SIZE)
    {}

//destructor
template<class T>
Queue<T>::~Queue() {
    delete[] info;
}

//copy constuctor
template<class T>
Queue<T>::Queue(const Queue& queue) :
    info(new T[max(queue.size(),INTITIAL_SIZE)]),
    current_size(queue.size()),
    max_size(max(queue.size(),INTITIAL_SIZE))
{
    for(int i=0; i<current_size ; i++){
        info[i]= queue.info[i];
    }
}

//operator= constuctor
template<class T>
Queue<T>& Queue<T>::operator=(const Queue& queue) 
{
  if (this == &queue)
    {
        return *this;
    }
    delete[] info;
    info = new T[max(queue.size(),INTITIAL_SIZE)];
    current_size = queue.size();
    max_size = max(queue.size(),INTITIAL_SIZE);
    for(int i=0; i< current_size ; i++)
    {
        info[i]= queue.info[i];
    }
return *this;
}
//---------------------------------all the aid functions of queue-------------------------------------------

//aid function #1
template<class T>
bool Queue<T>::isEmpty() const
{
    if(current_size==0){
        return true;
    }
    return false;
}

//aid function #2
template<class T>
bool Queue<T>::isFull() const
{
    if(current_size==max_size){
        return true;
    }
    return false;
}

//aid function #3
template<class T>
void Queue<T>::expend()
{
    int new_size= max_size+ EXPEND_RATE;
    T* new_info= new T[new_size];
    for(int i=0; i<current_size ;i++){
        new_info[i]= info[i];
    }
    delete info;
    info= new_info;
    max_size=new_size;
}

//----------------------------------all the member functions of queue-------------------------------------------
template<class T>
void Queue<T>::pushback(const T object)
{
    if(isFull()){
        expend();
    }
    info[current_size]= object;
    current_size++;
}

template<class T>                    
T& Queue<T>::front() const
{
    if(isEmpty()){
        throw EmptyQueue();                    //need add something
    }
    return info[0];
}

template<class T>
void Queue<T>::popFront()
{
    if(isEmpty()){
        throw EmptyQueue();                              //need add something
    }
    T* new_info=new T[max_size];           // notice- if size is 1 then weget new empty queue
    if(current_size>1)
    {
        for(int i=0; i<current_size; i++)
        {
            new_info[i]=info[i+1]
        }                   
    }
    delete[] info;
    info= new_info;
    current_size--;
}

template<class T>
int Queue<T>::size() const
{
    return current_size;
}
//----------------------------------------all the external functions-------------------------------------------

/**
     * change all the object in queue by given function
     *
     * @param  queue- queue to change his objects.
     * @param  condition- The name of the function or function object that set if the 
     *                    object will be in the new list
     * 
     * @return  new_queue -which is the filtered queue
     */
template<class T, typename condition>
Queue<T> filter(const Queue<T>& queue,const condition condition)
{
    Queue<T> new_queue;
    for(T& object : queue){
        if(condition(object)==true)
        {
            new_queue.pushback(object);
        }
    }
    return new_queue;
}

/**
     * change all the object in queue by given function
     *
     * @param  queue- queue to change his objects.
     * @param  condition- The name of the function or function object that modify the objects
     */
template<class T, typename condition>
void transform(const Queue<T>& queue,const condition condition)
{
    Queue<T> new_queue;
    for(T& object : queue){
        new_queue.pushback(condition(object));
    }
    return new_queue;
}

/**
     * change all the object in queue by given function
     *
     * @param  queue- queue to change his objects.
     * @param  condition- The name of the function or function object that modify the objects
     */
template<class T, typename T2, typename condition>
T2& reduce(const Queue<T>& queue,T2& initial_value,const condition condition)
{
    if(queue.isEmpty()){
        return initial_value;
    }
    for(T& object : queue){
        initial_value=condition(initial_value&, object);
    }
    return initial_value;
}

#endif

#endif /* EX3_QUEUE_H */ 