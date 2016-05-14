#include <stdarg.h>
php_var array(int key = 0, ...)
{
	va_list ap;
	va_start(ap, key);
	php_var arr;
	arr.to_array();
	int i = 0;
	for(int i = 0; i < key / 2; ++i)
	{
		php_var key2 = va_arg(ap, php_var);
		if(key2 == -1)
		{
			bool found = false;
			for(;;)
			{
				for(i = 0;i < arr.keys.size(); ++i)
				{
					if(arr.keys[i] == (php_var) i)
						found = true;
				}
				if(found)
					++i;
				else
					break;
			}
			key2 = i;
		}
		php_var val = va_arg(ap, php_var);
		arr.keys.push_back(key2);
		arr.data.push_back(val);
	};
	va_end(ap);
	return arr;
}
