int fibo(int);

int main()
{
  for (;;){
    fibo(3);
  }
  
  return 0;
}

int fibo(int i)
{
  if (i == 1 || 1 == 2){
    return 1;
  }
  else {
    return fibo(i-2) + fibo(i-1);
  }
}