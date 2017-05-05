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
   Queue() : vCapacity(0), data(NULL), countIn(0), countOut(0) {}

   // copy constructor : copy it
   Queue(const Queue & rhs) throw (const char *);

   // non-default constructor : pre-allocate
   Queue(int vCapacity) throw (const char *);

   // destructor : free everything
   ~Queue()        {if (vCapacity) delete [] data; }

   // is the container currently empty
   bool empty() const   { return (countIn - countOut) == 0; }

   // remove all the items from the container
   void clear()         { countIn = 0; countOut = 0;        }

   // how many items are currently in the container?
   int size() const     { return countIn - countOut;        }
   int capacity() const { return vCapacity;                }

   // get the item from the front of the Queue
   T & front() throw(const char *);

   // add an item to the Queue
   void push(const T &t) throw (const char *);

   //resize the Queue
   void resize(int newSize) throw (const char *);

   // remove top item from the Queue
   void pop() throw (const char *);

   // overloaded assignment operator
   Queue <T> &operator = (const Queue<T> &rhs) throw (const char*)
   {
      try
      {
         this->data = new T[rhs.vCapacity];
         this->vCapacity = rhs.vCapacity;
         this->countIn = 0;
         this->countOut = 0;

         int x = rhs.locHead();
         for (int i = 0; i < rhs.size(); i++)
         {
            if (x == (rhs.vCapacity + 1))
            {
               x = 0;
            }
            this->data[i] = rhs.data[x];
            this->countIn++;
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
   int numItems() const {return countIn - countOut;}      // how many items are currently in the Container?
   int locHead() const
    {
      if(vCapacity == 0)
      {
         return 0;
      }
      else
      {
         return (countIn -1) % vCapacity;
      }
   } // the location of the head

   int locTail() const
   {
      if (vCapacity == 0)
      {
         return 0;
      }
      else
      {
         return countOut % vCapacity;
      }
   }     // the location of the tail

   int vCapacity;     // how many items can I put on the Container before full?
   int countIn;       // the number of items added to queue
   int countOut;      // the number of items removed from queue
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
      vCapacity = 0;
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

// copy over the capacity, size and counts (for head and tail locations)
   countOut = rhs.countOut;
   countIn = rhs.countIn;
   assert(rhs.numItems() >= 0 && rhs.numItems() <= rhs.vCapacity);
   vCapacity = rhs.vCapacity;
//   numItems() = rhs.numItems();

   // copy the items over one at a time using the assignment operator
   for (int i = 0; i < vCapacity; i++)
      data[i] = rhs.data[i];

/*
   // the rest needs to be filled with the default value for T
   for (int i = numItems(); i < vCapacity; i++)
      data[i] = T();
      */
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
      this->vCapacity = 0;
      this->data = NULL;
      this->countIn = 0;
      this->countOut = 0;
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
   this->countIn = 0;
   this->countOut = 0;
   // initialize the container by calling the default constructor
   for (int i = 0; i < vCapacity; i++)
      data[i] = T();
}

/************************************************
* Container :: assignment
* Assign a value to a container
*************************************************
template <class T>
<T> Queue <T>::&operator = (const Queue<T> &rhs) throw (const char*)
{
   try
   {
      this->data = new T[rhs.vCapacity];
      this->vCapacity = rhs.vCapacity;
      this->countIn = 0;
      this->countOut = 0;

      int x = rhs.locHead();
      for (int i = 0; i < rhs.size(); i++)
      {
         if (x == rhs.vCapacity)
         {
            x = 0;
         }
         this->data[i] = rhs.data[x];
         this->countIn++;
         x++;
      }
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Can not allocate buffer for new Queue";
   }
return *this;
}
*/

/**************************************
*  Queue :: POP
*  remove the item on top of the Queue
***************************************/
template <class T>
void Queue<T> :: pop() throw (const char *)
{
   if (numItems() == 0)
   {
      throw "ERROR: Unable to pop from an empty Queue";
   }
   countOut++;
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

   if (numItems() == vCapacity - 1) // was vCapacity - 1
   {
      resize(vCapacity * 2);
//      this->vCapacity *= 2;
      try
      {
         T * temp = new(std::nothrow) T[vCapacity];
         int x = locHead();
         countIn = 0;
         countOut = 0;

         for (int i = 0; i < numItems(); i++)
         {
            if (x == (vCapacity + 1))
            {
               x = 0;
            }
            temp[i] = data[x];
            x++;
            countIn++;
         }

         delete [] data;
         data = temp;
      }

      catch(std::bad_alloc)
      {
         throw "Error: Cannot allocate buffer";
      }
   }

   if (numItems() < vCapacity)
   {
      data[locTail()] = t;
      countIn++;
   }
}

/**************************************
* QUEUE :: FRONT
* return the item at the front of the queue
***************************************/
template <class T>
T & Queue <T> :: front() throw (const char *)
{
   if (this->empty())
   {
      throw "ERROR: attempting to access an item in an empty queue";
   }
   else
   {
      return this->data[locHead()];
   }
};

/**************************************
* QUEUE :: RESIZE
* rewrite the Queue into a Queue of a larger size
***************************************/
template <class T>
void Queue <T> :: resize(int newSize) throw (const char *)
{
   try
   {
      vCapacity = newSize;
      T * temp = new(std::nothrow) T[vCapacity];

      for (int i = 0; i < numItems(); i++)
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


#endif // Queue_H
