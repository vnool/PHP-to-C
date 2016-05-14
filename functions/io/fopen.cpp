php_var fopen(php_var filename, php_var openmode)
{
	php_var stream;
	FILE *input = fopen((const char *) filename, (const char*) openmode);
	stream.res = (void *) input;
	return stream;
}