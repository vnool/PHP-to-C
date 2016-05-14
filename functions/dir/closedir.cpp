php_var closedir(php_var dir_handle)
{
	closedir(dir_handle.res);
	dir_handle.res = NULL;
	dir_handle.type = PHP_NULL;
	return dir_handle;
}
