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

/*string LoadConstant(IntExpression* e){
    stringstream code;
    string lugar = newTemp();
    code << "li "<< lugar << ", " << e->value;
    e->lugar = lugar;
    return code.str();
}*/

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
                  expr1_r.value;
            releaseTemp(expr2->lugar);
            r.code = code.str();
            r.value = 0;
            r.isConstant = false;
       }
       else if (expr2_r.isConstant) {
                lugar = newTemp();
                code << expr1_r.code << endl <<
                      "addi " << lugar << ", " << expr1->lugar << ", " <<
                      expr2_r.value;
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
                 (expr2_r.value*(-1));
           releaseTemp(expr1->lugar);
           r.code = code.str();
           r.value = 0;
           r.isConstant = false;
  }
  else if (expr1_r.isConstant){
            lugar = newTemp();
            string lugarTemp = newTemp();
            stringstream codeTemp;
            codeTemp << "li " << lugarTemp << ", " << expr1_r.value;
            code << codeTemp.str() << endl <<
                   expr2_r.code << endl <<
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

Result MultExpression::getCode(){
  stringstream code;
  Result r;
  Result expr1_r = expr1->getCode();
  Result expr2_r = expr2->getCode();

  if (expr1_r.isConstant && expr2_r.isConstant){
    r.value = expr1->Evaluate() * expr2->Evaluate();
    r.code = "";
    r.isConstant = true;
    return r;
  }
  else if (expr1_r.isConstant){
      //string l1 = LoadConstant((IntExpression*)expr1);
      string lugarTemp = newTemp();
      stringstream codeTemp;
      codeTemp << "li " << lugarTemp << ", " << expr1_r.value;

      lugar = newTemp();
      code << codeTemp.str() << endl <<
              expr2_r.code << endl <<
              "mult " << lugarTemp << ", " << expr2->lugar << endl <<
              "mflo " << lugar;
      releaseTemp(lugarTemp);
  } else if (expr2_r.isConstant){
            string lugarTemp = newTemp();
            stringstream codeTemp;
            codeTemp << "li " << lugarTemp << ", " << expr2_r.value;

            lugar = newTemp();
            code << expr1_r.code << endl <<
                    codeTemp.str() << endl <<
                    "mult " << expr1->lugar << ", " << lugarTemp << endl <<
                    "mflo " << lugar;
            releaseTemp(lugarTemp);
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

  if (expr1_r.isConstant && expr2_r.isConstant){
    r.value = expr1->Evaluate() / expr2->Evaluate();
    r.code = "";
    r.isConstant = true;
    return r;
  }
  else if (expr1_r.isConstant){
      lugar = newTemp();
      string lugarTemp = newTemp();
      stringstream codeTemp;
      codeTemp << "li " << lugarTemp << ", " << expr1_r.value;

      code << codeTemp.str() << endl <<
              expr2_r.code << endl <<
              "div " << lugarTemp << ", " << expr2->lugar << endl <<
              "mflo " << lugar;
      releaseTemp(lugarTemp);
  } else if (expr2_r.isConstant){
            lugar = newTemp();
            string lugarTemp = newTemp();
            stringstream codeTemp;
            codeTemp << "li " << lugarTemp << ", " << expr2_r.value;

            code << expr1_r.code << endl <<
                    codeTemp.str() << endl <<
                    "div " << expr1->lugar << ", " << lugarTemp << endl <<
                    "mflo " << lugar;
            releaseTemp(lugarTemp);
  } else {
        lugar = newTemp();
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
//  cout << "      ID Expr: " << lugar << endl;

  r.value = 0;
  r.code = code.str();
  r.isConstant = false;
  //releaseTemp(lugar);
  return r;
}
