#ifndef ERROR_H
#define ERROR_H

#include <string>
#include <exception>

class Error
{
private:
    std::string msg;

public:
    Error(std::string msg);

    ~Error() throw() {}
    virtual const char* what() const throw()
    {
        return msg.c_str();
    }
};

#endif // ERROR_H
