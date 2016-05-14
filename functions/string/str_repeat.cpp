php_var str_repeat(php_var input, php_var multiplier) {
	char *out;
	php_var retval;
	int i=(int)multiplier;
	if(i == 0)
		return (php_var)"";
	out=(char*)malloc(i*strlen(input)+1);
	memset(out,0,i*strlen(input)+1);

	for(;i>=1;i--)
		sprintf(out,"%s%s",out,(const char*)input);
	retval=out;
	free(out);
	return retval;
}
