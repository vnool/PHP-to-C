php_var shell_exec(php_var cmd)
{
	FILE *fp = popen(cmd, "r");
	if(fp == NULL) {
	  return (php_var) 0;
	}
	string returner;
	char * buf = (char *) malloc(1024);
	while(!feof(fp)) {
	  fread(buf, 1, 1023, fp);
	  returner += buf;
	}
	pclose(fp);
	return (php_var) returner;
}
