#ifndef MYEXCP_H
#define MYEXCP_H

#include <stdexcept>
#include <string>

/**
	Classe eccezione custom che deriva da std::domain_error
*/
class myexcp_domain_error : public std::domain_error {
public:
	/**
		Costruttore di default
	*/
	myexcp_domain_error();

	/**
		Costruttore che prende un messaggio d'errore
	*/
	myexcp_domain_error(const std::string &message);
};

/**
	Classe eccezione custom che deriva da std::out_of_range
*/
class myexcp_out_of_range : public std::out_of_range {
public:
	/**
		Costruttore di default
	*/
	myexcp_out_of_range();

	/**
		Costruttore che prende un messaggio d'errore
	*/
	myexcp_out_of_range(const std::string &message);
};

#endif