php_var array_reverse(php_var arr, php_var preserve_keys)
{
	php_var retval=arr;
	if((bool)preserve_keys == false)
	{
		for(i = 0;i < arr.size(); ++i)
			retval.keys[i]=arr.keys[arr.size()-i-1];
	}
	for(i = 0;i < arr.size(); ++i)
		retval.data[i]=arr.data[arr.size()-i-1];
}
