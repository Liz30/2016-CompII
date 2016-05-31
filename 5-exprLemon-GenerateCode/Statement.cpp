#include <string>
#include <iostream>
#include <list>
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
      it++;
    }
    //showVars();
}
