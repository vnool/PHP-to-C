php_var passthru(php_var str)
{
  int i;
  i = system ((char *)str);
  if(i == -1) {
    return (php_var) 0;
  }
  else {
    return (php_var) 1;
  }
}
