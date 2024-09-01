#ifndef SET_H
#define SET_H

#include "myexcp.h"

#include <iostream>
#include <iterator>
#include <cstddef>

/**
  @brief classe Set

  La classe implementa un Set di elementi generici T unici (senza ripetizione).
  Il funtore Equals serve a comparare due elementi a e b di tipo T, e restituisce true se sono uguali.

*/
template <typename T, typename Equals>
class Set
{

  /**
    @brief Struttura node

    Struttura dati node interna che viene usata per creare il Set.
    Ogni nodo ha un valore (val) e un puntatore al nodo successivo (next).
  */
  struct node
  {
    T val;
    node *next;

    /**
      @brief Costruttore di default

      Il costruttore di default e' puramente una formalita'. E' privato e non viene mai usato.

      @post next = nullptr
    */
    node() : next(nullptr) {}

    /**
      @brief Costruttore secondario

      @param v valore da copiare

      @post val == v
      @post next = nullptr
    */
    explicit node(const T &v) : val(v), next(nullptr) {}

    /**
      @brief Copy constructor

      @param other node da copiare

      @post val = other.val
      @post next = other.next
    */
    node(const node &other) : val(other.val), next(other.next) {}

    /**
      @brief Operatore di assegnamento

      @param other node da copiare

      @post val = other.val
      @post next = other.next

      @return reference al node this
    */
    node &operator=(const node &other)
    {
      val = other.val;
      next = other.next;
      return *this;
    }

    /**
      Distruttore.  Vuoto perche' non e' mai allocata memoria (esplicitamente).
    */
    ~node() {}
  };

  /**
    @brief ricerca di un valore nel Set
    Verifica se un elemento e' gia' presente nel Set e ritorna il puntatore al nodo precedente

    @param val valore da cercare nel Set

    @return puntatore al nodo precedente del nodo trovato, nullptr se non esiste (o se e' la testa, la gestione spetta al chiamante)
  */
  node *find_internal(const T &val) const
  {
    node *curr = _head;
    node *prev = _head;

    while (curr != nullptr)
    {
      if (_equals(curr->val, val))
        return prev;
      prev = curr;
      curr = curr->next;
    }

    return nullptr;
  }

  node *_head;        ///< puntatore al primo elemento del Set
  unsigned int _size; ///< numero di elementi nel Set
  Equals _equals;     ///< funtore per il confronto di eguaglianza tra dati T

public:
  /**
    @brief Costruttore di default.

    @post _head == nullptr
    @post _size == 0
  */
  Set() : _head(nullptr), _size(0) {}

  /**
    @brief Copy constructor

    @param other Set da copiare

    @post _size = other._size
    @post Set chiamante contiene tutti e soli gli elementi di other.
    @throw std::bad_alloc possibile eccezione di allocazione
  */
  Set(const Set &other) : _head(nullptr), _size(0)
  {
    node *curr = other._head;

    try
    {
      clear();
      while (curr != nullptr)
      {
        add(curr->val);
        curr = curr->next;
      }
    }
    catch (...)
    {
      clear();
      std::cerr << ("   %%%   ERROR IN MEMORY ALLOCATION   %%%");
      throw;
    }
  }

  /**
    @brief Costruttore con coppia di iteratori generici

    @param beg iteratore all'inizio del Set
    @param end iteratore alla fine del Set

    @post _size = other._size
    @post Set chiamante contiene tutti e soli gli elementi del Set con iteratori beg e end
    @throw std::bad_alloc possibile eccezione di allocazione
  */
  template <typename Q>
  Set(Q beg, Q end) : _head(nullptr), _size(0)
  {
    try
    {
      clear();
      while (beg != end)
      {
        add(static_cast<T>(*beg));
        ++beg;
      }
    }
    catch (...)
    {
      clear();
      std::cerr << ("   %%%   ERROR IN MEMORY ALLOCATION   %%%");
      throw;
    }
  }

  /**
    @brief Operatore di assegnamento

    @param other Set da copiare

    @return reference al Set this

    @post _size = other._size
    @post Set chiamante contiene tutti e soli gli elementi di other.
  */
  Set &operator=(const Set &other)
  {
    if (this != &other)
    {
      Set tmp(other);
      std::swap(this->_head, tmp._head);
      std::swap(this->_size, tmp._size);
    }
    return *this;
  }

  /**
    @brief Distruttore

    @post _head == nullptr
    @post _size == 0
  */
  ~Set()
  {
    clear();
  }

  /**
    @brief Svuota il Set

    @post _head == nullptr
    @post _size == 0
  */
  void clear()
  {
    node *curr = _head;

    while (curr != nullptr)
    {
      node *next = curr->next;
      delete curr;
      curr = next;
    }
    _size = 0;
    _head = nullptr;
  }

  /**
     @brief Operatore di lettura dell'elemento in posizione index

     @param index indice dell'elemento da leggere

     @return reference all'elemento in posizione index

     @throw myexcp::myexcp_domain_error se viene passato un Set vuoto
     @throw myexcp::myexcp_out_of_range se viene passato un indice out of bounds
   */
  const T &operator[](int index) const
  {
    if (_size == 0)
      throw(myexcp_domain_error("Empty Set"));
    if (index < 0 || index > _size - 1)
      throw(myexcp_out_of_range("Index out of bounds"));

    node *curr = _head;
    while (index != 0)
    {
      curr = curr->next;
      --index;
    }
    return curr->val;
  }

  /**
    @brief Operatore di confronto (uguaglianza) tra due Set

    Due Set sono definiti equivalenti quando hanno esattamente gli stessi elementi,
    a prescindere dal loro ordine

    @param other Set da confrontare

    @return true se other e il Set chiamante sono equivalenti
  */
  bool operator==(const Set &other) const
  {
    // Set con size diversi
    if (_size != other._size)
      return false;
    // Stesso Set
    if (_head == other._head)
      return true;
    // Una delle due teste nullptr (caso inclusivo controllato precedentemente)
    if (_head == nullptr || other._head == nullptr)
      return false;

    node *curr = _head;
    while (curr != nullptr)
    {
      if (!other.find_internal(curr->val))
        return false;
      curr = curr->next;
    }
    return true;
  }

  /**
    @brief Aggiunge un elemento nel set assicurandosi che non sia gia' presente

    @param val valore da inserire nel set

    @post _size = _size+1

    @throw std::bad_alloc possibile eccezione di allocazione
  */
  void add(const T &val)
  {
    node *tmp = new node(val);

    if (_size == 0)
    {
      _head = tmp;
      _size = 1;
      return;
    }

    // per come e' implementata find_internal, devo essere sicuro che _head non sia uguale a val
    if (_equals(_head->val, val))
    {
      delete tmp;
      tmp = nullptr; ///< per sicurezza
      return;
    }

    node *prev = find_internal(val);

    // find ha trovato elemento con valore val
    if (prev != nullptr)
    {
      delete tmp;
      tmp = nullptr; ///< per sicurezza
      return;
    }

    tmp->next = _head;
    _head = tmp;
    ++_size;
    return;
  }

  /**
    @brief Rimuove (se presente) un elemento dal set.

    Cerca di rimuovere l'elemento con valore val dal Set chiamante. Se trova l'elemento lo cancella
    e ritorna true. Se non lo trova ritorna false.

    @param val valore da rimuovere dal set

    @post _size = _size-1 se val e' presente

    @return true se val e' stato rimosso, false altrimenti
  */
  bool remove(const T &val)
  {

    if (_size == 0)
      return false;

    // per come e' implementata find_internal(), mi devo assicurare che il valore da cancellare non sia in _head
    if (_equals(_head->val, val))
    {
      node *tmp = _head;
      _head = tmp->next;
      delete tmp;
      tmp = nullptr; ///< per sicurezza
      --_size;
      return true;
    }

    node *prev = find_internal(val);
    // find non ha trovato elemento con valore val
    if (prev == nullptr)
      return false;

    node *culprit = prev->next;

    prev->next = culprit->next;
    delete culprit;
    culprit = nullptr; ///< per sicurezza
    --_size;
    return true;
  }

  /**
    @brief ricerca di un valore nel Set
    Verifica se un elemento e' gia' presente nel set, ritorna true se e' presente, false altrimenti

    @param val valore da cercare nel Set

    @return true se valore e' presente nel Set, false altrimenti
  */
  bool find(const T &val) const
  {
    if (_size == 0)
      return false;
    // per come e' implementata find_internal(), mi devo assicurare che il valore da trovare non sia in _head
    if (_equals(_head->val, val))
      return true;
    return find_internal(val) != nullptr;
  }

  /**
    @brief stampa del Set nello standard output

    Overloading dell'operatore << dello standard output per stampa del Set

    @return ostream con il Set da stampare
  */
  friend std::ostream &operator<<(std::ostream &os, const Set &mset)
  {
    node *curr = mset._head;
    bool first = true;
    os << "{";
    while (curr != nullptr)
    {
      if(!first) os << ", ";
      first = false;
      os << curr->val;
      curr = curr->next;
    }
    os << "}";
    return os;
  }

  /**
  @brief classe const_iterator

  Classe interna di iteratori costanti (sola lettura) per iterare sul Set

  */
  class const_iterator
  {
  public:
    typedef std::forward_iterator_tag iterator_category;
    typedef T val_type;
    typedef ptrdiff_t difference_type;
    typedef const T *pointer;
    typedef const T &reference;

    /**
      @brief Costruttore di default.

      @post _ptr = nullptr
    */
    const_iterator() : _ptr(nullptr) {}

    /**
      @brief Copy constructor

      @param other iteratore da copiare

      @post _ptr = other._ptr
    */
    const_iterator(const const_iterator &other) : _ptr(other._ptr) {}

    /**
      @brief Operatore di assegnamento

      @param other iteratore da copiare

      @return reference all'iteratore this

      @post _ptr = other._ptr
    */
    const_iterator &operator=(const const_iterator &other)
    {
      _ptr = other._ptr;
      return *this;
    }

    /**
      @brief Distruttore

      @post _ptr = nullptr
    */
    ~const_iterator() {}

    /**
      @brief Operatore di dereferenziamento

      @return reference al valore dell'elemento puntato da _ptr

      @throw myexcp::myexcp_domain_error se viene dereferenziato un nullptr
    */
    reference operator*() const
    {
      if (_ptr == nullptr)
        throw(myexcp_domain_error("Dereferencing nullptr"));
      return _ptr->val;
    }

    /**
      @brief Operatore freccia

      @return puntatore al valore dell'elemento puntato da _ptr
    */
    pointer operator->() const
    {
      if (_ptr == nullptr)
        throw(myexcp_domain_error("Dereferencing nullptr"));
      return &(_ptr->val);
    }

    /**
      @brief Operatore post incremento

      @param int dummy parameter

      @post _ptr = _ptr->next

      @return reference all'iteratore this (prima di essere incrementato)

      @throw myexcp::myexcp_domain_error se viene dereferenziato un nullptr
    */
    const_iterator operator++(int)
    {
      if (_ptr == nullptr)
        throw(myexcp_domain_error("Dereferencing nullptr"));
      const_iterator tmp(*this);
      _ptr = _ptr->next;
      return tmp;
    }

    /**
      @brief Operatore pre incremento

      @post _ptr = _ptr->next

      @return reference all'iteratore this (incrementato)

      @throw myexcp::myexcp_domain_error se viene dereferenziato un nullptr
    */
    const_iterator &operator++()
    {
      if (_ptr == nullptr)
        throw(myexcp_domain_error("Dereferencing nullptr"));
      _ptr = _ptr->next;
      return *this;
    }

    /**
    @brief Operatore di confronto (uguaglianza) tra due iteratori

    @param other iteratore da confrontare

    @return true se i due iteratori puntano allo stesso elemento
    */
    bool operator==(const const_iterator &other) const
    {
      return _ptr == other._ptr;
    }

    /**
    @brief Operatore di confronto (disuguaglianza) tra due iteratori

    Predicato opposto al == operator

    @param other iteratore da confrontare

    @return true se i due iteratori non puntano allo stesso elemento
    */
    bool operator!=(const const_iterator &other) const
    {
      return _ptr != other._ptr;
    }

  private:
    const node *_ptr;

    friend class Set;

    const_iterator(const node *p) : _ptr(p) {}
  };

  /**
      @brief Iteratore all'inizio del Set

      @return copia dell'iteratore all'inizio del Set
  */
  const_iterator begin() const
  {
    return const_iterator(_head);
  }

  /**
      @brief Iteratore alla fine del Set

      @return copia dell'iteratore alla fine del Set
  */
  const_iterator end() const
  {
    return const_iterator(nullptr);
  }
};

/**
    @brief Crea un nuovo Set con tutti e soli gli elementi del Set di partenza che soddisfano un certo predicato

    @param mset Set di partenza
    @param pred predicato booleano filtro

    @return Set con tutti e soli gli elementi del Set di partenza che soddisfano il predicato P

    @throw std::bad_alloc possibile eccezione di allocazione
  */
template <typename T, typename E, typename P>
Set<T, E> filter_out(const Set<T, E> &mset, P pred)
{
  Set<T, E> out_set;
  typename Set<T, E>::const_iterator beg = mset.begin(),
                                     end = mset.end();

  try
  {
    while (beg != end)
    {
      if (pred(*beg))
        out_set.add(*beg);
      ++beg;
    }
  }
  catch (...)
  {
    std::cerr << ("   %%%   ERROR IN MEMORY ALLOCATION   %%%");
    throw;
  }
  return out_set;
}

/**
    @brief Concatenazione di due set

    @param set1 primo Set da concatenare
    @param set2 secondo Set da concatenare

    @return Set che contiene gli elementi di entrambi i Set (la loro concatenazione)

    @throw std::bad_alloc possibile eccezione di allocazione
  */
template <typename T, typename E>
Set<T, E> operator+(const Set<T, E> &set1, const Set<T, E> &set2)
{
  Set<T, E> out_set = set2;
  typename Set<T, E>::const_iterator beg = set1.begin(),
                                     end = set1.end();
  try
  {
    while (beg != end)
    {
      out_set.add(*beg);
      ++beg;
    }
  }
  catch (...)
  {
    std::cerr << ("   %%%   ERROR IN MEMORY ALLOCATION   %%%");
    throw;
  }
  return out_set;
}

/**
    @brief Intersezione di due Set

    @param set1 primo Set da intersecare
    @param set2 secondo Set da intersecare

    @return Set che contiene gli elementi comuni ad entrambi i Set (la loro intersezione)

    @throw std::bad_alloc possibile eccezione di allocazione
  */
template <typename T, typename E>
Set<T, E> operator-(const Set<T, E> &set1, const Set<T, E> &set2)
{
  Set<T, E> out_set;
  typename Set<T, E>::const_iterator beg = set1.begin(),
                                     end = set1.end();

  try
  {
    while (beg != end)
    {
      if (set2.find(*beg))
        out_set.add(*beg);
      ++beg;
    }
  }
  catch (...)
  {
    std::cerr << ("   %%%   ERROR IN MEMORY ALLOCATION   %%%");
    throw;
  }

  return out_set;
}

#endif