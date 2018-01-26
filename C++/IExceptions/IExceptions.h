//
//  IExceptions.h
//  RNN
//
//  Created by Daniel Solovich on 1/3/18.
//  Copyright © 2018 Daniel Solovich. All rights reserved.
//

#ifndef IExceptions_h
#define IExceptions_h

#include "stacktrace.h"


class IExcpetions
{
public:
    std::string backtrace = Backtrace(1); 
    virtual std::string getError() = 0;
};

class SizeError : public IExcpetions
{
private:
    const std::string error = "number of strings or number of rows in first matrix does not equal to second matrix number of strings or number of rows";
public:
    std::string getError() override
    {
        return error;
    }
};

class NoDataInMemoryException : public IExcpetions
{
private:
    const std::string error = "no data in memory";
public:
    std::string getError() override
    {
        return error;
    }
};

class ImageHasNoData : public IExcpetions
{
private:
    const std::string error = "image has no data yet";
public:
    std::string getError() override
    {
        return error;
    }
};

class FileNotFoundException : public IExcpetions
{
private:
    const std::string error = "file was not found";
public:
    virtual std::string getError() override
    {
        return error;
    }
};




#endif /* IExceptions_h */
