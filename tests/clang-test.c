
struct some_record {
  int a1;
  char b2;
  short c3;
};

int foo(struct some_record* r)
{
  r->a1 = 0;

  return r->c3;
}

struct some_other_record {
  int a1;
  char b2;
  short c3;
};
