#ifndef DEBUG_H
#define DEBUG_H

#include <fstream>

class debugObj
{
 	  private:
	  		  std::ofstream logFile;
	  		  const char * logFileName;
	  		  bool active;
	  public:
	  		  debugObj();
	  		  debugObj(const char *);
	  		  void setState(bool);
	  		  void ErrorOut(const char *);
	  		  void ErrorOut(const char *, const char*);
	  		  void ErrorOut(const char *, const int);
	  		  void Msg(const char *);
	  		  void Msg(const char *, const char *);
	  		  void Msg(const char *, const int);
};

#endif
