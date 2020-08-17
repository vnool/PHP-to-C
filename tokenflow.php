<?php
	class TokenGenerator
	{
		var $functions = array('main');
		var $curfunction = 0;
		var $code;
		var $prototypes;
		var $includes = array();
		var $cppincludes = array();
		var $namespace;
		var $tabs = 0;
		var $scope = array();
		var $funccount = 1;
		var $inclass = false;
		var $classes = array();
		var $curclass = 0;
		var $foreach = 0;
		var $defines = array();
		var $objects = array();
		var $inswitch = 0;
		var $switchstate = array();
		var $switched = array();
		var $libs = array();
		var $globals = array();
		function __construct($tokenizer)
		{
			global $funcs;
			$this->code = array('main' => array());
			$this->prototypes = array('main' => array('int', array('int _argc', 'char **_argv')));
			$this->namespace = 'std';
			$this->includes[] = 'sstream';
			$parameters = array();
			$i = -1;
			$in = array();
			$superglobals = array('_ENV');
			$temptabs = false;
			for($a = 0; $a < count($tokenizer->tokens); ++$a)
			{
				if(is_array($tokenizer->tokens[$a]) && $tokenizer->tokens[$a][0] == T_GLOBAL && !in_array(substr($tokenizer->tokens[$a + 1][1], 1), $this->globals))
					$this->globals[] = substr($tokenizer->tokens[$a + 1][1], 1);
			}
			$this->scope[] = $this->globals;
			$this->scope[0][] = 'argc';
			$this->scope[0][] = 'argv';
			for($a = 0; $a < count($tokenizer->tokens); ++$a)
			{
				if(is_array($tokenizer->tokens[$a]))
					list($token, $data) = $tokenizer->tokens[$a];
				else
				{
					$token = $tokenizer->tokens[$a];
					$data = null;
				}
				switch($token)
				{
					case T_INLINE_HTML:
						$html = str_replace(array('\\', '"'), array('\\\\', '\"'), $data);
						$this->includes[] = 'iostream';
						$this->AddCode('cout << "' . $html . '";');
						if($temptabs != false)
						{
							--$this->tabs;
							if($temptabs == 2)
								$this->AddCode('}');
							$temptabs = false;
						}
						break;
					case T_PRINT:
					case T_ECHO:
						$parameters = array();
						for($z = $a + 1; $z < count($tokenizer->tokens); ++$z)
						{
							if(is_array($tokenizer->tokens[$z]))
								list($token, $data) = $tokenizer->tokens[$z];
							else
							{
								$token = $tokenizer->tokens[$z];
								$data = null;
							}
							switch($token)
							{
								case ';':
									break 2;
								default:
									list($parameters[], $z) = $this->parse_statement($tokenizer, $z);
									break;
							}
						}
						$this->AddCode('cout << ' . implode(' << ', $parameters) . ';');
						if($temptabs != false)
						{
							--$this->tabs;
							$temptabs = false;
						}
						$a = $z - 1;
						break;
					case T_GLOBAL:
						$this->scope[$this->curfunction][] = substr($tokenizer->tokens[$a + 1][1], 1);
						$a += 2;
						break;
					case T_FUNCTION:
						break;
					case T_STRING:
						if(is_array($tokenizer->tokens[$a - 1]) && $tokenizer->tokens[$a - 1][0] == T_FUNCTION)
						{
							$this->functions[] = $data;
							$this->curfunction = $this->funccount++;
							$this->scope[] = array();
							list($statement, $z) = $this->parse_function($tokenizer, $a);
							$statement = substr($statement, strpos($statement, '(') + 1, -1);
							if(strstr($statement, ', '))
								$params = explode(', ', $statement);
							else
								$params = array($statement);
							$this->prototypes[$data] = array('void', $params);
							$this->code[$data] = array();
							$a = $z + 1;
							if(DEBUG)
								echo 'In function: ', $data, "\n";
						}
						elseif(is_array($tokenizer->tokens[$a - 1]) && $tokenizer->tokens[$a - 1][0] == T_CLASS)
						{
							$this->classes[$data] = array('public' => array(), 'private' => array(), 'funcs' => array());
							$this->curclass = $data;
							$this->inclass = true;
							++$a;
						}
						else
						{
							list($statement, $z) = $this->parse_function($tokenizer, $a);
							if($statement != NULL)
								$this->AddCode($statement . ';');
							$a = $z;
							if($temptabs != false)
							{
								--$this->tabs;
								// if($temptabs == 2)
									// $this->AddCode('}');
								$temptabs = false;
							}
						}
						break;
					case T_VAR:
						if(is_array($tokenizer->tokens[$a + 1]) && $tokenizer->tokens[$a + 1][0] == T_VARIABLE)
						{
							list($this->classes[$this->curclass]['public'][], $a) = $this->parse_statement($tokenizer, $a + 1);
							++$a;
						}
						break;
					case T_SWITCH:
						list($this->switchstate[++$this->inswitch], $a) = $this->parse_statement($tokenizer, $a + 2);
						$this->switched[$this->inswitch] = false;
						$a += 2;
						break;
					case T_CASE:
						list($case, $a) = $this->parse_statement($tokenizer, $a + 1);
						if($this->switched[$this->inswitch] == false)
						{
							$this->AddCode('if(' . $this->switchstate[$this->inswitch] . ' == ' . $case . ')');
							$this->switched[$this->inswitch] = true;
						}
						else
						{
							--$this->tabs;
							$this->AddCode('}');
							$this->AddCode('else if(' . $this->switchstate[$this->inswitch] . ' == ' . $case . ')');
						}
						$this->AddCode('{');
						++$this->tabs;
						break;
					case T_BREAK:
						$this->AddCode('goto _end_' . $this->inswitch . ';');
						break;
					case T_DEFAULT:
						$this->AddCode('else');
						break;
					case T_DEC:
					case T_INC:
					case T_VARIABLE:
						list($statement, $a) = $this->parse_statement($tokenizer, $a);
						$this->AddCode($statement . ';');
						if($temptabs != false)
						{
							--$this->tabs;
							$temptabs = false;
						}
						break;
					case T_ELSEIF:
					case T_IF:
						list($expression, $a) = $this->parse_statement($tokenizer, $a);
						if($token == T_IF)
							$this->AddCode('if (' . $expression . ')');
						else
							$this->AddCode('else if (' . $expression . ')');
						++$a;
						if($tokenizer->tokens[$a + 1] != '{')
						{
							++$this->tabs;
							$temptabs = true;
						}
						break;
					case T_ELSE:
						if($temptabs !== false)
						{
							--$this->tabs;
							$temptabs = false;
						}
						$this->AddCode('else');
						if($tokenizer->tokens[$a + 1] != '{')
						{
							++$this->tabs;
							$temptabs = true;
						}
						break;
					case T_FOR:
						$statements = array();
						$statement = (string) null;
						$in = 0;
						for($z = $a + 1; $z < count($tokenizer->tokens); ++$z)
						{
							if(is_array($tokenizer->tokens[$z]))
								list($token_, $data_) = $tokenizer->tokens[$z];
							else
							{
								$token_ = &$tokenizer->tokens[$z];
								$data_ = null;
							}
							switch($token_)
							{
								case '(':
									++$in;
									break;
								case ')':
									if(--$in == 0)
									{
										$statements[] = $statement;
										$statement = (string) null;
										break 2;
									}
									break;
								case ';':
									$statements[] = $statement;
									$statement = (string) null;
									break;
								default:
									list($t, $z) = $this->parse_statement($tokenizer, $z);
									$statement .= $t;
									break;
							}
						}
						$a = $z;
						$this->AddCode('for(' . implode('; ', $statements) . ')');
						if($tokenizer->tokens[$a + 1] != '{')
						{
							++$this->tabs;
							$temptabs = true;
						}
						break;
					case T_FOREACH:
						list($arrname, $a) = $this->parse_statement($tokenizer, $a + 2);
						$arrname = substr($arrname, 1);
						if(is_array($tokenizer->tokens[$a + 2]) && $tokenizer->tokens[$a + 2][0] == T_DOUBLE_ARROW)
						{
							list($key, $a) = $this->parse_statement($tokenizer, $a + 1);
							list($data, $a) = $this->parse_statement($tokenizer, $a + 1);
						}
						else
						{
							list($data, $a) = $this->parse_statement($tokenizer, $a + 1);
							$key = null;
						}
						if($tokenizer->tokens[$a + 2] == '{')
							$a += 2;
						else
							$temptabs = 2;
						$this->AddCode('for(php_var i' . $this->foreach . ' = 0; i' . $this->foreach . ' < _' . $arrname . '.keys.size(); ++i' . $this->foreach . ')');
						$this->AddCode('{');
						++$this->tabs;
						if($key !== null)
							$this->AddCode($key . ' = _' . $arrname . '.keys[i' . $this->foreach . '];');
						$this->AddCode($data . ' = _' . $arrname . '.data[i' . $this->foreach . '];');
						++$this->foreach;
						break;
					case T_WHILE:
						$statement = (string)null;
						$in = 0;
						for($z = $a + 1; $z < count($tokenizer->tokens); ++$z)
						{
							if(is_array($tokenizer->tokens[$z]))
								list($token_, $data_) = $tokenizer->tokens[$z];
							else
							{
								$token_ = &$tokenizer->tokens[$z];
								$data_ = null;
							}
							switch($token_)
							{
								case '(':
									if($in > 0)
										$statement .= '(';
									++$in;
									break;
								case ')':
									if(--$in == 0)
										break 2;
									$statement .= ')';
									break;
								default:
									list($t, $z) = $this->parse_statement($tokenizer, $z);
									$statement .= $t;
									break;
							}
						}
						$a = $z;
						$this->AddCode('while(' .$statement . ')');
						if($tokenizer->tokens[$a + 1] != '{')
						{
							++$this->tabs;
							$temptabs = true;
						}
						break;
					case T_RETURN:
						if($this->curfunction > 0)
						{
							list($statement, $a) = $this->parse_statement($tokenizer, $a);
							$this->prototypes[$this->functions[$this->curfunction]][0] = 'php_var';
							$this->AddCode('return ' . $statement . ';' . "\n");
						}
						break;
					case '{':
						$this->AddCode('{');
						++$this->tabs;
						break;
					case '}':
						if($this->tabs == 0)
						{
							if(!empty($this->inclass))
								$this->inclass = (string) null;
							else
								$this->curfunction = 0;
						}
						elseif(($this->tabs == 1 && $this->inclass) || ($this->tabs < 0 && $this->curfunction > 0))
						{
							$this->curfunction = 0;
							$this->tabs = 0;
						}
						else
						{
							--$this->tabs;
							if($this->inswitch > 0)
							{
								if($this->switched[$this->inswitch] == true)
									$this->AddCode('}');
								$this->AddCode('_end_' . $this->inswitch . ':');
							}
							else
								$this->AddCode('}');
							if($this->tabs == 0 && $this->curfunction > 0 && $this->inswitch == 0)
								$this->curfunction = 0;
							if($this->inswitch != 0)
								++$this->inswitch;
						}
						break;
					case T_OPEN_TAG:
					case T_CLOSE_TAG:
						break;
					case ';':
						break;
					default:
						break;
				}
			}
		}
		function parse_function(&$tokenizer, $token_)
		{
			global $funcs;
			$parameters = array();
			$funcname = $tokenizer->tokens[$token_][1];
			if($tokenizer->tokens[$token_ + 1] != '(')
				return array($funcname, $token_);
			if(is_array($tokenizer->tokens[$token_ - 1]) && $tokenizer->tokens[$token_ - 1][0] == T_OBJECT_OPERATOR)
			{
				return array('_' . $funcname, $token_);
			}
			if($funcname == 'sizeof')
				$funcname = 'count';
			for($i = $token_ + 1; $i < count($tokenizer->tokens); ++$i)
			{
				if(is_array($tokenizer->tokens[$i]))
					list($token, $data) = $tokenizer->tokens[$i];
				else
				{
					$token = &$tokenizer->tokens[$i];
					$data = null;
				}
				switch($token)
				{
					case '(':
						list($param, $i) = $this->parse_statement($tokenizer, $i);
						if($tokenizer->tokens[$token_][0] == T_ARRAY && count($parameters) % 2 == 0 && (is_array($tokenizer->tokens[$i + 1]) && $tokenizer->tokens[$i + 1][1] != '=>'))
							$parameters[] = -1;
						$parameters[] = $param;
						break;
					case T_STRING:
					case '-':
					case T_CONSTANT_ENCAPSED_STRING:
					case T_DEC:
					case T_INC:
					case T_DNUMBER:
					case T_LNUMBER:
					case T_VARIABLE:
						list($parameters[], $i) = $this->parse_statement($tokenizer, $i);
						break;
					case ',':
						break;
					case ';':
					case ')':
						break 2;
					default:
						if(!DEBUG)
							break;
						if($data === null)
							echo $token, "\n";
						else
							echo token_name($token), "\n";
						break;
				}
			}
			if(strtolower($funcname) == 'define')
				++$i;
			elseif($tokenizer->tokens[$i] == ';')
				--$i;
			if($tokenizer->tokens[$token_][0] == T_ARRAY)
			{
				if(count($parameters) == 0)
					return array('array()', $i);
				$params = array();
				$params[-1] = count($parameters);
				foreach($parameters as $param)
					$params[] = $param;
				$parameters = $params;
			}
			if(!in_array($funcname, $this->functions) && isset($funcs[$funcname]))
			{
				if(is_array($funcs[$funcname]))
				{
					if(count($funcs[$funcname]) == 2)
					{
						list($h, $cpp) = $funcs[$funcname];
						$lib = null;
					}
					else
						list($h, $cpp, $lib) = $funcs[$funcname];
					if($h != null)
					{
						if(is_array($h))
						{
							foreach($h as $h_)
								$this->includes[] = $h_;
						}
						else
							$this->includes[] = $h;
					}
					if($cpp != null)
					{
						if(is_array($cpp))
						{
							foreach($cpp as $cpp_)
								$this->cppincludes[] = $cpp_;
						}
						else
							$this->cppincludes[] = $cpp;
					}
					if($lib != null)
					{
						if(is_array($lib))
						{
							foreach($lib as $lib_)
								$this->libs[] = $lib_;
						}
						else
							$this->libs[] = $lib;
					}
				}
				else
					$this->includes[] = $funcs[$funcname];
			}
			if($tokenizer->tokens[$token_][0] == T_ARRAY && count($parameters) == 2)
				return array('array()', $i);
			if(strtolower($funcname) == 'define')
			{
				if($parameters[0]{0} == '"')
					$parameters[0] = substr($parameters[0], 1, -1);
				$this->defines[$parameters[0]] = $parameters[1];
				return array(NULL, $i);
			}
			else
				return array($funcname . '(' . implode(', ', $parameters) . ')', $i);
		}
		/**
		 * Parse statement.
		 *
		 * @param $tokenizer object Tokenizer object.
		 * @param $token int Pointer to current token.
		 * @return string
		 * @access public
		 */
		function parse_statement(&$tokenizer, $token)
		{
			$tokens = &$tokenizer->tokens;
			$code = (string) null;
			$in = 0;
			$pre = $post = (string)null;
			$params = array();
			$inconcat = false;
			$inbrace = false;
			for($i = $token; $i < count($tokens); ++$i)
			{
				if(is_array($tokenizer->tokens[$i]))
					list($token_, $data_) = $tokens[$i];
				else
				{
					$token_ = $tokens[$i];
					$data_ = null;
				}
				if($tokenizer->tokens[$i + 1] == '.')
					$inconcat = true;
				switch($token_)
				{
					case T_VARIABLE:
						if($inconcat == true && $inbrace == false)
							$code .= '(string)(const char*)';
						if(is_array($tokenizer->tokens[$i + 1]) && $tokenizer->tokens[$i + 1][0] == T_OBJECT_OPERATOR)
						{
							if(strtolower($data_) == '$this')
								$code .= 'this.';
							else
								$code .= 'OBJ<' . $this->objects[$data_] . '>(_' . substr($data_, 1) . ')->';
							break;
						}
						if(in_array(substr($data_, 1), $this->scope[$this->curfunction]))
							$code .= '_' . substr($data_, 1);
						else
						{
							$code .= 'php_var _' . substr($data_, 1);
							$this->scope[$this->curfunction][] = substr($data_, 1);
						}
						break;
					case T_ARRAY:
					case T_STRING:
						if($inconcat == true && $inbrace == false)
							$code .= '(string)(const char*)';
						if(strtolower($data_) == 'true' || strtolower($data_) == 'false' || strtolower($data_) == 'null')
							$code .= '(php_var) ' . strtolower($data_);
						elseif(is_array($tokenizer->tokens[$i - 1]) && $tokenizer->tokens[$i - 1][0] == T_NEW)
						{
							$code .= '(void *) new ' . $data_;
							$this->objects[$tokenizer->tokens[$i - 3][1]] = $data_;
						}
						elseif(is_array($tokenizer->tokens[$i - 1]) && $tokenizer->tokens[$i - 1][0] == T_OBJECT_OPERATOR)
							$code .= '_' . $data_;
						elseif($tokenizer->tokens[$i + 1] != '(')
							$code .= $data_;
						else
						{
							list($t, $i) = $this->parse_function($tokenizer, $i);
							$code .= '(php_var)' . $t;
						}
						break;
					case '=':
						$params[] = $pre . $code . $post;
						$pre = $post = $code = (string) null;
						$inconcat = false;
						break;
					case T_PLUS_EQUAL:
						$code .= ' += ';
						break;
					case T_MINUS_EQUAL:
						$code .= ' -= ';
						break;
					case T_CONSTANT_ENCAPSED_STRING:
						if($data_ == '"\n"')
						{
							$code .='endl';
							break;
						}
						if($inconcat == true && $inbrace == false)
							$code .= '(string)(const char*)';
						if(is_array($tokenizer->tokens[$i - 1]) && $tokenizer->tokens[$i - 1][0] == T_IS_EQUAL)
							$code .= '(string) "' . str_replace('"', '\\"', substr($data_, 1, -1) ). '"';
						else
							$code .= '(php_var)' . '"' . str_replace('"', '\\"', substr($data_, 1, -1) ). '"';
						break;
					case T_DNUMBER:
					case T_LNUMBER:
						if(($tokenizer->tokens[$i - 2] == ',' || $tokenizer->tokens[$i - 2] == '(' || $tokenizer->tokens[$i - 2] == '.') && $tokenizer->tokens[$i - 1] == '-')
							$data_ = '-' . $data_;
						if($inconcat == true && $inbrace == false)
							$code .= '(string)(const char*)';
						if(is_array($tokenizer->tokens[$i - 1]) && $tokenizer->tokens[$i - 1][0] == T_IS_EQUAL)
							$code .= '(string)' . $data_;
						else
							$code .= '(php_var)' . $data_;
						break;
					case T_DEC:
						$code .= '--';
						break;
					case T_INC:
						$code .= '++';
						break;
					case '<':
						$code .= ' < ';
						break;
					case '>':
						$code .= ' > ';
						break;
					case '(':
						if($in > 0)
							$code .= '(';
						++$in;
						break;
					case ')':
						if($in > 1)
							$code .= ')';
						if(--$in <= 0)
							break 2;
						break;
					case ':':
					case T_AS:
					case T_DOUBLE_ARROW:
					case ',':
					case ';':
						break 2;
					case T_BOOLEAN_AND:
						$code .= ' && ';
						break;
					case T_BOOLEAN_OR:
						$code .= ' || ';
						break;
					case T_IS_NOT_EQUAL:
						$code .= ' != ';
						break;
					case T_IS_EQUAL:
						$code .= ' == ';
						break;
					case T_IS_NOT_IDENTICAL:
						$code = '!is_identical(' . $code . ', ';
						$post = ')';
						break;
					case T_IS_IDENTICAL:
						$code = 'is_identical(' . $code . ', ';
						$post = ')';
						break;
					case '^':
						$code .= ' ^ ';
						break;
					case '[':
						$code .= '[';
						$inbrace = true;
						break;
					case ']':
						$code .= ']';
						$inbrace = false;
						break;
					case '-':
						if($tokenizer->tokens[$i - 1] != ',' && $tokenizer->tokens[$i - 1] != '(' && $tokenizer->tokens[$i - 1] != '.')
							$code .= ' - ';
						break;
					case '+':
						$code .= ' + ';
						break;
					case '%':
						$code .= ' % ';
						break;
					case '/':
						$code .= ' / ';
						break;
					case '|':
						$code .= ' | ';
						break;
					case '.':
						$code .= ' + ';
						$inconcat = true;
						break;
					default:
						break;
				}
			}
			$params[] = $pre . $code . $post;
			if(isset($tokens[$i]) && ((!is_array($tokens[$i]) && $tokens[$i] != ',') || $in < 0))
				--$i;
			return array(implode(' = ', $params), $i);
		}
		function debug_token(&$tokenizer, $token, $token_ = null)
		{
			for($i = $token; $i < count($tokenizer->tokens); ++$i)
			{
				if($token_ !== null && $tokenizer->tokens[$i] == $token_)
					break;
				if(is_array($tokenizer->tokens[$i]))
					echo $i, ' - ', token_name($tokenizer->tokens[$i][0]), ': "', $tokenizer->tokens[$i][1], '"', "\n";
				else
					echo $i, ' - "', $tokenizer->tokens[$i], '"', "\n";
			}
		}
		function AddCode($line, $function = null)
		{
			if($function === null)
				$function = $this->curfunction;
			if($this->tabs > 0)
				$this->code[$this->functions[$function]][] = str_repeat("\t", $this->tabs) . $line;
			else
			$this->code[$this->functions[$function]][] = $line;
		}
		function Convert()
		{
			$flags = (string) null;
			$code = (string) null;
			$used = array();
			foreach($this->includes as $include)
			{
				if(!in_array($include, $used))
				{
					$code .= '#include <' . $include . '>' . "\n";
					$used[] = $include;
				}
			}
			if($this->namespace != null)
				$code .= 'using namespace ' . $this->namespace .';' . "\n";
			$code .= implode(null, file('php_var.cpp')) . "\n\n";
			$used = array();
			foreach($this->cppincludes as $include)
			{
				if(!in_array($include, $used))
				{
					$code .= implode(null, file('functions/' . $include)) . "\n\n";
					$used[] = $include;
				}
			}
			$used = array();
			foreach($this->libs as $lib)
			{
				if(!in_array($lib, $used))
				{
					$flags .= '-l' . $lib . ' ';
					$used[] = $lib;
				}
			}
			foreach($this->globals as $glob)
				$code .= 'php_var _' . $glob . ';' . "\n";
			foreach($this->defines as $def => $val)
				$code .= '#define ' . $def . ' ' . $val . "\n";
			foreach($this->classes as $class => $arr)
			{
				$code .= 'class ' . $class . "\n";
				$code .= '{' . "\n";
				$code .= 'public:' . "\n";
				foreach($arr['public'] as $var)
					$code .= "\t" . 'php_var ' . $var . ';' . "\n";
				$code .= 'private:' . "\n";
				foreach($arr['private'] as $var)
					$code .= "\t" . 'php_var ' . $var . ';' . "\n";
				$code .= '};' . "\n";
			}
			$code .= "\n";
			$this->functions = array_reverse($this->functions);
			foreach($this->functions as $function)
				$code .= $this->prototypes[$function][0] . ' ' . $function . '(' . implode(', ', $this->prototypes[$function][1]) . ');' . "\n";
			foreach($this->functions as $function)
			{
				$prototype = $this->prototypes[$function][0] . ' ' . $function . '(' . implode(', ', $this->prototypes[$function][1]) . ')' . "\n";
				$code .= $prototype;
				$code .= '{' . "\n";
				foreach($this->code[$function] as $line)
					$code .= "\t" . $line . "\n";
				if($function == 'main')
					$code .= "\t" . 'return 0;' . "\n";
				$code .= '}' . "\n";
			}
			return array($code, $flags);
		}
	}
?>
