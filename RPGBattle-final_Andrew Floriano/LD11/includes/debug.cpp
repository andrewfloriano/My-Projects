#include "debug.h"

debugObj::debugObj()
{
	logFileName="debug.log";
}

debugObj::debugObj(const char* fileName)
{
	logFileName=fileName;
}

void debugObj::setState(bool in)
{
	active=in;
	if(active)
	{
		logFile.open(logFileName,std::ios::out);
		logFile<<"Logging program to debug.log"<<std::endl;
		logFile.close();
	}
}

void debugObj::ErrorOut(const char* errorMessage)
{
	if(!active)
	{
		return;
	}
     logFile.open(logFileName,std::ios::app);
     logFile<<"\nError: "<<errorMessage;
     logFile.close();
}

void debugObj::ErrorOut(const char* errorMessage, const char * other)
{
    if(!active)
	{
		return;
	}
     logFile.open(logFileName,std::ios::app);
     logFile<<"\nError: "<<errorMessage<<other;
     logFile.close();
}

void debugObj::ErrorOut(const char* errorMessage, const int other)
{
    if(!active)
	{
		return;
	}
     logFile.open(logFileName,std::ios::app);
     logFile<<"\nError: "<<errorMessage<<" Number: "<<other;
     logFile.close();
}

void debugObj::Msg(const char* debugMessage)
{
    if(!active)
	{
		return;
	}
     logFile.open(logFileName,std::ios::app);
     logFile<<"\nDebug Message: "<<debugMessage;
     logFile.close();
}

void debugObj::Msg(const char* debugMessage, const char * other)
{
    if(!active)
	{
		return;
	}
     logFile.open(logFileName,std::ios::app);
     logFile<<"\nDebug Message: "<<debugMessage<<other;
     logFile.close();
}

void debugObj::Msg(const char* errorMessage, const int other)
{
    if(!active)
	{
		return;
	}
     logFile.open(logFileName,std::ios::app);
     logFile<<"\nDebug Message: "<<errorMessage<<" : "<<other;
     logFile.close();
}
