#include <sstream>
#include <string>
#include "Expression.h"

using namespace std;

#define nTemp 10

extern map<string, int> vars;
map<string, int> varsTemp; // false vacio; true ocupado
const char *temps[] = {"$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7", "$t8", "$t9"};

void showTemp(){
  for (int i = 0; i < nTemp; i++)
        cout<<"vars["<<i<<"]: "<<varsTemp[temps[i]]<<endl;
}

string newTemp(){
  int i;
  for (i = 0; i < nTemp; i++){
    if (varsTemp.find(temps[i]) == varsTemp.end()) {
        varsTemp[temps[i]] = 1;;
        cout<<"             TEMP ["<<temps[i]<<"]: "<<varsTemp[temps[i]]<<endl;
        return string(temps[i]);
    }
  }
  //cout<<"             TEMP i: "<<i<<endl;
  return string ("");
}

void releaseTemp(string reg){
    cout<<" RELEASE: "<<reg<<endl;
    varsTemp.erase(reg);
    showTemp();
}

void releaseAllTemp(){
  for (int i = 0; i < nTemp; i++)
        releaseTemp(temps[i]);
}

string AddExpression::getCode(){
  stringstream code;

  if (expr1->getKind()==INT_EXPR && expr2->getKind()==INT_EXPR){
    value = expr1->Evaluate() + expr2->Evaluate();
    code << " ";
  }
  else if (expr1->getKind()==INT_EXPR){
            lugar = newTemp();
            code << expr2->getCode() << endl <<
                  "addi " << lugar << ", " << expr2->lugar << ", " <<
                  expr1->Evaluate();
            //releaseTemp(expr2->lugar);
       }
       else if (expr2->getKind()==INT_EXPR) {
                lugar = newTemp();
                code << expr1->getCode() << endl <<
                      "addi " << lugar << ", " << expr1->lugar << ", " <<
                      expr2->Evaluate();
              //  releaseTemp(expr1->lugar);
       }
       else {
          lugar = newTemp();
          code << expr1->getCode() << endl <<
                  expr2->getCode() << endl <<
                  "add " << lugar << ", " << expr1->lugar << ", " <<
                  expr2->lugar;
       }
  return code.str();
}

string SubExpression::getCode(){
  stringstream code;

  if (expr1->getKind()==INT_EXPR && expr2->getKind()==INT_EXPR){
    value = expr1->Evaluate() - expr2->Evaluate();
    code << " ";
  }
  else if (expr2->getKind()==INT_EXPR) {
           lugar = newTemp();
           code << expr1->getCode() << endl <<
                 "addi " << lugar << ", " << expr1->lugar << ", " <<
                 (expr2->Evaluate()*(-1));
           //releaseTemp(expr1->lugar);
  }
  else if (expr1->getKind()==INT_EXPR){
            lugar = newTemp();
            string lugarTemp = newTemp();
            stringstream codeTemp;
            codeTemp << "li " << lugarTemp << ", " << expr1->Evaluate();
            code << expr2->getCode() << endl <<
                  codeTemp.str() << endl <<
                  "sub " << lugar << ", " << lugarTemp << ", " <<
                  expr2->lugar;
            //releaseTemp(expr2->lugar);
       }
       else {
          lugar = newTemp();
          code << expr1->getCode() << endl <<
                  expr2->getCode() << endl <<
                  "sub " << lugar << ", " << expr1->lugar << ", " <<
                  expr2->lugar;
       }
   //releaseTemp(expr1->lugar);
   //releaseTemp(expr2->lugar);
  return code.str();
}

string MultExpression::getCode(){
  stringstream code;

  lugar = newTemp();
  code << expr1->getCode() << endl <<
          expr2->getCode() << endl <<
          "mult " << expr1->lugar << ", " << expr2->lugar << endl <<
          "mflo " << lugar;
  //releaseTemp(expr1->lugar);
  //releaseTemp(expr2->lugar);
  return code.str();
}

string DivExpression::getCode(){
  stringstream code;
  lugar = newTemp();
  code << expr1->getCode() << endl <<
          expr2->getCode() << endl <<
          "div " << expr1->lugar << ", " << expr2->lugar << endl <<
          "mflo " << lugar;
  //releaseTemp(expr1->lugar);
  //releaseTemp(expr2->lugar);

  return code.str();
}

string IntExpression::getCode(){
  stringstream code;
  lugar = newTemp();
  code << "li "<< lugar << ", " << value;
  return code.str();
}

string IdExpression::getCode(){
  stringstream code;
  lugar = newTemp();
  code << "li "<< lugar << ", " << vars[id];
  //releaseTemp(lugar);
  return code.str();
}
