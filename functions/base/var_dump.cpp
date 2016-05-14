void var_dump(php_var var)
{

  cout << "Type: ";
  switch(var.type) {
  case PHP_NULL:
    cout << "NULL" << endl;
    break;
  case PHP_STRING:
    cout << "STRING" << "(" << sizeof(var) << ")" << " - " << var.container.length() << " chars - \"" <<  var.container << "\"" << endl;
    break;
  case PHP_INT:
    cout << "INTEGER" << "(" << sizeof(var) << ") " << var.container << endl;
    break;
  case PHP_BOOL:
    cout << "BOOLEAN" << "(" << sizeof(var) << ") " << var.container << endl;
    break;
  case PHP_ARRAY:
    cout << "ARRAY (" << var.keys.size() << ")" << endl;
    for(int i = 0; i < var.keys.size(); ++i) {
      cout << "\t\t" << "[" << var.keys[i] << "]" << "\t" << endl;
      switch(var.data[i].type) {
      case PHP_NULL:
	var_dump(var.data[i]);
	break;
      case PHP_STRING:
	var_dump(var.data[i]);
	break;
      case PHP_INT:
	var_dump(var.data[i]);
	break;
      case PHP_BOOL:
	var_dump(var.data[i]);
	break;
      case PHP_ARRAY:
	var_dump(var.data[i]);
	break;
      case PHP_RESOURCE:
	var_dump(var.data[i]);
	break;
      }
    }
    break;
  case PHP_RESOURCE:
    cout << "RESOURCE" << endl;
    break;
  }
}


