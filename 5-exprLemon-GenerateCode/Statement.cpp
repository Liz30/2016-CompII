#include <string>
#include <iostream>
#include <list>
#include <sstream>
#include "Expression.h"
#include "Statement.h"

using namespace std;

void showVars(){
  map<string, int>::iterator oi;
  for (oi=vars.begin(); oi != vars.end(); ++oi)
      cout<<oi->first<<"  =  "<<oi->second<<endl;
}

void PrintStatement::Execute(){
    //cout<<"Vars PRINT: "<<vars.size()<<endl;
    //cout<<endl<<"Expr_List: "<<expr_list->size()<<endl;
    ExpressionList::iterator it = expr_list->begin();
    while (it != expr_list->end()){
      Expression* n = *it;
      cout<<n->Evaluate()<<endl;
      //cout << n->getCode()<<endl;
      it++;
    }
    //showVars();
}

string PrintStatement::getCode(){
  stringstream code;
  ExpressionList::iterator it = expr_list->begin();
  while (it != expr_list->end()){
    Expression* n = *it;
    if (n->getCode().isConstant){
      string lugarTemp = newTemp();
      cout << "li " << lugarTemp << ", " << n->getCode().value << endl <<
              "move $a0, " << lugarTemp << endl <<
              "li   $v0, 1" << endl <<
              "syscall" << endl << endl;
      releaseTemp(lugarTemp);
    } else {
        cout << n->getCode().code << endl <<
                "move $a0, " << n->lugar<< endl <<
                "li   $v0, 1" << endl <<
                "syscall" << endl << endl;
    }
    releaseTemp(n->lugar);

    it++;
  }
  //releaseAllTemp();
  //showTemp();
  return code.str();
}

string AssignStatement::getCode(){
  stringstream code;

  return code.str();
}

string TextStatement::getCode(){
  stringstream code;
  return code.str();
}
