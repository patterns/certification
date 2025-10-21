// SListNode.h; Hsin-ih Tu; 2025.10.20;
// Declaration of list node

enum NodeType { HeadNode, ItemNode, ErrorNode };

// nodes can be three kinds head, item, error
template <typename T>
class SListNode {
   NodeType ntype_;
   union {
      bool hn_;
      T item_;
      short int error_;
   };

public:
   SListNode(NodeType, bool);
   SListNode(NodeType, short int);
   SListNode(T);
   SListNode *prev_;
   SListNode *next_;

   void initialize(T elem, SListNode *prev, SListNode *next);
   SListNode *clone(const int) const;
   SListNode *child() const;
   SListNode *parent() const;
   bool isHeadNode() const;
   bool elementMatch(T elem) const;
   T element() const;
};

////////////////////////////////////////////////
// Definition of list node

// ctor head node
template <typename T>
SListNode<T>::SListNode(NodeType nt, bool val) {
   ntype_ = HeadNode;
   hn_ = val;
}

// ctor error node
template <typename T>
SListNode<T>::SListNode(NodeType nt, short int val) {
   ntype_ = ErrorNode;
   error_ = val;
}

// ctor item node
template <typename T>
SListNode<T>::SListNode(T elem) {
   ntype_ = ItemNode;
   item_ = elem;
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
template <typename T>
SListNode<T> *SListNode<T>::clone(const int length) const {
   // make the head copy
   SListNode *dummy = new SListNode<T>(HeadNode, true);
   ////dummy->initialize(NODE_HEAD, nullptr, nullptr);
   dummy->ntype_ = HeadNode;
   dummy->next_ = nullptr;
   dummy->prev_ = nullptr;

   if (ntype_ != HeadNode) {  // expect to be called by header node
      return dummy;           // probably should throw exception here.....
   }

   switch (length) {
      case 0: {  // empty list
         break;
      }
      case 1: {  // single node
         SListNode<T> *tail = parent();
         if (tail->ntype_ == ItemNode) {
            SListNode<T> *newNode = new SListNode<T>(tail->item_);
            ////newNode->ntype_ = ItemNode;
            newNode->item_ = tail->item_;  // copy item
            newNode->next_ = dummy;        // circular link from tail
            newNode->prev_ = dummy;        // link child to head
            dummy->next_ = newNode;        // link head to child
            dummy->prev_ = newNode;        // circular link to tail
         }
         break;
      }
      default: {
         SListNode<T> *bookmark;

         // make the node copies starting with tail (reverse)
         SListNode<T> *visit = parent();
         SListNode<T> *newNode = new SListNode<T>(visit->item_);

         ////newNode->ntype_ = ItemNode;
         newNode->item_ = visit->item_;  // copy tail
         newNode->next_ = dummy;         // link tail to head
         newNode->prev_ = nullptr;       // placeholder for parent to tail
         dummy->prev_ = newNode;         // link head to tail

         bookmark = newNode;       // bookmark the child
         visit = visit->parent();  // position cursor to the parent of tail

         // non-tail nodes
         for (int i = 1; i < length; i++) {
            newNode = new SListNode<T>(visit->item_);
            bookmark->prev_ = newNode;  // link child to new parent
            ////newNode->ntype_ = ItemNode;
            newNode->item_ = visit->item_;  // copy item
            newNode->next_ = bookmark;      // link parent to child
            newNode->prev_ = nullptr;       // placeholder (for new node)
            bookmark = newNode;             // bookmark the child
            visit = visit->parent();        // decrement cursor
         }

         bookmark->prev_ = dummy;  // link zero node to head
         dummy->next_ = newNode;   // link head to zero node
      }
   }

   return dummy;
}

// check node type
template <typename T>
bool SListNode<T>::isHeadNode() const {
   return (ntype_ == HeadNode);
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
   /*   if (ntype_ != ItemNode) {
         return T();
      }
   */
   return item_;
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
