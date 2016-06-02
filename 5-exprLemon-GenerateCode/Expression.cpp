#include <sstream>
#include <string>
#include "Expression.h"

using namespace std;

#define nTemp 10

extern map<string, int> vars;
map<string, int> varsTemp; // false vacio; true ocupado
const char* temps[] = {"$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7", "$t8", "$t9"};

void showTemp(){
  for (int i = 0; i < nTemp; i++)
        cout<<"vars["<<i<<"]: "<<varsTemp[temps[i]]<<endl;
}

string newTemp(){
  int i;
  for (i = 0; i < nTemp; i++){
    if (varsTemp.find(temps[i]) == varsTemp.end()) {
        varsTemp[temps[i]] = 1;;
        //cout<<"             TEMP ["<<temps[i]<<"]: "<<varsTemp[temps[i]]<<endl;
        return string(temps[i]);
    }
  }
  //cout<<"             TEMP i: "<<i<<endl;
  return string ("");
}

void releaseTemp(string reg){
    //cout<<" RELEASE: "<<reg<<endl;
    varsTemp.erase(reg);
    //showTemp();
}

void releaseAllTemp(){
  for (int i = 0; i < nTemp; i++)
        releaseTemp(string(temps[i]));
}

Result AddExpression::getCode(){
  stringstream code;
  Result r;// = new Result;
  Result expr1_r = expr1->getCode();
  Result expr2_r = expr2->getCode();

  if (expr1_r.isConstant && expr2_r.isConstant){
    r.value = expr1->Evaluate() + expr2->Evaluate();
    r.code = "";
    r.isConstant = true;
    //cout << "                   VALUE: "<<r.value<<endl;
  }
  else if (expr1_r.isConstant){
            lugar = newTemp();
            code << expr2_r.code << endl <<
                  "addi " << lugar << ", " << expr2->lugar << ", " <<
                  expr1->Evaluate();
            releaseTemp(expr2->lugar);
            r.code = code.str();
            r.value = 0;
            r.isConstant = false;
       }
       else if (expr2_r.isConstant) {
                lugar = newTemp();
                code << expr1_r.code << endl <<
                      "addi " << lugar << ", " << expr1->lugar << ", " <<
                      expr2->Evaluate();
                releaseTemp(expr1->lugar);
                r.code = code.str();
                r.value = 0;
                r.isConstant = false;
       }
       else {
          lugar = newTemp();
          code << expr1_r.code << endl <<
                  expr2_r.code << endl <<
                  "add " << lugar << ", " << expr1->lugar << ", " <<
                  expr2->lugar;
          r.code = code.str();
          r.value = 0;
          r.isConstant = false;
          releaseTemp(expr1->lugar);
          releaseTemp(expr2->lugar);
       }
  return r;
}

Result SubExpression::getCode(){
  stringstream code;
  Result r;
  Result expr1_r = expr1->getCode();
  Result expr2_r = expr2->getCode();

  if (expr1_r.isConstant && expr2_r.isConstant){
    r.value = expr1->Evaluate() - expr2->Evaluate();
    r.code = "";
    r.isConstant = true;
  }
  else if (expr2_r.isConstant) {
           lugar = newTemp();
           code << expr1_r.code << endl <<
                 "addi " << lugar << ", " << expr1->lugar << ", " <<
                 (expr2->Evaluate()*(-1));
           releaseTemp(expr1->lugar);
           r.code = code.str();
           r.value = 0;
           r.isConstant = false;
  }
  else if (expr1_r.isConstant){
            lugar = newTemp();
            string lugarTemp = newTemp();
            stringstream codeTemp;
            codeTemp << "li " << lugarTemp << ", " << expr1->Evaluate();
            code << expr2_r.code << endl <<
                  codeTemp.str() << endl <<
                  "sub " << lugar << ", " << lugarTemp << ", " <<
                  expr2->lugar;
            releaseTemp(expr2->lugar);
            releaseTemp(lugarTemp);
            r.code = code.str();
            r.value = 0;
            r.isConstant = false;
       }
       else {
          lugar = newTemp();
          code << expr1_r.code << endl <<
                  expr2_r.code << endl <<
                  "sub " << lugar << ", " << expr1->lugar << ", " <<
                  expr2->lugar;
          r.code = code.str();
          r.value = 0;
          r.isConstant = false;
          releaseTemp(expr1->lugar);
          releaseTemp(expr2->lugar);
       }
  return r;
}

string LoadConstant(IntExpression* e){
    stringstream code;
    string lugar = newTemp();
    code << "li "<< lugar << ", " << e->value;
    e->lugar = lugar;
    return code.str();
}

Result MultExpression::getCode(){
  stringstream code;
  Result r;
  Result expr1_r = expr1->getCode();
  Result expr2_r = expr2->getCode();

  if (expr1_r.isConstant && expr2_r.isConstant){
      string l1 = LoadConstant((IntExpression*)expr1);
      string l2 = LoadConstant((IntExpression*)expr2);
      //cout << "NUEVO: " << l1 << endl << l2 << endl;
      lugar = newTemp();
      code << l1 << endl <<
              l2 << endl <<
              "mult " << expr1->lugar << ", " << expr2->lugar << endl <<
              "mflo " << lugar;
  }
  else if (expr1_r.isConstant){
      string l1 = LoadConstant((IntExpression*)expr1);
      lugar = newTemp();
      code << l1 << endl <<
              expr2_r.code << endl <<
              "mult " << expr1->lugar << ", " << expr2->lugar << endl <<
              "mflo " << lugar;
  } else if (expr2_r.isConstant){
            string l2 = LoadConstant((IntExpression*)expr2);
            lugar = newTemp();
            code << expr1_r.code << endl <<
                    l2 << endl <<
                    "mult " << expr1->lugar << ", " << expr2->lugar << endl <<
                    "mflo " << lugar;
  } else {
          lugar = newTemp();
          code << expr1_r.code << endl <<
                  expr2_r.code << endl <<
                  "mult " << expr1->lugar << ", " << expr2->lugar << endl <<
                  "mflo " << lugar;
  }
  releaseTemp(expr1->lugar);
  releaseTemp(expr2->lugar);

  r.code = code.str();
  r.value = 0;
  r.isConstant = false;

  return r;
}

Result DivExpression::getCode(){
  stringstream code;
  Result r;
  Result expr1_r = expr1->getCode();
  Result expr2_r = expr2->getCode();
  lugar = newTemp();

  if (expr1_r.isConstant && expr2_r.isConstant){
      string l1 = LoadConstant((IntExpression*)expr1);
      string l2 = LoadConstant((IntExpression*)expr2);
      //cout << "NUEVO: " << l1 << endl << l2 << endl;
      code << l1 << endl <<
              l2 << endl <<
              "div " << expr1->lugar << ", " << expr2->lugar << endl <<
              "mflo " << lugar;
  }
  else if (expr1_r.isConstant){
      string l1 = LoadConstant((IntExpression*)expr1);
      code << l1 << endl <<
              expr2_r.code << endl <<
              "div " << expr1->lugar << ", " << expr2->lugar << endl <<
              "mflo " << lugar;
  } else if (expr2_r.isConstant){
            string l2 = LoadConstant((IntExpression*)expr2);
            code << expr1_r.code << endl <<
                    l2 << endl <<
                    "div " << expr1->lugar << ", " << expr2->lugar << endl <<
                    "mflo " << lugar;
  } else {
        code << expr1_r.code << endl <<
                expr2_r.code << endl <<
                "div " << expr1->lugar << ", " << expr2->lugar << endl <<
                "mflo " << lugar;
  }
  releaseTemp(expr1->lugar);
  releaseTemp(expr2->lugar);

  r.code = code.str();
  r.value = 0;
  r.isConstant = false;

  return r;
}

Result IntExpression::getCode(){
  Result r;

  r.code = "";
  r.value = value;
  r.isConstant = true;

  return r;
}

Result IdExpression::getCode(){
  stringstream code;
  Result r;

  lugar = newTemp();
  code << "li "<< lugar << ", " << vars[id];

  r.value = 0;
  r.code = code.str();
  r.isConstant = false;
  //releaseTemp(lugar);
  return r;
}
