php_var fread(php_var handle, php_var length)
{
	char* buf;
	buf = (char*)malloc((int)length+1);
	memset(buf,0,(int)length+1);
	fread(buf, 1, (int)length, (FILE *) handle.res);
	php_var ret = buf;
	free(buf);
	return ret;
}