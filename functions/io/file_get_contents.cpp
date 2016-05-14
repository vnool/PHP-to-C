php_var file(php_var filename)
{
	long size;
	char* buffer;
	FILE* fp = fopen((const char*)filename, "r");
	if(fp == NULL)
		return((php_var)false);
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	rewind(fp);
	buffer = (char*)malloc(size);
	if(buffer == NULL)
		return (php_var) "";
	fread(buffer,1,size,fp);
	fclose(fp);
	php_var ret = buffer;
	free(buffer);
	return ret;
}
  
