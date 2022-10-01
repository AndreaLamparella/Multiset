#ifndef MULTISET_H
#define MULTISET_H

#include <algorithm>
#include <stdexcept>
#include <math.h> // floor
#include <iterator> // std::forward_iterator_tag
#include <cstddef>  // std::ptrdiff_t
#include <climits>
#include "element_not_found.h"

template <typename T, typename Comp, typename Eq>
class multiset {
private:

  typedef unsigned int size_type;

  /**
   * @brief entry del multiset, costituita da una coppia valore, frequenza
  */
  
  struct element {
    T value;            ///< il dato effettivo memorizzato
    unsigned int freq;  ///< la frequenza con cui @p value compare nel multiset

    /// @brief istanzia un element
    element() : freq(0) { }

    /// @brief istanzia un elment contenente un valore con frequenza unitaria
    /// @param v il valore presente in element
    explicit element(const T &v) : value(v), freq(1) { }

    /// @brief copy constructor 
    /// @param other element da cui copiare i dati per istanziare l'oggetto corrente
    element(const element &other) : value(other.value), freq(other.freq) { }

    ~element() {}

  };

  /**
   * Ritorna l'indice in cui è presente il valore
   * oppure, se non è presente, l'indice in cui può essere
   * inserito senza alterare l'ordine
   * Potrebbe restituire intero più grande del container
   * nel caso in cui tale elemento deve essere messo per ultimo
   */
  size_type binsearch(const T &val) const {
    size_type low = 0, high = _size;
    while (low < high) {
      size_type mid = low + (high - low) / 2; // TODO use floor

      if (_equal(_data[mid].value, val))
        return mid;

      else if (_compare(_data[mid].value, val))
        low = mid + 1;
      else if (_compare(val, _data[mid].value))
        high = mid;
      }
    return low;
  }



  element *_data;   ///< puntatore al primo elemento
  size_type _size;  ///< elementi distinti nel multiset
  Comp _compare;    ///< funtore che implementa una relazione d'ordine
  Eq _equal;        ///< funtore che implementa una relazione d'equivalenza

 public:
  /// @brief istanzia un multiset vuoto
  multiset() : _data(nullptr), _size(0) {}

  /// @brief copy constructor
  /// @param other multiset da copiare i dati per istanziare l'oggetto corrente
  multiset(const multiset &other) : _data(nullptr), _size(0) {
    _data = new element[other._size];
    try {
        for (size_type i = 0; i < other._size; ++i)
            _data[i] = other._data[i];
        _size = other._size;
    } catch (...) {
        clear();
        throw;
    }
  } 

  /// @brief multiset assignment operator
  multiset &operator=(const multiset &other) {
    if (this != other)  {
      multiset tmp(other);
      std::swap(this->_data, tmp._data);
      std::swap(this->_size, tmp._size);
    }

    return *this;
  }

  ~multiset() {
    clear();
  }

  /// @brief istanzia un multiset a partire da due iteratori
  /// @param b iteratore di inizio sequenza
  /// @param e iteratore di fine sequenza
  template<typename Iter>
  multiset(Iter b, Iter e) : _data(nullptr), _size(0) {
    try {
      for (; b != e; ++b)
        insert(static_cast<T>(*b));
    } catch (...) {
      clear();
      throw ;
    }
  }

  
// TODO 
// potrebbe essere sufficiente controllare se i < _size poiché
// se l'elemento è contenuto allora ritorna un indice compreso fra [0, _size[
// altrimenti se non appartiene ritorna 
// 1. un indice compreso fra [0, _size[ 
// 2. _size qualora dovesse essere inserito per ultimo
// pertanto controllare che a quell'indice il valore è proprio quello cercato
// è ridondante

/**
 * ASSOLUTAMENTE NO! 
 * È importante controllare il valore altrimenti non è possibile determinare se
 * la binsearch() ritorna l'indice di un elemento effettivamente presente nella
 * struttura dati, oppure l'indice di dove si dovrebbe inserire l'elemento per 
 * mantenere l'ordine della stessa.

  bool contains_Draft(const T &v) const {
    size_type i = binsearch(v);
    return i < _size ? true : false;
  }
*/

  /**
   * Metodo helper del distruttore. 
   * Rimuove tutti i dati della matrice dalla memoria.
   * 
   * @see ~multiset()
  */
  void clear() {
    delete[] _data;
    _data = nullptr;
    _size = 0;
  }

  /// @brief restituisce il numero di elementi del multiset
  size_type size() const {
    int sum = 0;
    element *tmp = _data;
    for (int i = 0; i < _size; ++i) {
      if (tmp->freq > 0 && sum > INT_MAX - tmp->freq)
        throw std::overflow_error("Overflow occurred");
      sum += tmp->freq;
      ++tmp;
    }
    return sum;
  }

  /// @brief inserisce un elemento nel multiset mantenendone l'ordine
  /// @param x l'elemento da inserire
  void insert(const T &x) {
    size_type i = 0;
    size_type where = binsearch(x);

    if (where < _size && _data[where].value == x) {
      ++_data[where].freq;
    } else {
      size_type sz = _size + 1;
      element *tmp = new element[sz];
      
      // copio i dati prima 
      for(; i < where; ++i) 
        tmp[i] = _data[i];

      // aggiungo l'elemento nuovo
      tmp[i++] = element(x);

      // e copio la restante parte degli elementi
      for(; i <= _size; ++i) 
        tmp[i] = _data[i-1];

      clear();
      _data = tmp;
      _size = sz;
    }
  }

  /// @brief elimina un elemento dal multiset
  /// @param x l'elemento da inserire dal multiset
  void erase(const T &x) {
    size_type where = binsearch(x);
    if ((where < _size && _data[where].value != x) || where >= _size) { 
      throw element_not_found("Erasing an element which is not in the multiset");
    }
    
    // decremento il numero di occorrenze di quel dato
    // se è ancora maggiore di 0 allora non bisogna riallocare memoria
    if (--_data[where].freq > 0) return;

    size_type i = 0, sz = _size - 1;
    element *tmp = new element[sz];

    for (; i < where; ++i)
      tmp[i] = _data[i];
    ++i; // "salto" l'elemento da eliminare

    for(; i < _size; ++i) 
      tmp[i-1] = _data[i];

    clear();
    _data = tmp;
    _size = sz;
  }

  /// @brief confronta se due multiset sono uguali a meno del loro ordinamento
  /// @param other multiset di confronto
  /// @return true se i multiset sono uguali, false altrimenti
  template<typename Comp2>
  bool operator==(const multiset<T, Comp2, Eq> &other) const {
    if (this->size() != other.size()) 
      return false;

    for (unsigned int i = 0; i < _size; ++i) {
      bool same_value = contains(_data[i].value) == other.contains(_data[i].value);
      bool same_freq = _data[i].freq == other.occurs(_data[i].value);
      if (!(same_value && same_freq))
        return false; 
    }
    return true;
  }

  /// @brief restituisce il numero di occorrenze di un elemento
  /// @param x il valore di cui si vogliono le occorrenze
  /// @return il numero di occorrenze di @p x, 
  ///         0 nel caso in cui @p x non appartenga al multiset
  size_type occurs(const T &x) const {
    size_type where = binsearch(x);
    
    return where < _size && _data[where].value == x ? _data[where].freq : 0 ;
     // TODO devo lanciare una eccezione?

  }

  /// @brief determina se un elemento appartiene al multiset 
  /// @param v il valore da cercare all'interno del multiset
  /// @return true se appartiene, false altrimenti
  bool contains(const T &v) const {
    size_type i = binsearch(v);
    return (i < _size && _data[i].value == v);
  }

class const_iterator {
	public:
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef T                               value_type;
		typedef ptrdiff_t                       difference_type;
		typedef const T*                        pointer;
		typedef const T&                        reference;

	
		const_iterator() : ptr(nullptr), f(0) {	}
		
		const_iterator(const const_iterator &other) : ptr(other.ptr), f(other.f) { }

		const_iterator& operator=(const const_iterator &other) {
      ptr = other.ptr;
      f = other.f;
      return *this;
		}

		~const_iterator() {	}

		// Ritorna il dato riferito dall'iteratore (dereferenziamento)
		reference operator*() const {
			return ptr->value;
		}

		// Ritorna il puntatore al dato riferito dall'iteratore
		pointer operator->() const {
			return &ptr->value;
		}
		
		// Operatore di iterazione post-incremento
		const_iterator operator++(int) {
			const_iterator past(*this);
      if (f == 0) 
        f = ptr->freq;
      
      if (f > 1) {
        --f;
      } else {
        ++ptr;
        f = 0;
      }

      return past;
		}

		// Operatore di iterazione pre-incremento
		const_iterator& operator++() {
      if (f == 0) 
        f = ptr->freq;

			if (f > 1) {
        --f;
      } else {
        ++ptr;
        f = 0;
      }
      return *this;      
		}
    
		// Operatore di iterazione post-decremento
    const_iterator operator--(int) {
      const_iterator past(*this);
      if (f == 0) 
        f = ptr->freq;
      if (f < ptr->freq) {
        ++f;
      } else {
        --ptr;
        f = 0;
      }
      return past;
    }
		// Operatore di iterazione pre-decremento
    const_iterator& operator--() {
      if (f == 0) 
        f = ptr->freq;
      if (f < ptr->freq) {
        ++f;
      } else {
        --ptr;
        f = 0;
      }
      return *this;
    }

		// Uguaglianza
		bool operator==(const const_iterator &other) const {
      // return ptr == other.ptr;
			return (ptr == other.ptr) && (f == other.f);
		}
		
		// Diversita'
		bool operator!=(const const_iterator &other) const {
			return !(*this == other);
		}

	private:
		//Dati membro
    const element *ptr;
    int f;

		friend class multiset; 

		// Costruttore privato di inizializzazione usato dalla classe container
		// tipicamente nei metodi begin e end
		const_iterator(const element *elem)  {
      ptr = elem;
      f = 0;
     }
		
		
	}; // classe const_iterator
	
	// Ritorna l'iteratore all'inizio della sequenza dati
	const_iterator begin() const {
		return const_iterator(_data);
	}
	
	// Ritorna l'iteratore alla fine della sequenza dati
	const_iterator end() const {
		return const_iterator(_data + _size);
	}  

  friend std::ostream &operator<<(std::ostream &os, const multiset &ms) {
    os << "{ ";
    for (size_type i = 0; i < ms._size; ++i) {
      os << "<" << ms._data[i].value << ", " << ms._data[i].freq << "> ";
    }
    os << "}";

    return os;  
  }

};


#endif
