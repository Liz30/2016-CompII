class Test {
  boolean a, b;
  int i = 10; int m;

  int whileTest(int y, boolean g){
    int tmp, miMax, op;
    tmp = 0;
    op = 30;
    miMax = 0;

    while (tmp < 10)
    {
        if (op > miMax){
            miMax = op;
        }
      tmp = tmp + 1;
    }
    print "Max: ",miMax;
    return miMax;
  }

  void main()
  {
      m = whileTest(8, false);
  }

  void ifTest(){
      if ((i+20) > 10){
        print " i es menor a 10";
      }
      else{
          print " i es mayor a 10";
      }
  }

  int forTest(){
    int y;
    for (m=0, y=i; m < i; m=m+1, y = y + 10){
      //print "i: ", i, "  m: ", m, "  y: ",y;
    }
    //print m;
  }

  void q(){

  }


}
