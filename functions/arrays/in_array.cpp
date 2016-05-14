php_var in_array(php_var needle, php_var haystack, php_var strick = false)
{
	int i = 0;
	for(i = 0;i < haystack.keys.size(); ++i)
	{
		if(haystack.data[i] == needle)
		{
			if(strick==true)
			{
				if(needle.type==haystack.data[i].type)
					return (php_var)true;
				return (php_var) false;
			}
			return (php_var) true;
		}
	}
	return (php_var) false;
}