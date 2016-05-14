#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#define PHP_NULL 0
#define PHP_STRING 1
#define PHP_INT 2
#define PHP_BOOL 3
#define PHP_ARRAY 4
#define PHP_RESOURCE 5
#define PHP_OBJECT 6

char* intstring(long i)
{
	char *buf = new char[11];
	sprintf(buf, "%i", i);
	return buf;
}
char* doublestring(double i)
{
	char *buf = new char[16];
	sprintf(buf, "%d", i);
	return buf;
}

class php_var
{
	public:
		php_var() // Constructor
		{
			type = PHP_NULL; // Make the var, but make it null.
			container = "";
		}
		php_var(const char* str)
		{
			container = str;
			type = PHP_STRING;
		}
		php_var(double i)
		{
			type = PHP_INT;
			container = doublestring(i);
		}
		php_var(int i)
		{
			type = PHP_INT;
			container = intstring(i);
		}
		php_var(unsigned int i)
		{
			container = intstring(i);
			type = PHP_INT;
		}
		php_var(long i)
		{
			container = intstring(i);
			type = PHP_INT;
		}
		php_var(const php_var &temp)
		{
			type = temp.type;
			container = temp.container;
			keys = temp.keys;
			data = temp.data;
			res = temp.res;
		}
		php_var(char * str)
		{
			container = str;
			type = PHP_STRING;
		}
		php_var(string str)
		{
			container = str;
			type = PHP_STRING;
		}
		php_var(bool b)
		{
			if(b)
				container = "1";
			else
				container = "0";
			type = PHP_BOOL;
		}
		operator const char*()
		{
			if(type == PHP_STRING || type == PHP_INT)
				return container.c_str();
			else
				return "Array";
		}
		operator string()
		{
			if(type == PHP_STRING || type == PHP_INT)
				return container;
			else
				return string("Array");
		}
		operator bool()
		{
			if(type != PHP_BOOL || (type == PHP_BOOL && container.compare("1") == 0))
				return true;
			return false;
		}
		operator double()
		{
			return atof(container.c_str());
		}
		operator float()
		{
			return atof(container.c_str());
		}
		operator int()
		{
			return atoi(container.c_str());
		}
		operator unsigned int()
		{
			return atoi(container.c_str());
		}
		operator long()
		{
			return atol(container.c_str());
		}
		php_var &operator[](int subscript)
		{
			if(type == PHP_STRING)
			{
				// return &container[subscript];
			}
			else if(type == PHP_ARRAY)
			{
				php_var key = subscript;
				int i = 0;
				for(i = 0;i < keys.size(); ++i)
				{
					if(key.container.compare(keys[i].container) == 0)
						return data[i];
				}
				php_var temp;
				keys.push_back(key);
				data.push_back(temp);
				return data[i];
			}
		}
		php_var &operator[](unsigned int subscript)
		{
			if(type == PHP_STRING)
			{
				// return &container[subscript];
			}
			else if(type == PHP_ARRAY)
			{
				php_var key = subscript;
				int i = 0;
				for(i = 0;i < keys.size(); ++i)
				{
					if(key.container.compare(keys[i].container) == 0)
						return data[i];
				}
				php_var temp;
				keys.push_back(key);
				data.push_back(temp);
				return data[i];
			}
		}
		php_var &operator[](long subscript)
		{
			if(type == PHP_STRING)
			{
				// return &container[subscript];
			}
			else if(type == PHP_ARRAY)
			{
				php_var key = subscript;
				int i = 0;
				for(i = 0;i < keys.size(); ++i)
				{
					if(key.container.compare(keys[i].container) == 0)
						return data[i];
				}
				php_var temp;
				keys.push_back(key);
				data.push_back(temp);
				return data[i];
			}
		}
		php_var &operator[](const char* subscript)
		{
			if(type == PHP_STRING)
			{
				// return &container[subscript];
			}
			else if(type == PHP_ARRAY)
			{
				php_var key = subscript;
				int i = 0;
				for(i = 0;i < keys.size(); ++i)
				{
					if(key.container.compare(keys[i].container) == 0)
						return data[i];
				}
				php_var temp;
				keys.push_back(key);
				data.push_back(temp);
				return data[i];
			}
		}
		php_var &operator[](char* subscript)
		{
			if(type == PHP_STRING)
			{
				// return &container[subscript];
			}
			else if(type == PHP_ARRAY)
			{
				php_var key = subscript;
				int i = 0;
				for(i = 0;i < keys.size(); ++i)
				{
					if(key.container.compare(keys[i].container) == 0)
						return data[i];
				}
				php_var temp;
				keys.push_back(key);
				data.push_back(temp);
				return data[i];
			}
		}
		php_var &operator[](string subscript)
		{
			if(type == PHP_STRING)
			{
				// return &container[subscript];
			}
			else if(type == PHP_ARRAY)
			{
				php_var key = subscript;
				int i = 0;
				for(i = 0;i < keys.size(); ++i)
				{
					if(key.container.compare(keys[i].container) == 0)
						return data[i];
				}
				php_var temp;
				keys.push_back(key);
				data.push_back(temp);
				return data[i];
			}
		}
		php_var &operator[](php_var subscript)
		{
			if(type == PHP_STRING)
			{
				// return (char *)&container[subscript];
			}
			else if(type == PHP_ARRAY)
			{
				php_var key = subscript;
				int i = 0;
				for(i = 0;i < keys.size(); ++i)
				{
					if(key.container.compare(keys[i].container) == 0)
						return data[i];
				}
				php_var temp;
				keys.push_back(key);
				data.push_back(temp);
				return data[i];
			}
		}
		bool operator<(int i)
		{
			if(atol(container.c_str()) < i)
				return true;
			return false;
		}
		bool operator>(int i)
		{
			if(atol(container.c_str()) > i)
				return true;
			return false;
		}
		bool operator<(php_var i)
		{
			if(atol(container.c_str()) < atol(i.container.c_str()))
				return true;
			return false;
		}
		bool operator>(php_var i)
		{
			if(atol(container.c_str()) > atol(i.container.c_str()))
				return true;
			return false;
		}
		bool operator!=(const char* cmp)
		{
			if(container.compare(cmp))
				return true;
			return false;
		}
		bool operator!=(int i)
		{
			if(atol(container.c_str()) == i)
				return false;
			return true;
		}
		bool operator!=(php_var var)
		{
			if(!container.compare(var.container))
				return false;
			return true;
		}
		bool operator==(const char* cmp)
		{
			if(container.compare(cmp) == 0)
				return true;
			return false;
		}
		bool operator==(int i)
		{
			if(atol(container.c_str()) == i)
				return true;
			return false;
		}
		bool operator==(php_var var)
		{
			if(container.compare(var.container) == 0)
				return true;
			return false;
		}
		int operator++(int i)
		{
			int ret = atol(container.c_str());
			container = intstring(ret + i);
			return ret;
		}
		int operator++()
		{
			int ret = atol(container.c_str()) + 1;
			container = intstring(ret);
			return ret;
		}
		int operator--(int i)
		{
			int ret = atol(container.c_str());
			container = intstring(ret);
			return ret;
		}
		int operator--()
		{
			int ret = atol(container.c_str()) + 1;
			container = intstring(ret);
			return ret;
		}
		void operator+=(int inc)
		{
			if(type == PHP_INT)
			{
				container = intstring(atol(container.c_str()) + inc);
			}
		}
		void operator+=(php_var str)
		{
			if(str.type == PHP_INT)
			{
				container = intstring(atol(container.c_str()) + atoi(str.container.c_str()));
				if(type != PHP_INT && type != PHP_STRING)
					type = PHP_INT;
			}
			else
			{
				container += str.container;
				if(type != PHP_STRING)
					type = PHP_STRING;
			}
		}
		void operator+=(string str)
		{
			container += str;
		}
		void operator+=(const char* str)
		{
			container += str;
		}
		void operator+=(char* str)
		{
			container += str;
		}
		void operator-=(int dec)
		{
			if(type == PHP_INT)
			{
				container = intstring(atol(container.c_str()) - dec);
			}
		}
		void operator/(php_var i)
		{
			if(type == PHP_INT)
				container = doublestring(atof(container.c_str()) / atof(i.container.c_str()));
		}
		void operator-(php_var i)
		{
			if(type == PHP_INT)
				container = doublestring(atof(container.c_str()) - atof(i.container.c_str()));
		}
		friend ostream &operator<<( ostream &out, const php_var &var );
		void to_array()
		{
			type = PHP_ARRAY;
		}
		string container; // Contains value.
		vector<php_var> keys;
		vector<php_var> data;
		void *res;
		void *obj_type;
		int res_type;
		int type; // Contains current type.
};
ostream &operator<<( ostream &out, const php_var &var )
{
	if(var.type == PHP_ARRAY)
		out << "Array";
	else
		out << var.container;
}
bool operator<(int i,php_var v)
{
	return(v > i);
}
bool operator>(int i, php_var v)
{
	return(v < i);
}
php_var operator+(php_var l, php_var r)
{
	return (php_var)((int) l + (int) r);
}
php_var operator-(php_var l, php_var r)
{
	return (php_var)((int) l - (int) r);
}
#define is_identical(var, varb) (((var) == (varb) && (var).type == (varb).type) ? (php_var)true : (php_var)false)
