class Test {
  boolean a, b;
  int i = 90; int m;

  void main()
  {
    boolean test;
    test = true;
    print !test;
  }

  void g (boolean u){
    boolean f;
    int y;
    u = false;
    f = true;
    y = 100;

    print "f: ", f, "    u: ", u;
    print "   && ", f && u;
    print "   || ", f || u;
    print "   == ", f << u;
  }

  void is(int d){
    int f;
    f = 10;  // No declarada, bugs es que f en g() la declara global
    print  f;
  }

  void test(){
      if ((i+20) > 10){
        print " i es menor a 10";
      }
      else{
          print " i es mayor a 10";
      }

  }

}
