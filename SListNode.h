// SListNode.h; Hsin-ih Tu; 2025.10.20;
// Declaration of list node

#include "specials.h"

enum NodeType { HeadNode, ItemNode, ErrorNode, FreeNode };

// nodes can be three kinds head, item, error
template <typename T>
class SListNode {
   NodeType ntype_;
   union {
      bool hn_;
      T item_;
      short int error_;
   };
   int counter_;

public:
   SListNode(NodeType, bool);
   SListNode(NodeType, short int);
   SListNode(T);
   ~SListNode();
   SListNode *prev_;
   SListNode *next_;

   void initialize(T elem, SListNode *prev, SListNode *next);
   SListNode *clone() const;
   SListNode *child() const;
   SListNode *parent() const;
   bool isHeadNode() const;
   bool isItemNode() const;
   bool elementMatch(T elem) const;
   T element() const;
   int counterTotal() const;
   int counterPlus();
};

////////////////////////////////////////////////
// Definition of list node

// ctor head node
template <typename T>
SListNode<T>::SListNode(NodeType nt, bool val) {
   ntype_ = HeadNode;
   hn_ = val;
   counter_ = 0;
   next_ = nullptr;
   prev_ = nullptr;
}

// ctor error node
template <typename T>
SListNode<T>::SListNode(NodeType nt, short int val) {
   ntype_ = ErrorNode;
   error_ = val;
   counter_ = 0;
}

// ctor item node
template <typename T>
SListNode<T>::SListNode(T elem) {
   ntype_ = ItemNode;
   item_ = elem;
   counter_ = 0;
}

// destructor of node
template <typename T>
SListNode<T>::~SListNode() {
   if (ntype_ == FreeNode) {
      return;  // already in destroy stage
   }

   if (ntype_ != ItemNode) {
      return;  // no item data that requires freeing
   }

   ntype_ = FreeNode;  // mark node as being destroyed

   if (!std::is_fundamental<T>()) {
      ////std::string is = static_cast<std::string>(item_);
      std::string is = resolveString(item_);
      std::string empty;

      is.clear();      // reset string
      is.resize(0);    // shrink capacity
      is.swap(empty);  // trigger destroy of internal buffer
   }
}

// node initialization (see TICPP, Bruce Eckel)
template <typename T>
void SListNode<T>::initialize(T elem, SListNode<T> *prev, SListNode<T> *next) {
   ntype_ = ItemNode;
   item_ = elem;
   prev_ = prev;
   next_ = next;
}

// copy the nodes meant to be called by the header node
// Big assumption, only item nodes are copied.
template <typename T>
SListNode<T> *SListNode<T>::clone() const {
   // make the head copy
   SListNode<T> *dummy = new SListNode<T>(HeadNode, true);

   if (!isHeadNode()) {  // expect to be called by header node
      return dummy;      // probably should throw exception here.....
   }

   SListNode<T> *n0 = child();
   if (n0 == nullptr) {  // empty list
      return dummy;
   }

   SListNode<T> *n1 = n0->child();
   if (n1->ntype_ == HeadNode) {     // single node
      if (n0->ntype_ == ItemNode) {  // we only care about items
         SListNode<T> *newNode = new SListNode<T>(n0->item_);
         newNode->next_ = dummy;  // circular link from tail
         newNode->prev_ = dummy;  // link child to head
         dummy->next_ = newNode;  // link head to child
         dummy->prev_ = newNode;  // circular link to tail
      }
      return dummy;
   }

   SListNode<T> *bookmark = dummy;
   SListNode<T> *visit = n0;

   while (visit->ntype_ == ItemNode) {
      SListNode *newNode = new SListNode<T>(visit->item_);
      bookmark->next_ = newNode;  // link child to parent
      newNode->prev_ = bookmark;  // link parent to child
      newNode->next_ = nullptr;   // placeholder (for new node)
      bookmark = newNode;         // bookmark the child
      visit = visit->child();     // advance cursor
   }

   bookmark->next_ = dummy;  // link tail node to head
   dummy->prev_ = bookmark;  // link head to tail node

   return dummy;
}

// check node type
template <typename T>
bool SListNode<T>::isHeadNode() const {
   return (ntype_ == HeadNode);
}

// check node type is item
template <typename T>
bool SListNode<T>::isItemNode() const {
   return (ntype_ == ItemNode);
}

// check element val
template <typename T>
bool SListNode<T>::elementMatch(T elem) const {
   if (ntype_ != ItemNode) {
      return false;
   }
   return (item_ == elem);
}

// element val getter
template <typename T>
T SListNode<T>::element() const {
   if (ntype_ != ItemNode) {
      return T();
   }

   return item_;
}

// total items of same value inclusive
template <typename T>
int SListNode<T>::counterTotal() const {
   return counter_;
}

template <typename T>
int SListNode<T>::counterPlus() {
   return counter_ += 1;
}

// next pointer getter
template <typename T>
SListNode<T> *SListNode<T>::child() const {
   return next_;
}

// previous pointer getter
template <typename T>
SListNode<T> *SListNode<T>::parent() const {
   return prev_;
}
