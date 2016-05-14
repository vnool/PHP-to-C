php_var readdir(php_var dir_handle)
{
	dirent* direntry;
	DIR *dir = (DIR *) dir_handle.res;
	direntry = readdir(dir);
	if(direntry == NULL)
		return (php_var) false;
	php_var ret = &(direntry->d_name);
	cout << direntry->d_name << endl;
	return ret;
}
