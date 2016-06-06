//AUFGABEN 4.1-4.12
#ifndef BUW_LIST_HPP 
#define BUW_LIST_HPP

#include <cstddef>
#include <utility>

/*
Wissenwertes:
Value_type = T
operator=/assign - weißt Werte auf den Behälter
front - Zugriff auf erstes Element /push_front - fügt Element an Anfang
back - Zugriff auf letztes Element /push_back - fügt Elemente ans Ende
pop_back - entfernt letztes Element
pop_front - entfernt erstes Element
clear - löscht Inhalt
erase - löscht Elemente
swap - tauscht Listeninhalte
reverse - kehrt Reihenfolge der Elemente um
*this = pointer, der Objekt zeigt (Adresse)
& = reference (Auch Zeiger, aber direkt aufs Objekt)
const reference (linksbündig, wenn nichts rechts. T const reference x, bezieht sich auf T und ist konstant)
&& = rechtsbündig + reference
Unterschied: Reference - Pointer = Reference kann niemals NULL sein, Pointer schon; Reference ist festgelegt auf Objekt, Pointer kann wechseln; reference muss initialisiert werden, Pointer sind dies jederzeit. (Deswegen auch typedef)
<t> = identifier = Identität für Objekt
DOPPELT Verkettete Liste: Doubly linked lists can store each of the elements they contain in different and unrelated storage locations. (Kann im vor und rückwärts iteriert werden)
Sequence = festgelegte Sequenz in der Liste (reihenfolge, Position)
assertion = um Ausdruck zu evaluieren, Ausdruck darf nicht 0 sein

COPY Konstruktor:
Beim kompilieren wird die vom Menschen verständliche Computersprache in Maschinencode umgewandelt. Der Copy-Konstruktor kopiert die Werte eines Objektes,
*/

//AUFGABE 4.1
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
//AB hier AUFGABE 4.4 implementiert
//Typedef deklariert Objekte, Pointer etc. damit sie intialisierbar und von einem Typ sind
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
    return &(m_node -> m_value); //Übergabewert mit einem Zeiger(reference direkt aufs objekt)
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

  Self next() const //nächster Knoten
  {
    if (m_node)
      return ListIterator(m_node -> m_next);
    else
      return ListIterator(nullptr);
  }

  Self prev() const //vorheriger Knoten
  {
    if (m_node)
      return ListIterator(m_node -> m_prev);
    else
      return ListIterator(nullptr); //wenn kein Knoten = nullptr für Zeiger
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
//AUFGABE 4.7
  //Copy-Konstruktor
 List(List<T> const& listC): 
 m_size {0}, 
 m_first {nullptr}, 
 m_last {nullptr} {
    for (iterator i = listC.begin(); i != listC.end(); ++i) 
    {
      push_back(*i); //*i input/output iterator
    }
  }

//AUFGABE 4.12 - Move- Konstruktor
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
  List<T>& operator = (List<T> list) { //Copy-Konstrukt by-value umgangen, by-value kopiert Werte in formalen Parameter
    swap(list); //Swap-Element
    return *this; //Destruktor für List aufgerufen(beinhaltet alte *this)
  }

 //Vertauscht Inhalte der Listen mit *this
  void swap(List<T>& list) {
      std::swap(m_size, list.m_size);
      std::swap(m_first, list.m_first);
      std::swap(m_last, list.m_last);
  }

  //Swap Funktion in der Liste
  //Friend Methoden haben Zugriff auf Elemente anderer Klassen (muss innerhalb der Klasse deklariert werden)
  friend void swap(List<T>& l1, List<T>& l2) {
    l1.swap(l2);
  }
  
  //AUFGABE 4.3 - Destruktor
  ~List() {
    clear(); 
  //Löscht alle Elemente aus der Liste
  }

  //AUFGABE 4.2
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


//AUFGABE 4.3 - Clear Funktion
  //Voraussetzung des Destruktors und der clear Funktion
  void clear() {
    while (m_size > 0) {
      pop_front();
    }
  }
//AUFGABE 4.5 - Begin und End
  //Iterator, der auf m-first zeigt
  iterator begin() const {
  	return iterator {m_first};
  }

  //Iterator, der auf das Element hinter m_last zeigt
  iterator end() const {
  	return iterator {};
  }

//AUFGABE 4.8 - Insert Methode
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
//AUFGABE 4.9 - Reverse Freie Funktion
   //Kehrt die Sequenz der Liste, die mit der Funktion aufgerufen wird, um.
  void reverse() {
    List<T> tmp{*this}; //Kopie der Liste erstellt(tmp), this ist der pointer auf das Objekt
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

//AUFGABE 4.6 - bool operatoren mit xs=ASIZE, ys=BSIZE

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
//AUFGABE 4.9 - Reverse
  
//Übergebene Liste genommen und reverse angewendet
template<typename T>
List<T> reverse (List<T> reverseList) { //reverse Methode, reverselist Objekt
  reverseList.reverse();
  return reverseList; 
//RETURN: Neue Liste mit umgekehrten Elementen
}

#endif // #define BUW_LIST_HPP
