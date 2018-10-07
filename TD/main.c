int fibo(int i);

int global;
int zero = 0;
int main()
{
  fibo(8);
  //TODO: Add LED loop
  return global;
}

int fibo(int i)
{
  if (i == 1 || i == 2)
  {
    return 1;
  }
  else
  {
    return fibo(i - 2) + fibo(i - 1);
  }
}