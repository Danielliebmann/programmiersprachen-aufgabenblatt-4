//AUFGABEN 4.1-4.12
#ifndef BUW_LIST_HPP 
#define BUW_LIST_HPP

#include <cstddef>
#include <utility>

template <typename T>
class List;

template <typename T>
struct ListNode 
{
  ListNode() : m_value {}, m_prev {nullptr}, m_next {nullptr} {}
  ListNode(T const& v, ListNode* prev, ListNode* next) : m_value{v}, m_prev{prev}, m_next{next} 
  {}
  T m_value; //Wert
  ListNode* m_prev; //Zeigt auf vorherigen Knoten
  ListNode* m_next; //Zeigt auf nächsten Knoten
};

template <typename T>
struct ListIterator 
{
  typedef ListIterator<T> Self;
  typedef T value_type; 
  typedef T* pointer; 
  typedef T& reference; 
  typedef ptrdiff_t difference_type;
  typedef std::forward_iterator_tag iterator_category;

  friend class List<T>;

  ListIterator(): 
  m_node {nullptr} {} //Der Default-Konstruktor
  ListIterator(ListNode<T>* n): 
  m_node {n} {} //Der Konstruktor

  //const: Wert verändert den anderen Wert nicht
  //Value at Operator: Gibt Value, die in einer bestimmten Adresse gespeichert ist aus
  reference operator * () const  
  {
    return (m_node-> m_value); //Wert der von m-node and m_value übergeben wird
  } 

  //Struct macht übergebenen Wert zu seinem Member (pointer operator -> ()const) 
  pointer operator -> () const 
  {
    return &(m_node -> m_value); //Übergabewert mit einem Zeiger
  } 

    //Inkrement Operator (auch i++)
  Self& operator ++ () 
  {
    if (m_node) 
    {
      m_node = m_node -> m_next; //m_node zeigt nun auf den nächsten Knoten
    }
    return *this; //returned m_node, dereferenced pointer(klon des Objekts), durch return wird die reference ausgegeben
  } 

    //Inkrement Operator (auch i++) 
  Self operator ++ (int) //integer Parameter um zwischen prä- und postfix zu unterscheiden
  { 
    Self temp = *this; //erzeut eine Kopie wie oben
    ++(*this); //++a = pre-inkrement, a++ = post-inkrement
    return temp;   //Kopie vor dem pre-Inkrement 
  } 
  
  //Vergleich: Zeiger Knoten Iterator und Zeiger Objekt x (== gleich)
  bool operator == (const Self& x) const 
  {
    return m_node == x.m_node;
  } 

  //Vergleich: Zeiger Knoten Iterator und Zeiger Objekt x (!= ungleich)
  bool operator != (const Self& x) const 
  {
    return m_node != x.m_node;
  } 

  Self next() const 
  {
    if (m_node)
      return ListIterator(m_node -> m_next);
    else
      return ListIterator(nullptr);
  }

  Self prev() const {
    if (m_node)
      return ListIterator(m_node -> m_prev);
    else
      return ListIterator(nullptr);
  }


private:
  //Knoten auf den der Iterator zeigt 
  ListNode<T>* m_node = nullptr;
};

template <typename T>
struct ListConstIterator {
  friend class List<T>;
public:
// not implemented yet
private:
  ListNode<T>* m_node = nullptr;
};

template <typename T>
class List {
//Der Default-Konstruktor
public: 
  typedef T value_type;
  typedef T* pointer;
  typedef const T* const_pointer;
  typedef T& reference; 
  typedef const T& const_reference;
  typedef ListIterator<T> iterator; 
  typedef ListConstIterator<T> const_iterator;

  friend class ListIterator<T>;
  friend class ListConstIterator<T>;

 //Default-Konstruktor
  List<T>(): 
  m_size {0}, 
  m_first {nullptr}, 
  m_last {nullptr} 
  {} 

  //Copy-Konstruktor
 List(List<T> const& listC): m_size {0}, m_first {nullptr}, m_last {nullptr} {
    for (iterator i = listC.begin(); i != listC.end(); ++i) {
      push_back(*i); // protip ;-)
    }
  }


 //Move-Konstruktor
  List(List&& listM): 
  m_size {listM.m_size}, 
  m_first {listM.m_first}, 
  m_last {listM.m_last} {
    //Listenelement von listmove werden entnommen
    listM.m_size = 0;
    listM.m_first = nullptr;
    listM.m_last = nullptr;
    //Somit ist listmove jetzt leer
  }

   //Zuordnung-Operator ordnet die Elemente einer Liste einer anderen zu.
  List<T>& operator = (List<T> list) { //Copy-Konstrukt by-value umgangen
    swap(list); //Swap-Element
    return *this; //Dekstruktor für List aufgerufen(beinhaltet alte *this)
  }

 //Vertauscht Inhalte der Listen mit *this
  void swap(List<T>& list) {
      std::swap(m_size, list.m_size);
      std::swap(m_first, list.m_first);
      std::swap(m_last, list.m_last);
  }

  //Freie Swap Funktion in der Liste
  friend void swap(List<T>& l1, List<T>& l2) {
    l1.swap(l2);
  }

  //Destruktor 
  ~List() {
    clear(); 
  //Löscht alle Elemente aus der Liste
  }
  //ist die Liste leer oder nicht? 
  bool empty() const {
    return m_size == 0;
  }

  //Größe der Liste?
  std::size_t size() const {
    return m_size;
  }

  //erhält erstes Element der Liste
  T const& front() const {
    return (*m_first).m_value;
  // m_first -> m_value
  }

  T& front() {
    return (*m_first).m_value; 
  // m_first -> m_value
  }

  //Neues erstes Element wird hinzugefügt
  void push_front(T const& a) {
    if (m_size == 0) {
      m_first = new ListNode<T>{a, nullptr, nullptr};
      m_last = m_first;
    }
   //Hier mit size 1
    else if (m_size >= 1) {
      m_first = new ListNode<T>{a, nullptr, m_first};
      m_first -> m_next -> m_prev = m_first;
    }

    ++m_size;
  }

  //Erstes Element der Liste wird entfernt
  void pop_front() {
    if (m_size == 1) {
      assert(m_first != nullptr);
      delete m_first;
      m_first = nullptr;
      m_size = 0;
    }

    else if (m_size > 1) {
      assert(m_first != nullptr);
      delete m_first;
      m_first = m_first -> m_next;
      --m_size;
    }
  }

  //Erhält letztes Element der Liste
  T const& last() const {
    return (*m_last).m_value; 
  // m_last -> m_value
  }

  T& last() {
    return (*m_last).m_value; 
  // m_last -> m_value
  }


    //Neues letztes Element wird der Liste hinzugefügt
  void push_back(T const& a) {
    if (m_size == 0) {
      m_last = new ListNode<T>{a, nullptr, nullptr};
      m_first = m_last;
    }

    else if (m_size >= 1) {
      m_last = new ListNode<T>{a, m_last, nullptr};
      m_last -> m_prev -> m_next = m_last;
    }

    ++m_size;
  }

  //letztes Element der Liste wird entfernt
  void pop_back() {
    if (m_size == 1) {
      assert(m_last != nullptr);
      delete m_last;
      m_last = nullptr;
      m_size = 0;
    }

    else if (m_size > 1) {
      assert(m_last != nullptr);
      delete m_last;
      m_last = m_last -> m_prev;
      --m_size;
    }
  }


//Alle Elemente der Liste werden entfernt 
  //Voraussetzung des Destruktors und der clear Funktion
  void clear() {
    while (m_size > 0) {
      pop_front();
    }
  }

  //Iterator, der auf m-first zeigt
  iterator begin() const {
  	return iterator {m_first};
  }

  //Iterator, der auf das Element hinter m_last zeigt
  iterator end() const {
  	return iterator {};
  }

  //Von Insert der gegebene Wert and bestimmte Position
  void insert(iterator position, T const& value) {
	
    if (position == begin()) 
    { 
     push_front(value);
    }

    else if (position == end()) 
    { 
     push_back(value);
    }

    else {
      ListNode <T>* insertNode = new ListNode<T> {value, position.prev().m_node, position.m_node};
	
      position.prev().m_node -> m_next = insertNode;
      position.m_node -> m_prev = insertNode;
      //Vergrößert Listengröße
      ++m_size; 
    }
  }

   //Kehrt die Sequenz der Liste, die mit der Funktion aufgerufen wird, um.
  void reverse() {
    List<T> tmp{*this}; //Kopie der Liste erstellt
    clear(); //löscht Liste
    for (iterator it = tmp.begin(); it != tmp.end(); ++it) {
      push_front(*it); //iteriert die List tmp und kehr Sequenz der anfänglichen Liste mit push_front um
  }
}


private:
  std::size_t m_size = 0;
  ListNode<T>* m_first = nullptr;
  ListNode<T>* m_last = nullptr;
};


//Sind beide Listen gleich?
template<typename T>
bool operator == (List<T> const& ASize, List<T> const& BSize) {
	bool result = true;
	//Gleiche Größe für gleiche Listen
	if (ASize.size() != BSize.size()) { 
	result = false;
	}

	else {
	 ListIterator<T> ASize_it = ASize.begin(); 
	 ListIterator<T> BSize_it = BSize.begin();
	//von Anfang bis Ende
	while (ASize_it != ASize.end() && BSize_it != BSize.end()) { 
//Element in Liste ASIZE ist gleich/ungleich dem Element der Liste BSIZE auf derselben Position
         if (*ASize_it != *BSize_it) 
	{ 
  	  result = false;
        break;
	}
//vergrößert Iteratoren zum nächsten Knoten
		++ASize_it;
		++BSize_it;
		}
	}

	return result;
}

//Sind die Listen unterschiedlich?
template<typename T>
bool operator != (List<T> const& ASize, List<T> const& BSize) {
	return !(ASize == BSize);
}
  
//Übergebene Liste genommen und reverse angewendet
template<typename T>
List<T> reverse (List<T> reverseList) {
  reverseList.reverse();
  return reverseList; 
//RETURN: Neue Liste mit umgekehrten Elementen
}

#endif // #define BUW_LIST_HPP