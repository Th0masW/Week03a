/***********************************************************************
* Header:
*    Queue
* Summary:
*    This class contains the notion of a container: a bucket to hold
*    data for the user. This is just a starting-point for more advanced
*    constainers such as the Queue, set, Queue, queue, deque, and map
*    which we will build later this semester.
*
*    This will contain the class definition of:
*        Queue            : Similar to Queue
*
* Author
*    Br. Helfrich
************************************************************************/

#ifndef Queue_H
#define Queue_H

#include <cassert>

/************************************************
 * Queue
 * A class that operates like a Queue
 ***********************************************/
template <class T>
class Queue
{
public:
   // default constructor : empty and kinda useless
   Queue() : numItems(0), vCapacity(0), data(NULL), locHead(0), locTail(0) {}

   // copy constructor : copy it
   Queue(const Queue & rhs) throw (const char *);

   // non-default constructor : pre-allocate
   Queue(int vCapacity) throw (const char *);

   // destructor : free everything
   ~Queue()        {if (vCapacity) delete [] data; }

   // is the container currently empty
   bool empty() const   { return (locHead - locTail) == 0; }

   // remove all the items from the container
   void clear()         { locHead = 0; locTail = 0;        }

   // how many items are currently in the container?
   int size() const     { return locTail - locHead;        }
   int capacity() const { return vCapacity;                }

   // return item at the front of the Queue
   T front() const throw (const char *)
   {
      if (numItems == 0)
      {
         throw "ERROR: Unable to reference the element from an empty Queue";
      }
      return data[locHead++];
   }

   // add an item to the Queue
   void push(const T &t) throw (const char *);

   // remove top item from the Queue
   void pop() throw (const char *);


   /************************************************
   * Container :: assignment
   * Assign a value to a container
   *************************************************/
   Queue <T> &operator = (const Queue<T> &rhs) throw (const char*)
   {
      try
      {
         this->data = new T[rhs.vCapacity];
         this->vCapacity = rhs.vCapacity;
         this->numItems = rhs.numItems;

         int x = locHead;
         for (int i = 0; i < rhs.size(); i++)
         {
            this->data[i] = rhs.data[x];
            x++;
         }
      }
      catch (std::bad_alloc)
      {
         throw "ERROR: Can not allocate buffer for new Queue";
      }
   return *this;
   }

   // overloaded []
   T &operator[] (int index) throw (const char*)
   {
      return data[index];
   }
   const T &operator[] (int index) const throw (const char*)
   {
      return data[index];
   }

private:
   T * data;          // dynamically allocated array of T
   int numItems = locTail - locHead; // how many items are currently in the Container?
   int vCapacity;     // how many items can I put on the Container before full?
   int locHead;       // the location of the head
   int locTail;       // the location of the tail
};


/*******************************************
 * CONTAINER :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
Queue <T> :: Queue(const Queue <T> & rhs) throw (const char *)
{
   assert(rhs.vCapacity >= 0);

   // do nothing if there is nothing to do
   if (rhs.vCapacity == 0)
   {
      vCapacity = numItems = 0;
      data = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[rhs.vCapacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }

   // copy over the capacity and size
   assert(rhs.numItems >= 0 && rhs.numItems <= rhs.vCapacity);
   vCapacity = rhs.vCapacity;
   numItems = rhs.numItems;

   // copy the items over one at a time using the assignment operator
   for (int i = 0; i < numItems; i++)
      data[i] = rhs.data[i];

   // the rest needs to be filled with the default value for T
   for (int i = numItems; i < vCapacity; i++)
      data[i] = T();
}

/**********************************************
 * CONTAINER : NON-DEFAULT CONSTRUCTOR
 * Preallocate the container to "capacity"
 **********************************************/
template <class T>
Queue <T> :: Queue(int vCapacity) throw (const char *)
{
   assert(vCapacity >= 0);
   // do nothing if there is nothing to do
   if (vCapacity == 0)
   {
      this->vCapacity = this->numItems = 0;
      this->data = NULL;
      return;
   }
   // attempt to allocate
   try
   {
      data = new T[vCapacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }
   // copy over the stuff
   this->vCapacity = vCapacity;
   this->numItems = 0;
   // initialize the container by calling the default constructor
   for (int i = 0; i < vCapacity; i++)
      data[i] = T();
}

/**************************************
*  Queue :: POP
*  remove the item on top of the Queue
***************************************/
template <class T>
void Queue<T> :: pop() throw (const char *)
{
   if (numItems == 0)
   {
      throw "ERROR: Unable to pop from an empty Queue";
   }
   locHead++;
}

/**************************************
*  Queue :: PUSH
*  add a new item to the top of the Queue
***************************************/
template <class T>
void Queue <T> ::push(const T &t) throw (const char *)
{
   if (vCapacity == 0)
   {
      vCapacity = 1;
      data = new T[vCapacity];
   }

   if (vCapacity - 1 == numItems)
   {
      this->vCapacity *= 2;

      try
      {
         T * temp = new(std::nothrow) T[vCapacity];

         for (int i = 0; i < numItems; i++)
         {
            temp[i] = data[i];
         }

         delete [] data;
         data = temp;
      }

      catch(std::bad_alloc)
      {
         throw "Error: Cannot allocate buffer";
      }
   }

   if (numItems < vCapacity)
   {
      data[numItems] = t;
      numItems++;
   }
}

#endif // Queue_H
