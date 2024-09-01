#include "myexcp.h"

myexcp_domain_error::myexcp_domain_error(const std::string &message) 
	: std::domain_error(message) {}
myexcp_domain_error::myexcp_domain_error() 
	: std::domain_error("Generic domain error") {}

myexcp_out_of_range::myexcp_out_of_range(const std::string &message) 
	: std::out_of_range(message) {}
myexcp_out_of_range::myexcp_out_of_range() 
	: std::out_of_range("Generic out_of_range error") {}
