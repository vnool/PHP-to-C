php_var opendir(php_var path)
{
	php_var dirp;
	dirp.type = PHP_RESOURCE;

	dirp.res = (void *) opendir(path.container.c_str());
	return dirp;
}
