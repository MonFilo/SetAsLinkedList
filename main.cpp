#include "set.h"
#include "myexcp.h"

#include <iostream>
#include <string>

/**
  @brief Funtore di uguaglianza tra interi

  @param a primo intero da confrontare
  @param b secondo intero da confrontare

  @return true se a == b, false altrimenti
*/
struct int_equal
{
	inline bool operator()(int a, int b) const
	{
		return a == b;
	}
};

/**
  @brief Funtore di uguaglianza tra interi costanti

  @param a primo intero const da confrontare
  @param b secondo intero const da confrontare

  @return true se a == b, false altrimenti
*/
struct const_int_equal
{
	inline bool operator()(const int a, const int b) const
	{
		return a == b;
	}
};

/**
  @brief Funtore di uguaglianza tra float

  @param a primo float da confrontare
  @param b secondo float da confrontare

  @return true se a == b, false altrimenti
*/
struct float_equal
{
	inline bool operator()(float a, float b) const
	{
		return a == b;
	}
};

/**
  @brief Funtore di uguaglianza tra string

  @param a prima string da confrontare
  @param b seconda string da confrontare

  @return true se a == b, false altrimenti
*/
struct string_equal
{
	inline bool operator()(std::string a, std::string b) const
	{
		return a == b;
	}
};

/**
  @brief Funtore di uguaglianza tra bool

  @param a primo bool da confrontare
  @param b secondo bool da confrontare

  @return true se a == b, false altrimenti
*/
struct bool_equal
{
	inline bool operator()(bool a, bool b) const
	{
		return a == b;
	}
};

/**
  @brief Funtore di uguaglianza tra Set di interi

  @param a primo set da confrontare
  @param b secondo set da confrontare

  @return true se a e b hanno medesimi set al loro interno, false altrimenti
*/
struct set_int_equal
{
	bool operator()(Set<int, int_equal> fst_set, Set<int, int_equal> snd_set) const
	{
		typename Set<int, int_equal>::const_iterator beg = fst_set.begin(),
													 end = fst_set.end();
		typename Set<int, int_equal>::const_iterator beg2 = snd_set.begin(),
													 end2 = snd_set.end();
		if (beg == end && beg2 == end2)
			return true;
		if (beg == end || beg2 == end2)
			return false;
		while (beg != end)
		{
			if (!snd_set.find(*beg))
				return false;
			++beg;
		}
		return true;
	}
};

/**
  @brief Funtore per controllare positivita' di interi

  @param a intero da controllare

  @return true a > 0, false altrimenti
*/
struct int_is_positive
{
	inline bool operator()(int a) const
	{
		return (a > 0);
	}
};

/**
  @brief Funtore per controllare positivita' di float

  @param a float da controllare

  @return true se a > 0, false altrimenti
*/
struct float_is_positive
{
	inline bool operator()(float a) const
	{
		return (a > 0);
	}
};

/**
  @brief Funtore per controllare lunghezza di string

  @param a string da controllare

  @return true se lunghezza di a < 5, false altrimenti
*/
struct string_is_short
{
	inline bool operator()(std::string a) const
	{
		return (a.length() < 5);
	}
};

/**
  @brief Funtore per controllare veridicita' di bool

  @param a bool da controllare

  @return true a == true, false altrimenti
*/
struct bool_is_true
{
	inline bool operator()(bool a) const
	{
		return a;
	}
};

struct person
{
	char const *name;
	char const *surname;
	unsigned int age;
};

/**
  @brief Funtore di uguaglianza tra person

  @param a prima person da confrontare
  @param b seconda person da confrontare

  @return true se a e b hanno medesimi dati (nome, cognome, eta'), false altrimenti
*/
struct person_equal
{
	inline bool operator()(person a, person b) const
	{
		return (a.surname == b.surname && a.name == b.name && a.age == b.age);
	}
};

/**
  @brief Funtore per controllare eta' di person

  @param a person da controllare

  @return true se eta' di a > 25, false altrimenti
*/
struct person_is_old
{
	inline bool operator()(person a) const
	{
		return a.age > 25;
	}
};

/**
  @brief Funtore per controllare dimensione di Set di interi

  @param a set da controllare

  @return true se a contiene almeno 4 elementi, false altrimenti
*/
struct set_is_large
{
	bool operator()(Set<int, int_equal> mset) const
	{
		typename Set<int, int_equal>::const_iterator beg = mset.begin(),
													 end = mset.end();
		unsigned int counter = 0;
		while (beg != end)
		{
			counter++;
			++beg;
		}
		return counter > 3;
	}
};

/**
	@brief stampa del dato person nello standard output

	Overloading dell'operatore << dello standard output per stampa di person

	@return ostream con la person da stampare
  */
std::ostream &operator<<(std::ostream &os, const person &p)
{
	os << "[";
	os << p.name << " " << p.surname << ", " << p.age;
	os << "]";
	return os;
}

/**
	@brief test su tipi di dati int
	Test completo dell'interfaccia (tutti i metodi pubblici) della classe templata Set su dati di tipo int
  */
void test_int_set()
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	// Test su tipi di dati semplici (int)
	std::cout << "--- TEST SU DATI INT ---\n"
			  << std::endl;

	// Test costruttore default
	std::cout << "- default constructor: " << std::endl;

	Set<int, int_equal> set1;
	std::cout << "\tset1 = " << set1 << std::endl;

	// Test add
	std::cout << "- add" << std::endl;

	std::cout << "\t10 to " << set1 << " -> ";
	set1.add(10);
	std::cout << set1 << std::endl;

	std::cout << "\t-10 to " << set1 << " -> ";
	set1.add(-10);
	std::cout << set1 << std::endl;

	std::cout << "\t1 to " << set1 << " -> ";
	set1.add(1);
	std::cout << set1 << std::endl;

	std::cout << "\t5 to " << set1 << " -> ";
	set1.add(5);
	std::cout << set1 << std::endl;

	std::cout << "\t1 to " << set1 << " -> ";
	set1.add(1);
	std::cout << set1 << std::endl;

	// Test remove
	std::cout << "- remove" << std::endl;

	std::cout << "\t-5 from " << set1 << " -> ";
	bool temp = set1.remove(-5);
	std::cout << set1 << " : " << (temp ? "true" : "false") << std::endl;

	std::cout << "\t5 from " << set1 << " -> ";
	temp = set1.remove(5);
	std::cout << set1 << " : " << (temp ? "true" : "false") << std::endl;

	// Test clear
	std::cout << "- clear" << std::endl;

	std::cout << '\t' << set1 << " -> ";
	set1.clear();
	std::cout << set1 << std::endl;

	// Reset per test seguenti
	set1.add(7);
	set1.add(23);
	set1.add(-5);
	set1.add(0);

	// Test copy constructor
	std::cout << "- copy constructor" << std::endl;

	std::cout << "\tset1 = " << set1 << std::endl;
	Set<int, int_equal> set2 = Set<int, int_equal>(set1);
	std::cout << "\tset2 = " << set2 << std::endl;

	// Test operator =
	std::cout << "- operator =" << std::endl;

	Set<int, int_equal> set3;
	set3 = set2;
	std::cout << "\tset3 = " << set3 << std::endl;

	// Test costruttore con iterators
	std::cout << "- costruttore con iterators" << std::endl;

	Set<int, int_equal> set4(set3.begin(), set3.end());
	std::cout << "\tset4 = " << set4 << std::endl;

	// Test operator []
	std::cout << "- operator []" << std::endl;

	std::cout << "\tset1 = " << set1 << std::endl;
	try
	{
		std::cout << "\tset1[1] = " << set1[1] << std::endl;
	}
	catch (myexcp_domain_error &e)
	{	
		std::cerr << e.what() << std::endl;
	}
	catch(myexcp_out_of_range &e)
	{
		std::cerr << e.what() << std::endl;
	}
	try
	{
		std::cout << "\tset1[-1] = " << set1[-1] << std::endl;
	}
	catch (myexcp_domain_error &e)
	{	
		std::cerr << e.what() << std::endl;
	}
	catch(myexcp_out_of_range &e)
	{
		std::cerr << e.what() << std::endl;
	}
	try
	{
		std::cout << "\tset1[4] = " << set1[4] << std::endl;
	}
	catch (myexcp_domain_error &e)
	{	
		std::cerr << e.what() << std::endl;
	}
	catch(myexcp_out_of_range &e)
	{
		std::cerr << e.what() << std::endl;
	}

	// Test operator ==
	std::cout << "- operator ==" << std::endl;

	set2.remove(7);
	std::cout << '\t' << set1 << " == " << set1 << " : " << ((set1 == set1) ? "true" : "false") << std::endl;
	std::cout << '\t' << set1 << " == " << set2 << " : " << ((set1 == set2) ? "true" : "false") << std::endl;
	std::cout << '\t' << set1 << " == " << set4 << " : " << ((set1 == set4) ? "true" : "false") << std::endl;

	// Test filter_out
	std::cout << "- filter_out (positive)" << std::endl;

	int_is_positive is_pos_int;
	std::cout << '\t' << set1 << " -> " << filter_out(set1, is_pos_int) << std::endl;

	// Reset per test seguenti
	set1.clear();
	set1.add(0);
	set1.add(-5);
	set1.add(7);
	set1.add(12);
	set1.add(-4);

	set2.clear();
	set2.add(1);
	set2.add(0);
	set2.add(-7);

	set3.clear();
	set3.add(6);
	set3.add(12);

	std::cout << "set1 = " << set1 << std::endl;
	std::cout << "set2 = " << set2 << std::endl;
	std::cout << "set3 = " << set3 << std::endl;
	set2 = set1;
	std::cout << "set2 = " << set2 << std::endl;

	// Test operator+
	std::cout << "- operator +" << std::endl;
	std::cout << '\t' << set1 << " + " << set2 << " = " << set1 + set2 << std::endl;
	std::cout << '\t' << set2 << " + " << set1 << " = " << set2 + set1 << std::endl;
	std::cout << '\t' << set2 << " + " << set3 << " = " << set2 + set3 << std::endl;

	// Test operator-
	std::cout << "- operator -" << std::endl;

	std::cout << '\t' << set1 << " - " << set2 << " = " << set1 - set2 << std::endl;
	std::cout << '\t' << set2 << " - " << set1 << " = " << set2 - set1 << std::endl;
	std::cout << '\t' << set1 << " - " << set3 << " = " << set1 - set3 << std::endl;

	// Test find
	std::cout << "- find " << std::endl;

	std::cout << "\t1 in " << set1 << " : " << ((set1.find(1)) ? "true" : "false") << std::endl;
	std::cout << "\t0 in " << set1 << " : " << ((set1.find(0)) ? "true" : "false") << std::endl;
	std::cout << "\t-3 in " << (set1 - set2) << " : " << (((set1 - set2).find(-3)) ? "true" : "false") << std::endl;
}

/**
	@brief test su tipi di dati const int
	Test completo dell'interfaccia (tutti i metodi pubblici) della classe templata Set su dati di tipo const int
  */
void test_const_set()
{

	//////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	// Test su tipi di dati costanti (int)
	std::cout << "\n\n--- TEST SU DATI CONST INT ---\n"
			  << std::endl;

	// Test costruttore default
	std::cout << "- default constructor: " << std::endl;

	Set<const int, const_int_equal> setc1;
	std::cout << "\tsetc1 = " << setc1 << std::endl;

	// Test add
	std::cout << "- add" << std::endl;

	std::cout << "\t10 to " << setc1 << " -> ";
	setc1.add(10);
	std::cout << setc1 << std::endl;

	std::cout << "\t-10 to " << setc1 << " -> ";
	setc1.add(-10);
	std::cout << setc1 << std::endl;

	std::cout << "\t1 to " << setc1 << " -> ";
	setc1.add(1);
	std::cout << setc1 << std::endl;

	std::cout << "\t5 to " << setc1 << " -> ";
	setc1.add(5);
	std::cout << setc1 << std::endl;

	std::cout << "\t1 to " << setc1 << " -> ";
	setc1.add(1);
	std::cout << setc1 << std::endl;

	// Test remove
	std::cout << "- remove" << std::endl;

	std::cout << "\t-5 from " << setc1 << " -> ";
	bool temp = setc1.remove(-5);
	std::cout << setc1 << " : " << (temp ? "true" : "false") << std::endl;

	std::cout << "\t5 from " << setc1 << " -> ";
	temp = setc1.remove(5);
	std::cout << setc1 << " : " << (temp ? "true" : "false") << std::endl;

	// Test clear
	std::cout << "- clear" << std::endl;

	std::cout << '\t' << setc1 << " -> ";
	setc1.clear();
	std::cout << setc1 << std::endl;

	// Reset per test seguenti
	setc1.add(7);
	setc1.add(23);
	setc1.add(-5);
	setc1.add(0);

	// Test copy constructor
	std::cout << "- copy constructor" << std::endl;

	std::cout << "\tsetc1 = " << setc1 << std::endl;
	Set<const int, const_int_equal> setc2 = Set<const int, const_int_equal>(setc1);
	std::cout << "\tsetc2 = " << setc2 << std::endl;

	// Test operator =
	std::cout << "- operator =" << std::endl;

	Set<const int, const_int_equal> setc3;
	setc3 = setc2;
	std::cout << "\tsetc3 = " << setc3 << std::endl;

	// Test costruttore con iterators
	std::cout << "- costruttore con iterators" << std::endl;

	Set<const int, const_int_equal> setc4(setc3.begin(), setc3.end());
	std::cout << "\tsetc4 = " << setc4 << std::endl;

	// Test operator []
	std::cout << "- operator []" << std::endl;

	std::cout << "\tsetc1 = " << setc1 << std::endl;
	try
	{
		std::cout << "\tsetc1[1] = " << setc1[1] << std::endl;
	}
	catch (myexcp_domain_error &e)
	{	
		std::cerr << e.what() << std::endl;
	}
	catch(myexcp_out_of_range &e)
	{
		std::cerr << e.what() << std::endl;
	}
	try
	{
		std::cout << "\tsetc1[-1] = " << setc1[-1] << std::endl;
	}
	catch (myexcp_domain_error &e)
	{	
		std::cerr << e.what() << std::endl;
	}
	catch(myexcp_out_of_range &e)
	{
		std::cerr << e.what() << std::endl;
	}
	try
	{
		std::cout << "\tsetc1[4] = " << setc1[4] << std::endl;
	}
	catch (myexcp_domain_error &e)
	{	
		std::cerr << e.what() << std::endl;
	}
	catch(myexcp_out_of_range &e)
	{
		std::cerr << e.what() << std::endl;
	}

	// Test operator ==
	std::cout << "- operator ==" << std::endl;

	setc2.remove(7);
	std::cout << '\t' << setc1 << " == " << setc1 << " : " << ((setc1 == setc1) ? "true" : "false") << std::endl;
	std::cout << '\t' << setc1 << " == " << setc2 << " : " << ((setc1 == setc2) ? "true" : "false") << std::endl;
	std::cout << '\t' << setc1 << " == " << setc4 << " : " << ((setc1 == setc4) ? "true" : "false") << std::endl;

	// Test filter_out
	std::cout << "- filter_out (positive)" << std::endl;

	int_is_positive is_pos_int;
	std::cout << '\t' << setc1 << " -> " << filter_out(setc1, is_pos_int) << std::endl;

	// Reset per test seguenti
	setc1.clear();
	setc1.add(0);
	setc1.add(-5);
	setc1.add(7);
	setc1.add(12);
	setc1.add(-4);

	setc2.clear();
	setc2.add(1);
	setc2.add(0);
	setc2.add(-7);

	setc3.clear();
	setc3.add(6);
	setc3.add(-4);

	std::cout << "setc1 = " << setc1 << std::endl;
	std::cout << "setc2 = " << setc2 << std::endl;
	std::cout << "setc3 = " << setc3 << std::endl;
	setc2 = setc1;
	std::cout << "setc2 = " << setc2 << std::endl;

	// Test operator+
	std::cout << "- operator +" << std::endl;

	std::cout << '\t' << setc1 << " + " << setc2 << " = " << setc1 + setc2 << std::endl;
	std::cout << '\t' << setc2 << " + " << setc1 << " = " << setc2 + setc1 << std::endl;
	std::cout << '\t' << setc2 << " + " << setc3 << " = " << setc2 + setc3 << std::endl;

	// Test operator-
	std::cout << "- operator -" << std::endl;

	std::cout << '\t' << setc1 << " - " << setc2 << " = " << setc1 - setc2 << std::endl;
	std::cout << '\t' << setc2 << " - " << setc1 << " = " << setc2 - setc1 << std::endl;
	std::cout << '\t' << setc1 << " - " << setc3 << " = " << setc1 - setc3 << std::endl;

	// Test find
	std::cout << "- find " << std::endl;

	std::cout << "\t1 in " << setc1 << " : " << ((setc1.find(1)) ? "true" : "false") << std::endl;
	std::cout << "\t0 in " << setc1 << " : " << ((setc1.find(0)) ? "true" : "false") << std::endl;
	std::cout << "\t-3 in " << (setc1 - setc2) << " : " << (((setc1 - setc2).find(-3)) ? "true" : "false") << std::endl;
}

/**
	@brief test su tipi di dati float
	Test completo dell'interfaccia (tutti i metodi pubblici) della classe templata Set su dati di tipo float
  */
void test_float_set()
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	// Test su tipi di dati semplici (float)

	std::cout << "\n\n--- TEST SU DATI FLOAT ---\n"
			  << std::endl;

	// Test costruttore default
	std::cout << "- default constructor: " << std::endl;

	Set<float, float_equal> setf1;
	std::cout << "\tsetf1 = " << setf1 << std::endl;

	// Test add
	std::cout << "- add" << std::endl;

	std::cout << "\t10.34 to " << setf1 << " -> ";
	setf1.add(10.34);
	std::cout << setf1 << std::endl;

	std::cout << "\t-10.72 to " << setf1 << " -> ";
	setf1.add(-10.72);
	std::cout << setf1 << std::endl;

	std::cout << "\t1.0 to " << setf1 << " -> ";
	setf1.add(1.0);
	std::cout << setf1 << std::endl;

	std::cout << "\t5.468468 to " << setf1 << " -> ";
	setf1.add(5.468468);
	std::cout << setf1 << std::endl;

	std::cout << "\t1.0 to " << setf1 << " -> ";
	setf1.add(1.0);
	std::cout << setf1 << std::endl;

	// Test remove
	std::cout << "- remove" << std::endl;

	std::cout << "\t-5.3 from " << setf1 << " -> ";
	bool temp = setf1.remove(-5.3);
	std::cout << setf1 << " : " << (temp ? "true" : "false") << std::endl;

	std::cout << "\t5.468468 from " << setf1 << " -> ";
	temp = setf1.remove(5.468468);
	std::cout << setf1 << " : " << (temp ? "true" : "false") << std::endl;

	// Test clear
	std::cout << "- clear" << std::endl;

	std::cout << '\t' << setf1 << " -> ";
	setf1.clear();
	std::cout << setf1 << std::endl;

	// Reset per test seguenti
	setf1.add(5.2);
	setf1.add(12.679);
	setf1.add(-9.12);
	setf1.add(0);

	// Test copy constructor
	std::cout << "- copy constructor" << std::endl;

	std::cout << "\tsetf1 = " << setf1 << std::endl;
	Set<float, float_equal> setf2 = Set<float, float_equal>(setf1);
	std::cout << "\tsetf2 = " << setf2 << std::endl;

	// Test operator =
	std::cout << "- operator =" << std::endl;

	Set<float, float_equal> setf3;
	setf3 = setf2;
	std::cout << "\tsetf3 = " << setf3 << std::endl;

	// Test costruttore con iterators
	std::cout << "- costruttore con iterators" << std::endl;

	Set<float, float_equal> setf4(setf3.begin(), setf3.end());
	std::cout << "\tsetf4 = " << setf4 << std::endl;

	// Test operator []
	std::cout << "- operator []" << std::endl;

	std::cout << "\tsetf1 = " << setf1 << std::endl;
	try
	{
		std::cout << "\tsetf1[1] = " << setf1[1] << std::endl;
	}
	catch (myexcp_domain_error &e)
	{	
		std::cerr << e.what() << std::endl;
	}
	catch(myexcp_out_of_range &e)
	{
		std::cerr << e.what() << std::endl;
	}

	// Test operator ==
	std::cout << "- operator ==" << std::endl;

	setf2.remove(-9.12);
	std::cout << '\t' << setf1 << " == " << setf1 << " : " << ((setf1 == setf1) ? "true" : "false") << std::endl;
	std::cout << '\t' << setf1 << " == " << setf2 << " : " << ((setf1 == setf2) ? "true" : "false") << std::endl;
	std::cout << '\t' << setf1 << " == " << setf4 << " : " << ((setf1 == setf4) ? "true" : "false") << std::endl;

	// Test filter_out
	std::cout << "- filter_out (positive)" << std::endl;

	float_is_positive is_pos_float;
	std::cout << '\t' << setf1 << " -> " << filter_out(setf1, is_pos_float) << std::endl;

	// Reset per test seguenti
	setf1.clear();
	setf1.add(0.735);
	setf1.add(-578.3456);
	setf1.add(2.235);
	setf1.add(11.2);
	setf1.add(-8.888);

	setf2.clear();
	setf2.add(2.235);
	setf2.add(0.002);
	setf2.add(-9.532);

	setf3.clear();
	setf3.add(6.9567);
	setf3.add(8);

	// Test operator+
	std::cout << "- operator +" << std::endl;

	std::cout << '\t' << setf1 << " + " << setf2 << " = " << setf1 + setf2 << std::endl;
	std::cout << '\t' << setf2 << " + " << setf1 << " = " << setf2 + setf1 << std::endl;
	std::cout << '\t' << setf2 << " + " << setf3 << " = " << setf2 + setf3 << std::endl;

	// Test operator-
	std::cout << "- operator -" << std::endl;

	std::cout << '\t' << setf1 << " - " << setf2 << " = " << setf1 - setf2 << std::endl;
	std::cout << '\t' << setf2 << " - " << setf1 << " = " << setf2 - setf1 << std::endl;
	std::cout << '\t' << setf1 << " - " << setf3 << " = " << setf1 - setf3 << std::endl;

	// Test find
	std::cout << "- find " << std::endl;

	std::cout << "\t0.735 in " << setf1 << " : " << ((setf1.find(0.735)) ? "true" : "false") << std::endl;
	std::cout << "\t0 in " << setf1 << " : " << ((setf1.find(0)) ? "true" : "false") << std::endl;
	std::cout << "\t2.235 in " << (setf1 - setf2) << " : " << (((setf1 - setf2).find(2.235)) ? "true" : "false") << std::endl;
}

/**
	@brief test su tipi di dati string
	Test completo dell'interfaccia (tutti i metodi pubblici) della classe templata Set su dati di tipo string
  */
void test_string_set()
{
//////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	// Test su tipi di dati semplici (string)

	std::cout << "\n\n--- TEST SU DATI STRING ---\n"
			  << std::endl;

	// Test costruttore default
	std::cout << "- default constructor: " << std::endl;

	Set<std::string, string_equal> sets1;
	std::cout << "\tsetf1 = " << sets1 << std::endl;

	// Test add
	std::cout << "- add" << std::endl;

	std::cout << "\t\"dolor\" to " << sets1 << " -> ";
	sets1.add("dolor");
	std::cout << sets1 << std::endl;

	std::cout << "\t\"Ipsum\" to " << sets1 << " -> ";
	sets1.add("Ipsum");
	std::cout << sets1 << std::endl;

	std::cout << "\t\"Lorem\" to " << sets1 << " -> ";
	sets1.add("Lorem");
	std::cout << sets1 << std::endl;

	std::cout << "\t\"Ipsum\" to " << sets1 << " -> ";
	sets1.add("Ipsum");
	std::cout << sets1 << std::endl;

	std::cout << "\t\"\" to " << sets1 << " -> ";
	sets1.add("");
	std::cout << sets1 << std::endl;
	
	// Test remove
	std::cout << "- remove" << std::endl;

	std::cout << "\t\"Lorem\" from " << sets1 << " -> ";
	bool temp = sets1.remove("Lorem");
	std::cout << sets1 << " : " << (temp ? "true" : "false") << std::endl;

	std::cout << "\t\"amet\" from " << sets1 << " -> ";
	temp = sets1.remove("amet");
	std::cout << sets1 << " : " << (temp ? "true" : "false") << std::endl;

	std::cout << "\t\"\" from " << sets1 << " -> ";
	temp = sets1.remove("");
	std::cout << sets1 << " : " << (temp ? "true" : "false") << std::endl;

	// Test clear
	std::cout << "- clear" << std::endl;

	std::cout << '\t' << sets1 << " -> ";
	sets1.clear();
	std::cout << sets1 << std::endl;
	
	// Reset per test seguenti
	sets1.add("unde");
	sets1.add("perspiciatis");
	sets1.add("ut");
	sets1.add("Sed");	

	// Test copy constructor
	std::cout << "- copy constructor" << std::endl;

	std::cout << "\tsets1 = " << sets1 << std::endl;
	Set<std::string, string_equal> sets2 = Set<std::string, string_equal>(sets1);
	std::cout << "\tsets2 = " << sets2 << std::endl;

	// Test operator =
	std::cout << "- operator =" << std::endl;

	Set<std::string, string_equal> sets3;
	sets3 = sets2;
	std::cout << "\tsets3 = " << sets3 << std::endl;

	// Test costruttore con iterators
	std::cout << "- costruttore con iterators" << std::endl;

	Set<std::string, string_equal> sets4(sets3.begin(), sets3.end());
	std::cout << "\tsets4 = " << sets4 << std::endl;

	// Test operator []
	std::cout << "- operator []" << std::endl;

	std::cout << "\tsets1 = " << sets1 << std::endl;
	try
	{
		std::cout << "\tsets1[1] = " << sets1[1] << std::endl;
	}
	catch (myexcp_domain_error &e)
	{	
		std::cerr << e.what() << std::endl;
	}
	catch(myexcp_out_of_range &e)
	{
		std::cerr << e.what() << std::endl;
	}

	// Test operator ==
	std::cout << "- operator ==" << std::endl;

	sets2.remove("ut");
	std::cout << '\t' << sets1 << " == " << sets1 << " : " << ((sets1 == sets1) ? "true" : "false") << std::endl;
	std::cout << '\t' << sets1 << " == " << sets2 << " : " << ((sets1 == sets2) ? "true" : "false") << std::endl;
	std::cout << '\t' << sets1 << " == " << sets4 << " : " << ((sets1 == sets4) ? "true" : "false") << std::endl;

	// Test filter_out
	std::cout << "- filter_out (short)" << std::endl;

	string_is_short is_short_string;
	std::cout << '\t' << sets1 << " -> " << filter_out(sets1, is_short_string) << std::endl;

	// Reset per test seguenti
	sets1.clear();
	sets1.add("accusamus");
	sets1.add("at");
	sets1.add("eos");
	sets1.add("Vero");
	sets1.add("At");

	sets2.clear();
	sets2.add("");
	sets2.add("accusamus");
	sets2.add("iusto");
	sets2.add("Vero");

	sets3.clear();
	sets3.add("odio");
	sets3.add("dignissimos");

	// Test operator+
	std::cout << "- operator +" << std::endl;

	std::cout << '\t' << sets1 << " + " << sets2 << " = " << sets1 + sets2 << std::endl;
	std::cout << '\t' << sets2 << " + " << sets1 << " = " << sets2 + sets1 << std::endl;
	std::cout << '\t' << sets2 << " + " << sets3 << " = " << sets2 + sets3 << std::endl;

	// Test operator-
	std::cout << "- operator -" << std::endl;

	std::cout << '\t' << sets1 << " - " << sets2 << " = " << sets1 - sets2 << std::endl;
	std::cout << '\t' << sets2 << " - " << sets1 << " = " << sets2 - sets1 << std::endl;
	std::cout << '\t' << sets1 << " - " << sets3 << " = " << sets1 - sets3 << std::endl;

	// Test find
	std::cout << "- find " << std::endl;

	std::cout << "\t\"eos\" in " << sets1 << " : " << ((sets1.find("eos")) ? "true" : "false") << std::endl;
	std::cout << "\t\"odio\" in " << sets1 << " : " << ((sets1.find("odio")) ? "true" : "false") << std::endl;
	std::cout << "\t\"\" in " << (sets1 - sets2) << " : " << (((sets1 - sets2).find("")) ? "true" : "false") << std::endl;
}

/**
	@brief test su tipi di dati bool
	Test completo dell'interfaccia (tutti i metodi pubblici) della classe templata Set su dati di tipo bool
  */
void test_bool_set()
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	// Test su tipi di dati semplici (bool)
	std::cout << "\n\n--- TEST SU DATI BOOL ---\n"
			  << std::endl;

	// Test costruttore default
	std::cout << "- default constructor: " << std::endl;

	Set<bool, bool_equal> setb1;
	std::cout << "\tsetb1 = " << setb1 << std::endl;

	// Test add
	std::cout << "- add" << std::endl;

	std::cout << "\ttrue to " << setb1 << " -> ";
	setb1.add(true);
	std::cout << setb1 << std::endl;

	std::cout << "\tfalse to " << setb1 << " -> ";
	setb1.add(false);
	std::cout << setb1 << std::endl;

	std::cout << "\ttrue to " << setb1 << " -> ";
	setb1.add(true);
	std::cout << setb1 << std::endl;

	// Test remove
	std::cout << "- remove" << std::endl;

	std::cout << "\tfalse from " << setb1 << " -> ";
	bool temp = setb1.remove(false);
	std::cout << setb1 << " : " << (temp ? "true" : "false") << std::endl;

	// Test clear
	std::cout << "- clear" << std::endl;

	std::cout << '\t' << setb1 << " -> ";
	setb1.clear();
	std::cout << setb1 << std::endl;

	// Reset per test seguenti
	setb1.add(true);
	setb1.add(false);

	// Test copy constructor
	std::cout << "- copy constructor" << std::endl;

	std::cout << "\tsetb1 = " << setb1 << std::endl;
	Set<bool, bool_equal> setb2 = Set<bool, bool_equal>(setb1);
	std::cout << "\tsetb2 = " << setb2 << std::endl;

	// Test operator =
	std::cout << "- operator =" << std::endl;

	Set<bool, bool_equal> setb3;
	setb3 = setb2;
	std::cout << "\tsetb3 = " << setb3 << std::endl;

	// Test costruttore con iterators
	std::cout << "- costruttore con iterators" << std::endl;

	Set<bool, bool_equal> setb4(setb3.begin(), setb3.end());
	std::cout << "\tsetb4 = " << setb4 << std::endl;

	// Test operator []
	std::cout << "- operator []" << std::endl;

	std::cout << "\tsetb1 = " << setb1 << std::endl;
	try
	{
		std::cout << "\tsetb1[1] = " << setb1[1] << std::endl;
	}
	catch (myexcp_domain_error &e)
	{	
		std::cerr << e.what() << std::endl;
	}
	catch(myexcp_out_of_range &e)
	{
		std::cerr << e.what() << std::endl;
	}

	// Test operator ==
	std::cout << "- operator ==" << std::endl;

	setb2.remove(false);
	std::cout << '\t' << setb1 << " == " << setb1 << " : " << ((setb1 == setb1) ? "true" : "false") << std::endl;
	std::cout << '\t' << setb1 << " == " << setb2 << " : " << ((setb1 == setb2) ? "true" : "false") << std::endl;
	std::cout << '\t' << setb1 << " == " << setb4 << " : " << ((setb1 == setb4) ? "true" : "false") << std::endl;

	// Test filter_out
	std::cout << "- filter_out (true)" << std::endl;

	bool_is_true is_true;
	std::cout << '\t' << setb1 << " -> " << filter_out(setb1, is_true) << std::endl;

	// Reset per test seguenti
	setb1.clear();
	setb1.add(true);

	setb2.clear();
	setb2.add(false);

	setb3.clear();
	setb3.add(true);
	setb3.add(false);

	// Test operator+
	std::cout << "- operator +" << std::endl;

	std::cout << '\t' << setb1 << " + " << setb2 << " = " << setb1 + setb2 << std::endl;
	std::cout << '\t' << setb2 << " + " << setb1 << " = " << setb2 + setb1 << std::endl;
	std::cout << '\t' << setb2 << " + " << setb3 << " = " << setb2 + setb3 << std::endl;

	// Test operator-
	std::cout << "- operator -" << std::endl;

	std::cout << '\t' << setb1 << " - " << setb2 << " = " << setb1 - setb2 << std::endl;
	std::cout << '\t' << setb2 << " - " << setb1 << " = " << setb2 - setb1 << std::endl;
	std::cout << '\t' << setb1 << " - " << setb3 << " = " << setb1 - setb3 << std::endl;

	// Test find
	std::cout << "- find " << std::endl;

	std::cout << "\t1 in " << setb1 << " : " << ((setb1.find(1)) ? "true" : "false") << std::endl;
	std::cout << "\t0 in " << setb1 << " : " << ((setb1.find(0)) ? "true" : "false") << std::endl;
	std::cout << "\t-3 in " << (setb1 - setb2) << " : " << (((setb1 - setb2).find(-3)) ? "true" : "false") << std::endl;
}

/**
	@brief test su tipi di dati int
	Test completo dell'interfaccia (tutti i metodi pubblici) della classe templata Set su dati di tipo int, utilizzando Set vuoti
  */
void test_empty_set()
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	// Test su Set vuoti
	std::cout << "\n\n--- TEST SU SET VUOTI ---\n"
			  << std::endl;

	// Test costruttore default
	std::cout << "- default constructor: " << std::endl;

	Set<int, int_equal> set0;
	std::cout << "\tset0 = " << set0 << std::endl;

	// Test add
	std::cout << "- add" << std::endl;

	std::cout << "\t0 to " << set0 << " -> ";
	set0.add(0);
	std::cout << set0 << std::endl;

	// Test remove
	std::cout << "- remove" << std::endl;

	std::cout << "\t0 from " << set0 << " -> ";
	bool temp = set0.remove(0);
	std::cout << set0 << " : " << (temp ? "true" : "false") << std::endl;

	std::cout << "\t0 from " << set0 << " -> ";
	temp = set0.remove(0);
	std::cout << set0 << " : " << (temp ? "true" : "false") << std::endl;

	// Test clear
	std::cout << "- clear" << std::endl;

	std::cout << '\t' << set0 << " -> ";
	set0.clear();
	std::cout << set0 << std::endl;

	// Test copy constructor
	std::cout << "- copy constructor" << std::endl;

	std::cout << "\tset0 = " << set0 << std::endl;
	Set<int, int_equal> set01 = Set<int, int_equal>(set0);
	std::cout << "\tset01 = " << set01 << std::endl;

	// Test operator =
	std::cout << "- operator =" << std::endl;

	set01.add(1);
	std::cout << '\t' << set01 << " -> ";
	set01 = set0;
	std::cout << set01 << std::endl;

	// Test costruttore con iterators
	std::cout << "- costruttore con iterators" << std::endl;

	Set<int, int_equal> set02(set0.begin(), set0.end());
	std::cout << "\tset02 = " << set02 << std::endl;

	// Test operator []
	std::cout << "- operator []" << std::endl;

	std::cout << "\tset0 = " << set0 << std::endl;
	try
	{
		std::cout << "\tset0[0] = " << set0[0] << std::endl;
	}
	catch (myexcp_domain_error &e)
	{	
		std::cerr << e.what() << std::endl;
	}
	catch(myexcp_out_of_range &e)
	{
		std::cerr << e.what() << std::endl;
	}

	// Test operator ==
	std::cout << "- operator ==" << std::endl;

	set01.add(1);

	std::cout << '\t' << set0 << " == " << set01 << " : " << ((set0 == set01) ? "true" : "false") << std::endl;
	std::cout << '\t' << set0 << " == " << set0 << " : " << ((set0 == set0) ? "true" : "false") << std::endl;

	// Test filter_out
	std::cout << "- filter_out (positive)" << std::endl;

	int_is_positive is_pos_int;
	std::cout << '\t' << set0 << " -> " << filter_out(set0, is_pos_int) << std::endl;

	// Test operator+
	std::cout << "- operator +" << std::endl;

	std::cout << '\t' << set0 << " + " << set0 << " = " << set0 + set0 << std::endl;
	std::cout << '\t' << set0 << " + " << set01 << " = " << set0 + set01 << std::endl;

	// Test operator-
	std::cout << "- operator -" << std::endl;

	std::cout << '\t' << set0 << " - " << set0 << " = " << set0 - set0 << std::endl;
	std::cout << '\t' << set0 << " - " << set01 << " = " << set0 - set01 << std::endl;

	// Test find
	std::cout << "- find " << std::endl;

	std::cout << "\t0 in " << set0 << " : " << ((set0.find(0)) ? "true" : "false") << std::endl;
}

/**
	@brief test su tipi di dati person
	Test completo dell'interfaccia (tutti i metodi pubblici) della classe templata Set su dati di tipo person (custom struct)
  */
void test_person_set()
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	// Test su tipi di dati complessi (person)
	std::cout << "\n\n--- TEST SU DATI PERSON ---\n"
			  << std::endl;
	struct person p1 = {"Ugo", "Ughi", 32};
	struct person p2 = {"Ugo", "Ughi", 7};
	struct person p3 = {"Ugo", "Ughi", 32};
	struct person p4 = {"Ada", "Adi", 87};
	struct person p5 = {"Ian", "Iani", 16};
	struct person p6 = {"Leo", "Lei", 46};
	struct person p7 = {"Mia", "Mei", 65};
	struct person p8 = {"Eva", "Evi", 4};
	struct person p9 = {"Noa", "Noi", 1};

	// Test costruttore default
	std::cout << "- default constructor: " << std::endl;

	Set<person, person_equal> setp1;
	std::cout << "\tsetp1 = " << setp1 << std::endl;

	// Test add
	std::cout << "- add" << std::endl;

	std::cout << "\t[Ugo Ughi, 32] to " << setp1 << " -> ";
	setp1.add(p1);
	std::cout << setp1 << std::endl;

	std::cout << "\t[Ugo Ughi, 7] to " << setp1 << " -> ";
	setp1.add(p2);
	std::cout << setp1 << std::endl;

	std::cout << "\t[Ugo Ughi, 32] to " << setp1 << " -> ";
	setp1.add(p3);
	std::cout << setp1 << std::endl;

	std::cout << "\t[Ada Adi, 87] to " << setp1 << " -> ";
	setp1.add(p4);
	std::cout << setp1 << std::endl;

	// Test remove
	std::cout << "- remove" << std::endl;

	std::cout << "\t[Ugo Ughi, 32] from " << setp1 << " -> ";
	bool temp = setp1.remove(p3);
	std::cout << setp1 << " : " << (temp ? "true" : "false") << std::endl;

	std::cout << "\t[Ian Iani, 65] from " << setp1 << " -> ";
	temp = setp1.remove(p5);
	std::cout << setp1 << " : " << (temp ? "true" : "false") << std::endl;

	// Test clear
	std::cout << "- clear" << std::endl;

	std::cout << '\t' << setp1 << " -> ";
	setp1.clear();
	std::cout << setp1 << std::endl;

	// Reset per test seguenti
	setp1.add(p1);
	setp1.add(p4);
	setp1.add(p5);
	setp1.add(p6);

	// Test copy constructor
	std::cout << "- copy constructor" << std::endl;

	std::cout << "\tsetp1 = " << setp1 << std::endl;
	Set<person, person_equal> setp2 = Set<person, person_equal>(setp1);
	std::cout << "\tsetp2 = " << setp2 << std::endl;

	// Test operator =
	std::cout << "- operator =" << std::endl;

	Set<person, person_equal> setp3;
	setp3 = setp2;
	std::cout << "\tsetp3 = " << setp3 << std::endl;

	// Test costruttore con iterators
	std::cout << "- costruttore con iterators" << std::endl;

	Set<person, person_equal> setp4(setp3.begin(), setp3.end());
	std::cout << "\tsetp4 = " << setp4 << std::endl;

	// Test operator []
	std::cout << "- operator []" << std::endl;

	std::cout << "\tsetp1 = " << setp1 << std::endl;
	try
	{
		std::cout << "\tsetp1[1] = " << setp1[1] << std::endl;
	}
	catch (myexcp_domain_error &e)
	{	
		std::cerr << e.what() << std::endl;
	}
	catch(myexcp_out_of_range &e)
	{
		std::cerr << e.what() << std::endl;
	}

	// Test operator ==
	std::cout << "- operator ==" << std::endl;

	setp2.remove(p5);
	std::cout << '\t' << setp1 << " == " << setp1 << " : " << ((setp1 == setp1) ? "true" : "false") << std::endl;
	std::cout << '\t' << setp1 << " == " << setp2 << " : " << ((setp1 == setp2) ? "true" : "false") << std::endl;
	std::cout << '\t' << setp1 << " == " << setp4 << " : " << ((setp1 == setp4) ? "true" : "false") << std::endl;

	// Test filter_out
	std::cout << "- filter_out (old)" << std::endl;

	person_is_old is_old_person;
	std::cout << '\t' << setp1 << " -> " << filter_out(setp1, is_old_person) << std::endl;

	// Reset per test seguenti
	setp1.clear();
	setp1.add(p1);
	setp1.add(p4);

	setp2.clear();
	setp2.add(p2);
	setp2.add(p3);
	setp2.add(p8);

	setp3.clear();
	setp3.add(p9);

	// Test operator+
	std::cout << "- operator +" << std::endl;

	std::cout << '\t' << setp1 << " + " << setp2 << " = " << setp1 + setp2 << std::endl;
	std::cout << '\t' << setp2 << " + " << setp1 << " = " << setp2 + setp1 << std::endl;
	std::cout << '\t' << setp2 << " + " << setp3 << " = " << setp2 + setp3 << std::endl;

	// Test operator-
	std::cout << "- operator -" << std::endl;

	std::cout << '\t' << setp1 << " - " << setp2 << " = " << setp1 - setp2 << std::endl;
	std::cout << '\t' << setp2 << " - " << setp1 << " = " << setp2 - setp1 << std::endl;
	std::cout << '\t' << setp1 << " - " << setp3 << " = " << setp1 - setp3 << std::endl;

	// Test find
	std::cout << "- find " << std::endl;

	std::cout << "\t[Ada Adi, 87] in " << setp1 << " : " << ((setp1.find(p4)) ? "true" : "false") << std::endl;
	std::cout << "\t[Ugo Ughi, 7] in " << setp1 << " : " << ((setp1.find(p2)) ? "true" : "false") << std::endl;
	std::cout << "\t[Ugo Ughi, 32] in " << (setp1 - setp2) << " : " << (((setp1 - setp2).find(p1)) ? "true" : "false") << std::endl;
}

/**
	@brief test su tipi di dati Set
	Test completo dell'interfaccia (tutti i metodi pubblici) della classe templata Set su dati di tipo Set (Set di Sets)
  */
void test_sets_set()
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	// Test su tipi di dati complessi (set di set)
	std::cout << "\n\n--- TEST SU SET DI SET ---\n"
			  << std::endl;

	Set<int, int_equal> set0;
	Set<int, int_equal> set1;
	set1.add(0);
	set1.add(-5);
	set1.add(7);
	set1.add(12);
	set1.add(-4);
	Set<int, int_equal> set2;
	set2.add(8);
	set2.add(6);
	Set<int, int_equal> set3;
	set1.add(7);
	set1.add(23);
	set1.add(-5);
	set1.add(0);

	std::cout << "\tset1= " << set1 << std::endl;
	std::cout << "\tset2 = " << set2 << std::endl;
	std::cout << "\tset3 = " << set3 << std::endl;

	std::cout << std::endl;

	// Test costruttore default
	std::cout << "- default constructor: " << std::endl;

	Set<Set<int, int_equal>, set_int_equal> setset1;
	std::cout << "\tsetset1 = " << setset1 << std::endl;

	// Test add
	std::cout << "- add" << std::endl;

	std::cout << '\t' << set1 << " to " << setset1 << " -> ";
	setset1.add(set1);
	std::cout << setset1 << std::endl;

	std::cout << '\t' << set3 << " to " << setset1 << " -> ";
	setset1.add(set3);
	std::cout << setset1 << std::endl;

	std::cout << '\t' << set1 << " to " << setset1 << " -> ";
	setset1.add(set1);
	std::cout << setset1 << std::endl;

	// Test remove
	std::cout << "- remove" << std::endl;

	std::cout << '\t' << set1 << " from " << setset1 << " -> ";
	bool temp = setset1.remove(set1);
	std::cout << setset1 << " : " << (temp ? "true" : "false") << std::endl;

	std::cout << '\t' << set2 << " from " << setset1 << " -> ";
	temp = setset1.remove(set2);
	std::cout << setset1 << " : " << (temp ? "true" : "false") << std::endl;

	// Test clear
	std::cout << "- clear" << std::endl;

	std::cout << '\t' << setset1 << " -> ";
	setset1.clear();
	std::cout << setset1 << std::endl;

	// Reset per test seguenti
	setset1.add(set1);
	setset1.add(set2);
	setset1.add(set0);
	setset1.add(set3);

	// Test copy constructor
	std::cout << "- copy constructor" << std::endl;

	std::cout << "\tsetset1 = " << setset1 << std::endl;
	Set<Set<int, int_equal>, set_int_equal> setset2 = Set<Set<int, int_equal>, set_int_equal>(setset1);
	std::cout << "\tsetset2 = " << setset2 << std::endl;

	// Test operator =
	std::cout << "- operator =" << std::endl;

	Set<Set<int, int_equal>, set_int_equal> setset3;
	setset3 = setset2;
	std::cout << "\tsetset3 = " << setset3 << std::endl;

	// Test costruttore con iterators
	std::cout << "- costruttore con iterators" << std::endl;

	Set<Set<int, int_equal>, set_int_equal> setset4(setset3.begin(), setset3.end());
	std::cout << "\tsetset4 = " << setset4 << std::endl;

	// Test operator []
	std::cout << "- operator []" << std::endl;

	std::cout << "\tsetset1 = " << setset1 << std::endl;
	try
	{
		std::cout << "\tsetset1[1] = " << setset1[1] << std::endl;
	}
	catch (myexcp_domain_error &e)
	{	
		std::cerr << e.what() << std::endl;
	}
	catch(myexcp_out_of_range &e)
	{
		std::cerr << e.what() << std::endl;
	}
	try
	{
		std::cout << "\tsetset1[2][2] = " << setset1[2][2] << std::endl;
	}
	catch (myexcp_domain_error &e)
	{	
		std::cerr << e.what() << std::endl;
	}
	catch(myexcp_out_of_range &e)
	{
		std::cerr << e.what() << std::endl;
	}

	// Test operator ==
	std::cout << "- operator ==" << std::endl;

	setset2.remove(set2);
	std::cout << '\t' << setset1 << " == " << setset1 << " : " << ((setset1 == setset1) ? "true" : "false") << std::endl;
	std::cout << '\t' << setset1 << " == " << setset2 << " : " << ((setset1 == setset2) ? "true" : "false") << std::endl;
	std::cout << '\t' << setset1 << " == " << setset4 << " : " << ((setset1 == setset4) ? "true" : "false") << std::endl;

	// Test filter_out
	std::cout << "- filter_out (large)" << std::endl;

	set_is_large is_set_large;
	std::cout << '\t' << setset1 << " -> " << filter_out(setset1, is_set_large) << std::endl;

	// Reset per test seguenti
	setset1.clear();
	setset1.add(set1);
	setset1.add(set2);

	setset2.clear();
	setset2.add(set1);
	setset2.add(set3);

	setset3.clear();
	setset3.add(set1);

	// Test operator+
	std::cout << "- operator +" << std::endl;

	std::cout << '\t' << setset1 << " + " << setset2 << " = " << setset1 + setset2 << std::endl;
	std::cout << '\t' << setset2 << " + " << setset1 << " = " << setset2 + setset1 << std::endl;
	std::cout << '\t' << setset2 << " + " << setset3 << " = " << setset2 + setset3 << std::endl;

	// Test operator-
	std::cout << "- operator -" << std::endl;

	std::cout << '\t' << setset1 << " - " << setset2 << " = " << setset1 - setset2 << std::endl;
	std::cout << '\t' << setset2 << " - " << setset1 << " = " << setset2 - setset1 << std::endl;
	std::cout << '\t' << setset1 << " - " << setset3 << " = " << setset1 - setset3 << std::endl;

	// Test find
	std::cout << "- find " << std::endl;

	std::cout << '\t' << set1 << " in " << setset1 << " : " << ((setset1.find(set1)) ? "true" : "false") << std::endl;
	std::cout << '\t' << set2 << " in " << setset1 << " : " << ((setset1.find(set2)) ? "true" : "false") << std::endl;
}
/**
	@brief test sui const_iterator
	Test completo dell'interfaccia (tutti i metodi pubblici) della classe const_iterator interna alla classe Set
  */
void test_const_iterator()
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	// Test su constant_iterator

	std::cout << "\n\n--- CONSTANT ITERATOR ---\n"
			  << std::endl;

	Set<int, int_equal> set1;
	set1.add(0);
	set1.add(-5);
	set1.add(7);
	set1.add(12);
	set1.add(-4);
	std::cout << "set1 = " << set1 << std::endl;

	// Test costruttore default
	Set<int, int_equal>::const_iterator ci;
	Set<int, int_equal>::const_iterator ce;

	// Test assegnamento e begin()/end()
	ci = set1.begin();
	ce = set1.end();

	// Test dereferenziamento
	std::cout << "- dereferenziamento: " << std::endl;
	try
	{
		std::cout << "\t*(ci) = " << *ci << std::endl;
	}
	catch (myexcp_domain_error &e)
	{	
		std::cerr << e.what() << std::endl;
	}
	catch(myexcp_out_of_range &e)
	{
		std::cerr << e.what() << std::endl;
	}
	try
	{
		std::cout << "\t*(ce) = " << *ce << std::endl;
	}
	catch (myexcp_domain_error &e)
	{	
		std::cerr << e.what() << std::endl;
	}
	catch(myexcp_out_of_range &e)
	{
		std::cerr << e.what() << std::endl;
	}
	// Test pre-incremento
	std::cout << "- pre-incremento: " << std::endl;
	try
	{
		std::cout << "\t*(++ci) = " << *(++ci) << std::endl;
	}
	catch (myexcp_domain_error &e)
	{	
		std::cerr << e.what() << std::endl;
	}
	catch(myexcp_out_of_range &e)
	{
		std::cerr << e.what() << std::endl;
	}
	try
	{
		std::cout << "\t*(++ce) = " << *(++ce) << std::endl;
	}
	catch (myexcp_domain_error &e)
	{	
		std::cerr << e.what() << std::endl;
	}
	catch(myexcp_out_of_range &e)
	{
		std::cerr << e.what() << std::endl;
	}
	// Test post-incremento
	std::cout << "- post-incremento: " << std::endl;
	try
	{
		std::cout << "\t*(ci++) = " << *(ci++) << std::endl;
	}
	catch (myexcp_domain_error &e)
	{	
		std::cerr << e.what() << std::endl;
	}
	catch(myexcp_out_of_range &e)
	{
		std::cerr << e.what() << std::endl;
	}
	try
	{
		std::cout << "\t*(ci) = " << *ci << std::endl;
	}
	catch (myexcp_domain_error &e)
	{	
		std::cerr << e.what() << std::endl;
	}
	catch(myexcp_out_of_range &e)
	{
		std::cerr << e.what() << std::endl;
	}
	try
	{
		std::cout << "\t*(ce++) = " << *(ce++) << std::endl;
	}
	catch (myexcp_domain_error &e)
	{	
		std::cerr << e.what() << std::endl;
	}
	catch(myexcp_out_of_range &e)
	{
		std::cerr << e.what() << std::endl;
	}
	try
	{
		std::cout << "\t*(ce) = " << *ce << std::endl;
	}
	catch (myexcp_domain_error &e)
	{	
		std::cerr << e.what() << std::endl;
	}
	catch(myexcp_out_of_range &e)
	{
		std::cerr << e.what() << std::endl;
	}

	// Test copy constructor
	std::cout << "- copy constructor" << std::endl;
	Set<int, int_equal>::const_iterator ci2 = Set<int, int_equal>::const_iterator(ci);
	std::cout << "\t*(ci2) = " << *ci2 << std::endl;

	// Test operator =
	std::cout << "- operator =" << std::endl;
	Set<int, int_equal>::const_iterator ci3;
	ci3 = ci2;
	std::cout << "\t*(ci3) = " << *ci3 << std::endl;

	// Test operator ==
	std::cout << "- operator ==" << std::endl;
	bool temp = (ci == ci2);
	std::cout << "\tci == ci2"
			  << " : " << (temp ? "true" : "false") << std::endl;
	// Test operator !=
	std::cout << "- operator !=" << std::endl;
	temp = (ci != ++ci2);
	std::cout << "\tci != ++ci2"
			  << " : " << (temp ? "true" : "false") << std::endl;

	// Test operator ->
	std::cout << "- operator ->" << std::endl;
	struct person p1 = {"Ada", "Adi", 87};
	Set<person, person_equal> setp1;
	setp1.add(p1);

	Set<person, person_equal>::const_iterator cip = setp1.begin();
	std::cout << "\t*(cip) = " << *cip << std::endl;
	std::cout << "\t(cip)->age = " << cip->age << std::endl;
}

int main()
{
	test_int_set();
	test_const_set();
	test_float_set();
	test_string_set();
	test_bool_set();
	test_empty_set();
	test_person_set();
	test_sets_set();
	test_const_iterator();

	return 0;
}
// Test distruttore