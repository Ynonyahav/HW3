#ifndef EX3_QUEUE_H
#define EX3_QUEUE_H

#include <exception>

//---------------------------------------Queue class-------------------------------------------
template<class T>
class Queue
{
public:
    /**
     * c'tor of Queue class
     * build the queue with no cells
     * 
     * @return
     *      new queue with no cells.
     */
    Queue();

    /**
     *here we are dedclare that we dont want to use the default c'tor of copy and operator = 
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
     * get new parameter T and push it in the end of the queue
     *
     * @param T - object to place in the queue.
     *
     */
    void pushBack(const T object);

    /**
     * for const object
     * return the fist object in the queue
     *
     * @return &T - object to place in the queue.
     *
     */
    const T& front() const;

    /**
     * return the fist object in the queue
     * 
     * @return &T - object to place in the queue.
    */
    T& front();
    /**
     * remove and free the memory of the m_first objecct in the queue
     *
     * @return T - the m_first object in the queue.
     */
    void popFront();

    /**
     * @return 
     *      the size of queue
     */
    int size() const;

    //kind of declaration for iterator class
    class Iterator; 
    Iterator begin(); 
    Iterator end();

    //kind of declaration for ConstIterator class
    class ConstIterator; 
    ConstIterator begin() const; 
    ConstIterator end() const;

    class EmptyQueue {};

private:

    class Node;
    Node* m_first;
    Node* m_lest;
    int m_total_size;
};

//---------------------------------------Node class-------------------------------------------
template<class T>
class Queue<T>::Node {
public:

    Node(const T& object) : m_info(object), m_next(nullptr) {};                                    //the c'tor
    Node(const Node&)= default;                               //all others c'tors are default
    Node& operator=(const Node&)= default;
    ~Node()= default;

    void destroyNode(Node *node);

    T m_info;
    Node* m_next;

};

//------------------------------------iterator class + implementation-------------------------------------------
template<class T>
class Queue<T>::Iterator
{ 
public: 

    Iterator(typename Queue<T>::Node* node);     //c'tor of iterator
    ~Iterator()= default;                                     //default destroyer
    Iterator(const Iterator&) = default;                      //default copy c'tor
    Iterator& operator=(const Iterator&) = default;           //default operator= c'tor
    Iterator& operator++();
    T& operator*();
    bool operator!=(const Iterator& iterator);

    class InvalidOperation {};

private:

    Queue<T>::Node* current_node;
    
};
//--------------------------------ConstIterator class+ implementation-------------------------------------------
template<class T>
class Queue<T>::ConstIterator
{ 
public: 

    ConstIterator(const Queue<T>::Node* node);                           //c'tor of iterator
    ~ConstIterator()= default;                                          //default destroyer
    ConstIterator(const ConstIterator&) = default;                      //default copy c'tor
    ConstIterator& operator=(const ConstIterator&) = default;           //default operator= c'tor

    const T& operator*() const;                               //pointer to object with iterator
    ConstIterator& operator++();                                  //prefix iteratorbool
    bool operator!=(const ConstIterator& iterator) const;          //check != between 2 iterators


        class InvalidOperation {};

private:

    const Queue<T>::Node* current_node;
};
//-------------------------------begin and end ConstIterator implementation-------------------------------------------

//this function give the begin iterator
template<class T>
typename Queue<T>::ConstIterator Queue<T>::begin() const 
{
    return ConstIterator(m_first);
}

//this function give the end iterator
template<class T> 
typename Queue<T>::ConstIterator Queue<T>::end() const 
{ 
    return ConstIterator(nullptr); 
}

//--------------------------------begin and end iterator implementation-------------------------------------------

//this function give the begin iterator
template<class T>
typename Queue<T>::Iterator Queue<T>::begin() 
{
    return Iterator(m_first);
}

//this function give the end iterator
template<class T> 
typename Queue<T>::Iterator Queue<T>::end()
{ 
    return Iterator(nullptr); 
}
//----------------------------------Node destroyNode implementation-------------------------------------------

template<class T>
void Queue<T>::Node::destroyNode(Node *node)
{
    if(node->m_next != nullptr){
        destroyNode(node->m_next);
    }
    delete node;
}
//----------------------------------all the c'tor of queue-------------------------------------------

//main constructor
template<class T>
Queue<T>::Queue() :
    m_first(nullptr),
    m_lest(nullptr),
    m_total_size(0)
    {}

//destructor
template<class T>
Queue<T>::~Queue() {
    if(m_first != nullptr){
        m_first->destroyNode(m_first);
    }
}

//copy constuctor
template<class T>
Queue<T>::Queue(const Queue<T>& other)
{
    this->m_total_size = 0;
    this->m_first = nullptr;
    this->m_lest = nullptr;
    for(typename Queue<T>::ConstIterator it = other.begin(); it != other.end(); ++it){
    try{
        this->pushBack(*it);
    }
    catch(const std::bad_alloc& e){
        delete[] this;
        throw e;
        }
    }
}

//operator= constuctor
template<class T>
Queue<T>& Queue<T>::operator=(const Queue& queue)
{
    Queue<T> temp= queue;
    if(temp.m_size != queue.m_size){
        throw std::bad_alloc();
    }
    this->~Queue();
    this->m_first= queue.m_first;
    this->current_size= queue.current_size;
    return *this;
}

//---------------------------------all the aid functions of queue-------------------------------------------

//aid function #1
template<class T>
bool Queue<T>::isEmpty() const
{
    return m_first == nullptr;
}

//----------------------------------all the member functions of queue-------------------------------------------

template<class T>
void Queue<T>::pushBack(const T object)
{
    Node* newNode = new Node(object);
    m_total_size++;
    if (isEmpty()) {
        m_first = m_lest = newNode;
    } else {
        m_lest->m_next = newNode;
        m_lest = newNode;
    }
}

template<class T>                    
const T& Queue<T>::front() const
{
    if(isEmpty()){
        throw Queue<T>::EmptyQueue();
    }
    return m_first->m_info;
}

template<class T>
T& Queue<T>::front()
{
    if(isEmpty()){
        throw Queue<T>::EmptyQueue();
    }
    return m_first->m_info;
}

template<class T>
void Queue<T>::popFront()
{
    if(isEmpty()){
        throw EmptyQueue();
    }
    //if there is only one node
    if(m_first == m_lest){
        delete m_first;
        m_first = m_lest = nullptr;
        m_total_size--;
        return;
    }
    Node* temp_node = m_first;
    m_first = m_first->m_next;
    m_total_size--;
    delete temp_node;
}

template<class T>
int Queue<T>::size() const
{
    return m_total_size;
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
template<class T, typename Condition>
Queue<T> filter(const Queue<T>& queue,const Condition condition)
{
    Queue<T> new_queue;
    for(const T& it : queue){
        if(condition(it))
        {
            new_queue.pushBack(it);
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
template<class T, typename Condition>
void transform(Queue<T>& queue, const Condition condition)
{
    for(typename Queue<T>::Iterator it = queue.begin(); it != queue.end(); ++it){
        *it = condition(*it);
    }
}

/**
     * change all the object in queue by given function
     *
     * @param  queue- queue to change his objects.
     * @param  condition- The name of the function or function object that modify the objects
*/
template<class T, class T2, typename Condition>
T2 reduce(const Queue<T>& queue,T2 initial_value,const Condition condition)
{
    if(queue.isEmpty()){
        return initial_value;
    }
    for(typename Queue<T>::ConstIterator it = queue.begin(); it != queue.end(); ++it){
        initial_value=condition(initial_value, *it);
    }
    return initial_value;
}

//----------------------------------------all the iterator functions-------------------------------------------

template<class T>
Queue<T>::Iterator::Iterator(typename Queue<T>::Node* node) : current_node(node){}     //c'tor of iterator

template<class T>
typename Queue<T>::Iterator& Queue<T>::Iterator::operator++(){
    if(this->current_node == nullptr){
        throw Queue::Iterator::InvalidOperation();
    }
    this->current_node = this->current_node->m_next;
    return *this;
}

template<class T>
T& Queue<T>::Iterator::operator*()
{                               //pointer to object with iterator
    if(current_node == nullptr){
        throw Queue::Iterator::InvalidOperation();
    }
    return this->current_node->m_info;
}

template<class T>
bool Queue<T>::Iterator::operator!=(const Iterator& iterator)
{          //check != between 2 iterators
    return current_node!= iterator.current_node;
}

//----------------------------------------all the ConstIterator functions-------------------------------------------

template<class T>
Queue<T>::ConstIterator::ConstIterator(const typename Queue<T>::Node* node) : current_node(node){}   //c'tor of iterator

template<class T>
const T& Queue<T>::ConstIterator::operator*() const{                               //pointer to object with iterator
    if(current_node == nullptr){
        throw InvalidOperation();
    }
    return current_node->m_info;
}

template<class T>
typename Queue<T>::ConstIterator& Queue<T>::ConstIterator::operator++()
{                                   //prefix iterator
    if(this->current_node == nullptr)
    {
        throw InvalidOperation();
    }
    this->current_node = this->current_node->m_next;
    return *this;
}

template<class T>
bool Queue<T>::ConstIterator::operator!=(const ConstIterator& iterator) const
{          //check != between 2 iterators
    return (this->current_node != iterator.current_node);
}


#endif   //EX3_QUEUE_H
