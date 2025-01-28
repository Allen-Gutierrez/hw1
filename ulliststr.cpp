#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

// WRITE YOUR CODE HERE

void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}


// My Work Below

void ULListStr::push_back(const std::string& val) 
{
// Checking for the list if its empty or if the linked list if full in the tail side
   if (tail_ == NULL || tail_->last == ARRSIZE) {
      // need a temporary new Item if the list is full
      Item* temp = new Item();

      if (tail_ != NULL) {
        tail_->next = temp; // moved the tail to the new item at the end 
        temp->prev = tail_; // sets the temp pointer
      }
      tail_ = temp; // Update the tail_ to the tem item 

      if (head_ == NULL) {
          head_ = tail_; // If the list was naturally empty to begin with, this would solve it 
      }
   }
 
  
  // Adding the new element to the linked list after the safty checks are in place
  tail_->val[tail_->last] = val;
  tail_->last++; // moves last forward by one
  size_++; // resizes the list 
}

void ULListStr::push_front(const std::string& val) 
{
// Checking for the list if its empty or if the linked list if the head item is filled
   if (head_ == NULL || head_->first == 0) {
      // need a temporary new Item if the list is full
      Item* temp = new Item();

      if (head_ != NULL) {
        head_->prev = temp; // links the head to the temp
      }
      temp->next = head_; // makes temp to the old head_
      head_ = temp; // moves head_ to the temp
      if (tail_ == NULL) {
          tail_ = head_; // If the list was naturally empty to begin with, this would solve it 
      }

      // Inintialize temp
      temp->first = ARRSIZE; // set first to end of array
      temp->last = ARRSIZE; // set last to end of array

   }
 
  
  // Adjusitng the first pointer to make room 
  head_->first--; // moves first back by one 
  head_->val[head_->first] = val; // places the new Val at the first position of the list
  size_++; // resizes the list 
}

void ULListStr::pop_back() 
{
// Base Case
    if( empty() ) {
      throw std::out_of_range("List is empty, cant work");
    }

    tail_->last--; // removes the elements from the tail

    size_--; // reduces the size_ by one
}

void ULListStr::pop_front()
{
//  Checking if the list is empty
     if( empty() ) {
      throw std::out_of_range("List is empty, cant work");
    }

    // tracking the current (now old) head
    Item* old = head_;
    
    if ( (head_->last - head_->first) > 1) {
      head_->first++; // moving the head up by one
    }
    else if (head_ == tail_) { // If only on value in the list
        delete old;
        head_ = NULL;
        tail_ = NULL;
    }
    else { // move head and delete old and set pointers
        head_ = head_->next;
        delete old;
        head_->prev = NULL;
    }

    size_--; // reduces the size_ by one
}

std::string const & ULListStr::back() const
{
    // Should always be pointing to the last/back varaiable
    return tail_->val[tail_->last-1];
}

std::string const & ULListStr::front() const
{
    // Should always be pointing to the first/front varaiable
    return head_->val[head_->first];
}

std::string* ULListStr::getValAtLoc(size_t loc) const
{
   // Checking if the list contains any elements
    if( empty() ) {
      throw std::out_of_range("List is empty, cant work");
    }

    // Checking if the location of the value is larger than the size of the list
    if ( loc >= size_) {
      throw std::out_of_range("Loc is outside of linked list size");
    }

    // starts a new Item to keep track through our main linked list, starting with where the head is.
    Item* temp = head_;

    // Going through the list to get the Value at location

    // Goes through a loop till it finds the loc 
    while (temp != NULL) {
        if ( loc >= (temp->last - temp->first) )
        {
          loc -= temp->last - temp->first;
          temp = temp->next; 
        }
        else {
            return &temp->val[temp->first + loc];
        }

    }

    // Only applies if out of range
    throw std::out_of_range("An unexpected error has occured");
}

