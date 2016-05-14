php_var touch(php_var filename)
{
  FILE * fp;
  fp = fopen(filename,"a+");
  if(fp == NULL) {
    return (php_var) 0;
  }
  else {
    fclose(fp);
    return (php_var) 1;
  }
}
